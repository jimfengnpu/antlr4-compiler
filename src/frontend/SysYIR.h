#pragma once

#include "antlr4-runtime.h"

using namespace antlr4::tree;


enum class IRType : size_t {
    TERMINAL = 1,
    ERROR = 2,
    RULE = 3,
};

class SysYIR{

public:
};
