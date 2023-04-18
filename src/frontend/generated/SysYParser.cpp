
// Generated from src/frontend/grammar/SysY.g4 by ANTLR 4.12.0


#include "SysYListener.h"

#include "SysYParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SysYParserStaticData final {
  SysYParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SysYParserStaticData(const SysYParserStaticData&) = delete;
  SysYParserStaticData(SysYParserStaticData&&) = delete;
  SysYParserStaticData& operator=(const SysYParserStaticData&) = delete;
  SysYParserStaticData& operator=(SysYParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sysyParserOnceFlag;
SysYParserStaticData *sysyParserStaticData = nullptr;

void sysyParserInitialize() {
  assert(sysyParserStaticData == nullptr);
  auto staticData = std::make_unique<SysYParserStaticData>(
    std::vector<std::string>{
      "compUnit", "decl", "comDecl", "bType", "comDef", "initVal", "exp", 
      "mulExp", "unaryExp", "priExp", "lVal"
    },
    std::vector<std::string>{
      "", "','", "';'", "'int'", "'float'", "'['", "']'", "'='", "'{'", 
      "'}'", "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "WS", "COMMENT", "IntConstant", "FloatConstant", "DigitSequence", 
      "Ident"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,22,107,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,1,0,4,0,24,8,0,11,0,12,0,25,1,1,1,1,1,
  	2,1,2,1,2,1,2,5,2,34,8,2,10,2,12,2,37,9,2,1,2,1,2,1,3,1,3,1,4,1,4,1,4,
  	1,4,1,4,5,4,48,8,4,10,4,12,4,51,9,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,
  	5,61,8,5,10,5,12,5,64,9,5,1,5,1,5,3,5,68,8,5,1,6,1,6,1,6,5,6,73,8,6,10,
  	6,12,6,76,9,6,1,7,1,7,1,7,5,7,81,8,7,10,7,12,7,84,9,7,1,8,1,8,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,3,9,95,8,9,1,10,1,10,1,10,1,10,1,10,5,10,102,8,10,
  	10,10,12,10,105,9,10,1,10,0,0,11,0,2,4,6,8,10,12,14,16,18,20,0,3,1,0,
  	3,4,1,0,10,11,1,0,12,14,106,0,23,1,0,0,0,2,27,1,0,0,0,4,29,1,0,0,0,6,
  	40,1,0,0,0,8,42,1,0,0,0,10,67,1,0,0,0,12,69,1,0,0,0,14,77,1,0,0,0,16,
  	85,1,0,0,0,18,94,1,0,0,0,20,96,1,0,0,0,22,24,3,2,1,0,23,22,1,0,0,0,24,
  	25,1,0,0,0,25,23,1,0,0,0,25,26,1,0,0,0,26,1,1,0,0,0,27,28,3,4,2,0,28,
  	3,1,0,0,0,29,30,3,6,3,0,30,35,3,8,4,0,31,32,5,1,0,0,32,34,3,8,4,0,33,
  	31,1,0,0,0,34,37,1,0,0,0,35,33,1,0,0,0,35,36,1,0,0,0,36,38,1,0,0,0,37,
  	35,1,0,0,0,38,39,5,2,0,0,39,5,1,0,0,0,40,41,7,0,0,0,41,7,1,0,0,0,42,49,
  	5,22,0,0,43,44,5,5,0,0,44,45,3,12,6,0,45,46,5,6,0,0,46,48,1,0,0,0,47,
  	43,1,0,0,0,48,51,1,0,0,0,49,47,1,0,0,0,49,50,1,0,0,0,50,52,1,0,0,0,51,
  	49,1,0,0,0,52,53,5,7,0,0,53,54,3,10,5,0,54,9,1,0,0,0,55,68,3,12,6,0,56,
  	57,5,8,0,0,57,62,3,10,5,0,58,59,5,1,0,0,59,61,3,10,5,0,60,58,1,0,0,0,
  	61,64,1,0,0,0,62,60,1,0,0,0,62,63,1,0,0,0,63,65,1,0,0,0,64,62,1,0,0,0,
  	65,66,5,9,0,0,66,68,1,0,0,0,67,55,1,0,0,0,67,56,1,0,0,0,68,11,1,0,0,0,
  	69,74,3,14,7,0,70,71,7,1,0,0,71,73,3,14,7,0,72,70,1,0,0,0,73,76,1,0,0,
  	0,74,72,1,0,0,0,74,75,1,0,0,0,75,13,1,0,0,0,76,74,1,0,0,0,77,82,3,16,
  	8,0,78,79,7,2,0,0,79,81,3,16,8,0,80,78,1,0,0,0,81,84,1,0,0,0,82,80,1,
  	0,0,0,82,83,1,0,0,0,83,15,1,0,0,0,84,82,1,0,0,0,85,86,3,18,9,0,86,17,
  	1,0,0,0,87,88,5,15,0,0,88,89,3,12,6,0,89,90,5,16,0,0,90,95,1,0,0,0,91,
  	95,3,20,10,0,92,95,5,19,0,0,93,95,5,20,0,0,94,87,1,0,0,0,94,91,1,0,0,
  	0,94,92,1,0,0,0,94,93,1,0,0,0,95,19,1,0,0,0,96,103,5,22,0,0,97,98,5,5,
  	0,0,98,99,3,12,6,0,99,100,5,6,0,0,100,102,1,0,0,0,101,97,1,0,0,0,102,
  	105,1,0,0,0,103,101,1,0,0,0,103,104,1,0,0,0,104,21,1,0,0,0,105,103,1,
  	0,0,0,9,25,35,49,62,67,74,82,94,103
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sysyParserStaticData = staticData.release();
}

}

SysYParser::SysYParser(TokenStream *input) : SysYParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

SysYParser::SysYParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  SysYParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *sysyParserStaticData->atn, sysyParserStaticData->decisionToDFA, sysyParserStaticData->sharedContextCache, options);
}

