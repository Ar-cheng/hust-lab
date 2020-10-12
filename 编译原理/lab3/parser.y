%error-verbose//更准确的给出错误性质
%locations//更准确的标识错误的位置
%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"

extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct ASTNode *,int);
%}

%union {
	int    type_int;
	float  type_float;
        char   type_char[2];
        char   type_string[31];
	char   type_id[32];
	struct ASTNode *ptr;
};

//  %type 定义非终结符的语义值类型
%type  <ptr> program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args  StructSpecifier StructName FORDEC 

//% token 定义终结符的语义值类型
%token <type_int> INT              /*指定INT的语义值是type_int，有词法分析得到的数值*/
%token <type_id> ID  RELOP TYPE    /*指定ID,RELOP 的语义值是type_id，有词法分析得到的标识符字符串*/
%token <type_float> FLOAT          /*指定ID的语义值是type_id，有词法分析得到的标识符字符串*/
%token <type_char> CHAR            /*指定CHAR的语义是type_char，由词法分析得到的数值*/
%token <type_string> STRING        /*指定STRING的语义是type_string，由词法分析得到的数值*/

%token LP RP LC RC SEMI COMMA      //{ } ( ) ; , 
/*用bison对该文件编译时，带参数-d，生成的.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码*/
%token PLUS MINUS STAR DIV ASSIGNOP AND OR NOT IF ELSE WHILE RETURN FOR SWITCH CASE COLON DEFAULT
//+ - * / = & | ! if else return for switch case colon default
%token LB RB DPLUS DMINUS EXP_DPLUS EXP_DMINUS DPLUS_EXP DMINUS_EXP PLUS_ASSIGNOP MINUS_ASSIGNOP STAR_ASSIGNOP DIV_ASSIGNOP ARRAY_DEF ARRAY_READ BREAK CONTINUE FOR_DEC  DOT STRUCT STRUCT_READ 
// [ ]  ++exp exp++ --exp exp-- += -= *= /=

/*以下为接在上述token后依次编码的枚举常量，作为AST结点类型标记*/
%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF FUNC_DEC EXT_DEC_LIST PARAM_LIST PARAM_DEC VAR_DEF DEC_LIST DEF_LIST COMP_STM STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE STRUCTNAME STRUCT_DEF STRUCT_DEC
%token FUNC_CALL ARGS FUNCTION PARAM ARG CALL LABEL GOTO JLT JLE JGT JGE EQ NEQ

%right ASSIGNOP PLUS_ASSIGNOP MINUS_ASSIGNOP STAR_ASSIGNOP DIV_ASSIGNOP//= += -+ *= /= 
%left OR //||
%left AND // &&
%left RELOP // ">"|"<"|">="|"<="|"=="|"!=" 
%left PLUS MINUS //+ -
%left STAR DIV // * /
%right UMINUS NOT DPLUS DMINUS   //- ! ++ -- 
%right 	LB//(
%left 	RB//)
%left DOT
%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE
//下面的优先级更高

%%
//program: 初始语法单元
program: ExtDefList    { //display($1,0); 
                         semantic_Analysis0($1);
                        }     //显示语法树,语义分析
         ; 
//ExtDefList: 零个或多个ExtDef
ExtDefList:                   {$$=NULL;}
          | ExtDef ExtDefList {$$=mknode(2,EXT_DEF_LIST,yylineno,$1,$2);}   //每一个EXTDEFLIST的结点，其第1棵子树对应一个外部变量声明或函数
          ;  
//ExtDef: 一个全局变量、结构体或函数的定义
ExtDef:   Specifier ExtDecList SEMI   {$$=mknode(2,EXT_VAR_DEF,yylineno,$1,$2);}   //该结点对应一个外部变量声明
         |Specifier SEMI {$$=$1;} //对应只有声明没有变量名的情况
         |Specifier FuncDec CompSt    {$$=mknode(3,FUNC_DEF,yylineno,$1,$2,$3);}         //该结点对应一个函数定义
         | error SEMI   {$$=NULL;}
         ;
//StructSpecifier: 结构体描述符
StructSpecifier: STRUCT StructName LC DefList RC {$$=mknode(2,STRUCT_DEF,yylineno,$2,$4);}//定义结构体
                |STRUCT ID {$$=mknode(1,STRUCT_DEC,yylineno,$2);strcpy($$->type_id,$2);}//定义结构体变量
                ;
