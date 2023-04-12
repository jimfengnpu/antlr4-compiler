
// Generated from src/frontend/grammer/SysY.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "SysYParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by SysYParser.
 */
class  SysYListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(SysYParser::ProgContext *ctx) = 0;
  virtual void exitProg(SysYParser::ProgContext *ctx) = 0;

  virtual void enterExpr(SysYParser::ExprContext *ctx) = 0;
  virtual void exitExpr(SysYParser::ExprContext *ctx) = 0;


};

