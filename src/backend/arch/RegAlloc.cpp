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
#ifdef VAL_REG
void displayRegLive(pBlock block, set<vReg*>& vals) {
    int sid = 0;
    int xid = 0;
    vector<vReg*> rx{};
    for (auto v : vals) {
        if (regLive[v][block].size()) {
            rx.push_back(v);
            xid++;
        }
    }
    for (auto ir = block->irHead; ir; ir = ir->next) {
        for (auto s = ir->asmHead; s; s = s->next) {
            for (int i = 0; i < xid; i++) {
                if (isLive(block, rx[i], sid)) {
                    cout << "|";
                } else {
                    cout << " ";
                }
            }
            cout << sid << ": " << s->name;
            if (s->targetOp) cout << " " << s->targetOp->regId;
            if (s->name != callOp) {
                for (auto op : s->op) {
                    cout << " " << (op->regType == REG_IMM) ? op->value
                                                            : op->regId;
                }
            }
            cout << endl;
            sid++;
        }
    }
}
#endif
bool intersectConflict(vReg* a, vReg* b, pBlock block, int* s, int* e) {
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
            if (inter_s <= inter_e) {
                *s = inter_s;
                *e = inter_e;
                return true;
            }
            if ((*i_ra)->start < (*i_rb)->start) {
                i_rb++;
            } else {
                i_ra++;
            }
        }
    }
    return false;
}

