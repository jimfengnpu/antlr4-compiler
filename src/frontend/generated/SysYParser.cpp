
// Generated from src/frontend/grammar/SysY.g4 by ANTLR 4.12.0


#include "SysYListener.h"
#include "SysYVisitor.h"

#include "SysYParser.h"


#include "../../common/SysYIR.h"


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
      "compUnit", "decl", "funcDef", "funcType", "bType", "def", "funcFParam", 
      "funcArrParam", "block", "stmt", "initVal", "cond", "exp", "lVal", 
      "arrAccess"
    },
    std::vector<std::string>{
      "", "','", "';'", "'('", "')'", "'='", "'['", "']'", "'{'", "'}'", 
      "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", "'&&'", "'||'", "'+'", 
      "'-'", "'!'", "'*'", "'/'", "'%'", "", "", "'void'", "'int'", "'float'", 
      "'const'", "'if'", "'else'", "'while'", "'break'", "'continue'", "'return'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "WS", "COMMENT", "VoidType", "IntType", 
      "FloatType", "ConstPrefix", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", 
      "RETURN", "IntConstant", "FloatConstant", "DigitSequence", "Ident"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,39,226,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,1,0,1,0,4,0,33,8,0,11,0,12,0,34,1,1,3,1,38,8,1,1,1,1,1,1,1,1,1,5,1,
  	44,8,1,10,1,12,1,47,9,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,5,2,57,8,2,10,
  	2,12,2,60,9,2,3,2,62,8,2,1,2,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,5,5,73,8,
  	5,10,5,12,5,76,9,5,1,5,1,5,3,5,80,8,5,1,6,1,6,1,6,3,6,85,8,6,1,7,1,7,
  	1,7,5,7,90,8,7,10,7,12,7,93,9,7,1,8,1,8,1,8,5,8,98,8,8,10,8,12,8,101,
  	9,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,3,9,111,8,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,3,9,122,8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,3,9,136,8,9,1,9,3,9,139,8,9,1,10,1,10,1,10,3,10,144,8,10,1,10,1,10,
  	5,10,148,8,10,10,10,12,10,151,9,10,1,10,3,10,154,8,10,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,166,8,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,5,11,174,8,11,10,11,12,11,177,9,11,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,12,5,12,188,8,12,10,12,12,12,191,9,12,3,12,193,8,12,
  	1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,202,8,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,5,12,210,8,12,10,12,12,12,213,9,12,1,13,1,13,5,13,217,8,13,
  	10,13,12,13,220,9,13,1,14,1,14,1,14,1,14,1,14,0,2,22,24,15,0,2,4,6,8,
  	10,12,14,16,18,20,22,24,26,28,0,7,1,0,26,28,1,0,27,28,1,0,10,13,1,0,14,
  	15,1,0,18,20,1,0,21,23,1,0,18,19,249,0,32,1,0,0,0,2,37,1,0,0,0,4,50,1,
  	0,0,0,6,66,1,0,0,0,8,68,1,0,0,0,10,70,1,0,0,0,12,81,1,0,0,0,14,86,1,0,
  	0,0,16,94,1,0,0,0,18,138,1,0,0,0,20,153,1,0,0,0,22,165,1,0,0,0,24,201,
  	1,0,0,0,26,214,1,0,0,0,28,221,1,0,0,0,30,33,3,2,1,0,31,33,3,4,2,0,32,
  	30,1,0,0,0,32,31,1,0,0,0,33,34,1,0,0,0,34,32,1,0,0,0,34,35,1,0,0,0,35,
  	1,1,0,0,0,36,38,5,29,0,0,37,36,1,0,0,0,37,38,1,0,0,0,38,39,1,0,0,0,39,
  	40,3,8,4,0,40,45,3,10,5,0,41,42,5,1,0,0,42,44,3,10,5,0,43,41,1,0,0,0,
  	44,47,1,0,0,0,45,43,1,0,0,0,45,46,1,0,0,0,46,48,1,0,0,0,47,45,1,0,0,0,
  	48,49,5,2,0,0,49,3,1,0,0,0,50,51,3,6,3,0,51,52,5,39,0,0,52,61,5,3,0,0,
  	53,58,3,12,6,0,54,55,5,1,0,0,55,57,3,12,6,0,56,54,1,0,0,0,57,60,1,0,0,
  	0,58,56,1,0,0,0,58,59,1,0,0,0,59,62,1,0,0,0,60,58,1,0,0,0,61,53,1,0,0,
  	0,61,62,1,0,0,0,62,63,1,0,0,0,63,64,5,4,0,0,64,65,3,16,8,0,65,5,1,0,0,
  	0,66,67,7,0,0,0,67,7,1,0,0,0,68,69,7,1,0,0,69,9,1,0,0,0,70,74,5,39,0,
  	0,71,73,3,28,14,0,72,71,1,0,0,0,73,76,1,0,0,0,74,72,1,0,0,0,74,75,1,0,
  	0,0,75,79,1,0,0,0,76,74,1,0,0,0,77,78,5,5,0,0,78,80,3,20,10,0,79,77,1,
  	0,0,0,79,80,1,0,0,0,80,11,1,0,0,0,81,82,3,8,4,0,82,84,5,39,0,0,83,85,
  	3,14,7,0,84,83,1,0,0,0,84,85,1,0,0,0,85,13,1,0,0,0,86,87,5,6,0,0,87,91,
  	5,7,0,0,88,90,3,28,14,0,89,88,1,0,0,0,90,93,1,0,0,0,91,89,1,0,0,0,91,
  	92,1,0,0,0,92,15,1,0,0,0,93,91,1,0,0,0,94,99,5,8,0,0,95,98,3,2,1,0,96,
  	98,3,18,9,0,97,95,1,0,0,0,97,96,1,0,0,0,98,101,1,0,0,0,99,97,1,0,0,0,
  	99,100,1,0,0,0,100,102,1,0,0,0,101,99,1,0,0,0,102,103,5,9,0,0,103,17,
  	1,0,0,0,104,105,3,26,13,0,105,106,5,5,0,0,106,107,3,24,12,0,107,108,5,
  	2,0,0,108,139,1,0,0,0,109,111,3,24,12,0,110,109,1,0,0,0,110,111,1,0,0,
  	0,111,112,1,0,0,0,112,139,5,2,0,0,113,139,3,16,8,0,114,115,5,30,0,0,115,
  	116,5,3,0,0,116,117,3,22,11,0,117,118,5,4,0,0,118,121,3,18,9,0,119,120,
  	5,31,0,0,120,122,3,18,9,0,121,119,1,0,0,0,121,122,1,0,0,0,122,139,1,0,
  	0,0,123,124,5,32,0,0,124,125,5,3,0,0,125,126,3,22,11,0,126,127,5,4,0,
  	0,127,128,3,18,9,0,128,139,1,0,0,0,129,130,5,33,0,0,130,139,5,2,0,0,131,
  	132,5,34,0,0,132,139,5,2,0,0,133,135,5,35,0,0,134,136,3,24,12,0,135,134,
  	1,0,0,0,135,136,1,0,0,0,136,137,1,0,0,0,137,139,5,2,0,0,138,104,1,0,0,
  	0,138,110,1,0,0,0,138,113,1,0,0,0,138,114,1,0,0,0,138,123,1,0,0,0,138,
  	129,1,0,0,0,138,131,1,0,0,0,138,133,1,0,0,0,139,19,1,0,0,0,140,154,3,
  	24,12,0,141,143,5,8,0,0,142,144,3,20,10,0,143,142,1,0,0,0,143,144,1,0,
  	0,0,144,149,1,0,0,0,145,146,5,1,0,0,146,148,3,20,10,0,147,145,1,0,0,0,
  	148,151,1,0,0,0,149,147,1,0,0,0,149,150,1,0,0,0,150,152,1,0,0,0,151,149,
  	1,0,0,0,152,154,5,9,0,0,153,140,1,0,0,0,153,141,1,0,0,0,154,21,1,0,0,
  	0,155,156,6,11,-1,0,156,166,3,24,12,0,157,158,3,24,12,0,158,159,7,2,0,
  	0,159,160,3,24,12,0,160,166,1,0,0,0,161,162,3,24,12,0,162,163,7,3,0,0,
  	163,164,3,24,12,0,164,166,1,0,0,0,165,155,1,0,0,0,165,157,1,0,0,0,165,
  	161,1,0,0,0,166,175,1,0,0,0,167,168,10,2,0,0,168,169,5,16,0,0,169,174,
  	3,22,11,3,170,171,10,1,0,0,171,172,5,17,0,0,172,174,3,22,11,2,173,167,
  	1,0,0,0,173,170,1,0,0,0,174,177,1,0,0,0,175,173,1,0,0,0,175,176,1,0,0,
  	0,176,23,1,0,0,0,177,175,1,0,0,0,178,179,6,12,-1,0,179,202,5,36,0,0,180,
  	202,5,37,0,0,181,202,3,26,13,0,182,183,5,39,0,0,183,192,5,3,0,0,184,189,
  	3,24,12,0,185,186,5,1,0,0,186,188,3,24,12,0,187,185,1,0,0,0,188,191,1,
  	0,0,0,189,187,1,0,0,0,189,190,1,0,0,0,190,193,1,0,0,0,191,189,1,0,0,0,
  	192,184,1,0,0,0,192,193,1,0,0,0,193,194,1,0,0,0,194,202,5,4,0,0,195,196,
  	5,3,0,0,196,197,3,24,12,0,197,198,5,4,0,0,198,202,1,0,0,0,199,200,7,4,
  	0,0,200,202,3,24,12,3,201,178,1,0,0,0,201,180,1,0,0,0,201,181,1,0,0,0,
  	201,182,1,0,0,0,201,195,1,0,0,0,201,199,1,0,0,0,202,211,1,0,0,0,203,204,
  	10,2,0,0,204,205,7,5,0,0,205,210,3,24,12,3,206,207,10,1,0,0,207,208,7,
  	6,0,0,208,210,3,24,12,2,209,203,1,0,0,0,209,206,1,0,0,0,210,213,1,0,0,
  	0,211,209,1,0,0,0,211,212,1,0,0,0,212,25,1,0,0,0,213,211,1,0,0,0,214,
  	218,5,39,0,0,215,217,3,28,14,0,216,215,1,0,0,0,217,220,1,0,0,0,218,216,
  	1,0,0,0,218,219,1,0,0,0,219,27,1,0,0,0,220,218,1,0,0,0,221,222,5,6,0,
  	0,222,223,3,24,12,0,223,224,5,7,0,0,224,29,1,0,0,0,28,32,34,37,45,58,
  	61,74,79,84,91,97,99,110,121,135,138,143,149,153,165,173,175,189,192,
  	201,209,211,218
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

std::vector<SysYParser::FuncDefContext *> SysYParser::CompUnitContext::funcDef() {
  return getRuleContexts<SysYParser::FuncDefContext>();
}

SysYParser::FuncDefContext* SysYParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<SysYParser::FuncDefContext>(i);
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


std::any SysYParser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
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
    setState(32); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(32);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(30);
        decl();
        break;
      }

      case 2: {
        setState(31);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(34); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1006632960) != 0));
   
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

