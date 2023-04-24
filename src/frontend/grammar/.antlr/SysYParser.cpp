
// Generated from /home/jimfeng/antlr4-compiler/src/frontend/grammar/SysY.g4 by ANTLR 4.9.2



#include "SysYParser.h"


using namespace antlrcpp;
using namespace antlr4;

SysYParser::SysYParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

SysYParser::~SysYParser() {
  delete _interpreter;
}

std::string SysYParser::getGrammarFileName() const {
  return "SysY.g4";
}

const std::vector<std::string>& SysYParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& SysYParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- CompUnitContext ------------------------------------------------------------------

SysYParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::VarDeclContext *> SysYParser::CompUnitContext::varDecl() {
  return getRuleContexts<SysYParser::VarDeclContext>();
}

SysYParser::VarDeclContext* SysYParser::CompUnitContext::varDecl(size_t i) {
  return getRuleContext<SysYParser::VarDeclContext>(i);
}

std::vector<SysYParser::ConstDeclContext *> SysYParser::CompUnitContext::constDecl() {
  return getRuleContexts<SysYParser::ConstDeclContext>();
}

SysYParser::ConstDeclContext* SysYParser::CompUnitContext::constDecl(size_t i) {
  return getRuleContext<SysYParser::ConstDeclContext>(i);
}

std::vector<SysYParser::FuncDefContext *> SysYParser::CompUnitContext::funcDef() {
  return getRuleContexts<SysYParser::FuncDefContext>();
}

SysYParser::FuncDefContext* SysYParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<SysYParser::FuncDefContext>(i);
}


size_t SysYParser::CompUnitContext::getRuleIndex() const {
  return SysYParser::RuleCompUnit;
}


SysYParser::CompUnitContext* SysYParser::compUnit() {
  CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, SysYParser::RuleCompUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(33); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(33);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(30);
        varDecl();
        break;
      }

      case 2: {
        setState(31);
        constDecl();
        break;
      }

      case 3: {
        setState(32);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(35); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SysYParser::VoidType)
      | (1ULL << SysYParser::IntType)
      | (1ULL << SysYParser::FloatType)
      | (1ULL << SysYParser::ConstPrefix))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

SysYParser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::ConstDeclContext::ConstPrefix() {
  return getToken(SysYParser::ConstPrefix, 0);
}

SysYParser::BTypeContext* SysYParser::ConstDeclContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

std::vector<SysYParser::DefContext *> SysYParser::ConstDeclContext::def() {
  return getRuleContexts<SysYParser::DefContext>();
}

SysYParser::DefContext* SysYParser::ConstDeclContext::def(size_t i) {
  return getRuleContext<SysYParser::DefContext>(i);
}


size_t SysYParser::ConstDeclContext::getRuleIndex() const {
  return SysYParser::RuleConstDecl;
}


