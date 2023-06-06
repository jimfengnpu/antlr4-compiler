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
    assert(0);
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

void SSAMaker::fillSuccPhi(pBlock block, pBlock from){
    for(auto& obj: block->phiOrigin){
        auto found = findUsingObj(obj);
        // if(found)
        block->phiList[obj].insert({from, found});
    }
}

pBlock SSAMaker::visit(pBlock block){
    visitStack.push_back(block);
    visited[block] = true;
    for(auto& obj : block->phiOrigin){
        if(!renamedObj[block][obj]){
            pIRScalValObj targ = dynamic_pointer_cast<IRScalValObj>(obj);
            auto newObj = block->phiObj[obj] = make_shared<IRScalValObj>(*targ.get());
            newObj->name = getNewName(obj);
            // cout << "add "<< obj->name << " in "<< block<<endl;
            renamedObj[block][obj] = newObj;
            block->phiDef.insert(newObj);
        }
    }
    for(auto& ir: block->structions){
        // cout << *ir.get() << endl;
        if(ir->opt1)ir->opt1= renameObj(block, ir->opt1);
        if(ir->opt2)ir->opt2 = renameObj(block, ir->opt2);
        pIRScalValObj targ = dynamic_pointer_cast<IRScalValObj>(ir->target), newObj = nullptr;
        if(targ){
            if(targ->isTmp || targ->scopeSymbols->isGlobal){
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
    if(block->branchVal){
        block->branchVal = dynamic_pointer_cast<IRScalValObj>(renameObj(block, block->branchVal));
    }
    if(block->nextNormal){
        fillSuccPhi(block->nextNormal, block);
    }
    if(block->nextBranch){
        fillSuccPhi(block->nextBranch, block);
    }
    for(auto child: block->domChild){
        visit(child);
    }
    visitStack.pop_back();
    return nullptr;
}

pBlock SSAFinalizer::visit(pBlock block){
    
    return nullptr;
}