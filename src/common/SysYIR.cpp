
#include "SysYIR.h"

int IRObj::tmp_block_id = 0;
int IRObj::tmp_id = 0;
string IRObj::toString() {
    string s;
    if(is_val){
        s += "v";
    }else s += "b";
    switch(val_type) {
        case IR_INT:
            s += "i";break;
        case IR_VOID:
            s += "v";break;
    }

    return string("<" + s +":" + name + ">");
}

string SysYIR::toString() {
    return string(IRTypeName(type) + " " + target.get()->toString() + 
        "," + opt1.get()->toString() + "," + opt2.get()->toString());
}

pIRObj SymbolTable::findSymbol(string name) {
    return nullptr;
}

