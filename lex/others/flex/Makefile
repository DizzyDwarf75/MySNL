all: lexer clean

lexer: lex.o lex.yy.o main.o
	gcc lex.o lex.yy.o main.o -lfl -o lexer

lex.o: ../lex.c
	gcc -c ../lex.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: lex.l
	lex lex.l

main.o: main.c
	gcc -c main.c

clean:
	rm *.o 
