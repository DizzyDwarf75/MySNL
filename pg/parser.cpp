#include "parser.h"
#include <iostream>
using namespace std;


STnode * Parser::Program()
{
  ProgramHead();
  DeclarePart();
  ProgramBody();
  match(DOT);
  return nullptr;
}

STnode * Parser::ProgramHead()
{
  match(PROGRAM);
  ProgramName();
  return nullptr;
}

STnode * Parser::ProgramName()
{
  match(ID);
  return nullptr;
}

STnode * Parser::DeclarePart()
{
  TypeDecPart();
  VarDecPart();
  ProcDecPart();
  return nullptr;
}

STnode * Parser::TypeDecPart()
{
  if(cur_token->getLex() == PROCEDURE || cur_token->getLex() ==  VAR || cur_token->getLex() ==  BEGIN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == TYPE)
  {
    TypeDec();
  }
  return nullptr;
}

STnode * Parser::TypeDec()
{
  match(TYPE);
  TypeDecList();
  return nullptr;
}

STnode * Parser::TypeDecList()
{
  TypeId();
  match(EQ);
  TypeDef();
  match(SEMI);
  TypeDecMore();
  return nullptr;
}

STnode * Parser::TypeDecMore()
{
  if(cur_token->getLex() == PROCEDURE || cur_token->getLex() ==  VAR || cur_token->getLex() ==  BEGIN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == ID)
  {
    TypeDecList();
  }
  return nullptr;
}

STnode * Parser::TypeId()
{
  match(ID);
  return nullptr;
}

STnode * Parser::TypeDef()
{
  if(cur_token->getLex() == INTEGER || cur_token->getLex() ==  CHAR)
  {
    BaseType();
  }
  else if(cur_token->getLex() == ARRAY || cur_token->getLex() ==  RECORD)
  {
    StructureType();
  }
  else if(cur_token->getLex() == ID)
  {
    match(ID);
  }
  return nullptr;
}

STnode * Parser::BaseType()
{
  if(cur_token->getLex() == INTEGER)
  {
    match(INTEGER);
  }
  else if(cur_token->getLex() == CHAR)
  {
    match(CHAR);
  }
  return nullptr;
}

STnode * Parser::StructureType()
{
  if(cur_token->getLex() == ARRAY)
  {
    ArrayType();
  }
  else if(cur_token->getLex() == RECORD)
  {
    RecType();
  }
  return nullptr;
}

STnode * Parser::ArrayType()
{
  match(ARRAY);
  match(LMIDPAREN);
  Low();
  match(UNDERRANGE);
  Top();
  match(RMIDPAREN);
  match(OF);
  BaseType();
  return nullptr;
}

STnode * Parser::Low()
{
  match(INTC_VAL);
  return nullptr;
}

STnode * Parser::Top()
{
  match(INTC_VAL);
  return nullptr;
}

STnode * Parser::RecType()
{
  match(RECORD);
  FieldDecList();
  match(END);
  return nullptr;
}

STnode * Parser::FieldDecList()
{
  if(cur_token->getLex() == INTEGER || cur_token->getLex() ==  CHAR)
  {
    BaseType();
    IdList();
    match(SEMI);
    FieldDecMore();
  }
  else if(cur_token->getLex() == ARRAY)
  {
    ArrayType();
    IdList();
    match(SEMI);
    FieldDecMore();
  }
  return nullptr;
}

STnode * Parser::FieldDecMore()
{
  if(cur_token->getLex() == END)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == INTEGER || cur_token->getLex() ==  CHAR || cur_token->getLex() ==  ARRAY)
  {
    FieldDecList();
  }
  return nullptr;
}

STnode * Parser::IdList()
{
  match(ID);
  IdMore();
  return nullptr;
}

STnode * Parser::IdMore()
{
  if(cur_token->getLex() == SEMI)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == COMMA)
  {
    match(COMMA);
    IdList();
  }
  return nullptr;
}

STnode * Parser::VarDecPart()
{
  if(cur_token->getLex() == PROCEDURE || cur_token->getLex() ==  BEGIN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == VAR)
  {
    VarDec();
  }
  return nullptr;
}

