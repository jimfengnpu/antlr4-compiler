#ifndef ASM_EMIT_H
#define ASM_EMIT_H

#include "IRProcessor.h"
#include "IRRunner.h"
#include "Arch.h"
#include <sstream>

class AsmEmitter: public IRProcessor{
    IRRunner *runner;
    ofstream fout;
    BaseArch* archInfo;
public:
    AsmEmitter(string fileName, BaseArch* arch, IRRunner* runner): 
        fout(fileName, ios::out), runner(runner), archInfo(arch){}
    virtual void apply(ASTVisitor& visitor){
        runner->visit(visitor.globalData);
        emitData(&visitor.globalSymbolTable);
        for(auto f: visitor.functions){
            if(f->entry){
                emitFunc(f);
            }
        }
    }
    void emitData(SymbolTable* table);
    void emitFunc(pIRFunc func);
    string printAsmOp(vReg* reg);
    void printAsm(ASMInstr* instr);
};
#endif