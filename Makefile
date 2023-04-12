all:clean gen_code
	-mkdir build
	@cd build && cmake ../src && make

.PHONY:clean
clean:
	-rm -r build

gen_code:
	@antlr4 src/frontend/grammar*.g4 -Dlanguage=Cpp -Xexact-output-dir -o src/frontend

run:all
	@./build/jimfeng-compiler