SysYParser::BTypeContext* SysYParser::DeclContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

std::vector<SysYParser::DefContext *> SysYParser::DeclContext::def() {
  return getRuleContexts<SysYParser::DefContext>();
}

SysYParser::DefContext* SysYParser::DeclContext::def(size_t i) {
  return getRuleContext<SysYParser::DefContext>(i);
}

tree::TerminalNode* SysYParser::DeclContext::ConstPrefix() {
  return getToken(SysYParser::ConstPrefix, 0);
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


std::any SysYParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::DeclContext* SysYParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, SysYParser::RuleDecl);
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
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::ConstPrefix) {
      setState(36);
      match(SysYParser::ConstPrefix);
    }
    setState(39);
    bType();
    setState(40);
    def();
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__0) {
      setState(41);
      match(SysYParser::T__0);
      setState(42);
      def();
      setState(47);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(48);
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

void SysYParser::FuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDef(this);
}

void SysYParser::FuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDef(this);
}


std::any SysYParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncDefContext* SysYParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 4, SysYParser::RuleFuncDef);
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
    setState(50);
    funcType();
    setState(51);
    match(SysYParser::Ident);
    setState(52);
    match(SysYParser::T__2);
    setState(61);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::IntType

    || _la == SysYParser::FloatType) {
      setState(53);
      funcFParam();
      setState(58);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__0) {
        setState(54);
        match(SysYParser::T__0);
        setState(55);
        funcFParam();
        setState(60);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(63);
    match(SysYParser::T__3);
    setState(64);
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

void SysYParser::FuncTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncType(this);
}

