GRAMMAR_DIR = src/frontend/grammar
GRAMMAR_RULE = ${GRAMMAR_DIR}/SysY.g4
START_RULE = prog
ANTLR_GEN_DIR = src/frontend
TARGET_FILE = build/compiler

all:clean  ${TARGET_FILE}
	
clean:
	-rm -r build

${TARGET_FILE}:gen_code
	-mkdir build
	@cd build && cmake .. && make -j4

gen_code:
	antlr4 ${GRAMMAR_RULE} -Dlanguage=Cpp -Xexact-output-dir -o ${ANTLR_GEN_DIR}

gen_graph:
	antlr4-parse ${GRAMMAR_RULE} ${START_RULE} -gui 

run:${TARGET_FILE}
	./${TARGET_FILE}


.PHONY:all clean run 
