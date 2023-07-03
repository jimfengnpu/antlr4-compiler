#include "Structure.h"

int IRValObj::tmpValId = 0;
int IRBlock::masterId = 0;
int IRBlock::branchId = 0;
int IRBlock::loopId = 0;
int IRStrValObj::constStrId = 0;

int CalConstExp(IRType type, int exp1Val, int exp2Val) {
    int value = 0;
    switch (type) {
        case IRType::ASSIGN:
            value = exp1Val;
            break;
        case IRType::ADD:
            value = exp1Val + exp2Val;
            break;
        case IRType::SUB:
            value = exp1Val - exp2Val;
            break;
        case IRType::MUL:
            value = exp1Val * exp2Val;
            break;
        case IRType::DIV:
            if (exp2Val == 0) throw runtime_error("divided by zero");
            value = exp1Val / exp2Val;
            break;
        case IRType::MOD:
            if (exp2Val == 0) throw runtime_error("divided by zero");
            value = exp1Val % exp2Val;
            break;
        case IRType::SL:
            value = exp1Val << exp2Val;
            break;
        case IRType::SR:
            value = exp1Val >> exp2Val;
            break;
        case IRType::NEG:
            value = -exp1Val;
            break;
        case IRType::NOP:
            value = exp1Val;
            break;
        case IRType::NOT:
            value = exp1Val ? 0 : 1;
            break;
        case IRType::EQ:
            value = (exp1Val == exp2Val) ? 1 : 0;
            break;
        case IRType::NEQ:
            value = (exp1Val != exp2Val) ? 1 : 0;
            break;
        case IRType::LT:
            value = (exp1Val < exp2Val) ? 1 : 0;
            break;
        case IRType::GT:
            value = (exp1Val > exp2Val) ? 1 : 0;
            break;
        case IRType::LE:
            value = (exp1Val <= exp2Val) ? 1 : 0;
            break;
        case IRType::GE:
            value = (exp1Val >= exp2Val) ? 1 : 0;
            break;
        default:
            break;
    }
    return value;
}

void IRObj::print(std::ostream &os) const { os << "$" << name; }

void IRValObj::print(std::ostream &os) const { IRObj::print(os); }

void IRScalValObj::print(std::ostream &os) const {
    // if(fa){
    //     os << *fa.get();
    //     os << "[" << offset <<"]";
    // }else {
    IRObj::print(os);

    if (!fa && isConst && !isIdent) {
        os << ":" << value;
    }
}

void IRArrValObj::print(std::ostream &os) const {
    IRObj::print(os);
    os << "([" << size << "])";
    for (auto &[off, val] : value) {
        os << *val.get();
    }
}

void IRStrValObj::print(std::ostream &os) const {
    IRObj::print(os);
    os << value;
}

void SysYIR::print(std::ostream &os) const {
    os << IRTypeName(type);
    if (target != nullptr) os << " " << target.get()->name;
    if (opt1 != nullptr) os << ", " << opt1.get()->name;
    if (opt2 != nullptr) os << ", " << opt2.get()->name;
    // if(auto scal=toScal(opt2)){
    //     if(scal->constState==IR_CONST)
    //     os << "(" << scal->value<<")";
    // }
}

ASMInstr *SysYIR::addASMBack(ASMInstr *instr, ASMInstr *end) {
    if (nullptr == end) end = asmTail;
    if (instr != nullptr) {
        if (!asmHead) asmHead = instr;
        if (end) {
            if (end->next) {
                end->next->prev = instr;
                instr->next = end->next;
            }
            end->next = instr;
        }
        instr->prev = end;
        if (end == asmTail) {
            asmTail = instr;
        }
        asmInstrs.push_back(instr);
        instr->ir = this;
    }
    return instr;
}

ASMInstr *SysYIR::addASMFront(ASMInstr *instr, ASMInstr *before) {
    if (before == nullptr) before = asmHead;
    if (instr != nullptr) {
        if (!asmTail) asmTail = instr;
        if (before) {
            if (before->prev) {
                before->prev->next = instr;
                instr->prev = before->prev;
            }
            before->prev = instr;
        }
        instr->next = before;
        if (before == asmHead) {
            asmHead = instr;
        }
        asmInstrs.push_front(instr);
        instr->ir = this;
    }
    return instr;
}

