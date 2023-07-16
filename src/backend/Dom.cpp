#include "Dom.h"

pBlock DomMaker::find(pBlock p) {
    // 并不经典的并查集函数 (tarjan算法中的魔改版)
    if (setFa[p] == p) return p;
    pBlock r = find(setFa[p]);
    if (sdno[setV[setFa[p]]] < sdno[setV[p]]) setV[p] = setV[setFa[p]];
    return setFa[p] = r;
}

void DomMaker::makeDom(pIRFunc func) {
    // tarjan 的 dom 树快速算法, 不明觉厉
    pBlock p;
    visitId = 0;
    dfn.clear();
    sdno.clear();
    idom.clear();
    dfsFa.clear();
    bucket.clear();
    visitBlocks.clear();
    setFa.clear();
    setV.clear();
    for (auto p : func->blocks) {
        setFa[p] = p;
        setV[p] = p;
        p->domChild.clear();
        p->domFrontier.clear();
        p->domFa = nullptr;
    }
    visit(func->entry);
    for (auto ip = visitBlocks.rbegin(); ip + 1 != visitBlocks.rend(); ip++) {
        p = *ip;
        for (auto pre : p->from) {
            if (dfn[pre]) {
                sdno[p] = min(sdno[p], sdno[eval(pre)]);
            }
        }
        bucket[visitBlocks[sdno[p] - 1]].push_back(p);
        pBlock fa = setFa[p] = dfsFa[p];
        for (auto v : bucket[fa]) {
            pBlock u = eval(v);
            idom[v] = sdno[u] == sdno[v] ? fa : u;
        }
        bucket[fa].clear();
    }
    for (int i = 1; i < visitId; i++) {
        p = visitBlocks[i];
        idom[p] = idom[p] == visitBlocks[sdno[p] - 1] ? idom[p] : idom[idom[p]];
        p->domFa = idom[p];
        idom[p]->domChild.insert(p);
    }
    for (int i = 0; i < visitId; i++) {
        p = visitBlocks[i];
        if (p->from.size() > 1) {
            for (pBlock pp : p->from) {
                pBlock runner = pp;
                while (runner && runner != p->domFa) {
                    runner->domFrontier.insert(p);
                    runner = runner->domFa;
                }
            }
        }
    }
}