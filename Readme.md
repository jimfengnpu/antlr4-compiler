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
+ Backend
