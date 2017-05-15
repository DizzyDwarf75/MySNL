#ifndef LEXER_H__
#define LEXER_H__

#include "../lex.h"
#include <stdbool.h>

bool reservedLookup(int line, char*, TokenNode**);
void printLexType(LexType lex);
void printTokenList();
void printToken(Token);
void dump2file(TokenNode*);
void Error(int line, char c);
void init(char *filename);


bool isssep(char c);
TokenNode *ssep(int line, char c);

#endif
