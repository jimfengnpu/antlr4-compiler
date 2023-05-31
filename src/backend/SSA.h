#pragma once
#include "../common/IRProcessor.h"

class SSAMaker: public IRProcessor{
    map<pBlock, bool> visited;
    map<pBlock, map<pIRValObj, pIRValObj> > renamedObj;
    map<pIRValObj, int> renamedId;
    vector<pBlock> visitStack;
public:
    SSAMaker(){}
    virtual pBlock visit(pBlock block){
        for(auto& ir: block->structions){
            if(ir->type == IRType::ASSIGN){
                auto targ = dynamic_pointer_cast<IRValObj>(ir->target);
                if(!targ->isTmp){
                    for(auto df: block->domFrontier){
                        df->phiFa.push_back(targ);
                    }
                }
            }
        }
        for(pBlock child: block->domChild){
            visit(child);
        }
        return nullptr;
    }
    string getNewName(pIRValObj obj){
        return obj->name + "." + to_string(renamedId[obj]++);
    }
    void fillPostPhi(pBlock block, pBlock from);
    void visitRename(pBlock block);
    virtual void apply(ASTVisitor& visitor){
        for(auto& func: visitor.functions){
            if(func->entry){
                visit(func->entry);
                renamedObj.clear();
                visited.clear();
                renamedId.clear();
                for(auto& param: func->params){
                    pIRScalValObj obj = dynamic_pointer_cast<IRScalValObj>(param);
                    if(obj){
                        auto newObj = make_shared<IRScalValObj>(*obj.get());
                        newObj->name = getNewName(obj);
                        param = newObj;
                        renamedObj[func->entry][obj] = newObj;
                    }
                }
                visitRename(func->entry);
            }
        }
    }
    pIRValObj findUsingObj(pIRValObj origin);
    pIRObj renameObj(pBlock block, pIRObj operand);
};