void SysYParser::FuncTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncType(this);
}


std::any SysYParser::FuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncType(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncTypeContext* SysYParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, SysYParser::RuleFuncType);
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
    setState(66);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 469762048) != 0))) {
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


std::any SysYParser::BTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBType(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::BTypeContext* SysYParser::bType() {
  BTypeContext *_localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
  enterRule(_localctx, 8, SysYParser::RuleBType);
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
    setState(68);
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

void SysYParser::DefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef(this);
}

void SysYParser::DefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef(this);
}


std::any SysYParser::DefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitDef(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::DefContext* SysYParser::def() {
  DefContext *_localctx = _tracker.createInstance<DefContext>(_ctx, getState());
  enterRule(_localctx, 10, SysYParser::RuleDef);
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
    setState(70);
    match(SysYParser::Ident);
    setState(74);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__5) {
      setState(71);
      arrAccess();
      setState(76);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(79);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::T__4) {
      setState(77);
      match(SysYParser::T__4);
      setState(78);
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

SysYParser::FuncArrParamContext* SysYParser::FuncFParamContext::funcArrParam() {
  return getRuleContext<SysYParser::FuncArrParamContext>(0);
}


size_t SysYParser::FuncFParamContext::getRuleIndex() const {
  return SysYParser::RuleFuncFParam;
}

void SysYParser::FuncFParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncFParam(this);
}

void SysYParser::FuncFParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncFParam(this);
}


std::any SysYParser::FuncFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncFParam(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncFParamContext* SysYParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 12, SysYParser::RuleFuncFParam);
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
    setState(81);
    bType();
    setState(82);
    match(SysYParser::Ident);
    setState(84);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::T__5) {
      setState(83);
      funcArrParam();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncArrParamContext ------------------------------------------------------------------

SysYParser::FuncArrParamContext::FuncArrParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::ArrAccessContext *> SysYParser::FuncArrParamContext::arrAccess() {
  return getRuleContexts<SysYParser::ArrAccessContext>();
}

SysYParser::ArrAccessContext* SysYParser::FuncArrParamContext::arrAccess(size_t i) {
  return getRuleContext<SysYParser::ArrAccessContext>(i);
}


size_t SysYParser::FuncArrParamContext::getRuleIndex() const {
  return SysYParser::RuleFuncArrParam;
}

void SysYParser::FuncArrParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncArrParam(this);
}

