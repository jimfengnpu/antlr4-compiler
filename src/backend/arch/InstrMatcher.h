#ifndef INSTR_MATCHER_H
#define INSTR_MATCHER_H

#include "IRProcessor.h"
#include "Arch.h"

class InstrMatcher: public IRProcessor{
    BaseArch* archInfo;
public:
    InstrMatcher(BaseArch* arch):archInfo(arch){}
    virtual pBlock visit(pBlock block);
    virtual void apply(ASTVisitor& visitor){
        for(auto& f: visitor.functions){
            if(f->entry){
                for(pBlock block: f->blocks){
                    visit(block);
                }
            }
        }
    }
};

#endif