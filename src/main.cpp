#include "antlr4-runtime.h"
#include "frontend/SysYLexer.h"
#include "frontend/SysYParser.h"
#include "iostream"

using namespace antlr4;
using namespace std;

int main(int argc, char** argv) {
    string input_buf;
    stringstream input_file;
    fstream fin;
    if(argc > 1){
        fin.open(argv[1]);
        while(fin >> input_buf) {
            input_file << input_buf;
        }
        fin.close();
    }else {
        while(cin >> input_buf) {
            input_file << input_buf;
        }
    }
    cout << "input:" << input_file.str();
    ANTLRInputStream input(input_file);
    SysYLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    SysYParser parser(&tokens);
    tree::ParseTree *tree = parser.prog();

    auto s = tree->toStringTree(&parser);
    std::cout << "Parse Tree: " << s << std::endl;

    return 0;
}