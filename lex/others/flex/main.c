#include <stdio.h>
#include <stdlib.h>
#include "../lex.h"

extern int yylex();

void displayTokens(TokenNode *head)
{
    TokenNode *pn = head;
    while(pn)
    {
        printf("%4d, %4d, %s\n", pn->token.lineno, pn->token.lex, pn->token.sem);
        pn = pn->link;
    }
}

int main(int argc, char **argv)
{
    FILE *source;
    if(!(source = fopen(argv[1], "r")))
        exit(-1);
    extern FILE * yyin;
    yyin = source;
    TokenNode *head;
    head = getTokenList();
    displayTokens(head);
    return 0;
}
