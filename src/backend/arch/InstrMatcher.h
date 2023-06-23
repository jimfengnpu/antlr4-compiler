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
        triggers.push_back(new LiveCalculator());
        addTriggers();
        for(auto& f: visitor.functions){
            if(f->entry){
                for(pBlock block: f->blocks){
                    visit(block);
                }
                pBlock last=nullptr;
                for(pBlock block=f->entry; block;){
                    if(last){
                        last->asmNextBlock = block;
                    }
                    last = block;
                    block = archInfo->matchBlockEnd(block);
                }
            }
        }
    }
};

#endif