//StructName: 结构体名
StructName:     {$$=NULL;}
           | ID {$$=mknode(0,STRUCTNAME,yylineno);strcpy($$->type_id,$1);}
           ;
//Specifier: 类型描述符
Specifier:  TYPE    {$$=mknode(0,TYPE,yylineno);strcpy($$->type_id,$1);
                        if(!strcmp($1,"int")) $$->type=INT;
                        if(!strcmp($1,"float")) $$->type=FLOAT;
                        if(!strcmp($1,"char")) $$->type=CHAR;
                        if(!strcmp($1,"string")) $$->type=STRING;}
        |StructSpecifier  {$$=$1;} 
        ;      
//ExtDecList: 零个或多个VarDec
ExtDecList:  VarDec      {$$=$1;}       /*每一个EXT_DECLIST的结点，其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
           | VarDec COMMA ExtDecList {$$=mknode(2,EXT_DEC_LIST,yylineno,$1,$3);}
           ;  
//VarDec: 一个变量的定义
VarDec:  ID          {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}   //ID结点，标识符符号串存放结点的type_id
         | VarDec LB Exp RB {$$=mknode(2,ARRAY_DEF,yylineno,$1,$3);} //任意维度的数组
         ;
//FuncDec: 函数头
FuncDec: ID LP VarList RP   {$$=mknode(1,FUNC_DEC,yylineno,$3);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
	|ID LP  RP   {$$=mknode(0,FUNC_DEC,yylineno);strcpy($$->type_id,$1);$$->ptr[0]=NULL;}//函数名存放在$$->type_id
        ;  
//VarList: 形参列表
VarList: ParamDec  {$$=mknode(1,PARAM_LIST,yylineno,$1);}
        | ParamDec COMMA  VarList  {$$=mknode(2,PARAM_LIST,yylineno,$1,$3);}
        ;
//ParamDec: 一个形参的定义
ParamDec: Specifier VarDec         {$$=mknode(2,PARAM_DEC,yylineno,$1,$2);}
         ;

//CompSt: 函数体、由花括号括起来的语句块, 即复合语句
CompSt: LC DefList StmList RC    {$$=mknode(2,COMP_STM,yylineno,$2,$3);}
       ;
//StmList: 语句列表
StmList:                {$$=NULL; }  
        | Stmt StmList  {$$=mknode(2,STM_LIST,yylineno,$1,$2);}
        ;
//Stmt: 一条语句
Stmt:  Exp SEMI    {$$=mknode(1,EXP_STMT,yylineno,$1);}
      | CompSt      {$$=$1;}      //复合语句结点直接最为语句结点，不再生成新的结点
      | RETURN Exp SEMI   {$$=mknode(1,RETURN,yylineno,$2);}
      | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   {$$=mknode(2,IF_THEN,yylineno,$3,$5);}
      | IF LP Exp RP Stmt ELSE Stmt   {$$=mknode(3,IF_THEN_ELSE,yylineno,$3,$5,$7);}
      | WHILE LP Exp RP Stmt {$$=mknode(2,WHILE,yylineno,$3,$5);}
      | BREAK SEMI {$$=mknode(0,BREAK,yylineno);strcpy($$->type_id,"BREAK");}
      | CONTINUE SEMI {$$=mknode(0,CONTINUE,yylineno);strcpy($$->type_id,"CONTINUE");}
      | FOR LP FORDEC RP Stmt {$$=mknode(2,FOR,yylineno,$3,$5);}
      /* | FOR LP Exp SEMI Exp SEMI Exp RP {$$=mknode(3,FOR,yylineno,$3,$5,$7);} */
      | SEMI {$$=NULL;}  //对应于只有Stmt为空句子的情况
      ;
//For 语句体
FORDEC: Exp SEMI Exp SEMI Exp {$$=mknode(3, FOR_DEC, yylineno, $1, $3, $5);}
        ;

//DefList: 变量定义列表
DefList:              {$$=NULL; }
        | Def DefList {$$=mknode(2,DEF_LIST,yylineno,$1,$2);}
        | error SEMI   {$$=NULL;}
        ;
//Def: 一条变量定义
Def:    Specifier DecList SEMI {$$=mknode(2,VAR_DEF,yylineno,$1,$2);}
        ;
//DecList:
DecList: Dec  {$$=mknode(1,DEC_LIST,yylineno,$1);}
       | Dec COMMA DecList  {$$=mknode(2,DEC_LIST,yylineno,$1,$3);}
        ;
