#include "ASTVisitor.h"

std::any ASTVisitor::visitChildren(antlr4::tree::ParseTree *ctx) {
    for(auto child: ctx->children) {
        child->accept(this);
    }
    return nullptr;
}

std::any ASTVisitor::visitCompUnit(SysYParser::CompUnitContext * ctx) {
    visitChildren(ctx);
    return nullptr != globalSymbolTable.findSymbol("main");
}

std::any ASTVisitor::visitFuncDef(SysYParser::FuncDefContext* ctx) {
    ctx->returnType =  any_cast<int>(visit(ctx->funcType()));
    std::string identity = ctx->Ident()->getText();
    vector<pIRIntObj> params;
    for(auto fParam: ctx->funcFParam()) {
        params.push_back(any_cast<pIRIntObj>(visit(fParam)));
    }
    SysYParser::BlockContext *blockCtx = ctx->block();
    
    pBlock funcBlock = creatFunction(identity, ctx->block(), 
        ctx->returnType, params);
    visit(blockCtx);
    return nullptr;
}

std::any ASTVisitor::visitFuncType(SysYParser::FuncTypeContext* ctx) {
    if(ctx->IntType() != nullptr)return IR_INT;
    return IR_VOID;
}

std::any ASTVisitor::visitFuncFParam(SysYParser::FuncFParamContext* ctx) {
    int fParamType = any_cast<int>(visit(ctx->bType()));
    std::string identity = ctx->Ident()->getText();
    pIRIntObj fParamVal;
    if(auto arrParam = ctx->funcArrParam()) {
        vector<int> dim = {1};
        for(auto arrAccess: arrParam->arrAccess()) {
            pIRIntValObj val = any_cast<pIRIntValObj>(visit(arrAccess->exp()));
            dim.push_back(val.get()->value);
        }
        fParamVal = make_shared<IRIntArrObj>(false, dim, identity);
    }else {
        fParamVal = make_shared<IRIntValObj>(false, 0, identity);
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

void ASTVisitor::initArrVal(SysYParser::InitValContext* ctx, pIRIntArrObj obj, int size, int level, int start){
    cout<<"arrInit "<<size<<" "<<start<<endl;
    for(auto initVal: ctx->initVal()) {
        if(auto exp = initVal->exp()){
            pIRIntValObj expVal = any_cast<pIRIntValObj>(visitExp(exp));
            pIRIntValObj arrMemVal = newObj<IRIntValObj>(obj, start, "");
            obj.get()->value[start] = arrMemVal;
            if(nullptr != curBlock){
                curBlock->insertIR(IRType::ASSIGN, arrMemVal, expVal, nullptr);
            }else{
                arrMemVal.get()->value = expVal.get()->value;
            }
            start ++;
        }else{
            int childSize = size/(obj.get()->dims[level]);
            initArrVal(initVal, obj, childSize, level+1, start);
            start += childSize;
        }
    }
}

std::any ASTVisitor::visitInitVal(SysYParser::InitValContext* ctx, pIRIntObj obj) {
    cout<< "enter initVal"<<endl;
    if(auto valObj = dynamic_pointer_cast<IRIntValObj>(obj)){
        pIRIntValObj expVal = any_cast<pIRIntValObj>(visitExp(ctx->exp()));
        if(nullptr != curBlock){
            curBlock.get()->insertIR(IRType::ASSIGN, valObj, expVal, nullptr);
        }else {
            valObj.get()->value = expVal.get()->value;
        }
        return ctx->exp()->obj;
    }else{
        auto arrObj = dynamic_pointer_cast<IRIntArrObj>(obj);
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
        ctx->obj = newObj<IRIntValObj>(declCtx->isConst, 0, identity);
    }else{
        vector<int> dims;
        for(int i=0; i<arrVec.size(); i++) {
            pIRIntValObj val = any_cast<pIRIntValObj>(visit(arrVec[i]->exp()));
            int s = val.get()->value;
            dims.push_back(s);
        }
        ctx->obj = newObj<IRIntArrObj>(declCtx->isConst, dims, identity);
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
        ctx->obj = newObj<IRIntValObj>(true,  stoi(text.substr(start), &idx, base), "");
    }else if(auto v = ctx->lVal()){
        string name = v->Ident()->getText();
        auto symbol_obj = globalSymbolTable.findSymbol(name);
        if(symbol_obj == nullptr)throw runtime_error("undefined symbol:" + name);
    }else{
        bool is_const = true;
        for(auto exp: ctx->exp()){
            visit(exp);
            is_const = is_const && (exp->obj.get()->isConst);
        }
        if(ctx->op != nullptr) {
            string op = ctx->op->getText();
            int num_op = ctx->children.size();
            IRType type = opfinder[num_op][op];
            if(is_const){
                int value = 0;
                switch(type){
                    case IRType::ADD:
                        value = ctx->exp(0)->obj.get()->value + ctx->exp(1)->obj.get()->value;break;
                    case IRType::SUB:
                        value = ctx->exp(0)->obj.get()->value - ctx->exp(1)->obj.get()->value;break;
                    case IRType::MUL:
                        value = ctx->exp(0)->obj.get()->value * ctx->exp(1)->obj.get()->value;break;
                    case IRType::DIV:
                        if(ctx->exp(1)->obj.get()->value == 0)throw runtime_error("divided by zero");
                        value = ctx->exp(0)->obj.get()->value / ctx->exp(1)->obj.get()->value;break;
                    case IRType::MOD:
                        if(ctx->exp(1)->obj.get()->value == 0)throw runtime_error("divided by zero");
                        value = ctx->exp(0)->obj.get()->value % ctx->exp(1)->obj.get()->value;break;
                }
            }else{
                ctx->obj = newObj<IRIntValObj>(false, 0, "");
                curBlock.get()->insertIR(type, ctx->obj, ctx->exp(0)->obj, ctx->exp(1)->obj);
            }
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

// std::any ASTVisitor::visitAssignStmt(SysYParser::AssignStmtContext* ctx) {

// }
