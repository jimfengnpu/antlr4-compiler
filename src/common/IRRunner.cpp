#include "IRRunner.h"


int IRRunner::callLib(pIRFunc libFunc){
    string name = libFunc->name;
    if(name == "@putint"){
        needNewLine = true;
        fout << getValue(paramsBuf.back());
    }else if(name == "@putch"){
        char c = getValue(paramsBuf.back());
        fout <<c;
        needNewLine = false;
    }else if(name == "@putarray"){
        pIRArrValObj arr = dynamic_pointer_cast<IRArrValObj>(paramsBuf[0]);
        int val, n = getValue(paramsBuf[1]);
        fout << n << ":";
        int addr = getAddr(arr);
        for(int i=0;i<n;i++){
            val = addr2val[addr +i];
            fout << " " << val;
        }
        fout << endl;
        needNewLine = false;
    }else if(name == "@getint"){
        int rt;
        fin >> rt;
        return rt;
    }else if(name == "@getch"){
        char c;
        fin >> noskipws >> c;
        return (int)c;
    }else if(name == "@getarray"){
        pIRArrValObj arr = dynamic_pointer_cast<IRArrValObj>(paramsBuf.back());
        int n, val;
        fin >> n;
        int addr = getAddr(arr);
        for(int i=0;i<n;i++){
            fin >> val;
            addr2val[addr + i] = val;
        }
        return n;
    }
    return 0;
}

pBlock IRRunner::visit(pBlock block){
    #ifdef VAL_IR
        cout << "enter:" << block->name <<endl;
    #endif
    for(auto& ir:block->structions) {
        if(!ir->removedMask)
            runSysY(*(ir));
    }
    if(block->nextBranch && getValue(block->branchVal) != 0)
        return block->nextBranch;
    return block->nextNormal;
}

int IRRunner::runFunc(pIRFunc func){
    pBlock block = func->entry;
    while(block != nullptr){
        block = visit(block);
    }
    int rt = 0;
    if(func->returnVal) rt = getValue(func->returnVal);
    return rt;
}

int IRRunner::getAddr(pIRValObj obj){
    if(obj->fa)return getAddr(obj->fa) + obj->offset;
    int addr;
    bool flag = false;
    if(!frameStack.empty()){
        try{
            addr = frameStack.back()->frameData.at(obj);
            flag = true;
        }catch(...){
        }
    }
    if(!flag){
        try{
            addr = globalData.frameData.at(obj);
        }catch(...){
            // throw runtime_error("no corresponding obj");
            alloc(obj);
            return getAddr(obj);
        }
    }
    return addr;
}

int IRRunner::getValue(pIRObj obj){
    auto valObj = toScal(obj);
    int rt = 0;
    bool flag = false;
    if(valObj->isConst&&(!valObj->isIdent)){
        rt = valObj->value;
        #ifdef VAL_IR
            cout << "const ";
        #endif
    }else{
        int addr = getAddr(valObj);
        #ifdef VAL_IR
        cout << "addr: "<<obj->name << " "<<addr<<" ";
        #endif
        rt = addr2val[addr];
    }
    #ifdef VAL_IR
        cout << "get:"<< valObj;
        if(!valObj->name.empty())cout << "("<< valObj->name<<")";
        cout << " "<< rt << " ";
    #endif
    return rt;
}

void IRRunner::storeValue(pIRValObj obj, int val){
    int addr = getAddr(obj);
    #ifdef VAL_IR
        cout << "addr: "<<obj->name << " "<<addr<<" ";
    #endif
    addr2val[addr] = val;
    #ifdef VAL_IR
        cout << "st "<< obj;
        if(!obj->name.empty())cout << "("<< obj->name<<")";
        cout<< " "<< val<<" ";
    #endif
}

void IRRunner::alloc(pIRValObj obj){
    #ifdef VAL_IR
        cout << "add "<< obj<<"("<< obj->name<<") ";
    #endif
    DataFrame* curFrame = (frameStack.empty())? (&globalData):frameStack.back();
    if(auto val = toScal(obj)){
        curFrame->frameData[val] = addrTop++;
    }else{
        auto arr = dynamic_pointer_cast<IRArrValObj>(obj);
        curFrame->frameData[arr] = addrTop;
        addrTop += arr->size;
    }
}

