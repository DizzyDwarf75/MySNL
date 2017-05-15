%{
    #include"../lex.h"
    int line = 1;
%}

%%
\n                              ++line;

program                         printf("%d  :PROGRAM    %s\n", line, yytext); strcpy(strbuff, yytext); return PROGRAM;
type                            printf("%d  :TYPE       %s\n", line, yytext); strcpy(strbuff, yytext); return TYPE;
var                             printf("%d  :VAR        %s\n", line, yytext); strcpy(strbuff, yytext); return VAR;
procedure                       printf("%d  :PROCEDURE  %s\n", line, yytext); strcpy(strbuff, yytext); return PROCEDURE;
begin                           printf("%d  :BEGIN_R    %s\n", line, yytext); strcpy(strbuff, yytext); return BEGIN_R;
end                             printf("%d  :END_R      %s\n", line, yytext); strcpy(strbuff, yytext); return END_R;
array                           printf("%d  :ARRAY      %s\n", line, yytext); strcpy(strbuff, yytext); return ARRAY;
of                              printf("%d  :OF         %s\n", line, yytext); strcpy(strbuff, yytext); return OF;
record                          printf("%d  :RECORD     %s\n", line, yytext); strcpy(strbuff, yytext); return RECORD;
if                              printf("%d  :IF         %s\n", line, yytext); strcpy(strbuff, yytext); return IF;
then                            printf("%d  :THEN       %s\n", line, yytext); strcpy(strbuff, yytext); return THEN;
else                            printf("%d  :ELSE       %s\n", line, yytext); strcpy(strbuff, yytext); return ELSE;
fi                              printf("%d  :FI         %s\n", line, yytext); strcpy(strbuff, yytext); return FI;
while                           printf("%d  :WHILE      %s\n", line, yytext); strcpy(strbuff, yytext); return WHILE;
do                              printf("%d  :DO         %s\n", line, yytext); strcpy(strbuff, yytext); return DO;
endwh                           printf("%d  :ENDWH      %s\n", line, yytext); strcpy(strbuff, yytext); return ENDWH;
read                            printf("%d  :READ       %s\n", line, yytext); strcpy(strbuff, yytext); return READ;
write                           printf("%d  :WRITE      %s\n", line, yytext); strcpy(strbuff, yytext); return WRITE;
return                          printf("%d  :RETURN     %s\n", line, yytext); strcpy(strbuff, yytext); return RETURN;
integer                         printf("%d  :INTEGER    %s\n", line, yytext); strcpy(strbuff, yytext); return INTEGER;
char                            printf("%d  :CHAR       %s\n", line, yytext); strcpy(strbuff, yytext); return CHAR;

[a-zA-Z][a-zA-Z0-9]*            printf("%d  :ID         %s\n", line, yytext); strcpy(strbuff, yytext); return ID;
[0-9]+                          printf("%d  :INTC_VAL   %s\n", line, yytext); strcpy(strbuff, yytext); return INTC_VAL;
:=                              printf("%d  :ASSIGN     %s\n", line, yytext); strcpy(strbuff, yytext); return ASSIGN;
=                               printf("%d  :EQ         %s\n", line, yytext); strcpy(strbuff, yytext); return EQ;
\<                              printf("%d  :LT         %s\n", line, yytext); strcpy(strbuff, yytext); return LT;
\+                              printf("%d  :PLUS       %s\n", line, yytext); strcpy(strbuff, yytext); return PLUS; 
\-                              printf("%d  :MINUS      %s\n", line, yytext); strcpy(strbuff, yytext); return MINUS;
\*                              printf("%d  :TIMES      %s\n", line, yytext); strcpy(strbuff, yytext); return TIMES;
\/                              printf("%d  :DIVIDE     %s\n", line, yytext); strcpy(strbuff, yytext); return DIVIDE;
\(                              printf("%d  :LPAREN     %s\n", line, yytext); strcpy(strbuff, yytext); return LPAREN;
\)                              printf("%d  :RPAREN     %s\n", line, yytext); strcpy(strbuff, yytext); return RPAREN;
\.                              printf("%d  :DOT        %s\n", line, yytext); strcpy(strbuff, yytext); return DOT;
\:                              printf("%d  :COLON      %s\n", line, yytext); strcpy(strbuff, yytext); return COLON;
\;                              printf("%d  :SEMI       %s\n", line, yytext); strcpy(strbuff, yytext); return SEMI;
\,                              printf("%d  :COMMA      %s\n", line, yytext); strcpy(strbuff, yytext); return COMMA;
\[                              printf("%d  :LMIDPAREN  %s\n", line, yytext); strcpy(strbuff, yytext); return LMIDPAREN;
\]                              printf("%d  :RMIDPAREN  %s\n", line, yytext); strcpy(strbuff, yytext); return RMIDPAREN;
\.\.                            printf("%d  :UNDERANGE  %s\n", line, yytext); strcpy(strbuff, yytext); return UNDERANGE;
'[a-zA-Z0-9]'                   printf("%d  :CHAR_VAL   %s\n", line, yytext); strcpy(strbuff, yytext); return CHAR_VAL;
[ \t]                           ;
\{[^\}]*\}                      ;
.                               printf("**ERROR**\n");
<<EOF>>                       printf("%d  :ENDFILE    %s\n", line, yytext); strcpy(strbuff, yytext); yyterminate();
%%
TokenNode * getTokenList()
{
    TokenNode *head = (TokenNode*)malloc(sizeof(TokenNode));
    TokenNode *curr = head, *tmp;
    LexType type;
    while((type = yylex()))
    {
        tmp = tokenNode(line, type, strbuff);
        curr->link = tmp;
        curr = curr->link;
    }
    //discard old head (with no actural values)
    tmp = head->link;
    free(head);
    head = tmp;

    return head;
}
