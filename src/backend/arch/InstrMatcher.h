#ifndef INSTR_MATCHER_H
#define INSTR_MATCHER_H

#include "IRProcessor.h"
#include "Arch.h"
#include <queue>

class InstrMatcher: public IRProcessor{
    BaseArch* archInfo;
    queue<pBlock> blocks{};
public:
    InstrMatcher(BaseArch* arch):archInfo(arch){}
    virtual pBlock visit(pBlock block);
    virtual void apply(Prog& prog){
        triggers.push_back(new LiveCalculator());
        addTriggers();
        for(auto& f: prog.functions){
            if(f->entry){
                archInfo->prepareFuncParamRegs(f);
                for(pBlock block: f->blocks){
                    visit(block);
                }
                pBlock last=nullptr;
                map<pBlock, bool> visited{};
                vector<pBlock> vec{};
                blocks.push(f->entry);
                while(blocks.size())
                {
                    pBlock block = blocks.front();
                    blocks.pop();
                    vec.clear();
                    if(!visited[block]){
                        visited[block] = true;
                        if(last){
                            last->asmNextBlock = block;
                        }
                        archInfo->matchBlockEnd(block, vec);
                        for(auto b: vec){
                            blocks.push(b);
                        }
                        last = block;
                    }
                }
            }
        }
    }
};

#endif