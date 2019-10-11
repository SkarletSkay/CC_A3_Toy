.PHONY: clean mem

CC := clang
CFLAGS := -g

run: parser.tab.o lex.o ast.o main.o
	$(CC) -g -o $@ $+

mem:
	valgrind --leak-check=full ./run

clean:
	rm -f run *.o parser.tab* lex.[ch]

parser.tab.o: lex.c

lex.c: lex.l
	flex --header-file=lex.h --outfile=lex.c lex.l

parser.tab.c: parser.y
	bison -d parser.y
