#include "Arch.h"

bool BaseArch::matchIR(pSysYIR ir) {
    for (auto matcher : matchers[ir->type]) {
        if (int matchSize = matcher(ir)) {
            auto maskIr = ir->prev;
            while (nullptr != maskIr && (--matchSize) > 0) {
                maskIr->asmRemovedMask = true;
                maskIr = maskIr->prev;
            }
            return true;
        }
    }
    return false;
}

vReg* getVREG(pIRValObj obj) {
    if (!obj) return nullptr;
    vReg* v = valRegs[obj];
    if (v == nullptr) {
        // global vReg with symbol
        if (auto scal = toScal(obj)) {
            if (isImm(obj)) {
                v = new vReg(scal->value);
                goto end;
            } else {  // local
                // reg
                v = new vReg();
            }
        } else {
            auto arr = dynamic_pointer_cast<IRArrValObj>(obj);
            v = new vReg();
            v->regType = REG_M;
            v->size = arr->size;
            v->isAddr = true;
        }
        if (obj->scopeSymbols && obj->scopeSymbols->isGlobal) {
            v->var = obj;
        } else if ((!obj->isParam) && v->regType == REG_M) {
            setVregMem(v, obj->func);
        }
        valRegs[obj] = v;
    }
end:
    return v;
}

// return:immOk T && param ref:immObj not null: op exists imm and imm check
// pass, immOk F && immObj not null: op exists imm and imm check wrong immObj
// null : no imm ops
bool checkDoubleOpImm(pSysYIR ir, vReg*& immScal, vReg*& regObj,
                      bool checkSecOnly, bool (*check)(vReg*)) {
    if (isImm(ir->opt1) && (!checkSecOnly)) {
        immScal = getVREG(toVal(ir->opt1));
        regObj = getVREG(toVal(ir->opt2));
    } else if (isImm(ir->opt2)) {
        immScal = getVREG(toVal(ir->opt2));
        regObj = getVREG(toVal(ir->opt1));
    } else {
        immScal = nullptr;
        regObj = nullptr;
        return false;
    }
    return check(immScal);
}

vReg* processSymbol(vReg* val, pSysYIR ir, ASMInstr* instr) {
    if (val->var != nullptr) {
        vReg* nReg = new vReg();
        ir->addASMFront(loadAddrOp, nReg, {val}, nullptr, instr);
        val = nReg;
    }
    return val;
}

vReg* processLoad(vReg* val, pSysYIR ir, ASMInstr* instr) {
    if (val != nullptr) {
        vReg* nReg = nullptr;
        if (val->regType == REG_IMM) {
            nReg = new vReg();
            ir->addASMFront(loadImmOp, nReg, {val}, nullptr, instr);
        } else if (val->ref || val->var) {
            nReg = new vReg();
            auto loadInstr = ir->addASMFront(val->isAddr ? loadDwOp : loadOp,
                                             nReg, {}, nullptr, instr);
            if (val->var != nullptr) {
                val = processSymbol(val, ir, loadInstr);
            }
            loadInstr->addOp(val);
        }
        if (nReg != nullptr) {
            val = nReg;
        }
    }
    return val;
}

vReg* processStore(vReg* val, pSysYIR ir, ASMInstr* instr) {
    if (val != nullptr) {
        if (val->ref || val->var) {
            vReg* nReg = new vReg();
            auto stInstr = ir->addASMBack(val->isAddr ? storeDwOp : storeOp,
                                          nullptr, {nReg}, nullptr, instr);
            if (val->var != nullptr) {
                val = processSymbol(val, ir, stInstr);
            }
            stInstr->addOp(val);
            val = nReg;
        }
    }
    return val;
}

ASMInstr* addASM(string name, pSysYIR ir, vReg* des, vector<vReg*> ops,
                 pBlock target, bool noStore) {
    vector<vReg*> src{};
    for (auto op : ops) {
        if (op) {
            auto regOp = processLoad(op, ir, nullptr);
            src.push_back(regOp);
        }
    }
    auto mainInstr = new ASMInstr(name, des, {src.begin(), src.end()}, target);
    ir->addASMBack(mainInstr);
    if (des && !noStore) {
        des = processStore(des, ir, mainInstr);
        mainInstr->targetOp = des;
    }
    return mainInstr;
}

int matchCalImmInstr(string name, pSysYIR ir, bool checkSecOnly,
                     bool (*check)(vReg*)) {
    vReg *immObj = nullptr, *regObj = nullptr;
    bool immOk = checkDoubleOpImm(ir, immObj, regObj, checkSecOnly, check);
    if (nullptr != immObj) {
        if (immOk) {
            addASM(name, ir, getVREG(ir->target), {regObj})->addOp(immObj);
            return 1;
        }
    }
    return 0;
}

int matchCalInstr(string name, pSysYIR ir) {
    addASM(name, ir, getVREG(ir->target),
           {getVREG(toVal(ir->opt1)), getVREG(toVal(ir->opt2))});
    return 1;
}
