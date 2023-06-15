#pragma once
#include "../common/IRProcessor.h"

// base class for optimize processor
class Optimizer: public IRProcessor{
public:
    deque<pBlock> workList;
    map<pBlock, bool> visited;
    bool changed;
    Optimizer(){}
    virtual void applyBlock(pBlock block)=0;
    virtual void applyNextBlock(pBlock block){
        if(block->nextNormal && (!visited[block->nextNormal]))
            workList.push_back(block->nextNormal);
        if(block->nextBranch && (!visited[block->nextBranch]))
            workList.push_back(block->nextBranch);
    }
    virtual void applyFunc(pIRFunc func){}
    virtual void prepareTriggers(){}
    virtual void apply(ASTVisitor& visitor){
        bool triggerNeeded = false;
        for(auto& func: visitor.functions){
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
    virtual void applyBlock(pBlock block){}
    virtual void applyFunc(pIRFunc func);
    virtual void prepareTriggers();
};

class ConstBroadcast: public Optimizer{
public:
    ConstBroadcast(){}
    void setConstState(pBlock block, pIRObj obj);
    virtual void applyBlock(pBlock block);
    virtual void prepareTriggers();
};

class CodeCleaner: public Optimizer{
public:
    CodeCleaner(){}
    virtual void applyBlock(pBlock block);
    virtual void prepareTriggers();
};