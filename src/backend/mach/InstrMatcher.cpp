#include "InstrMatcher.h"

pBlock InstrMatcher::visit(pBlock block) {
    for (auto ir = block->irHead; ir != nullptr && ir->type != IRType::BR;
         ir = ir->next) {
        archInfo->matchIR(ir);
    }
    return nullptr;
}
