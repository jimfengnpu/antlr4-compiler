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
            for(auto s=ir->asmHead; s; s=s->next){
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
            for(auto s=ir->asmHead; s; s=s->next){
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
                valCost[opDef] += blockFreq[block];
            }
            for(auto op=(*s)->op.begin() +1;op!=(*s)->op.end(); op++){
                if(vals.find(*op) != vals.end()){
                    if(!regLive[*op][i]){
                        regLive[*op].flip(i);
                    }
                    valCost[*op] += blockFreq[block];
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
    map<vReg*, bool> colored;
    map<vReg*, bool> removed;
    map<vReg*, int> regIds;
    deque<vReg*> regOrder;
    int k = archInfo->genRegsId.size();
    do{
        while(!checkList.empty()){
            checkList.pop();
        }
        colored.clear();
        removed.clear();
        regIds.clear();
        regOrder.clear();
        conficted=false;
        makeGraph(func);
        map<vReg* , unordered_set<vReg*> > bkConflict(conflictMap);
        priority_queue<vReg*, vector<vReg*>, ValConflictComparator> qvals;
        for(auto v: vals){
            if(v->regId != -1){
                colored[v] = true;
                regIds[v] = v->regId;
            }
            qvals.push(v);
        }
        while(qvals.size()){
            auto v=qvals.top();
            if(conflictMap[v].size() < k){
                for(auto adj: conflictMap[v]){
                    conflictMap[adj].erase(v);
                }
                conflictMap[v].clear();
            }
            qvals.pop();
            regOrder.push_front(v);
        }
        conflictMap = bkConflict;
        for(auto v: regOrder){
            if(!colored[v]){
                set<int> scolor{};
                for(auto adj: conflictMap[v]){
                    if(colored[adj]){
                        scolor.insert(regIds[adj]);
                    }
                }
                for(auto c: archInfo->genRegsId){
                    if(scolor.find(c) == scolor.end()){
                        colored[v] = true;
                        regIds[v] = c;
                        break;
                    }
                }
            }
            if(!colored[v]){
                checkList.push(v);
            }
        }
        if(checkList.size()){
            auto splited = checkList.top();
            splited->regType = REG_M;
            for(auto b: func->blocks){
                for(auto ir=b->irHead;ir;ir=ir->next){
                    for(auto s=ir->asmHead; s; s=s->next){
                        for(int i=0;i<s->op.size();i++){
                            if(s->op[i] == splited){
                                vReg* mreg = new vReg();
                                if(i){
                                    ir->addASMFront(new ASMInstr(loadOp, {mreg, splited}), s);
                                }else{
                                    ir->addASMFront(new ASMInstr(storeOp, {mreg, splited}), s);
                                }
                            }
                        }
                    }
                }
            }
            conficted = true;
        }
    }while(conficted);
}