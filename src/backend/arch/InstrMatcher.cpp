#include "InstrMatcher.h"


pBlock InstrMatcher::visit(pBlock block){
    for(auto ir: block->structions){
        if(!ir->removedMask){
            archInfo->matchIR(ir);
        }
    }
    archInfo->matchIR(block->branchIR);
}
