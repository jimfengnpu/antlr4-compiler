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
    virtual void apply(ASTVisitor& visitor){

    }
};
#endif