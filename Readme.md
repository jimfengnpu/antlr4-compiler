# SysY Compiler Via Antlr4
### Author
jimfengnpu@qq.com
## Introduction
SysY: subSet of C (no for, goto, struct, no operators like: ++,--, ^, &, etc.)
detailed feature:
+ constant: int(dec/oct/hex)
+ statement: empty;regular;if/if-else;while[break;continue];return;
+ function: int/void
+ 多维数组，数组传参，数组初始化列表

Arch: RISC-V 64 遵循RISCV调用约定;并提供后续可能扩展其他架构的接口
## Developement Details

+ Frontend: antlr4.12.0 (visitor)
+ IR: customized linear
+ Optimization procedure:
    - SSA
    - Constant Folding
    - Code Clean(死代码删除)
    - Arithmatical Optimization
    - Common Subexpression(不考虑如x+4+3的树平衡问题)
    - ...(Iteration until not change)
```
ADD y, x(0), 0(x) => ASSIGN y, x
SUB y, x, 0 => ASSIGN y, x
MUL y, x(1), 1(x) => ASSIGN y, x
DIV y, x, 1 => ASSIGN y, x
MUL z, x, 2**y(imm) => SL z, x, y
DIV z, x, 2**y(imm) => {...}
```
+ Instr matcher 指令选择:
format: ir... => asm{op(condition)\<side effect\>};...(多个汇编)
注：
    1. ‘=>’左侧多条ir表示连续的ir序列类型；右侧多条汇编指令规则按照从左到右的顺序，根据对应的括号中的条件匹配
    2. 条件中=imm表示要求为立即数；=0表示要求为立即数0；
    3. ir: op1: 操作数1；op2: 操作数2
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
EQ, BR => beqz(op1|op2=0); beq;
NEQ, BR => bnez(op1|op2=0); bne;
GT, BR => bgtz(op2=0); bltz(op1=0); bgt;
LT, BR => bltz(op2=0); blez(op1=0); blt;
LE, BR => blez(op2=0); bgez(op1=0); ble;
ARR, => add
IDX, => ; add
CALL, => call
PARAM, .skip
RET, .skip
DEF, .skip
PHI, .skip

//about vReg:
IRValObj 的成员变量，指示数据存放位置的类型和信息，对于ArrObj，其数据为数组的起始地址，ScalObj为数据值
REG_R: 数据通常放置在寄存器中,分配寄存器
REG_M: 数据通常放置在内存中,不分配寄存器
REG_IMM:立即数
```

- Reg Allocator
主体方法是自底向上的的全局图着色分配（参考cooper书，有一些自己的启发式操作）
大体思路：
    1. 每个待处理函数先从入口搜索一次，统计每个基本块的频度系数，用于后面计算逐出成本（此处按每层循环*10计算）
    2. 重复3-6步，进行寄存器分配，直到不存在未分配的寄存器类型虚拟寄存器
    3. 根据虚拟寄存器活跃性分析计算并记录需要着色的虚拟寄存器，访问次数以及活跃区间（以机器指令为单位），构建冲突图
    4. 根据图着色原理化简冲突图，并排出着色顺序（预着色的也在其中）
    5. 按照队列顺序依次着色，每次着色按照固定的顺序尝试，如果不是预着色的寄存器，将其加入可能的逐出优先队列，如果预着色的存在冲突，则尝试给其中一个进行活跃区间分割（此种情况完成后重新从第3步开始，详见后面说明）
    6. 尝试着色结束后如有未着色的寄存器，则取优先队列计算得到cost最小的进行逐出，遍历代码进行load/store指令插入，返回第3步（其中cost通过访问次数、活跃区间长度、频度系数、冲突图度数共同决定，详见后面说明）
    7. 完成当前函数寄存器分配，根据用到的寄存器设置函数入口出口的汇编
    8. 由于保存寄存器扩大栈空间，可能存在第7步之后访存偏移量超出限制的情况，所以完成所有函数的寄存器分配之后进行一次检查，对可能的汇编进行改写（方便起见此处改写中新使用的寄存器一律使用t0，同时着色时不使用t0）

    一些启发式操作：
    1. 寄存器活跃区间非常规定义：定义为从定值点的下一条指令开始到最后一次使用点结束，这样可以从原理上解释有些指令可以源寄存器，目的寄存器可以相同的情况
    2. 活跃区间分割：两个预着色的寄存器冲突，如caller的参数与callee的参数冲突，将在callee传参之前和函数调用之后插入两次赋值，将caller寄存器中间的部分保存到另外的寄存器（这样的效果，应该总比溢出访存要好一些吧）
    3. 根据访问次数和活跃性区间长度可以算得溢出之后冲突位置减少的量, 这样可以令逐出之后没有减少活跃区间长度的寄存器成本高
    $ cost = (\sum^{access} blockFreq )/(liveRangeLen+1-AccessCnt+eps)/InferenceMapDegree $
## 附录
+ 开发阶段
2023.4.10 环境搭建、工具使用
2023.4.18 文法工具浅试
4.20--5.20 前端文法及visitor IR
2023.5.23 IR模拟运行通过
2023.5.30 DOM树，DF完成
2023.6.7  SSA完成
6.8 --6.15 优化组件(常量传播/死代码删除)
6.16--6.21 后端指令选择，数据结构优化重构
6.22--7.10 后端寄存器分配
2023.7.13 添加公共子表达式及算术优化
2023.7.17 测例基本通过(103/103;35/37;15/15)
2023.8.12 修完所有bug(测例100%通过(含隐藏测例))
2023.8.15 优化代码结构

+ 主要参考资料
  1. [Antlr4官方文档](https://github.com/antlr/antlr4/blob/master/doc/index.md)
  2. Cooper 书：Engineering A Compiler 2nd Edition
  3. [支配树的Lengauer-Tarjan算法](https://www.cnblogs.com/meowww/p/6475952.html)
  4. RISC-V指令集，手册