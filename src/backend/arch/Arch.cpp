#include "Arch.h"



bool BaseArch::matchIR(pSysYIR ir){
    for(auto matcher: matchers[ir->type]){
        if(int matchSize = matcher(ir)){
            while(nullptr != ir && (--matchSize)){
                ir->asmRemovedMask = true;
                ir = ir->prev;
            }
            return true;
        }
    }
    return false;
}

void processIdxStore(pIRValObj obj, pSysYIR ir){
    if(!obj || obj->fa == nullptr)return;
    assert(obj->offsetObj != nullptr);
    ir->addASMBack("sw", {obj, obj->offsetObj});
}

inline bool isImm(pIRScalValObj scal){
    if(!scal)return false;
    if(!scal->isConst)return false;
    return true;
}

inline bool isImm(pIRObj obj){
    return isImm(toScal(obj));
}

inline bool isImmInLimit(pIRObj obj, int limit){
    auto scal = toScal(obj);
    if(!isImm(scal))return false;
    int v = scal->value;
    return (v < (1<<(limit-1)) && (v >= -(1<<(limit-1))));
}

bool isInstrImm(pIRObj obj){
    return isImmInLimit(obj, 12);
}

bool checkDoubleOpImm(pSysYIR ir, pIRScalValObj& immScal, pIRValObj& regObj){
    if(isImm(ir->opt1)){
        immScal = toScal(ir->opt1);
        regObj = toVal(ir->opt2);
    }else if(isImm(ir->opt2)){
        immScal = toScal(ir->opt2);
        regObj = toVal(ir->opt1);
    }else{
        return false;
    }
    return true;
}

int matchCalImmInstr(string name, pSysYIR ir){
    pIRValObj immObj=nullptr, regObj=nullptr;
    if(isInstrImm(ir->opt1)){
        immObj=toVal(ir->opt1);regObj=toVal(ir->opt2);
    }else if(isInstrImm(ir->opt2)){
        immObj=toVal(ir->opt2);regObj=toVal(ir->opt1);
    }
    if(nullptr != immObj){
        immObj->setImmRegWithVal(toScal(immObj)->value);
        ir->addASMBack(name, {ir->target, regObj, immObj});
        return 1;
    }
    return 0;
}

int matchCalInstr(string name, pSysYIR ir){
    ir->addASMBack(name, {ir->target, toVal(ir->opt1), toVal(ir->opt2)});
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
            ir->addASMBack(name + "z", {reg}, target);
        }else{
            if(imm == brValDef->opt1){
                name = oppoBranch[name];
            }
            ir->addASMBack(name + "z", {reg, imm}, target);
        }
    }
    ir->addASMBack(name, {toVal(brValDef->opt1), toVal(brValDef->opt2)},
        target);
    return 2;
}

void RISCV::defineArchInfo(){
    stackPointerRegId = REG::sp;
    memByteAlign = 4;
    addMatchers(IRType::ASSIGN,
    {
        [](pSysYIR ir)->int{
            ir->addASMBack("mv", {ir->target, toVal(ir->opt1)});
            return 1;
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
            pIRScalValObj immObj = toScal(ir->opt2);
            if(nullptr != immObj && isInstrImm(immObj)){
                immObj->setImmRegWithVal(-immObj->value);
                ir->addASMBack("addi", {ir->target, toVal(ir->opt1), immObj});
                return 1;
            }
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
            pIRScalValObj immObj = toScal(ir->opt2);
            if(nullptr != immObj && isInstrImm(immObj)){
                immObj->regInfo.regType = REG_IMM;
                immObj->regInfo._val.immVal = immObj->value;
                ir->addASMBack("slli", {ir->target, toVal(ir->opt1), immObj});
                return 1;
            }
            return matchCalInstr("sll", ir);
        }
    });
    addMatchers(IRType::SR,
    {
        [](pSysYIR ir)->int{
            pIRScalValObj immObj = toScal(ir->opt2);
            if(nullptr != immObj && isInstrImm(immObj)){
                immObj->regInfo.regType = REG_IMM;
                immObj->regInfo._val.immVal = immObj->value;
                ir->addASMBack("srai", {ir->target, toVal(ir->opt1), immObj});
                return 1;
            }
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
            toVal(ir->target)->regInfo.regType = REG_M;
            ir->addASMBack("add", {toVal(ir->opt2), toVal(ir->opt1), toVal(ir->opt2)});
            return 1;
        }
    });
    addMatchers(IRType::ARR,
    {
        [](pSysYIR ir)->int{
            ir->addASMBack("add", {toVal(ir->opt2), toVal(ir->opt1), toVal(ir->opt2)});
            return 1;
        }
    });
    addMatchers(IRType::BR,
    {
        [](pSysYIR ir)->int{
            pSysYIR brValDef = ir->prev;
            pBlock target = ir->block->nextBranch;
            
            assert(toVal(ir->opt1)->defStruction == brValDef);
            switch (brValDef->type)
            {
            case IRType::NOT:
                ir->addASMBack("beqz", {toVal(brValDef->opt1)}, target);
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
                break;
            }
            return 2;
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
                auto asmInstr = new ASMInstr("mv", {}, nullptr);
                asmInstr->op.push_back(paramReg);
                asmInstr->op.push_back(&toVal(ir->opt1)->regInfo);
                ir->asmInstrs.push_front(asmInstr);
                paramIr = paramIr->prev;
            }
            pIRFunc func = toFunc(ir->opt1);
            ir->addASMBack("call", {}, func->entry);
            if(func->returnType != IR_VOID){
                auto asmInstr = new ASMInstr("mv", {ir->target}, nullptr);
                auto retVal = new vReg();
                retVal->regType = REG_R;
                retVal->_val.regId = a0;
                asmInstr->op.push_back(retVal);
                ir->asmInstrs.push_back(asmInstr);
            }
            return paramCnt + 1;
        }
    });
}