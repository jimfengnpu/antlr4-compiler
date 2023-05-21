#pragma once
#include "antlr4-runtime.h"
#include "generated/SysYBaseVisitor.h"
#include "../common/SysYIR.h"


class ASTVisitor: public SysYBaseVisitor{
    SysYParser::BlockContext* curScopeBlock = nullptr;
public:
    SymbolTable globalSymbolTable;
    std::vector<pIRFunc> functions;
    pIRFunc curFunc = nullptr;
    pBlock curBlock = nullptr;
    pBlock globalData = nullptr;
    
    // ASTVisitor() = default;
    pBlock creatFunction(string name, 
        SysYParser::BlockContext* blockContext,
        int returnType, vector<pIRValObj> args) {
        auto func = make_shared<IRFunc>(returnType, "@" + name, args, 
            blockContext==nullptr? nullptr : &(blockContext->symbolTable));
        functions.push_back(func);
        globalSymbolTable.registerSymbol(func);
        curFunc = func;
        if(blockContext != nullptr){
            func->entry = newFuncBlock(IR_NORMAL);
        }else{
            func->entry = nullptr;
        }
        return func->entry;
    }

    void registerLibFunc(){
        creatFunction("getint", nullptr, IR_INT, vector<pIRValObj>());
        creatFunction("getch", nullptr, IR_INT, vector<pIRValObj>());
        creatFunction("getarray", nullptr, IR_INT, vector<pIRValObj>({
            make_shared<IRArrValObj>(false, vector<int>({1}), "")
        }));
        creatFunction("putint", nullptr, IR_VOID, vector<pIRValObj>({
            make_shared<IRScalValObj>(false, 0, "")}));
        creatFunction("putch", nullptr, IR_VOID, vector<pIRValObj>({
            make_shared<IRScalValObj>(false, 0, "")}));
        creatFunction("putarray", nullptr, IR_VOID, vector<pIRValObj>({
            make_shared<IRScalValObj>(false, 0, ""),
            make_shared<IRArrValObj>(false, vector<int>({1}), "")
        }));
        creatFunction("putf", nullptr, IR_VOID, vector<pIRValObj>({
            make_shared<IRStrValObj>()
        }));
        creatFunction("starttime", nullptr, IR_VOID, vector<pIRValObj>());
        creatFunction("stoptime", nullptr, IR_VOID, vector<pIRValObj>());
    }

    pBlock newFuncBlock(int blockType, string name=string("")) {
        pBlock block = newObj<IRBlock>(blockType, name);
        return block;
    }

    //the last arg must be str name
    template<typename _Tp, typename... _Args>
    inline shared_ptr<_Tp> newObj(_Args&&... __args) {
        auto obj = make_shared<_Tp>(std::forward<_Args>(__args)...);
        // auto name = std::get<sizeof...(__args) -1>(std::forward_as_tuple(__args...));
        // cout << curFunc << " " << name << endl;
        // if(nullptr != curFunc && (string(name).empty())){
        //     obj.get()->name = obj->getDefaultName();
        // }
        obj->scopeSymbols = (curScopeBlock == nullptr)? &globalSymbolTable
                        :&(curScopeBlock->symbolTable);
        return obj;
    }

    pIRObj findSymbol(string name) {
        SysYParser::BlockContext* scope = curScopeBlock;
        while(nullptr != scope) {
            pIRObj obj = scope->symbolTable.findSymbol(name);
            if(obj)return obj;
            scope = scope->upperBlock;
        }
        return globalSymbolTable.findSymbol(name);
    }

    pIRObj registerIndent(pIRObj obj){
        if(curScopeBlock != nullptr){
            curScopeBlock->symbolTable.registerSymbol(obj);
        }
        globalSymbolTable.registerSymbol(obj);
        return obj;
    }

    void insertIR(IRType type, pIRObj t, pIRObj op1, pIRObj op2){
        if(curBlock != nullptr){
            curBlock->insertIR(type, t, op1, op2);
        }
    }

    virtual std::any visitChildren(antlr4::tree::ParseTree *ctx)override;
    virtual std::any visitCompUnit(SysYParser::CompUnitContext * ctx)override;
    virtual std::any visitFuncDef(SysYParser::FuncDefContext* ctx)override;
    virtual std::any visitFuncType(SysYParser::FuncTypeContext* ctx)override;
    virtual std::any visitFuncFParam(SysYParser::FuncFParamContext* ctx)override;
    virtual std::any visitDecl(SysYParser::DeclContext* ctx)override;
    virtual std::any visitDef(SysYParser::DefContext* ctx)override;
    virtual std::any visitBType(SysYParser::BTypeContext* ctx)override;
    virtual void initArrVal(SysYParser::InitValContext* ctx, pIRArrValObj obj, int size, int level, int start);
    virtual std::any visitInitVal(SysYParser::InitValContext* ctx, pIRValObj Obj);
    virtual std::any visitExp(SysYParser::ExpContext* ctx)override;
    virtual std::any visitBlock(SysYParser::BlockContext* ctx)override;
    virtual std::any visitCond(SysYParser::CondContext* ctx)override;
    virtual std::any visitLVal(SysYParser::LValContext* ctx)override;
    virtual std::any visitAssignStmt(SysYParser::AssignStmtContext* ctx)override;
    virtual std::any visitExpStmt(SysYParser::ExpStmtContext* ctx)override;
    virtual std::any visitBlockStmt(SysYParser::BlockStmtContext* ctx)override;
    virtual std::any visitCondStmt(SysYParser::CondStmtContext* ctx)override;
    virtual std::any visitLoopStmt(SysYParser::LoopStmtContext* ctx)override;
    virtual std::any visitBreakStmt(SysYParser::BreakStmtContext* ctx)override;
    virtual std::any visitContStmt(SysYParser::ContStmtContext* ctx)override;
    virtual std::any visitReturnStmt(SysYParser::ReturnStmtContext* ctx)override;
};
