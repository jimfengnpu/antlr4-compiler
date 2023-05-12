
// Generated from src/frontend/grammar/SysY.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "SysYListener.h"


/**
 * This class provides an empty implementation of SysYListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  SysYBaseListener : public SysYListener {
public:

  virtual void enterCompUnit(SysYParser::CompUnitContext * /*ctx*/) override { }
  virtual void exitCompUnit(SysYParser::CompUnitContext * /*ctx*/) override { }

  virtual void enterDecl(SysYParser::DeclContext * /*ctx*/) override { }
  virtual void exitDecl(SysYParser::DeclContext * /*ctx*/) override { }

  virtual void enterFuncDef(SysYParser::FuncDefContext * /*ctx*/) override { }
  virtual void exitFuncDef(SysYParser::FuncDefContext * /*ctx*/) override { }

  virtual void enterFuncType(SysYParser::FuncTypeContext * /*ctx*/) override { }
  virtual void exitFuncType(SysYParser::FuncTypeContext * /*ctx*/) override { }

  virtual void enterBType(SysYParser::BTypeContext * /*ctx*/) override { }
  virtual void exitBType(SysYParser::BTypeContext * /*ctx*/) override { }

  virtual void enterDef(SysYParser::DefContext * /*ctx*/) override { }
  virtual void exitDef(SysYParser::DefContext * /*ctx*/) override { }

  virtual void enterFuncFParam(SysYParser::FuncFParamContext * /*ctx*/) override { }
  virtual void exitFuncFParam(SysYParser::FuncFParamContext * /*ctx*/) override { }

  virtual void enterFuncArrParam(SysYParser::FuncArrParamContext * /*ctx*/) override { }
  virtual void exitFuncArrParam(SysYParser::FuncArrParamContext * /*ctx*/) override { }

  virtual void enterBlock(SysYParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(SysYParser::BlockContext * /*ctx*/) override { }

  virtual void enterAssignStmt(SysYParser::AssignStmtContext * /*ctx*/) override { }
  virtual void exitAssignStmt(SysYParser::AssignStmtContext * /*ctx*/) override { }

  virtual void enterExpStmt(SysYParser::ExpStmtContext * /*ctx*/) override { }
  virtual void exitExpStmt(SysYParser::ExpStmtContext * /*ctx*/) override { }

  virtual void enterBlockStmt(SysYParser::BlockStmtContext * /*ctx*/) override { }
  virtual void exitBlockStmt(SysYParser::BlockStmtContext * /*ctx*/) override { }

  virtual void enterCondStmt(SysYParser::CondStmtContext * /*ctx*/) override { }
  virtual void exitCondStmt(SysYParser::CondStmtContext * /*ctx*/) override { }

  virtual void enterLoopStmt(SysYParser::LoopStmtContext * /*ctx*/) override { }
  virtual void exitLoopStmt(SysYParser::LoopStmtContext * /*ctx*/) override { }

  virtual void enterBreakStmt(SysYParser::BreakStmtContext * /*ctx*/) override { }
  virtual void exitBreakStmt(SysYParser::BreakStmtContext * /*ctx*/) override { }

  virtual void enterContStmt(SysYParser::ContStmtContext * /*ctx*/) override { }
  virtual void exitContStmt(SysYParser::ContStmtContext * /*ctx*/) override { }

  virtual void enterReturnStmt(SysYParser::ReturnStmtContext * /*ctx*/) override { }
  virtual void exitReturnStmt(SysYParser::ReturnStmtContext * /*ctx*/) override { }

  virtual void enterInitVal(SysYParser::InitValContext * /*ctx*/) override { }
  virtual void exitInitVal(SysYParser::InitValContext * /*ctx*/) override { }

  virtual void enterCond(SysYParser::CondContext * /*ctx*/) override { }
  virtual void exitCond(SysYParser::CondContext * /*ctx*/) override { }

  virtual void enterExp(SysYParser::ExpContext * /*ctx*/) override { }
  virtual void exitExp(SysYParser::ExpContext * /*ctx*/) override { }

  virtual void enterLVal(SysYParser::LValContext * /*ctx*/) override { }
  virtual void exitLVal(SysYParser::LValContext * /*ctx*/) override { }

  virtual void enterArrAccess(SysYParser::ArrAccessContext * /*ctx*/) override { }
  virtual void exitArrAccess(SysYParser::ArrAccessContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

