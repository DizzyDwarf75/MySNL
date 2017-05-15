#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "../lex.h"
#include"lexer.h"

FILE    *source;       //source file to parse
int     line = 1;       //mark the lines

void init(char *filename)
{
    if(!(source = fopen(filename, "r")))
    {
        perror("can't open file");
        exit(1);
    }
    line = 1;
}

void over()
{
    fclose(source);
}

void Error(int line, char c)
{
    printf("line %d: ...%c error occured!\n", line, c);
}

TokenNode* getTokenList()
{
    TokenNode   *head;
    TokenNode   *currentNode;
    TokenNode   *tmp;

    head        = malloc(sizeof(TokenNode));
    currentNode = head;

    char    c, nextc;
    char    identifier[50];     //store id string
    char    number[50];         //store num string
    char    charstr[2] = {'\0', '\0'};  //store char string
    int     idinc = 0;          //identifier index 
    int     numinc = 0;         //number index

    /*  mainloop  */
    while((c = fgetc(source)) != EOF)
    {
        //line increase
        if(c == '\n')
            ++line; 
        
        if(isalpha(c))      //ID := [a-zA-Z]+[a-zA-Z0-9]*
        {
            identifier[idinc++] = c;

            while((nextc = fgetc(source)) != EOF)
            {
                if(isalnum(nextc))
                {
                    identifier[idinc++] = nextc;
                }
                else
                {
                    identifier[idinc++] = '\0';
                    if(!reservedLookup(line, identifier, &currentNode))
                    {
                        tmp = tokenNode(line, ID, identifier);
                        currentNode->link = tmp;
                        currentNode = currentNode->link;
                    }

                    //reset
                    ungetc(nextc, source);
                    idinc = 0;      //important, cause idinc is global within the function body

                    break;
                }
            }
        }
        else if(isdigit(c))     //INTC := [0-9]+
        {
            number[numinc] = c;
            while(isdigit(nextc = fgetc(source)))
            {
                ++numinc;
                number[numinc] = nextc;
            }
            number[numinc+1] = '\0';
            tmp = tokenNode(line, INTC_VAL, number);
            currentNode->link = tmp;
            currentNode = currentNode->link;
            //reset, the same to string
            ungetc(nextc, source);
            numinc = 0;     //important, cause idinc is global within the function body
        }
        else if(isssep(c))  //single character seperator
        {
            tmp = ssep(line, c);  //ssep() : handle that many kinds of the seperators
            if(tmp)
            {
                currentNode->link = tmp;
                currentNode = currentNode->link;
            }
            //ungetc(c, source);
        }
        else if(c == ':')   //ASSIGN := :=  ,   :[^=] := ERROR
        {
            if((nextc = fgetc(source)) != '=')
            {
                ungetc(nextc, source);
                Error(line, c);
            }
            else
            {
                tmp = tokenNode(line, ASSIGN, ":=");
                currentNode->link = tmp;
                currentNode = currentNode->link;
            }
        }
        else if(c == '{')       //COMMENTS := \{.*\}, simply ignore any comments
        {
            while((nextc = fgetc(source)) != EOF)
            {
                if(nextc == '}')
                    break;
            }
        }
        else if(c == '.')       //UNDERANGE := \.\.  ,  ENDFILE := \.EOF    ,  \.[^\.] | \.[^EOF] := ERROR
        {
            nextc = fgetc(source);
            if(nextc == '.')
            {
                tmp = tokenNode(line, UNDERANGE, "..");
                currentNode->link = tmp;
                currentNode = currentNode->link;
            }
            else
            {
                if(nextc = EOF)
                {
                    tmp = tokenNode(line, ENDFILE, ".EOF");
                    currentNode->link = tmp;
                    currentNode = currentNode->link;
                }
                else
                {
                    ungetc(nextc, source);
                    Error(line, c);
                }
            }
        }
        else if(c == '\'')    //CHARC := '[a-zA-Z0-9]'
        {
            nextc = fgetc(source);
            char c = nextc;
            if(!(isalpha(c) || isdigit(c)))
            {
                ungetc(nextc, source);
                Error(line, c);
            }
            else
            {
                nextc = fgetc(source);
                if(nextc != '\'')
                {
                    ungetc(nextc, source);
                    Error(line, c);
                }
                else
                {
                    charstr[0] = c;
                    tmp = tokenNode(line, CHAR_VAL, charstr);
                    currentNode->link = tmp;
                    currentNode = currentNode->link;
                }
            }
        }
        else
        {
            Error(line, c);
        }
    }

    return head;
}

bool isssep(char c)
{
    if(c == ',' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';' || c == '[' || c == ']' || c == '=' || c == '<' || c == EOF || isspace(c)) 
        return true;
    else
        return false;
}

