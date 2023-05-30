#pragma once
#include "../common/IRProcessor.h"

class SSAMaker: public IRProcessor{
public:
    SSAMaker(){}
    virtual pBlock visit(pBlock block);
    virtual void apply(){
        
    }
};