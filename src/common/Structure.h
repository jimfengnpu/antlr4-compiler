#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <assert.h>

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// #define VAL_IR 1
// #define VAL_LIVE 1
// #define VAL_CFGDOM 1

// #define VAL_RUN 1

// EM defination refered from `elf.h`
#define EM_RISCV 243

#define EM_ARCH EM_RISCV

#define IR_VOID 0
#define IR_INT 1
#define IR_FLOAT 2

#define IR_NORMAL 0
#define IR_BRANCH 1
#define IR_LOOP 2

#define IR_UNDEF 0
#define IR_CONST 1
#define IR_NAC 2
#define CONST_OP(x, y) (((x) == 1 && (y) == 1) ? 1 : 2)
#define CONST_STATE(x, y) (min(2, (x) + (y)))

#define REG_IMM 0
#define REG_R 1
#define REG_M 2

#define REG_STR(x) #x

#define ENUM_STR(x, offset) #x + (offset)

#define ENUMCASE_TO_STRING(x, offset) \
    case x:                           \
        return ENUM_STR(x, offset);

// class IRObj;
class IRValObj;
typedef shared_ptr<IRValObj> pIRValObj;
class IRScalValObj;
typedef shared_ptr<IRScalValObj> pIRScalValObj;
class IRArrValObj;
class SysYIR;
typedef shared_ptr<SysYIR> pSysYIR;
class FuncFrame;
class IRBlock;
typedef shared_ptr<IRBlock> pBlock;
class IRFunc;
class SymbolTable;
typedef shared_ptr<IRFunc> pIRFunc;
// class BlockContext;

class vReg {
   public:
    /*
     * REG_R: data usually in phy reg
     *     regId: equals enum value of coresponding reg
     * REG_M: data usually in mem (.data or stack)
     *     var: == nullptr: stack mem, stackMemOff: offset with frame
     * pointer(usually neg)
     *     else:       var: base var of this mem(global name or
     * arr fa) stackMemOff: offset with fa
     */
    int regType = REG_R;
    int immVal = 0;
    int stackMemOff = 0;
    int regId = -1;
    shared_ptr<IRValObj> var = nullptr;
    vReg() = default;
    vReg(int type, int immVal) : regType(type) { this->immVal = immVal; }
};

class IRObj {
   public:
    string name;
    SymbolTable *scopeSymbols = nullptr;
    // for val/arr: ident | %t + index in CFG_val
    // for CFG: function name ident
    // for BB: .L + index in CFG_master/branch/loop

    bool isIdent;
    IRObj() {}
    IRObj(bool isIndent, string name) : isIdent(isIndent), name(name) {}
    virtual void print(ostream &os) const;
    friend ostream &operator<<(ostream &os, const IRObj &val) {
        val.print(os);
        return os;
    }
};
typedef shared_ptr<IRObj> pIRObj;

class IRValObj : public IRObj {
    static int tmpValId;

   public:
    bool isConst;
    bool isTmp;
    int offset;
    shared_ptr<IRScalValObj> offsetObj;
    shared_ptr<IRArrValObj> fa;
    // ssa u-d <lv 3> **add within ssa rename**
    bool ssaDef = false;
    pSysYIR defStruction;        // for no-ssa val=>nullptr; common=>pIR
    set<pSysYIR> useStructions;  //... common=>pIR; branch=>pBlock.branchIR;
    // machine info <lv 4> **arch associated**
    vReg regInfo;

    IRValObj() {}
    IRValObj(bool isConst, bool isIdent, string name)
        : IRObj(isIdent, name.empty() ? getDefaultName() : name),
          isTmp(name.empty()),
          fa(nullptr),
          isConst(isConst) {}
    IRValObj(const shared_ptr<IRArrValObj> &arrParent, string name)
        : IRObj(true, name.empty() ? getDefaultName() : name),
          isTmp(name.empty()),
          fa(arrParent),
          isConst(((IRValObj *)arrParent.get())->isConst) {}
    // note: for const indent return true
    inline bool isConstant() { return isConst && (fa == nullptr); }
    void setImmRegWithVal(int val) {
        regInfo.regType = REG_IMM;
        regInfo.immVal = val;
    }
    inline vReg *reg() { return &regInfo; }
    virtual void print(ostream &os) const override;
    virtual string getDefaultName() { return "%t" + to_string(++tmpValId); }
};
inline pIRValObj toVal(pIRObj obj) {
    return dynamic_pointer_cast<IRValObj>(obj);
}

class ASMInstr {
   public:
    string name;
    vector<vReg *> op;
    pBlock jTarget;
    pIRFunc callFunc;
    SysYIR *ir = nullptr;
    ASMInstr *next = nullptr;
    ASMInstr *prev = nullptr;
    ASMInstr(string name, vector<vReg *> oprands, pBlock jBlock = nullptr)
        : name(name) {
        for (auto opArg : oprands) {
            if (opArg) {
                op.push_back(opArg);
            }
        }
        if (jBlock) {
            jTarget = jBlock;
        }
    }
    void addOp(vReg *nOp) {
        if (nOp) {
            op.push_back(nOp);
        }
    }
};

