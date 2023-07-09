#ifndef INSTR_MATCHER_H
#define INSTR_MATCHER_H

#include <deque>

#include "Arch.h"
#include "IRProcessor.h"

class InstrMatcher : public IRProcessor {
    BaseArch* archInfo;
    deque<pBlock> blocks{};

   public:
    InstrMatcher(BaseArch* arch) : archInfo(arch) {}
    virtual pBlock visit(pBlock block);
    virtual void apply(Prog& prog) {
        triggers.push_back(new LiveCalculator(true));
        addTriggers();
        for (auto& f : prog.functions) {
            if (f->entry) {
                archInfo->prepareFuncPreRegs(f);
                for (pBlock block : f->blocks) {
                    visit(block);
                }
                pBlock last = nullptr;
                map<pBlock, bool> visited{};
                vector<pBlock> vec{};
                blocks.push_back(f->entry);
                while (blocks.size()) {
                    pBlock block = blocks.front();
                    blocks.pop_front();
                    vec.clear();
                    if (!visited[block]) {
                        visited[block] = true;
                        if (last) {
                            last->asmNextBlock = block;
                        }
                        archInfo->matchBlockEnd(block, vec);
                        for (auto b = vec.rbegin(); b != vec.rend(); b++) {
                            blocks.push_front(*b);
                        }
                        last = block;
                    }
                }
            }
        }
    }
};

#endif