#pragma once
#include "../frontend/ASTVisitor.h"


class IRProcessor{
public:
    IRProcessor()=default;
    virtual void apply(ASTVisitor& visitor)=0;
    virtual pBlock visit(pBlock root){
        return nullptr;
    };
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

class BlockPruner: public IRProcessor{
    vector<pBlock> deleted;
public:
    BlockPruner()=default;
    bool checkRemoveEmptyBlock(pBlock block);
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