#include "antlr4-runtime.h"
#include "SysYLexer.h"
#include "SysYParser.h"
#include "ASTVisitor.h"
#include "IRProcessor.h"
#include "IRRunner.h"
#include "Dom.h"
#include "SSA.h"
#include "Optimizer.h"
#include "InstrMatcher.h"
#include <iostream>
#include <fstream>

using namespace antlr4;
using namespace std;

int main(int argc, char** argv) {
    string src="", out="out.s";
    bool outOption = false;
    for(int i=0; i < argc; i++){
        if(argv[i] == "-o")outOption=true;
        else{
            if(outOption){
                out = string(argv[i]);
                outOption = false;
            }else{
                src = string(argv[i]);
            }
        }
    }
    string input_file;
    if(!src.empty()){
        try{
            ifstream fin(src);
            fin.unsetf(ios::skipws);
            input_file = string((istreambuf_iterator<char>(fin)),istreambuf_iterator<char>());
            fin.close();
        }catch(...){
            cout << "open file failed" << endl;
            return -1;
        }
    }else {
        cout << "no input file"<< endl;
        return -1;
    }
    // cout << "input:" << endl << input_file << endl;
    ANTLRInputStream input(input_file);
    SysYLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    
    SysYParser parser(&tokens);
    auto tree = parser.compUnit();
    auto s = tree->toStringTree(&parser, true);
    // std::cout << "Parse Tree: " << endl << s << std::endl;
    ASTVisitor visitor;
    bool exist_main =  any_cast<bool>(visitor.visit(tree));

    IRProcessors processors(visitor);
    RISCV riscv_arch;
    // model list:
    // DomMaker: generate dom tree in pBlock, triggers: 
    processors.add(new BlockPruner());
    processors.add(new DomMaker());
    processors.add(new SSAMaker());
    processors.add(new ConstBroadcast());// auto clean
    #ifdef VAL_RUN
    processors.add(new SSAFinalizer());
    processors.add(new IRRunner(cin, cout));
    #endif
    processors.add(new InstrMatcher(&riscv_arch));
    processors.apply();
    #ifdef VAL_IR
        cout << "IR:";
        cout << *(visitor.globalData.get());
        for(auto &f : visitor.functions){
            if(f->entry != nullptr){
                cout << endl << *f;
            }
        }
        cout << endl;
    #endif
    // }catch(...){
    //     cout << "open file failed" << endl;
    //     return -1;
    // }
    // return runner.returnVal;
    return 0;
}