// choose a possible live range to color a different reg
bool splitVal(vReg* a, vReg* b) {
    int s, e;
    if (a == b) return false;
    assert(!(a->fixed && b->fixed));
    vReg* val = a->fixed ? b : a;
    vReg* nReg = new vReg();
    for (auto [blk, ra] : regLive[a]) {
        auto rb = regLive[b][blk];
        if (rb.size() && ra.size()) {
#ifdef VAL_REG
            cout << blk->name << endl;
            for (auto r : regLive[a][blk]) {
                cout << "[" << r->start << "," << r->end << "] ";
            }
            cout << endl;
            for (auto r : regLive[b][blk]) {
                cout << "[" << r->start << "," << r->end << "] ";
            }
            cout << endl;
#endif
            if (intersectConflict(a, b, blk, &s, &e)) {
                int i = 0;
                for (auto ir = blk->irHead; ir; ir = ir->next) {
                    for (auto inst = ir->asmHead; inst;
                         inst = inst->next, i++) {
                        if (i >= s && i <= e) {
                            for (int j = 0; j < inst->op.size(); j++) {
                                if (inst->op[j] == val) {
                                    inst->op[j] = nReg;
                                }
                            }
                            if (inst->targetOp && inst->targetOp == val) {
                                inst->targetOp = nReg;
                            }
                        }
                        if (i == s - 1 || s==0 && i == 0) {
                            auto newInst = ir->addASMFront(
                                assignOp, nReg, {val}, nullptr, inst);
                            // inst->prev->next = newInst;
                            // newInst->prev = inst;
                        } else if (i == e) {
                            auto newInst = ir->addASMBack(assignOp, val, {nReg},
                                                          nullptr, inst);
                            // inst->next->prev = newInst;
                            // newInst->next = inst;
                            inst = newInst;
                        }
                        if (i > e) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    // assert(0);
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
    for (auto v : block->liveOutRegs) {
        if (vals.find(v) != vals.end()) {
            addNewRange(block, v, sid - 1);
            liveNow.insert(v);
        }
    }
    int i = sid - 1;
    for (auto s = asmVec.rbegin(); i >= 0; i--, s++) {
        if ((*s)->name == callOp) {
            for (auto op : (*s)->op) {
                if (vals.find(op) != vals.end()) {
                    if (!isLive(block, op, i)) {
                        addNewRange(block, op, i);
                        liveNow.insert(op);
                    }
                    killRange(block, op, i - 1);
                    liveNow.erase(op);
                    if (liveNow.size()) {
                        for (auto& v : liveNow) {
                            conflictMap[v].insert(op);
                            conflictMap[op].insert(v);
                        }
                    }
                }
            }
            continue;
        }
        if ((*s)->op.size() == 0) continue;
        if ((*s)->targetOp != nullptr) {
            auto opDef = (*s)->targetOp;
            if (vals.find(opDef) != vals.end()) {
                killRange(block, opDef, i);
                liveNow.erase(opDef);
                if (liveNow.size()) {
                    for (auto& v : liveNow) {
                        conflictMap[v].insert(opDef);
                        conflictMap[opDef].insert(v);
                    }
                }
                valCost[opDef] += blockFreq[block];
            }
        }
        for (auto op = (*s)->op.begin(); op != (*s)->op.end(); op++) {
            if (vals.find(*op) != vals.end()) {
                if (!isLive(block, *op, i)) {
                    addNewRange(block, *op, i);
                    liveNow.insert(*op);
                }
                valCost[*op] += blockFreq[block];
            }
        }
    }
}

void RegAllocator::getVregClass(vReg* v) {
    if (v->regType == REG_R && v->var == nullptr) {
        vals.insert(v);
    }
    // } else if (v->regType == REG_M) {
    //     if (v->ref == nullptr) {
    //         if (v->var == nullptr) {
    //             memVals.insert(v);
    //         }
    //     } else {
    //         getVregClass(v->ref);
    //     }
    // }
}

void RegAllocator::makeGraph(pIRFunc func) {
    vals.clear();
    conflictMap.clear();
    for (auto [v, mp] : regLive) {
        for (auto [b, r] : mp) {
            r.clear();
        }
    }
    regLive.clear();
// assembly add id
#ifdef VAL_REG
    cout << "make " << func->name << endl;
#endif
    for (pBlock block = func->entry; block; block = block->asmNextBlock) {
        for (auto ir = block->irHead; ir; ir = ir->next) {
            for (auto s = ir->asmHead; s; s = s->next) {
                for (auto v : s->op) {
                    getVregClass(v);
                }
                if (auto v = s->targetOp) {
                    getVregClass(v);
                }
            }
        }
    }
    for (pBlock block = func->entry; block; block = block->asmNextBlock) {
        makeBlockLiveRange(block);
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
#ifdef VAL_REG
        for (auto block = func->entry; block; block = block->asmNextBlock) {
            cout << block->name << endl;
            displayRegLive(block, vals);
        }
#endif
        unordered_map<vReg*, unordered_set<vReg*> > bkConflict(conflictMap);
        priority_queue<vReg*, vector<vReg*>, ValConflictComparator> qvals;
        for (auto v : vals) {
            assert(v->regType == REG_R);
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
            set<int> scolor{};
            if (!colored[v]) {
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
            } else {
                for (auto adj : conflictMap[v]) {
                    if (colored[adj] && regIds[adj] == regIds[v]) {
                        if (splitVal(v, adj)) {
                            conficted = true;
                            goto loop;
                        }
                    }
                }
            }
            if (!colored[v]) {
                checkList.push(v);
            }
        }
        if (checkList.size()) {
            auto spilled = checkList.top();
            spilled->regType = REG_M;
            curFunc->stackCapacity.value += memByteAlign;
            spilled->size = 1;
            setVregMem(spilled, func);
            for (auto b : func->blocks) {
                for (auto ir = b->irHead; ir; ir = ir->next) {
                    for (auto s = ir->asmHead; s; s = s->next) {
                        vReg* mreg = nullptr;
                        for (int i = 0; i < s->op.size(); i++) {
                            if (s->op[i] == spilled) {
                                mreg = new vReg(spilled);
                                ir->addASMFront(
                                    new ASMInstr(loadOp, mreg, {spilled}), s);
                                s->op[i] = mreg;
                            }
                        }
                        if (s->targetOp && s->targetOp == spilled) {
                            mreg = new vReg(spilled);
                            ir->addASMFront(
                                new ASMInstr(storeOp, nullptr, {mreg, spilled}),
                                s);
                            s->targetOp = mreg;
                        }
                    }
                }
            }
            conficted = true;
        }
    loop:;
    } while (conficted);
    for (auto [r, c] : regIds) {
        r->regId = c;
    }
}