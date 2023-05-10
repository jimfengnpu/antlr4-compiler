#pragma once
#include "antlr4-runtime.h"
#include "generated/SysYBaseVisitor.h"
#include "../common/SysYIR.h"


class ASTVisitor: public SysYBaseVisitor{
public:
    SymbolTable symbolTable;
    std::vector<pBlock> blocks;
    pBlock cur_block;
    // ASTVisitor() = default;
    pBlock creatNewBlock(string name="", pBlock from=nullptr) {
        pBlock block = make_shared<IRBlock>(name);
        if(from != nullptr) {
            block->from = from;
            from->next = block;
        }
        blocks.push_back(block);
        return block;
    }

    pIRObj registerIndent(pIRObj obj){
        symbolTable.symbol_stack.push_back(obj);
        return obj;
    }
    virtual std::any visitChildren(antlr4::tree::ParseTree *ctx)override;
    virtual std::any visitCompUnit(SysYParser::CompUnitContext * ctx)override;
    virtual std::any visitDecl(SysYParser::DeclContext* ctx)override;
    virtual std::any visitDef(SysYParser::DefContext* ctx)override;
    virtual std::any visitBType(SysYParser::BTypeContext* ctx)override;
    virtual std::any visitInitVal(SysYParser::InitValContext* ctx, pIRIntObj Obj);
    virtual std::any visitExp(SysYParser::ExpContext* ctx)override;
    virtual void initArrVal(SysYParser::InitValContext* ctx, pIRIntArrObj obj, int size, int level, int start);
};