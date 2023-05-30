
#include "SysYIR.h"

int IRValObj::tmpValId = 0;
int IRBlock::masterId = 0;
int IRBlock::branchId = 0;
int IRBlock::loopId = 0;
int IRStrValObj::constStrId = 0;

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
    for(auto &ir: structions) {
        // os << *ir.get() << "\\|";//std::endl;
        os << *ir.get() << std::endl;
    }
    // }
    // os << "\"];"<<endl;
    //cfg
    // for(auto p: from){
    //     os << p->name << " -> " << name << ";" << endl;
    // }
    //dom
    // if(domFa != nullptr)
    //     os << domFa->name << " -> " << name << "[color=\"red\"];" << endl;
    if(nullptr != nextBranch){
        os << "\tIF " << branchVal->name << " GOTO " 
            << nextBranch.get()->name << endl;
    }
    if(nullptr != nextNormal)
        os << "\tGOTO " << nextNormal.get()->name << endl;
    // else
    //     os << "\tEND" << endl;
}

void IRFunc::print(std::ostream& os) const{
    os << name << ":" << endl;
    for(auto blk: blocks) {
        os << *blk.get();
    }
}
