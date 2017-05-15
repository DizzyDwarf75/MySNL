#include <iostream>
#include "scanner.h"
#include "parse.h"
#include "parserLL1.h"

//#include "parser.h"

using namespace std;

void readTxt(string file)
{
    ifstream infile;
    infile.open(file.data());   //���ļ����������ļ���������
    //assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ��������

    string s;
    while(getline(infile,s))
    {
        cout<<s<<endl;
    }
    infile.close();             //�ر��ļ�������
}


Token * lexsolve(string filename)
{
    Lexer * lex = Lexer::getLexer(filename.c_str());
    Token * head = lex->getTokenList();
    cout<<"down phase 1"<<endl;
    lex->printTokenList(head);
    cout<<"ok\n";
    return head;
}

void parsersolve(Token * head)
{
    Parser * parser = Parser::getParser(head);
    parser->Program();
    if(parser->state)
        cout<<"No error occured.\n";
     else cout<<"Error occured.\n";
}

void parserLLsolve(Token * head)
{
    ParserLL * parser = ParserLL::getParser(head);

    parser->parse();
    if(parser->state)
        cout<<"1:  No error occured.\n";
    else cout<<"Error occured.\n";


    //parser->Program();
    //if(parser->state)
    //    cout<<"No error occured.\n";
}




int main()
{



    //�ʷ�����

    string filename = "c1.txt";

    cout << "input filename:";
    cin >> filename;

    Token * head = lexsolve(filename);

    //�﷨���� �ݹ�����

    parsersolve(head);

    cout<<"ok\n";

    ////�﷨���� LL(1)



    freopen( "../outputTree/Myout.txt", "w", stdout );

    parserLLsolve(head);


    //FILE * file = fopen("path.txt","r");

   // while(f)

   //string path = "path.txt";
  // readTxt(path);








    return 0;
}
