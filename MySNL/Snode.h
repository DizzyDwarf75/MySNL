#ifndef SNODE_H_INCLUDED
#define SNODE_H_INCLUDED

#ifndef __NODE_H__
#define __NODE_H__


#include <string>
#include <vector>
using namespace std;

//STnode : the base class
class STnode
{
public:
    virtual void display(string& sep);
};

//ExpK
class ExpK : public STnode
{
public:
    void display(string& sep);
    //ExpK members
};

//OpK :
class OpK : public ExpK
{
public:
    void display(string& sep);
    //OpK members
    char op;
    STnode * left;
    STnode * right;
};

//Const :
class Const : public ExpK
{
public:
    void display(string& sep);
    //Const members
    int value;
};

class IdV : public ExpK
{
public:
    void display(string& sep);
    //IdV members
    string name;
};

//StmtK
class StmtK : public STnode
{
public:
    void display(string& sep);
    //StmtK members;
};


//IfK
class IfK : public StmtK
{
public:
    void display(string& sep);
    //IfK members
    STnode * condtE;
    STnode * thenS;
    STnode * elseS;
};

//WhileK
class WhileK : public StmtK
{
public:
    void display(string& sep);
    //WhileK members
    STnode * condtE;
    STnode * bodyS;
};

//AssignK
class AssignK : public StmtK
{
public:
    void display(string& sep);
    //Assign members
    STnode * left;
    STnode * right;
};

//ReadK
class ReadK : public StmtK
{
public:
    void display(string& sep);
    //ReadK members
    string id;
};

//WriteK
class WriteK : public StmtK
{
public:
    void display(string& sep);
    //WriteK members
    string id;
};

//CallK
class CallK : public StmtK
{
public:
    void display(string& sep);
    //CallK members
    STnode * name;
    STnode * param;
};

//ReturnK
class ReturnK : public StmtK
{
public:
    void display(string& sep);
    //ReturnK members
    //nothing here
};

//DecK
class DecK : public STnode
{
public:
    void display(string& sep);
    //DecK members
};

//ArrayK
class ArrayK : public DecK
{
public:
    void display(string& sep);
    //ArrayK members
    string typeName;
    int low;
    int top;
};

//CharK
class CharK : public DecK
{
public:
    void display(string& sep);
    //CharK members
    vector<string> ids;
};

//IntegerK
class IntegerK : public DecK
{
public:
    void display(string& sep);
    //IntegerK members
    vector<string> ids;
};

//RecordK
class RecordK : public DecK
{
public:
    void display(string& sep);
    //Record members
    STnode * child;
};

class IdK : public DecK
{
public:
    void display(string& sep);
    //IdK members
    string * type;
    string id;
};

//ProK    root
class ProK : public STnode
{
public:
    void display(string& sep);
    //ProK members
    STnode * programHead;
    STnode * declarePart;
    STnode * programBody;
};

//PheadK
class PheadK : public STnode
{
public:
    void display(string& sep);
    //PheadK members
    string programName;
};

//TypeK
class TypeK : public STnode
{
public:
    void display(string& sep);
    //TypeK members
    STnode * child;
    STnode * sibling;
};

//VarK
class VarK : public STnode
{
public:
    void display(string& sep);
    //VarK members
    STnode * child;
    STnode * sibling;
};

//ProcDecK
class ProcDecK : public STnode
{
public:
    void display(string& sep);
    //ProcDecK members
    string procName;
    STnode * params;
    STnode * body;
    STnode * sibling;
};

//StmLK
class StmLK : public STnode
{
public:
    void display(string& sep);
    //StmLK members
    vector<STnode*> stmts;
};

#endif



#endif // SNODE_H_INCLUDED
