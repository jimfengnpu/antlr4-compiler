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
                        auto p = workList.front();
                        workList.pop_front();
                        if(visited[p])continue;
                        visited[p] = true;
                        applyBlock(p);
                        applyNextBlock(p);
                    }
                    applyFunc(func);
                    triggerNeeded |= changed;
                }while(changed);
            }
        }
        if(triggerNeeded) addTriggers();
    }
};

class BlockPruner: public Optimizer{
    vector<pBlock> deleted;
public:
    BlockPruner();
    bool checkRemoveEmptyBlock(pBlock block);
    virtual void applyBlock(pBlock block);
    virtual void applyFunc(pIRFunc func){
        for(auto p: func->blocks){
            if(!visited[p])deleted.push_back(p);
        }
        if(deleted.size() > 0)changed = true;
        for(auto p: deleted){
            func->blocks.erase(p);
        }
        deleted.clear();
    }
};

class ConstBroadcast: public Optimizer{
    map<pBlock, map<pIRScalValObj, int> > constState;
public:
    ConstBroadcast();
    void setConstState(pBlock block, pIRObj obj);
    virtual void applyBlock(pBlock block);
};

class CodeCleaner: public Optimizer{
public:
    CodeCleaner();
    void checkObjUse(pIRObj obj);
    virtual void applyBlock(pBlock block);
};