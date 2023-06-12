#include "IRProcessor.h"
#include "../backend/Dom.h"


bool BlockPruner::checkRemoveEmptyBlock(pBlock block){
    if(block->structions.size() > 0)return false;
    if(block->nextBranch == nullptr){
        /*
        *B1-->B2
        B0-->x:*B1,B3
            ==>
        B0-->x:B2,B3
        */
        auto& succ = block->nextNormal->from;
        succ.erase(block);
        for(auto fa: block->from){
            if(fa->nextNormal == block){
                fa->nextNormal = block->nextNormal;
            }else{
                fa->nextBranch = block->nextNormal;
            }
            succ.insert(fa);
        }
        block->nextNormal->phiOrigin.insert(block->phiOrigin.begin(), block->phiOrigin.end());
        block->nextNormal->phiList.insert(block->phiList.begin(), block->phiList.end());
        block->nextNormal->phiDef.insert(block->phiDef.begin(), block->phiDef.end());
        block->nextNormal->phiKey.insert(block->phiKey.begin(), block->phiKey.end());
        block->nextNormal->phiObj.insert(block->phiObj.begin(), block->phiObj.end());
        return true;
    }
    if(block->from.size() > 1)return false;
    auto fa = *(block->from.begin());
    if(fa->nextBranch != nullptr)return false;
    assert(fa->nextBranch == nullptr);
    /*
    B0-->*B1-->x:B2,B3
        ==>
    B0-->x:B2,B3
    */
    fa->nextNormal = block->nextNormal;
    fa->nextBranch = block->nextBranch;
    fa->branchVal = block->branchVal;
    block->nextNormal->from.erase(block);
    block->nextNormal->from.insert(fa);
    if(block->nextBranch){
        block->nextBranch->from.erase(block);
        block->nextBranch->from.insert(fa);
    }
    return true;
}

void BlockPruner::processDependency(IRProcessors* procs){
    procs->add(new DomMaker());
}

void LiveCalculator::mergeSuccLivein(pBlock block, pBlock from){
    if(!block)return;
    int sz = from->liveOut.size();
    from->liveOut.insert(block->liveIn.begin(), block->liveIn.end());
    for(auto& origin: block->phiOrigin){
        from->liveOut.insert(block->phiList[origin][from]);
    }
    if(from->liveOut.size() != sz)
        changed = true;
}

pBlock LiveCalculator::visit(pBlock block){
    vector<pIRValObj> diff{};
    mergeSuccLivein(block->nextBranch, block);
    mergeSuccLivein(block->nextNormal, block);
    set_difference(block->liveOut.begin(), block->liveOut.end(),
        block->defObj.begin(), block->defObj.end(), back_inserter(diff));
    for(auto p: diff){
        block->liveIn.insert(p);
    }
    return nullptr;
}

void LiveCalculator::makeLive(pIRFunc& func){
    for(auto& block: func->blocks){
        block->liveIn.clear();
        block->liveOut.clear();
        block->useObj.clear();
        block->defObj.clear();
        auto& liveUse = block->useObj;
        auto& liveDef = block->defObj;
        pIRValObj op1, op2, targ;
        for(auto& obj: block->phiOrigin){
            liveDef.insert(block->phiObj[obj]);
        }
        for(auto& ir: block->structions){
            op1 = dynamic_pointer_cast<IRValObj>(ir->opt1);
            op2 = dynamic_pointer_cast<IRValObj>(ir->opt2);
            targ = dynamic_pointer_cast<IRValObj>(ir->target);
            if(op1 && (!op1->isConstant()||(op1->isIdent)) 
                && liveDef.find(op1) == liveDef.end())liveUse.insert(op1);
            if(op2 && (!op2->isConstant()||(op2->isIdent)) 
                && liveDef.find(op2) == liveDef.end())liveUse.insert(op2);
            if(targ && !targ->scopeSymbols->isGlobal)liveDef.insert(targ);
        }
        if(block->branchVal && liveDef.find(block->branchVal) == liveDef.end())
            liveUse.insert(block->branchVal);
        block->liveIn.insert(liveUse.begin(), liveUse.end());
    }
    do{
        changed = false;
        for(auto& block: func->blocks){
            visit(block);
        }
    }while(changed);
}