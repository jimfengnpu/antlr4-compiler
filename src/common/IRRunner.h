#pragma once
#include "IRProcessor.h"


class DataFrame{
public:
    map<pIRScalValObj, int> value;
};
// typedef shared_ptr<DataFrame> pDataFrame;

class IRRunner: IRProcessor{
public:
    ostream& fout;
    istream& fin;
    pIRFunc curFunc = nullptr;
    vector<pIRValObj> paramsBuf;
    DataFrame globalData;
    std::vector<DataFrame * > dataStack;
    IRRunner()=default;
    IRRunner(ASTVisitor& visitor, istream& fin, ostream& fout): IRProcessor(visitor),
        fin(fin), fout(fout){}
    virtual void apply(){
        run(visitor.globalData);
        runFunc(std::dynamic_pointer_cast<IRFunc>(visitor.findSymbol("@main")));
    }
    pBlock run(pBlock block);
    int runFunc(pIRFunc func);
    void runSysY(const SysYIR& instr);
    int getValue(pIRObj obj);
    void storeValue(pIRScalValObj obj, int val);
    void operateScalObj(IRType type, pIRObj target, pIRObj opt1, pIRObj opt2);
};