SysYParser::ConstDeclContext* SysYParser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 2, SysYParser::RuleConstDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    match(SysYParser::ConstPrefix);
    setState(38);
    bType();
    setState(39);
    def();
    setState(44);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__0) {
      setState(40);
      match(SysYParser::T__0);
      setState(41);
      def();
      setState(46);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(47);
    match(SysYParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

SysYParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::BTypeContext* SysYParser::VarDeclContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

std::vector<SysYParser::DefContext *> SysYParser::VarDeclContext::def() {
  return getRuleContexts<SysYParser::DefContext>();
}

SysYParser::DefContext* SysYParser::VarDeclContext::def(size_t i) {
  return getRuleContext<SysYParser::DefContext>(i);
}


size_t SysYParser::VarDeclContext::getRuleIndex() const {
  return SysYParser::RuleVarDecl;
}


SysYParser::VarDeclContext* SysYParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, SysYParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(49);
    bType();
    setState(50);
    def();
    setState(55);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__0) {
      setState(51);
      match(SysYParser::T__0);
      setState(52);
      def();
      setState(57);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(58);
    match(SysYParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

SysYParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::FuncTypeContext* SysYParser::FuncDefContext::funcType() {
  return getRuleContext<SysYParser::FuncTypeContext>(0);
}

tree::TerminalNode* SysYParser::FuncDefContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

SysYParser::BlockContext* SysYParser::FuncDefContext::block() {
  return getRuleContext<SysYParser::BlockContext>(0);
}

std::vector<SysYParser::FuncFParamContext *> SysYParser::FuncDefContext::funcFParam() {
  return getRuleContexts<SysYParser::FuncFParamContext>();
}

SysYParser::FuncFParamContext* SysYParser::FuncDefContext::funcFParam(size_t i) {
  return getRuleContext<SysYParser::FuncFParamContext>(i);
}


size_t SysYParser::FuncDefContext::getRuleIndex() const {
  return SysYParser::RuleFuncDef;
}


SysYParser::FuncDefContext* SysYParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 6, SysYParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(60);
    funcType();
    setState(61);
    match(SysYParser::Ident);
    setState(62);
    match(SysYParser::T__2);
    setState(71);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::IntType

    || _la == SysYParser::FloatType) {
      setState(63);
      dynamic_cast<FuncDefContext *>(_localctx)->funcFParamContext = funcFParam();
      dynamic_cast<FuncDefContext *>(_localctx)->params.push_back(dynamic_cast<FuncDefContext *>(_localctx)->funcFParamContext);
      setState(68);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__0) {
        setState(64);
        match(SysYParser::T__0);
        setState(65);
        dynamic_cast<FuncDefContext *>(_localctx)->funcFParamContext = funcFParam();
        dynamic_cast<FuncDefContext *>(_localctx)->params.push_back(dynamic_cast<FuncDefContext *>(_localctx)->funcFParamContext);
        setState(70);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(73);
    match(SysYParser::T__3);
    setState(74);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

SysYParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::FuncTypeContext::VoidType() {
  return getToken(SysYParser::VoidType, 0);
}

tree::TerminalNode* SysYParser::FuncTypeContext::IntType() {
  return getToken(SysYParser::IntType, 0);
}

tree::TerminalNode* SysYParser::FuncTypeContext::FloatType() {
  return getToken(SysYParser::FloatType, 0);
}


size_t SysYParser::FuncTypeContext::getRuleIndex() const {
  return SysYParser::RuleFuncType;
}


SysYParser::FuncTypeContext* SysYParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 8, SysYParser::RuleFuncType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SysYParser::VoidType)
      | (1ULL << SysYParser::IntType)
      | (1ULL << SysYParser::FloatType))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BTypeContext ------------------------------------------------------------------

SysYParser::BTypeContext::BTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::BTypeContext::IntType() {
  return getToken(SysYParser::IntType, 0);
}

tree::TerminalNode* SysYParser::BTypeContext::FloatType() {
  return getToken(SysYParser::FloatType, 0);
}


size_t SysYParser::BTypeContext::getRuleIndex() const {
  return SysYParser::RuleBType;
}


SysYParser::BTypeContext* SysYParser::bType() {
  BTypeContext *_localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
  enterRule(_localctx, 10, SysYParser::RuleBType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    _la = _input->LA(1);
    if (!(_la == SysYParser::IntType

    || _la == SysYParser::FloatType)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefContext ------------------------------------------------------------------

SysYParser::DefContext::DefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::DefContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

std::vector<SysYParser::ArrAccessContext *> SysYParser::DefContext::arrAccess() {
  return getRuleContexts<SysYParser::ArrAccessContext>();
}

SysYParser::ArrAccessContext* SysYParser::DefContext::arrAccess(size_t i) {
  return getRuleContext<SysYParser::ArrAccessContext>(i);
}

SysYParser::InitValContext* SysYParser::DefContext::initVal() {
  return getRuleContext<SysYParser::InitValContext>(0);
}


size_t SysYParser::DefContext::getRuleIndex() const {
  return SysYParser::RuleDef;
}


SysYParser::DefContext* SysYParser::def() {
  DefContext *_localctx = _tracker.createInstance<DefContext>(_ctx, getState());
  enterRule(_localctx, 12, SysYParser::RuleDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    match(SysYParser::Ident);
    setState(84);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__5) {
      setState(81);
      arrAccess();
      setState(86);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(89);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::T__4) {
      setState(87);
      match(SysYParser::T__4);
      setState(88);
      initVal();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

SysYParser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::BTypeContext* SysYParser::FuncFParamContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

tree::TerminalNode* SysYParser::FuncFParamContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

std::vector<SysYParser::ArrAccessContext *> SysYParser::FuncFParamContext::arrAccess() {
  return getRuleContexts<SysYParser::ArrAccessContext>();
}

SysYParser::ArrAccessContext* SysYParser::FuncFParamContext::arrAccess(size_t i) {
  return getRuleContext<SysYParser::ArrAccessContext>(i);
}


size_t SysYParser::FuncFParamContext::getRuleIndex() const {
  return SysYParser::RuleFuncFParam;
}


SysYParser::FuncFParamContext* SysYParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 14, SysYParser::RuleFuncFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    bType();
    setState(92);
    match(SysYParser::Ident);
    setState(101);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::T__5) {
      setState(93);
      match(SysYParser::T__5);
      setState(94);
      match(SysYParser::T__6);
      setState(98);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__5) {
        setState(95);
        arrAccess();
        setState(100);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

SysYParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::VarDeclContext *> SysYParser::BlockContext::varDecl() {
  return getRuleContexts<SysYParser::VarDeclContext>();
}

SysYParser::VarDeclContext* SysYParser::BlockContext::varDecl(size_t i) {
  return getRuleContext<SysYParser::VarDeclContext>(i);
}

std::vector<SysYParser::ConstDeclContext *> SysYParser::BlockContext::constDecl() {
  return getRuleContexts<SysYParser::ConstDeclContext>();
}

SysYParser::ConstDeclContext* SysYParser::BlockContext::constDecl(size_t i) {
  return getRuleContext<SysYParser::ConstDeclContext>(i);
}

std::vector<SysYParser::StmtContext *> SysYParser::BlockContext::stmt() {
  return getRuleContexts<SysYParser::StmtContext>();
}

SysYParser::StmtContext* SysYParser::BlockContext::stmt(size_t i) {
  return getRuleContext<SysYParser::StmtContext>(i);
}


size_t SysYParser::BlockContext::getRuleIndex() const {
  return SysYParser::RuleBlock;
}


SysYParser::BlockContext* SysYParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 16, SysYParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103);
    match(SysYParser::T__7);
    setState(109);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SysYParser::T__1)
      | (1ULL << SysYParser::T__2)
      | (1ULL << SysYParser::T__7)
      | (1ULL << SysYParser::T__17)
      | (1ULL << SysYParser::T__18)
      | (1ULL << SysYParser::T__19)
      | (1ULL << SysYParser::IntType)
      | (1ULL << SysYParser::FloatType)
      | (1ULL << SysYParser::ConstPrefix)
      | (1ULL << SysYParser::IF)
      | (1ULL << SysYParser::WHILE)
      | (1ULL << SysYParser::BREAK)
      | (1ULL << SysYParser::CONTINUE)
      | (1ULL << SysYParser::RETURN)
      | (1ULL << SysYParser::IntConstant)
      | (1ULL << SysYParser::FloatConstant)
      | (1ULL << SysYParser::Ident))) != 0)) {
      setState(107);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case SysYParser::IntType:
        case SysYParser::FloatType: {
          setState(104);
          varDecl();
          break;
        }

        case SysYParser::ConstPrefix: {
          setState(105);
          constDecl();
          break;
        }

        case SysYParser::T__1:
        case SysYParser::T__2:
        case SysYParser::T__7:
        case SysYParser::T__17:
        case SysYParser::T__18:
        case SysYParser::T__19:
        case SysYParser::IF:
        case SysYParser::WHILE:
        case SysYParser::BREAK:
        case SysYParser::CONTINUE:
        case SysYParser::RETURN:
        case SysYParser::IntConstant:
        case SysYParser::FloatConstant:
        case SysYParser::Ident: {
          setState(106);
          stmt();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(111);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(112);
    match(SysYParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

SysYParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::StmtContext::getRuleIndex() const {
  return SysYParser::RuleStmt;
}

void SysYParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LoopStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::LoopStmtContext::WHILE() {
  return getToken(SysYParser::WHILE, 0);
}

SysYParser::CondContext* SysYParser::LoopStmtContext::cond() {
  return getRuleContext<SysYParser::CondContext>(0);
}

SysYParser::StmtContext* SysYParser::LoopStmtContext::stmt() {
  return getRuleContext<SysYParser::StmtContext>(0);
}

SysYParser::LoopStmtContext::LoopStmtContext(StmtContext *ctx) { copyFrom(ctx); }


//----------------- BlockStmtContext ------------------------------------------------------------------

SysYParser::BlockContext* SysYParser::BlockStmtContext::block() {
  return getRuleContext<SysYParser::BlockContext>(0);
}

SysYParser::BlockStmtContext::BlockStmtContext(StmtContext *ctx) { copyFrom(ctx); }


//----------------- AssignStmtContext ------------------------------------------------------------------

SysYParser::LValContext* SysYParser::AssignStmtContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

SysYParser::ExpContext* SysYParser::AssignStmtContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::AssignStmtContext::AssignStmtContext(StmtContext *ctx) { copyFrom(ctx); }


//----------------- BreakStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::BreakStmtContext::BREAK() {
  return getToken(SysYParser::BREAK, 0);
}

SysYParser::BreakStmtContext::BreakStmtContext(StmtContext *ctx) { copyFrom(ctx); }


//----------------- ExpStmtContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::ExpStmtContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::ExpStmtContext::ExpStmtContext(StmtContext *ctx) { copyFrom(ctx); }


//----------------- ReturnStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ReturnStmtContext::RETURN() {
  return getToken(SysYParser::RETURN, 0);
}

SysYParser::ExpContext* SysYParser::ReturnStmtContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::ReturnStmtContext::ReturnStmtContext(StmtContext *ctx) { copyFrom(ctx); }


//----------------- ContStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ContStmtContext::CONTINUE() {
  return getToken(SysYParser::CONTINUE, 0);
}

