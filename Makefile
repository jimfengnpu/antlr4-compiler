GRAMMAR_DIR = src/frontend/grammar
GRAMMAR_RULE = ${GRAMMAR_DIR}/SysY.g4
START_RULE = compUnit
ANTLR_GEN_DIR = src/frontend/generated
TARGET_FILE = build/compiler
TEST_INPUT = test_input.sy
OUT_DOT = test.gv
FUNC = eval

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

run_asm: ${asm_demo}
	sed -i 's/starttime/_sysy_starttime/g' out.s
	sed -i 's/stoptime/_sysy_stoptime/g' out.s
	/opt/riscv/bin/riscv64-unknown-linux-gnu-gcc -g -march=rv64gc out.s -L compiler2021/lib/riscv64/ -lsysy -o /tmp/test.x
	qemu-riscv64 /tmp/test.x

asm_demo: ${TEST_INPUT}


lines:
	@find src -type f -not -path "src/frontend/generated/*" | xargs wc -l 

.PHONY:all clean run 
