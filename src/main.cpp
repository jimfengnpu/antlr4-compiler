#include "antlr4-runtime.h"
#include "frontend/SysYLexer.h"
#include "frontend/SysYParser.h"

using namespace antlr4;

int main() {
    ANTLRInputStream input("a = b + \"c\";(((x * d))) * e + f; a + (x * (y ? 0 : 1) + z);");
    SysYLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    SysYParser parser(&tokens);
    tree::ParseTree *tree = parser.prog();

    auto s = tree->toStringTree(&parser);
    std::cout << "Parse Tree: " << s << std::endl;

    return 0;
}