void SysYParser::FuncArrParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncArrParam(this);
}


std::any SysYParser::FuncArrParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncArrParam(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncArrParamContext* SysYParser::funcArrParam() {
  FuncArrParamContext *_localctx = _tracker.createInstance<FuncArrParamContext>(_ctx, getState());
  enterRule(_localctx, 14, SysYParser::RuleFuncArrParam);
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
    setState(86);
    match(SysYParser::T__5);
    setState(87);
    match(SysYParser::T__6);
    setState(91);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__5) {
      setState(88);
      arrAccess();
      setState(93);
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

//----------------- BlockContext ------------------------------------------------------------------

SysYParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::DeclContext *> SysYParser::BlockContext::decl() {
  return getRuleContexts<SysYParser::DeclContext>();
}

SysYParser::DeclContext* SysYParser::BlockContext::decl(size_t i) {
  return getRuleContext<SysYParser::DeclContext>(i);
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

void SysYParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void SysYParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any SysYParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
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
    setState(94);
    match(SysYParser::T__7);
    setState(99);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 822353854732) != 0)) {
      setState(97);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case SysYParser::IntType:
        case SysYParser::FloatType:
        case SysYParser::ConstPrefix: {
          setState(95);
          decl();
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
          setState(96);
          stmt();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(101);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(102);
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

void SysYParser::LoopStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoopStmt(this);
}
void SysYParser::LoopStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoopStmt(this);
}

