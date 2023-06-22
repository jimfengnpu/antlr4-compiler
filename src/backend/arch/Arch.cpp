#include "Arch.h"

#if EM_ARCH == EM_RISCV
string storeOp = "sw";
string loadOp = "lw";
#endif

bool BaseArch::matchIR(pSysYIR ir){
    for(auto matcher: matchers[ir->type]){
        if(int matchSize = matcher(ir)){
            auto maskIr = ir->prev;
            while(nullptr != maskIr && (--matchSize)){
                maskIr->asmRemovedMask = true;
                maskIr = maskIr->prev;
            }
            return true;
        }
    }
    return false;
}

vReg* processStore(pIRValObj obj, ASMInstr** instr){
    if(!obj)return nullptr;
    auto scal = toScal(obj);
    if(!scal || scal->regInfo.regType != REG_M){
        instr = nullptr;
        return obj->reg();
    }
    auto nReg = new vReg();
    *instr = new ASMInstr(storeOp, {nReg, obj->reg()});
    return nReg;
}

vReg* processLoad(pIRValObj obj, ASMInstr** instr){
    if(!obj)return nullptr;
    auto scal = toScal(obj);
    if(!scal || scal->regInfo.regType != REG_M){
        instr = nullptr;
        return obj->reg();
    }
    auto nReg = new vReg();
    *instr = new ASMInstr(loadOp, {nReg, obj->reg()});
    return nReg;
}


inline bool isImm(pIRScalValObj scal){
    if(!scal)return false;
    if(!scal->isConst)return false;
    return true;
}

inline bool isImm(pIRObj obj){
    return isImm(toScal(obj));
}

ASMInstr* addASM(string name, pSysYIR ir, 
    initializer_list<pIRValObj> ops, pBlock target=nullptr){
    ASMInstr* ldInstr = nullptr, *stInstr = nullptr;
    auto targ = processStore(ir->target, &stInstr);
    auto mainInstr = new ASMInstr(name, {targ}, target);
    for(auto op: ops){
        if(op){
            auto regOp = processLoad(op, &ldInstr);
            if(ldInstr){
                ir->addASMBack(ldInstr);
            }
            mainInstr->addOp(regOp);
        }
    }
    ir->addASMBack(mainInstr);
    if(stInstr){
        ir->addASMBack(stInstr);
    }
    return mainInstr;
}

inline bool isImmInLimit(pIRScalValObj obj, int width){
    int lim = 1<<width;
    int v = obj->value + lim/2 ;
    return v >= 0 && v < lim;
}

bool checkDoubleOpImm(pSysYIR ir, pIRScalValObj& immScal, 
    pIRValObj& regObj, bool checkSecOnly=false, 
    bool (*check)(pIRScalValObj)=[](pIRScalValObj obj)->bool{return true;}){
    if(isImm(ir->opt1)&&(!checkSecOnly)){
        immScal = toScal(ir->opt1);
        regObj = toVal(ir->opt2);
    }else if(isImm(ir->opt2)){
        immScal = toScal(ir->opt2);
        regObj = toVal(ir->opt1);
    }else{
        immScal = nullptr;
        regObj = nullptr;
        return false;
    }
    return true;
}

int matchCalImmInstr(string name, pSysYIR ir,
    bool checkSecOnly=false, 
    bool (*check)(pIRScalValObj)=[](pIRScalValObj obj)->bool{
        if(isImmInLimit(obj, 12)){
            obj->setImmRegWithVal(obj->value);
            return true;
        }
        return false;
    })
{
    pIRScalValObj immObj=nullptr;
    pIRValObj regObj=nullptr;
    checkDoubleOpImm(ir, immObj, regObj, checkSecOnly, check);
    if(nullptr != immObj){
        addASM(name, ir, {regObj, immObj});
        return 1;
    }
    return 0;
}

int matchCalInstr(string name, pSysYIR ir){
    addASM(name, ir, { toVal(ir->opt1), toVal(ir->opt2)});
    return 1;
}

int matchBrZeroInstr(string name, pSysYIR brValDef, 
    pSysYIR ir, pBlock target)
{
    map<string, string>oppoBranch={
        {"bgt", "blt"},
        {"blt", "bgt"},
        {"bge", "ble"},
        {"ble", "bge"}
    };
    pIRScalValObj imm=nullptr;
    pIRValObj reg=nullptr;
    if(checkDoubleOpImm(brValDef, imm, reg) && imm->value == 0){
        if(brValDef->type==IRType::EQ 
            || brValDef->type==IRType::NEQ){
            addASM(name + "z", ir, {reg}, target);
        }else{
            if(imm == brValDef->opt1){
                name = oppoBranch[name];
            }
            addASM(name + "z", ir, {reg, imm}, target);
        }
    }else{
        addASM(name, ir, {toVal(brValDef->opt1), toVal(brValDef->opt2)}, target);
    }
    return 2;
}

