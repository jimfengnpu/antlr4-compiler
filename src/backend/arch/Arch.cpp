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

inline bool isImm(pIRObj obj, int limit){
    auto scal = toScal(obj);
    if(!scal)return false;
    if(!scal->isConst)return false;
    int v = scal->value;
    return (v < (1<<(limit-1)) && (v >= -(1<<(limit-1))));
}

bool isInstrImm(pIRObj obj){
    return isImm(obj, 12);
}

void processIdxStore(pIRValObj obj, pSysYIR ir){
    if(!obj || obj->fa == nullptr)return;
    assert(obj->offsetObj != nullptr);
    ir->addASMBack("sw", {obj, obj->offsetObj});
}

int matchCalImmInstr(string name, pSysYIR ir, 
    int (*transVal)(int) = [](int v)->int{return v;}){
    pIRValObj immObj=nullptr, regObj=nullptr;
    if(isInstrImm(ir->opt1)){
        immObj=toVal(ir->opt1);regObj=toVal(ir->opt2);
    }else if(isInstrImm(ir->opt2)){
        immObj=toVal(ir->opt2);regObj=toVal(ir->opt1);
    }
    if(nullptr != immObj){
        immObj->regInfo.regType = REG_IMM;
        immObj->regInfo._val.immVal = transVal(toScal(immObj)->value);
        ir->addASMBack(name, {ir->target, regObj, immObj});
        return 1;
    }
    return 0;
}

int matchCalInstr(string name, pSysYIR ir){
    ir->addASMBack(name, {ir->target, toVal(ir->opt1), toVal(ir->opt2)});
    return 1;
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
            int imm=matchCalImmInstr("addiw", ir);
            if(imm)return imm;
            return matchCalInstr("add", ir);
        }
    });
    addMatchers(IRType::SUB,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("addi", ir, [](int v)->int{return -v;});
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
    
    addMatchers(IRType::NEG,
    {
        [](pSysYIR ir)->int{
            return matchCalInstr("neg", ir);
        }
    });
    addMatchers(IRType::IDX,
    {
        [](pSysYIR ir)->int{
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

}