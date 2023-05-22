#pragma once
#include "IRProcessor.h"


class DataFrame{
public:
    map<pIRValObj, int> frameData;
};
// typedef shared_ptr<DataFrame> pDataFrame;

class IRRunner: IRProcessor{
public:
    ostream& fout;
    istream& fin;
    int returnVal;
    bool needNewLine = false;
    pIRFunc curFunc = nullptr;
    vector<pIRValObj> paramsBuf;
    DataFrame globalData;
    std::vector<DataFrame * > frameStack;
    std::map<int, int> addr2val;
    std::map<int, string> addr2str;
    int addrTop = 0;
    IRRunner()=default;
    IRRunner(ASTVisitor& visitor, istream& fin, ostream& fout): IRProcessor(visitor),
        fin(fin), fout(fout){}
    virtual void apply(){
        run(visitor.globalData);
        auto frame = new DataFrame();
        frameStack.push_back(frame);
        returnVal = runFunc(std::dynamic_pointer_cast<IRFunc>(visitor.findSymbol("@main")));
        frameStack.pop_back();
        delete frame;
        if(needNewLine)fout <<endl;
        fout << (returnVal&0xFF) << endl;
    }
    int callLib(pIRFunc libFunc);
    pBlock run(pBlock block);
    int runFunc(pIRFunc func);
    void runSysY(const SysYIR& instr);
    void operateScalObj(IRType type, pIRObj target, pIRObj opt1, pIRObj opt2);
    int getValue(pIRObj obj);
    void storeValue(pIRValObj obj, int val);
    void alloc(pIRValObj obj);
    int getAddr(pIRValObj obj);
};
