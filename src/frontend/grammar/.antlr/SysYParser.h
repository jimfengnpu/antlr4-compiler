
// Generated from /home/jimfeng/antlr4-compiler/src/frontend/grammar/SysY.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  SysYParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, WS = 24, COMMENT = 25, VoidType = 26, 
    IntType = 27, FloatType = 28, ConstPrefix = 29, IF = 30, ELSE = 31, 
    WHILE = 32, BREAK = 33, CONTINUE = 34, RETURN = 35, IntConstant = 36, 
    FloatConstant = 37, DigitSequence = 38, Ident = 39
  };

  enum {
    RuleCompUnit = 0, RuleConstDecl = 1, RuleVarDecl = 2, RuleFuncDef = 3, 
    RuleFuncType = 4, RuleBType = 5, RuleDef = 6, RuleFuncFParam = 7, RuleBlock = 8, 
    RuleStmt = 9, RuleInitVal = 10, RuleCond = 11, RuleExp = 12, RuleLVal = 13, 
    RuleArrAccess = 14
  };

  explicit SysYParser(antlr4::TokenStream *input);
  ~SysYParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class CompUnitContext;
  class ConstDeclContext;
  class VarDeclContext;
  class FuncDefContext;
  class FuncTypeContext;
  class BTypeContext;
  class DefContext;
  class FuncFParamContext;
  class BlockContext;
  class StmtContext;
  class InitValContext;
  class CondContext;
  class ExpContext;
  class LValContext;
  class ArrAccessContext; 

  class  CompUnitContext : public antlr4::ParserRuleContext {
  public:
    CompUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VarDeclContext *> varDecl();
    VarDeclContext* varDecl(size_t i);
    std::vector<ConstDeclContext *> constDecl();
    ConstDeclContext* constDecl(size_t i);
    std::vector<FuncDefContext *> funcDef();
    FuncDefContext* funcDef(size_t i);

   
  };

  CompUnitContext* compUnit();

  class  ConstDeclContext : public antlr4::ParserRuleContext {
  public:
    ConstDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ConstPrefix();
    BTypeContext *bType();
    std::vector<DefContext *> def();
    DefContext* def(size_t i);

   
  };

  ConstDeclContext* constDecl();

  class  VarDeclContext : public antlr4::ParserRuleContext {
  public:
    VarDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BTypeContext *bType();
    std::vector<DefContext *> def();
    DefContext* def(size_t i);

   
  };

  VarDeclContext* varDecl();

  class  FuncDefContext : public antlr4::ParserRuleContext {
  public:
    SysYParser::FuncFParamContext *funcFParamContext = nullptr;
    std::vector<FuncFParamContext *> params;
    FuncDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncTypeContext *funcType();
    antlr4::tree::TerminalNode *Ident();
    BlockContext *block();
    std::vector<FuncFParamContext *> funcFParam();
    FuncFParamContext* funcFParam(size_t i);

   
  };

  FuncDefContext* funcDef();

  class  FuncTypeContext : public antlr4::ParserRuleContext {
  public:
    FuncTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VoidType();
    antlr4::tree::TerminalNode *IntType();
    antlr4::tree::TerminalNode *FloatType();

   
  };

  FuncTypeContext* funcType();

  class  BTypeContext : public antlr4::ParserRuleContext {
  public:
    BTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntType();
    antlr4::tree::TerminalNode *FloatType();

   
  };

  BTypeContext* bType();

  class  DefContext : public antlr4::ParserRuleContext {
  public:
    DefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Ident();
    std::vector<ArrAccessContext *> arrAccess();
    ArrAccessContext* arrAccess(size_t i);
    InitValContext *initVal();

   
  };

  DefContext* def();

  class  FuncFParamContext : public antlr4::ParserRuleContext {
  public:
    FuncFParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BTypeContext *bType();
    antlr4::tree::TerminalNode *Ident();
    std::vector<ArrAccessContext *> arrAccess();
    ArrAccessContext* arrAccess(size_t i);

   
  };

  FuncFParamContext* funcFParam();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VarDeclContext *> varDecl();
    VarDeclContext* varDecl(size_t i);
    std::vector<ConstDeclContext *> constDecl();
    ConstDeclContext* constDecl(size_t i);
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);

   
  };

  BlockContext* block();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StmtContext() = default;
    void copyFrom(StmtContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LoopStmtContext : public StmtContext {
  public:
    LoopStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *WHILE();
    CondContext *cond();
    StmtContext *stmt();
  };

  class  BlockStmtContext : public StmtContext {
  public:
    BlockStmtContext(StmtContext *ctx);

    BlockContext *block();
  };

  class  AssignStmtContext : public StmtContext {
  public:
    AssignStmtContext(StmtContext *ctx);

    LValContext *lVal();
    ExpContext *exp();
  };

  class  BreakStmtContext : public StmtContext {
  public:
    BreakStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *BREAK();
  };

  class  ExpStmtContext : public StmtContext {
  public:
    ExpStmtContext(StmtContext *ctx);

    ExpContext *exp();
  };

  class  ReturnStmtContext : public StmtContext {
  public:
    ReturnStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *RETURN();
    ExpContext *exp();
  };

  class  ContStmtContext : public StmtContext {
  public:
    ContStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *CONTINUE();
  };

  class  CondStmtContext : public StmtContext {
  public:
    CondStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *IF();
    CondContext *cond();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);
    antlr4::tree::TerminalNode *ELSE();
  };

  StmtContext* stmt();

  class  InitValContext : public antlr4::ParserRuleContext {
  public:
    InitValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpContext *exp();
    std::vector<InitValContext *> initVal();
    InitValContext* initVal(size_t i);

   
  };

  InitValContext* initVal();

  class  CondContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *comp = nullptr;
    CondContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpContext *exp();
    std::vector<CondContext *> cond();
    CondContext* cond(size_t i);

   
  };

  CondContext* cond();
  CondContext* cond(int precedence);
  class  ExpContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *op = nullptr;
    ExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntConstant();
    antlr4::tree::TerminalNode *FloatConstant();
    LValContext *lVal();
    antlr4::tree::TerminalNode *Ident();
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);

   
  };

  ExpContext* exp();
  ExpContext* exp(int precedence);
  class  LValContext : public antlr4::ParserRuleContext {
  public:
    LValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Ident();
    std::vector<ArrAccessContext *> arrAccess();
    ArrAccessContext* arrAccess(size_t i);

   
  };

  LValContext* lVal();

  class  ArrAccessContext : public antlr4::ParserRuleContext {
  public:
    ArrAccessContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpContext *exp();

   
  };

  ArrAccessContext* arrAccess();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool condSempred(CondContext *_localctx, size_t predicateIndex);
  bool expSempred(ExpContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