void IRBlock::print(std::ostream &os) const {
#ifdef VAL_CFGDOM
    os << name << "[label=\"" << name << " |";
#else
    os << "\n" << name << ":";
#ifdef VAL_LIVE
    os << "live in:";
    for (auto &p : liveIn) {
        if (p) os << " " << p->name;
    }
    os << endl;
    os << "live out:";
    for (auto &p : liveOut) {
        if (p) os << " " << p->name;
    }
    os << endl;
    os << "def:";
    for (auto &p : defObj) {
        if (p) os << " " << p->name;
    }
    os << endl;
    os << "use:";
    for (auto &p : useObj) {
        if (p) os << " " << p->name;
    }
    os << endl;
    os << "df:";
    for (auto &df : domFrontier) {
        os << " " << df->name;
    }
    os << endl;
    os << "domChild:";
    for (auto &child : domChild) {
        os << " " << child->name;
    }
#endif
#endif
    for (auto ir = irHead; ir != nullptr; ir = ir->next) {
#ifdef VAL_CFGDOM
        os << "\\n";
#else
        os << "\n\t";
#endif
        os << *ir.get();
        if (ir->type == IRType::PHI) {
            for (auto &[from, use] : phiList.at(ir->target)) {
                os << " (" << from->name << ")" << use->name << " ";
            }
        }
        if (ir->type == IRType::BR) {
            assert(nextBranch != nullptr);
            os << " GOTO " << nextBranch.get()->name;
        }
        if (ir == irHead) {
            os << " << H";
        }
        if (ir == irTail) {
            os << " << T";
        }
        if (!ir->asmRemovedMask) {
            for (auto ins = ir->asmHead; ins; ins = ins->next) {
                os << "\t" << ins->name;
            }
        } else {
            os << "--m";
        }
    }

    if (nullptr != nextNormal) {
#ifdef VAL_CFGDOM
        os << "\\n";
#else
        os << "\n\t";
#endif
        os << "GOTO " << nextNormal.get()->name;
    }
// cfg
#ifdef VAL_CFGDOM
    os << "\"];" << endl;
    for (auto p : from) {
        os << p->name << " -> " << name << ";" << endl;
    }
    // dom
    if (domFa != nullptr)
        os << domFa->name << " -> " << name << "[color=\"red\"];" << endl;
#endif
}

pSysYIR IRBlock::insertIR(IRType type, pIRValObj t, pIRObj op1, pIRObj op2,
                          pSysYIR ir) {
    auto newIR = make_shared<SysYIR>(type, t, op1, op2);
    if (ir == nullptr) {
        ir = branchIR;
    }
    if (ir != nullptr) {
        newIR->prev = ir->prev;
        if (ir->prev) {
            ir->prev->next = newIR;
        }
        ir->prev = newIR;
    } else {
        newIR->prev = irTail;
        if (irTail) {
            irTail->next = newIR;
        }
    }
    newIR->next = ir;
    if (ir == branchIR) {
        irTail = newIR;
    }
    if (ir == irHead) {
        irHead = newIR;
    }
    structions.push_back(newIR);
    return newIR;
}

bool IRBlock::finishBB(pBlock next_normal, pBlock next_branch,
                       pIRScalValObj branch_val) {
    // 此基本块如果已经结束过，不应覆盖原有值
    if (nextNormal != nullptr) return false;
    nextNormal = next_normal;
    nextBranch = next_branch;
    branchVal = branch_val;
    if (nullptr != branch_val) {
        branchIR = make_shared<SysYIR>(IRType::BR, nullptr, branchVal, nullptr);
        branchIR->prev = irTail;
        if (irTail) {
            irTail->next = branchIR;
        }
    }
    return true;
}

void IRBlock::remove(pSysYIR ir) {
    if (ir->prev) {
        ir->prev->next = ir->next;
    }
    if (ir->next) {
        ir->next->prev = ir->prev;
    }
    if (ir == irTail) {
        irTail = irTail->prev;
    }
    if (ir == irHead) {
        irHead = irHead->next;
    }
    if (ir == branchIR) {
        branchIR = nullptr;
    }
    ir->removedMask = true;
}

// block structions size (jump excluded)
int IRBlock::size() {
    int cnt = 0;
    for (auto ir = irHead; ir != nullptr; ir = ir->next) {
        if (ir->type == IRType::BR) break;
        cnt++;
    }
    return cnt;
}

int IRBlock::asmLen() {
    int cnt = 0;
    for (auto ir = irHead; ir != nullptr; ir = ir->next) {
        if (!ir->asmRemovedMask) {
            cnt += ir->asmSize();
        }
    }
    return cnt;
}

bool IRBlock::hasPhi() {
    for (auto ir = irHead; ir != nullptr; ir = ir->next) {
        if (ir->type == IRType::PHI) {
            return true;
        } else
            break;
    }
    return false;
}

void IRFunc::print(std::ostream &os) const {
#ifdef VAL_CFGDOM
    os << "#";
#endif
    os << name << ":";
#ifdef VAL_CFGDOM
    os << endl;
#endif
    for (auto blk : blocks) {
        os << *blk.get();
    }
}
