#include "Optimizer.h"


void ConstBroadcast::setConstState(pIRObj obj){
    if(!obj)return;
    auto scalObj = dynamic_pointer_cast<IRScalValObj>(obj);
    if(!scalObj)return;
    if(scalObj->fa != nullptr)return;
    // immediate number
    if(scalObj->isConstant() && !scalObj->isIdent){
        scalObj->constState = IR_CONST;
    }else if(scalObj->defStruction != nullptr){
        int constState = IR_UNDEF;
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
                    constState = IR_NAC;
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
                constState = CONST_STATE(constState, op->constState);
                if(constState == IR_NAC && value == op->value){
                    constState = IR_CONST;
                }else{
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
        }
    }
}

void ConstBroadcast::applyBlock(pBlock block){
    for(auto obj: block->phiDef){
        setConstState(obj);
    }
    for(auto& ir: block->structions){
        setConstState(ir->target);
    }
}