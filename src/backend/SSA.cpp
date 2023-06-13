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
    return nullptr;
}

pIRObj SSAMaker::renameObj(pIRObj operand, pIRObj useSource){
    // cout << "rename "<< operand->name <<endl;
    pIRScalValObj obj = dynamic_pointer_cast<IRScalValObj>(operand);
    pIRValObj out_obj;
    if(!obj)return operand;
    if(obj->scopeSymbols->isGlobal || obj->fa != nullptr)return operand;
    if(obj->isConstant()&&(!obj->isIdent))return operand;
    out_obj = findUsingObj(obj);
    assert(out_obj != nullptr);
    out_obj->useStructions.insert(useSource);
    return out_obj;
}

void SSAMaker::fillSuccPhi(pBlock block, pBlock from){
    for(auto& obj: block->phiOrigin){
        auto found = dynamic_pointer_cast<IRValObj>(renameObj(obj, from));
        if(found){
            block->phiList[obj].insert({from, found});
        }
    }
}

pBlock SSAMaker::visit(pBlock block){   
    visitStack.push_back(block);
    for(auto& obj : block->phiOrigin){
        if(!renamedObj[block][obj]){
            pIRScalValObj targ = dynamic_pointer_cast<IRScalValObj>(obj);
            auto newObj = block->phiObj[obj] = make_shared<IRScalValObj>(*targ.get());
            newObj->name = getNewName(obj);
            // cout << "add "<< obj->name << " in "<< block<<endl;
            renamedObj[block][obj] = newObj;
            newObj->phiDef = true;
            newObj->defStruction = block;
            block->phiDef.insert(newObj);
            block->phiKey[newObj] = obj;
        }
    }
    for(auto& ir: block->structions){
        // cout << *ir.get() << endl;
        if(ir->opt1)ir->opt1= renameObj(ir->opt1, ir);
        if(ir->opt2)ir->opt2 = renameObj(ir->opt2, ir);
        if(ir->type == IRType::RET){
            block->function->returnVal = dynamic_pointer_cast<IRValObj>(ir->opt1);
        }
        if(ir->type == IRType::IDX)continue;
        pIRScalValObj targ = dynamic_pointer_cast<IRScalValObj>(ir->target), newObj = nullptr;
        if(targ){
            if(targ->scopeSymbols->isGlobal || targ->fa != nullptr){
                newObj = targ;
            }else {
                newObj = make_shared<IRScalValObj>(*targ.get());
                newObj->name = getNewName(targ);
                newObj->defStruction = ir;
                ir->target = newObj;
            }
            // cout << "add "<< targ->name << " in "<< block<<endl;
            renamedObj[block][targ] = newObj;
        }
    }
    if(block->branchVal){
        block->branchVal = dynamic_pointer_cast<IRScalValObj>(renameObj(block->branchVal, block));
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