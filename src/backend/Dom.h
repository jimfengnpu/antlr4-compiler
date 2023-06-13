#pragma once
#include "../common/IRProcessor.h"


class DomMaker: public IRProcessor{
public:
    map<pBlock, int> dfn;
    map<pBlock, int> sdno;
    map<pBlock, pBlock> idom;
    map<pBlock, pBlock> dfsFa;
    map<pBlock, pBlock> setFa;
    map<pBlock, pBlock> setV;
    map<pBlock, vector<pBlock> > bucket;
    vector<pBlock> visitBlocks;
    int visitId;
    DomMaker(){
        triggers.push_back(new LiveCalculator());
    }
    virtual void apply(ASTVisitor& visitor){
        addTriggers();
        for(auto& func: visitor.functions){
            if(func->entry)
            makeDom(func);
        }
    }
    void makeDom(pIRFunc func);
    pBlock find(pBlock p);
    pBlock eval(pBlock p){
        find(p);
        return setV[p];
    }
    virtual pBlock visit(pBlock r){
        dfn[r] = ++visitId;
        visitBlocks.push_back(r);
        sdno[r] = visitId;
        if(r->nextNormal && dfn[r->nextNormal]==0){
            dfsFa[r->nextNormal] = r;
            visit(r->nextNormal);
        }
        if(r->nextBranch && dfn[r->nextBranch]==0){
            dfsFa[r->nextBranch] = r;
            visit(r->nextBranch);
        }
        return nullptr;
    }
};