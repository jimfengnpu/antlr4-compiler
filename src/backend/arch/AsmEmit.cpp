#include "AsmEmit.h"

void AsmEmitter::emitData(SymbolTable* table) {
    for (auto [s, v] : table->symbols) {
        if (auto val = toVal(v)) {
            auto scal = toScal(val);
            if (scal && !scal->isConst) {
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

string AsmEmitter::printAsmOp(vReg* reg, bool memType = false) {
    if (reg->regType == REG_IMM) {
        return to_string(reg->immVal);
    }
    if (reg->var) {
        return reg->var->name;
    }
    int regId = reg->regId;
    int off = reg->stackMemOff;
    for (auto v = reg->ref; v; v = v->ref) {
        // if (regId != -1) {
        //     break;
        // }
        off += v->stackMemOff;
        regId = v->regId;
    }
    string s =
        archInfo->regs[regId == -1 ? archInfo->stackPointerRegId : regId];
    if (!memType) {
        return s;
    }
    return to_string(off) + "(" + s + ")";
}

void AsmEmitter::printAsm(ASMInstr* instr) {
    string opName = instr->name;
    if (opName == assignOp && instr->targetOp->regId == instr->op[0]->regId) {
        return;
    }
    fout << "\t" << opName;
    bool start = false;
    if (opName != callOp) {
        deque<vReg*> ops{};
        for (auto p : instr->op) {
            ops.push_back(p);
        }
        int memTypeIdx = -1;
        if (instr->targetOp) {
            if (opName == storeOp || opName == storeDwOp) {
                ops.push_back(instr->targetOp);
                memTypeIdx = 1;
            } else {
                ops.push_front(instr->targetOp);
                if (opName == loadOp || opName == loadDwOp) {
                    memTypeIdx = 1;
                }
            }
        }
        if (int s = ops.size()) {
            for (int i = 0; i < s; i++) {
                fout << (start ? ", " : "\t")
                     << printAsmOp(ops[i], i == memTypeIdx);
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
    for (auto block = func->entry; block; block = block->asmNextBlock) {
        if (block != func->entry) {
            fout << block->name << ":\n";
        } else {
            for (auto s : func->initInstrs) {
                printAsm(s);
            }
        }
        if (block == func->exit) {
            for (auto s : func->exitInstrs) {
                printAsm(s);
            }
        }
        for (auto ir = block->irHead; ir; ir = ir->next) {
            for (auto s = ir->asmHead; s; s = s->next) {
                printAsm(s);
            }
        }
    }
}