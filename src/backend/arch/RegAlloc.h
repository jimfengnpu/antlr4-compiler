#ifndef REG_ALLOC_H
#define REG_ALLOC_H

#include "Arch.h"
#include "IRProcessor.h"
#include <queue>


class RegAllocator: public IRProcessor{
    BaseArch* archInfo;
    map<pIRValObj, pIRValObj> phiFa; 
    map<pIRValObj, int> valCost;
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
    virtual void apply(ASTVisitor& visitor){
        for(auto func: visitor.functions){
            if(func->entry != nullptr){
                allocReg(func);
            }
        }
    }
};
#endif