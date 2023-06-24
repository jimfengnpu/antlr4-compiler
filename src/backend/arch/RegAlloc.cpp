#include "RegAlloc.h"
#include <bitset>


void RegAllocator::addLoopWeight(pBlock block){
    do{
        blockFreq[block] *= blockLoopWeight;
        block = visitPath[block];
    }while(block);
}

pBlock RegAllocator::visit(pBlock block){
    visited[block] = true;
    blockFreq[block] = 1;
    if(block->nextBranch){
        if(visited[block->nextBranch]){
            addLoopWeight(block->nextBranch);
        }else{
            visitPath[block] = block->nextBranch;
            visit(block->nextNormal);
        }
    }
    if(block->nextNormal){
        if(visited[block->nextNormal]){
            addLoopWeight(block->nextNormal);
        }else{
            visitPath[block] = block->nextNormal;
            visit(block->nextNormal);
        }
    }
    return nullptr;
}

void RegAllocator::makeGraph(pIRFunc func){
    int sid;
    map<vReg*, bitset<maxBlockASMId> > regLive;
    vector<ASMInstr*> asmVec;
    vals.clear();
    conflictMap.clear();
    //assembly add id
    for(pBlock block=func->entry;block;block=block->asmNextBlock){
        for(auto ir=block->irHead;ir;ir=ir->next){
            for(auto s: ir->asmInstrs){
                for(auto v: s->op){
                    if(v->regType==REG_R)
                    vals.insert(v);
                }
            }
        }
    }

    for(pBlock block=func->entry;block;block=block->asmNextBlock){
        sid = 0;
        asmVec.clear();
        regLive.clear();
        for(auto ir=block->irHead;ir;ir=ir->next){
            for(auto s: ir->asmInstrs){
                sid++;
                asmVec.push_back(s);
            }
        }
        for(auto v: block->liveOut){
            if(vals.find(v->reg()) != vals.end()){
                regLive[v->reg()].flip();
            }
        }
        int callAsmId = -1;
        int i=0;
        for(auto s=asmVec.rbegin(); i < sid; i--, s++){
            auto opDef=*((*s)->op.begin());
            if(vals.find(opDef) != vals.end()){
                regLive[opDef].flip();
            }
            for(auto op=(*s)->op.begin() +1;op!=(*s)->op.end(); op++){
                if(vals.find(*op) != vals.end()){
                    if(!regLive[*op][i]){
                        regLive[*op].flip(i);
                    }
                }
            }
        }
        for(auto [v1, v1liv]: regLive){
            for(auto [v2, v2liv]: regLive){
                if(v1!=v2){
                    auto intersect = regLive[v1] & regLive[v2];
                    if(intersect.any()){
                        conflictMap[v1].insert(v2);
                        conflictMap[v2].insert(v1);
                    }
                }
            }
        }
    }
}


void RegAllocator::allocReg(pIRFunc func){
    bool conficted;
    do{
        while(!checkList.empty()){
            checkList.pop();
        }
        conficted=false;
        makeGraph(func);

    }while(conficted);
}