SysYParser::~SysYParser() {
  delete _interpreter;
}

const atn::ATN& SysYParser::getATN() const {
  return *sysyParserStaticData->atn;
}

std::string SysYParser::getGrammarFileName() const {
  return "SysY.g4";
}

const std::vector<std::string>& SysYParser::getRuleNames() const {
  return sysyParserStaticData->ruleNames;
}

const dfa::Vocabulary& SysYParser::getVocabulary() const {
  return sysyParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SysYParser::getSerializedATN() const {
  return sysyParserStaticData->serializedATN;
}


//----------------- CompUnitContext ------------------------------------------------------------------

SysYParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::DeclContext *> SysYParser::CompUnitContext::decl() {
  return getRuleContexts<SysYParser::DeclContext>();
}

SysYParser::DeclContext* SysYParser::CompUnitContext::decl(size_t i) {
  return getRuleContext<SysYParser::DeclContext>(i);
}


size_t SysYParser::CompUnitContext::getRuleIndex() const {
  return SysYParser::RuleCompUnit;
}

void SysYParser::CompUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompUnit(this);
}

void SysYParser::CompUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompUnit(this);
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
    setState(23); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(22);
      decl();
      setState(25); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == SysYParser::T__2

    || _la == SysYParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

SysYParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::ComDeclContext* SysYParser::DeclContext::comDecl() {
  return getRuleContext<SysYParser::ComDeclContext>(0);
}


size_t SysYParser::DeclContext::getRuleIndex() const {
  return SysYParser::RuleDecl;
}

void SysYParser::DeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecl(this);
}

void SysYParser::DeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecl(this);
}

SysYParser::DeclContext* SysYParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, SysYParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(27);
    comDecl();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComDeclContext ------------------------------------------------------------------

SysYParser::ComDeclContext::ComDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::BTypeContext* SysYParser::ComDeclContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

std::vector<SysYParser::ComDefContext *> SysYParser::ComDeclContext::comDef() {
  return getRuleContexts<SysYParser::ComDefContext>();
}

SysYParser::ComDefContext* SysYParser::ComDeclContext::comDef(size_t i) {
  return getRuleContext<SysYParser::ComDefContext>(i);
}


