#include "SSA.h"

pIRValObj SSAMaker::findUsingObj(pBlock block, pIRValObj origin){
    while(block){
        try{
            return renamedObj[block][origin];
        }catch(...){
        }
        block = block->domFa;
    }
    return nullptr;
}

pIRObj SSAMaker::renameObj(pBlock block, pIRObj operand){
    pIRScalValObj obj = dynamic_pointer_cast<IRScalValObj>(operand);
    pIRValObj out_obj;
    if(!obj)return nullptr;
    if(obj->isConstant())return nullptr;
    out_obj = findUsingObj(block, obj);
    if(out_obj == nullptr){
        phiFinished[block] = false;
    }
    return out_obj;
}

void SSAMaker::visitRename(pBlock block){
    phiFinished[block] = true;
    for(auto& [obj, vec] : block->phiFa){
        for(auto fa: vec){
            block->phiList[obj].push_back(findUsingObj(fa, obj));
        }
    }
    if(visited[block])return;
    for(auto& ir: block->structions){
        ir->opt1= renameObj(block, ir->opt1);
        ir->opt2 = renameObj(block, ir->opt2);
        pIRScalValObj targ = dynamic_pointer_cast<IRScalValObj>(ir->target), newObj = nullptr;
        if(targ){
            if(targ->isTmp){
                newObj = targ;
            }else {
                newObj = make_shared<IRScalValObj>(targ->isConst, targ->name + to_string(++renamedId[targ]));
                ir->target = newObj;
            }
            renamedObj[block][targ] = newObj;
        }
    }
    if(!(visited[block->nextNormal]&&phiFinished[block->nextNormal]))
        visitRename(block->nextNormal);
    if(!(visited[block->nextBranch]&&phiFinished[block->nextBranch]))
        visitRename(block->nextBranch);
}