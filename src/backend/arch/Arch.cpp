#include "Arch.h"

#if EM_ARCH == EM_RISCV
string storeOp = "sw";
string loadOp = "lw";
string loadAddrOp = "la";
#endif

bool BaseArch::matchIR(pSysYIR ir){
    for(auto matcher: matchers[ir->type]){
        if(int matchSize = matcher(ir)){
            auto maskIr = ir->prev;
            while(nullptr != maskIr && (--matchSize)){
                maskIr->asmRemovedMask = true;
                maskIr = maskIr->prev;
            }
            return true;
        }
    }
    return false;
}

vReg* processStore(pIRValObj obj, deque<ASMInstr*>& instr){
    if(!obj)return nullptr;
    vReg* mReg = obj->reg();
    if(obj->scopeSymbols && obj->scopeSymbols->isGlobal 
    && (mReg->regType == REG_M)){
        mReg = new vReg();
        instr.push_back(new ASMInstr(loadAddrOp, {mReg, obj->reg()}));
    }
    auto scal = toScal(obj);
    if(!scal || scal->regInfo.regType != REG_M){
        instr.clear();
        return mReg;
    }
    auto nReg = new vReg();
    instr.push_back(new ASMInstr(storeOp, {nReg, mReg}));
    return nReg;
}

vReg* processLoad(pIRValObj obj, deque<ASMInstr*>& instr){
    if(!obj)return nullptr;
    vReg* mReg = obj->reg();
    if(obj->scopeSymbols && obj->scopeSymbols->isGlobal 
        && (mReg->regType == REG_M)){
        mReg = new vReg();
        instr.push_back(new ASMInstr(loadAddrOp, {mReg, obj->reg()}));
    }
    auto scal = toScal(obj);
    if(!scal || scal->regInfo.regType != REG_M){
        instr.clear();
        return mReg;
    }
    auto nReg = new vReg();
    instr.push_back(new ASMInstr(loadOp, {nReg, obj->reg()}));
    return nReg;
}


inline bool isImm(pIRScalValObj scal){
    if(!scal)return false;
    if(!scal->isConst)return false;
    return true;
}

inline bool isImm(pIRObj obj){
    return isImm(toScal(obj));
}

ASMInstr* addASM(string name, pSysYIR ir, 
    vector<pIRValObj> ops, pBlock target=nullptr){
    deque<ASMInstr*> ldInstr{};
    deque<ASMInstr*> stInstr{};
    vReg* targ=nullptr;
    if(!target){
        targ = processStore(ir->target, stInstr);
    }
    auto mainInstr = new ASMInstr(name, {targ}, target);
    for(auto op: ops){
        if(op){
            auto regOp = processLoad(op, ldInstr);
            if(ldInstr.size()){
                for(auto ins: ldInstr)
                    ir->addASMBack(ins);
                ldInstr.clear();
            }
            mainInstr->addOp(regOp);
        }
    }
    ir->addASMBack(mainInstr);
    if(stInstr.size()){
        for(auto ins: stInstr)
            ir->addASMBack(ins);
        stInstr.clear();
    }
    return mainInstr;
}

inline bool isImmInLimit(pIRScalValObj obj, int width){
    int lim = 1<<width;
    int v = obj->value + lim/2 ;
    return v >= 0 && v < lim;
}

bool checkDoubleOpImm(pSysYIR ir, pIRScalValObj& immScal, 
    pIRValObj& regObj, bool checkSecOnly=false, 
    bool (*check)(pIRScalValObj)=[](pIRScalValObj obj)->bool{return true;}){
    if(isImm(ir->opt1)&&(!checkSecOnly)){
        immScal = toScal(ir->opt1);
        regObj = toVal(ir->opt2);
    }else if(isImm(ir->opt2)){
        immScal = toScal(ir->opt2);
        regObj = toVal(ir->opt1);
    }else{
        immScal = nullptr;
        regObj = nullptr;
        return false;
    }
    return true;
}

