#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>

using namespace std;

#define IR_VOID 0
#define IR_INT 1
#define IR_FLOAT 2

#define IR_NORMAL 0
#define IR_BRANCH 1
#define IR_LOOP 2
// class IRObj;
// class IRIntObj;
class IRIntValObj;
// class IRIntArrObj;

// class IRBlock;
// // class IRFunc;
// class BlockContext;


class IRObj
{
public:
    string name; 
    // for val/arr: ident | .t + index in CFG_val
    // for CFG: function name ident
    // for BB: entry: == func name else:.func name + .M/.B/.L + index in CFG_master/branch/loop
    
    bool isIdent;
    IRObj() {}
    IRObj( bool isIndent, string name): isIdent(isIndent), name(name){}
    virtual void print(ostream& os) const;
    friend ostream& operator <<(ostream& os, const IRObj& val){
        val.print(os);
        return os;
    }
    
};
typedef shared_ptr<IRObj> pIRObj;

class IRIntObj : public IRObj
{
public:
    bool isConst;
    IRIntObj() {}
    IRIntObj(bool isConst, string name) : 
        isConst(isConst), IRObj(!name.empty(), name){}
    virtual void print(ostream& os) const override{};
};
typedef shared_ptr<IRIntObj> pIRIntObj;


class IRIntArrObj : public IRIntObj
{
public:
    map<int, shared_ptr<IRIntValObj>  >value;
    vector<int> dims; // int[2][3] => vector(2, 3)
    int size;
    IRIntArrObj(bool isConst, vector<int> dims, string name) : IRIntObj(isConst, name), dims(dims)
    {
        size = 1;
        for (auto d : dims)
        {
            size *= d;
        }
        value = map<int, shared_ptr<IRIntValObj> >();
    }
    virtual void print(ostream& os) const override;
};
typedef shared_ptr<IRIntArrObj> pIRIntArrObj;

class IRIntValObj : public IRIntObj
{
public:
    int value;
    shared_ptr<IRIntArrObj> fa;
    int offset;
    IRIntValObj() {}
    IRIntValObj(bool isConst, int value, string name) : value(value), IRIntObj(isConst, name)
    {
        fa = nullptr;
    }
    IRIntValObj(shared_ptr<IRIntArrObj> arrParent, int offset, string name) : 
        fa(arrParent), offset(offset){
            IRIntObj((fa.get())->isConst , "");
        }
    virtual void print(ostream& os) const override;
};
typedef shared_ptr<IRIntValObj> pIRIntValObj;

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
    AND = 9,
    OR = 10,
    EQ = 11,
    NEQ = 12,
    GT = 13,
    LT = 14,
    GE = 15,
    LE = 16,
    ARR = 17,
    CALL = 18,
    PARAM = 19
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
        {"%", IRType::MOD}
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
        ENUM_TO_STRING(IRType::AND)
        ENUM_TO_STRING(IRType::OR)
        ENUM_TO_STRING(IRType::EQ)
        ENUM_TO_STRING(IRType::NEQ)
        ENUM_TO_STRING(IRType::GT)
        ENUM_TO_STRING(IRType::LT)
        ENUM_TO_STRING(IRType::GE)
        ENUM_TO_STRING(IRType::LE)
        ENUM_TO_STRING(IRType::ARR)
        ENUM_TO_STRING(IRType::CALL)
        ENUM_TO_STRING(IRType::PARAM)
    default:
        return "unknown";
    }
}

class SysYIR: public IRObj
{
    IRType type;
    pIRObj target;
    pIRObj opt1;
    pIRObj opt2;
public:
    SysYIR(IRType type, pIRObj t, pIRObj op1, pIRObj op2)
        : type(type), target(t), opt1(op1), opt2(op2) {}
    virtual void print(ostream& os) const override;
};

class IRBlock;
typedef shared_ptr<IRBlock> pBlock;
class IRBlock : public IRObj
{ //Basic Block
    vector<pBlock> from;
    vector<unique_ptr<SysYIR> > structions;
    pBlock nextNormal;
    pBlock nextBranch;
    pIRIntValObj branchVal;
public:
    int blockType; // 0 normal 1 branch 2 loop

    IRBlock(int blockType, string name="", int type = IR_VOID):IRObj(type, name), blockType(blockType)
    {}
    void insertIR(IRType type, pIRObj t, pIRObj op1, pIRObj op2)
    {
        structions.push_back(make_unique<SysYIR>(type, t, op1, op2));
    }
    void finishBB(pBlock next_normal, pBlock next_branch=nullptr, pIRIntValObj branch_val=nullptr) {
        nextNormal = next_normal;
        nextBranch = next_branch;
        branchVal = branch_val;
    }
    virtual void print(ostream& os) const override;
};
typedef pair<pBlock, pBlock> pCondBlocks;


class SymbolTable
{
    map<string, pIRObj> symbols;
public:
    SymbolTable() = default;
    SymbolTable(const SymbolTable& table){
        symbols = table.symbols;
    }
    ~SymbolTable() = default;
    void registerSymbol(pIRObj obj) {
        symbols.insert({obj.get()->name, obj});
    }
    pIRObj findSymbol(string name) {
        return symbols[name];
    }
};

class IRFunc: public IRObj
{
    int tmpValId = 0;
    int masterId = 0;
    int loopId = 0;
    int branchId = 0;
public:
    vector<pIRIntObj> params;
    vector<pBlock> blocks;
    SymbolTable* symbolTable;
    int returnType;
    pIRIntObj returnVal;
    IRFunc(int returnType, string name, vector<pIRIntObj> params, SymbolTable* table):
        IRObj(true, name), returnType(returnType), symbolTable(table), params(params) {
            for(auto arg: this->params) {
                symbolTable->registerSymbol(arg);
            }
    }
    ~IRFunc() = default;
    string getDefaultName(pIRIntObj obj) {
        return ".t" + to_string(++tmpValId);
    }
    string getDefaultName(pBlock obj) {
        switch (obj.get()->blockType)
        {
        case IR_LOOP:
            return ".L" + to_string(++loopId);
        case IR_BRANCH:
            return ".B" + to_string(++branchId);
        default:
            return ".M" + to_string(++masterId);
        }
    }
};
typedef unique_ptr<IRFunc> pIRFunc;
