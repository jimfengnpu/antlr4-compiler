GRAMMAR_DIR = src/frontend/grammar
GRAMMAR_RULE = ${GRAMMAR_DIR}/SysY.g4
START_RULE = compUnit
ANTLR_GEN_DIR = src/frontend/generated
TARGET_FILE = build/compiler
TEST_INPUT = test_input.sy
OUT_DOT = test.gv
FUNC = main

all:clean  ${TARGET_FILE}
	
clean:
	-rm -r build

${TARGET_FILE}:
	-mkdir build
	@cd build && cmake .. && make -j4

gen_code:${GRAMMAR_RULE}
	-rm ${ANTLR_GEN_DIR}/*
	-rm -r ${ANTLR_GEN_DIR}/../grammar/.antlr
	antlr4 ${GRAMMAR_RULE} -Dlanguage=Cpp -Xexact-output-dir -visitor -o ${ANTLR_GEN_DIR}

gen_tree:
	antlr4-parse ${GRAMMAR_RULE} ${START_RULE} -gui ${TEST_INPUT}

gen_graph:
	echo "digraph{  nodesep = 1; node[shape = record];" > ${OUT_DOT}
	./${TARGET_FILE} ${TEST_INPUT} | awk '/^#@/ {p=0} /^#@.*${FUNC}/ {p=1} p' >> ${OUT_DOT}
	echo "}" >> ${OUT_DOT}


run: ${TARGET_FILE}
	./${TARGET_FILE} ${TEST_INPUT}

asm_demo: ${TEST_INPUT}


lines:
	find src/* -path "src/frontend/generated" -prune -o -name "*.*" -print | xargs wc -l

.PHONY:all clean run 
