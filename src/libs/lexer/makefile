GCC=gcc

./build/:
	mkdir -p build

lexer.o: ./build/
	@${GCC} lexer.c lexer.h token_storage.h token_storage.c -o build/lexer

build: lexer.o

test:
	@${GCC} test.c -o build/test

clean:
	rm -r ./build