SysYParser::ContStmtContext::ContStmtContext(StmtContext *ctx) { copyFrom(ctx); }


//----------------- CondStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::CondStmtContext::IF() {
  return getToken(SysYParser::IF, 0);
}

SysYParser::CondContext* SysYParser::CondStmtContext::cond() {
  return getRuleContext<SysYParser::CondContext>(0);
}

std::vector<SysYParser::StmtContext *> SysYParser::CondStmtContext::stmt() {
  return getRuleContexts<SysYParser::StmtContext>();
}

SysYParser::StmtContext* SysYParser::CondStmtContext::stmt(size_t i) {
  return getRuleContext<SysYParser::StmtContext>(i);
}

tree::TerminalNode* SysYParser::CondStmtContext::ELSE() {
  return getToken(SysYParser::ELSE, 0);
}

SysYParser::CondStmtContext::CondStmtContext(StmtContext *ctx) { copyFrom(ctx); }


SysYParser::StmtContext* SysYParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 18, SysYParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(148);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<SysYParser::AssignStmtContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(114);
      lVal();
      setState(115);
      match(SysYParser::T__4);
      setState(116);
      exp(0);
      setState(117);
      match(SysYParser::T__1);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<SysYParser::ExpStmtContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(120);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SysYParser::T__2)
        | (1ULL << SysYParser::T__17)
        | (1ULL << SysYParser::T__18)
        | (1ULL << SysYParser::T__19)
        | (1ULL << SysYParser::IntConstant)
        | (1ULL << SysYParser::FloatConstant)
        | (1ULL << SysYParser::Ident))) != 0)) {
        setState(119);
        exp(0);
      }
      setState(122);
      match(SysYParser::T__1);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<SysYParser::BlockStmtContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(123);
      block();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<SysYParser::CondStmtContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(124);
      match(SysYParser::IF);
      setState(125);
      match(SysYParser::T__2);
      setState(126);
      cond(0);
      setState(127);
      match(SysYParser::T__3);
      setState(128);
      stmt();
      setState(131);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(129);
        match(SysYParser::ELSE);
        setState(130);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<SysYParser::LoopStmtContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(133);
      match(SysYParser::WHILE);
      setState(134);
      match(SysYParser::T__2);
      setState(135);
      cond(0);
      setState(136);
      match(SysYParser::T__3);
      setState(137);
      stmt();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<SysYParser::BreakStmtContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(139);
      match(SysYParser::BREAK);
      setState(140);
      match(SysYParser::T__1);
      break;
    }

    case 7: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<SysYParser::ContStmtContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(141);
      match(SysYParser::CONTINUE);
      setState(142);
      match(SysYParser::T__1);
      break;
    }

    case 8: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<SysYParser::ReturnStmtContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(143);
      match(SysYParser::RETURN);
      setState(145);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SysYParser::T__2)
        | (1ULL << SysYParser::T__17)
        | (1ULL << SysYParser::T__18)
        | (1ULL << SysYParser::T__19)
        | (1ULL << SysYParser::IntConstant)
        | (1ULL << SysYParser::FloatConstant)
        | (1ULL << SysYParser::Ident))) != 0)) {
        setState(144);
        exp(0);
      }
      setState(147);
      match(SysYParser::T__1);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitValContext ------------------------------------------------------------------

