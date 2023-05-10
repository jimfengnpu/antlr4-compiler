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

struct IRBlock;
typedef shared_ptr<IRBlock> pBlock;
typedef std::pair<pBlock, pBlock> pCondBlocks;
class IRIntArrObj;
typedef shared_ptr<IRIntArrObj> pIRIntArrObj;
class IRObj
{
public:
    string name; // for BB => func name
    int val_type;
    bool is_ident;
    bool is_val;
    static int tmp_id;
    static int tmp_block_id;
    IRObj() {}
    IRObj(bool is_val, int val_type, string name)
    {
        this->val_type = val_type;
        this->is_val = is_val;
        this->is_ident = !(name.empty());
        if (is_ident)
        {
            this->name = name;
        }
        else
        {
            if (is_val)
            {
                this->name = string(".t").append(to_string(++tmp_id));
            }
            else
                this->name = string(".L").append(to_string(++tmp_block_id));
        }
    }
    virtual void print(ostream& os) const;
    friend ostream& operator <<(ostream& os, const IRObj& val){
        val.print(os);
        return os;
    }
};

class IRIntObj : public IRObj
{
public:
    bool is_const;
    IRIntObj()
    {
        is_val = true;
        val_type = IR_INT;
    }
    IRIntObj(bool is_const, string name) : is_const(is_const), IRObj(true, IR_INT, name){
    }
    virtual void print(ostream& os) const override{};
};

class IRIntValObj : public IRIntObj
{
public:
    int value;
    pIRIntArrObj fa;
    int offset;
    IRIntValObj() {}
    IRIntValObj(bool is_const, int value, string name = string("")) : value(value), IRIntObj(is_const, name)
    {
        fa = nullptr;
    }
    IRIntValObj(pIRIntArrObj arr, int offset) : IRIntObj(), fa(arr), offset(offset)
    {
    }
    virtual void print(ostream& os) const override;
};
typedef shared_ptr<IRIntObj> pIRIntObj;
typedef shared_ptr<IRIntValObj> pIRIntValObj;

class IRIntArrObj : public IRIntObj
{
public:
    map<int, pIRIntValObj> value;
    vector<int> dims; // int[2][3] => vector(2, 3)
    int size;
    IRIntArrObj(bool is_const, vector<int> dims, string name = string("")) : IRIntObj(is_const, name), dims(dims)
    {
        size = 1;
        for (auto d : dims)
        {
            size *= d;
        }
        value = map<int, pIRIntValObj>();
    }
    virtual void print(ostream& os) const override;
};

typedef shared_ptr<IRObj> pIRObj;
#define ENUM_TO_STRING(x) \
    case x:               \
        return #x + 8;
enum class IRType : int
{
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
    IFT = 17,
    JMP = 18,
    CALL = 19,
    PUSH = 20,
    IDX = 21,
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
        ENUM_TO_STRING(IRType::IFT)
        ENUM_TO_STRING(IRType::JMP)
        ENUM_TO_STRING(IRType::CALL)
        ENUM_TO_STRING(IRType::PUSH)
    default:
        return "unknown";
    }
}

class SysYIR:public IRObj
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

class SymbolTable
{
public:
    vector<pIRObj> symbol_stack;
    SymbolTable() = default;
    ~SymbolTable() = default;
    pIRObj findSymbol(string name);
};

class IRBlock : public IRObj
{ // 从语义上说应该是BB,但是对于{}的作用域，他的范围是比BB要小的，这里的定义是作用域的最小单位，同时需要满足BB的性质
public:
    pBlock from;
    vector<unique_ptr<SysYIR>> structions;
    pBlock next;
    IRBlock(string name, int type = IR_VOID) : IRObj(false, type, name)
    {
    }
    void insertIR(IRType type, pIRObj t, pIRObj op1, pIRObj op2)
    {
        structions.push_back(make_unique<SysYIR>(type, t, op1, op2));
    }
    virtual void print(ostream& os) const override;
};