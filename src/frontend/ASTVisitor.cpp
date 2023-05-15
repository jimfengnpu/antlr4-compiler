#include "ASTVisitor.h"

std::any ASTVisitor::visitChildren(antlr4::tree::ParseTree *ctx) {
    for(auto child: ctx->children) {
        child->accept(this);
    }
    return nullptr;
}

std::any ASTVisitor::visitCompUnit(SysYParser::CompUnitContext * ctx) {
    globalData = make_shared<IRBlock>(IR_NORMAL, ".global");
    curBlock = globalData;
    // curFunc->blocks.push_back(curBlock);
    visitChildren(ctx);
    return nullptr != globalSymbolTable.findSymbol("main");
}

std::any ASTVisitor::visitFuncDef(SysYParser::FuncDefContext* ctx) {
    ctx->returnType =  any_cast<int>(visit(ctx->funcType()));
    std::string identity = ctx->Ident()->getText();
    vector<pIRValObj> params;
    for(auto fParam: ctx->funcFParam()) {
        params.push_back(any_cast<pIRValObj>(visit(fParam)));
    }
    SysYParser::BlockContext *blockCtx = ctx->block();
    
    pBlock funcBlock = creatFunction(identity, ctx->block(), 
        ctx->returnType, params);
    curBlock = funcBlock;
    // curFunc->blocks.push_back(curBlock);
    visit(blockCtx);
    curFunc->blocks.push_back(curFunc->exit);
    return nullptr;
}

std::any ASTVisitor::visitFuncType(SysYParser::FuncTypeContext* ctx) {
    if(ctx->IntType() != nullptr)return IR_INT;
    return IR_VOID;
}

std::any ASTVisitor::visitFuncFParam(SysYParser::FuncFParamContext* ctx) {
    int fParamType = any_cast<int>(visit(ctx->bType()));
    std::string identity = ctx->Ident()->getText();
    pIRValObj fParamVal;
    if(auto arrParam = ctx->funcArrParam()) {
        vector<int> dim = {1};
        for(auto arrAccess: arrParam->arrAccess()) {
            pIRScalValObj val = any_cast<pIRScalValObj>(visit(arrAccess->exp()));
            dim.push_back(val.get()->value);
        }
        fParamVal = make_shared<IRArrValObj>(false, dim, identity);
    }else {
        fParamVal = make_shared<IRScalValObj>(false, 0, identity);
    }
    return fParamVal;
}

std::any ASTVisitor::visitDecl(SysYParser::DeclContext* ctx) {
    ctx->isConst = !(ctx->ConstPrefix() == nullptr);
    ctx->type =  any_cast<int>(visit(ctx->bType()));
    for(auto defCtx: ctx->def()) {
        visit(defCtx);
    }
    return nullptr;
}

std::any ASTVisitor::visitBType(SysYParser::BTypeContext* ctx) {
    // if(ctx->FloatType() != nullptr)return IR_FLOAT;
    return IR_INT;
}

void ASTVisitor::initArrVal(SysYParser::InitValContext* ctx, pIRArrValObj obj, int size, int level, int start){
    cout<<"arrInit "<<size<<" "<<start<<endl;
    int childSize = size/(obj.get()->dims[level]);
    for(auto initVal: ctx->initVal()) {
        if(auto exp = initVal->exp()){
            pIRScalValObj expVal = any_cast<pIRScalValObj>(visitExp(exp));
            pIRScalValObj arrMemVal = newObj<IRScalValObj>(obj, "");
            assert(nullptr != curBlock);
            curBlock->insertIR(IRType::IDX, arrMemVal, obj, newObj<IRScalValObj>(true, start, ""));
            curBlock->insertIR(IRType::ASSIGN, arrMemVal, expVal, nullptr);
            start ++;
        }else if(childSize && start % childSize == 0){
            initArrVal(initVal, obj, childSize, level+1, start);
            start += childSize;
        }else {
            initArrVal(initVal, obj, 1, level, start);
            start ++;
        }
    }
}

std::any ASTVisitor::visitInitVal(SysYParser::InitValContext* ctx, pIRValObj obj) {
    // cout<< "enter initVal"<<endl;
    if(auto valObj = dynamic_pointer_cast<IRScalValObj>(obj)){
        pIRValObj expVal = any_cast<pIRValObj>(visitExp(ctx->exp()));
        assert(nullptr != curBlock);
        curBlock.get()->insertIR(IRType::ASSIGN, valObj, expVal, nullptr);
        return ctx->exp()->obj;
    }else{
        auto arrObj = dynamic_pointer_cast<IRArrValObj>(obj);
        initArrVal(ctx, arrObj, arrObj.get()->size, 0, 0);
        return nullptr;
    }
    // cout<< "end initVal"<<endl;
    return nullptr;
}

