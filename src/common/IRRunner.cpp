#include "IRRunner.h"


pBlock IRRunner::run(pBlock block){
    for(auto& ir:block->structions) {
        runSysY(*(ir));
    }
    if(block->nextBranch && block->branchVal->value)return block->nextBranch;
    return block->nextNormal;
}

int IRRunner::runFunc(pIRFunc func){
    auto frame = new DataFrame();
    dataStack.push_back(frame);
    pBlock block = func->entry;
    while(block != nullptr){
        block = run(block);
    }
    int rt = 0;
    if(func->returnVal) rt = getValue(func->returnVal);
    dataStack.pop_back();
    delete frame;
    return rt;
}
pIRScalValObj getScalObj(pIRObj obj){
    auto scalObj = dynamic_pointer_cast<IRScalValObj>(obj);
    if(scalObj->fa){
        scalObj = scalObj->fa->findValue(scalObj->offset);
    }
    return scalObj;
}

int IRRunner::getValue(pIRObj obj){
    auto valObj = getScalObj(obj);
    if(valObj->isConst)return valObj->value;
    if(!dataStack.empty()){
        try{
            for(auto frame= dataStack.rbegin();frame!=dataStack.rend();frame++)
            {
                return (*frame)->value.at(valObj);
            }
        }catch(...){}
    }
    try{
        return globalData.value.at(valObj);
    }catch(...){
        throw runtime_error("no corresponding obj");
    }
}

void IRRunner::storeValue(pIRScalValObj obj, int val){
    if(dataStack.empty()){
        globalData.value[obj] = val;
    }else{
        (*dataStack.rbegin())->value[obj] = val;
    }
}

void IRRunner::operateScalObj(IRType type, pIRObj target, pIRObj opt1, pIRObj opt2){
    pIRScalValObj targ = nullptr;
    int exp1Val, exp2Val;
    int value = 0;
    targ = getScalObj(target);
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
    case IRType::PARAM:
        param = dynamic_pointer_cast<IRValObj>(instr.target);
        paramsBuf.push_back(param);
        break;
    case IRType::CALL:
        targ = getScalObj(instr.target);
        func = dynamic_pointer_cast<IRFunc>(instr.opt1);
        if(func->symbolTable == nullptr){
            
        }else{
            auto rParam = paramsBuf.rbegin();
            for(auto& obj: func->params){
                *(obj.get()) = *(*(rParam)).get();
                rParam++;
            }
            dataStack.push_back(new DataFrame());
            run(func->entry);
        }
        break;
    case IRType::ARR:
    case IRType::IDX:
    case IRType::RET:
        break;
    default:
        throw runtime_error("unknown ir type");
    }
}