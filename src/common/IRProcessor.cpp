#include "IRProcessor.h"

bool BlockPruner::checkRemoveEmptyBlock(pBlock block){
    if(block->structions.size() > 0)return false;
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