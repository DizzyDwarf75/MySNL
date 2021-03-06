#include <iostream>
#include <cctype>
#include "lex.h"

map<LexType, string> lexName = {
    {PROGRAM, "PROGRAM"},   {TYPE, "TYPE"}, {VAR, "VAR"},       {PROCEDURE, "PROCEDURE"},
    {BEGIN, "BEGIN"},       {END, "END"},   {ARRAY, "ARRAY"},   {OF, "OF"},
    {RECORD, "RECORD"},     {IF, "IF"},     {THEN, "THEN"},     {ELSE, "ELSE"},
    {FI, "FI"},             {WHILE, "WHILE"},{DO, "DO"},        {ENDWH, "ENDWH"},
    {READ, "READ"},         {WRITE, "WRITE"},{RETURN, "RETURN"},{INTEGER, "INTEGER"},
    {CHAR, "CHAR"}, {INTEGER_T, "INTEGER_T"},{CHAR_T, "CHAR_T"},{ID, "ID"},
    {INTC_VAL, "INTC_VAL"},{CHAR_VAL, "CHAR_VAL"},{ASSIGN, ":="},{EQ, "="},
    {LT, "<"},     {PLUS, "+"},         {MINUS, "-"},   {TIMES, "*"},
    {DIVIDE, "/"}, {LPAREN, "("}, {RPAREN, ")"}, {DOT, "."},
    {COLON, ":"},   {SEMI, ";"},     {COMMA, ","},   {LMIDPAREN, "["},
    {RMIDPAREN, "]"},   {UNDERRANGE, ".."},       {ENDFILE, "EOF"},
    {ERROR, "ERROR"}
};

map<string, LexType> reservedWords = {
    { "program", PROGRAM},{ "type", TYPE},{ "var", VAR},{ "procedure", PROCEDURE},
    { "begin", BEGIN},{ "end", END},{ "array", ARRAY},{ "of", OF},
    { "record", RECORD},{ "if", IF},{ "then", THEN},{ "else", ELSE},
    { "fi", FI},{ "char", CHAR},{ "while", WHILE},{ "do", DO},
    { "endwh", ENDWH},{ "read", READ},{ "write", WRITE},{ "return", RETURN},
    { "integer", INTEGER},
};

Token * Lexer::getTokenList()
{
    Token * head = new Token(0, ERROR, "");
    Token * current = head;
    char lookahead;

    while(source.get(lookahead) && !source.eof())
    {
        if(lookahead == '\n')
            ++lineRec;
        if(isalpha(lookahead))
        {
            string s(1, lookahead);
            idBuff.append(s);
            while(source.get(lookahead) && isalnum(lookahead))
            {
                string s(1, lookahead);
                idBuff.append(s);
            }
            source.unget();
            Token * tmp = reversedLookup(idBuff);
            current->next = tmp;
            current = current->next;
            idBuff.clear();
        }
        else if(isdigit(lookahead))
        {
            string s(1, lookahead);
            idBuff.append(s);
            while(source.get(lookahead) && isdigit(lookahead))
            {
                string s(1, lookahead);
                idBuff.append(s);
                //intBuff = intBuff * 10 + (lookahead-'0');
            }
            source.unget();

            Token * tmp = new Token(lineRec, INTC_VAL, idBuff);
            idBuff.clear();
            current->next = tmp;
            current = current->next;
        }
        else if(isssep(lookahead))
        {
            Token * tmp = ssep(lookahead);
            current->next = tmp;
            current = current->next;
        }
        else if(lookahead == ':')
        {
            char next;
            source.get(next);
            if(next != '=')
            {
                cout<<"line "<<lineRec<<" : Unknown pattern: "<<lookahead<<next<<endl;
                source.unget();
            }
            else
            {
                Token * tmp = new Token(lineRec, ASSIGN, lexName[ASSIGN]);
                current->next = tmp;
                current = current->next;
            }
        }
        else if(lookahead == '{')
        {
            char next;
            while(source.get(next) && next != '}')
            {
            }
        }
        else if(lookahead == '.')
        {
            char next;
                source.get(next);
                if(next == '.')
                {
                    Token * tmp = new Token(lineRec, UNDERRANGE, lexName[UNDERRANGE]);
                    current->next = tmp;
                    current = current->next;
                }
                else
                {
                    Token * tmp = new Token(lineRec, DOT, lexName[DOT]);
                    current->next = tmp;
                    current = current->next;
                    source.unget();
                }
        }
        else if(lookahead == '\'')
        {
            char next;
            source.get(next);
            if(!isalnum(next))
            {
                cout<<"line "<<lineRec<<" : Unknown pattern: "<<lookahead<<next<<endl;
                source.unget();
            }
            else
            {
                string s(1, next);
                idBuff.append(s);
                source.get(next);
                if(next != '\'')
                {
                    cout<<"line "<<lineRec<<" : Unknown pattern: "<<lookahead<<idBuff<<next<<endl;
                    source.unget();
                    source.unget();
                }
                else
                {
                    Token * tmp = new Token(lineRec, CHAR_VAL, idBuff);
                    current->next = tmp;
                    current = current->next;
                    idBuff.clear();
                }
            }
        }
        else
        {
            if(!isspace(lookahead))
            {
                if(lookahead == '.')
                {
                    Token * tmp = new Token(lineRec, DOT, ".");
                    current->next = tmp;
                    current = current->next;
                }
                else
                {
                    cout<<"line "<<lineRec<<" : Unknown character "<<lookahead<<endl;
                }
            }
        }
    }
    current = head;
    head = head->next;
    delete current;
    return head;
}

bool Lexer::isssep(char c)
{
    if(c == ',' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';' || c == '[' || c == ']' || c == '=' || c == '<')
        return true;
    else
        return false;
}

Token * Lexer::ssep(char c)
{
    map<char, LexType> sgsep = {
        {'+', PLUS}, {'-', MINUS}, {'*', TIMES}, {'/', DIVIDE},
        {'(', LPAREN}, {')', RPAREN}, {';', SEMI}, {'[', LMIDPAREN},
        {']', RMIDPAREN}, {'=', EQ}, {'<', LT}, {',', COMMA}
    };
    Token * tmp = new Token(lineRec, sgsep[c], lexName[sgsep[c]]);
    return tmp;
}

void Lexer::printTokenList(Token * head)
{
    Token * curr = head;
    while(curr)
    {
        cout<<curr->getLine()<<" : "<<curr->getLexName()<<" , "<<curr->getSem()<<endl;
        curr = curr->next;
    }
}

Token * Lexer::reversedLookup(string str)
{
    Token * tmp;
    if(reservedWords.find(str) != reservedWords.end())
    {
        tmp = new Token(lineRec, reservedWords[str], str);
    }
    else
    {
        tmp = new Token(lineRec, ID, str);
    }
    return tmp;
}