size_t SysYParser::ComDeclContext::getRuleIndex() const {
  return SysYParser::RuleComDecl;
}

void SysYParser::ComDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComDecl(this);
}

void SysYParser::ComDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComDecl(this);
}

SysYParser::ComDeclContext* SysYParser::comDecl() {
  ComDeclContext *_localctx = _tracker.createInstance<ComDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, SysYParser::RuleComDecl);
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
    setState(29);
    bType();
    setState(30);
    comDef();
    setState(35);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__0) {
      setState(31);
      match(SysYParser::T__0);
      setState(32);
      comDef();
      setState(37);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(38);
    match(SysYParser::T__1);
   
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


size_t SysYParser::BTypeContext::getRuleIndex() const {
  return SysYParser::RuleBType;
}

void SysYParser::BTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBType(this);
}

void SysYParser::BTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBType(this);
}

SysYParser::BTypeContext* SysYParser::bType() {
  BTypeContext *_localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, SysYParser::RuleBType);
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
    setState(40);
    _la = _input->LA(1);
    if (!(_la == SysYParser::T__2

    || _la == SysYParser::T__3)) {
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

//----------------- ComDefContext ------------------------------------------------------------------

SysYParser::ComDefContext::ComDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::ComDefContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

SysYParser::InitValContext* SysYParser::ComDefContext::initVal() {
  return getRuleContext<SysYParser::InitValContext>(0);
}

std::vector<SysYParser::ExpContext *> SysYParser::ComDefContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::ComDefContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}


size_t SysYParser::ComDefContext::getRuleIndex() const {
  return SysYParser::RuleComDef;
}

void SysYParser::ComDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComDef(this);
}

void SysYParser::ComDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComDef(this);
}

SysYParser::ComDefContext* SysYParser::comDef() {
  ComDefContext *_localctx = _tracker.createInstance<ComDefContext>(_ctx, getState());
  enterRule(_localctx, 8, SysYParser::RuleComDef);
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
    setState(42);
    match(SysYParser::Ident);
    setState(49);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__4) {
      setState(43);
      match(SysYParser::T__4);
      setState(44);
      exp();
      setState(45);
      match(SysYParser::T__5);
      setState(51);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

    setState(52);
    match(SysYParser::T__6);
    setState(53);
    initVal();
   
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

void SysYParser::InitValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitVal(this);
}

void SysYParser::InitValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitVal(this);
}

SysYParser::InitValContext* SysYParser::initVal() {
  InitValContext *_localctx = _tracker.createInstance<InitValContext>(_ctx, getState());
  enterRule(_localctx, 10, SysYParser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(67);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__14:
      case SysYParser::IntConstant:
      case SysYParser::FloatConstant:
      case SysYParser::Ident: {
        enterOuterAlt(_localctx, 1);
        setState(55);
        exp();
        break;
      }

      case SysYParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(56);
        match(SysYParser::T__7);
        setState(57);
        initVal();
        setState(62);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysYParser::T__0) {
          setState(58);
          match(SysYParser::T__0);
          setState(59);
          initVal();
          setState(64);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(65);
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

//----------------- ExpContext ------------------------------------------------------------------

SysYParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::MulExpContext *> SysYParser::ExpContext::mulExp() {
  return getRuleContexts<SysYParser::MulExpContext>();
}

SysYParser::MulExpContext* SysYParser::ExpContext::mulExp(size_t i) {
  return getRuleContext<SysYParser::MulExpContext>(i);
}


size_t SysYParser::ExpContext::getRuleIndex() const {
  return SysYParser::RuleExp;
}

void SysYParser::ExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExp(this);
}

void SysYParser::ExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExp(this);
}