class IRArrValObj : public IRValObj {
   public:
    map<int, shared_ptr<IRScalValObj>> value;
    vector<int> dims;  // int[2][3] => vector(2, 3)
    int size;
    IRArrValObj(bool isConst, vector<int> dims, string name)
        : IRValObj(isConst, true, name), dims(dims) {
        size = 1;
        for (auto d : dims) {
            size *= d;
        }
        regInfo.regType = REG_M;
        value = map<int, shared_ptr<IRScalValObj>>();
    }
    IRArrValObj(const shared_ptr<IRArrValObj> &arrParent, vector<int> dims,
                string name)
        : IRValObj(arrParent, name) {
        size = 1;
        for (auto d : dims) {
            size *= d;
        }
        regInfo.regType = REG_M;
    }
    virtual void print(ostream &os) const override;
};
typedef shared_ptr<IRArrValObj> pIRArrValObj;

class IRScalValObj : public IRValObj {
   public:
    // <lv 4> const folding
    int constState;
    int value = 0;
    IRScalValObj() {}
    IRScalValObj(int value)
        : value(value),
          IRValObj(true, false, to_string(value)),
          constState(IR_CONST) {}
    IRScalValObj(bool isConst, string name)
        : value(0), IRValObj(isConst, true, name), constState(IR_NAC) {}
    IRScalValObj(const shared_ptr<IRArrValObj> &arrParent, string name)
        : IRValObj(arrParent, name), constState(IR_NAC) {}
    virtual void print(ostream &os) const override;
};

inline pIRScalValObj toScal(pIRObj obj) {
    return dynamic_pointer_cast<IRScalValObj>(obj);
}

class IRStrValObj : public IRValObj {
    static int constStrId;

   public:
    string value;
    IRStrValObj() {}
    IRStrValObj(string value, string name)
        : value(value), IRValObj(true, false, name) {}
    virtual void print(ostream &os) const override;
    virtual string getDefaultName() { return ".s" + to_string(++constStrId); }
};
typedef shared_ptr<IRStrValObj> pIRStrValObj;

#define IR_TO_STRING(x) ENUMCASE_TO_STRING(x, 8)

enum class IRType : int {
    NOP,
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NEG,
    AND,
    OR,
    SL,
    SR,
    NOT,
    EQ,
    NEQ,
    GT,
    LT,
    GE,
    LE,
    ARR,
    IDX,
    CALL,
    PARAM,
    RET,
    BR,
    DEF,
    PHI,
};
static map<string, IRType> opfinder[2] = {
    {{"+", IRType::ASSIGN}, {"-", IRType::NEG}, {"!", IRType::NOT}},
    {{"+", IRType::ADD},
     {"-", IRType::SUB},
     {"*", IRType::MUL},
     {"/", IRType::DIV},
     {"%", IRType::MOD},
     {"==", IRType::EQ},
     {"!=", IRType::NEQ},
     {"<", IRType::LT},
     {">", IRType::GT},
     {"<=", IRType::LE},
     {">=", IRType::GE}}};
static string IRTypeName(IRType type) {
    switch (type) {
        IR_TO_STRING(IRType::ASSIGN)
        IR_TO_STRING(IRType::ADD)
        IR_TO_STRING(IRType::SUB)
        IR_TO_STRING(IRType::MUL)
        IR_TO_STRING(IRType::DIV)
        IR_TO_STRING(IRType::MOD)
        IR_TO_STRING(IRType::NEG)
        IR_TO_STRING(IRType::AND)
        IR_TO_STRING(IRType::OR)
        IR_TO_STRING(IRType::SL)
        IR_TO_STRING(IRType::SR)
        IR_TO_STRING(IRType::NOT)
        IR_TO_STRING(IRType::EQ)
        IR_TO_STRING(IRType::NEQ)
        IR_TO_STRING(IRType::GT)
        IR_TO_STRING(IRType::LT)
        IR_TO_STRING(IRType::GE)
        IR_TO_STRING(IRType::LE)
        IR_TO_STRING(IRType::ARR)
        IR_TO_STRING(IRType::IDX)
        IR_TO_STRING(IRType::CALL)
        IR_TO_STRING(IRType::PARAM)
        IR_TO_STRING(IRType::RET)
        IR_TO_STRING(IRType::DEF)
        IR_TO_STRING(IRType::PHI)
        IR_TO_STRING(IRType::BR)
        default:
            return "unknown";
    }
}
class IRBlock;
typedef shared_ptr<IRBlock> pBlock;

class SysYIR : public IRObj {
    deque<ASMInstr *> asmInstrs;

   public:
    bool removedMask = false;
    IRType type;
    pIRValObj target;
    pIRObj opt1;
    pIRObj opt2;
    shared_ptr<SysYIR> prev = nullptr;
    shared_ptr<SysYIR> next = nullptr;
    pBlock block = nullptr;
    ASMInstr *asmHead = nullptr;
    ASMInstr *asmTail = nullptr;
    // <lv 4> asm && arch
    bool asmRemovedMask = false;

