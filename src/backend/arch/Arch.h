#ifndef ARCH_H
#define ARCH_H
#include "Structure.h"
using namespace std;
/*
 * rule:
 * storeOp use, memObj
 * loadOp def, memObj
 * callOp use... , target
 * others def, use...
 */
#if EM_ARCH == EM_RISCV
#define storeOp "sw"
#define loadOp "lw"
#define loadAddrOp "la"
#define callOp "call"
#define SEC_RO ".section .rodata"
#define SEC_RW ".data"
#define SEC_RX ".text"
#define ASM_DECL(s) ".global " + s
#define ASM_DATA_VAL ".word"
#define ASM_DATA_ZERO ".zero"
#define ASM_DATA_STR ".string"
#endif

class BaseArch {
   public:
    map<int, string> regs;
    map<IRType, vector<int (*)(pSysYIR)> > matchers;
    vector<int> genRegsId;
    set<int> callerSaveRegs;
    set<int> caleeSaveRegs;
    int stackPointerRegId = -1;
    int framePointerRegId = -1;
    int memByteAlign = 4;
    int frameByteAlign = 16;
    int branchBlockASMLimit = 512;
    int paramRegCnt;
    BaseArch() = default;
    virtual void defineArchInfo() = 0;
    void addMatchers(IRType type,
                     initializer_list<int (*)(pSysYIR)> newMatchers) {
        for (auto matcher : newMatchers) {
            matchers[type].push_back(matcher);
        }
    }
    void addGenRegs(initializer_list<int> regs) {
        for (int r : regs) {
            genRegsId.push_back(r);
        }
    }
    bool matchIR(pSysYIR ir);
    virtual void matchBlockEnd(pBlock block, vector<pBlock>& nextBlocks) = 0;
    virtual void prepareFuncParamRegs(pIRFunc func) = 0;
};

class RISCV : public BaseArch {
    enum REG {
        zero,
        ra,
        sp,
        gp,
        tp,
        t0,
        t1,
        t2,
        s0 = 8,
        fp = 8,
        s1,
        a0,
        a1,
        a2,
        a3,
        a4,
        a5,
        a6,
        a7,
        s2,
        s3,
        s4,
        s5,
        s6,
        s7,
        s8,
        s9,
        s10,
        s11,
        t3,
        t4,
        t5,
        t6,
        pc
    };

   public:
    RISCV() {
        regs[zero] = REG_STR(zero);
        regs[ra] = REG_STR(ra);
        regs[sp] = REG_STR(sp);
        regs[gp] = REG_STR(gp);
        regs[tp] = REG_STR(tp);
        regs[t0] = REG_STR(t0);
        regs[t1] = REG_STR(t1);
        regs[t2] = REG_STR(t2);
        regs[s0] = REG_STR(s0);
        regs[s1] = REG_STR(s1);
        regs[a0] = REG_STR(a0);
        regs[a1] = REG_STR(a1);
        regs[a2] = REG_STR(a2);
        regs[a3] = REG_STR(a3);
        regs[a4] = REG_STR(a4);
        regs[a5] = REG_STR(a5);
        regs[a6] = REG_STR(a6);
        regs[a7] = REG_STR(a7);
        regs[s2] = REG_STR(s2);
        regs[s3] = REG_STR(s3);
        regs[s4] = REG_STR(s4);
        regs[s5] = REG_STR(s5);
        regs[s6] = REG_STR(s6);
        regs[s7] = REG_STR(s7);
        regs[s8] = REG_STR(s8);
        regs[s9] = REG_STR(s9);
        regs[s10] = REG_STR(s10);
        regs[s11] = REG_STR(s11);
        regs[t3] = REG_STR(t3);
        regs[t4] = REG_STR(t4);
        regs[t5] = REG_STR(t5);
        regs[t6] = REG_STR(t6);
        regs[pc] = REG_STR(pc);
        defineArchInfo();
    }
    virtual void defineArchInfo() override;
    virtual void matchBlockEnd(pBlock block, vector<pBlock>& nextBlocks);
    virtual void prepareFuncParamRegs(pIRFunc func);
};
#endif
