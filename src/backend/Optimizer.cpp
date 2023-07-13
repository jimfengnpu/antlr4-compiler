#include "Optimizer.h"

#include "Dom.h"

void BlockPruner::prepareTriggers() {
    triggers.push_back(new ConstBroadcast());
    triggers.push_back(new CodeCleaner());
    triggers.push_back(new DomMaker());
}

// change phi use of %block% from %from% to %now%(if %now% not nullptr,
// otherwise just erase %from%)
void changeErasePhiFrom(pBlock block, pBlock from, pBlock now) {
    for (auto ir = block->irHead; ir != nullptr; ir = ir->next) {
        if (ir->type == IRType::PHI) {
            if (nullptr != now) {
                block->phiList[ir->target][now] =
                    block->phiList[ir->target][from];
            }
            block->phiList[ir->target].erase(from);
        } else
            break;
    }
}

bool BlockPruner::checkRemoveEmptyBlock(pBlock block) {
    if (block->size() > 0) return false;
    if (block->from.size() > 0) {
        if (block->nextNormal->hasPhi() ||
            block->nextBranch && block->nextBranch->hasPhi()) {
            return false;
        }
    }
    if (block->nextBranch == nullptr) {
        /*
        *B1-->B2
        B0-->x:*B1,B3
            ==>
        B0-->x:B2,B3
        */
        auto& succ = block->nextNormal->from;
        succ.erase(block);
        for (auto fa : block->from) {
            assert(fa != nullptr);
            if (fa->nextNormal == block) {
                fa->nextNormal = block->nextNormal;
            }
            if (fa->nextBranch == block) {
                fa->nextBranch = block->nextNormal;
            }
            succ.insert(fa);
            changeErasePhiFrom(block->nextNormal, block, fa);
        }
        return true;
    }
    if (block->from.size() > 1) return false;
    auto fa = *(block->from.begin());
    if (nullptr == fa || fa->nextBranch != nullptr) return false;
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
    changeErasePhiFrom(block->nextNormal, block, fa);
    if (block->nextBranch) {
        block->nextBranch->from.erase(block);
        block->nextBranch->from.insert(fa);
        changeErasePhiFrom(block->nextBranch, block, fa);
    }
    return true;
}

void BlockPruner::applyFunc(pIRFunc func) {
    deleted.clear();
    for (pBlock block : func->blocks) {
        if (!visited[block] || (block != func->entry && block != func->exit &&
                                checkRemoveEmptyBlock(block))) {
            deleted.push_back(block);
            if (!visited[block]) {
                changeErasePhiFrom(block->nextNormal, block, nullptr);
                if (block->nextBranch)
                    changeErasePhiFrom(block->nextBranch, block, nullptr);
            }
        }
    }
    if (deleted.size() > 0) changed = true;
    for (auto block : deleted) {
        func->blocks.erase(block);
    }
}

void ConstBroadcast::prepareTriggers() {
    triggers.push_back(new CodeCleaner());
}

bool clearConstUse(pSysYIR ir, pIRObj obj, int& value) {
    auto scalObj = toScal(obj);
    if (nullptr == scalObj) return false;
    if (scalObj->fa != nullptr) return false;
    if (scalObj->constState == IR_CONST) {
        scalObj->useStructions.erase(ir);
        value = scalObj->value;
        return true;
    }
    return false;
}

void ConstBroadcast::setConstState(pBlock block, pIRObj obj) {
    auto scalObj = toScal(obj);
    if (nullptr == scalObj) return;
    if (scalObj->fa != nullptr) return;
    // immediate number
    if (scalObj->isConstant() && !scalObj->isIdent) {
        scalObj->constState = IR_CONST;
    } else if (auto defIr = scalObj->defStruction) {
        int constState = IR_UNDEF;
        int value = 0;
        // if( = dynamic_pointer_cast<SysYIR>(scalObj->defStruction)){
        // define in normal struction
        switch (defIr->type) {
            case IRType::DEF:
                constState = IR_CONST;
                break;
            case IRType::PHI:
                for (auto& [from, use] : block->phiList.at(scalObj)) {
                    auto op = toScal(use);
                    if (constState == IR_CONST && op->constState == IR_CONST &&
                        value == op->value) {
                        constState = IR_CONST;
                    } else {
                        constState = CONST_STATE(constState, op->constState);
                    }
                    if (constState == IR_CONST) {
                        value = op->value;
                    }
                }
                break;
            case IRType::CALL:
            case IRType::IDX:
            case IRType::RET:
                constState = IR_NAC;
                break;
            default:  // usual cal
                constState = IR_CONST;
                auto op1 = toScal(defIr->opt1);
                auto op2 = toScal(defIr->opt2);
                if (op1) {
                    constState = CONST_OP(constState, op1->constState);
                }
                if (op2) {
                    constState = CONST_OP(constState, op2->constState);
                }
                if (constState == IR_CONST) {
                    value = CalConstExp(defIr->type, op1->value,
                                        op2 ? op2->value : 0);
                }
        }
        scalObj->constState = constState;
        if (constState == IR_CONST) {
            scalObj->value = value;
            scalObj->name = to_string(value);
            scalObj->isConst = true;
            scalObj->isIdent = false;
            changed = true;
        }
    }
}