std::any SysYParser::LoopStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLoopStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStmtContext ------------------------------------------------------------------

SysYParser::BlockContext* SysYParser::BlockStmtContext::block() {
  return getRuleContext<SysYParser::BlockContext>(0);
}

SysYParser::BlockStmtContext::BlockStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::BlockStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockStmt(this);
}
void SysYParser::BlockStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockStmt(this);
}

std::any SysYParser::BlockStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBlockStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStmtContext ------------------------------------------------------------------

SysYParser::LValContext* SysYParser::AssignStmtContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

SysYParser::ExpContext* SysYParser::AssignStmtContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::AssignStmtContext::AssignStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::AssignStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignStmt(this);
}
void SysYParser::AssignStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignStmt(this);
}

std::any SysYParser::AssignStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitAssignStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::BreakStmtContext::BREAK() {
  return getToken(SysYParser::BREAK, 0);
}

SysYParser::BreakStmtContext::BreakStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::BreakStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStmt(this);
}
void SysYParser::BreakStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStmt(this);
}

std::any SysYParser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpStmtContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::ExpStmtContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::ExpStmtContext::ExpStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::ExpStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpStmt(this);
}
void SysYParser::ExpStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpStmt(this);
}

std::any SysYParser::ExpStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitExpStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ReturnStmtContext::RETURN() {
  return getToken(SysYParser::RETURN, 0);
}

SysYParser::ExpContext* SysYParser::ReturnStmtContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::ReturnStmtContext::ReturnStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::ReturnStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStmt(this);
}
void SysYParser::ReturnStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStmt(this);
}

std::any SysYParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ContStmtContext::CONTINUE() {
  return getToken(SysYParser::CONTINUE, 0);
}

SysYParser::ContStmtContext::ContStmtContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::ContStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContStmt(this);
}
void SysYParser::ContStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContStmt(this);
}

std::any SysYParser::ContStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitContStmt(this);
  else
    return visitor->visitChildren(this);
}
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

void SysYParser::CondStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondStmt(this);
}
void SysYParser::CondStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondStmt(this);
}

std::any SysYParser::CondStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitCondStmt(this);
  else
    return visitor->visitChildren(this);
}
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
    setState(138);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(104);
      lVal();
      setState(105);
      match(SysYParser::T__4);
      setState(106);
      exp(0);
      setState(107);
      match(SysYParser::T__1);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::ExpStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(110);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 755916079112) != 0)) {
        setState(109);
        exp(0);
      }
      setState(112);
      match(SysYParser::T__1);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::BlockStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(113);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SysYParser::CondStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(114);
      match(SysYParser::IF);
      setState(115);
      match(SysYParser::T__2);
      setState(116);
      cond(0);
      setState(117);
      match(SysYParser::T__3);
      setState(118);
      stmt();
      setState(121);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(119);
        match(SysYParser::ELSE);
        setState(120);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SysYParser::LoopStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(123);
      match(SysYParser::WHILE);
      setState(124);
      match(SysYParser::T__2);
      setState(125);
      cond(0);
      setState(126);
      match(SysYParser::T__3);
      setState(127);
      stmt();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SysYParser::BreakStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(129);
      match(SysYParser::BREAK);
      setState(130);
      match(SysYParser::T__1);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SysYParser::ContStmtContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(131);
      match(SysYParser::CONTINUE);
      setState(132);
      match(SysYParser::T__1);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<SysYParser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(133);
      match(SysYParser::RETURN);
      setState(135);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 755916079112) != 0)) {
        setState(134);
        exp(0);
      }
      setState(137);
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


