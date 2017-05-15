#ifndef __LEX_H__
#define __LEX_H__

#define MAXRESERVED 21
#define MAXIDSIZE   50

/* lex types */
typedef enum
{
    /* reserved words */
    PROGRAM = 1,    TYPE,   VAR,    PROCEDURE,
    //BEGIN_R END_R : add postfix '_R' in case may be conflit with flex default constants
    BEGIN_R,      END_R,    ARRAY,  OF,
    RECORD,     IF,     THEN,   ELSE,
    FI,         WHILE,  DO,     ENDWH,
    READ,       WRITE,  RETURN,INTEGER, CHAR,
    //
	ENDFILE, ERROR,
    //types
	INTEGER_T, CHAR_T,
    //
	ID, INTC_VAL, CHAR_VAL,
    //
	ASSIGN, EQ, LT, PLUS, MINUS,
	TIMES, DIVIDE, LPAREN, RPAREN,
	DOT, COLON, SEMI, COMMA,
	LMIDPAREN, RMIDPAREN, UNDERANGE
} LexType;

/* handle reserved words */
typedef struct ReservedWord
{ 
    char* str;
    LexType tok;
} ReservedWord;

static ReservedWord reservedWords[MAXRESERVED] = 
{
    {"program",PROGRAM},    {"type",TYPE},      {"var",VAR},
    {"procedure",PROCEDURE},{"begin",BEGIN_R},   {"end",END_R},
    {"array",ARRAY},        {"of",OF},          {"record",RECORD},
    {"if",IF},              {"then",THEN},      {"else",ELSE},
    {"fi",FI},              {"while",WHILE},    {"do",DO},
    {"endwh",ENDWH},        {"read",READ},      {"write",WRITE},
    {"return",RETURN},     {"integer",INTEGER},{"char",CHAR} 
};

/* lex token*/
typedef struct Token
{
    int lineno;
    LexType lex;
    char sem[MAXIDSIZE];
} Token;

/* used to generate token list */
typedef struct TokenNode TokenNode;
typedef struct TokenNode
{
    Token token;
    TokenNode *link;
} TokenNode;

/* used to contain sem string in a time */
static char strbuff[MAXIDSIZE];

/* return a string of tokens, for next step using */
TokenNode * getTokenList();

/* Token constructor */
TokenNode *tokenNode(int lineno, LexType lex, char *sem);

/* display tokens, mainly for testing */
void displayTokens(TokenNode *head);

#endif
