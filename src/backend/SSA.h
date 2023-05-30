#pragma once
#include "../common/IRProcessor.h"

class SSAMaker: public IRProcessor{
    map<pBlock, bool> visited;
    map<pBlock, bool> phiFinished;
    map<pBlock, map<pIRValObj, pIRValObj> > renamedObj;
    map<pIRValObj, int> renamedId;
public:
    SSAMaker(){}
    virtual pBlock visit(pBlock block){
        for(auto& ir: block->structions){
            if(ir->type == IRType::ASSIGN){
                auto targ = dynamic_pointer_cast<IRValObj>(ir->target);
                if(!targ->isTmp){
                    for(auto df: block->domFrontier){
                        df->phiFa[targ].push_back(block);
                    }
                }
            }
        }
        for(pBlock child: block->domChild){
            visit(child);
        }
        return nullptr;
    }
    void visitRename(pBlock block);
    virtual void apply(ASTVisitor& visitor){
        for(auto& func: visitor.functions){
            if(func->entry){
                visit(func->entry);
                renamedObj.clear();
                visited.clear();
                phiFinished.clear();
                renamedId.clear();
                visitRename(func->entry);
            }
        }
    }
    pIRValObj findUsingObj(pBlock block, pIRValObj origin);
    pIRObj renameObj(pBlock block, pIRObj operand);
};