std::any SysYParser::InitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitInitVal(this);
  else
    return visitor->visitChildren(this);
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
    setState(153);
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
        setState(140);
        exp(0);
        break;
      }

      case SysYParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(141);
        match(SysYParser::T__7);
        setState(143);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 755916079368) != 0)) {
          setState(142);
          initVal();
        }
        setState(149);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysYParser::T__0) {
          setState(145);
          match(SysYParser::T__0);
          setState(146);
          initVal();
          setState(151);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(152);
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

std::vector<SysYParser::ExpContext *> SysYParser::CondContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::CondContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
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

void SysYParser::CondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCond(this);
}

void SysYParser::CondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCond(this);
}


std::any SysYParser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
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
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(156);
      exp(0);
      break;
    }

    case 2: {
      setState(157);
      exp(0);
      setState(158);
      antlrcpp::downCast<CondContext *>(_localctx)->comp = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 15360) != 0))) {
        antlrcpp::downCast<CondContext *>(_localctx)->comp = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(159);
      exp(0);
      break;
    }

    case 3: {
      setState(161);
      exp(0);
      setState(162);
      antlrcpp::downCast<CondContext *>(_localctx)->comp = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == SysYParser::T__13

      || _la == SysYParser::T__14)) {
        antlrcpp::downCast<CondContext *>(_localctx)->comp = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(163);
      exp(0);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(175);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(173);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(167);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(168);
          antlrcpp::downCast<CondContext *>(_localctx)->lop = match(SysYParser::T__15);
          setState(169);
          cond(3);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(170);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(171);
          antlrcpp::downCast<CondContext *>(_localctx)->lop = match(SysYParser::T__16);
          setState(172);
          cond(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(177);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
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


std::any SysYParser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
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
    setState(201);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      setState(179);
      match(SysYParser::IntConstant);
      break;
    }

    case 2: {
      setState(180);
      match(SysYParser::FloatConstant);
      break;
    }

    case 3: {
      setState(181);
      lVal();
      break;
    }

    case 4: {
      setState(182);
      match(SysYParser::Ident);
      setState(183);
      match(SysYParser::T__2);
      setState(192);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 755916079112) != 0)) {
        setState(184);
        exp(0);
        setState(189);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysYParser::T__0) {
          setState(185);
          match(SysYParser::T__0);
          setState(186);
          exp(0);
          setState(191);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(194);
      match(SysYParser::T__3);
      break;
    }

    case 5: {
      setState(195);
      match(SysYParser::T__2);
      setState(196);
      exp(0);
      setState(197);
      match(SysYParser::T__3);
      break;
    }

    case 6: {
      setState(199);
      antlrcpp::downCast<ExpContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1835008) != 0))) {
        antlrcpp::downCast<ExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(200);
      exp(3);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(211);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(209);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(203);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(204);
          antlrcpp::downCast<ExpContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 14680064) != 0))) {
            antlrcpp::downCast<ExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(205);
          exp(3);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(206);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(207);
          antlrcpp::downCast<ExpContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == SysYParser::T__17

          || _la == SysYParser::T__18)) {
            antlrcpp::downCast<ExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(208);
          exp(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(213);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
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


std::any SysYParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
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
    setState(214);
    match(SysYParser::Ident);
    setState(218);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(215);
        arrAccess(); 
      }
      setState(220);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
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

void SysYParser::ArrAccessContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrAccess(this);
}

void SysYParser::ArrAccessContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrAccess(this);
}


std::any SysYParser::ArrAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitArrAccess(this);
  else
    return visitor->visitChildren(this);
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
    setState(221);
    match(SysYParser::T__5);
    setState(222);
    exp(0);
    setState(223);
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
    case 11: return condSempred(antlrcpp::downCast<CondContext *>(context), predicateIndex);
    case 12: return expSempred(antlrcpp::downCast<ExpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SysYParser::condSempred(CondContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::expSempred(ExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 2);
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void SysYParser::initialize() {
  ::antlr4::internal::call_once(sysyParserOnceFlag, sysyParserInitialize);
}
