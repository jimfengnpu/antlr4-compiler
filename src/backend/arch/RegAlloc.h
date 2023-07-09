#ifndef REG_ALLOC_H
#define REG_ALLOC_H

#include <queue>

#include "Arch.h"
#include "IRProcessor.h"

const int maxBlockASMId = 1024;
const int blockLoopWeight = 10;

class liveRange {
   public:
    pBlock block;
    int start;
    int end;
    vReg* cusReg = nullptr;
    liveRange(pBlock b, int s, int e) : block(b), start(s), end(e) {}
};

static pIRFunc curFunc;
static unordered_map<vReg*, int> valCost{};
static unordered_map<vReg*, map<pBlock, vector<liveRange*> > > regLive;
static unordered_map<vReg*, unordered_set<vReg*> > conflictMap;
struct ValConflictComparator {
    bool operator()(vReg* a, vReg* b) const {  // > 小顶
        if (a->regId != b->regId) return a->regId != -1;
        return (conflictMap[a].size()) > (conflictMap[b].size());
    }
};

class RegAllocator : public IRProcessor {
    BaseArch* archInfo;
    map<pBlock, bool> visited;
    map<pBlock, pBlock> visitPath;
    map<pBlock, int> blockFreq;
    set<vReg*> vals{};
    unordered_set<vReg*> memVals{};
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
    void getVregClass(vReg* r);
    virtual pBlock visit(pBlock);
    void addLoopWeight(pBlock block);
    void makeBlockLiveRange(pBlock block);
    void makeGraph(pIRFunc func);
    virtual void apply(Prog& prog) {
        for (auto func : prog.functions) {
            if (func->entry != nullptr) {
                allocReg(func);
                unordered_set<int> regUsed{};
                for (auto v : vals) {
                    assert(v->regId != -1);
                    regUsed.insert(v->regId);
                }
                archInfo->prepareFuncInitExitAsm(func, regUsed, memVals);
            }
        }
    }
};
#endif