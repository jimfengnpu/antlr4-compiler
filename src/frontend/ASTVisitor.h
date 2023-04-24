#pragma once
#include "generated/SysYBaseVisitor.h"
#include <list>


class ASTVisitor: SysYBaseVisitor{
// public:
    
    ASTVisitor() {
        
    }
    virtual std::any visitCompUnit(SysYParser::CompUnitContext * ctx)override;
};