#include "../frontend/ASTVisitor.h"

class IRRunner{
public:
    ostream& fout;
    istream& fin;
    ASTVisitor& visitor;
    IRRunner()=default;
    void run(pBlock block);
    void runSysY(const SysYIR& instr);
};