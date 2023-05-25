#pragma once
#include "../frontend/ASTVisitor.h"


class IRProcessor{
public:
    IRProcessor()=default;
    virtual void apply(ASTVisitor& visitor)=0;
    virtual pBlock visit(pBlock root)=0;
};

class IRProcessors{
public:
    vector<IRProcessor*> processors;
    ASTVisitor& visitor;
    IRProcessors(ASTVisitor& visitor): visitor(visitor){}
    void apply(){
        for(auto proc: processors){
            proc->apply(visitor);
        }
    }
    void add(IRProcessor* proc){
        processors.push_back(proc);
    }
};
