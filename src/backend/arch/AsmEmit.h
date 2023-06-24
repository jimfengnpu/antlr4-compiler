#ifndef ASM_EMIT_H
#define ASM_EMIT_H

#include "IRProcessor.h"
#include "IRRunner.h"
#include <sstream>

class AsmEmitter: public IRProcessor{
    IRRunner *runner;
    ofstream fout;
public:
    AsmEmitter(string fileName, IRRunner* runner): fout(fileName, ios::out), runner(runner){}
    virtual void apply(ASTVisitor& visitor){
        runner->visit(visitor.globalData);
        
    }
};
#endif