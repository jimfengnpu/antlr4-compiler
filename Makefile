GRAMMAR_DIR = src/frontend/grammar
GRAMMAR_RULE = ${GRAMMAR_DIR}/SysY.g4
START_RULE = compUnit
ANTLR_GEN_DIR = src/frontend/generated
TARGET_FILE = build/compiler

all:clean  ${TARGET_FILE}
	
clean:
	-rm -r build

${TARGET_FILE}:
	-mkdir build
	@cd build && cmake .. && make -j4

gen_code:
	-rm ${ANTLR_GEN_DIR}/*
	-rm -r ${ANTLR_GEN_DIR}/../grammar/.antlr
	antlr4 ${GRAMMAR_RULE} -Dlanguage=Cpp -Xexact-output-dir -visitor -o ${ANTLR_GEN_DIR}

gen_graph:
	antlr4-parse ${GRAMMAR_RULE} ${START_RULE} -gui test_input.c

run: ${TARGET_FILE}
	./${TARGET_FILE}


.PHONY:all clean run 
