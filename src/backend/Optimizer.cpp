#include "Optimizer.h"
#include "Dom.h"


bool BlockPruner::checkRemoveEmptyBlock(pBlock block){
    if(block->size() > 0)return false;
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

void BlockPruner::applyBlock(pBlock block){
    if(checkRemoveEmptyBlock(block))
        deleted.push_back(block);
}

void ConstBroadcast::setConstState(pIRObj obj){
    if(!obj)return;
    auto scalObj = dynamic_pointer_cast<IRScalValObj>(obj);
    if(!scalObj)return;
    if(scalObj->fa != nullptr)return;
    // immediate number
    if(scalObj->isConstant() && !scalObj->isIdent){
        scalObj->constState = IR_CONST;
    }else if(scalObj->defStruction != nullptr){
        int constState = IR_NAC;
        int value = 0;
        if(auto defIr = dynamic_pointer_cast<SysYIR>(scalObj->defStruction)){
            // define in normal struction
            switch(defIr->type){
                case IRType::DEF:
                    constState = IR_CONST;
                    break;
                case IRType::CALL:
                case IRType::IDX:
                case IRType::RET:
                    break;
                default: //usual cal
                    constState = IR_CONST;
                    auto op1 = dynamic_pointer_cast<IRScalValObj>(defIr->opt1);
                    auto op2 = dynamic_pointer_cast<IRScalValObj>(defIr->opt2);
                    if(op1)constState = CONST_OP(constState, op1->constState);
                    if(op2)constState = CONST_OP(constState, op2->constState);
                    if(constState == IR_CONST){
                        value = CalConstExp(defIr->type, op1->value, op2?op2->value:0);
                    }
            }
            if(constState == IR_CONST){
                defIr->removedMask = true;
            }
        }else{
            auto block = dynamic_pointer_cast<IRBlock>(scalObj->defStruction);
            assert(block!=nullptr);
            for(auto& [from, use]: block->phiList[block->phiKey[scalObj]]){
                auto op = dynamic_pointer_cast<IRScalValObj>(use);
                if(constState == IR_CONST && op->constState == IR_CONST && value == op->value){
                    constState = IR_CONST;
                }else{
                    constState = CONST_STATE(constState, op->constState);
                }
                if(constState == IR_CONST){
                    value = op->value;
                }
            }
            if(constState == IR_CONST){
                block->phiOrigin.erase(block->phiKey[scalObj]);
            }
        }
        scalObj->constState = constState;
        if(constState == IR_CONST){
            scalObj->value = value;
            scalObj->defStruction = nullptr;
            scalObj->name = to_string(value);
            scalObj->isConst = true;
            scalObj->isIdent = false;
            changed = true;
        }
    }
}

void ConstBroadcast::applyBlock(pBlock block){
    for(auto obj: block->phiDef){
        setConstState(obj);
    }
    for(auto& ir: block->structions){
        if(!ir->removedMask)
            setConstState(ir->target);
    }
}