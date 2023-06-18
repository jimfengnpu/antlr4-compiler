#ifndef ARCH_H
#define ARCH_H
#include "SysYIR.h"
using namespace std;


class BaseArch{
public:
    map<int, string> regs;
    map<IRType, vector<int (*)(pSysYIR)> > matchers;
    vector<int> genRegsId;
    int stackPointerRegId;
    int memByteAlign;
    BaseArch(){}
    virtual void defineArchInfo()=0;
    void addMatchers(IRType type, initializer_list<int (*)(pSysYIR)> newMatchers){
        for(auto matcher: newMatchers){
            matchers[type].push_back(matcher);
        }
    }

    bool matchIR(pSysYIR ir);
};


class RISCV: public BaseArch{
    enum REG{
        zero, ra, sp, gp, tp, t0, t1, t2, s0=8, fp=8, s1,
        a0, a1, a2, a3, a4, a5, a6, a7, 
        s2, s3, s4, s5, s6, s7, s8, s9, s10, s11,
        t3, t4, t5, t6, pc
    };
    RISCV(){
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
    virtual void defineArchInfo();
};
#endif