#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

#include "Snode.h"
#include "scanner.h"

class Parser
{
    Token * cur_token;
    Token * pre_token;

    Parser(Token * head){
        cur_token = head;
    }
public:
    bool state = true;
public:
    static Parser* getParser(Token * head)
    {
        return (new Parser(head));
    }
public:


public:
    STnode * Program();

private:
    STnode * ProgramHead();
    STnode * ProgramName();
    STnode * DeclarePart();
    STnode * TypeDecPart();
    STnode * TypeDec();
    STnode * TypeDecList();
    STnode * TypeDecMore();
    STnode * TypeId();
    STnode * TypeDef();
    STnode * BaseType();
    STnode * StructureType();
    STnode * ArrayType();
    STnode * Low();
    STnode * Top();
    STnode * RecType();
    STnode * FieldDecList();
    STnode * FieldDecMore();
    STnode * IdList();
    STnode * IdMore();
    STnode * VarDecPart();
    STnode * VarDec();
    STnode * VarDecList();
    STnode * VarDecMore();
    STnode * VarIdList();
    STnode * VarIdMore();
    STnode * ProcDecPart();
    STnode * ProcDec();
    STnode * ProcDecMore();
    STnode * ProcName();
    STnode * ParamList();
    STnode * ParamDecList();
    STnode * ParamMore();
    STnode * Param();
    STnode * FormList();
    STnode * FidMore();
    STnode * ProcBody();
    STnode * ProgramBody();
    STnode * StmList();
    STnode * StmMore();
    STnode * Stm();
    STnode * AssCall();
    STnode * AssignmentRest();
    STnode * ConditionalStm();
    STnode * LoopStm();
    STnode * InputStm();
    STnode * Invar();
    STnode * OutputStm();
    STnode * ReturnStm();
    STnode * CallStmRest();
    STnode * ActParamList();
    STnode * ActParamMore();
    STnode * RelExp();
    STnode * OtherRelE();
    STnode * Exp();
    STnode * OtherTerm();
    STnode * Term();
    STnode * OtherFactor();
    STnode * Factor();
    STnode * Variable();
    STnode * VariMore();
    STnode * FieldVar();
    STnode * FieldVarMore();
    STnode * CmpOp();
    STnode * AddOp();
    STnode * MultOp();
    bool match(LexType lex);
};




#endif // PARSE_H_INCLUDED
