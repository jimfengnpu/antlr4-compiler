
#include "SysYIR.h"

void IRObj::print(std::ostream& os) const{
    os << "$" << name << ":";
}

void IRIntValObj::print(std::ostream& os) const{
    if(isConst && (!isIdent)){
        os << value;
    }else{
        if(fa){
            os << *fa.get();
            os << "[" << offset <<"]";
        }else{
            IRObj::print(os);
        }
    }
}

void IRIntArrObj::print(std::ostream& os) const{
    IRObj::print(os);
    os << "([" << size << "])";
}

void SysYIR::print(std::ostream& os) const{
    os << IRTypeName(type);
    os << " " << *target.get() << "," << *opt1.get();
    if(opt2 != nullptr){
        os << "," << *opt2.get();
    }
}

void IRBlock::print(std::ostream& os) const{
    os << name << ":\n";
    for(auto &ir: structions) {
        os << "\t" << *ir.get() << std::endl;
    }
}


