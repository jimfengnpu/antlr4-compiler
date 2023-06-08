#pragma once
#include "../frontend/ASTVisitor.h"


class IRProcessors;
class IRProcessor{
public:
    IRProcessor()=default;
    virtual void apply(ASTVisitor& visitor)=0;
    virtual void processDependency(IRProcessors* procs){};
    virtual pBlock visit(pBlock root){
        return nullptr;
    };
};

class IRProcessors{
public:
    deque<IRProcessor*> processors;
    ASTVisitor& visitor;
    IRProcessors(ASTVisitor& visitor): visitor(visitor){}
    void apply(){
        while(processors.size()){
            auto proc = processors.front();
            processors.pop_front();
            cout << typeid(decltype(proc)).name()<< endl;
            proc->apply(visitor);
            delete proc;
        }
    }
    void add(IRProcessor* proc){
        processors.push_back(proc);
        proc->processDependency(this);
    }
};

class BlockPruner: public IRProcessor{
    vector<pBlock> deleted;
public:
    BlockPruner()=default;
    bool checkRemoveEmptyBlock(pBlock block);
    virtual void processDependency(IRProcessors* procs);
    virtual void apply(ASTVisitor& visitor){
        for(auto& f: visitor.functions){
            deleted.clear();
            for(auto block: f->blocks){
                if(block != f->entry && block != f->exit){
                    if(checkRemoveEmptyBlock(block))
                        deleted.push_back(block);
                }
            }
            for(auto p: deleted){
                f->blocks.erase(p);
            }
        }
    }
};

class LiveCalculator: public IRProcessor{
    bool changed;
public:
    LiveCalculator(){}
    void makeLive(pIRFunc& func);
    void mergeSuccLivein(pBlock block, pBlock from);
    virtual pBlock visit(pBlock block);
    virtual void apply(ASTVisitor& visitor){
        for(auto& f: visitor.functions){
            if(f->entry){
                makeLive(f);
            }
        }
    }
};