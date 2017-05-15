#ifndef __LEX_H__
#define __LEX_H__

#include <cstring>

#include <map>
#include <fstream>

using namespace std;

enum LexType
{
    /* reserved words */
    PROGRAM = 1,  TYPE,   VAR,    PROCEDURE,
    BEGIN,    END,    ARRAY,  OF,
    RECORD,   IF,     THEN,   ELSE,
    FI,       WHILE,  DO,     ENDWH,
    READ,     WRITE,  RETURN,INTEGER, CHAR,
    //types, just a symbol of type **name**, no actual sematic infomation
    INTEGER_T, CHAR_T,
    //
    ID,
    //not like INTEGER_T and CHAR_T, these two do have certain meanings
    INTC_VAL, CHAR_VAL,
    //
    ASSIGN, EQ,     LT,     PLUS, MINUS,
    TIMES,  DIVIDE, LPAREN, RPAREN,
    DOT,    COLON,  SEMI,   COMMA,
    LMIDPAREN, RMIDPAREN, UNDERRANGE,
    //
    ENDFILE = 0, ERROR = -1,
};

extern map<LexType, char *> lexName;

extern map<char *, LexType> reservedWords;

class Token
{
public:
    Token(int line, LexType lex, char * sem)
    {
        this->line = line;
        this->lex = lex;
        this->sem = sem;
    }
    int getLine()
    {
        return line;
    }
    char * getLexName()
    {
        return lexName[lex];
    }
    LexType getLex()
    {
        return lex;
    }
    char * getSem()
    {
        return sem;
    }
    Token * next;
private:
    int line;
    LexType lex;
    char * sem;
};

class Lexer
{
public:
    static Lexer * getLexer(char * filename)
    {
        return (new Lexer(filename));
    }
    ~Lexer()
    {
        source.close();
    }
    Token * getTokenList();
    void printTokenList(Token * head);

private:
    Lexer(char * filename) : lineRec(0), idBuff(""), intBuff(0)
    {
        //source = ifstream(filename);
    }
    ifstream source;
    int lineRec;
    char * idBuff;
    double intBuff;
    Token * reversedLookup(char * str);
    bool isssep(char c);
    Token * ssep(char c);
};

#endif
