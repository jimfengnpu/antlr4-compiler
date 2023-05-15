
#include "SysYIR.h"

void IRObj::print(std::ostream& os) const{
    os << "$" << name;
}

void IRValObj::print(std::ostream& os) const{
    IRObj::print(os);
}

void IRScalValObj::print(std::ostream& os) const{
    if(fa){
        // os << *fa.get();
        // os << "[" << offset <<"]";
    }else {
        IRObj::print(os);
    }
    if(isConst && !isIdent){
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

void SysYIR::print(std::ostream& os) const{
    os << IRTypeName(type);
    os << " " << *target.get() << ", " << *opt1.get();
    if(opt2 != nullptr){
        os << ", " << *opt2.get();
    }
}

void IRBlock::print(std::ostream& os) const{
    os << name << ":\n";
    for(auto &ir: structions) {
        os << "\t" << *ir.get() << std::endl;
    }
    if(nullptr != nextBranch){
        os << "\tIF " << *branchVal.get() << " GOTO " 
            << nextBranch.get()->name << endl;
    }
    if(nullptr != nextNormal)
        os << "\tGOTO " << nextNormal.get()->name << endl;
    else
        os << "\tEND" << endl;
}

void IRFunc::print(std::ostream& os) const{
    os << name << ":" << endl;
    for(auto blk: blocks) {
        os << *blk.get();
    }
}

