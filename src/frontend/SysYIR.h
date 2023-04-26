#pragma once

#include <string>
#include <vector>
#include <memory>

using namespace std;
//    4          3         2          1    0
//is_func/BB  is_const  is_ident    val/ret_type
#define IR_VOID 0
#define IR_INT 1
#define IR_FLOAT 2

#define IRVAL_VAR_IDENT 4
#define IRVAL_CONSTANT 8
#define IRVAl_CONST_IDENT 12

#define IRVAL_MASK_CONST 8
#define IRVAL_MASK_IDENT 4
struct IRObj {
    string name; // empty string imply tmp value
    int attr;
    union {
        float float_value;
        int int_value;
    }value;
};

enum class IRType : int {
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
    IFN = 18,
    BR = 19,
    JMP = 20,
    CALL = 21,
};

class SysYIR{

public:
    IRType type;
    shared_ptr<IRObj> target;
    shared_ptr<IRObj> opt1;
    shared_ptr<IRObj> opt2;
};
struct IRBlock { //从语义上说应该是BB,但是对于{}的作用域，他的范围是比BB要小的，这里的定义是作用域的最小单位，同时需要满足BB的性质
    IRBlock *from;
    IRBlock *next;
};

class SymbolTable {
    public:
        vector<shared_ptr<IRObj> > symbol_stack; 
        SymbolTable();
        ~SymbolTable();
        shared_ptr<IRObj> findSymbol(string name);
};