STnode * Parser::VarDec()
{
  match(VAR);
  VarDecList();
  return nullptr;
}

STnode * Parser::VarDecList()
{
  TypeDef();
  VarIdList();
  match(SEMI);
  VarDecMore();
  return nullptr;
}

STnode * Parser::VarDecMore()
{
  if(cur_token->getLex() == PROCEDURE || cur_token->getLex() ==  BEGIN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == ID || cur_token->getLex() ==  INTEGER || cur_token->getLex() ==  CHAR || cur_token->getLex() ==  ARRAY || cur_token->getLex() ==  RECORD)
  {
    VarDecList();
  }
  return nullptr;
}

STnode * Parser::VarIdList()
{
  match(ID);
  VarIdMore();
  return nullptr;
}

STnode * Parser::VarIdMore()
{
  if(cur_token->getLex() == SEMI)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == COMMA)
  {
    match(COMMA);
    VarIdList();
  }
  return nullptr;
}

STnode * Parser::ProcDecPart()
{
  if(cur_token->getLex() == BEGIN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == PROCEDURE)
  {
    ProcDec();
  }
  else if(cur_token->getLex() == TYPE || cur_token->getLex() ==  VAR)
  {
    DeclarePart();
  }
  return nullptr;
}

STnode * Parser::ProcDec()
{
  match(PROCEDURE);
  ProcName();
  match(LPAREN);
  ParamList();
  match(RPAREN);
  match(SEMI);
  ProcDecPart();
  ProcBody();
  ProcDecMore();
  return nullptr;
}

STnode * Parser::ProcDecMore()
{
  if(cur_token->getLex() == BEGIN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == PROCEDURE)
  {
    ProcDec();
  }
  return nullptr;
}

STnode * Parser::ProcName()
{
  match(ID);
  return nullptr;
}

STnode * Parser::ParamList()
{
  if(cur_token->getLex() == RPAREN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == VAR || cur_token->getLex() ==  ID || cur_token->getLex() ==  INTEGER || cur_token->getLex() ==  CHAR || cur_token->getLex() ==  ARRAY || cur_token->getLex() ==  RECORD)
  {
    ParamDecList();
  }
  return nullptr;
}

STnode * Parser::ParamDecList()
{
  Param();
  ParamMore();
  return nullptr;
}

STnode * Parser::ParamMore()
{
  if(cur_token->getLex() == RPAREN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == SEMI)
  {
    match(SEMI);
    ParamDecList();
  }
  return nullptr;
}

STnode * Parser::Param()
{
  if(cur_token->getLex() == ID || cur_token->getLex() ==  INTEGER || cur_token->getLex() ==  CHAR || cur_token->getLex() ==  ARRAY || cur_token->getLex() ==  RECORD)
  {
    TypeDef();
    FormList();
  }
  else if(cur_token->getLex() == VAR)
  {
    match(VAR);
    TypeDef();
    FormList();
  }
  return nullptr;
}

STnode * Parser::FormList()
{
  match(ID);
  FidMore();
  return nullptr;
}

STnode * Parser::FidMore()
{
  if(cur_token->getLex() == SEMI || cur_token->getLex() ==  RPAREN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == COMMA)
  {
    match(COMMA);
    FormList();
  }
  return nullptr;
}

STnode * Parser::ProcBody()
{
  ProgramBody();
  return nullptr;
}

STnode * Parser::ProgramBody()
{
  match(BEGIN);
  StmList();
  match(END);
  return nullptr;
}

STnode * Parser::StmList()
{
  Stm();
  StmMore();
  return nullptr;
}

STnode * Parser::StmMore()
{
  if(cur_token->getLex() == ENDWH || cur_token->getLex() ==  ELSE || cur_token->getLex() ==  FI || cur_token->getLex() ==  END)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == SEMI)
  {
    match(SEMI);
    StmList();
  }
  return nullptr;
}

