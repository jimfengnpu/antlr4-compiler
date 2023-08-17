#ifndef ASM_EMIT_H
#define ASM_EMIT_H

#include <sstream>

#include "Arch.h"
#include "IRProcessor.h"
#include "IRRunner.h"

class AsmEmitter : public IRProcessor {
    IRRunner* runner;
    ofstream fout;
    BaseArch* archInfo;

   public:
    AsmEmitter(string fileName, BaseArch* arch, IRRunner* runner)
        : fout(fileName, ios::out), runner(runner), archInfo(arch) {}
    virtual void apply(Prog& prog) {
        runner->visit(prog.globalData);
        emitData(&prog.globalSymbolTable);
        for (auto f : prog.functions) {
            if (f->entry) {
                emitFunc(f);
            }
        }
    }
    void emitData(SymbolTable* table);
    void emitFunc(pIRFunc func);
    string printAsmOp(vReg* reg, bool memType);
    void printAsm(ASMInstr* instr);
};
#endif