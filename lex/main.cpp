#include <iostream>
#include "lex.h"
#include "lex.cpp"
using namespace std;
int main()
{
    Lexer * lex = Lexer::getLexer("snl");
    Token * head = lex->getTokenList();

    cout<<"down phase 1"<<endl;
    lex->printTokenList(head);
    return 0;
}
