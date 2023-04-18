
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

  virtual void enterComDecl(SysYParser::ComDeclContext * /*ctx*/) override { }
  virtual void exitComDecl(SysYParser::ComDeclContext * /*ctx*/) override { }

  virtual void enterBType(SysYParser::BTypeContext * /*ctx*/) override { }
  virtual void exitBType(SysYParser::BTypeContext * /*ctx*/) override { }

  virtual void enterComDef(SysYParser::ComDefContext * /*ctx*/) override { }
  virtual void exitComDef(SysYParser::ComDefContext * /*ctx*/) override { }

  virtual void enterInitVal(SysYParser::InitValContext * /*ctx*/) override { }
  virtual void exitInitVal(SysYParser::InitValContext * /*ctx*/) override { }

  virtual void enterExp(SysYParser::ExpContext * /*ctx*/) override { }
  virtual void exitExp(SysYParser::ExpContext * /*ctx*/) override { }

  virtual void enterMulExp(SysYParser::MulExpContext * /*ctx*/) override { }
  virtual void exitMulExp(SysYParser::MulExpContext * /*ctx*/) override { }

  virtual void enterUnaryExp(SysYParser::UnaryExpContext * /*ctx*/) override { }
  virtual void exitUnaryExp(SysYParser::UnaryExpContext * /*ctx*/) override { }

  virtual void enterPriExp(SysYParser::PriExpContext * /*ctx*/) override { }
  virtual void exitPriExp(SysYParser::PriExpContext * /*ctx*/) override { }

  virtual void enterLVal(SysYParser::LValContext * /*ctx*/) override { }
  virtual void exitLVal(SysYParser::LValContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

