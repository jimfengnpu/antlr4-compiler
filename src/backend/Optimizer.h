#pragma once
#include "../common/IRProcessor.h"

// base class for optimize processor
class Optimizer: public IRProcessor{
public:
    Optimizer(){}
    virtual void applyIR(pSysYIR struction)=0;
    virtual void apply(ASTVisitor& visitor){
        for(auto& func: visitor.functions){
            for(auto p: func->blocks){
                for(auto& ir: p->structions){
                    applyIR(ir);
                }
            }
        }
    }
};