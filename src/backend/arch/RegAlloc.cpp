#include "RegAlloc.h"

void RegAllocator::allocReg(pIRFunc func){
    set<vReg*> vals{};
    phiFa.clear();
    while(!checkList.empty()){
        checkList.pop();
    }
    for(pBlock block: func->blocks){
        
    }

}