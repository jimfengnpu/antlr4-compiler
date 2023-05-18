
#include "SysYIR.h"

int IRValObj::tmpValId = 0;
int IRBlock::masterId = 0;
int IRBlock::branchId = 0;
int IRBlock::loopId = 0;
int IRStrValObj::constStrId = 0;
#ifdef VAL_IR

inline string idName(const string& origin) {
    string name = origin;
    replace(name.begin(), name.end(), '.', '_');
    return name;
}
void IRObj::print(std::ostream& os) const{
    os << idName(name);
}

void IRValObj::print(std::ostream& os) const{
    os << "int ";
    IRObj::print(os);
}

void IRScalValObj::print(std::ostream& os) const{
    // if(fa){
    //     os << *fa.get();
    //     os << "[" << offset <<"]";
    // }else {
    IRValObj::print(os);
    // }
    // if(!fa && isConst && !isIdent){
    //     os << ":" << value;
    // }
}

void IRArrValObj::print(std::ostream& os) const{
    IRValObj::print(os);
    for(auto d: dims) {
        os << "[" << d << "]";
    }
    // os << "([" << size << "])";
    // for(auto& [off, val]: value) {
    //     os << *val.get();
    // }
}

void SysYIR::print(std::ostream& os) const{
    os << IRTypeName(type);
    os << " " << idName(target->name) << ", " << idName(opt1->name);
    if(opt2 != nullptr){
        os << ", " << idName(opt2->name);
    }
}

void IRBlock::print(std::ostream& os) const{
    os << idName(name) << ":\n";
    auto irIter = structions.begin();
    while(irIter != structions.end()) {
        auto& ir = *irIter;
        switch(ir->type) {
            
            default:
                os << "\t" << *ir.get() << std::endl;
        }
        irIter++;
    }
    if(nullptr != nextBranch){
        os << "\tif(" << idName(branchVal->name) << ") goto " 
            << idName(nextBranch.get()->name) << ";" << endl;
    }
    if(nullptr != nextNormal)
        os << "\tgoto " << idName(nextNormal.get()->name) << ";" << endl;
}

void IRFunc::print(std::ostream& os) const{
    if(returnType == IR_INT) os<< "int ";
    else os << "void ";
    os << name << "(" ;
    auto symIter = symbolTable->symbols.begin();
    for(auto p = params.begin(); p!=params.end();p++) {
        if(p!=params.begin()) os << ", ";
        os << *((*p).get());
        symIter++;
    }
    os << ")" << endl;
    // while(symIter != symbolTable->symbols.end()) {
    //     auto ptr = (symIter->second).get();
    //     os << "\t" << *ptr << ";" << endl;
    //     symIter++;
    // }
    // for(auto blk: blocks) {
    //     os << *blk.get();
    // }
    // os << "\treturn " << idName(returnVal.get()->name) << ";" << endl;
    // os << "}" <<endl;
}
#else
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
    for(auto &ir: structions) {
        os << "\t" << *ir.get() << std::endl;
    }
    if(nullptr != nextBranch){
        os << "\tIF " << branchVal->name << " GOTO " 
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

#endif

