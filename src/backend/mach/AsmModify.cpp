#include "AsmModify.h"

pBlock AsmModifier::visit(pBlock block) {
    for (auto ir = block->irHead; ir; ir = ir->next) {
        for (auto s = ir->asmHead; s; s = s->next) {
            archInfo->processAsm(s);
        }
    }
    return block->asmNextBlock;
}