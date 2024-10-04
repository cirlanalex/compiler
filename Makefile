all: parser lexer structs symtable usage messages gencode
	gcc -o minipas -O2 parser.o lexer.o structs.o symtable.o usage.o messages.o gencode.o -lfl -lm

parser: parser.y
	bison -d parser.y
	mv parser.tab.c parser.c
	gcc -O2 -c parser.c

lexer: lexer.fl
	flex lexer.fl
	mv lex.yy.c lexer.c
	gcc -O2 -c lexer.c
messages: messages.c messages.h
	gcc -O2 -c messages.c
structs: structs.c structs.h
	gcc -O2 -c structs.c
symtable: symtable.c symtable.h
	gcc -O2 -c symtable.c
usage: usage.c usage.h
	gcc -O2 -c usage.c
gencode: gencode.c gencode.h
	gcc -O2 -c gencode.c
clean:
	rm -f *~
	rm -f *.o
	rm -f parser.c
	rm -f parser.tab.h
	rm -f lexer.c
	rm -f a.out
	rm -f minipas
