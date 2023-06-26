#include <fstream>
#include <iostream>

#include "ASTVisitor.h"
#include "AsmEmit.h"
#include "Dom.h"
#include "IRProcessor.h"
#include "IRRunner.h"
#include "InstrMatcher.h"
#include "Optimizer.h"
#include "RegAlloc.h"
#include "SSA.h"
#include "SysYLexer.h"
#include "SysYParser.h"
#include "antlr4-runtime.h"

using namespace antlr4;
using namespace std;

int main(int argc, char** argv) {
    // load args
    string src = "", out = "out.s";
    bool outOption = false;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0)
            outOption = true;
        else {
            if (outOption) {
                out = string(argv[i]);
                outOption = false;
            } else {
                src = string(argv[i]);
            }
        }
    }
    // open src input file
    string input_file;
    if (!src.empty()) {
        try {
            ifstream fin(src);
            fin.unsetf(ios::skipws);
            input_file = string((istreambuf_iterator<char>(fin)),
                                istreambuf_iterator<char>());
            fin.close();
        } catch (...) {
            throw RuntimeException("open file failed");
        }
    } else {
        throw RuntimeException("fatal: no input file");
    }
    // antlr4 lexer and parser
    ANTLRInputStream input(input_file);
    SysYLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    SysYParser parser(&tokens);
    auto tree = parser.compUnit();
    // CST finished

    Prog prog;  // main program content
    ASTVisitor visitor;
    prog.globalData = make_shared<IRBlock>(IR_NORMAL, ".global");
    visitor.globalData = prog.globalData;
    visitor.functions = &prog.functions;
    visitor.globalSymbolTable = &prog.globalSymbolTable;
    bool exist_main = any_cast<bool>(visitor.visit(tree));
    if (!exist_main) {
        throw RuntimeException("no main function found!");
    }
    prog.mainFunc = toFunc(visitor.findSymbol("main"));

    // process models ,`apply` will execute all the processors added in the
    // queue including triggers during execution
    IRProcessors processors(prog);
    RISCV riscv_arch;

    // model list:
    // DomMaker: generate dom tree in pBlock, triggers:
    processors.add(new BlockPruner());
    processors.add(new DomMaker());
    processors.add(new SSAMaker());
    processors.add(new ConstBroadcast());  // auto clean
    processors.add(new SSAFinalizer());
#ifdef VAL_RUN  // for emulate
    processors.add(new IRRunner(cin, cout));
#endif
    processors.add(new InstrMatcher(&riscv_arch));
    processors.add(new RegAllocator(&riscv_arch));
    processors.add(new AsmEmitter(out, &riscv_arch, new IRRunner(cin, cout)));
    processors.apply();

    return 0;
}
