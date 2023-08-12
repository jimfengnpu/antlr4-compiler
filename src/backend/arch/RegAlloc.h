#ifndef REG_ALLOC_H
#define REG_ALLOC_H

#include <queue>

#include "Arch.h"
#include "AsmModify.h"
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
static unordered_map<vReg*, int> valAccCnt{};
static unordered_map<vReg*, map<pBlock, vector<liveRange*> > > regLive;
static unordered_map<vReg*, unordered_set<vReg*> > conflictMap;
struct ValConflictComparator {
    bool operator()(vReg* a, vReg* b) const {  // > 小顶
        if (a->regId != b->regId) return a->regId != -1;
        return (conflictMap[a].size()) > (conflictMap[b].size());
    }
};

static int liveLen(vReg* v) {
    int s = 0;
    for (auto [b, vec] : regLive[v]) {
        for (auto r : vec) {
            s += (r->end - r->start + 1);
        }
    }
    return s;
}

static double calCost(vReg* v) {
    if (liveLen(v) == 0 || valCost[v] == 0) {
        return 1 / 0.0;  // this means v is used in call, never spilled
    }
    const double eps = 1e-8;
    double cost = (double)valCost[v];
    double range_fac = liveLen(v) + 1 - valAccCnt[v] + eps;
    cost /= range_fac * conflictMap[v].size();
    return cost;
}

class RegAllocator : public IRProcessor {
    BaseArch* archInfo;
    map<pBlock, bool> visited;
    map<pBlock, pBlock> visitPath;
    map<pBlock, int> blockFreq;
    set<vReg*> vals{};
    // unordered_set<vReg*> memVals{};
    struct ValCostComparator {
        bool operator()(vReg* a, vReg* b) const {  // > 小顶
            if (a->regId != -1) return true;
            // if (liveLen(b) == 0) return false;
            return calCost(a) > calCost(b);
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
        triggers.push_back(new AsmModifier(archInfo));
        addTriggers();
        for (auto func : prog.functions) {
            if (func->entry != nullptr) {
                visit(func->entry);
                allocReg(func);
                unordered_set<int> regUsed{};
                for (auto v : vals) {
                    assert(v->regId != -1);
                    regUsed.insert(v->regId);
                }
                archInfo->prepareFuncInitExitAsm(func, regUsed);
            }
        }
    }
};
#endif