    SysYIR(IRType type, pIRValObj t, pIRObj op1, pIRObj op2)
        : type(type), target(t), opt1(op1), opt2(op2) {}
    virtual void print(ostream &os) const override;

    ASMInstr *addASMBack(ASMInstr *instr, ASMInstr *end = nullptr);

    ASMInstr *addASMFront(ASMInstr *instr, ASMInstr *before = nullptr);

    ASMInstr *addASMBack(string name, vector<vReg *> oprands,
                         pBlock target = nullptr) {
        auto instr = new ASMInstr(name, oprands, target);
        return addASMBack(instr);
    }

    ASMInstr *addASMFront(string name, vector<vReg *> oprands,
                          pBlock target = nullptr) {
        auto instr = new ASMInstr(name, oprands, target);
        return addASMFront(instr);
    }
    int asmSize() { return asmInstrs.size(); }
};

int CalConstExp(IRType type, int exp1Val, int exp2Val = 0);

class IRBlock : public IRObj {  // Basic Block

    static int masterId;
    static int loopId;
    static int branchId;
    vector<shared_ptr<SysYIR>> structions;

   public:
    // basic & CFG <lv 0>
    int blockType;  // 0 normal 1 branch 2 loop
    shared_ptr<SysYIR> branchIR;
    pIRScalValObj branchVal = nullptr;
    pBlock nextNormal = nullptr;
    pBlock nextBranch = nullptr;
    set<pBlock> from;
    pIRFunc function;
    pSysYIR irHead, irTail;
    // dom <lv 1>
    set<pBlock> domChild;
    set<pBlock> domFrontier;
    pBlock domFa;
    // live interval <lv 2>
    set<pIRValObj> defObj;  // 当前block内定义的值,包括phi指令定义的
    set<pIRValObj>
        useObj;  // 当前block内用到的,但定值点在前面block的值(不含phi指令用到的(因phi的use与前驱相关))
    set<pIRValObj>
        liveIn;  // 当前block开头处活跃的值(当前块或后面块用到但是定值点在前面block)不包含phi指令用到的
    set<pIRValObj>
        liveOut;  // 当前block结尾处活跃的值(对后面有用,包含phi指令用到的)
    // SSA <lv3>
    map<pIRValObj, map<pBlock, pIRValObj>>
        phiList;  // x(k) => [ fromBlock => x(i)]
    // asm block order <lv 4>
    pBlock asmNextBlock = nullptr;

    IRBlock(int blockType, string name = "")
        : IRObj(IR_VOID, name.empty() ? getDefaultName(blockType) : name),
          blockType(blockType) {}
    // insert before %ir%(if %ir% ==nullptr,insert tail, just before branch ir)
    shared_ptr<SysYIR> insertIR(IRType type, pIRValObj t, pIRObj op1,
                                pIRObj op2, pSysYIR ir = nullptr);

    bool finishBB(pBlock next_normal, pBlock next_branch = nullptr,
                  pIRScalValObj branch_val = nullptr);

    void remove(pSysYIR ir);

    int size();    // block structions size (jump excluded)
    int asmLen();  // block asm length
    bool hasPhi();

    virtual void print(ostream &os) const override;

    virtual string getDefaultName(int type) {
        return ".L" + to_string(++masterId);
    }
};
// False, True
typedef pair<pBlock, pBlock> pCondBlocks;

class SymbolTable {
   public:
    bool isGlobal = false;
    map<string, pIRObj> symbols = {};
    SymbolTable() = default;
    SymbolTable(const SymbolTable &table) : isGlobal(false) {
        symbols = table.symbols;
    }
    ~SymbolTable() = default;
    void registerSymbol(const pIRObj &obj) {
        symbols.insert({obj.get()->name, obj});
    }
    pIRObj findSymbol(string name) {
        if (symbols.empty()) return nullptr;
        try {
            return symbols.at(name);
        } catch (...) {
            return nullptr;
        }
    }
};

class IRFunc : public IRObj {
   public:
    vector<pIRValObj> params;
    set<pBlock> blocks;
    pBlock entry;
    pBlock exit;
    int returnType;
    pIRValObj returnVal;

    set<pIRValObj> vals;
    vector<ASMInstr> initInstrs;
    vReg stackSpaceImm;

    SymbolTable *symbolTable;
    // table == nullptr : lib function
    IRFunc(int returnType, string name, vector<pIRValObj> params,
           SymbolTable *table)
        : IRObj(true, name),
          returnType(returnType),
          symbolTable(table),
          params(params) {
        if (symbolTable != nullptr) {
            for (auto &arg : this->params) {
                symbolTable->registerSymbol(arg);
                arg->scopeSymbols = symbolTable;
            }
        }
    }
    ~IRFunc() = default;

    virtual void print(ostream &os) const override;
};
inline pIRFunc toFunc(pIRObj obj) { return dynamic_pointer_cast<IRFunc>(obj); }

class Prog {
   public:
    SymbolTable globalSymbolTable;
    std::vector<pIRFunc> functions;
    pIRFunc mainFunc;
    pBlock globalData;
    Prog() = default;
};
#endif