void ConstBroadcast::applyBlock(pBlock block) {
    int value;
    for (auto ir = block->irHead; ir != nullptr; ir = ir->next) {
        setConstState(block, ir->target);
        if (clearConstUse(ir, ir->opt1, value)) {
            ir->opt1 = make_shared<IRScalValObj>(value);
        }
        if (clearConstUse(ir, ir->opt2, value)) {
            ir->opt2 = make_shared<IRScalValObj>(value);
        }
        if (IRType::PHI == ir->type) {
            for (auto [from, use] : block->phiList[ir->target]) {
                if (clearConstUse(ir, use, value)) {
                    block->phiList[ir->target][from] =
                        make_shared<IRScalValObj>(value);
                }
            }
        }
    }
}

void CommonExp::prepareTriggers() { triggers.push_back(new CodeCleaner()); }

pIRObj CommonExp::checkOp(pIRObj val) {
    auto s = toScal(val);
    if (s && s->isConstant() && !s->isIdent) {
        pIRObj imm = constMap[s->value];
        if (imm) {
            val = imm;
        } else {
            constMap[s->value] = val;
        }
    }
    return val;
}

void clearUse(pIRValObj val, pSysYIR ir) {
    if (val && val->ssaDef) {
        val->useStructions.erase(ir);
    }
}

bool checkUse(pIRValObj val) {
    if (val && val->ssaDef) {
        if (val->defStruction->type == IRType::PHI) {
            return false;
        }
    }
    return true;
}

void CommonExp::applyBlock(pBlock block) {
    for (auto ir = block->irHead; ir != nullptr; ir = ir->next) {
        if (IRType::CALL != ir->type && IRType::PHI != ir->type &&
            IRType::PARAM != ir->type && IRType::DEF != ir->type &&
            IRType::ASSIGN != ir->type) {
            pIRObj op1 = ir->opt1, op2 = ir->opt2;
            op1 = checkOp(op1);
            op2 = checkOp(op2);
            auto val = ops[ir->type][op1][op2];
            if (val != nullptr && val != toVal(ir->opt1) &&
                checkUse(toVal(op1)) && checkUse(toVal(op2))) {
                clearUse(toVal(ir->opt1), ir);
                clearUse(toVal(ir->opt2), ir);
                ir->type = IRType::ASSIGN;
                ir->opt1 = val;
                if (val->ssaDef) {
                    val->useStructions.insert(ir);
                }
                ir->opt2 = nullptr;
                changed = true;
            } else {
                ops[ir->type][op1][op2] = ir->target;
            }
        }
    }
}

void CommonExp::applyFunc(pIRFunc func) {
    constMap.clear();
    ops.clear();
}

void CodeCleaner::prepareTriggers() { triggers.push_back(new BlockPruner()); }

bool checkObjUseEmpty(pIRObj obj) {
    auto scalObj = toScal(obj);
    if (scalObj)
        if (scalObj->fa == nullptr)
            if (auto defIr = scalObj->defStruction) {
                return scalObj->useStructions.empty();
            }
    return false;
}

void CodeCleaner::applyBlock(pBlock block) {
    for (auto ir = block->irHead; ir != nullptr; ir = ir->next) {
        if (IRType::CALL != ir->type && checkObjUseEmpty(ir->target)) {
            if (ir->type == IRType::BR) {
                if (0 != block->branchVal->value) {  // always branch
                    block->nextNormal->from.erase(block);
                    changeErasePhiFrom(block->nextNormal, block, nullptr);
                    block->nextNormal = block->nextBranch;
                } else {
                    block->nextBranch->from.erase(block);
                    changeErasePhiFrom(block->nextBranch, block, nullptr);
                }
                block->branchVal = nullptr;
                block->nextBranch = nullptr;
            }
            block->remove(ir);
            changed = true;
        }
    }
    if (block->branchVal) {
        if (block->nextBranch == block->nextNormal) {
            block->branchVal = nullptr;
            block->nextBranch = nullptr;
            changed = true;
        }
    }
}