int matchCalImmInstr(string name, pSysYIR ir,
    bool checkSecOnly=false, 
    bool (*check)(pIRScalValObj)=[](pIRScalValObj obj)->bool{
        if(isImmInLimit(obj, 12)){
            obj->setImmRegWithVal(obj->value);
            return true;
        }
        return false;
    })
{
    pIRScalValObj immObj=nullptr;
    pIRValObj regObj=nullptr;
    checkDoubleOpImm(ir, immObj, regObj, checkSecOnly, check);
    if(nullptr != immObj){
        addASM(name, ir, {regObj, immObj});
        return 1;
    }
    return 0;
}

int matchCalInstr(string name, pSysYIR ir){
    addASM(name, ir, { toVal(ir->opt1), toVal(ir->opt2)});
    return 1;
}

pBlock RISCV::matchBlockEnd(pBlock block){
    pBlock brTarget = block->nextBranch;
    pBlock nxTarget = block->nextNormal;
    pSysYIR lastIr = block->irTail;
    map<IRType, string> irBrAsm = {
        {IRType::NOT, "beqz"},
        {IRType::EQ, "beq"},
        {IRType::NEQ, "bne"},
        {IRType::GT, "bgt"},
        {IRType::LT, "blt"},
        {IRType::GE, "bge"},
        {IRType::LE, "ble"}
    };
    map<string, string> oppoBranch= //op a, b =>T else F ===> oppo[op] b, a =>T else F
    {
        {"bgt", "blt"},
        {"blt", "bgt"},
        {"bge", "ble"},
        {"ble", "bge"}
    };
    map<string, string> fllipBranch=//op a, b =>T else F ===> fllip[op] a, b =>F else T
    {
        {"bgt", "ble"},
        {"blt", "bge"},
        {"bge", "blt"},
        {"ble", "bgt"},
        {"beq", "bne"},
        {"bgtz", "blez"},
        {"bltz", "bgez"},
        {"bgez", "bltz"},
        {"blez", "bgtz"},
        {"beqz", "bnez"},
    };
    int mask = 0;
    int cnt = 0;
    if(nullptr != brTarget){
        pSysYIR ir = block->branchIR;
        lastIr = ir;
        pSysYIR brValDef = toVal(ir->opt1)->defStruction;
        assert(toVal(ir->opt1)->defStruction == brValDef);
        string name = irBrAsm[brValDef->type];
        mask = 2;
        pIRScalValObj imm=nullptr;
        pIRValObj reg=nullptr;
        vector<pIRValObj> oprands{};
        if(name.empty()){
            name = "bnez";
            mask = 1;
            oprands.push_back(toVal(ir->opt1));
        }else{
            if(checkDoubleOpImm(brValDef, imm, reg) && imm->value == 0){
                if(brValDef->type==IRType::EQ 
                    || brValDef->type==IRType::NEQ){
                    name = name + "z";
                    oprands.push_back(reg);
                }else{
                    if(imm == brValDef->opt1){
                        name = oppoBranch[name] + "z";
                    }
                    oprands.push_back(reg);
                    oprands.push_back(imm);
                }
            }else{
                oprands.push_back(toVal(brValDef->opt1));
                oprands.push_back(toVal(brValDef->opt2));
            }
        }
        for(pBlock b = brTarget; b; b = b->asmNextBlock){
            cnt += b->asmLen();
        }
        if(cnt > branchBlockASMLimit){
            pBlock t = brTarget;
            brTarget = nxTarget;
            nxTarget = t;
            name = fllipBranch[name];
        }
        addASM(name, lastIr, {oprands.begin(), oprands.end()}, brTarget);
    }
    if(nxTarget){
        addASM("j", lastIr, {}, nxTarget);
    }
    for(auto maskIr=lastIr->prev; maskIr&&((--mask)>0);maskIr=maskIr->prev){
        maskIr->asmRemovedMask = true;
    }
    return brTarget && (cnt == 0)? brTarget : nxTarget;
}

