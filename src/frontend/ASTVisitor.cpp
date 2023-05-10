#include "ASTVisitor.h"

std::any ASTVisitor::visitChildren(antlr4::tree::ParseTree *ctx) {
    for(auto child: ctx->children) {
        child->accept(this);
    }
    return nullptr;
}

std::any ASTVisitor::visitCompUnit(SysYParser::CompUnitContext * ctx) {
    cur_block = creatNewBlock("global");
    visitChildren(ctx);
    return false;
}

std::any ASTVisitor::visitDecl(SysYParser::DeclContext* ctx) {
    ctx->is_const = !(ctx->ConstPrefix() == nullptr);
    ctx->type =  any_cast<int>(visit(ctx->bType()));
    for(auto defCtx: ctx->def()) {
        visit(defCtx);
    }
    return nullptr;
}

std::any ASTVisitor::visitBType(SysYParser::BTypeContext* ctx) {
    if(!(ctx->FloatType() == nullptr))return IR_FLOAT;
    return IR_INT;
}

void ASTVisitor::initArrVal(SysYParser::InitValContext* ctx, pIRIntArrObj obj, int size, int level, int start){
    cout<<"arrInit "<<size<<" "<<start<<endl;
    for(auto initVal: ctx->initVal()) {
        cout<< cur_block.get() <<endl;
        if(auto exp = initVal->exp()){
            pIRIntValObj expVal = any_cast<pIRIntValObj>(visitExp(exp));
            pIRIntValObj arrMemVal = make_shared<IRIntValObj>(obj, start);
            obj.get()->value[start] = arrMemVal;
            cur_block->insertIR(IRType::ASSIGN, arrMemVal, expVal, nullptr);
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
        cur_block.get()->insertIR(IRType::ASSIGN, valObj, 
            any_cast<pIRIntValObj>(visitExp(ctx->exp())), nullptr);
        return ctx->exp()->obj;
    }else{
        auto arrObj = dynamic_pointer_cast<IRIntArrObj>(obj);
        initArrVal(ctx, arrObj, arrObj.get()->size, 0, 0);
        return nullptr;
    }
    // cout<< "end initVal"<<endl;
}

std::any ASTVisitor::visitDef(SysYParser::DefContext* ctx) {
    cout << "enter def"<<endl;
    std::string identity = ctx->Ident()->getText();
    SysYParser::DeclContext* declCtx = (SysYParser::DeclContext*)ctx->parent;
    auto arrVec = ctx->arrAccess();
    if(arrVec.empty()){
        ctx->obj = make_shared<IRIntValObj>(declCtx->is_const, 0, identity);
    }else{
        vector<int> dims;
        for(int i=0; i<arrVec.size(); i++) {
            pIRIntValObj val = any_cast<pIRIntValObj>(visit(arrVec[i]->exp()));
            int s = val.get()->value;
            dims.push_back(s);
        }
        ctx->obj = make_shared<IRIntArrObj>(declCtx->is_const,dims,identity);
    }
    if(ctx->initVal()) {
        visitInitVal(ctx->initVal(), ctx->obj);
    }
    registerIndent(ctx->obj);
    cout<< "exit def" <<endl;
    return nullptr;
}

std::any ASTVisitor::visitExp(SysYParser::ExpContext* ctx) {
    if(auto v = ctx->IntConstant()){
        ctx->obj = make_shared<IRIntValObj>(true,  stoi(v->getText()));
    }else if(auto v = ctx->lVal()){

    }
    return ctx->obj;
}