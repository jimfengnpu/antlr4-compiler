#include "SSA.h"

SSAMaker::SSAMaker() { triggers.push_back(new LiveCalculator()); }

pIRValObj SSAMaker::findUsingObj(pIRValObj origin) {
    // cout << "find "<<origin->name <<" in ";
    for (auto block = visitStack.rbegin(); block != visitStack.rend();
         block++) {
        // cout << *block << " ";
        try {
            return renamedObj[*block].at(origin);
        } catch (...) {
        }
    }
    return nullptr;
}

pIRObj SSAMaker::renameObj(pIRObj operand, pSysYIR useSource) {
    // cout << "rename "<< operand->name <<endl;
    pIRScalValObj obj = toScal(operand);
    pIRValObj out_obj;
    if (!obj) return operand;
    if (obj->isConstant() && (!obj->isIdent)) return operand;
    if (obj->scopeSymbols->isGlobal || obj->fa != nullptr) return operand;
    out_obj = findUsingObj(obj);
    assert(out_obj != nullptr);
    out_obj->useStructions.insert(useSource);
    return out_obj;
}

void SSAMaker::fillSuccPhi(pBlock block, pBlock from) {
    for (auto ir = block->irHead; ir != nullptr; ir = ir->next) {
        if (ir->type == IRType::PHI) {
            auto defObj = toVal(ir->target);
            auto origin = phiOrigin[block][defObj];
            if (origin == nullptr) origin = defObj;
            auto found = toVal(renameObj(origin, ir));
            phiList[block][origin][from] = found;
        } else
            break;
    }
}

pBlock SSAMaker::visit(pBlock block) {
    visitStack.push_back(block);
    for (auto ir = block->irHead; ir != nullptr; ir = ir->next) {
        if (ir->opt1) ir->opt1 = renameObj(ir->opt1, ir);
        if (ir->opt2) ir->opt2 = renameObj(ir->opt2, ir);
        if (ir->type == IRType::RET) {
            block->function->returnVal = toVal(ir->opt1);
        }
        if (ir->type == IRType::IDX) continue;
        pIRScalValObj targ = toScal(ir->target), newObj = nullptr;
        if (targ) {
            if (targ->scopeSymbols->isGlobal || targ->fa != nullptr) {
                newObj = targ;
            } else {
                newObj = make_shared<IRScalValObj>(*targ.get());
                newObj->name = getNewName(targ);
                newObj->defStruction = ir;
                newObj->ssaDef = true;
                ir->target = newObj;
            }
            if (ir->type == IRType::PHI) {
                phiOrigin[block][newObj] = targ;
            }
            renamedObj[block][targ] = newObj;
        }
    }
    if (block->nextNormal) {
        fillSuccPhi(block->nextNormal, block);
    }
    if (block->nextBranch) {
        fillSuccPhi(block->nextBranch, block);
    }
    for (auto child : block->domChild) {
        visit(child);
    }
    visitStack.pop_back();
    return nullptr;
}