void IRRunner::operateScalObj(IRType type, pIRObj target, pIRObj opt1, pIRObj opt2){
    pIRScalValObj targ = nullptr;
    int exp1Val, exp2Val = 0;
    int value = 0;
    targ = toScal(target);
    exp1Val = getValue(opt1);
    if(opt2 != nullptr){
        exp2Val = getValue(opt2);
    }
    value = CalConstExp(type, exp1Val, exp2Val);
    storeValue(targ, value);
}
void IRRunner::runSysY(const SysYIR& instr){
    #ifdef VAL_IR
    cout << IRTypeName(instr.type);
    if(instr.target != nullptr)
        cout << " " << instr.target.get()->name;
    if(instr.opt1 != nullptr)
        cout << ", " << instr.opt1.get()->name;
    if(instr.opt2 != nullptr)
        cout << ", " << instr.opt2.get()->name<<endl;
    #endif
    pIRScalValObj targ = nullptr;
    pIRValObj param = nullptr;
    pIRFunc func;
    pIRArrValObj arr, arrTarg;
    int addr;
    switch (instr.type)
    {
    case IRType::ASSIGN:
    case IRType::ADD:
    case IRType::SUB:
    case IRType::MUL:
    case IRType::DIV:
    case IRType::MOD:
    case IRType::EQ:
    case IRType::NEQ:
    case IRType::LT:
    case IRType::GT:
    case IRType::LE:
    case IRType::GE:
    case IRType::NEG:
    case IRType::NOT:
    case IRType::NOP:
        operateScalObj(instr.type, instr.target, instr.opt1, instr.opt2);
        break;
    case IRType::DEF:
        param = dynamic_pointer_cast<IRValObj>(instr.target);
        // // cout << param <<endl;
        alloc(param);
        break;
    case IRType::PARAM:
        param = dynamic_pointer_cast<IRValObj>(instr.opt1);
        paramsBuf.push_back(param);
        break;
    case IRType::CALL:
        targ = toScal(instr.target);
        int rt;
        func = dynamic_pointer_cast<IRFunc>(instr.opt1);
        if(func->symbolTable == nullptr){
            rt = callLib(func);
        }else{
            auto rParam = paramsBuf.rbegin();
            auto frame = new DataFrame();
            for(auto& obj: func->params){
                // *(obj.get()) = *(*(rParam)).get();
                if(auto arg = toScal(*rParam) ){
                    auto valObj = toScal(obj);
                    frame->frameData[valObj] = addrTop++;
                    addr2val[frame->frameData[valObj]] = getValue(arg);
                }else {
                    auto arrArg = dynamic_pointer_cast<IRArrValObj>(*rParam);
                    auto valObj = dynamic_pointer_cast<IRArrValObj>(obj);
                    frame->frameData[valObj] = getAddr(arrArg);
                }
                rParam++;
            }
            frameStack.push_back(frame);
            rt = runFunc(func);
            frameStack.pop_back();
            delete frame;
        }
        paramsBuf.clear();
        if(func->returnType == IR_INT)
            storeValue(targ, rt);
        break;
    case IRType::ARR:
        arr = dynamic_pointer_cast<IRArrValObj>(instr.target);
        arrTarg = dynamic_pointer_cast<IRArrValObj>(instr.opt1);
        arr->offset = getValue(instr.opt2);
        frameStack.back()->frameData[arr] = getAddr(arrTarg) + arr->offset;
        break;
    case IRType::IDX:
        targ = toScal(instr.target);
        // cout << targ->fa<< " " <<endl;
        targ->offset = getValue(instr.opt2);
        break;
    case IRType::RET:
        break;
    default:
        throw runtime_error("unknown ir type");
    }
    #ifdef VAL_IR
        cout <<endl;
    #endif
}