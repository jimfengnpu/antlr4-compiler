
#include "SysYIR.h"

int IRValObj::tmpValId = 0;
int IRBlock::masterId = 0;
int IRBlock::branchId = 0;
int IRBlock::loopId = 0;
int IRStrValObj::constStrId = 0;

int CalConstExp(IRType type, int exp1Val, int exp2Val){
    int value = 0;
    switch (type)
        {
            case IRType::ASSIGN:
                value = exp1Val;break;
            case IRType::ADD:
                value = exp1Val + exp2Val;break;
            case IRType::SUB:
                value = exp1Val - exp2Val;break;
            case IRType::MUL:
                value = exp1Val * exp2Val;break;
            case IRType::DIV:
                if(exp2Val == 0)throw runtime_error("divided by zero");
                value = exp1Val / exp2Val;break;
            case IRType::MOD:
                if(exp2Val == 0)throw runtime_error("divided by zero");
                value = exp1Val % exp2Val;break;
            case IRType::NEG:
                value = - exp1Val;break;
            case IRType::NOP:
                value = exp1Val;break;
            case IRType::NOT:
                value = exp1Val?0:1;break;
            case IRType::EQ:
                value = (exp1Val == exp2Val)?1:0;break;
            case IRType::NEQ:
                value = (exp1Val != exp2Val)?1:0;break;
            case IRType::LT:
                value = (exp1Val < exp2Val)?1:0;break;
            case IRType::GT:
                value = (exp1Val > exp2Val)?1:0;break;
            case IRType::LE:
                value = (exp1Val <= exp2Val)?1:0;break;
            case IRType::GE:
                value = (exp1Val >= exp2Val)?1:0;break;            
            default:
                break;
        }
    return value;
}

void IRObj::print(std::ostream& os) const{
    os << "$" << name;
}

void IRValObj::print(std::ostream& os) const{
    IRObj::print(os);
}

void IRScalValObj::print(std::ostream& os) const{
    // if(fa){
    //     os << *fa.get();
    //     os << "[" << offset <<"]";
    // }else {
    IRObj::print(os);
    
    if(!fa && isConst && !isIdent){
        os << ":" << value;
    }
}

void IRArrValObj::print(std::ostream& os) const{
    IRObj::print(os);
    os << "([" << size << "])";
    for(auto& [off, val]: value) {
        os << *val.get();
    }
}

void IRStrValObj::print(std::ostream& os) const{
    IRObj::print(os);
    os << value;
}

void SysYIR::print(std::ostream& os) const{
    os << IRTypeName(type);
    if(target != nullptr)
        os << " " << target.get()->name;
    if(opt1 != nullptr)
        os << ", " << opt1.get()->name;
    if(opt2 != nullptr)
        os << ", " << opt2.get()->name;
}

void IRBlock::print(std::ostream& os) const{
    os << name << ":\n";
    // os << name << "[label=\"" << name << " |";
    // if(structions.size() > 4){ 
    //     os << *structions[0].get() <<"\\|";
    //     os << *structions[1].get() <<"\\|...\\|";
    //     os << *structions[structions.size() -1].get() <<"\\|";
    // }else{
    os << "live in:";
    for(auto& p: liveIn){
        if(p)
        os << " " << p->name;
    }
    os << endl;
    os << "live out:";
    for(auto& p: liveOut){
        if(p)
        os << " " << p->name;
    }
    os << endl;
    for(auto& [obj, vec]: phiList){
        os << "\tPHI " << phiObj.at(obj)->name;
        for(auto f: vec){
            os << " ("<< f.first->name << ")"<<f.second->name<<" ";
        }
        os << endl;
    }
    for(auto &ir: structions) {
        // os << *ir.get() << "\\n";
        os << "\t" << *ir.get() << std::endl;
    }
    // }
    if(nullptr != nextBranch){
        os << "\tIF " << branchVal->name << " GOTO " 
            << nextBranch.get()->name << endl;
    }
    if(nullptr != nextNormal)
        os << "\tGOTO " << nextNormal.get()->name << endl;
    // else
    //     os << "\tEND" << endl;
    // os << "\"];"<<endl;
    // cfg
    for(auto p: from){
        os << p->name << " -> " << name << ";" << endl;
    }
    // dom
    if(domFa != nullptr)
        os << domFa->name << " -> " << name << "[color=\"red\"];" << endl;
    os << "df:";
    for(auto& df: domFrontier){
        os << " " << df->name;
    }
    os << endl;
}

void IRFunc::print(std::ostream& os) const{
    os << name << ":" << endl;
    for(auto blk: blocks) {
        os << *blk.get();
    }
}
