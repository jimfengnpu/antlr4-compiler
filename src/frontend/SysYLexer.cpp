
// Generated from src/frontend/grammar/SysY.g4 by ANTLR 4.12.0


#include "SysYLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct SysYLexerStaticData final {
  SysYLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SysYLexerStaticData(const SysYLexerStaticData&) = delete;
  SysYLexerStaticData(SysYLexerStaticData&&) = delete;
  SysYLexerStaticData& operator=(const SysYLexerStaticData&) = delete;
  SysYLexerStaticData& operator=(SysYLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sysylexerLexerOnceFlag;
SysYLexerStaticData *sysylexerLexerStaticData = nullptr;

void sysylexerLexerInitialize() {
  assert(sysylexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<SysYLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "WS", 
      "COMMENT", "IntConstant", "FloatConstant", "DecimalFloatingConstant", 
      "HexadecimalFloatingConstant", "FractionalConstant", "ExponentPart", 
      "Sign", "DigitSequence", "HexadecimalFractionalConstant", "BinaryExponentPart", 
      "HexadecimalDigits", "Ident", "NonDigit", "Digit", "NonZeroDigit", 
      "OctalDigit", "HexadecimalDigit"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,22,246,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,1,0,
  	1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,5,1,5,1,
  	6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,
  	1,14,1,14,1,15,1,15,1,16,4,16,111,8,16,11,16,12,16,112,1,16,1,16,1,17,
  	1,17,1,17,1,17,5,17,121,8,17,10,17,12,17,124,9,17,1,17,1,17,1,17,1,17,
  	5,17,130,8,17,10,17,12,17,133,9,17,1,17,1,17,3,17,137,8,17,1,17,1,17,
  	1,18,1,18,5,18,143,8,18,10,18,12,18,146,9,18,1,18,1,18,5,18,150,8,18,
  	10,18,12,18,153,9,18,1,18,1,18,1,18,4,18,158,8,18,11,18,12,18,159,3,18,
  	162,8,18,1,19,1,19,3,19,166,8,19,1,20,1,20,3,20,170,8,20,1,20,1,20,1,
  	20,3,20,175,8,20,1,21,1,21,1,21,1,21,3,21,181,8,21,1,21,1,21,1,22,3,22,
  	186,8,22,1,22,1,22,1,22,1,22,1,22,3,22,193,8,22,1,23,1,23,3,23,197,8,
  	23,1,23,1,23,1,24,1,24,1,25,4,25,204,8,25,11,25,12,25,205,1,26,3,26,209,
  	8,26,1,26,1,26,1,26,1,26,1,26,3,26,216,8,26,1,27,1,27,3,27,220,8,27,1,
  	27,1,27,1,28,4,28,225,8,28,11,28,12,28,226,1,29,1,29,1,29,5,29,232,8,
  	29,10,29,12,29,235,9,29,1,30,1,30,1,31,1,31,1,32,1,32,1,33,1,33,1,34,
  	1,34,1,131,0,35,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,
  	12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,0,43,0,45,0,47,
  	0,49,0,51,21,53,0,55,0,57,0,59,22,61,0,63,0,65,0,67,0,69,0,1,0,11,3,0,
  	9,10,13,13,32,32,2,0,10,10,13,13,2,0,88,88,120,120,2,0,69,69,101,101,
  	2,0,43,43,45,45,2,0,80,80,112,112,3,0,65,90,95,95,97,122,1,0,48,57,1,
  	0,49,57,1,0,48,55,3,0,48,57,65,70,97,102,255,0,1,1,0,0,0,0,3,1,0,0,0,
  	0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,
  	0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,
  	0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,
  	37,1,0,0,0,0,39,1,0,0,0,0,51,1,0,0,0,0,59,1,0,0,0,1,71,1,0,0,0,3,73,1,
  	0,0,0,5,75,1,0,0,0,7,79,1,0,0,0,9,85,1,0,0,0,11,87,1,0,0,0,13,89,1,0,
  	0,0,15,91,1,0,0,0,17,93,1,0,0,0,19,95,1,0,0,0,21,97,1,0,0,0,23,99,1,0,
  	0,0,25,101,1,0,0,0,27,103,1,0,0,0,29,105,1,0,0,0,31,107,1,0,0,0,33,110,
  	1,0,0,0,35,136,1,0,0,0,37,161,1,0,0,0,39,165,1,0,0,0,41,174,1,0,0,0,43,
  	176,1,0,0,0,45,192,1,0,0,0,47,194,1,0,0,0,49,200,1,0,0,0,51,203,1,0,0,
  	0,53,215,1,0,0,0,55,217,1,0,0,0,57,224,1,0,0,0,59,228,1,0,0,0,61,236,
  	1,0,0,0,63,238,1,0,0,0,65,240,1,0,0,0,67,242,1,0,0,0,69,244,1,0,0,0,71,
  	72,5,44,0,0,72,2,1,0,0,0,73,74,5,59,0,0,74,4,1,0,0,0,75,76,5,105,0,0,
  	76,77,5,110,0,0,77,78,5,116,0,0,78,6,1,0,0,0,79,80,5,102,0,0,80,81,5,
  	108,0,0,81,82,5,111,0,0,82,83,5,97,0,0,83,84,5,116,0,0,84,8,1,0,0,0,85,
  	86,5,91,0,0,86,10,1,0,0,0,87,88,5,93,0,0,88,12,1,0,0,0,89,90,5,61,0,0,
  	90,14,1,0,0,0,91,92,5,123,0,0,92,16,1,0,0,0,93,94,5,125,0,0,94,18,1,0,
  	0,0,95,96,5,43,0,0,96,20,1,0,0,0,97,98,5,45,0,0,98,22,1,0,0,0,99,100,
  	5,42,0,0,100,24,1,0,0,0,101,102,5,47,0,0,102,26,1,0,0,0,103,104,5,37,
  	0,0,104,28,1,0,0,0,105,106,5,40,0,0,106,30,1,0,0,0,107,108,5,41,0,0,108,
  	32,1,0,0,0,109,111,7,0,0,0,110,109,1,0,0,0,111,112,1,0,0,0,112,110,1,
  	0,0,0,112,113,1,0,0,0,113,114,1,0,0,0,114,115,6,16,0,0,115,34,1,0,0,0,
  	116,117,5,47,0,0,117,118,5,47,0,0,118,122,1,0,0,0,119,121,8,1,0,0,120,
  	119,1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,0,122,123,1,0,0,0,123,137,1,
  	0,0,0,124,122,1,0,0,0,125,126,5,47,0,0,126,127,5,42,0,0,127,131,1,0,0,
  	0,128,130,9,0,0,0,129,128,1,0,0,0,130,133,1,0,0,0,131,132,1,0,0,0,131,
  	129,1,0,0,0,132,134,1,0,0,0,133,131,1,0,0,0,134,135,5,42,0,0,135,137,
  	5,47,0,0,136,116,1,0,0,0,136,125,1,0,0,0,137,138,1,0,0,0,138,139,6,17,
  	1,0,139,36,1,0,0,0,140,144,3,65,32,0,141,143,3,63,31,0,142,141,1,0,0,
  	0,143,146,1,0,0,0,144,142,1,0,0,0,144,145,1,0,0,0,145,162,1,0,0,0,146,
  	144,1,0,0,0,147,151,5,48,0,0,148,150,3,67,33,0,149,148,1,0,0,0,150,153,
  	1,0,0,0,151,149,1,0,0,0,151,152,1,0,0,0,152,162,1,0,0,0,153,151,1,0,0,
  	0,154,155,5,48,0,0,155,157,7,2,0,0,156,158,3,69,34,0,157,156,1,0,0,0,
  	158,159,1,0,0,0,159,157,1,0,0,0,159,160,1,0,0,0,160,162,1,0,0,0,161,140,
  	1,0,0,0,161,147,1,0,0,0,161,154,1,0,0,0,162,38,1,0,0,0,163,166,3,41,20,
  	0,164,166,3,43,21,0,165,163,1,0,0,0,165,164,1,0,0,0,166,40,1,0,0,0,167,
  	169,3,45,22,0,168,170,3,47,23,0,169,168,1,0,0,0,169,170,1,0,0,0,170,175,
  	1,0,0,0,171,172,3,51,25,0,172,173,3,47,23,0,173,175,1,0,0,0,174,167,1,
  	0,0,0,174,171,1,0,0,0,175,42,1,0,0,0,176,177,5,48,0,0,177,180,7,2,0,0,
  	178,181,3,53,26,0,179,181,3,57,28,0,180,178,1,0,0,0,180,179,1,0,0,0,181,
  	182,1,0,0,0,182,183,3,55,27,0,183,44,1,0,0,0,184,186,3,51,25,0,185,184,
  	1,0,0,0,185,186,1,0,0,0,186,187,1,0,0,0,187,188,5,46,0,0,188,193,3,51,
  	25,0,189,190,3,51,25,0,190,191,5,46,0,0,191,193,1,0,0,0,192,185,1,0,0,
  	0,192,189,1,0,0,0,193,46,1,0,0,0,194,196,7,3,0,0,195,197,3,49,24,0,196,
  	195,1,0,0,0,196,197,1,0,0,0,197,198,1,0,0,0,198,199,3,51,25,0,199,48,
  	1,0,0,0,200,201,7,4,0,0,201,50,1,0,0,0,202,204,3,63,31,0,203,202,1,0,
  	0,0,204,205,1,0,0,0,205,203,1,0,0,0,205,206,1,0,0,0,206,52,1,0,0,0,207,
  	209,3,57,28,0,208,207,1,0,0,0,208,209,1,0,0,0,209,210,1,0,0,0,210,211,
  	5,46,0,0,211,216,3,57,28,0,212,213,3,57,28,0,213,214,5,46,0,0,214,216,
  	1,0,0,0,215,208,1,0,0,0,215,212,1,0,0,0,216,54,1,0,0,0,217,219,7,5,0,
  	0,218,220,3,49,24,0,219,218,1,0,0,0,219,220,1,0,0,0,220,221,1,0,0,0,221,
  	222,3,51,25,0,222,56,1,0,0,0,223,225,3,69,34,0,224,223,1,0,0,0,225,226,
  	1,0,0,0,226,224,1,0,0,0,226,227,1,0,0,0,227,58,1,0,0,0,228,233,3,61,30,
  	0,229,232,3,61,30,0,230,232,3,63,31,0,231,229,1,0,0,0,231,230,1,0,0,0,
  	232,235,1,0,0,0,233,231,1,0,0,0,233,234,1,0,0,0,234,60,1,0,0,0,235,233,
  	1,0,0,0,236,237,7,6,0,0,237,62,1,0,0,0,238,239,7,7,0,0,239,64,1,0,0,0,
  	240,241,7,8,0,0,241,66,1,0,0,0,242,243,7,9,0,0,243,68,1,0,0,0,244,245,
  	7,10,0,0,245,70,1,0,0,0,23,0,112,122,131,136,144,151,159,161,165,169,
  	174,180,185,192,196,205,208,215,219,226,231,233,2,0,1,0,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sysylexerLexerStaticData = staticData.release();
}

}

SysYLexer::SysYLexer(CharStream *input) : Lexer(input) {
  SysYLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *sysylexerLexerStaticData->atn, sysylexerLexerStaticData->decisionToDFA, sysylexerLexerStaticData->sharedContextCache);
}

SysYLexer::~SysYLexer() {
  delete _interpreter;
}

std::string SysYLexer::getGrammarFileName() const {
  return "SysY.g4";
}

const std::vector<std::string>& SysYLexer::getRuleNames() const {
  return sysylexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& SysYLexer::getChannelNames() const {
  return sysylexerLexerStaticData->channelNames;
}

const std::vector<std::string>& SysYLexer::getModeNames() const {
  return sysylexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& SysYLexer::getVocabulary() const {
  return sysylexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SysYLexer::getSerializedATN() const {
  return sysylexerLexerStaticData->serializedATN;
}

const atn::ATN& SysYLexer::getATN() const {
  return *sysylexerLexerStaticData->atn;
}




void SysYLexer::initialize() {
  ::antlr4::internal::call_once(sysylexerLexerOnceFlag, sysylexerLexerInitialize);
}
