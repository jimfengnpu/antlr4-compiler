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
                for (int i = 0; i < size; i++) {
                    int value = runner->addr2val[addr + i];
                    if (value) {
                        if (zeroSize) {
                            fout << "\t" << ASM_DATA_ZERO << " "
                                 << to_string(archInfo->memByteAlign * zeroSize)
                                 << endl;
                            zeroSize = 0;
                        }
                        fout << "\t" << ASM_DATA_VAL << " " << to_string(value)
                             << endl;
                    } else {
                        zeroSize++;
                    }
                }
                if (zeroSize) {
                    fout << "\t" << ASM_DATA_ZERO << " "
                         << to_string(archInfo->memByteAlign * zeroSize)
                         << endl;
                }
            }
        }
    }
}
string AsmEmitter::printAsmOp(vReg* reg) {
    if (reg->regType == REG_R) {
        return archInfo->regs[reg->regId];
    }
    if (reg->regType == REG_IMM) {
        return to_string(reg->immVal);
    }
    int off = reg->stackMemOff;
    if (reg->var && reg->var->scopeSymbols &&
        reg->var->scopeSymbols->isGlobal) {
        return reg->var->name;
    }
    return to_string(off) + "(" + archInfo->regs[archInfo->stackPointerRegId] +
           ")";
}

void AsmEmitter::printAsm(ASMInstr* instr) {
    fout << "\t" << instr->name;
    bool start = false;
    if (instr->op.size()) {
        for (vReg* op : instr->op) {
            fout << (start ? ", " : "\t") << printAsmOp(op);
            start = true;
        }
    }
    if (instr->jTarget) {
        fout << (start ? ", " : "\t") << instr->jTarget->name;
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