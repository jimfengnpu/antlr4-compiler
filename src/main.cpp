#include "antlr4-runtime.h"
#include "frontend/generated/SysYLexer.h"
#include "frontend/generated/SysYParser.h"
#include "frontend/ASTVisitor.h"
#include "common/IRRunner.h"
#include "iostream"
#include "fstream"

using namespace antlr4;
using namespace std;

int main(int argc, char** argv) {
    string input_file;
    if(argc > 1){
        try{
            ifstream fin(argv[1]);
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
    // cout<< ".data"<<endl;
    // for(auto& [name, value]: visitor.globalSymbolTable.symbols) {
    //     if(auto sym = value.get())
    //         cout << *(sym) <<endl;
    // }
    #ifdef VAL_IR
        cout << "IR:"<<endl;
        cout << *(visitor.globalData.get());
        for(auto &f : visitor.functions){
            cout << *f;
        }
    #endif
    // assert(argc >= 3);
    // try{
    //     ofstream& foutput(string(argv[2]));
    //     // tree = BuildAST(tree);
    //     // s = tree->toStringTree(&parser, true);
    //     // std::cout << "Parse Tree: " << s << std::endl;
    //     ifstream finput(argv[3]);
        IRRunner runner(visitor, cin, cout);
        runner.apply();
    // }catch(...){
    //     cout << "open file failed" << endl;
    //     return -1;
    // }
    return 0;
}