std::any ASTVisitor::visitDef(SysYParser::DefContext* ctx) {
    // cout << "enter def"<<endl;
    std::string identity = ctx->Ident()->getText();
    SysYParser::DeclContext* declCtx = (SysYParser::DeclContext*)ctx->parent;
    auto arrVec = ctx->arrAccess();
    if(arrVec.empty()){
        ctx->obj = newObj<IRScalValObj>(declCtx->isConst, 0, identity);
    }else{
        vector<int> dims;
        for(int i=0; i<arrVec.size(); i++) {
            pIRScalValObj val = any_cast<pIRScalValObj>(visit(arrVec[i]->exp()));
            int s = val.get()->value;
            dims.push_back(s);
        }
        ctx->obj = newObj<IRArrValObj>(declCtx->isConst, dims, identity);
    }
    if(ctx->initVal()) {
        visitInitVal(ctx->initVal(), ctx->obj);
    }
    registerIndent(ctx->obj);
    // cout<< "exit def" <<endl;
    return nullptr;
}

std::any ASTVisitor::visitExp(SysYParser::ExpContext* ctx) {
    // cout << "enter exp"<<endl;
    if(auto v = ctx->IntConstant()){
        int base = 10;
        int start = 0;
        size_t idx = 0;
        string text = v->getText();
        if(text[0] == '0' && text.size() > 1){base = 8;start = 1;}
        else if(text[0] == '0' && (text[1] == 'x' || text[1] == 'X')){base = 16;start = 2;}
        cout<< text.substr(start)<< " " << base <<endl;
        ctx->obj = newObj<IRScalValObj>(true,  stoi(text.substr(start), &idx, base), "");
    }else if(auto v = ctx->lVal()){
        auto symbol_obj = any_cast<pIRValObj>(visit(v));
        if(symbol_obj == nullptr)throw runtime_error("can't find symbol");
        ctx->obj = symbol_obj;
    }else{
        bool is_const = true;
        if(ctx->exp().empty())return nullptr;
        for(auto exp: ctx->exp()){
            visit(exp);
            is_const = is_const && (exp->obj.get()->isConst);
        }
        if(ctx->op != nullptr) {
            ctx->obj = newObj<IRScalValObj>(false, 0, "");
            string op = ctx->op->getText();
            int num_op = ctx->exp().size();
            // cout << "exp "<< num_op <<endl;
            IRType type = opfinder[num_op][op];
            // if(is_const){
            //     int value = 0;
            //     switch(type){
            //         case IRType::ADD:
            //             value = ctx->exp(0)->obj.get()->value + ctx->exp(1)->obj.get()->value;break;
            //         case IRType::SUB:
            //             value = ctx->exp(0)->obj.get()->value - ctx->exp(1)->obj.get()->value;break;
            //         case IRType::MUL:
            //             value = ctx->exp(0)->obj.get()->value * ctx->exp(1)->obj.get()->value;break;
            //         case IRType::DIV:
            //             if(ctx->exp(1)->obj.get()->value == 0)throw runtime_error("divided by zero");
            //             value = ctx->exp(0)->obj.get()->value / ctx->exp(1)->obj.get()->value;break;
            //         case IRType::MOD:
            //             if(ctx->exp(1)->obj.get()->value == 0)throw runtime_error("divided by zero");
            //             value = ctx->exp(0)->obj.get()->value % ctx->exp(1)->obj.get()->value;break;
            //     }
            // }else{
            if(num_op > 1)
                curBlock->insertIR(type, ctx->obj, ctx->exp(0)->obj, ctx->exp(1)->obj);
            else 
                curBlock->insertIR(type, ctx->obj, ctx->exp(0)->obj, nullptr);
            // }
        }else if(auto func = ctx->Ident()){
            ctx->obj = newObj<IRScalValObj>(false, 0, "");
            auto funcObj = dynamic_pointer_cast<IRFunc>(findSymbol(func->getText()));
            if(funcObj == nullptr)throw runtime_error("unknown function name");
            auto params = ctx->exp();
            for(auto p = params.rbegin(); p!= params.rend(); p++) {
                curBlock->insertIR(IRType::PARAM, funcObj, (*p)->obj , nullptr);
            }
            curBlock->insertIR(IRType::CALL, ctx->obj, funcObj, nullptr);
        }else {
            ctx->obj = ctx->exp(0)->obj;
        }
    }
    // cout << "exit exp"<<endl;
    return ctx->obj;
}

std::any ASTVisitor::visitBlock(SysYParser::BlockContext* ctx) {
    visitChildren(ctx);
    return nullptr;
}

std::any ASTVisitor::visitCond(SysYParser::CondContext* ctx) {
    if(auto logical = ctx->lop) {
        auto subLeftCond = ctx->cond(0);
        auto subRightCond = ctx->cond(1);
        pBlock midBlock = newFuncBlock(IR_BRANCH);
        if(logical->getText() == "&&") {
            subLeftCond->branchs = {ctx->branchs.first, midBlock};
        }else {
            subLeftCond->branchs = {midBlock, ctx->branchs.second};
        }
        subRightCond->branchs = ctx->branchs;
        visit(subLeftCond);
        curBlock = midBlock;
        visit(subRightCond);
    }else{
        pIRScalValObj result;
        if(auto comp = ctx->comp){
            visit(ctx->exp(0));
            visit(ctx->exp(1));
            result = newObj<IRScalValObj>(false, 0, "");
            string op = comp->getText();
            IRType type = opfinder[0][op];
            curBlock->insertIR(type, result, 
                ctx->exp(0)->obj, ctx->exp(1)->obj);
        }else {
            visit(ctx->exp(0));
            result = dynamic_pointer_cast<IRScalValObj>(ctx->exp(0)->obj);
            assert(result != nullptr);
        }
        if(curBlock->finishBB(ctx->branchs.first, 
            ctx->branchs.second, result))
            curFunc->blocks.push_back(curBlock);
    }
    return nullptr;
}

