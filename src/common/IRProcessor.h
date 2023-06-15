#pragma once
#include "../frontend/ASTVisitor.h"


class IRProcessors;

class IRProcessor{
public:
    IRProcessors* procs=nullptr;
    deque<IRProcessor*> triggers;
    IRProcessor()=default;
    virtual void apply(ASTVisitor& visitor)=0;
    virtual void addTriggers();
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
            // for(auto pr: processors){
            //     cout << pr << " ";
            // }
            // cout << endl;
            auto proc = processors.front();
            processors.pop_front();
            proc->apply(visitor);
            #ifdef VAL_IR
                cout << "IR:";
                cout << *(visitor.globalData.get());
                for(auto &f : visitor.functions){
                    cout << endl << *f;
                }
                cout << endl;
            #endif
        }
    }
    void add(IRProcessor* proc){
        processors.push_back(proc);
        proc->procs = this;
    }
};


class LiveCalculator: public IRProcessor{
    bool changed;
public:
    LiveCalculator();
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