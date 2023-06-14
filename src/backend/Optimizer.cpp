#include "Optimizer.h"
#include "Dom.h"


BlockPruner::BlockPruner(){
    triggers.push_back(new DomMaker());
}


void changePhiFrom(pBlock block, pBlock from, pBlock now){
    for(auto& ir: block->structions){
        if(ir->type == IRType::PHI){
            block->phiList[ir->target][now] = block->phiList[ir->target][from];
            block->phiList[ir->target].erase(from);
        }else break;
    }
}

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
            changePhiFrom(block->nextNormal, block, fa);
        }
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
    changePhiFrom(block->nextNormal, block, fa);
    if(block->nextBranch){
        block->nextBranch->from.erase(block);
        block->nextBranch->from.insert(fa);
        changePhiFrom(block->nextBranch, block, fa);
    }
    return true;
}

void BlockPruner::applyBlock(pBlock block){
    if(checkRemoveEmptyBlock(block))
        deleted.push_back(block);
}

ConstBroadcast::ConstBroadcast(){
    triggers.push_back(new BlockPruner());
}

void ConstBroadcast::setConstState(pBlock block, pIRObj obj){
    if(!obj)return;
    auto scalObj = dynamic_pointer_cast<IRScalValObj>(obj);
    if(!scalObj)return;
    if(scalObj->fa != nullptr)return;
    // immediate number
    if(scalObj->isConstant() && !scalObj->isIdent){
        scalObj->constState = IR_CONST;
    }else if(auto defIr = scalObj->defStruction){
        int constState = IR_NAC;
        int value = 0;
        // if( = dynamic_pointer_cast<SysYIR>(scalObj->defStruction)){
            // define in normal struction
        switch(defIr->type){
            case IRType::DEF:
                constState = IR_CONST;
                break;
            case IRType::PHI:
                for(auto& [from, use]: block->phiList.at(scalObj)){
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
        scalObj->constState = constState;
        if(constState == IR_CONST){
            scalObj->value = value;
            scalObj->defStruction = nullptr;
            scalObj->useStructions.clear();
            scalObj->name = to_string(value);
            scalObj->isConst = true;
            scalObj->isIdent = false;
            changed = true;
        }
    }
}

void ConstBroadcast::applyBlock(pBlock block){
    for(auto& ir: block->structions){
        if(!ir->removedMask)
            setConstState(block, ir->target);
    }
}

CodeCleaner::CodeCleaner(){
    triggers.push_back(new BlockPruner());
}

void CodeCleaner::checkObjUse(pIRObj obj){
    if(!obj)return;
    auto scalObj = dynamic_pointer_cast<IRScalValObj>(obj);
    if(!scalObj)return;
    if(scalObj->fa != nullptr)return;
}

void CodeCleaner::applyBlock(pBlock block){
    for(auto& ir: block->structions){
        if(!ir->removedMask){
            checkObjUse(ir->target);
        }
    }
    if(block->branchVal){
        checkObjUse(block->branchVal);
    }
}