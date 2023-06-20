#include "InstrMatcher.h"


pBlock InstrMatcher::visit(pBlock block){
    for(auto ir=block->irHead; ir!=nullptr;ir=ir->next){
        archInfo->matchIR(ir);
    }
    archInfo->matchIR(block->branchIR);
    return nullptr;
}
