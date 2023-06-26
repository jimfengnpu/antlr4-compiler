#ifndef REG_ALLOC_H
#define REG_ALLOC_H

#include <queue>

#include "Arch.h"
#include "IRProcessor.h"

const int maxBlockASMId = 1024;
const int blockLoopWeight = 10;

static map<vReg*, int> valCost{};
static map<vReg*, unordered_set<vReg*> > conflictMap;
struct ValConflictComparator {
    bool operator()(vReg* a, vReg* b) const {  // > 小顶
        if (a->regId != -1) return true;
        return (conflictMap[a].size()) > (conflictMap[b].size());
    }
};

class RegAllocator : public IRProcessor {
    BaseArch* archInfo;
    map<pBlock, bool> visited;
    map<pBlock, pBlock> visitPath;
    map<pBlock, int> blockFreq;
    set<vReg*> vals{};
    struct ValCostComparator {
        bool operator()(vReg* a, vReg* b) const {  // > 小顶
            if (a->regId != -1) return true;
            return ((double)valCost[a] / conflictMap[a].size()) >
                   ((double)valCost[b] / conflictMap[b].size());
        }
    };
    priority_queue<vReg*, vector<vReg*>, ValCostComparator> checkList;

   public:
    RegAllocator(BaseArch* arch) : archInfo(arch) {}
    void allocReg(pIRFunc func);
    virtual pBlock visit(pBlock);
    void addLoopWeight(pBlock block);
    void makeGraph(pIRFunc func);
    virtual void apply(Prog& prog) {
        for (auto func : prog.functions) {
            if (func->entry != nullptr) {
                allocReg(func);
            }
        }
    }
};
#endif