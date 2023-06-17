#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <memory>
#include <utility>
#include <algorithm>
#include <iostream>
#include "../backend/arch/Arch.h"

using namespace std;

#define IR_VOID 0
#define IR_INT 1
#define IR_FLOAT 2

#define IR_NORMAL 0
#define IR_BRANCH 1
#define IR_LOOP 2

#define IR_UNDEF 0
#define IR_CONST 1
#define IR_NAC   2
#define CONST_OP(x, y) (((x)==1&&(y)==1)?1:2)
#define CONST_STATE(x, y) (min(2, (x) + (y)))


#define ENUM_STR(x, offset) \
    #x + (offset)

#define ENUMCASE_TO_STRING(x, offset) \
    case x:               \
        return ENUM_STR(x, offset);

#define VAL_IR 1
// #define VAL_LIVE 1
// #define VAL_CFGDOM 1

// #define VAL_RUN 1

// class IRObj;
// class IRValObj;
class IRScalValObj;
typedef shared_ptr<IRScalValObj> pIRScalValObj;
class IRArrValObj;
class SysYIR;
typedef shared_ptr<SysYIR> pSysYIR;
class FuncFrame;
// class IRBlock;
class IRFunc;
class SymbolTable;
typedef shared_ptr<IRFunc> pIRFunc;
// class BlockContext;


class IRObj
{
public:
    string name; 
    SymbolTable* scopeSymbols=nullptr;
    // for val/arr: ident | .t + index in CFG_val
    // for CFG: function name ident
    // for BB: entry: == func name else:.func name + .M/.B/.L + index in CFG_master/branch/loop
    
    bool isIdent;
    IRObj() {}
    IRObj(bool isIndent, string name): isIdent(isIndent), name(name){
    }
    virtual void print(ostream& os) const;
    friend ostream& operator <<(ostream& os, const IRObj& val){
        val.print(os);
        return os;
    }
    
};
typedef shared_ptr<IRObj> pIRObj;

class IRValObj : public IRObj
{
    static int tmpValId;
public:
    bool isConst;
    bool isTmp;
    int offset;
    shared_ptr<IRArrValObj> fa;
    // u-d <lv 3> **add within ssa rename**
    bool ssaDef=false;
    pSysYIR defStruction;// for no-ssa val=>nullptr; common=>pIR
    set<pSysYIR> useStructions; //... common=>pIR; branch=>pBlock.branchIR;
    vReg regInfo;

    IRValObj() {}
    IRValObj(bool isConst, bool isIdent, string name) : IRObj(isIdent, name.empty()? getDefaultName(): name),isTmp(name.empty()),
    fa(nullptr), isConst(isConst){
    }
    IRValObj(const shared_ptr<IRArrValObj>& arrParent, string name): IRObj(true, name.empty()? getDefaultName(): name),isTmp(name.empty()),
        fa(arrParent),isConst(((IRValObj*)arrParent.get())->isConst){
    }
    //note: for const indent return true
    inline bool isConstant(){
        return isConst&&(fa==nullptr);
    }
    virtual void print(ostream& os) const override;
    virtual string getDefaultName() {
        return "%t" + to_string(++tmpValId);
    }
};
typedef shared_ptr<IRValObj> pIRValObj;


class IRArrValObj : public IRValObj
{
public:
    map<int, shared_ptr<IRScalValObj>  >value;
    vector<int> dims; // int[2][3] => vector(2, 3)
    int size;
    IRArrValObj(bool isConst, vector<int> dims, string name) : IRValObj(isConst, true, name), dims(dims)
    {
        size = 1;
        for (auto d : dims)
        {
            size *= d;
        }
        value = map<int, shared_ptr<IRScalValObj> >();
    }
    IRArrValObj(const shared_ptr<IRArrValObj>& arrParent, vector<int> dims, string name): IRValObj(arrParent, name){
        size = 1;
        for (auto d : dims)
        {
            size *= d;
        }
    }
    virtual void print(ostream& os) const override;
};
typedef shared_ptr<IRArrValObj> pIRArrValObj;

