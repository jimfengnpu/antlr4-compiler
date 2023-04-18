#pragma once

#include "antlr4-runtime.h"

using namespace antlr4::tree;

class SysYAST{

public:
    static ParseTree* BuildAST(ParseTree * t);
};
