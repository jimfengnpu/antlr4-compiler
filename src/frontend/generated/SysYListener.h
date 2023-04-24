
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

  virtual void enterConstDecl(SysYParser::ConstDeclContext *ctx) = 0;
  virtual void exitConstDecl(SysYParser::ConstDeclContext *ctx) = 0;

  virtual void enterVarDecl(SysYParser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(SysYParser::VarDeclContext *ctx) = 0;

  virtual void enterFuncDef(SysYParser::FuncDefContext *ctx) = 0;
  virtual void exitFuncDef(SysYParser::FuncDefContext *ctx) = 0;

  virtual void enterFuncType(SysYParser::FuncTypeContext *ctx) = 0;
  virtual void exitFuncType(SysYParser::FuncTypeContext *ctx) = 0;

  virtual void enterBType(SysYParser::BTypeContext *ctx) = 0;
  virtual void exitBType(SysYParser::BTypeContext *ctx) = 0;

  virtual void enterDef(SysYParser::DefContext *ctx) = 0;
  virtual void exitDef(SysYParser::DefContext *ctx) = 0;

  virtual void enterFuncParam(SysYParser::FuncParamContext *ctx) = 0;
  virtual void exitFuncParam(SysYParser::FuncParamContext *ctx) = 0;

  virtual void enterBlock(SysYParser::BlockContext *ctx) = 0;
  virtual void exitBlock(SysYParser::BlockContext *ctx) = 0;

  virtual void enterAssignStmt(SysYParser::AssignStmtContext *ctx) = 0;
  virtual void exitAssignStmt(SysYParser::AssignStmtContext *ctx) = 0;

  virtual void enterExpStmt(SysYParser::ExpStmtContext *ctx) = 0;
  virtual void exitExpStmt(SysYParser::ExpStmtContext *ctx) = 0;

  virtual void enterBlockStmt(SysYParser::BlockStmtContext *ctx) = 0;
  virtual void exitBlockStmt(SysYParser::BlockStmtContext *ctx) = 0;

  virtual void enterCondStmt(SysYParser::CondStmtContext *ctx) = 0;
  virtual void exitCondStmt(SysYParser::CondStmtContext *ctx) = 0;

  virtual void enterLoopStmt(SysYParser::LoopStmtContext *ctx) = 0;
  virtual void exitLoopStmt(SysYParser::LoopStmtContext *ctx) = 0;

  virtual void enterBreakStmt(SysYParser::BreakStmtContext *ctx) = 0;
  virtual void exitBreakStmt(SysYParser::BreakStmtContext *ctx) = 0;

  virtual void enterContStmt(SysYParser::ContStmtContext *ctx) = 0;
  virtual void exitContStmt(SysYParser::ContStmtContext *ctx) = 0;

  virtual void enterReturnStmt(SysYParser::ReturnStmtContext *ctx) = 0;
  virtual void exitReturnStmt(SysYParser::ReturnStmtContext *ctx) = 0;

  virtual void enterInitVal(SysYParser::InitValContext *ctx) = 0;
  virtual void exitInitVal(SysYParser::InitValContext *ctx) = 0;

  virtual void enterCond(SysYParser::CondContext *ctx) = 0;
  virtual void exitCond(SysYParser::CondContext *ctx) = 0;

  virtual void enterExp(SysYParser::ExpContext *ctx) = 0;
  virtual void exitExp(SysYParser::ExpContext *ctx) = 0;

  virtual void enterLVal(SysYParser::LValContext *ctx) = 0;
  virtual void exitLVal(SysYParser::LValContext *ctx) = 0;

  virtual void enterArrAccess(SysYParser::ArrAccessContext *ctx) = 0;
  virtual void exitArrAccess(SysYParser::ArrAccessContext *ctx) = 0;


};

