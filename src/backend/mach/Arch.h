#ifndef ARCH_H
#define ARCH_H
#include "Structure.h"
#include "unordered_set"
using namespace std;
/*
 * rule:
 * storeOp use, memObj(use)
 * loadOp def, memObj
 * callOp ret(def), use... , target
 * others def, use...
 */
#if EM_ARCH == EM_RISCV

#define storeOp "sw"
#define storeDwOp "sd"
#define loadOp "lw"
#define loadDwOp "ld"
#define loadAddrOp "la"
#define loadImmOp "li"
#define assignOp "mv"
#define callOp "call"
#define retOp "ret"
#define framePtrRegId 8

#define memByteAlign 4
#define paramRegCnt 8

#define commonCalImmBit 12

#define SEC_RO ".section .rodata"
#define SEC_RW ".data"
#define SEC_RX ".text"

#define ASM_DECL(s) ".global " + s
#define ASM_DATA_VAL ".word"
#define ASM_DATA_ZERO ".zero"
#define ASM_DATA_STR ".string"

#endif

#define IS_STORE_OP(s) ((s == storeOp) || (s == storeDwOp))
#define IS_LOAD_OP(s) ((s == loadOp) || (s == loadDwOp))
#define IS_MEM_OP(s) (IS_STORE_OP(s) || IS_LOAD_OP(s))

static unordered_map<pIRValObj, vReg*> valRegs;

inline bool isImm(pIRScalValObj scal) {
    if (!scal) return false;
    if (!scal->isConstant()) return false;
    return true;
}

inline bool isInLimit(int val, int width) {
    int lim = 1 << width;
    int v = val + lim / 2;
    return v >= 0 && v < lim;
}

inline int getAligned(int x, int align) {
    return ((x + align - 1) / align) * align;
}

inline bool isImm(pIRObj obj) { return isImm(toScal(obj)); }

inline bool isImm(vReg* val) { return val->regType == REG_IMM; }

inline bool isImmInLimit(vReg* val, int width) {
    if (isImm(val)) {
        return isInLimit(val->getValue(), width);
    }
    return false;
}

inline void setVregMem(vReg* val, pIRFunc func) {
    func->stackCapacitySize += memByteAlign * val->size;
    val->ref = &func->stackCapacity;
    val->value = -func->stackCapacitySize;
}

vReg* getVREG(pIRValObj obj);
bool checkDoubleOpImm(
    pSysYIR ir, vReg*& immScal, vReg*& regObj, bool checkSecOnly = false,
    bool (*check)(vReg*) = [](vReg* r) -> bool { return true; });
vReg* processSymbol(vReg* val, pSysYIR ir, ASMInstr* instr = nullptr);
vReg* processLoad(vReg* val, pSysYIR ir, ASMInstr* instr = nullptr);
vReg* processStore(vReg* val, pSysYIR ir, ASMInstr* instr = nullptr);
ASMInstr* addASM(string name, pSysYIR ir, vReg* des, vector<vReg*> ops,
                 pBlock target = nullptr, bool noStore = false);

int matchCalImmInstr(
    string name, pSysYIR ir, bool checkSecOnly = false,
    bool (*check)(vReg*) = [](vReg* r) -> bool {
        if (isImmInLimit(r, commonCalImmBit)) {
            return true;
        }
        r->regType = REG_R;
        return false;
    });

int matchCalInstr(string name, pSysYIR ir);

class BaseArch {
   public:
    map<int, string> regs;
    map<IRType, vector<int (*)(pSysYIR)> > matchers;
    vector<int> genRegsId;
    set<int> callerSaveRegs;
    set<int> calleeSaveRegs;
    int stackPointerRegId = -1;
    int framePointerRegId = -1;
    int frameByteAlign = 16;
    int branchBlockASMLimit = 512;
    BaseArch() = default;
    virtual ~BaseArch() = default;
    virtual void defineArchInfo() = 0;
    void addMatchers(IRType type,
                     initializer_list<int (*)(pSysYIR)> newMatchers) {
        for (auto matcher : newMatchers) {
            matchers[type].push_back(matcher);
        }
    }
    static void addRegs(vector<int>& regsVec, vector<int> regs) {
        for (int r : regs) {
            regsVec.push_back(r);
        }
    }
    static void addRegs(set<int>& regSet, vector<int> regs) {
        for (int r : regs) {
            regSet.insert(r);
        }
    }
    bool matchIR(pSysYIR ir);
    virtual void processAsm(ASMInstr* s) = 0;
    virtual void matchBlockEnd(pBlock block, vector<pBlock>& nextBlocks) = 0;
    virtual void prepareFuncPreRegs(pIRFunc func) = 0;
    virtual void prepareFuncInitExitAsm(pIRFunc func,
                                        unordered_set<int>& useRegs) = 0;
};

#endif
