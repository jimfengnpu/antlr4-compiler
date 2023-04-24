#include "antlr4-runtime.h"
#include "frontend/generated/SysYLexer.h"
#include "frontend/generated/SysYParser.h"
#include "frontend/ASTVisitor.h"
#include "iostream"

using namespace antlr4;
using namespace std;

int main(int argc, char** argv) {
    string input_file;
    if(argc > 1){
        ifstream fin(argv[1]);
        fin.unsetf(ios::skipws);
        input_file = string((istreambuf_iterator<char>(fin)),istreambuf_iterator<char>());
        fin.close();
    }else {
        cout << "no input file"<< endl;
        return -1;
    }
    cout << "input:" << endl << input_file;
    ANTLRInputStream input(input_file);
    SysYLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    
    SysYParser parser(&tokens);
    tree::ParseTree* tree = parser.compUnit();
    auto s = tree->toStringTree(&parser);
    std::cout << "Original Parse Tree: " << s << std::endl;
    // tree = BuildAST(tree);
    // s = tree->toStringTree(&parser, true);
    // std::cout << "Parse Tree: " << s << std::endl;

    return 0;
}