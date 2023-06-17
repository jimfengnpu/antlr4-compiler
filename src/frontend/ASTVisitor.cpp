#include "ASTVisitor.h"
#include "../common/SysYIR.h"

std::any ASTVisitor::visitChildren(antlr4::tree::ParseTree *ctx) {
    for(auto child: ctx->children) {
        child->accept(this);
    }
    return nullptr;
}

std::any ASTVisitor::visitCompUnit(SysYParser::CompUnitContext * ctx) {
    registerLibFunc();
    globalData = make_shared<IRBlock>(IR_NORMAL, ".global");
    globalSymbolTable.isGlobal = true;
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
    if(curFunc->exit == nullptr){
        curFunc->exit = curBlock;
    }else{
        if(curFunc->returnType != IR_VOID)
            insertIR(IRType::ASSIGN, curFunc->returnVal, 
            newObj<IRScalValObj>(0), nullptr);
        finishBB(curFunc->exit);
        curBlock = curFunc->exit;
    }
    insertIR(IRType::RET, nullptr, curFunc->returnVal, nullptr);
    finishBB(nullptr);
    curBlock = globalData;
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
            pIRScalValObj val = toScal(any_cast<pIRValObj>(visit(arrAccess->exp())));
            dim.push_back(val.get()->value);
        }
        fParamVal = make_shared<IRArrValObj>(false, dim, identity);
    }else {
        fParamVal = make_shared<IRScalValObj>(false, identity);
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
    // cout<<"arrInit "<<size<<" "<<start<<endl;
    int s = start;
    int childSize = size/(obj.get()->dims[level]);
    for(auto initVal: ctx->initVal()) {
        if(start - s >= size)break;
        if(auto exp = initVal->exp()){
            pIRScalValObj expVal = toScal(any_cast<pIRValObj>(visitExp(exp)));
            pIRScalValObj arrMemVal = newObj<IRScalValObj>(obj, "");
            assert(nullptr != curBlock);
            insertIR(IRType::IDX, arrMemVal, obj, newObj<IRScalValObj>(start));
            insertIR(IRType::ASSIGN, arrMemVal, expVal, nullptr);
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
    if(auto valObj = toScal(obj)){
        pIRScalValObj expVal = toScal(any_cast<pIRValObj>(visitExp(ctx->exp())));
        assert(nullptr != curBlock);
        if(expVal->isConst)valObj->value = expVal->value;
        insertIR(IRType::ASSIGN, valObj, expVal, nullptr);
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
        ctx->obj = newObj<IRScalValObj>(declCtx->isConst, identity);
    }else{
        vector<int> dims;
        for(int i=0; i<arrVec.size(); i++) {
            pIRScalValObj val = toScal(
                any_cast<pIRValObj>(visit(arrVec[i]->exp())));
            if(!val->isConst)throw runtime_error("array size must be const");
            int s = val.get()->value;
            dims.push_back(s);
        }
        ctx->obj = newObj<IRArrValObj>(declCtx->isConst, dims, identity);
    }
    insertIR(IRType::DEF, ctx->obj, nullptr, nullptr);
    if(ctx->initVal()) {
        visitInitVal(ctx->initVal(), ctx->obj);
    }
    registerIndent(ctx->obj);
    // cout<< "exit def" <<endl;
    return nullptr;
}

pIRScalValObj ASTVisitor::calcExp(IRType type, pIRScalValObj exp1, pIRScalValObj exp2, bool is_const){
    if(is_const){
        int value = 0;
        assert(exp1 != nullptr);
        value = CalConstExp(type, exp1->value, exp2?exp2->value:0);
        return newObj<IRScalValObj>(value);
    }else{
        auto obj = newObj<IRScalValObj>(false, "");
        insertIR(type, obj, exp1, exp2);
        return obj;
    }
}

std::any ASTVisitor::visitExp(SysYParser::ExpContext* ctx) {
    // cout << "enter exp"<<endl;
    if(auto v = ctx->IntConstant()){
        int base = 10;
        int start = 0;
        size_t idx = 0;
        string text = v->getText();
        if(text[0] == '0' && text.size() > 1){base = 8;start = 1;}
        if(text[0] == '0' && (text[1] == 'x' || text[1] == 'X')){
            base = 16;start = 2;
            std::transform(text.begin(), text.end(), text.begin(), ::tolower);
        }
        int val = stol(text.substr(start), &idx, base);
        ctx->obj = newObj<IRScalValObj>(val);
    }else if(auto v = ctx->StringConstant()){
        ctx->obj = newObj<IRStrValObj>(v->getText(), "");
    }else if(auto v = ctx->lVal()){
        auto symbol_obj = any_cast<pIRValObj>(visit(v));
        if(symbol_obj == nullptr)throw runtime_error("can't find symbol");
        ctx->obj = symbol_obj;
    }else{
        bool is_const = true;
        auto expVec = ctx->exp();
        if(!expVec.empty()){
            for(auto exp: ctx->exp()){
                visit(exp);
                is_const = is_const && (exp->obj->isConstant());
            }
        }
        if(ctx->op != nullptr) {
            string op = ctx->op->getText();
            int op_idx = ctx->exp().size() - 1;
            // cout << "exp "<< num_op <<endl;
            IRType type = opfinder[op_idx][op];
            pIRScalValObj exp1 = toScal(ctx->exp(0)->obj);
            pIRScalValObj exp2 = nullptr;
            if(op_idx == 1)
                exp2 = toScal(ctx->exp(1)->obj);
            ctx->obj = calcExp(type, exp1, exp2, is_const);
        }else if(auto func = ctx->Ident()){
            ctx->obj = newObj<IRScalValObj>(false, "");
            auto funcObj = dynamic_pointer_cast<IRFunc>(findSymbol("@" + func->getText()));
            if(funcObj == nullptr)throw runtime_error("unknown function name");
            if(!expVec.empty()){
                for(auto p = expVec.rbegin(); p!= expVec.rend(); p++) {
                    insertIR(IRType::PARAM, nullptr, (*p)->obj, nullptr);
                }
            }
            insertIR(IRType::CALL, ctx->obj, funcObj, nullptr);
        }else {
            ctx->obj = ctx->exp(0)->obj;
        }
    }
    // cout << "exit exp"<<endl;
    return ctx->obj;
}

std::any ASTVisitor::visitBlock(SysYParser::BlockContext* ctx) {
    ctx->upperBlock = curScopeBlock;
    curScopeBlock = ctx;
    visitChildren(ctx);
    curScopeBlock = ctx->upperBlock;
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
        visit(ctx->exp());
        result = toScal(ctx->exp()->obj);
        assert(result != nullptr);
        finishBB(ctx->branchs.first, ctx->branchs.second, result);
    }
    return nullptr;
}

std::any ASTVisitor::visitLVal(SysYParser::LValContext* ctx) {
    string name = ctx->Ident()->getText();
    auto obj = findSymbol(name);
    if(auto scalObj = toScal(obj)){
        return (pIRValObj)scalObj;
    }else if(auto arrObj = dynamic_pointer_cast<IRArrValObj>(obj)){
        assert(arrObj != nullptr);
        if(curFunc == nullptr)throw runtime_error("lVal array reference global");
        auto dim = arrObj.get()->dims;
        int size = arrObj.get()->size;
        auto arrCtxs = ctx->arrAccess();
        pIRScalValObj off = newObj<IRScalValObj>(0), tmp = nullptr;
        auto iter = dim.begin();
        auto arrEndIter = dim.begin();
        auto arrIter = arrCtxs.begin();
        while(iter != dim.end()){
            pIRScalValObj dimExp = newObj<IRScalValObj>(0);
            tmp = calcExp(IRType::MUL, newObj<IRScalValObj>(*iter), off, off->isConstant());
            if(arrIter != arrCtxs.end()){
                dimExp = toScal(any_cast<pIRValObj>(visit((*arrIter)->exp())));
                arrIter ++;
                arrEndIter++;
            }
            off = calcExp(IRType::ADD, dimExp, tmp, dimExp->isConstant()&& tmp->isConstant());
            iter++;
        }
        
        if(arrEndIter != dim.end()){
            vector<int> new_dim;
            while(arrEndIter != dim.end()){
                new_dim.push_back(*arrEndIter);
                arrEndIter++;
            }
            auto newArr = newObj<IRArrValObj>(arrObj, new_dim,"");
            insertIR(IRType::ARR, newArr, arrObj, off);
            return (pIRValObj)newArr;
        }
        auto elem = newObj<IRScalValObj>(arrObj, "");
        insertIR(IRType::IDX, elem, arrObj, off);
        return (pIRValObj)elem;
    }
    throw runtime_error("no matched symbol lval");
    return nullptr;
}

std::any ASTVisitor::visitAssignStmt(SysYParser::AssignStmtContext* ctx) {
    visit(ctx->exp());
    auto lValObj = any_cast<pIRValObj>(visit(ctx->lVal()));
    insertIR(IRType::ASSIGN, lValObj, ctx->exp()->obj, nullptr);
    // if(!lValObj->isTmp){
    //     curBlock->defObj.push_back(lValObj);
    // }
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
    pBlock condFinal = newFuncBlock(IR_NORMAL);
    auto condCtx = ctx->cond();
    condCtx->branchs = {condFalse, condTrue};
    if(nullptr != curBlock){
        visit(condCtx);
        curBlock = condTrue;
        visit(ctx->stmt(0));
        finishBB(condFinal);
        curBlock = condFalse;
        if(ctx->stmt().size() > 1){
            visit(ctx->stmt(1));
        }
        finishBB(condFinal);
        curBlock = condFinal;
    }
    return nullptr;
}

std::any ASTVisitor::visitLoopStmt(SysYParser::LoopStmtContext* ctx) {
    pBlock condBranch = newFuncBlock(IR_NORMAL);
    pBlock condLoop = newFuncBlock(IR_LOOP);
    pBlock condOut = newFuncBlock(IR_NORMAL);
    auto condCtx = ctx->cond();
    ctx->loopEntry = condBranch;
    condCtx->branchs = {condOut, condLoop};
    if(nullptr != curBlock){
        finishBB(condBranch);
        curBlock = condBranch;
        visit(condCtx);
        curBlock = condLoop;
        visit(ctx->stmt());
        finishBB(condBranch);
        curBlock = condOut;
    }
    return nullptr;
}

std::any ASTVisitor::visitBreakStmt(SysYParser::BreakStmtContext* ctx) {
    SysYParser::LoopStmtContext* loopCtx = nullptr;
    antlr4::tree::ParseTree* tree = ctx->parent;
    while(ctx != nullptr){
        loopCtx = dynamic_cast<SysYParser::LoopStmtContext*>(tree);
        if(loopCtx != nullptr)break;
        tree = tree->parent;
    }
    if(loopCtx == nullptr)throw runtime_error("no outside loop");
    finishBB(loopCtx->cond()->branchs.first);
    curBlock = nullptr;
    return nullptr;
}

std::any ASTVisitor::visitContStmt(SysYParser::ContStmtContext* ctx) {
    SysYParser::LoopStmtContext* loopCtx = nullptr;
    antlr4::tree::ParseTree* tree = ctx->parent;
    while(ctx != nullptr){
        loopCtx = dynamic_cast<SysYParser::LoopStmtContext*>(tree);
        if(loopCtx != nullptr)break;
        tree = tree->parent;
    }
    if(loopCtx == nullptr)throw runtime_error("no outside loop");
    finishBB(loopCtx->loopEntry);
    curBlock = nullptr;
    return nullptr;
}

std::any ASTVisitor::visitReturnStmt(SysYParser::ReturnStmtContext* ctx) {
    if(auto expCtx = ctx->exp()){
        auto retVal = any_cast<pIRValObj>(visit(expCtx));
        if(curFunc->returnVal == nullptr)
            curFunc->returnVal = newObj<IRScalValObj>(false, "");
        insertIR(IRType::ASSIGN, curFunc->returnVal, retVal, nullptr);
    }
    if(curFunc->exit == nullptr)
        curFunc->exit = newFuncBlock(IR_NORMAL);
    finishBB(curFunc->exit);
    curBlock = nullptr;
    return nullptr;
}