SysYParser::InitValContext::InitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::ExpContext* SysYParser::InitValContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

std::vector<SysYParser::InitValContext *> SysYParser::InitValContext::initVal() {
  return getRuleContexts<SysYParser::InitValContext>();
}

SysYParser::InitValContext* SysYParser::InitValContext::initVal(size_t i) {
  return getRuleContext<SysYParser::InitValContext>(i);
}


size_t SysYParser::InitValContext::getRuleIndex() const {
  return SysYParser::RuleInitVal;
}


SysYParser::InitValContext* SysYParser::initVal() {
  InitValContext *_localctx = _tracker.createInstance<InitValContext>(_ctx, getState());
  enterRule(_localctx, 20, SysYParser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(162);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__2:
      case SysYParser::T__17:
      case SysYParser::T__18:
      case SysYParser::T__19:
      case SysYParser::IntConstant:
      case SysYParser::FloatConstant:
      case SysYParser::Ident: {
        enterOuterAlt(_localctx, 1);
        setState(150);
        exp(0);
        break;
      }

      case SysYParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(151);
        match(SysYParser::T__7);
        setState(152);
        initVal();
        setState(157);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysYParser::T__0) {
          setState(153);
          match(SysYParser::T__0);
          setState(154);
          initVal();
          setState(159);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(160);
        match(SysYParser::T__8);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

SysYParser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::ExpContext* SysYParser::CondContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

std::vector<SysYParser::CondContext *> SysYParser::CondContext::cond() {
  return getRuleContexts<SysYParser::CondContext>();
}

SysYParser::CondContext* SysYParser::CondContext::cond(size_t i) {
  return getRuleContext<SysYParser::CondContext>(i);
}


size_t SysYParser::CondContext::getRuleIndex() const {
  return SysYParser::RuleCond;
}



SysYParser::CondContext* SysYParser::cond() {
   return cond(0);
}

SysYParser::CondContext* SysYParser::cond(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, parentState);
  SysYParser::CondContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, SysYParser::RuleCond, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(165);
    exp(0);
    _ctx->stop = _input->LT(-1);
    setState(181);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(179);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(167);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(168);
          dynamic_cast<CondContext *>(_localctx)->comp = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << SysYParser::T__9)
            | (1ULL << SysYParser::T__10)
            | (1ULL << SysYParser::T__11)
            | (1ULL << SysYParser::T__12))) != 0))) {
            dynamic_cast<CondContext *>(_localctx)->comp = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(169);
          cond(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(170);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(171);
          dynamic_cast<CondContext *>(_localctx)->comp = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == SysYParser::T__13

          || _la == SysYParser::T__14)) {
            dynamic_cast<CondContext *>(_localctx)->comp = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(172);
          cond(4);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(173);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(174);
          dynamic_cast<CondContext *>(_localctx)->comp = match(SysYParser::T__15);
          setState(175);
          cond(3);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(176);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(177);
          dynamic_cast<CondContext *>(_localctx)->comp = match(SysYParser::T__16);
          setState(178);
          cond(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(183);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

SysYParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::ExpContext::IntConstant() {
  return getToken(SysYParser::IntConstant, 0);
}

tree::TerminalNode* SysYParser::ExpContext::FloatConstant() {
  return getToken(SysYParser::FloatConstant, 0);
}

SysYParser::LValContext* SysYParser::ExpContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

tree::TerminalNode* SysYParser::ExpContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

std::vector<SysYParser::ExpContext *> SysYParser::ExpContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::ExpContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}


size_t SysYParser::ExpContext::getRuleIndex() const {
  return SysYParser::RuleExp;
}



SysYParser::ExpContext* SysYParser::exp() {
   return exp(0);
}

SysYParser::ExpContext* SysYParser::exp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, parentState);
  SysYParser::ExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, SysYParser::RuleExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(207);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(185);
      match(SysYParser::IntConstant);
      break;
    }

    case 2: {
      setState(186);
      match(SysYParser::FloatConstant);
      break;
    }

    case 3: {
      setState(187);
      lVal();
      break;
    }

    case 4: {
      setState(188);
      match(SysYParser::Ident);
      setState(189);
      match(SysYParser::T__2);
      setState(198);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SysYParser::T__2)
        | (1ULL << SysYParser::T__17)
        | (1ULL << SysYParser::T__18)
        | (1ULL << SysYParser::T__19)
        | (1ULL << SysYParser::IntConstant)
        | (1ULL << SysYParser::FloatConstant)
        | (1ULL << SysYParser::Ident))) != 0)) {
        setState(190);
        exp(0);
        setState(195);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysYParser::T__0) {
          setState(191);
          match(SysYParser::T__0);
          setState(192);
          exp(0);
          setState(197);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(200);
      match(SysYParser::T__3);
      break;
    }

    case 5: {
      setState(201);
      match(SysYParser::T__2);
      setState(202);
      exp(0);
      setState(203);
      match(SysYParser::T__3);
      break;
    }

    case 6: {
      setState(205);
      dynamic_cast<ExpContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SysYParser::T__17)
        | (1ULL << SysYParser::T__18)
        | (1ULL << SysYParser::T__19))) != 0))) {
        dynamic_cast<ExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(206);
      exp(3);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(217);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(215);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(209);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(210);
          dynamic_cast<ExpContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << SysYParser::T__20)
            | (1ULL << SysYParser::T__21)
            | (1ULL << SysYParser::T__22))) != 0))) {
            dynamic_cast<ExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(211);
          exp(3);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(212);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(213);
          dynamic_cast<ExpContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == SysYParser::T__17

          || _la == SysYParser::T__18)) {
            dynamic_cast<ExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(214);
          exp(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(219);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

SysYParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::LValContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

std::vector<SysYParser::ArrAccessContext *> SysYParser::LValContext::arrAccess() {
  return getRuleContexts<SysYParser::ArrAccessContext>();
}

SysYParser::ArrAccessContext* SysYParser::LValContext::arrAccess(size_t i) {
  return getRuleContext<SysYParser::ArrAccessContext>(i);
}


size_t SysYParser::LValContext::getRuleIndex() const {
  return SysYParser::RuleLVal;
}


SysYParser::LValContext* SysYParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 26, SysYParser::RuleLVal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(220);
    match(SysYParser::Ident);
    setState(224);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(221);
        arrAccess(); 
      }
      setState(226);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrAccessContext ------------------------------------------------------------------

SysYParser::ArrAccessContext::ArrAccessContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::ExpContext* SysYParser::ArrAccessContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}