//Dec:
Dec:     VarDec  {$$=$1;}
       | VarDec ASSIGNOP Exp  {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}
       ;
//Exp: 一个表达式
Exp:    Exp ASSIGNOP Exp {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}//$$结点type_id空置未用，正好存放运算符
      | Exp AND Exp   {$$=mknode(2,AND,yylineno,$1,$3);strcpy($$->type_id,"AND");}
      | Exp OR Exp    {$$=mknode(2,OR,yylineno,$1,$3);strcpy($$->type_id,"OR");}
      | Exp RELOP Exp {$$=mknode(2,RELOP,yylineno,$1,$3);strcpy($$->type_id,$2);}  //词法分析关系运算符号自身值保存在$2中
      | Exp PLUS Exp  {$$=mknode(2,PLUS,yylineno,$1,$3);strcpy($$->type_id,"PLUS");}
      | Exp MINUS Exp {$$=mknode(2,MINUS,yylineno,$1,$3);strcpy($$->type_id,"MINUS");}
      | Exp STAR Exp  {$$=mknode(2,STAR,yylineno,$1,$3);strcpy($$->type_id,"STAR");}
      | Exp DIV Exp   {$$=mknode(2,DIV,yylineno,$1,$3);strcpy($$->type_id,"DIV");}
      | Exp PLUS ASSIGNOP Exp {$$=mknode(2,PLUS_ASSIGNOP,yylineno,$1,$4);strcpy($$->type_id,"PLUS_ASSIGNOP");}
      | Exp MINUS ASSIGNOP Exp {$$=mknode(2,MINUS_ASSIGNOP,yylineno,$1,$4);strcpy($$->type_id,"MINUS_ASSIGNOP");}
      | Exp STAR ASSIGNOP Exp {$$=mknode(2,STAR_ASSIGNOP,yylineno,$1,$4);strcpy($$->type_id,"STAR_ASSIGNOP");}
      | Exp DIV ASSIGNOP Exp {$$=mknode(2,DIV_ASSIGNOP,yylineno,$1,$4);strcpy($$->type_id,"DIV_ASSIGNOP");}     
      | Exp DPLUS {$$=mknode(1,EXP_DPLUS,yylineno,$1);strcpy($$->type_id,"EXP_DPLUS");}
      | Exp DMINUS  {$$=mknode(1,EXP_DMINUS,yylineno,$1);strcpy($$->type_id,"EXP_DMINUS");}
      | DPLUS Exp {$$=mknode(1,DPLUS_EXP,yylineno,$2);strcpy($$->type_id,"DPLUS_EXP");}
      | DMINUS Exp {$$=mknode(1,DMINUS_EXP,yylineno,$2);strcpy($$->type_id,"DMINUS_EXP");}
      | LP Exp RP     {$$=$2;}
      | MINUS Exp %prec UMINUS   {$$=mknode(1,UMINUS,yylineno,$2);strcpy($$->type_id,"UMINUS");}
      | NOT Exp       {$$=mknode(1,NOT,yylineno,$2);strcpy($$->type_id,"NOT");}
      | ID LP Args RP {$$=mknode(1,FUNC_CALL,yylineno,$3);strcpy($$->type_id,$1);}
      | ID LP RP      {$$=mknode(0,FUNC_CALL,yylineno);strcpy($$->type_id,$1);}
      | ID            {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
      | INT           {$$=mknode(0,INT,yylineno);$$->type_int=$1;$$->type=INT;}
      | FLOAT         {$$=mknode(0,FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
      | CHAR          {$$=mknode(0,CHAR,yylineno);
                        if($1[0]=='\\'){$$->type_char[0]='\\';$$->type_char[1]=$1[1];$$->type=CHAR;}
                        else{$$->type_char[0]=$1[0];$$->type=CHAR;}}
      | STRING        {$$=mknode(0,STRING,yylineno);strcpy($$->type_string,$1);$$->type=STRING;}
      | Exp LB Exp RB {$$=mknode(2,ARRAY_READ,yylineno,$1,$3);}
      | Exp DOT ID    {$$=mknode(2,STRUCT_READ,yylineno,$1,$3);strcpy($$->type_id,$3);}
      ;
//Args: 实参列表
Args:    Exp COMMA Args    {$$=mknode(2,ARGS,yylineno,$1,$3);}
       | Exp               {$$=mknode(1,ARGS,yylineno,$1);}
       ;
       
%%

int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return -1;
	yylineno=1;
	yyparse();
	return 0;
	}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}

