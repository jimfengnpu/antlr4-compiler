#pragma once
#include "../frontend/ASTVisitor.h"


class IRProcessor{
public:
    ASTVisitor& visitor;
    IRProcessor(ASTVisitor& visitor): visitor(visitor){}
    virtual void apply()=0;
};
