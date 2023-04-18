
// Generated from src/frontend/grammar/SysY.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "SysYParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by SysYParser.
 */
class  SysYListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterCompUnit(SysYParser::CompUnitContext *ctx) = 0;
  virtual void exitCompUnit(SysYParser::CompUnitContext *ctx) = 0;

  virtual void enterDecl(SysYParser::DeclContext *ctx) = 0;
  virtual void exitDecl(SysYParser::DeclContext *ctx) = 0;

  virtual void enterComDecl(SysYParser::ComDeclContext *ctx) = 0;
  virtual void exitComDecl(SysYParser::ComDeclContext *ctx) = 0;

  virtual void enterBType(SysYParser::BTypeContext *ctx) = 0;
  virtual void exitBType(SysYParser::BTypeContext *ctx) = 0;

  virtual void enterComDef(SysYParser::ComDefContext *ctx) = 0;
  virtual void exitComDef(SysYParser::ComDefContext *ctx) = 0;

  virtual void enterInitVal(SysYParser::InitValContext *ctx) = 0;
  virtual void exitInitVal(SysYParser::InitValContext *ctx) = 0;

  virtual void enterExp(SysYParser::ExpContext *ctx) = 0;
  virtual void exitExp(SysYParser::ExpContext *ctx) = 0;

  virtual void enterMulExp(SysYParser::MulExpContext *ctx) = 0;
  virtual void exitMulExp(SysYParser::MulExpContext *ctx) = 0;

  virtual void enterUnaryExp(SysYParser::UnaryExpContext *ctx) = 0;
  virtual void exitUnaryExp(SysYParser::UnaryExpContext *ctx) = 0;

  virtual void enterPriExp(SysYParser::PriExpContext *ctx) = 0;
  virtual void exitPriExp(SysYParser::PriExpContext *ctx) = 0;

  virtual void enterLVal(SysYParser::LValContext *ctx) = 0;
  virtual void exitLVal(SysYParser::LValContext *ctx) = 0;


};

