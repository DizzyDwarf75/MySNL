
#include <iostream>
#include <cstring>

#include <map>
#include <stack>
#include <fstream>
#include "parserLL1.h"

using namespace std;


map<int, string> Tnode =
{

    {Program , "ProgramK"},
    {ProgramHead , "ProgramHeadK"},
    {ProgramName , "ProgramNameK"},
    {DeclarePart , "DeclarePartK"},
    {TypeDecPart , "TypeDecPartK"},
    {TypeDec , "TypeDecK"},
    {TypeDecList , "TypeDecListK"},
    {TypeDecMore , "TypeDecMoreK"},
    {TypeId , "TypeIdK"},
    {TypeDef , "TypeDefK"},
    {BaseType , "BaseTypeK"},
    {StructureType , "StructureTypeK"},
    {ArrayType , "ArrayTypeK"},
    {Low , "LowK"},
    {Top , "TopK"},
    {RecType , "RecTypeK"},
    {FieldDecList , "FieldDecListK"},
    {FieldDecMore , "FieldDecMoreK"},
    {IdList , "IdListK"},
    {IdMore , "IdMoreK"},
    {VarDecPart , "VarDecPartK"},
    {VarDec , "VarDecK"},
    {VarDecList , "VarDecListK"},
    {VarDecMore , "VarDecMoreK"},
    {VarIdList , "VarIdListK"},
    {VarIdMore , "VarIdMoreK"},
    {ProcDecPart , "ProcDecPartK"},
    {ProcDec , "ProcDecK"},
    {ProcDecMore , "ProcDecMoreK"},
    {ProcName , "ProcNameK"},
    {ParamList , "ParamListK"},
    {ParamDecList , "ParamDecListK"},
    {ParamMore , "ParamMoreK"},
    {Param , "ParamK"},
    {FormList , "FormListK"},
    {FidMore , "FidMoreK"},
    {ProcBody , "ProcBodyK"},
    {ProgramBody , "ProgramBodyK"},
    {StmList , "StmListK"},
    {StmMore , "StmMoreK"},
    {Stm , "StmK"},
    {AssCall , "AssCallK"},
    {AssignmentRest , "AssignmentRestK"},
    {ConditionalStm , "ConditionalStmK"},
    {LoopStm , "LoopStmK"},
    {InputStm , "InputStmK"},
    {Invar , "InvarK"},
    {OutputStm , "OutputStmK"},
    {ReturnStm , "ReturnStmK"},
    {CallStmRest , "CallStmRestK"},
    {ActParamList , "ActParamListK"},
    {ActParamMore , "ActParamMoreK"},
    {RelExp , "RelExpK"},
    {OtherRelE , "OtherRelEK"},
    {Exp , "ExpK"},
    {OtherTerm , "OtherTermK"},
    {Term , "TermK"},
    {OtherFactor , "OtherFactorK"},
    {Factor , "FactorK"},
    {Variable , "VariableK"},
    {VariMore , "VariMoreK"},
    {FieldVar , "FieldVarK"},
    {FieldVarMore , "FieldVarMoreK"},
    {CmpOp , "CmpOpK"},
    {AddOp , "AddOpK"},
    {MultOp , "MultOpK"},
    {HHH , "HHHK"},
    {PROGRAM , "PROGRAMK"},
    {TYPE , "TYPEK"},
    {VAR , "VARK"},
    {PROCEDURE , "PROCEDUREK"},
    {BEGIN , "BEGINK"},
    {END , "ENDK"},
    {ARRAY , "ARRAYK"},
    {OF , "OFK"},
    {RECORD , "RECORDK"},
    {IF , "IFK"},
    {THEN , "THENK"},
    {ELSE , "ELSEK"},
    {FI , "FIK"},
    {WHILE , "WHILEK"},
    {DO , "DOK"},
    {ENDWH , "ENDWHK"},
    {READ , "READK"},
    {WRITE , "WRITEK"},
    {RETURN , "RETURNK"},
    {INTEGER , "INTEGERK"},
    {CHAR , "CHARK"},
    {INTEGER_T , "INTEGER_TK"},
    {CHAR_T , "CHAR_TK"},
    {ID , "IDK"},
    {ASSIGN , "ASSIGNK"},
    {EQ , "EQK"},
    {LT , "LTK"},
    {PLUS , "PLUSK"},
    {MINUS , "MINUSK"},
    {TIMES , "TIMESK"},
    {DIVIDE , "DIVIDEK"},
    {LPAREN , "LPARENK"},
    {RPAREN , "RPARENK"},
    {DOT , "DOTK"},
    {COLON , "COLONK"},
    {SEMI , "SEMIK"},
    {COMMA , "COMMAK"},
    {LMIDPAREN , "LMIDPARENK"},
    {RMIDPAREN , "RMIDPARENK"},
    {UNDERRANGE , "UNDERRANGEK"},
    {ENDFILE , "ENDFILEK"},
    {ERROR , "ERRORK"},
    {INTC_VAL , "INTC_VALK"},
    {CHAR_VAL , "CHAR_VALK"},

};





bool  ParserLL::match(LexType lex)
{
    if(cur_token->getLex() == lex)
    {
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
void ParserLL::parse()
{

    stack<int> sta;
    stack<int> levers;

    sta.push(-1);
    sta.push(Program);

    levers.push(-1);
    levers.push(0);
    levers.push(1);



    while(cur_token!=NULL)
    {
        int pre = sta.top();
        int lev = levers.top();

        LexType lex = cur_token->getLex();

        if(pre == HHH )
        {
            sta.pop();
            levers.pop();

            continue;
        }


        //printf("pre = %d %d %d\n",pre,cur_token->getLex(),cur_token->getLine());

        if( pre >= 100)
        {
            int expression = mp[pre][lex];

            //printf("expression = %d\n",expression);

            if(expression < 0)
            {
                cout<<"line "<<cur_token->getLine()<<" : unexpected token "<<cur_token->getLexName()<<" : "<<cur_token->getSem()<<endl;
                state = false;
                break;
            }

            sta.pop();
            levers.pop();

            cout<<lev<<":";

            for(int i=0; i<lev * 2; i++)
                printf(" ");

            cout<<Tnode[pre]<<endl;


            for(int i=0; i<exnode[expression].len; i++)
            {
                sta.push(exnode[expression].lst[i]);
                levers.push(lev + 1);
            }
        }
        else
        {
            if(match((LexType)pre))
            {
                sta.pop();
                levers.pop();

                //printf("%d ",lev);
                cout<<lev<<":";
                for(int i=0; i<lev * 2; i++)
                    printf(" ");
                cout<<Tnode[pre]<<" "<<pre_token->getSem()<<endl;

            }
            else
            {
                cout<<"line "<<cur_token->getLine()<<" : unexpected token "<<cur_token->getLexName()<<" : "<<cur_token->getSem()<<endl;
                state = false;
                break;
            }
        }
    }

    //printf("ok");

    if(sta.top()!=-1)
        state = false;


}

