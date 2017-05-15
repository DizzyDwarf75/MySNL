#include <stdlib.h>
#include <string.h>
#include "lex.h"

/* Token constructor */                                                                                                                           
TokenNode *tokenNode(int lineno, LexType lex, char *sem)
{
    TokenNode *tmp = (TokenNode*)malloc(sizeof(TokenNode));
    tmp->token.lineno = lineno;
    tmp->token.lex = lex;
    strcpy(tmp->token.sem, sem);
    tmp->link = NULL;

    return tmp;
}

/* display tokens, mainly for testing */
void displayTokens(TokenNode *head);
