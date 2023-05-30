#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

#define IR_VOID 0
#define IR_INT 1
#define IR_FLOAT 2

#define IR_NORMAL 0
#define IR_BRANCH 1
#define IR_LOOP 2
// #define VAL_IR 1
// class IRObj;
// class IRValObj;
class IRScalValObj;
typedef shared_ptr<IRScalValObj> pIRScalValObj;
class IRArrValObj;
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
    IRValObj() {}
    IRValObj(bool isConst, bool isIdent, string name) : IRObj(isIdent, name.empty()? getDefaultName(): name),isTmp(name.empty()),
    fa(nullptr), isConst(isConst){
    }
    IRValObj(const shared_ptr<IRArrValObj>& arrParent, string name): fa(arrParent), 
        IRObj(true, name.empty()? getDefaultName(): name), isConst(((IRValObj*)arrParent.get())->isConst){
    }
    inline bool isConstant(){
        return isConst&&(fa==nullptr);
    }
    virtual void print(ostream& os) const override;
    virtual string getDefaultName() {
        return ".t" + to_string(++tmpValId);
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
    IRArrValObj(const shared_ptr<IRArrValObj>& arrParent, vector<int> dims, string name){
        IRValObj(arrParent, name);
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
    // int type;
    int value;
    IRScalValObj() {}
    IRScalValObj(int value): value(value), IRValObj(true, false, to_string(value)){
    }
    IRScalValObj(bool isConst, string name) : value(0), IRValObj(isConst, true, name){
    }
    IRScalValObj(const shared_ptr<IRArrValObj>& arrParent, string name): IRValObj(arrParent, name){}
    virtual void print(ostream& os) const override;
};

class IRStrValObj : public IRValObj
{
    static int constStrId;
public:
    string value;
    IRStrValObj() {}
    IRStrValObj(string value, string name) : value(value), IRValObj(true, false, name)
    {
        fa = nullptr;
    }
    virtual void print(ostream& os) const override;
    virtual string getDefaultName() {
        return ".s" + to_string(++constStrId);
    }
};
typedef shared_ptr<IRStrValObj> pIRStrValObj;

#define ENUM_TO_STRING(x) \
    case x:               \
        return #x + 8;
enum class IRType : int
{
    NOP = 0,
    ASSIGN = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    MOD = 6,
    NEG = 7,
    NOT = 8,
    EQ = 9,
    NEQ = 10,
    GT = 11,
    LT = 12,
    GE = 13,
    LE = 14,
    ARR = 15,
    IDX = 16,
    CALL = 17,
    PARAM = 18,
    RET = 19,
    DEF = 20
};
static map<string, IRType> opfinder[2]={
    {
        {"+", IRType::NOP},
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
        ENUM_TO_STRING(IRType::ASSIGN)
        ENUM_TO_STRING(IRType::ADD)
        ENUM_TO_STRING(IRType::SUB)
        ENUM_TO_STRING(IRType::MUL)
        ENUM_TO_STRING(IRType::DIV)
        ENUM_TO_STRING(IRType::MOD)
        ENUM_TO_STRING(IRType::NEG)
        ENUM_TO_STRING(IRType::NOT)
        ENUM_TO_STRING(IRType::EQ)
        ENUM_TO_STRING(IRType::NEQ)
        ENUM_TO_STRING(IRType::GT)
        ENUM_TO_STRING(IRType::LT)
        ENUM_TO_STRING(IRType::GE)
        ENUM_TO_STRING(IRType::LE)
        ENUM_TO_STRING(IRType::ARR)
        ENUM_TO_STRING(IRType::IDX)
        ENUM_TO_STRING(IRType::CALL)
        ENUM_TO_STRING(IRType::PARAM)
        ENUM_TO_STRING(IRType::RET)
        ENUM_TO_STRING(IRType::DEF)
    default:
        return "unknown";
    }
}

class SysYIR: public IRObj
{
public:
    IRType type;
    pIRObj target;
    pIRObj opt1;
    pIRObj opt2;
    SysYIR(IRType type, pIRObj t, pIRObj op1, pIRObj op2)
        : type(type), target(t), opt1(op1), opt2(op2) {}
    virtual void print(ostream& os) const override;
};

class IRBlock;
typedef shared_ptr<IRBlock> pBlock;
class IRBlock : public IRObj
{ //Basic Block
    
    static int masterId;
    static int loopId;
    static int branchId;
public:
    vector<pBlock> from;
    vector<unique_ptr<SysYIR> > structions;
    vector<pBlock> domChild;
    vector<pBlock> domFrontier;
    pBlock domFa;
    vector<pIRValObj> defObj;
    vector<pIRValObj> useObj;
    map<pIRValObj, vector<pBlock> > phiFa;
    map<pIRValObj, vector<pIRValObj> > phiList;
    pBlock nextNormal = nullptr;
    pBlock nextBranch = nullptr;
    pIRScalValObj branchVal = nullptr;
    int blockType; // 0 normal 1 branch 2 loop

    IRBlock(int blockType, string name=""):IRObj(IR_VOID, name.empty()? getDefaultName(blockType):name), 
        blockType(blockType){}
    void insertIR(IRType type, pIRObj t, pIRObj op1, pIRObj op2)
    {
        structions.push_back(make_unique<SysYIR>(type, t, op1, op2));
    }
    bool finishBB(pBlock next_normal, pBlock next_branch=nullptr, pIRScalValObj branch_val=nullptr) {
        if(nextNormal != nullptr)return false;
        nextNormal = next_normal; 
        nextBranch = next_branch;
        branchVal = branch_val;
        return true;
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
    map<string, pIRObj> symbols = {};
    SymbolTable() = default;
    SymbolTable(const SymbolTable& table){
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
    vector<pBlock> blocks;
    pBlock entry;
    pBlock exit;
    SymbolTable* symbolTable;
    int returnType;
    pIRValObj returnVal;
    // table == nullptr : lib function
    IRFunc(int returnType, string name, vector<pIRValObj> params, SymbolTable* table):
        IRObj(true, name), returnType(returnType), symbolTable(table), params(params) {
        if(symbolTable != nullptr){
            for(auto arg: this->params) {
                symbolTable->registerSymbol(arg);
            }
        }
    }
    ~IRFunc() = default;
    
    virtual void print(ostream& os) const override;
};
