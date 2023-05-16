
#include "SysYIR.h"

#define VAL_IR 1
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
    os << " " << target.get()->name << ", " << opt1.get()->name;
    if(opt2 != nullptr){
        os << ", " << opt2.get()->name;
    }
}

void IRBlock::print(std::ostream& os) const{
    os << idName(name) << ":\n";
    for(auto &ir: structions) {
        os << "\t" << *ir.get() << std::endl;
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
    os << "){" << endl;
    while(symIter != symbolTable->symbols.end()) {
        auto ptr = (symIter->second).get();
        if(ptr == nullptr)
            os << ptr << ";" << endl;
        else 
            os << *ptr << ";" << endl;
        symIter++;
    }
    for(auto blk: blocks) {
        os << *blk.get();
    }
    os << "\treturn " << idName(returnVal.get()->name) << ";" << endl;
    os << "}" <<endl;
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
    // }
    // if(!fa && isConst && !isIdent){
    //     os << ":" << value;
    // }
}

void IRArrValObj::print(std::ostream& os) const{
    IRObj::print(os);
    os << "([" << size << "])";
    // for(auto& [off, val]: value) {
    //     os << *val.get();
    // }
}

void SysYIR::print(std::ostream& os) const{
    os << IRTypeName(type);
    os << " " << target.get()->name << ", " << opt1.get()->name;
    if(opt2 != nullptr){
        os << ", " << opt2.get()->name;
    }
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
    os << "\tRET " << *returnVal.get() << endl;
}

#endif