SysYParser::ExpContext* SysYParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 12, SysYParser::RuleExp);
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
    setState(69);
    mulExp();
    setState(74);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__9

    || _la == SysYParser::T__10) {
      setState(70);
      _la = _input->LA(1);
      if (!(_la == SysYParser::T__9

      || _la == SysYParser::T__10)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(71);
      mulExp();
      setState(76);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpContext ------------------------------------------------------------------

SysYParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::UnaryExpContext *> SysYParser::MulExpContext::unaryExp() {
  return getRuleContexts<SysYParser::UnaryExpContext>();
}

SysYParser::UnaryExpContext* SysYParser::MulExpContext::unaryExp(size_t i) {
  return getRuleContext<SysYParser::UnaryExpContext>(i);
}


size_t SysYParser::MulExpContext::getRuleIndex() const {
  return SysYParser::RuleMulExp;
}

void SysYParser::MulExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulExp(this);
}

void SysYParser::MulExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulExp(this);
}

SysYParser::MulExpContext* SysYParser::mulExp() {
  MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, getState());
  enterRule(_localctx, 14, SysYParser::RuleMulExp);
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
    setState(77);
    unaryExp();
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28672) != 0)) {
      setState(78);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 28672) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(79);
      unaryExp();
      setState(84);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpContext ------------------------------------------------------------------

SysYParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::PriExpContext* SysYParser::UnaryExpContext::priExp() {
  return getRuleContext<SysYParser::PriExpContext>(0);
}


size_t SysYParser::UnaryExpContext::getRuleIndex() const {
  return SysYParser::RuleUnaryExp;
}

void SysYParser::UnaryExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExp(this);
}

void SysYParser::UnaryExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExp(this);
}

SysYParser::UnaryExpContext* SysYParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 16, SysYParser::RuleUnaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    priExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PriExpContext ------------------------------------------------------------------

SysYParser::PriExpContext::PriExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::ExpContext* SysYParser::PriExpContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::LValContext* SysYParser::PriExpContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

tree::TerminalNode* SysYParser::PriExpContext::IntConstant() {
  return getToken(SysYParser::IntConstant, 0);
}

tree::TerminalNode* SysYParser::PriExpContext::FloatConstant() {
  return getToken(SysYParser::FloatConstant, 0);
}


size_t SysYParser::PriExpContext::getRuleIndex() const {
  return SysYParser::RulePriExp;
}

void SysYParser::PriExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPriExp(this);
}

void SysYParser::PriExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPriExp(this);
}

SysYParser::PriExpContext* SysYParser::priExp() {
  PriExpContext *_localctx = _tracker.createInstance<PriExpContext>(_ctx, getState());
  enterRule(_localctx, 18, SysYParser::RulePriExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(94);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__14: {
        enterOuterAlt(_localctx, 1);
        setState(87);
        match(SysYParser::T__14);
        setState(88);
        exp();
        setState(89);
        match(SysYParser::T__15);
        break;
      }

      case SysYParser::Ident: {
        enterOuterAlt(_localctx, 2);
        setState(91);
        lVal();
        break;
      }

      case SysYParser::IntConstant: {
        enterOuterAlt(_localctx, 3);
        setState(92);
        match(SysYParser::IntConstant);
        break;
      }

      case SysYParser::FloatConstant: {
        enterOuterAlt(_localctx, 4);
        setState(93);
        match(SysYParser::FloatConstant);
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

//----------------- LValContext ------------------------------------------------------------------

SysYParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::LValContext::Ident() {
  return getToken(SysYParser::Ident, 0);
}

std::vector<SysYParser::ExpContext *> SysYParser::LValContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::LValContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}


size_t SysYParser::LValContext::getRuleIndex() const {
  return SysYParser::RuleLVal;
}

void SysYParser::LValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLVal(this);
}

void SysYParser::LValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLVal(this);
}

SysYParser::LValContext* SysYParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 20, SysYParser::RuleLVal);
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
    setState(96);
    match(SysYParser::Ident);
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__4) {
      setState(97);
      match(SysYParser::T__4);
      setState(98);
      exp();
      setState(99);
      match(SysYParser::T__5);
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void SysYParser::initialize() {
  ::antlr4::internal::call_once(sysyParserOnceFlag, sysyParserInitialize);
}
