
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     ID = 259,
     RELOP = 260,
     TYPE = 261,
     FLOAT = 262,
     CHAR = 263,
     STRING = 264,
     LP = 265,
     RP = 266,
     LC = 267,
     RC = 268,
     SEMI = 269,
     COMMA = 270,
     PLUS = 271,
     MINUS = 272,
     STAR = 273,
     DIV = 274,
     ASSIGNOP = 275,
     AND = 276,
     OR = 277,
     NOT = 278,
     IF = 279,
     ELSE = 280,
     WHILE = 281,
     RETURN = 282,
     FOR = 283,
     SWITCH = 284,
     CASE = 285,
     COLON = 286,
     DEFAULT = 287,
     LB = 288,
     RB = 289,
     DPLUS = 290,
     DMINUS = 291,
     EXP_DPLUS = 292,
     EXP_DMINUS = 293,
     DPLUS_EXP = 294,
     DMINUS_EXP = 295,
     PLUS_ASSIGNOP = 296,
     MINUS_ASSIGNOP = 297,
     STAR_ASSIGNOP = 298,
     DIV_ASSIGNOP = 299,
     ARRAY_DEF = 300,
     ARRAY_READ = 301,
     BREAK = 302,
     CONTINUE = 303,
     DOT = 304,
     STRUCT = 305,
     STRUCT_READ = 306,
     EXT_DEF_LIST = 307,
     EXT_VAR_DEF = 308,
     FUNC_DEF = 309,
     FUNC_DEC = 310,
     EXT_DEC_LIST = 311,
     PARAM_LIST = 312,
     PARAM_DEC = 313,
     VAR_DEF = 314,
     DEC_LIST = 315,
     DEF_LIST = 316,
     COMP_STM = 317,
     STM_LIST = 318,
     EXP_STMT = 319,
     IF_THEN = 320,
     IF_THEN_ELSE = 321,
     STRUCTNAME = 322,
     STRUCT_DEF = 323,
     STRUCT_DEC = 324,
     FUNC_CALL = 325,
     ARGS = 326,
     FUNCTION = 327,
     PARAM = 328,
     ARG = 329,
     CALL = 330,
     LABEL = 331,
     GOTO = 332,
     JLT = 333,
     JLE = 334,
     JGT = 335,
     JGE = 336,
     EQ = 337,
     NEQ = 338,
     UMINUS = 339,
     LOWER_THEN_ELSE = 340
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 16 "parser.y"

	int    type_int;
	float  type_float;
        char   type_char[2];
        char   type_string[31];
	char   type_id[32];
	struct ASTNode *ptr;



/* Line 1676 of yacc.c  */
#line 148 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

