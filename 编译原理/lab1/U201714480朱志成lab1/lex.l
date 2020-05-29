%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
#include<stdio.h>

int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
	//其中first_line和first_column表示该语法单元第一个单词出现的行号和列号，last_line和last_column表示该语法单元最后一个单词出现的行号和列号
typedef union {
	int type_int;
	int type_float;
	int type_char[2];
	char type_string[31];
	char type_id[32];
	struct node *ptr;
} YYLVAL;
//yylval用来保存单词属性
#define YYSTYPE YYLVAL

%}
%option yylineno

/* regex defination */
id   [A-Za-z][A-Za-z0-9]*
int    ([1-9][0-9]*)|(0)
float  ([0-9]*\.[0-9]+)|([0-9]+\.)
char  (\'.\')|(\'\\.\')
string 	(\".*\")

%%
{int}        {printf("(%s,INT)\n",yytext);yylval.type_int=atoi(yytext); return INT;}
{float}      {printf("(%s,FLOAT)\n",yytext);yylval.type_float=atof(yytext); return FLOAT;}
{char}       {if(yytext[1]!='\\') 
				{printf("(%c,CHAR)\n",yytext[1]);yylval.type_char[0]=yytext[1];return CHAR;} 
			else
				{printf("(\\%c,CHAR)\n",yytext[1],yytext[2]); yylval.type_char[0]='\\';
				yylval.type_char[1]=yytext[2];return CHAR;}}
{string}     {printf("(%s,STRING)\n",yytext);strcpy(yylval.type_string,yytext);return STRING;}

"int"        {printf("(int,TYPE)\n"); strcpy(yylval.type_id,  yytext);return TYPE;}
"float"      {printf("(float,TYPE)\n");strcpy(yylval.type_id,  yytext);return TYPE;}
"char"       {printf("(char,TYPE)\n");strcpy(yylval.type_id,  yytext);return TYPE;}
"string"     {printf("(int,TYPE)\n");strcpy(yylval.type_id,  yytext);return TYPE;} 

"return"     {printf("(%s,RETURN)\n",yytext);return RETURN;}
"if"         {printf("(%s,IF)\n",yytext);return IF;}
"else"       {printf("(%s,ELSE)\n",yytext);return ELSE;}
"while"      {printf("(%s,WHILE)\n",yytext);return WHILE;}
"for"		 {printf("(%s,FOR)\n",yytext);return FOR; }
"struct"	 {printf("(%s,STRUCT)\n",yytext);return STRUCT;} 
"break"		 {printf("(%s,BREAK)\n",yytext);return BREAK;} 
"continue"	 {printf("(%s,CONTINUE)\n",yytext);return CONTINUE;}

{id}        {printf("(%s,ID)\n",yytext);strcpy(yylval.type_id,yytext); return ID;/*由于关键字的形式也符合标识符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			{printf("(%s,SEMI)\n",yytext);return SEMI;}
","			{printf("(%s,COMMA)\n",yytext);return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {printf("(%s,RELOP)\n",yytext);strcpy(yylval.type_id, yytext);;return RELOP;}
"="			{printf("(%s,ASSIGNOP)\n",yytext);return ASSIGNOP;}
"+"			{printf("(%s,PLUS)\n",yytext);return PLUS;}
"-"			{printf("(%s,MINUS)\n",yytext);return MINUS;}
"*"			{printf("(%s,STAR)\n",yytext);return STAR;}
"/"			{printf("(%s,DIV)\n",yytext);return DIV;}
"++"		{printf("(%s,DPLUS)\n",yytext);return DPLUS;}
"--"		{printf("(%s,DMINUS)\n",yytext);return DMINUS;}
"&&"        {printf("(%s,AND)\n",yytext);return AND;}
"||"        {printf("(%s,OR)\n",yytext);return OR;}    
"!"			{printf("(%s,NOT)\n",yytext);return NOT;}
"("			{printf("(%s,LP)\n",yytext);return LP;}
")"			{printf("(%s,RP)\n",yytext);return RP;}
"{"			{printf("(%s,LC)\n",yytext);return LC;}  
"}"			{printf("(%s,RC)\n",yytext);return RC;}
"["         {printf("(%s,LB)\n",yytext);return LB;}
"]"         {printf("(%s,RB)\n",yytext);return RB;}
"."			{printf("(%s,DOT)\n",yytext);return DOT;}
[\n]           {yycolumn=1;}   
[ \r\t]          {}   
"//".* { }                       //单行注释  
"/*"(([^\*]*(\*[^\/])?)*)"*/" { } //多行注释

.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}

%%

// 和bison联用时，不需要这部分
// int main()
// {
// yylex();
// return 0;
// }

int yywrap()
{
return 1;
}