STnode * Parser::Stm()
{
  if(cur_token->getLex() == IF)
  {
    ConditionalStm();
  }
  else if(cur_token->getLex() == WHILE)
  {
    LoopStm();
  }
  else if(cur_token->getLex() == READ)
  {
    InputStm();
  }
  else if(cur_token->getLex() == WRITE)
  {
    OutputStm();
  }
  else if(cur_token->getLex() == RETURN)
  {
    ReturnStm();
  }
  else if(cur_token->getLex() == ID)
  {
    match(ID);
    AssCall();
  }
  return nullptr;
}

STnode * Parser::AssCall()
{
  if(cur_token->getLex() == ASSIGN || cur_token->getLex() ==  LMIDPAREN || cur_token->getLex() ==  DOT)
  {
    AssignmentRest();
  }
  else if(cur_token->getLex() == LPAREN)
  {
    CallStmRest();
  }
  return nullptr;
}

STnode * Parser::AssignmentRest()
{
  VariMore();
  match(ASSIGN);
  Exp();
  return nullptr;
}

STnode * Parser::ConditionalStm()
{
  match(IF);
  RelExp();
  match(THEN);
  StmList();
  match(ELSE);
  StmList();
  match(FI);
  return nullptr;
}

STnode * Parser::LoopStm()
{
  match(WHILE);
  RelExp();
  match(DO);
  StmList();
  match(ENDWH);
  return nullptr;
}

STnode * Parser::InputStm()
{
  match(READ);
  match(LPAREN);
  Invar();
  match(RPAREN);
  return nullptr;
}

STnode * Parser::Invar()
{
  match(ID);
  return nullptr;
}

STnode * Parser::OutputStm()
{
  match(WRITE);
  match(LPAREN);
  Exp();
  match(RPAREN);
  return nullptr;
}

STnode * Parser::ReturnStm()
{
  match(RETURN);
  return nullptr;
}

STnode * Parser::CallStmRest()
{
  match(LPAREN);
  ActParamList();
  match(RPAREN);
  return nullptr;
}

STnode * Parser::ActParamList()
{
  if(cur_token->getLex() == RPAREN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == LPAREN || cur_token->getLex() ==  INTC_VAL || cur_token->getLex() ==  ID)
  {
    Exp();
    ActParamMore();
  }
  return nullptr;
}

STnode * Parser::ActParamMore()
{
  if(cur_token->getLex() == RPAREN)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == COMMA)
  {
    match(COMMA);
    ActParamList();
  }
  return nullptr;
}

STnode * Parser::RelExp()
{
  Exp();
  OtherRelE();
  return nullptr;
}

STnode * Parser::OtherRelE()
{
  CmpOp();
  Exp();
  return nullptr;
}

STnode * Parser::Exp()
{
  Term();
  OtherTerm();
  return nullptr;
}

STnode * Parser::OtherTerm()
{
  if(cur_token->getLex() == RMIDPAREN || cur_token->getLex() ==  RPAREN || cur_token->getLex() ==  LT || cur_token->getLex() ==  EQ || cur_token->getLex() ==  COMMA || cur_token->getLex() ==  DO || cur_token->getLex() ==  THEN || cur_token->getLex() ==  SEMI || cur_token->getLex() ==  ENDWH || cur_token->getLex() ==  ELSE || cur_token->getLex() ==  FI || cur_token->getLex() ==  END)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == PLUS || cur_token->getLex() ==  MINUS)
  {
    AddOp();
    Exp();
  }
  return nullptr;
}

STnode * Parser::Term()
{
  Factor();
  OtherFactor();
  return nullptr;
}

STnode * Parser::OtherFactor()
{
  if(cur_token->getLex() == PLUS || cur_token->getLex() ==  MINUS || cur_token->getLex() ==  RMIDPAREN || cur_token->getLex() ==  RPAREN || cur_token->getLex() ==  LT || cur_token->getLex() ==  EQ || cur_token->getLex() ==  COMMA || cur_token->getLex() ==  DO || cur_token->getLex() ==  THEN || cur_token->getLex() ==  SEMI || cur_token->getLex() ==  ENDWH || cur_token->getLex() ==  ELSE || cur_token->getLex() ==  FI || cur_token->getLex() ==  END)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == TIMES || cur_token->getLex() ==  DIVIDE)
  {
    MultOp();
    Term();
  }
  return nullptr;
}