void RISCV::defineArchInfo(){
    stackPointerRegId = REG::sp;
    framePointerRegId = REG::s0;
    memByteAlign = 4;
    frameByteAlign = 16;
    branchBlockASMLimit = 512;
    addGenRegs({

    });
    addMatchers(IRType::ASSIGN,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("li", ir, false, [](pIRScalValObj imm)->bool{
                return true;
            });
            if(imm)return imm;
            return matchCalInstr("mv", ir);
        }
    });
    addMatchers(IRType::ADD,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("addi", ir);
            if(imm)return imm;
            return matchCalInstr("add", ir);
        }
    });
    addMatchers(IRType::SUB,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("addi", ir, true, [](pIRScalValObj imm)->bool{
                if(isImmInLimit(imm, 12)){
                    imm->setImmRegWithVal(-imm->value);
                    return true;
                }
                return false;
            });
            if(imm)return imm;
            return matchCalInstr("sub", ir);
        }
    });
    addMatchers(IRType::MUL,
    {
        [](pSysYIR ir)->int{
            return matchCalInstr("mul", ir);
        }
    });
    addMatchers(IRType::DIV,
    {
        [](pSysYIR ir)->int{
            return matchCalInstr("div", ir);
        }
    });
    addMatchers(IRType::MOD,
    {
        [](pSysYIR ir)->int{
            return matchCalInstr("rem", ir);
        }
    });
    addMatchers(IRType::AND,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("andi", ir);
            if(imm)return imm;
            return matchCalInstr("and", ir);
        }
    });
    addMatchers(IRType::OR,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("ori", ir);
            if(imm)return imm;
            return matchCalInstr("or", ir);
        }
    });
    addMatchers(IRType::SL,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("slli", ir, true);
            if(imm)return imm;
            return matchCalInstr("sll", ir);
        }
    });
    addMatchers(IRType::SR,
    {
        [](pSysYIR ir)->int{
            int imm=matchCalImmInstr("srai", ir, true);
            if(imm)return imm;
            return matchCalInstr("sra", ir);
        }
    });
    addMatchers(IRType::NEG,
    {
        [](pSysYIR ir)->int{
            return matchCalInstr("neg", ir);
        }
    });
    addMatchers(IRType::IDX,
    {
        //opt1: arr, opt2: scal, offset
        [](pSysYIR ir)->int{
            pIRScalValObj immObj=nullptr;
            pIRValObj arrObj=nullptr;
            vReg* obj = toVal(ir->target)->reg();
            if(checkDoubleOpImm(ir, immObj, arrObj, true, [](pIRScalValObj imm)->bool{
                return true;
            })){
                obj->stackMemOff = 4*immObj->value;
            }else{
                matchCalInstr("add", ir);
            }
            obj->regType = REG_M;
            obj->var = toVal(ir->opt1);
            return 1;
        }
    });
    addMatchers(IRType::ARR,
    {
        [](pSysYIR ir)->int{
            matchCalInstr("add", ir);
            return 1;
        }
    });
    addMatchers(IRType::CALL,
    {
        [](pSysYIR ir)->int{
            int paramCnt = 0;
            pSysYIR paramIr = ir->prev;
            while(paramIr && paramIr->type == IRType::PARAM){
                vReg* paramReg = new vReg();
                if(paramCnt < 8){
                    paramReg->regType = REG_R;
                    paramReg->regId = a0 + paramCnt;
                }else{
                    paramReg->regType = REG_M;
                }
                deque<ASMInstr*> ldInstr{};
                vReg* regOp = processLoad(toVal(ir->opt1), ldInstr);
                auto asmInstr = new ASMInstr("mv", {});
                asmInstr->addOp(paramReg);
                asmInstr->addOp(regOp);
                if(ldInstr.size()){
                    for(auto ins: ldInstr)
                        paramIr->addASMBack(ins);
                    ldInstr.clear();
                }
                paramIr->addASMBack(asmInstr);
                paramIr = paramIr->prev;
            }
            pIRFunc func = toFunc(ir->opt1);
            ir->addASMBack("call", {}, func->entry);
            if(func->returnType != IR_VOID){
                auto retVal = new vReg();
                retVal->regType = REG_R;
                retVal->regId = a0;
                addASM("mv", ir, {})->addOp(retVal);
            }
            return paramCnt + 1;
        }
    });
}