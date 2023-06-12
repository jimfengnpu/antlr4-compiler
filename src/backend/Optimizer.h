#pragma once
#include "../common/IRProcessor.h"

// base class for optimize processor
class Optimizer: public IRProcessor{
    deque<pBlock> workList;
    map<pBlock, bool> visited;
public:
    bool changed;
    Optimizer(){}
    virtual void applyBlock(pBlock block)=0;
    virtual void apply(ASTVisitor& visitor){
        for(auto& func: visitor.functions){
            if(func->entry){
                do{
                    workList.clear();
                    visited.clear();
                    workList.push_back(func->entry);
                    changed = false;
                    while(workList.size()){
                        auto p = workList.front();
                        workList.pop_front();
                        visited[p] = true;
                        applyBlock(p);
                        if(p->nextNormal && (!visited[p->nextNormal]))
                            workList.push_back(p->nextNormal);
                        if(p->nextBranch && (!visited[p->nextBranch]))
                            workList.push_back(p->nextBranch);
                    }
                }while(changed);
            }
        }
    }
};

class ConstBroadcast: public Optimizer{
    map<pBlock, map<pIRScalValObj, int> > constState;
public:
    ConstBroadcast(){}
    void setConstState(pIRObj obj);
    virtual void processDependency(IRProcessors* procs);
    virtual void applyBlock(pBlock block);
};