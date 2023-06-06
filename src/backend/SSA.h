#pragma once
#include "../common/IRProcessor.h"
#include <deque>

class SSAMaker: public IRProcessor{
    map<pBlock, bool> visited;
    map<pBlock, map<pIRValObj, pIRValObj> > renamedObj;
    map<pIRValObj, int> renamedId;
    vector<pBlock> visitStack;
public:
    SSAMaker(){}
    // rename
    virtual pBlock visit(pBlock block);
    string getNewName(pIRValObj obj){
        return obj->name + "." + to_string(renamedId[obj]++);
    }
    void fillSuccPhi(pBlock block, pBlock from);
    virtual void apply(ASTVisitor& visitor){
        map<pIRValObj, set<pBlock> > phiDef;
        set<pIRValObj> phiUse;
        map<pBlock, bool> phiFlag;
        for(auto& func: visitor.functions){
            if(func->entry){
                //init
                renamedObj.clear();
                visited.clear();
                renamedId.clear();
                visitStack.clear();
                phiUse.clear();
                phiDef.clear();
                //insert phi
                for(auto b: func->blocks){
                    for(auto& obj: b->defObj){
                        if(auto scalObj = dynamic_pointer_cast<IRScalValObj>(obj)){
                            phiDef[obj].insert(b);
                        }
                    }
                    phiUse.insert(b->useObj.begin(), b->useObj.end());
                }
                for(auto& obj: phiUse){
                    phiFlag.clear();
                    auto& blocks = phiDef[obj];
                    while(blocks.size()){
                        pBlock b = *(blocks.begin());
                        blocks.erase(b);
                        for(auto df: b->domFrontier){
                            if(!phiFlag[df]){
                                phiFlag[df] = true;
                                df->phiOrigin.push_back(obj);
                                blocks.insert(df);
                            }
                        }
                    }
                }
                //rename
                for(auto& param: func->params){
                    pIRScalValObj obj = dynamic_pointer_cast<IRScalValObj>(param);
                    if(obj){
                        auto newObj = make_shared<IRScalValObj>(*obj.get());
                        newObj->name = getNewName(obj);
                        param = newObj;
                        renamedObj[func->entry][obj] = newObj;
                    }
                }
                visit(func->entry);
            }
        }
    }
    pIRValObj findUsingObj(pIRValObj origin);
    pIRObj renameObj(pBlock block, pIRObj operand);
};

class SSAFinalizer: public IRProcessor{
public:
    SSAFinalizer(){}
    virtual pBlock visit(pBlock block);
    virtual void apply(ASTVisitor& visitor){
        set<pBlock> newBlocks;
        for(auto& func: visitor.functions){
            newBlocks.clear();
            for(auto block: func->blocks){
                for(auto& origin: block->phiOrigin){
                    for(auto& f: block->from){
                        pBlock insertBlock = f, newBlock = nullptr;
                        if(f->liveOut.find(block->phiObj[origin])!=f->liveOut.end()){
                            newBlock = make_shared<IRBlock>(IR_NORMAL);
                            newBlock->finishBB(block);
                            newBlocks.insert(newBlock);
                            if(f->nextBranch == block){
                                f->nextBranch = newBlock;
                            }else{
                                f->nextNormal = newBlock;
                            }
                            insertBlock = newBlock;
                        }
                        insertBlock->insertIR(
                            IRType::ASSIGN, block->phiObj[origin], 
                            block->phiList[origin][f], nullptr);
                    }
                }
            }
            func->blocks.insert(newBlocks.begin(), newBlocks.end());
        }
    }
};