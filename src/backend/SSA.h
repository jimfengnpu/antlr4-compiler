#ifndef SSA_H
#define SSA_H
#include <deque>

#include "IRProcessor.h"

class SSAMaker : public IRProcessor {
    map<pBlock, map<pIRValObj, pIRValObj> > renamedObj;
    map<pBlock, map<pIRValObj, pIRValObj> > phiOrigin;
    map<pBlock, map<pIRValObj, map<pBlock, pIRValObj> > > phiList;
    map<pIRValObj, int> renamedId;
    vector<pBlock> visitStack;

   public:
    SSAMaker();
    // rename
    virtual pBlock visit(pBlock block);
    string getNewName(pIRValObj obj) {
        return obj->name + "." + to_string(renamedId[obj]++);
    }
    void fillSuccPhi(pBlock block, pBlock from);
    virtual void apply(Prog& prog) {
        map<pIRValObj, set<pBlock> > phiDef;  // define point
        set<pIRValObj> phiUse;  // val used between blocks (union of useObj)
        map<pBlock, bool>
            phiFlag;  // if block has phi for certain obj(that in loop)
        for (auto& func : prog.functions) {
            if (func->entry) {
                // init
                renamedObj.clear();
                renamedId.clear();
                visitStack.clear();
                phiUse.clear();
                phiDef.clear();
                phiOrigin.clear();
                phiList.clear();
                // insert phi
                for (auto b : func->blocks) {
                    for (auto& obj : b->defObj) {
                        if (toScal(obj)) {
                            phiDef[obj].insert(b);
                        }
                    }
                    phiUse.insert(b->useObj.begin(), b->useObj.end());
                }
                for (auto& obj : phiUse) {
                    phiFlag.clear();
                    auto& blocks = phiDef[obj];
                    while (blocks.size()) {
                        pBlock b = *(blocks.begin());
                        blocks.erase(b);
                        for (auto df : b->domFrontier) {
                            if (!phiFlag[df] &&
                                df->liveIn.find(obj) != df->liveIn.end()) {
                                phiFlag[df] = true;
                                auto phiIR =
                                    df->insertIR(IRType::PHI, obj, nullptr,
                                                 nullptr, df->irHead);
                                phiIR->block = df;
                                blocks.insert(df);
                            }
                        }
                    }
                }
                // rename
                // rename func param
                for (auto& param : func->params) {
                    pIRScalValObj obj = toScal(param);
                    if (obj) {
                        auto newObj = make_shared<IRScalValObj>(*obj.get());
                        newObj->name = getNewName(obj);
                        param = newObj;
                        renamedObj[func->entry][obj] = newObj;
                    }
                }
                visit(func->entry);
                for (auto b : func->blocks) {
                    for (auto ir = b->irHead; ir != nullptr; ir = ir->next) {
                        if (ir->type == IRType::PHI) {
                            auto origin = phiOrigin[b][ir->target];
                            for (auto [from, use] : phiList[b][origin]) {
                                assert(use != nullptr);
                                b->phiList[ir->target][from] = use;
                            }
                        } else
                            break;
                    }
                }
            }
        }
        addTriggers();
    }
    pIRValObj findUsingObj(pIRValObj origin);
    pIRObj renameObj(pIRObj operand, pSysYIR useSource);
};

class SSAFinalizer : public IRProcessor {
   public:
    SSAFinalizer() {}
    virtual void apply(Prog& prog) {
        // possibly add new block in the iteration,
        // use another container here to avoid change during loop
        set<pBlock> newBlocks;
        for (auto& func : prog.functions) {
            newBlocks.clear();
            for (auto block : func->blocks) {
                for (auto ir = block->irHead; ir != nullptr; ir = ir->next) {
                    if (ir->type == IRType::PHI) {
                        auto phiDefObj = ir->target;
                        for (auto& f : block->from) {
                            pBlock insertBlock = f, newBlock = nullptr;
                            // if predecessor(f) has defined phi val in live
                            // out, then add another bb insert assign statement
                            // to avoid lost copy
                            if (f->liveOut.find(phiDefObj) !=
                                f->liveOut.end()) {
                                newBlock = make_shared<IRBlock>(IR_NORMAL);
                                newBlock->finishBB(block);
                                newBlocks.insert(newBlock);
                                if (f->nextBranch == block) {
                                    f->nextBranch = newBlock;
                                } else {
                                    f->nextNormal = newBlock;
                                }
                                insertBlock = newBlock;
                            }
                            pSysYIR tail = nullptr;
                            if (insertBlock->branchVal) {
                                tail = insertBlock->irTail;
                            }
                            insertBlock->insertIR(IRType::ASSIGN, phiDefObj,
                                                  block->phiList[phiDefObj][f],
                                                  nullptr, tail);
                        }
                        block->remove(ir);
                    }
                }
            }
            func->blocks.insert(newBlocks.begin(), newBlocks.end());
        }
    }
};
#endif
