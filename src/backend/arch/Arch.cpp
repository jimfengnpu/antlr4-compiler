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
    if (!scal->isConstant()) return false;
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
    func->stackCapacitySize += memByteAlign * val->size;
    val->ref = &func->stackCapacity;
    val->value = -func->stackCapacitySize;
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

vReg* processStore(vReg* val, pSysYIR ir, ASMInstr* instr = nullptr) {
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
                 pBlock target = nullptr, bool noStore = false) {
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
        // 这里处理了分支长度的问题,但是后来才知道是想多了,汇编器会帮你做的,,,
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
    // 这是一个vector, 同时定义了寄存器分配顺序
    addRegs(genRegsId, {a0, a1, a2, a3, a4, a5, a6, a7, t1, t2,  t3,
                        s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11});
    addRegs(calleeSaveRegs, {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11});
    addRegs(callerSaveRegs,
            {a0, a1, a2, a3, a4, a5, a6, a7, t0, t1, t2, t3, t4, t5, t6});
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
        {[](pSysYIR ir) -> int {  // opt1: arr, opt2: scal, offset
            vReg *offObj = nullptr, *arrObj = nullptr;
            vReg* obj = getVREG(ir->target);
            if (checkDoubleOpImm(ir, offObj, arrObj, true,
                                 [](vReg* imm) -> bool { return true; }) &&
                (arrObj->regType == REG_M && arrObj->var == nullptr &&
                 !(toVal(ir->opt1)->isParam))) {
                // arr 不来自参数,也不是全局变量，即为当前栈帧内分配的数组
                // 此时将引用的标量转为mem类型并通过value指定offset
                // getVREG调用时仍认为是寄存器标量,保证没有分配实际栈空间
                obj->value = offObj->value;
                obj->regType = REG_M;
            } else {
                arrObj = getVREG(toVal(ir->opt1));
                arrObj = processSymbol(arrObj, ir);
                if (toVal(ir->opt1)->isParam) {
                    arrObj = processLoad(arrObj, ir, nullptr);
                }
                offObj = getVREG(toVal(ir->opt2));
                if (isImmInLimit(offObj, 12)) {
                    offObj = new vReg(offObj->value);
                    offObj->ref = arrObj;
                    ir->addASMBack("addi", obj, {arrObj, offObj});
                } else {
                    offObj = processLoad(offObj, ir);
                    vReg* r = new vReg(0);
                    vReg* off = new vReg();
                    r->ref = arrObj;
                    ir->addASMBack("addi", off, {offObj, r});
                    ir->addASMBack("add", obj, {arrObj, off});
                }
            }
            obj->ref = arrObj;
            return 1;
        }});
    addMatchers(IRType::ARR, {[](pSysYIR ir) -> int {
                    vReg* obj = getVREG(ir->target);
                    vReg* arrObj = getVREG(toVal(ir->opt1));
                    arrObj = processSymbol(arrObj, ir);
                    vReg* offObj = getVREG(toVal(ir->opt2));
                    obj->regType = REG_R;
                    obj->isAddr = true;
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
                    return 1;
                }});
    addMatchers(IRType::RET, {[](pSysYIR ir) -> int {
                    vReg* retVal = nullptr;
                    if (ir->block->function->returnType != IR_VOID)
                        retVal = getVREG(toVal(ir->opt1));
                    addASM("ret", ir, nullptr, {retVal});
                    return 1;
                }});
    addMatchers(IRType::CALL, {[](pSysYIR ir) -> int {
                    int paramCnt = 0;
                    pSysYIR paramIr = ir->prev;
                    vector<vReg*> paramRegs{};
                    vReg* retVal = nullptr;
                    pIRFunc func = toFunc(ir->opt1);
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
                            paramReg->value = 8 * (paramCnt - 8);
                            paramReg->ref = &func->stackCapacity;
                            paramReg->isAddr = true;
                        }
                        addASM("mv", paramIr, paramReg,
                               {getVREG(toVal(paramIr->opt1))});
                        paramIr = paramIr->prev;
                        paramCnt++;
                    }
                    ir->block->function->callerMaxStackSize = max(
                        ir->block->function->callerMaxStackSize, paramCnt - 8);
                    if (func->returnType != IR_VOID) {
                        if (retVal == nullptr) {
                            retVal = new vReg();
                            retVal->regId = a0;
                            retVal->fixed = true;
                        }
                    } else {
                        retVal = nullptr;
                    }
                    ir->addASMBack(callOp, retVal,
                                   {paramRegs.begin(), paramRegs.end()}, func);
                    if (func->returnType != IR_VOID) {
                        addASM("mv", ir, getVREG(ir->target), {retVal});
                    }
                    return 1;
                }});
}

