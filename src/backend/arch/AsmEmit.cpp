#include "AsmEmit.h"

void AsmEmitter::emitData(SymbolTable* table) {
    for (auto [s, v] : table->symbols) {
        if (auto val = toVal(v)) {
            auto scal = toScal(val);
            if (scal) {
                fout << "\t" << ((scal->isConst) ? SEC_RO : SEC_RW) << endl;
                fout << "\t" << ASM_DECL(scal->name) << endl;
                fout << scal->name << ":\n";
                int value = runner->getValue(scal);
                fout << "\t" << ASM_DATA_VAL << " " << to_string(value) << endl;
            } else if (auto arr = dynamic_pointer_cast<IRArrValObj>(val)) {
                fout << "\t" << ((arr->isConst) ? SEC_RO : SEC_RW) << endl;
                fout << "\t" << ASM_DECL(arr->name) << endl;
                fout << arr->name << ":\n";
                int size = arr->size;
                int zeroSize = 0;
                int addr = runner->globalData.frameData[arr];
                int i = addr;
                for (auto itr = runner->addr2val.lower_bound(addr);
                     itr != runner->addr2val.end() && itr->first - addr < size;
                     itr++) {
                    zeroSize += itr->first - i;
                    i = itr->first + 1;
                    int value = itr->second;
                    if (value) {
                        if (zeroSize) {
                            fout << "\t" << ASM_DATA_ZERO << " "
                                 << to_string(memByteAlign * zeroSize) << endl;
                            zeroSize = 0;
                        }
                        fout << "\t" << ASM_DATA_VAL << " " << to_string(value)
                             << endl;
                    } else {
                        zeroSize++;
                    }
                }
                zeroSize += addr + size - i;
                if (zeroSize) {
                    fout << "\t" << ASM_DATA_ZERO << " "
                         << to_string(memByteAlign * zeroSize) << endl;
                }
            }
        }
    }
}
string AsmEmitter::printAsmOp(vReg* reg) {
    if (reg->regType == REG_IMM) {
        return to_string(reg->immVal);
    }
    if (reg->var) {
        return reg->var->name;
    }
    if (reg->regType == REG_R) {
        return archInfo->regs[reg->regId];
    }
    int off = reg->stackMemOff;
    int regId = reg->regId;
    for (auto v = reg->ref; v; v = v->ref) {
        off += v->stackMemOff;
        regId = v->regId;
    }
    return to_string(off) + "(" +
           archInfo->regs[regId == -1 ? archInfo->stackPointerRegId : regId] +
           ")";
}

void AsmEmitter::printAsm(ASMInstr* instr) {
    fout << "\t" << instr->name;
    bool start = false;
    if (instr->name != callOp) {
        deque<vReg*> ops{};
        for(auto p:instr->op){
            ops.push_back(p);
        }
        if(instr->targetOp){
            if(instr->name == storeOp){
                ops.push_back(instr->targetOp);
            }else{
                ops.push_front(instr->targetOp);
            }
        }
        if (ops.size()) {
            for (vReg* op : ops) {
                fout << (start ? ", " : "\t") << printAsmOp(op);
                start = true;
            }
        }
    }
    if (instr->label) {
        fout << (start ? ", " : "\t") << instr->label->name;
    }
    fout << endl;
}

void AsmEmitter::emitFunc(pIRFunc func) {
    fout << "\t" << SEC_RX << endl;
    fout << "\t" << ASM_DECL(func->name) << endl;
    fout << func->name << ":\n";
    for (auto s : func->initInstrs) {
        printAsm(&s);
    }
    for (auto block = func->entry; block; block = block->asmNextBlock) {
        if (block != func->entry) {
            fout << block->name << ":\n";
        }
        for (auto ir = block->irHead; ir; ir = ir->next) {
            for (auto s = ir->asmHead; s; s = s->next) {
                printAsm(s);
            }
        }
    }
}