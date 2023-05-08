#pragma once

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
typedef std::pair<pBlock,pBlock> pCondBlocks;

class IRObj {
public:
    string name; //for BB => func name
    int val_type;
    bool is_ident;
    bool is_val;
    static int tmp_id;
    static int tmp_block_id;
    IRObj(bool is_val, int val_type, string name){
        this->val_type = val_type;
        this->is_val = is_val;
        this->is_ident = !(name.empty());
        if(is_ident){
            this->name = name;
        }else {
            if(is_val)
                this->name = string(".t").append(to_string(++tmp_id));
            else
                this->name = string(".L").append(to_string(++tmp_block_id));
        }
    }
    string toString();
};

class IRIntObj: public IRObj{
public:
    bool is_const;
    IRIntObj(bool is_const, string name): 
        IRObj(true, IR_INT, name), is_const(is_const){
    }
};

class IRIntValObj: public IRIntObj{
public:
    int value;
    IRIntValObj(bool is_const, int value, string name=string("")): IRIntObj(is_const, name), value(value){
    }
};

class IRIntArrObj: public IRIntObj{
public:
    map<int, int> value;
    vector<int> dims; // int[2][3] => vector(2, 3)
    IRIntArrObj(bool is_const, vector<int> dims, string name=string("")): IRIntObj(is_const, name), dims(dims){
    }
};

class IRTextObj: public IRObj{
public:
    pBlock target;
    IRTextObj(pBlock target, int type=IR_VOID, string name=string("")): IRObj(false, type, name), target(target){
    }
};

typedef shared_ptr<IRObj> pIRObj;
#define ENUM_TO_STRING(x) case x: return #x + 8;
enum class IRType: int{
        ASSIGN = 1,
        ADD = 2,
        SUB = 3,
        MUL = 4, 
        DIV  = 5,
        REM = 6,
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
        BR = 18,
        JMP = 19,
        CALL = 20,
        PUSH = 21,
};
static string IRTypeName(IRType type) {
        switch (type)
        {
        ENUM_TO_STRING(IRType::ASSIGN)
        ENUM_TO_STRING(IRType::ADD)
        ENUM_TO_STRING(IRType::SUB)
        ENUM_TO_STRING(IRType::MUL)
        ENUM_TO_STRING(IRType::DIV)
        ENUM_TO_STRING(IRType::REM)
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
        ENUM_TO_STRING(IRType::BR)
        ENUM_TO_STRING(IRType::JMP)
        ENUM_TO_STRING(IRType::CALL)
        ENUM_TO_STRING(IRType::PUSH)
        default:            return "unknown";
    }
}

class SysYIR{

public:
    IRType type;
    pIRObj target;
    pIRObj opt1;
    pIRObj opt2;
    SysYIR(IRType type, pIRObj t, pIRObj op1, pIRObj op2)
    : type(type), target(t), opt1(op1), opt2(op2){}
    string toString();
};

class SymbolTable {
    public:
        vector<pIRObj> symbol_stack; 
        SymbolTable() = default;
        ~SymbolTable() = default;
        pIRObj findSymbol(string name);
};

struct IRBlock { //从语义上说应该是BB,但是对于{}的作用域，他的范围是比BB要小的，这里的定义是作用域的最小单位，同时需要满足BB的性质
    pBlock from;
    vector<unique_ptr<SysYIR> > structions;
    pBlock next;
    void insertIR(IRType type, pIRObj t, pIRObj op1, pIRObj op2){
        structions.push_back(make_unique<SysYIR>(type, t, op1, op2));
    }
};