void RISCV::processAsm(ASMInstr* s) {
    string op = s->name;
    if (op == "addi") {
        if (auto imm = s->op[1]) {
            int v = imm->getValue();
            if (v == 0) {
                s->op.pop_back();
                s->name = assignOp;
            } else if (!isInLimit(v, 12)) {
                auto r = newReg(t0);
                s->ir->addASMFront(loadImmOp, r, {s->op[1]}, nullptr, s);
                s->op[1] = r;
                s->name = "add";
            }
        }
    } else if (IS_MEM_OP(op)) {
        int memIdx = 0;
        if (IS_STORE_OP(op)) memIdx = 1;
        if (auto m = s->op[memIdx]) {
            int off = m->getValue();
            if (!isInLimit(off, 12)) {
                auto r = newReg(t0);
                s->ir->addASMFront(loadImmOp, r, {new vReg(off)}, nullptr, s);
                s->ir->addASMFront("add", r, {r, s->op[memIdx]}, nullptr, s);
                s->op[memIdx] = r;
            }
        }
    }
}

void RISCV::prepareFuncPreRegs(pIRFunc f) {
    vReg* v = nullptr;
    for (int i = 0; i < f->params.size(); i++) {
        v = new vReg();
        if (i < paramRegCnt) {
            v->regId = a0 + i;
        } else {
            v->regType = REG_M;
            v->value = 8 * (i - paramRegCnt);
            v->regId = fp;
            v->ref = v;
            v->isAddr = true;
        }
        valRegs[f->params[i]] = v;
    }
    if (f->returnType != IR_VOID) {
        v = new vReg();
        v->regId = a0;
        valRegs[f->returnVal] = v;
    }
}

// call after reg alloc
/** HIGH
 * =============== <= s0(fp)^
 * ra                       |
 * s1                       |=> regStackSize
 * ...                      |
 * -----------^<= func->stackCapacity vReg (.regId = s0, .value = -regStackSize)
 * local mem  | =>offset
 * xxx arr   --.ref = func->stackCapacity, .value = offset .regId = -1
 *
 * -----------
 * space for stack args
 * =============== <= sp
 *  LOW
 */
void RISCV::prepareFuncInitExitAsm(pIRFunc func, unordered_set<int>& useRegs) {
    auto& initInstrs = func->initInstrs;
    auto& exitInstrs = func->exitInstrs;
    vector<int> stackRegs{};
    vector<vReg*> stackMem{};
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
    int regStackSize = 0;
    for (auto r : stackRegs) {
        vReg* mReg = new vReg();
        mReg->regType = REG_M;
        mReg->size = 2;
        mReg->value = regStackSize;
        mReg->regId = sp;
        regStackSize += 8;
        initInstrs->addASMFront(storeDwOp, nullptr, {newReg(r), mReg});
        exitInstrs->addASMBack(loadDwOp, newReg(r), {mReg});
    }
    func->stackCapacitySize += func->callerMaxStackSize * 8;
    func->stackCapacitySize += regStackSize;
    // order: fifo (sp->s0, mem)
    // 方便起见，所有情况开栈sp都分两段减小
    func->stackCapacitySize =
        getAligned(func->stackCapacitySize, frameByteAlign);
    if (func->stackCapacitySize) {
        initInstrs->addASMFront("addi", newReg(sp),
                                {newReg(sp), new vReg(-regStackSize)});
        initInstrs->addASMBack("addi", newReg(s0),
                               {newReg(sp), new vReg(regStackSize)});
        int left_sp = func->stackCapacitySize - regStackSize;
        if (left_sp) {
            if (isInLimit(-left_sp, 12)) {
                initInstrs->addASMBack("addi", newReg(sp),
                                       {newReg(sp), new vReg(-left_sp)});
            } else {
                initInstrs->addASMBack(loadImmOp, newReg(t0),
                                       {new vReg(-left_sp)});
                initInstrs->addASMBack("add", newReg(sp),
                                       {newReg(sp), newReg(t0)});
            }
            if (isInLimit(left_sp, 12)) {
                exitInstrs->addASMFront("addi", newReg(sp),
                                        {newReg(sp), new vReg(left_sp)});
            } else {
                exitInstrs->addASMFront("add", newReg(sp),
                                        {newReg(sp), newReg(t0)});
                exitInstrs->addASMFront(loadImmOp, newReg(t0),
                                        {new vReg(left_sp)});
            }
        }
        exitInstrs->addASMBack("addi", newReg(sp),
                               {newReg(sp), new vReg(regStackSize)});
    }
    func->stackCapacity.value = -regStackSize;
}