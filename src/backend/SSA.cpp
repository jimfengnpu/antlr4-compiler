#include "SSA.h"

pIRValObj SSAMaker::findUsingObj(pIRValObj origin){
    // cout << "find "<<origin->name <<" in ";
    for(auto block=visitStack.rbegin(); block!=visitStack.rend();block++){
        // cout << *block << " "; 
        try{
            return renamedObj[*block].at(origin);
        }catch(...){
        }
    }
    // cout <<endl;
    // assert(0);
    return nullptr;
}

pIRObj SSAMaker::renameObj(pBlock block, pIRObj operand){
    // cout << "rename "<< operand->name <<endl;
    pIRScalValObj obj = dynamic_pointer_cast<IRScalValObj>(operand);
    pIRValObj out_obj;
    if(!obj)return operand;
    if(obj->scopeSymbols->isGlobal)return operand;
    if(obj->isConstant()&&(!obj->isIdent))return operand;
    out_obj = findUsingObj(obj);
    assert(out_obj != nullptr);
    return out_obj;
}

void SSAMaker::fillPostPhi(pBlock block, pBlock from){
    for(auto& obj: block->phiFa){
        auto found = findUsingObj(obj);
        if(found)
            block->phiList[obj].push_back({from, found});
    }
}

void SSAMaker::visitRename(pBlock block){
    // phiFinished[block] = true;
    // if(visited[block])return;
    visitStack.push_back(block);
    visited[block] = true;
    for(auto& obj : block->phiFa){
        if(!renamedObj[block][obj]){
            pIRScalValObj targ = dynamic_pointer_cast<IRScalValObj>(obj);
            auto newObj = block->phiObj[obj] = make_shared<IRScalValObj>(*targ.get());
            newObj->name = getNewName(obj);
            // cout << "add "<< obj->name << " in "<< block<<endl;
            renamedObj[block][obj] = newObj;
        }
    }
    for(auto& ir: block->structions){
        // cout << *ir.get() << endl;
        if(ir->type == IRType::PARAM)continue;
        if(ir->opt1)ir->opt1= renameObj(block, ir->opt1);
        if(ir->opt2)ir->opt2 = renameObj(block, ir->opt2);
        pIRScalValObj targ = dynamic_pointer_cast<IRScalValObj>(ir->target), newObj = nullptr;
        if(targ){
            if(targ->isTmp){
                newObj = targ;
            }else {
                newObj = make_shared<IRScalValObj>(*targ.get());
                newObj->name = getNewName(targ);
                ir->target = newObj;
            }
            // cout << "add "<< targ->name << " in "<< block<<endl;
            renamedObj[block][targ] = newObj;
        }
    }
    if(block->nextNormal){
        fillPostPhi(block->nextNormal, block);
    }
    if(block->nextBranch){
        fillPostPhi(block->nextBranch, block);
    }
    // if(block->nextBranch &&(!(visited[block->nextBranch]&&phiFinished[block->nextBranch])))
    //     visitRename(block->nextBranch);
    for(auto child: block->domChild){
        visitRename(child);
    }
    visitStack.pop_back();
}