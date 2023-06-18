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

void RISCV::defineArchInfo(){
    stackPointerRegId = REG::sp;
    memByteAlign = 4;
    addMatchers(IRType::ADD,
    {
        [](pSysYIR ir)->int{
            return 0;
        },
    });
}