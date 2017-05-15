#include <iostream>
#include "scanner.h"
#include "parse.h"
#include "parserLL1.h"

//#include "parser.h"

using namespace std;

void readTxt(string file)
{
    ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来
    //assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行

    string s;
    while(getline(infile,s))
    {
        cout<<s<<endl;
    }
    infile.close();             //关闭文件输入流
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



    //词法分析

    string filename = "c1.txt";

    cout << "input filename:";
    cin >> filename;

    Token * head = lexsolve(filename);

    //语法分析 递归向下

    parsersolve(head);

    cout<<"ok\n";

    ////语法分析 LL(1)



    freopen( "../outputTree/Myout.txt", "w", stdout );

    parserLLsolve(head);


    //FILE * file = fopen("path.txt","r");

   // while(f)

   //string path = "path.txt";
  // readTxt(path);








    return 0;
}