class IRScalValObj : public IRValObj
{
public:
    // <lv 4> const folding
    int constState;
    int value;
    IRScalValObj() {}
    IRScalValObj(int value): value(value), IRValObj(true, false, to_string(value)), constState(IR_CONST){
    }
    IRScalValObj(bool isConst, string name) : value(0), IRValObj(isConst, true, name), constState(IR_NAC){
    }
    IRScalValObj(const shared_ptr<IRArrValObj>& arrParent, string name): IRValObj(arrParent, name), constState(IR_NAC){}
    virtual void print(ostream& os) const override;
};

inline pIRScalValObj toScal(pIRObj obj){
    return dynamic_pointer_cast<IRScalValObj>(obj);
}

class IRStrValObj : public IRValObj
{
    static int constStrId;
public:
    string value;
    IRStrValObj() {}
    IRStrValObj(string value, string name) : value(value), IRValObj(true, false, name)
    {}
    virtual void print(ostream& os) const override;
    virtual string getDefaultName() {
        return ".s" + to_string(++constStrId);
    }
};
typedef shared_ptr<IRStrValObj> pIRStrValObj;

#define IR_TO_STRING(x) \
    ENUMCASE_TO_STRING(x, 8)

enum class IRType : int
{
    NOP, ASSIGN,
    ADD, SUB, MUL, DIV, MOD, NEG,
    NOT, EQ, NEQ, GT, LT, GE, LE,
    ARR, IDX,
    CALL, PARAM, RET, BR,
    DEF, PHI,
};
static map<string, IRType> opfinder[2]={
    {
        {"+", IRType::ASSIGN},
        {"-", IRType::NEG},
        {"!", IRType::NOT}
    },
    {
        {"+", IRType::ADD},
        {"-", IRType::SUB},
        {"*", IRType::MUL},
        {"/", IRType::DIV},
        {"%", IRType::MOD},
        {"==", IRType::EQ},
        {"!=", IRType::NEQ},
        {"<", IRType::LT},
        {">", IRType::GT},
        {"<=", IRType::LE},
        {">=", IRType::GE}
    }
};
static string IRTypeName(IRType type)
{
    switch (type)
    {
        IR_TO_STRING(IRType::ASSIGN)
        IR_TO_STRING(IRType::ADD)
        IR_TO_STRING(IRType::SUB)
        IR_TO_STRING(IRType::MUL)
        IR_TO_STRING(IRType::DIV)
        IR_TO_STRING(IRType::MOD)
        IR_TO_STRING(IRType::NEG)
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

class SysYIR: public IRObj
{
public:
    bool removedMask=false;
    IRType type;
    pIRValObj target;
    pIRObj opt1;
    pIRObj opt2;
    shared_ptr<SysYIR> prev=nullptr;
    shared_ptr<SysYIR> next=nullptr;
    pBlock block=nullptr;
    bool asmRemovedMask=false;
    vector<ASMInstr> asmInstrs;
    SysYIR(IRType type, pIRValObj t, pIRObj op1, pIRObj op2)
        : type(type), target(t), opt1(op1), opt2(op2) {}
    virtual void print(ostream& os) const override;
    void remove(){
        if(prev){
            prev->next = next;
        }
        if(next){
            next->prev = prev;
        }
        removedMask = true;
    }
};

int CalConstExp(IRType type, int exp1Val, int exp2Val=0);

class IRBlock : public IRObj
{ //Basic Block
    
    static int masterId;
    static int loopId;
    static int branchId;
public:
    // basic & CFG <lv 0>
    deque<shared_ptr<SysYIR> > structions;
    int blockType; // 0 normal 1 branch 2 loop
    shared_ptr<SysYIR> branchIR;
    pIRScalValObj branchVal = nullptr;
    pBlock nextNormal = nullptr;
    pBlock nextBranch = nullptr;
    set<pBlock> from;
    pIRFunc function;
    // dom <lv 1>
    set<pBlock> domChild;
    set<pBlock> domFrontier;
    pBlock domFa;
    // live interval <lv 2>
    set<pIRValObj> defObj;  // 当前block内定义的值,包括phi指令定义的
    set<pIRValObj> useObj;  // 当前block内用到的,但定值点在前面block的值(不含phi指令用到的(因phi的use与前驱相关))
    set<pIRValObj> liveIn;  // 当前block开头处活跃的值(当前块或后面块用到但是定值点在前面block)不包含phi指令用到的
    set<pIRValObj> liveOut; // 当前block结尾处活跃的值(对后面有用,包含phi指令用到的)
    // SSA <lv3>
    map<pIRValObj, map<pBlock, pIRValObj> > phiList; // x(k) => [ fromBlock => x(i)]

    IRBlock(int blockType, string name=""):IRObj(IR_VOID, name.empty()? getDefaultName(blockType):name), 
        blockType(blockType){}
    shared_ptr<SysYIR> insertIRBack(IRType type, pIRValObj t, pIRObj op1, pIRObj op2)
    {
        auto newIR = make_shared<SysYIR>(type, t, op1, op2);
        if(structions.size()){
            newIR->prev = structions.back();
            structions.back()->next = newIR;
        }
        structions.push_back(newIR);
        if(branchIR != nullptr){
            newIR->next = branchIR;
            branchIR->prev = newIR;
        }
        return newIR;
    }

    shared_ptr<SysYIR> insertIRFront(IRType type, pIRValObj t, pIRObj op1, pIRObj op2){
        auto newIR = make_shared<SysYIR>(type, t, op1, op2);
        if(structions.size()){
            structions.front()->prev = newIR;
            newIR->next = structions.front();
        }
        structions.push_front(newIR);
        return newIR;
    }

    bool finishBB(pBlock next_normal, pBlock next_branch=nullptr, pIRScalValObj branch_val=nullptr) {
        if(nextNormal != nullptr)return false;
        nextNormal = next_normal; 
        nextBranch = next_branch;
        branchVal = branch_val;
        branchIR = make_shared<SysYIR>(IRType::BR, nullptr, branchVal, nullptr);
        if(structions.size()){
            branchIR->prev = structions.back();
            structions.back()->next = branchIR;
        }
        return true;
    }
    // is block empty (all structions removed)
    inline int size(){
        int removedCnt = 0;
        for(auto& ir: structions){
            if(ir->removedMask){
                removedCnt++;
            }
        }
        return structions.size() - removedCnt;
    }

    bool hasPhi(){
        for(auto ir: structions){
            if(ir->type == IRType::PHI){
                return true;
            }else break;
        }
        return false;
    }
    // bool dominate(pBlock block, bool strict=true){
    //     if(block && strict){
    //         block = block->domFa;
    //     }
    //     while(block){
    //         if(block.get() == this)return true;
    //         block = block->domFa;
    //     }
    //     return false;
    // }

    virtual void print(ostream& os) const override;

    virtual string getDefaultName(int type) {
        switch (type)
        {
        case IR_LOOP:
            return "L" + to_string(++loopId);
        case IR_BRANCH:
            return "B" + to_string(++branchId);
        default:
            return "M" + to_string(++masterId);
        }
    }
};
// False, True
typedef pair<pBlock, pBlock> pCondBlocks;


class SymbolTable
{
public:
    bool isGlobal=false;
    map<string, pIRObj> symbols = {};
    SymbolTable() = default;
    SymbolTable(const SymbolTable& table): isGlobal(false){
        symbols = table.symbols;
    }
    ~SymbolTable() = default;
    void registerSymbol(const pIRObj& obj) {
        symbols.insert({obj.get()->name, obj});
    }
    pIRObj findSymbol(string name) {
        if(symbols.empty())return nullptr;
        try{
            return symbols.at(name);
        }catch(...){
            return nullptr;
        }
    }
};

class IRFunc: public IRObj
{
    
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

    SymbolTable* symbolTable;
    // table == nullptr : lib function
    IRFunc(int returnType, string name, vector<pIRValObj> params, SymbolTable* table):
        IRObj(true, name), returnType(returnType), symbolTable(table), params(params) {
        if(symbolTable != nullptr){
            for(auto& arg: this->params) {
                symbolTable->registerSymbol(arg);
                arg->scopeSymbols = symbolTable;
            }
        }
    }
    ~IRFunc() = default;
    
    virtual void print(ostream& os) const override;
};