void RISCV::defineArchInfo(){
    stackPointerRegId = REG::sp;
    memByteAlign = 4;
    addGenRegs({

    });
    addMatchers(IRType::ASSIGN,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("li", ir, false, [](pIRScalValObj imm)->bool{
                return true;
            });
            if(imm)return imm;
            return matchCalInstr("mv", ir);
        }
    });
    addMatchers(IRType::ADD,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("addi", ir);
            if(imm)return imm;
            return matchCalInstr("add", ir);
        }
    });
    addMatchers(IRType::SUB,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("addi", ir, true, [](pIRScalValObj imm)->bool{
                if(isImmInLimit(imm, 12)){
                    imm->setImmRegWithVal(-imm->value);
                    return true;
                }
                return false;
            });
            if(imm)return imm;
            return matchCalInstr("sub", ir);
        }
    });
    addMatchers(IRType::MUL,
    {
        [](pSysYIR ir)->int{
            return matchCalInstr("mul", ir);
        }
    });
    addMatchers(IRType::DIV,
    {
        [](pSysYIR ir)->int{
            return matchCalInstr("div", ir);
        }
    });
    addMatchers(IRType::MOD,
    {
        [](pSysYIR ir)->int{
            return matchCalInstr("rem", ir);
        }
    });
    addMatchers(IRType::AND,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("andi", ir);
            if(imm)return imm;
            return matchCalInstr("and", ir);
        }
    });
    addMatchers(IRType::OR,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("ori", ir);
            if(imm)return imm;
            return matchCalInstr("or", ir);
        }
    });
    addMatchers(IRType::SL,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("slli", ir, true);
            if(imm)return imm;
            return matchCalInstr("sll", ir);
        }
    });
    addMatchers(IRType::SR,
    {
        [](pSysYIR ir)->int{
            pIRScalValObj immObj = toScal(ir->opt2);
            int imm=matchCalImmInstr("srai", ir, true);
            if(imm)return imm;
            return matchCalInstr("sra", ir);
        }
    });
    addMatchers(IRType::NEG,
    {
        [](pSysYIR ir)->int{
            return matchCalInstr("neg", ir);
        }
    });
    addMatchers(IRType::IDX,
    {
        [](pSysYIR ir)->int{
            matchCalInstr("add", ir);
            toVal(ir->target)->reg()->regType = REG_M;
            return 1;
        }
    });
    addMatchers(IRType::ARR,
    {
        [](pSysYIR ir)->int{
            matchCalInstr("add", ir);
            return 1;
        }
    });
    addMatchers(IRType::BR,
    {
        [](pSysYIR ir)->int{
            pSysYIR brValDef = toVal(ir->opt1)->defStruction;
            pBlock target = ir->block->nextBranch;
            int mask = 2;
            // assert(toVal(ir->opt1)->defStruction == brValDef);
            switch (brValDef->type)
            {
            case IRType::NOT:
                addASM("beqz", ir, {toVal(brValDef->opt1)}, target);
                break;
            case IRType::EQ:
                matchBrZeroInstr("beq", brValDef, ir, target);
                break;
            case IRType::NEQ:
                matchBrZeroInstr("bne", brValDef, ir, target);
                break;
            case IRType::GT:
                matchBrZeroInstr("bgt", brValDef, ir, target);
                break;
            case IRType::LT:
                matchBrZeroInstr("blt", brValDef, ir, target);
                break;
            case IRType::GE:
                matchBrZeroInstr("bge", brValDef, ir, target);
                break;
            case IRType::LE:
                matchBrZeroInstr("ble", brValDef, ir, target);
                break;
            default:
                addASM("bnez", ir, {toVal(brValDef->opt1)}, target);
                mask = 1;
                break;
            }
            return mask;
        }
    });
    addMatchers(IRType::CALL,
    {
        [](pSysYIR ir)->int{
            int paramCnt = 0;
            pSysYIR paramIr = ir->prev;
            while(paramIr && paramIr->type == IRType::PARAM){
                vReg* paramReg = new vReg();
                if(paramCnt < 8){
                    paramReg->regType = REG_R;
                    paramReg->_val.regId = a0 + paramCnt;
                }else{
                    paramReg->regType = REG_M;
                }
                ASMInstr* ldInstr = nullptr;
                vReg* regOp = processLoad(toVal(ir->opt1), &ldInstr);
                auto asmInstr = new ASMInstr("mv", {});
                asmInstr->addOp(paramReg);
                asmInstr->op.push_back(regOp);
                if(ldInstr)
                paramIr->addASMBack(ldInstr);
                paramIr->addASMBack(asmInstr);
                paramIr = paramIr->prev;
            }
            pIRFunc func = toFunc(ir->opt1);
            ir->addASMBack("call", {}, func->entry);
            if(func->returnType != IR_VOID){
                auto retVal = new vReg();
                retVal->regType = REG_R;
                retVal->_val.regId = a0;
                addASM("mv", ir, {})->addOp(retVal);
            }
            return paramCnt + 1;
        }
    });
}