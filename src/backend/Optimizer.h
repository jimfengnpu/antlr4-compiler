#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "IRProcessor.h"

// base class for optimize processor
class Optimizer: public IRProcessor{
public:
    deque<pBlock> workList;
    map<pBlock, bool> visited;
    bool changed=false;
    Optimizer()=default;
    virtual void applyBlock(pBlock block)=0;
    virtual void applyNextBlock(pBlock block){
        if(block->nextNormal && (!visited[block->nextNormal]))
            workList.push_back(block->nextNormal);
        if(block->nextBranch && (!visited[block->nextBranch]))
            workList.push_back(block->nextBranch);
    }
    virtual void applyFunc(pIRFunc func){}
    virtual void prepareTriggers(){}
    virtual void apply(Prog& prog){
        bool triggerNeeded = false;
        applyBlock(prog.globalData);
        for(auto& func: prog.functions){
            if(func->entry){
                do{
                    workList.clear();
                    visited.clear();
                    workList.push_back(func->entry);
                    changed = false;
                    while(workList.size()){
                        // for(auto x: workList){
                        //     cout << x->name << " ";
                        // }
                        // cout << endl;
                        auto block = workList.front();
                        // if(block->name == "M3"){
                        //     cout << "break";
                        // }
                        workList.pop_front();
                        if(!visited[block]){
                            visited[block] = true;
                            applyBlock(block);
                        }
                        applyNextBlock(block);
                    }
                    applyFunc(func);
                    triggerNeeded |= changed;
                }while(changed);
            }
        }
        if(triggerNeeded){
            prepareTriggers();
            addTriggers();
        }
    }
};

class BlockPruner: public Optimizer{
    vector<pBlock> deleted;
public:
    BlockPruner(){}
    bool checkRemoveEmptyBlock(pBlock block);
    virtual void applyBlock(pBlock block)override{}
    virtual void applyFunc(pIRFunc func)override;
    virtual void prepareTriggers()override;
};

class ConstBroadcast: public Optimizer{
public:
    ConstBroadcast(){}
    void setConstState(pBlock block, pIRObj obj);
    virtual void applyBlock(pBlock block)override;
    virtual void prepareTriggers()override;
};

class CommonExp: public Optimizer{
    map<IRType, map<IRObj, map<IRObj, IRValObj> > > ops; 
public:
    CommonExp(){}
    virtual void applyBlock(pBlock block)override;
    virtual void prepareTriggers()override;
};

class CodeCleaner: public Optimizer{
public:
    CodeCleaner(){}
    virtual void applyBlock(pBlock block)override;
    virtual void prepareTriggers()override;
};
#endif
