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
    virtual void apply(ASTVisitor& visitor){
        triggers.push_back(new LiveCalculator());
        addTriggers();
        for(auto& f: visitor.functions){
            if(f->entry){
                for(pBlock block: f->blocks){
                    visit(block);
                }
                pBlock last=nullptr;
                map<pBlock, bool> visited{};
                vector<pBlock> vec{};
                visited[f->entry] = true;
                blocks.push(f->entry);
                while(blocks.size())
                {
                    pBlock block = blocks.front();
                    if(last){
                        last->asmNextBlock = block;
                    }
                    blocks.pop();
                    vec.clear();
                    archInfo->matchBlockEnd(block, vec);
                    for(auto b: vec){
                        if(!visited[b]){
                            visited[b] = true;
                            blocks.push(b);
                        }
                    }
                }
            }
        }
    }
};

#endif