TokenNode *ssep(int line, char c)
{
    LexType lex;
    char sem[50];
    
    switch(c)
    {
        case '+':
            lex = PLUS;
            sem[0] = '+';
            sem[1] = '\0';
            break;
        case '-':
            lex = MINUS;
            //strcpy(sem, "-");
            sem[0] = '-';
            sem[1] = '\0';
            break;
        case '*':
            lex = TIMES;
            //strcpy(sem, "*");
            sem[0] = '*';
            sem[1] = '\0';
            break;
        case '/':
            lex = DIVIDE;
            //strcpy(sem, "/");
            sem[0] = '/';
            sem[1] = '\0';
            break;
        case '(':
            lex = LPAREN;
            //strcpy(sem, "(");
            sem[0] = '(';
            sem[1] = '\0';
            break;
        case ')':
            lex = RPAREN;
            //strcpy(sem, ")");
            sem[0] = ')';
            sem[1] = '\0';
            break;
        case ';':
            lex = SEMI;
            //strcpy(sem, ";");
            sem[0] = ';';
            sem[1] = '\0';
            break;
        case '[':
            lex = LMIDPAREN;
            //strcpy(sem, "[");
            sem[0] = '[';
            sem[1] = '\0';
            break;
        case ']':
            lex = RMIDPAREN;
            //strcpy(sem, "]");
            sem[0] = ']';
            sem[1] = '\0';
            break;
        case '=':
            lex = EQ;
            //strcpy(sem, "=");
            sem[0] = '=';
            sem[1] = '\0';
            break;
        case '<':
            lex = LT;
            //strcpy(sem, "<");
            sem[0] = '<';
            sem[1] = '\0';
            break;
        case ',':
            lex = COMMA;
            sem[0] = ',';
            sem[1] = '\0';
            break;
        case ' ':
        case '\n':
        case '\t':
        case '\b':
        case '\r':
            return NULL;
        default:
            lex = ERROR;
            sem[0] = 'e';
            sem[1] = 'r';
            sem[2] = 'r';
            sem[3] = 'o';
            sem[4] = 'r';
            sem[5] = '\0';
            break;
    }

    return tokenNode(line, lex, sem);
}

bool reservedLookup(int line, char* s, TokenNode** currentNode)
{
    int i = 0;
    TokenNode *tmp;
    for(i = 0; i < MAXRESERVED; i++)
    {
        if(!strcmp(reservedWords[i].str, s))
        {
            tmp = tokenNode(line, reservedWords[i].tok, s);
            (*currentNode)->link = tmp;
            (*currentNode) = (*currentNode)->link;
            return true;
        }
    }
    return false;
}

void dump2file(TokenNode *head)
{
    TokenNode *node = head->link;
    FILE *target;
    if(!(target = fopen("lex.lexer", "w")))
    {
        perror("can't open file");
        exit(1);
    }
    while(node)
    {
        fwrite(&node->token, sizeof(Token), 1, target);
        node = node->link;
    }
}

void printTokenList(TokenNode* head)
{
    TokenNode *node;
    node = head->link;
    while(node)
    {
        printToken(node->token);
        node = node->link; 
    }
}
void printToken(Token token)
{
    printf("%d, ", token.lineno);
    printLexType(token.lex);
    printf(", %s\n", token.sem);
}

void printLexType(LexType lex)
{
    switch(lex)
    {
        case ENDFILE:
		  printf("EOF");
		  break; 
		case ERROR:
		  printf("ERROR");
		  break; 
		case PROGRAM:
		  printf("reserved word: program");
		  break; 
		case PROCEDURE:
		  printf("reserved word: procedure");
		  break; 
		case THEN:
		  printf("reserved word: then");
		  break; 
		case ELSE:
		  printf("reserved word: else");
		  break; 
		case ENDWH:
		  printf("reserved word: endwh");
		  break; 
		case BEGIN_R:
		  printf("reserved word: begin");
		  break; 
		case TYPE:
		  printf("reserved word: type");
		  break; 
		case FI:
		  printf("reserved word: fi");
		  break; 
		case END_R:
		  printf("reserved word: end");
		  break; 
		case VAR:
		  printf("reserved word: var");
		  break; 
		case WHILE:
		  printf("reserved word: while");
		  break; 
		case READ:
		  printf("reserved word: read");
		  break; 
		case IF:
		  printf("reserved word: if");
		  break; 
		case DO:
		  printf("reserved word: do");
		  break; 
		case WRITE:
		  printf("reserved word: write");
		  break; 
		case ARRAY:
		  printf("reserved word: array");
		  break; 
		case OF:
		  printf("reserved word: of");
		  break; 
		case RECORD:
		  printf("reserved word: record");
		  break; 
		case RETURN:
		  printf("reserved word: return");
		  break; 
		case INTEGER:
		  printf("reserved word: integer");
		  break; 
		case CHAR_VAL:
		  printf("reserved word: char");
		  break; 
		case ID:
		  printf("ID");
		  break; 
		case INTC_VAL:
		  printf("NUM");
		  break; 
		case CHAR_T:
		  printf("CHAR");
		  break; 
		case ASSIGN:
		  printf(":=");
		  break; 
		case EQ:
		  printf("=");
		  break; 
		case LT:
		  printf("<");
		  break; 
		case PLUS:
		  printf("+");
		  break; 
		case MINUS:
		  printf("-");
		  break; 
		case TIMES:
		  printf("*");
		  break; 
		case DIVIDE:
		  printf("/");
		  break; 
		case LPAREN:
		  printf("(");
		  break; 
		case RPAREN:
		  printf(")");
		  break; 
		case DOT:
		  printf(".");
		  break; 
		case COLON:
		  printf(":");
		  break; 
		case SEMI:
		  printf(";");
		  break; 
		case COMMA:
		  printf(",");
		  break; 
		case LMIDPAREN:
		  printf("[");
		  break; 
		case RMIDPAREN:
		  printf("]");
		  break; 
		case UNDERANGE:
		  printf("..");
		  break; 
    }
}
