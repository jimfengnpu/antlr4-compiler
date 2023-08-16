# SysY Compiler Via Antlr4
### Author
jimfengnpu@qq.com
## Introduction
SysY: subSet of C (no for, goto, struct, no operators like: ++,--, ^, &, etc.)
detailed feature:
+ constant: int(dec/oct/hex)
+ statement: empty;regular;if/if-else;while[break;continue];return;
+ 
## Developement Notes

+ Frontend: antlr4.12.0 (visitor)
+ IR: customized linear
+ Optimization procedure:
    - SSA
    - Constant Folding
    - Code Clean
    - ...(Iteration until not change)
```
ADD y, x(0), 0(x) => ASSIGN y, x
SUB y, x, 0 => ASSIGN y, x
MUL y, x(1), 1(x) => ASSIGN y, x
DIV y, x, 1 => ASSIGN y, x
MUL z, x, 2**y(+imm) => SL z, x, y
DIV z, x, 2**y(+imm) => {...}
```
+ Backend
    - Instr matcher:
format: ir... => asm{op(condition)\<side effect\>}...(多个汇编)
注：
    1. 
```
//risc-v:
NOP, 
ASSIGN, => mv
ADD, => addi((op1|op2)=imm); add;
SUB, => addi(op2=imm)<imm=-imm>; sub; 
MUL, => mul;
DIV, => div;
MOD, => rem;
NEG, => neg;
AND, => andi((op1|op2)=imm); and;
OR, => ori((op1|op2)=imm); or;
SL, => slli(op2=imm); sll;
SR, => srai(op2=imm); sra;
NOT,BR => beqz;
EQ, BR => beq; beqz(op1|op2=0);
NEQ, BR => bne; bnez(op1|op2=0);
GT, BR => bgt; bgtz(op2=0); bltz(op1=0);
LT, BR => blt; bltz(op2=0); blez(op1=0);
LE, BR => ble; blez(op2=0); bgez(op1=0);
ARR, => add
IDX, => ; add
CALL, => call
PARAM, .skip
RET, .skip
DEF, .skip
PHI, .skip

//about vReg:
IRValObj 的成员变量，指示数据存放位置的类型和信息，对于ArrObj，其数据为数组的起始地址，ScalObj为数据值
REG_R: 数据通常放置在寄存器中
REG_M: 数据通常放置在内存中
REG_IMM:立即数
```