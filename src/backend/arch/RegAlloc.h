#ifndef REG_ALLOC_H
#define REG_ALLOC_H

#include "Arch.h"
#include "IRProcessor.h"
#include <queue>

const int maxBlockASMId = 1024;
const int blockLoopWeight = 5;

class RegAllocator: public IRProcessor{
    BaseArch* archInfo;
    map<pBlock, bool> visited;
    map<pBlock, pBlock> visitPath;
    map<pBlock, int> blockFreq;
    map<vReg*, int> valCost;
    set<vReg*> vals{};
    map<vReg*, unordered_set<vReg*> > conflictMap;
    class ValComparator{
    public:
        bool operator()(const pIRValObj& a, const pIRValObj& b) const{
            return false;
        }
    };
    priority_queue<pIRValObj, vector<pIRValObj>, ValComparator> checkList;
public:
    RegAllocator(BaseArch* arch): archInfo(arch){}
    void allocReg(pIRFunc func);
    virtual pBlock visit(pBlock);
    void addLoopWeight(pBlock block);
    void makeGraph(pIRFunc func);
    virtual void apply(ASTVisitor& visitor){
        for(auto func: visitor.functions){
            if(func->entry != nullptr){
                allocReg(func);
            }
        }
    }
};
#endif