std::any ASTVisitor::visitLVal(SysYParser::LValContext* ctx) {
    string name = ctx->Ident()->getText();
    auto obj = findSymbol(name);
    if(auto scalObj = dynamic_pointer_cast<IRScalValObj>(obj)){
        return (pIRValObj)scalObj;
    }else{
        auto arrObj = dynamic_pointer_cast<IRArrValObj>(obj);
        auto dim = arrObj.get()->dims;
        int size = arrObj.get()->size;
        auto off = newObj<IRScalValObj>(false, 0, "");
        auto tmp = newObj<IRScalValObj>(false, 0, "");
        auto iter = dim.begin();
        if(curFunc == nullptr)throw runtime_error("lVal array reference global");
        for(auto arrCtx: ctx->arrAccess()) {
            int childSize = size/(*iter);
            curBlock->insertIR(IRType::MUL, tmp, 
                newObj<IRScalValObj>(true, childSize, ""), 
                any_cast<pIRScalValObj>(visit(arrCtx->exp())));
            curBlock->insertIR(IRType::ADD, off, off, tmp);
            iter++;
            size = childSize;
        }
        auto elem = newObj<IRScalValObj>(arrObj, "");
        curBlock->insertIR(IRType::IDX, elem, arrObj, off);
        if(size > 1){
            vector<int> new_dim;
            while(iter != dim.end()){
                new_dim.push_back(*iter);
            }
            auto newArr = newObj<IRArrValObj>(false, new_dim,"");
            curBlock->insertIR(IRType::ARR, newArr, elem, nullptr);
            return (pIRValObj)newArr;
        }
        return (pIRValObj)elem;
    }
    throw runtime_error("no matched symbol lval");
    return nullptr;
}

std::any ASTVisitor::visitAssignStmt(SysYParser::AssignStmtContext* ctx) {
    visit(ctx->exp());
    auto lValObj = any_cast<pIRScalValObj>(visit(ctx->lVal()));
    curBlock->insertIR(IRType::ASSIGN, lValObj, ctx->exp()->obj, nullptr);
    return nullptr;
}

std::any ASTVisitor::visitExpStmt(SysYParser::ExpStmtContext* ctx) {
    if(ctx->exp())
        visit(ctx->exp());
    return nullptr;
}

std::any ASTVisitor::visitBlockStmt(SysYParser::BlockStmtContext* ctx) {
    visitChildren(ctx);
    return nullptr;
}

std::any ASTVisitor::visitCondStmt(SysYParser::CondStmtContext* ctx) {
    pBlock condTrue = newFuncBlock(IR_BRANCH);
    pBlock condFalse = newFuncBlock(IR_BRANCH);
    pBlock condFinal = newFuncBlock(curBlock->blockType);
    auto condCtx = ctx->cond();
    condCtx->branchs = {condFalse, condTrue};
    visit(condCtx);
    curBlock = condTrue;
    visit(ctx->stmt(0));
    if(curBlock->finishBB(condFinal, nullptr, nullptr))
        curFunc->blocks.push_back(curBlock);
    curBlock = condFalse;
    if(ctx->stmt().size() > 1){
        visit(ctx->stmt(1));
    }
    if(curBlock->finishBB(condFinal, nullptr, nullptr))
        curFunc->blocks.push_back(curBlock);
    curBlock = condFinal;
    return nullptr;
}

std::any ASTVisitor::visitLoopStmt(SysYParser::LoopStmtContext* ctx) {
    return nullptr;
}

std::any ASTVisitor::visitBreakStmt(SysYParser::BreakStmtContext* ctx) {

    return nullptr;
}

std::any ASTVisitor::visitContStmt(SysYParser::ContStmtContext* ctx) {

    return nullptr;
}

std::any ASTVisitor::visitReturnStmt(SysYParser::ReturnStmtContext* ctx) {
    if(auto expCtx = ctx->exp()){
        auto retVal = any_cast<pIRValObj>(visit(expCtx));
        if(curFunc->returnVal == nullptr)
            curFunc->returnVal = retVal;
        else
            curBlock->insertIR(IRType::ASSIGN, curFunc->returnVal, retVal, nullptr);
    }
    if(curFunc->exit == nullptr)
        curFunc->exit = newFuncBlock(IR_NORMAL);
    if(curBlock->finishBB(curFunc->exit))
        curFunc->blocks.push_back(curBlock);
    return nullptr;
}