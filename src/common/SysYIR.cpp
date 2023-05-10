
#include "SysYIR.h"

int IRObj::tmp_block_id = 0;
int IRObj::tmp_id = 0;
void IRObj::print(std::ostream& os) const{
    os << "$" << name << ":";
    switch(val_type) {
        case IR_INT:
            os << "i";break;
        case IR_VOID:
            os << "v";break;
    }
}

void IRIntValObj::print(std::ostream& os) const{
    if(is_const && (!is_ident)){
        os << value;
    }else{
        if(fa){
            os << fa.get();
            os << "[" << offset <<"]";
        }
        IRObj::print(os);
    }
}

void IRIntArrObj::print(std::ostream& os) const{
    IRObj::print(os);
    os << "([" << size << "])";
}

void SysYIR::print(std::ostream& os) const{
    os << IRTypeName(type);
    os << " " << target << "," << opt1;
    if(opt2 != nullptr){
        os << "," << opt2;
    }
}

void IRBlock::print(std::ostream& os) const{
    os << name << ":\n";
    for(auto &ir: structions) {
        os << "\t" << ir.get() << std::endl;
    }
}

pIRObj SymbolTable::findSymbol(string name) {
    return nullptr;
}

