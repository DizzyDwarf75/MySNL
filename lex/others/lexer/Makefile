all: lexer clean

lexer: lex.o lexer.o main.o
	gcc lex.o lexer.o main.o -o lexer

lex.o: ../lex.c
	gcc -c ../lex.c

lexer.o: lexer.c
	gcc -c lexer.c

main.o: main.c
	gcc -c main.c

clean:
	rm *.o

