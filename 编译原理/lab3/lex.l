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
	// int type_char[2];
	char type_char;
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
/* char   ('[A-Za-z0-9]') */
string 	(\".*\")

%%

{int}        {yylval.type_int=atoi(yytext); return INT;}
{float}      {yylval.type_float=atof(yytext); return FLOAT;}
{char}       {if(yytext[1]!='\\') 
				{yylval.type_char[0]=yytext[1];return CHAR;} 
			else
				{yylval.type_char[0] = '\\';
				yylval.type_char[0] = yytext[2];return CHAR;}}

{string}     {strcpy(yylval.type_string,yytext);return STRING;}

"int"        {strcpy(yylval.type_id,  yytext);return TYPE;}
"float"      {strcpy(yylval.type_id,  yytext);return TYPE;}
"char"       {strcpy(yylval.type_id,  yytext);return TYPE;}
"string"     {strcpy(yylval.type_id,  yytext);return TYPE;} 

"return"     {return RETURN;}
"if"         {return IF;}
"else"       {return ELSE;}
"while"      {return WHILE;}
"for"		 {return FOR; }
"struct"	 {return STRUCT;} 
"break"		 {return BREAK;} 
"continue"	 {return CONTINUE;}

{id}        {strcpy(yylval.type_id,yytext); return ID;/*由于关键字的形式也符合标识符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			{return SEMI;}
","			{return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);;return RELOP;}
"="			{return ASSIGNOP;}
"+"			{return PLUS;}
"-"			{return MINUS;}
"*"			{return STAR;}
"/"			{return DIV;}
"++"		{return DPLUS;}
"--"		{return DMINUS;}
"&&"        {return AND;}
"||"        {return OR;}    
"!"			{return NOT;}
"("			{return LP;}
")"			{return RP;}
"{"			{return LC;}  
"}"			{return RC;}
"["         {return LB;}
"]"         {return RB;}
"."			{return DOT;}
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

