#ifndef IRPROCESSOR_H
#define IRPROCESSOR_H
#include "ASTVisitor.h"

class IRProcessors;

class IRProcessor {
   public:
    IRProcessors* procs = nullptr;
    deque<IRProcessor*> triggers;
    IRProcessor() = default;
    virtual void apply(Prog& prog) = 0;
    virtual void addTriggers();
    virtual pBlock visit(pBlock root) { return nullptr; };
};

class IRProcessors {
   public:
    deque<IRProcessor*> processors;
    Prog& prog;
    IRProcessors(Prog& prog) : prog(prog) {}
    void apply() {
        while (!processors.empty()) {
            auto proc = processors.front();
            processors.pop_front();
            proc->apply(prog);
            delete proc;
#ifdef VAL_IR
            cout << "IR:";
            cout << (prog.globalData.get());
            for (auto& f : prog.functions) {
                cout << endl << *f;
            }
            cout << endl;
#endif
        }
    }
    void add(IRProcessor* proc) {
        processors.push_back(proc);
        proc->procs = this;
    }
};

class LiveCalculator : public IRProcessor {
    bool changed;
    bool isRegLv;
   public:
    LiveCalculator(bool reg=false): isRegLv(reg){};
    void makeLive(pIRFunc& func);
    void mergeSuccLivein(pBlock block, pBlock from);
    virtual pBlock visit(pBlock block) override;
    virtual void apply(Prog& prog) override {
        for (auto& f : prog.functions) {
            if (f->entry) {
                makeLive(f);
            }
        }
    }
};
#endif
