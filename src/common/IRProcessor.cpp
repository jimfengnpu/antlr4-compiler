#include "IRProcessor.h"
#include "Optimizer.h"

void IRProcessor::addTriggers(){
    procs->processors.insert(procs->processors.begin(),
        triggers.begin(), triggers.end());
    for(auto t: triggers){
        t->procs = procs;
    }
}


LiveCalculator::LiveCalculator(){}

void LiveCalculator::mergeSuccLivein(pBlock block, pBlock from){
    if(!block)return;
    int sz = from->liveOut.size();
    from->liveOut.insert(block->liveIn.begin(), block->liveIn.end());
    for(auto ir=block->irHead; ir!=nullptr; ir=ir->next){
        if(ir->type == IRType::PHI){
            from->liveOut.insert(block->phiList[ir->target][from]);
        }
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
        // for(auto& obj: block->phiOrigin){
        //     liveDef.insert(block->phiObj[obj]);
        // }
        for(auto ir=block->irHead; ir!=nullptr; ir=ir->next){
            op1 = toVal(ir->opt1);
            op2 = toVal(ir->opt2);
            targ = toVal(ir->target);
            if(op1 && (!op1->isConstant()||(op1->isIdent)) 
                && liveDef.find(op1) == liveDef.end())liveUse.insert(op1);
            if(op2 && (!op2->isConstant()||(op2->isIdent)) 
                && liveDef.find(op2) == liveDef.end())liveUse.insert(op2);
            if(targ && !targ->scopeSymbols->isGlobal)liveDef.insert(targ);
        }
        block->liveIn.insert(liveUse.begin(), liveUse.end());
    }
    do{
        changed = false;
        for(auto& block: func->blocks){
            visit(block);
        }
    }while(changed);
}