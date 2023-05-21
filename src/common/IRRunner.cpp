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
        pIRArrValObj arr = dynamic_pointer_cast<IRArrValObj>(paramsBuf.back());
        int val, n = getValue(paramsBuf[paramsBuf.size() -2]);
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

pBlock IRRunner::run(pBlock block){
    #ifdef VAL_IR
        cout << "enter:" << block->name <<endl;
    #endif
    for(auto& ir:block->structions) {
        runSysY(*(ir));
    }
    if(block->nextBranch && getValue(block->branchVal) != 0)return block->nextBranch;
    return block->nextNormal;
}

int IRRunner::runFunc(pIRFunc func){
    pBlock block = func->entry;
    while(block != nullptr){
        block = run(block);
    }
    int rt = 0;
    if(func->returnVal) rt = getValue(func->returnVal);
    return rt;
}

int IRRunner::getAddr(pIRValObj obj){
    if(obj->fa)return getAddr(obj->fa) + obj->offset;
    int addr;
    try{
        addr = frameStack.back()->frameData.at(obj);
    }catch(...){
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
    auto valObj = dynamic_pointer_cast<IRScalValObj>(obj);
    int addr = getAddr(valObj);
    int rt = 0;
    bool flag = false;
    if(valObj->isConst){
        rt = valObj->value;
        #ifdef VAL_IR
            cout << "const ";
        #endif
    }else{
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
    if(auto val = dynamic_pointer_cast<IRScalValObj>(obj)){
        curFrame->frameData[val] = addrTop++;
    }else{
        auto arr = dynamic_pointer_cast<IRArrValObj>(obj);
        curFrame->frameData[arr] = addrTop;
        addrTop += arr->size;
    }
}

void IRRunner::operateScalObj(IRType type, pIRObj target, pIRObj opt1, pIRObj opt2){
    pIRScalValObj targ = nullptr;
    int exp1Val, exp2Val;
    int value = 0;
    targ = dynamic_pointer_cast<IRScalValObj>(target);
    exp1Val = getValue(opt1);
    if(opt2 != nullptr){
        exp2Val = getValue(opt2);
    }
    switch (type)
    {
        case IRType::ASSIGN:
            value = exp1Val;break;
        case IRType::ADD:
        assert(opt2!= nullptr);
            value = exp1Val + exp2Val;break;
        case IRType::SUB:
        assert(opt2!= nullptr);
            value = exp1Val - exp2Val;break;
        case IRType::MUL:
        assert(opt2!= nullptr);
            value = exp1Val * exp2Val;break;
        case IRType::DIV:
        assert(opt2!= nullptr);
            if(exp2Val == 0)throw runtime_error("divided by zero");
            value = exp1Val / exp2Val;break;
        case IRType::MOD:
        assert(opt2!= nullptr);
            if(exp2Val == 0)throw runtime_error("divided by zero");
            value = exp1Val % exp2Val;break;
        case IRType::NEG:
            value = - exp1Val;break;
        case IRType::NOP:
            value = exp1Val;break;
        case IRType::NOT:
            value = exp1Val?0:1;break;
        case IRType::EQ:
        assert(opt2!= nullptr);
            value = (exp1Val == exp2Val)?1:0;break;
        case IRType::NEQ:
        assert(opt2!= nullptr);
            value = (exp1Val != exp2Val)?1:0;break;
        case IRType::LT:
        assert(opt2!= nullptr);
            value = (exp1Val < exp2Val)?1:0;break;
        case IRType::GT:
        assert(opt2!= nullptr);
            value = (exp1Val > exp2Val)?1:0;break;
        case IRType::LE:
        assert(opt2!= nullptr);
            value = (exp1Val <= exp2Val)?1:0;break;
        case IRType::GE:
        assert(opt2!= nullptr);
            value = (exp1Val >= exp2Val)?1:0;break;            
        default:
            break;
    }
    storeValue(targ, value);
}
void IRRunner::runSysY(const SysYIR& instr){
    pIRScalValObj targ = nullptr;
    pIRValObj param = nullptr;
    pIRFunc func;
    pIRArrValObj arr;
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
        param = dynamic_pointer_cast<IRValObj>(instr.target);
        paramsBuf.push_back(param);
        break;
    case IRType::CALL:
        targ = dynamic_pointer_cast<IRScalValObj>(instr.target);
        int rt;
        func = dynamic_pointer_cast<IRFunc>(instr.opt1);
        if(func->symbolTable == nullptr){
            rt = callLib(func);
        }else{
            auto rParam = paramsBuf.rbegin();
            auto frame = new DataFrame();
            frameStack.push_back(frame);
            for(auto& obj: func->params){
                // *(obj.get()) = *(*(rParam)).get();
                if(auto arg = dynamic_pointer_cast<IRScalValObj>(*rParam) ){
                    auto valObj = dynamic_pointer_cast<IRScalValObj>(obj);
                    int val = getValue(arg);
                    storeValue(valObj, val);
                }else {
                    auto arrArg = dynamic_pointer_cast<IRArrValObj>(*rParam);
                    auto valObj = dynamic_pointer_cast<IRArrValObj>(obj);
                    storeValue(valObj, getValue(arrArg));
                }
                rParam++;
            }
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
        targ = dynamic_pointer_cast<IRScalValObj>(instr.opt1);
        storeValue(arr, getAddr(targ));
        break;
    case IRType::IDX:
        targ = dynamic_pointer_cast<IRScalValObj>(instr.target);
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