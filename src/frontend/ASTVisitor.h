#pragma once
#include "generated/SysYBaseVisitor.h"
#include "SysYIR.h"


class ASTVisitor: SysYBaseVisitor{
// public:

    ASTVisitor() {
        
    }
    virtual std::any visitCompUnit(SysYParser::CompUnitContext * ctx)override;
};