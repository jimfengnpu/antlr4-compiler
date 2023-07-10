#include "Arch.h"

static unordered_map<pIRValObj, vReg*> valRegs;

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

inline bool isImm(pIRScalValObj scal) {
    if (!scal) return false;
    if (!scal->isConstant() ||
        (scal->scopeSymbols && scal->scopeSymbols->isGlobal))
        return false;
    return true;
}

inline bool isInLimit(int val, int width) {
    int lim = 1 << width;
    int v = val + lim / 2;
    return v >= 0 && v < lim;
}

inline int getAligned(int x, int align) {
    return ((x + align - 1) / align) * align;
}

inline bool isImm(pIRObj obj) { return isImm(toScal(obj)); }

inline bool isImm(vReg* val) { return val->regType == REG_IMM; }

inline bool isImmInLimit(vReg* val, int width) {
    if (isImm(val)) {
        return isInLimit(val->getValue(), width);
    }
    return false;
}

inline void setVregMem(vReg* val, pIRFunc func) {
    func->stackCapacity.value += memByteAlign * val->size;
    val->ref = &func->stackCapacity;
    val->value = -func->stackCapacity.value;
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
        }
        if (obj->scopeSymbols && obj->scopeSymbols->isGlobal) {
            v->var = obj;
        } else if ((!obj->isParam) && v->regType == REG_M) {
            setVregMem(v, obj->func);
        }
    end:
        valRegs[obj] = v;
    }
    return v;
}
// return:immOk T && param ref:immObj not null: op exists imm and imm check
// pass, immOk F && immObj not null: op exists imm and imm check wrong immObj
// null : no imm ops
bool checkDoubleOpImm(
    pSysYIR ir, vReg*& immScal, vReg*& regObj, bool checkSecOnly = false,
    bool (*check)(vReg*) = [](vReg* r) -> bool { return true; }) {
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

vReg* processSymbol(vReg* val, pSysYIR ir, ASMInstr* instr = nullptr) {
    if (val->var != nullptr) {
        vReg* nReg = new vReg();
        ir->addASMFront(loadAddrOp, nReg, {val}, nullptr, instr);
        val = nReg;
    }
    return val;
}

vReg* processLoad(vReg* val, pSysYIR ir, ASMInstr* instr = nullptr) {
    if (val != nullptr) {
        vReg* nReg = nullptr;
        if (val->regType == REG_IMM) {
            nReg = new vReg();
            ir->addASMFront(loadImmOp, nReg, {val}, nullptr, instr);
        } else if (val->ref || val->var) {
            nReg = new vReg();
            auto loadInstr = ir->addASMFront(loadOp, nReg, {}, nullptr, instr);
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

vReg* processStore(vReg* val, pSysYIR ir, ASMInstr* instr = nullptr) {
    if (val != nullptr) {
        if (val->ref || val->var) {
            vReg* nReg = new vReg();
            auto stInstr =
                ir->addASMBack(storeOp, nullptr, {nReg}, nullptr, instr);
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
                 pBlock target = nullptr, bool noStore = false) {
    vector<vReg*> src{};
    for (auto op : ops) {
        if (op) {
            auto regOp = processLoad(op, ir);
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

int matchCalImmInstr(
    string name, pSysYIR ir, bool checkSecOnly = false,
    bool (*check)(vReg*) = [](vReg* r) -> bool {
        if (isImmInLimit(r, 12)) {
            return true;
        }
        r->regType = REG_R;
        return false;
    }) {
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

void RISCV::matchBlockEnd(pBlock block, vector<pBlock>& nextBlocks) {
    pBlock brTarget = block->nextBranch;
    pBlock nxTarget = block->nextNormal;
    pSysYIR lastIr = block->branchIR;
    vector<pBlock> ret{};
    map<IRType, string> irBrAsm = {{IRType::NOT, "beqz"}, {IRType::EQ, "beq"},
                                   {IRType::NEQ, "bne"},  {IRType::GT, "bgt"},
                                   {IRType::LT, "blt"},   {IRType::GE, "bge"},
                                   {IRType::LE, "ble"}};
    map<string, string>
        oppoBranch =  // op a, b =>T else F ===> oppo[op] b, a =>T else F
        {{"bgt", "blt"}, {"blt", "bgt"}, {"bge", "ble"}, {"ble", "bge"}};
    map<string, string>
        fllipBranch =  // op a, b =>T else F ===> fllip[op] a, b =>F else T
        {
            {"bgt", "ble"},   {"blt", "bge"},   {"bge", "blt"},
            {"ble", "bgt"},   {"beq", "bne"},   {"bgtz", "blez"},
            {"bltz", "bgez"}, {"bgez", "bltz"}, {"blez", "bgtz"},
            {"beqz", "bnez"},
        };
    int mask = 0;
    int cnt = 0;
    if (nullptr != brTarget) {
        pSysYIR ir = block->branchIR;
        lastIr = ir;
        pSysYIR brValDef = toVal(ir->opt1)->defStruction;
        assert(toVal(ir->opt1)->defStruction == brValDef);
        string name = "";
        if (brValDef) {
            name = irBrAsm[brValDef->type];
        }
        mask = 2;
        vReg *imm = nullptr, *reg = nullptr;
        vector<vReg*> oprands{};
        if (name.empty()) {
            name = "bnez";
            mask = 1;
            oprands.push_back(getVREG(toVal(ir->opt1)));
        } else {
            if (checkDoubleOpImm(brValDef, imm, reg) && imm->getValue() == 0) {
                if (brValDef->type == IRType::EQ ||
                    brValDef->type == IRType::NEQ) {
                    name = name + "z";
                    oprands.push_back(reg);
                } else {
                    if (imm == getVREG(toVal(brValDef->opt1))) {
                        name = oppoBranch[name] + "z";
                    }
                    oprands.push_back(reg);
                    oprands.push_back(imm);
                }
            } else {
                oprands.push_back(getVREG(toVal(brValDef->opt1)));
                oprands.push_back(getVREG(toVal(brValDef->opt2)));
            }
        }
        for (pBlock b = brTarget; b && (b->asmNextBlock || b == block);
             b = b->asmNextBlock) {
            cnt += b->asmLen();
        }
        if (cnt > branchBlockASMLimit) {
            pBlock t = brTarget;
            brTarget = nxTarget;
            nxTarget = t;
            name = fllipBranch[name];
        }
        addASM(name, lastIr, nullptr, {oprands.begin(), oprands.end()},
               brTarget);
    }
    if (nxTarget) {
        addASM("j", lastIr, nullptr, {}, nxTarget);
    }
    if (mask > 0) {
        for (auto maskIr = lastIr->prev; maskIr && ((--mask) > 0);
             maskIr = maskIr->prev) {
            maskIr->asmRemovedMask = true;
        }
    }
    if (brTarget && cnt == 0) {
        nextBlocks.push_back(brTarget);
    }
    if (nxTarget) {
        nextBlocks.push_back(nxTarget);
    }
}

void RISCV::defineArchInfo() {
    stackPointerRegId = REG::sp;
    framePointerRegId = REG::s0;
    frameByteAlign = 16;
    branchBlockASMLimit = 512;
    addRegs(genRegsId, {a0, a1, a2, a3, a4, a5,  a6,  a7, s1, s2, s3, s4,
                        s5, s6, s7, s8, s9, s10, s11, t0, t1, t2, t3, ra});
    addRegs(calleeSaveRegs, {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11});
    addMatchers(IRType::ASSIGN,
                {[](pSysYIR ir) -> int { return matchCalInstr("mv", ir); }});
    addMatchers(IRType::ADD, {[](pSysYIR ir) -> int {
                    int imm = matchCalImmInstr("addi", ir);
                    if (imm) return imm;
                    return matchCalInstr("add", ir);
                }});
    addMatchers(IRType::SUB, {[](pSysYIR ir) -> int {
                    int imm = matchCalImmInstr("addi", ir, true,
                                               [](vReg* imm) -> bool {
                                                   if (isImmInLimit(imm, 12)) {
                                                       imm->value = -imm->value;
                                                       return true;
                                                   }
                                                   imm->regType = REG_R;
                                                   return false;
                                               });
                    if (imm) return imm;
                    return matchCalInstr("sub", ir);
                }});
    addMatchers(IRType::MUL,
                {[](pSysYIR ir) -> int { return matchCalInstr("mul", ir); }});
    addMatchers(IRType::DIV,
                {[](pSysYIR ir) -> int { return matchCalInstr("div", ir); }});
    addMatchers(IRType::MOD,
                {[](pSysYIR ir) -> int { return matchCalInstr("rem", ir); }});
    addMatchers(IRType::AND, {[](pSysYIR ir) -> int {
                    int imm = matchCalImmInstr("andi", ir);
                    if (imm) return imm;
                    return matchCalInstr("and", ir);
                }});
    addMatchers(IRType::OR, {[](pSysYIR ir) -> int {
                    int imm = matchCalImmInstr("ori", ir);
                    if (imm) return imm;
                    return matchCalInstr("or", ir);
                }});
    addMatchers(IRType::SL, {[](pSysYIR ir) -> int {
                    int imm = matchCalImmInstr("slli", ir, true);
                    if (imm) return imm;
                    return matchCalInstr("sll", ir);
                }});
    addMatchers(IRType::SR, {[](pSysYIR ir) -> int {
                    int imm = matchCalImmInstr("srai", ir, true);
                    if (imm) return imm;
                    return matchCalInstr("sra", ir);
                }});
    addMatchers(IRType::NEG,
                {[](pSysYIR ir) -> int { return matchCalInstr("neg", ir); }});
    addMatchers(
        IRType::IDX,
        {// opt1: arr, opt2: scal, offset
         [](pSysYIR ir) -> int {
             vReg *offObj = nullptr, *arrObj = nullptr;
             vReg* obj = getVREG(ir->target);
             if (checkDoubleOpImm(ir, offObj, arrObj, true,
                                  [](vReg* imm) -> bool { return true; }) &&
                 (arrObj->regType == REG_M && arrObj->var == nullptr &&
                  !(toVal(ir->opt1)->isParam))) {
                 obj->value = offObj->value;
                 obj->regType = REG_M;
             } else {
                 arrObj = getVREG(toVal(ir->opt1));
                 arrObj = processSymbol(arrObj, ir);
                 offObj = getVREG(toVal(ir->opt2));
                 if (isImmInLimit(offObj, 12)) {
                     offObj = new vReg(offObj->value);
                     offObj->ref = arrObj;
                     ir->addASMBack("addi", obj, {arrObj, offObj});
                 } else {
                     offObj = processLoad(offObj, ir);
                     vReg* r = new vReg(0);
                     r->ref = arrObj;
                     ir->addASMBack("addi", offObj, {offObj, r});
                     ir->addASMBack("add", obj, {arrObj, offObj});
                 }
             }
             obj->ref = arrObj;
             //  obj->var = toVal(ir->target);
             return 1;
         }});
    addMatchers(IRType::ARR, {[](pSysYIR ir) -> int {
                    vReg* obj = getVREG(ir->target);
                    vReg* arrObj = getVREG(toVal(ir->opt1));
                    arrObj = processSymbol(arrObj, ir);
                    vReg* offObj = getVREG(toVal(ir->opt2));
                    if (isImmInLimit(offObj, 12)) {
                        // 此处offset 应为参数offset + arr 相对arr寄存器的offset
                        offObj = new vReg(offObj->value);
                        offObj->ref = arrObj;
                        ir->addASMBack("addi", obj, {arrObj, offObj});
                    } else {
                        offObj = processLoad(offObj, ir);
                        vReg* r = new vReg(0);
                        r->ref = arrObj;
                        ir->addASMBack("addi", offObj, {offObj, r});
                        ir->addASMBack("add", obj, {arrObj, offObj});
                    }
                    obj->regType = REG_R;
                    return 1;
                }});
    addMatchers(IRType::RET, {[](pSysYIR ir) -> int {
                    vReg* retVal = nullptr;
                    if (ir->block->function->returnType != IR_VOID)
                        retVal = getVREG(toVal(ir->opt1));
                    // if (retVal && isImm(retVal)) {
                    //     vReg* r = newReg(a0);
                    //     addASM("li", ir, r, {retVal});
                    //     retVal = r;
                    // }
                    addASM("ret", ir, nullptr, {retVal});
                    return 1;
                }});
    addMatchers(IRType::CALL, {[](pSysYIR ir) -> int {
                    int paramCnt = 0;
                    pSysYIR paramIr = ir->prev;
                    vector<vReg*> paramRegs{};
                    vReg* retVal = nullptr;
                    while (paramIr && paramIr->type == IRType::PARAM) {
                        vReg* paramReg = new vReg();
                        if (paramCnt < 8) {
                            paramReg->regType = REG_R;
                            paramReg->regId = a0 + paramCnt;
                            paramReg->fixed = true;
                            paramRegs.push_back(paramReg);
                            if (paramCnt == 0) {
                                retVal = paramReg;
                            }
                        } else {
                            paramReg->regType = REG_M;
                            paramReg->regId = RISCV::sp;
                            paramReg->value = 4 * (paramCnt - 8);
                        }
                        addASM("mv", paramIr, paramReg,
                               {getVREG(toVal(paramIr->opt1))});
                        paramIr = paramIr->prev;
                        paramCnt++;
                    }
                    ir->block->function->callerMaxStackSize = max(
                        ir->block->function->callerMaxStackSize, paramCnt - 8);
                    while (paramCnt < 8) {
                        vReg* paramReg = newReg(a0 + paramCnt);
                        paramRegs.push_back(paramReg);
                        if (paramCnt == 0) {
                            retVal = paramReg;
                        }
                        paramCnt++;
                    }
                    vector<int> callerTmpRegs{t0, t1, t2, t3, t4, t5, t6};
                    for (auto r : callerTmpRegs) {
                        vReg* paramReg = newReg(r);
                        paramRegs.push_back(paramReg);
                    }
                    pIRFunc func = toFunc(ir->opt1);
                    ir->addASMBack(callOp, nullptr,
                                   {paramRegs.begin(), paramRegs.end()}, func);
                    if (func->returnType != IR_VOID) {
                        addASM("mv", ir, getVREG(ir->target), {retVal});
                    }
                    return 1;
                }});
}

void RISCV::prepareFuncPreRegs(pIRFunc f) {
    vReg* v = nullptr;
    for (int i = 0; i < f->params.size(); i++) {
        v = new vReg();
        if (i < paramRegCnt) {
            v->regId = a0 + i;
        } else {
            v->regType = REG_M;
            v->value = memByteAlign * (i - paramRegCnt);
            v->regId = fp;
        }
        valRegs[f->params[i]] = v;
    }
    if (f->returnType != IR_VOID) {
        v = newReg(a0);
        valRegs[f->returnVal] = v;
    }
}

// call after reg alloc
void RISCV::prepareFuncInitExitAsm(pIRFunc func, unordered_set<int>& useRegs,
                                   unordered_set<vReg*>& useStk) {
    auto& initInstrs = func->initInstrs;
    auto& exitInstrs = func->exitInstrs;
    vector<int> stackRegs{};
    vector<vReg*> stackMem{};
    // if (func->stackCapacity.value) {
    // }
    for (auto r : calleeSaveRegs) {
        if (useRegs.find(r) != useRegs.end()) {
            stackRegs.push_back(r);
        }
    }
    stackRegs.push_back(s0);
    if (func->callList.size() > 0) {
        stackRegs.push_back(ra);
    }
    func->stackCapacity.regId = s0;
    // vReg regStackSize = new vReg();  // func->stackCapacity.value;
    int regStackSize = 0;
    // // max limit , avoid extra li in init & exit
    // bool stackOver = false;
    // if(func->stackCapacity.value > regStackLimit){
    //     regStackSize = regStackLimit;
    //     stackOver = true;
    // }
    for (auto r : stackRegs) {
        vReg* mReg = new vReg();
        mReg->regType = REG_M;
        mReg->size = 2;
        mReg->value = regStackSize;
        mReg->regId = sp;
        regStackSize += 8;
        initInstrs->addASMFront("sd", nullptr, {newReg(r), mReg});
        exitInstrs->addASMBack("ld", newReg(r), {mReg});
    }
    func->stackCapacity.value += func->callerMaxStackSize * memByteAlign;
    func->stackCapacity.value += regStackSize;
    // order: fifo (sp->s0, mem)
    func->stackCapacity.value =
        getAligned(func->stackCapacity.value, frameByteAlign);
    if (func->stackCapacity.value) {
        // todo check
        initInstrs->addASMFront("addi", newReg(sp),
                                {newReg(sp), new vReg(-regStackSize)});
        initInstrs->addASMBack("addi", newReg(s0),
                               {newReg(sp), new vReg(regStackSize)});
        int left_sp = func->stackCapacity.value - regStackSize;
        if (left_sp) {
            if (isInLimit(-left_sp, 12)) {
                initInstrs->addASMBack("addi", newReg(sp),
                                       {newReg(sp), new vReg(-left_sp)});
            } else {
                initInstrs->addASMBack("li", newReg(t0), {new vReg(-left_sp)});
                initInstrs->addASMBack("add", newReg(sp),
                                       {newReg(sp), newReg(t0)});
            }
            if (isInLimit(left_sp, 12)) {
                exitInstrs->addASMFront("addi", newReg(sp),
                                        {newReg(sp), new vReg(left_sp)});
            } else {
                exitInstrs->addASMFront("add", newReg(sp),
                                        {newReg(sp), newReg(t0)});
                exitInstrs->addASMFront("li", newReg(t0), {new vReg(left_sp)});
            }
        }
        exitInstrs->addASMBack("addi", newReg(sp),
                               {newReg(sp), new vReg(regStackSize)});
    }
    func->stackCapacity.value = -regStackSize;
}