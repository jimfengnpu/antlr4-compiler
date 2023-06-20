# SysY Compiler With Antlr4
### Author
jimfengnpu@qq.com
## Introduction
SysY: subSet of C (no for, goto, struct, no operators like: ++,--, ^, &, etc.)
## Develop Notes

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
MUL z, x, -2**y(+imm) => MUL t, x, 2**y; NEG z, t
DIV z, x, -2**y(+imm) => DIV t, x, 2**y; NEG z, t
MOD z, x, -2**y(+imm) => MOD t, x, 2**y; NEG z, t
GT y, imm(0), x => LT y, x, imm(0)
LT y, imm(0), x => GT y, x, imm(0)
GE y, imm(0), x => LE y, x, imm(0)
LE y, imm(0), x => GE y, x, imm(0)
```
+ Backend
    - Instr matcher:
```
//risc-v ir=>asm
NOP, 
ASSIGN, => mv
ADD, => addi((op1|op2)=imm); add;
SUB, => addi(op2=imm, imm:v=>-v); sub; 
MUL, => mul;
DIV, => div;
MOD, => rem;
NEG, => neg;
AND, => andi((op1|op2)=imm); and;
OR, => ori((op1|op2)=imm); or;
SL, => slli(op2=imm); sll;
SR, => srai(op2=imm); sra;
NOT,BR => beqz;
EQ, BR => beq; beqz(op1|op2=imm(0));
NEQ, BR => bne; bnez(op1|op2=imm(0));
GT, BR => bgt; bgtz[op2=imm(0)];
LT, BR => blt; bltz[op2=imm(0)];
GE, BR => bge; bgez[op2=imm(0)];
LE, BR => ble; blez[op2=imm(0)];
ARR, => add
IDX, => add 
CALL, => call
PARAM, .skip
RET, .skip
DEF, .skip
PHI, .skip
```