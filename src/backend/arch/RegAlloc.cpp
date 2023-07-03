#include "RegAlloc.h"

inline void addNewRange(pBlock block, vReg* reg, int end) {
    regLive[reg][block].push_back(new liveRange(block, 0, end));
}

inline void killRange(pBlock block, vReg* reg, int s) {
    if (regLive[reg][block].size()) {
        regLive[reg][block].back()->start = s + 1;
    }
}

inline bool isLive(pBlock block, vReg* reg, int p) {
    for (auto lr : regLive[reg][block]) {
        if (p >= lr->start && p <= lr->end) {
            return true;
        }
    }
    return false;
}

bool intersectConflict(vReg* a, vReg* b, pBlock block) {
    if (!a || !b) return false;
    if (a == b) return false;
    auto& srangeA = regLive[a][block];
    auto& srangeB = regLive[b][block];
    if (srangeA.size() && srangeB.size()) {
        auto i_ra = srangeA.begin();
        auto i_rb = srangeB.begin();
        while (i_ra != srangeA.end() && i_rb != srangeB.end()) {
            int inter_s = max((*i_ra)->start, (*i_rb)->start);
            int inter_e = min((*i_ra)->end, (*i_rb)->end);
            if (inter_s <= inter_e) return true;
            if ((*i_ra)->start < (*i_rb)->start) {
                i_rb++;
            } else {
                i_ra++;
            }
        }
    }
    return false;
}

void RegAllocator::addLoopWeight(pBlock block) {
    do {
        blockFreq[block] *= blockLoopWeight;
        block = visitPath[block];
    } while (block);
}

pBlock RegAllocator::visit(pBlock block) {
    visited[block] = true;
    blockFreq[block] = 1;
    if (block->nextBranch) {
        if (visited[block->nextBranch]) {
            addLoopWeight(block->nextBranch);
        } else {
            visitPath[block] = block->nextBranch;
            visit(block->nextNormal);
        }
    }
    if (block->nextNormal) {
        if (visited[block->nextNormal]) {
            addLoopWeight(block->nextNormal);
        } else {
            visitPath[block] = block->nextNormal;
            visit(block->nextNormal);
        }
    }
    return nullptr;
}

void RegAllocator::makeBlockLiveRange(pBlock block) {
    int sid;
    vector<ASMInstr*> asmVec;
    sid = 0;
    asmVec.clear();
    set<vReg*> liveNow{};
    for (auto ir = block->irHead; ir; ir = ir->next) {
        for (auto s = ir->asmHead; s; s = s->next) {
            sid++;
            asmVec.push_back(s);
        }
    }
    for (auto v : block->liveOut) {
        if (vals.find(v->reg()) != vals.end()) {
            addNewRange(block, v->reg(), sid - 1);
            liveNow.insert(v->reg());
        }
    }
    int callAsmId = -1;
    int i = sid - 1;
    for (auto s = asmVec.rbegin(); i >= 0; i--, s++) {
        if ((*s)->name == callOp) {
            for (auto v : liveNow) {
                killRange(block, v, i);
            }
            for (auto op : (*s)->op) {
                addNewRange(block, op, i);
            }
            continue;
        }
        if ((*s)->op.size() == 0) continue;
        auto opDef = (*s)->op.begin();
        // if storeOp first is use , def is mem type; use will exclude def
        if ((*s)->name == storeOp) {
            opDef++;
        }
        if ((*s)->jTarget != nullptr) {
            opDef = (*s)->op.end();
        }
        if (vals.find(*opDef) != vals.end()) {
            killRange(block, *opDef, i);
            valCost[*opDef] += blockFreq[block];
        }
        for (auto op = (*s)->op.begin(); op != (*s)->op.end(); op++) {
            if (op != opDef) {
                if (vals.find(*op) != vals.end()) {
                    if (!isLive(block, *op, i)) {
                        addNewRange(block, *op, i);
                    }
                    valCost[*op] += blockFreq[block];
                }
            }
        }
    }
}

void RegAllocator::makeGraph(pIRFunc func) {
    vals.clear();
    conflictMap.clear();
    regLive.clear();
    // assembly add id
    for (pBlock block = func->entry; block; block = block->asmNextBlock) {
        for (auto ir = block->irHead; ir; ir = ir->next) {
            for (auto s = ir->asmHead; s; s = s->next) {
                for (auto v : s->op) {
                    if (v->regType == REG_R) vals.insert(v);
                }
            }
        }
    }

    for (pBlock block = func->entry; block; block = block->asmNextBlock) {
        for (auto [v1, v1liv] : regLive) {
            for (auto [v2, v2liv] : regLive) {
                if (v1 != v2) {
                    if (intersectConflict(v1, v2, block)) {
                        conflictMap[v1].insert(v2);
                        conflictMap[v2].insert(v1);
                    }
                }
            }
        }
    }
}

void RegAllocator::allocReg(pIRFunc func) {
    bool conficted;
    map<vReg*, bool> colored;
    map<vReg*, bool> removed;
    map<vReg*, int> regIds;
    deque<vReg*> regOrder;
    int k = archInfo->genRegsId.size();
    do {
        while (!checkList.empty()) {
            checkList.pop();
        }
        colored.clear();
        removed.clear();
        regIds.clear();
        regOrder.clear();
        conficted = false;
        makeGraph(func);
        map<vReg*, unordered_set<vReg*> > bkConflict(conflictMap);
        priority_queue<vReg*, vector<vReg*>, ValConflictComparator> qvals;
        for (auto v : vals) {
            if (v->regId != -1) {
                colored[v] = true;
                regIds[v] = v->regId;
                regOrder.push_front(v);
            } else {
                qvals.push(v);
            }
        }
        while (qvals.size()) {
            auto v = qvals.top();
            if (conflictMap[v].size() < k) {
                for (auto adj : conflictMap[v]) {
                    conflictMap[adj].erase(v);
                }
                conflictMap[v].clear();
            }
            qvals.pop();
            regOrder.push_front(v);
        }
        conflictMap = bkConflict;
        for (auto v : regOrder) {
            if (!colored[v]) {
                set<int> scolor{};
                for (auto adj : conflictMap[v]) {
                    if (colored[adj]) {
                        scolor.insert(regIds[adj]);
                    }
                }
                for (auto c : archInfo->genRegsId) {
                    if (scolor.find(c) == scolor.end()) {
                        colored[v] = true;
                        regIds[v] = c;
                        break;
                    }
                }
            }
            if (!colored[v]) {
                checkList.push(v);
            }
        }
        if (checkList.size()) {
            auto splited = checkList.top();
            splited->regType = REG_M;
            for (auto b : func->blocks) {
                for (auto ir = b->irHead; ir; ir = ir->next) {
                    for (auto s = ir->asmHead; s; s = s->next) {
                        for (int i = 0; i < s->op.size(); i++) {
                            if (s->op[i] == splited) {
                                vReg* mreg = new vReg();
                                if (i) {
                                    ir->addASMFront(
                                        new ASMInstr(loadOp, {mreg, splited}),
                                        s);
                                } else {
                                    ir->addASMFront(
                                        new ASMInstr(storeOp, {mreg, splited}),
                                        s);
                                }
                            }
                        }
                    }
                }
            }
            conficted = true;
        }
    } while (conficted);
    for (auto [r, c] : regIds) {
        r->regId = c;
    }
}