STnode * Parser::Factor()
{
  if(cur_token->getLex() == LPAREN)
  {
    match(LPAREN);
    Exp();
    match(RPAREN);
  }
  else if(cur_token->getLex() == INTC_VAL)
  {
    match(INTC_VAL);
  }
  else if(cur_token->getLex() == CHAR_VAL)
  {
    match(CHAR_VAL);
  }
  else if(cur_token->getLex() == ID)
  {
    Variable();
  }
  return nullptr;
}

STnode * Parser::Variable()
{
  match(ID);
  VariMore();
  return nullptr;
}

STnode * Parser::VariMore()
{
  if(cur_token->getLex() == ASSIGN || cur_token->getLex() ==  TIMES || cur_token->getLex() ==  DIVIDE || cur_token->getLex() ==  PLUS || cur_token->getLex() ==  MINUS || cur_token->getLex() ==  RMIDPAREN || cur_token->getLex() ==  RPAREN || cur_token->getLex() ==  LT || cur_token->getLex() ==  EQ || cur_token->getLex() ==  COMMA || cur_token->getLex() ==  DO || cur_token->getLex() ==  THEN || cur_token->getLex() ==  SEMI || cur_token->getLex() ==  ENDWH || cur_token->getLex() ==  ELSE || cur_token->getLex() ==  FI || cur_token->getLex() ==  END)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == LMIDPAREN)
  {
    match(LMIDPAREN);
    Exp();
    match(RMIDPAREN);
  }
  else if(cur_token->getLex() == DOT)
  {
    match(DOT);
    FieldVar();
  }
  return nullptr;
}

STnode * Parser::FieldVar()
{
  match(ID);
  FieldVarMore();
  return nullptr;
}

STnode * Parser::FieldVarMore()
{
  if(cur_token->getLex() == ASSIGN || cur_token->getLex() ==  TIMES || cur_token->getLex() ==  DIVIDE || cur_token->getLex() ==  PLUS || cur_token->getLex() ==  MINUS || cur_token->getLex() ==  RMIDPAREN || cur_token->getLex() ==  RPAREN || cur_token->getLex() ==  LT || cur_token->getLex() ==  EQ || cur_token->getLex() ==  COMMA || cur_token->getLex() ==  DO || cur_token->getLex() ==  THEN || cur_token->getLex() ==  SEMI || cur_token->getLex() ==  ENDWH || cur_token->getLex() ==  ELSE || cur_token->getLex() ==  FI || cur_token->getLex() ==  END)
  {
    return nullptr;
  }
  else if(cur_token->getLex() == LMIDPAREN)
  {
    match(LMIDPAREN);
    Exp();
    match(RMIDPAREN);
  }
  return nullptr;
}

STnode * Parser::CmpOp()
{
  if(cur_token->getLex() == LT)
  {
    match(LT);
  }
  else if(cur_token->getLex() == EQ)
  {
    match(EQ);
  }
  return nullptr;
}

STnode * Parser::AddOp()
{
  if(cur_token->getLex() == PLUS)
  {
    match(PLUS);
  }
  else if(cur_token->getLex() == MINUS)
  {
    match(MINUS);
  }
  return nullptr;
}

STnode * Parser::MultOp()
{
  if(cur_token->getLex() == TIMES)
  {
    match(TIMES);
  }
  else if(cur_token->getLex() == DIVIDE)
  {
    match(DIVIDE);
  }
  return nullptr;
}

            bool Parser::match(LexType lex)
            {
                if(cur_token->getLex() == lex)
                {
                    //cout<<cur_token->getSem()<<endl;
                    pre_token = cur_token;
                    cur_token = cur_token->next;
                    return true;
                }
                else
                {
                    cout<<"line "<<cur_token->getLine()<<" : unexpected token "<<cur_token->getLexName()<<" : "<<cur_token->getSem()<<endl;
                    this->state = false;
                    return false;
                }
            }
            