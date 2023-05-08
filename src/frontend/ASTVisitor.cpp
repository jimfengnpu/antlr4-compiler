#include "ASTVisitor.h"

std::any ASTVisitor::visitChildren(antlr4::tree::ParseTree *ctx) {
    for(auto child: ctx->children) {
        child->accept(this);
    }
    return nullptr;
}

std::any ASTVisitor::visitCompUnit(SysYParser::CompUnitContext * ctx) {
    cur_block = creatNewBlock(nullptr);
    visitChildren(ctx);
    return false;
}

std::any ASTVisitor::visitDecl(SysYParser::DeclContext* ctx) {
    ctx->is_const = !(ctx->ConstPrefix() == nullptr);
    if(ctx->is_const) cout<< "const ";
    ctx->type =  any_cast<int>(visit(ctx->bType()));
    cout<<ctx->type<<endl;
    for(auto defCtx: ctx->def()) {
        visit(defCtx);
    }
    return nullptr;
}

std::any ASTVisitor::visitBType(SysYParser::BTypeContext* ctx) {
    if(!(ctx->FloatType() == nullptr))return IR_FLOAT;
    return IR_INT;
}

std::any ASTVisitor::visitInitVal(SysYParser::InitValContext* ctx, pIRObj Obj, int childSize, int start) {
    for(auto child: ctx->children) {
        if(
    }
}

std::any ASTVisitor::visitDef(SysYParser::DefContext* ctx) {
    std::string identity = ctx->Ident()->getText();
    SysYParser::DeclContext* declCtx = (SysYParser::DeclContext*)ctx->parent;
    auto arrVec = ctx->arrAccess();
    int elemSize = 1;
    if(arrVec.empty()){
        ctx->obj = make_shared<IRIntValObj>(IRIntValObj(declCtx->is_const, 0, identity));
    }else{
        vector<int> dims;
        for(int i=0; i<arrVec.size(); i++) {
            shared_ptr<IRIntValObj> val = any_cast<shared_ptr<IRIntValObj> >(visit(arrVec[i]));
            int s = val.get()->value;
            dims.push_back(s);
            if(i)elemSize *= s;
        }
        ctx->obj = make_shared<IRIntArrObj>(IRIntArrObj(declCtx->is_const,dims,identity));
    }
    if(ctx->initVal()) {
        visitInitVal(ctx->initVal(), ctx->obj, elemSize, 0);
    }
    registerIndent(ctx->obj);
    return nullptr;
}
