#ifndef ASM_MODIFY_H
#define ASM_MODIFY_H

#include "Arch.h"
#include "IRProcessor.h"

class AsmModifier : public IRProcessor {
    BaseArch* archInfo;
   public:
    AsmModifier(BaseArch* arch): archInfo(arch){}
    virtual pBlock visit(pBlock block);
    virtual void apply(Prog& prog) {
        for (auto func : prog.functions) {
            for(pBlock block=func->entry; block; ){
                block = visit(block);
            }
        }
    }
};

#endif