size_t SysYParser::ArrAccessContext::getRuleIndex() const {
  return SysYParser::RuleArrAccess;
}


SysYParser::ArrAccessContext* SysYParser::arrAccess() {
  ArrAccessContext *_localctx = _tracker.createInstance<ArrAccessContext>(_ctx, getState());
  enterRule(_localctx, 28, SysYParser::RuleArrAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(227);
    match(SysYParser::T__5);
    setState(228);
    exp(0);
    setState(229);
    match(SysYParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool SysYParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 11: return condSempred(dynamic_cast<CondContext *>(context), predicateIndex);
    case 12: return expSempred(dynamic_cast<ExpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SysYParser::condSempred(CondContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);
    case 2: return precpred(_ctx, 2);
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::expSempred(ExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> SysYParser::_decisionToDFA;
atn::PredictionContextCache SysYParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SysYParser::_atn;
std::vector<uint16_t> SysYParser::_serializedATN;

std::vector<std::string> SysYParser::_ruleNames = {
  "compUnit", "constDecl", "varDecl", "funcDef", "funcType", "bType", "def", 
  "funcFParam", "block", "stmt", "initVal", "cond", "exp", "lVal", "arrAccess"
};

std::vector<std::string> SysYParser::_literalNames = {
  "", "','", "';'", "'('", "')'", "'='", "'['", "']'", "'{'", "'}'", "'<'", 
  "'>'", "'<='", "'>='", "'=='", "'!='", "'&&'", "'||'", "'+'", "'-'", "'!'", 
  "'*'", "'/'", "'%'", "", "", "'void'", "'int'", "'float'", "'const'", 
  "'if'", "'else'", "'while'", "'break'", "'continue'", "'return'"
};

std::vector<std::string> SysYParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "WS", "COMMENT", "VoidType", "IntType", "FloatType", 
  "ConstPrefix", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN", "IntConstant", 
  "FloatConstant", "DigitSequence", "Ident"
};

dfa::Vocabulary SysYParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> SysYParser::_tokenNames;

SysYParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x29, 0xea, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x3, 0x2, 
       0x3, 0x2, 0x3, 0x2, 0x6, 0x2, 0x24, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 
       0x25, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 
       0x2d, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x30, 0xb, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x38, 0xa, 
       0x4, 0xc, 0x4, 0xe, 0x4, 0x3b, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 
       0x45, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x48, 0xb, 0x5, 0x5, 0x5, 0x4a, 
       0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
       0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x55, 0xa, 0x8, 0xc, 
       0x8, 0xe, 0x8, 0x58, 0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x5c, 
       0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 
       0x9, 0x63, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x66, 0xb, 0x9, 0x5, 0x9, 
       0x68, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 
       0x6e, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x71, 0xb, 0xa, 0x3, 0xa, 0x3, 
       0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
       0x5, 0xb, 0x7b, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
       0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x86, 
       0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
       0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
       0x5, 0xb, 0x94, 0xa, 0xb, 0x3, 0xb, 0x5, 0xb, 0x97, 0xa, 0xb, 0x3, 
       0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x9e, 0xa, 
       0xc, 0xc, 0xc, 0xe, 0xc, 0xa1, 0xb, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 
       0xc, 0xa5, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
       0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0xb6, 0xa, 0xd, 
       0xc, 0xd, 0xe, 0xd, 0xb9, 0xb, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 
       0xe, 0xc4, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xc7, 0xb, 0xe, 0x5, 0xe, 
       0xc9, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0xd2, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0xda, 0xa, 0xe, 
       0xc, 0xe, 0xe, 0xe, 0xdd, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 
       0xe1, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0xe4, 0xb, 0xf, 0x3, 0x10, 0x3, 
       0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x2, 0x4, 0x18, 0x1a, 0x11, 
       0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
       0x1a, 0x1c, 0x1e, 0x2, 0x9, 0x3, 0x2, 0x1c, 0x1e, 0x3, 0x2, 0x1d, 
       0x1e, 0x3, 0x2, 0xc, 0xf, 0x3, 0x2, 0x10, 0x11, 0x3, 0x2, 0x14, 0x16, 
       0x3, 0x2, 0x17, 0x19, 0x3, 0x2, 0x14, 0x15, 0x2, 0x102, 0x2, 0x23, 
       0x3, 0x2, 0x2, 0x2, 0x4, 0x27, 0x3, 0x2, 0x2, 0x2, 0x6, 0x33, 0x3, 
       0x2, 0x2, 0x2, 0x8, 0x3e, 0x3, 0x2, 0x2, 0x2, 0xa, 0x4e, 0x3, 0x2, 
       0x2, 0x2, 0xc, 0x50, 0x3, 0x2, 0x2, 0x2, 0xe, 0x52, 0x3, 0x2, 0x2, 
       0x2, 0x10, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x12, 0x69, 0x3, 0x2, 0x2, 0x2, 
       0x14, 0x96, 0x3, 0x2, 0x2, 0x2, 0x16, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x18, 
       0xa6, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xd1, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xde, 
       0x3, 0x2, 0x2, 0x2, 0x1e, 0xe5, 0x3, 0x2, 0x2, 0x2, 0x20, 0x24, 0x5, 
       0x6, 0x4, 0x2, 0x21, 0x24, 0x5, 0x4, 0x3, 0x2, 0x22, 0x24, 0x5, 0x8, 
       0x5, 0x2, 0x23, 0x20, 0x3, 0x2, 0x2, 0x2, 0x23, 0x21, 0x3, 0x2, 0x2, 
       0x2, 0x23, 0x22, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 
       0x25, 0x23, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x3, 0x2, 0x2, 0x2, 0x26, 
       0x3, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x7, 0x1f, 0x2, 0x2, 0x28, 0x29, 
       0x5, 0xc, 0x7, 0x2, 0x29, 0x2e, 0x5, 0xe, 0x8, 0x2, 0x2a, 0x2b, 0x7, 
       0x3, 0x2, 0x2, 0x2b, 0x2d, 0x5, 0xe, 0x8, 0x2, 0x2c, 0x2a, 0x3, 0x2, 
       0x2, 0x2, 0x2d, 0x30, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2c, 0x3, 0x2, 0x2, 
       0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x31, 0x3, 0x2, 0x2, 0x2, 
       0x30, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x7, 0x4, 0x2, 0x2, 0x32, 
       0x5, 0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 0x5, 0xc, 0x7, 0x2, 0x34, 0x39, 
       0x5, 0xe, 0x8, 0x2, 0x35, 0x36, 0x7, 0x3, 0x2, 0x2, 0x36, 0x38, 0x5, 
       0xe, 0x8, 0x2, 0x37, 0x35, 0x3, 0x2, 0x2, 0x2, 0x38, 0x3b, 0x3, 0x2, 
       0x2, 0x2, 0x39, 0x37, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x3, 0x2, 0x2, 
       0x2, 0x3a, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x39, 0x3, 0x2, 0x2, 0x2, 
       0x3c, 0x3d, 0x7, 0x4, 0x2, 0x2, 0x3d, 0x7, 0x3, 0x2, 0x2, 0x2, 0x3e, 
       0x3f, 0x5, 0xa, 0x6, 0x2, 0x3f, 0x40, 0x7, 0x29, 0x2, 0x2, 0x40, 
       0x49, 0x7, 0x5, 0x2, 0x2, 0x41, 0x46, 0x5, 0x10, 0x9, 0x2, 0x42, 
       0x43, 0x7, 0x3, 0x2, 0x2, 0x43, 0x45, 0x5, 0x10, 0x9, 0x2, 0x44, 
       0x42, 0x3, 0x2, 0x2, 0x2, 0x45, 0x48, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 
       0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0x4a, 0x3, 
       0x2, 0x2, 0x2, 0x48, 0x46, 0x3, 0x2, 0x2, 0x2, 0x49, 0x41, 0x3, 0x2, 
       0x2, 0x2, 0x49, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x3, 0x2, 0x2, 
       0x2, 0x4b, 0x4c, 0x7, 0x6, 0x2, 0x2, 0x4c, 0x4d, 0x5, 0x12, 0xa, 
       0x2, 0x4d, 0x9, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4f, 0x9, 0x2, 0x2, 0x2, 
       0x4f, 0xb, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x9, 0x3, 0x2, 0x2, 0x51, 
       0xd, 0x3, 0x2, 0x2, 0x2, 0x52, 0x56, 0x7, 0x29, 0x2, 0x2, 0x53, 0x55, 
       0x5, 0x1e, 0x10, 0x2, 0x54, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x58, 
       0x3, 0x2, 0x2, 0x2, 0x56, 0x54, 0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x3, 
       0x2, 0x2, 0x2, 0x57, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x58, 0x56, 0x3, 0x2, 
       0x2, 0x2, 0x59, 0x5a, 0x7, 0x7, 0x2, 0x2, 0x5a, 0x5c, 0x5, 0x16, 
       0xc, 0x2, 0x5b, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 0x3, 0x2, 0x2, 
       0x2, 0x5c, 0xf, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x5, 0xc, 0x7, 0x2, 
       0x5e, 0x67, 0x7, 0x29, 0x2, 0x2, 0x5f, 0x60, 0x7, 0x8, 0x2, 0x2, 
       0x60, 0x64, 0x7, 0x9, 0x2, 0x2, 0x61, 0x63, 0x5, 0x1e, 0x10, 0x2, 
       0x62, 0x61, 0x3, 0x2, 0x2, 0x2, 0x63, 0x66, 0x3, 0x2, 0x2, 0x2, 0x64, 
       0x62, 0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0x3, 0x2, 0x2, 0x2, 0x65, 0x68, 
       0x3, 0x2, 0x2, 0x2, 0x66, 0x64, 0x3, 0x2, 0x2, 0x2, 0x67, 0x5f, 0x3, 
       0x2, 0x2, 0x2, 0x67, 0x68, 0x3, 0x2, 0x2, 0x2, 0x68, 0x11, 0x3, 0x2, 
       0x2, 0x2, 0x69, 0x6f, 0x7, 0xa, 0x2, 0x2, 0x6a, 0x6e, 0x5, 0x6, 0x4, 
       0x2, 0x6b, 0x6e, 0x5, 0x4, 0x3, 0x2, 0x6c, 0x6e, 0x5, 0x14, 0xb, 
       0x2, 0x6d, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6b, 0x3, 0x2, 0x2, 0x2, 
       0x6d, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x71, 0x3, 0x2, 0x2, 0x2, 0x6f, 
       0x6d, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x3, 0x2, 0x2, 0x2, 0x70, 0x72, 
       0x3, 0x2, 0x2, 0x2, 0x71, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x7, 
       0xb, 0x2, 0x2, 0x73, 0x13, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x5, 0x1c, 
       0xf, 0x2, 0x75, 0x76, 0x7, 0x7, 0x2, 0x2, 0x76, 0x77, 0x5, 0x1a, 
       0xe, 0x2, 0x77, 0x78, 0x7, 0x4, 0x2, 0x2, 0x78, 0x97, 0x3, 0x2, 0x2, 
       0x2, 0x79, 0x7b, 0x5, 0x1a, 0xe, 0x2, 0x7a, 0x79, 0x3, 0x2, 0x2, 
       0x2, 0x7a, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 
       0x7c, 0x97, 0x7, 0x4, 0x2, 0x2, 0x7d, 0x97, 0x5, 0x12, 0xa, 0x2, 
       0x7e, 0x7f, 0x7, 0x20, 0x2, 0x2, 0x7f, 0x80, 0x7, 0x5, 0x2, 0x2, 
       0x80, 0x81, 0x5, 0x18, 0xd, 0x2, 0x81, 0x82, 0x7, 0x6, 0x2, 0x2, 
       0x82, 0x85, 0x5, 0x14, 0xb, 0x2, 0x83, 0x84, 0x7, 0x21, 0x2, 0x2, 
       0x84, 0x86, 0x5, 0x14, 0xb, 0x2, 0x85, 0x83, 0x3, 0x2, 0x2, 0x2, 
       0x85, 0x86, 0x3, 0x2, 0x2, 0x2, 0x86, 0x97, 0x3, 0x2, 0x2, 0x2, 0x87, 
       0x88, 0x7, 0x22, 0x2, 0x2, 0x88, 0x89, 0x7, 0x5, 0x2, 0x2, 0x89, 
       0x8a, 0x5, 0x18, 0xd, 0x2, 0x8a, 0x8b, 0x7, 0x6, 0x2, 0x2, 0x8b, 
       0x8c, 0x5, 0x14, 0xb, 0x2, 0x8c, 0x97, 0x3, 0x2, 0x2, 0x2, 0x8d, 
       0x8e, 0x7, 0x23, 0x2, 0x2, 0x8e, 0x97, 0x7, 0x4, 0x2, 0x2, 0x8f, 
       0x90, 0x7, 0x24, 0x2, 0x2, 0x90, 0x97, 0x7, 0x4, 0x2, 0x2, 0x91, 
       0x93, 0x7, 0x25, 0x2, 0x2, 0x92, 0x94, 0x5, 0x1a, 0xe, 0x2, 0x93, 
       0x92, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x3, 0x2, 0x2, 0x2, 0x94, 0x95, 
       0x3, 0x2, 0x2, 0x2, 0x95, 0x97, 0x7, 0x4, 0x2, 0x2, 0x96, 0x74, 0x3, 
       0x2, 0x2, 0x2, 0x96, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x96, 0x7d, 0x3, 0x2, 
       0x2, 0x2, 0x96, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x96, 0x87, 0x3, 0x2, 0x2, 
       0x2, 0x96, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x96, 0x8f, 0x3, 0x2, 0x2, 0x2, 
       0x96, 0x91, 0x3, 0x2, 0x2, 0x2, 0x97, 0x15, 0x3, 0x2, 0x2, 0x2, 0x98, 
       0xa5, 0x5, 0x1a, 0xe, 0x2, 0x99, 0x9a, 0x7, 0xa, 0x2, 0x2, 0x9a, 
       0x9f, 0x5, 0x16, 0xc, 0x2, 0x9b, 0x9c, 0x7, 0x3, 0x2, 0x2, 0x9c, 
       0x9e, 0x5, 0x16, 0xc, 0x2, 0x9d, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9e, 
       0xa1, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x9f, 0xa0, 
       0x3, 0x2, 0x2, 0x2, 0xa0, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa1, 0x9f, 0x3, 
       0x2, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0xb, 0x2, 0x2, 0xa3, 0xa5, 0x3, 0x2, 
       0x2, 0x2, 0xa4, 0x98, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x99, 0x3, 0x2, 0x2, 
       0x2, 0xa5, 0x17, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x8, 0xd, 0x1, 0x2, 
       0xa7, 0xa8, 0x5, 0x1a, 0xe, 0x2, 0xa8, 0xb7, 0x3, 0x2, 0x2, 0x2, 
       0xa9, 0xaa, 0xc, 0x6, 0x2, 0x2, 0xaa, 0xab, 0x9, 0x4, 0x2, 0x2, 0xab, 
       0xb6, 0x5, 0x18, 0xd, 0x7, 0xac, 0xad, 0xc, 0x5, 0x2, 0x2, 0xad, 
       0xae, 0x9, 0x5, 0x2, 0x2, 0xae, 0xb6, 0x5, 0x18, 0xd, 0x6, 0xaf, 
       0xb0, 0xc, 0x4, 0x2, 0x2, 0xb0, 0xb1, 0x7, 0x12, 0x2, 0x2, 0xb1, 
       0xb6, 0x5, 0x18, 0xd, 0x5, 0xb2, 0xb3, 0xc, 0x3, 0x2, 0x2, 0xb3, 
       0xb4, 0x7, 0x13, 0x2, 0x2, 0xb4, 0xb6, 0x5, 0x18, 0xd, 0x4, 0xb5, 
       0xa9, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xac, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xaf, 
       0x3, 0x2, 0x2, 0x2, 0xb5, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb9, 0x3, 
       0x2, 0x2, 0x2, 0xb7, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 0x3, 0x2, 
       0x2, 0x2, 0xb8, 0x19, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xb7, 0x3, 0x2, 0x2, 
       0x2, 0xba, 0xbb, 0x8, 0xe, 0x1, 0x2, 0xbb, 0xd2, 0x7, 0x26, 0x2, 
       0x2, 0xbc, 0xd2, 0x7, 0x27, 0x2, 0x2, 0xbd, 0xd2, 0x5, 0x1c, 0xf, 
       0x2, 0xbe, 0xbf, 0x7, 0x29, 0x2, 0x2, 0xbf, 0xc8, 0x7, 0x5, 0x2, 
       0x2, 0xc0, 0xc5, 0x5, 0x1a, 0xe, 0x2, 0xc1, 0xc2, 0x7, 0x3, 0x2, 
       0x2, 0xc2, 0xc4, 0x5, 0x1a, 0xe, 0x2, 0xc3, 0xc1, 0x3, 0x2, 0x2, 
       0x2, 0xc4, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc3, 0x3, 0x2, 0x2, 0x2, 
       0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xc7, 
       0xc5, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xc9, 
       0x3, 0x2, 0x2, 0x2, 0xc9, 0xca, 0x3, 0x2, 0x2, 0x2, 0xca, 0xd2, 0x7, 
       0x6, 0x2, 0x2, 0xcb, 0xcc, 0x7, 0x5, 0x2, 0x2, 0xcc, 0xcd, 0x5, 0x1a, 
       0xe, 0x2, 0xcd, 0xce, 0x7, 0x6, 0x2, 0x2, 0xce, 0xd2, 0x3, 0x2, 0x2, 
       0x2, 0xcf, 0xd0, 0x9, 0x6, 0x2, 0x2, 0xd0, 0xd2, 0x5, 0x1a, 0xe, 
       0x5, 0xd1, 0xba, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xbc, 0x3, 0x2, 0x2, 0x2, 
       0xd1, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xd1, 
       0xcb, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xdb, 
       0x3, 0x2, 0x2, 0x2, 0xd3, 0xd4, 0xc, 0x4, 0x2, 0x2, 0xd4, 0xd5, 0x9, 
       0x7, 0x2, 0x2, 0xd5, 0xda, 0x5, 0x1a, 0xe, 0x5, 0xd6, 0xd7, 0xc, 
       0x3, 0x2, 0x2, 0xd7, 0xd8, 0x9, 0x8, 0x2, 0x2, 0xd8, 0xda, 0x5, 0x1a, 
       0xe, 0x4, 0xd9, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xd6, 0x3, 0x2, 0x2, 
       0x2, 0xda, 0xdd, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xd9, 0x3, 0x2, 0x2, 0x2, 
       0xdb, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xdc, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xdd, 
       0xdb, 0x3, 0x2, 0x2, 0x2, 0xde, 0xe2, 0x7, 0x29, 0x2, 0x2, 0xdf, 
       0xe1, 0x5, 0x1e, 0x10, 0x2, 0xe0, 0xdf, 0x3, 0x2, 0x2, 0x2, 0xe1, 
       0xe4, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe3, 
       0x3, 0x2, 0x2, 0x2, 0xe3, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe2, 0x3, 
       0x2, 0x2, 0x2, 0xe5, 0xe6, 0x7, 0x8, 0x2, 0x2, 0xe6, 0xe7, 0x5, 0x1a, 
       0xe, 0x2, 0xe7, 0xe8, 0x7, 0x9, 0x2, 0x2, 0xe8, 0x1f, 0x3, 0x2, 0x2, 
       0x2, 0x1c, 0x23, 0x25, 0x2e, 0x39, 0x46, 0x49, 0x56, 0x5b, 0x64, 
       0x67, 0x6d, 0x6f, 0x7a, 0x85, 0x93, 0x96, 0x9f, 0xa4, 0xb5, 0xb7, 
       0xc5, 0xc8, 0xd1, 0xd9, 0xdb, 0xe2, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

SysYParser::Initializer SysYParser::_init;
