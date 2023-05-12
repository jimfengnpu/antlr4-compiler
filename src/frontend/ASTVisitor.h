#pragma once
#include "antlr4-runtime.h"
#include "generated/SysYBaseVisitor.h"
#include "../common/SysYIR.h"


class ASTVisitor: public SysYBaseVisitor{
    SymbolTable globalSymbolTable;
    SysYParser::BlockContext* curScopeBlock;
public:
    std::vector<IRFunc *> functions;
    IRFunc* curFunc;
    pBlock curBlock;
    // ASTVisitor() = default;
    pBlock creatFunction(string name, 
        SysYParser::BlockContext* blockContext,
        int returnType, vector<pIRIntObj>& args) {
        auto func = new IRFunc(returnType, name, args, &(blockContext->symbolTable));
        functions.push_back(func);
        pBlock block = make_shared<IRBlock>(IR_NORMAL, name);
        func->blocks.push_back(block);
        return block;
    }
    template<typename _Tp, typename... _Args>
    inline shared_ptr<_Tp> newMember(_Args&&... __args) {
        auto obj = make_shared<_Tp>(forward<_Args>(__args)...);
        auto name = std::get<sizeof...(__args) -1>(std::forward_as_tuple(std::forward<_Args>(__args)...));
        if(nullptr != curFunc && (string(name).empty())){
            obj.get()->name = curFunc->getDefaultName(obj);
        }
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

    virtual std::any visitChildren(antlr4::tree::ParseTree *ctx)override;
    virtual std::any visitCompUnit(SysYParser::CompUnitContext * ctx)override;
    virtual std::any visitFuncDef(SysYParser::FuncDefContext* ctx)override;
    virtual std::any visitDecl(SysYParser::DeclContext* ctx)override;
    virtual std::any visitDef(SysYParser::DefContext* ctx)override;
    virtual std::any visitBType(SysYParser::BTypeContext* ctx)override;
    virtual std::any visitInitVal(SysYParser::InitValContext* ctx, pIRIntObj Obj);
    virtual std::any visitExp(SysYParser::ExpContext* ctx)override;
    virtual void initArrVal(SysYParser::InitValContext* ctx, pIRIntArrObj obj, int size, int level, int start);
};
