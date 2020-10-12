/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     FOR_DEC = 304,
     DOT = 305,
     STRUCT = 306,
     STRUCT_READ = 307,
     EXT_DEF_LIST = 308,
     EXT_VAR_DEF = 309,
     FUNC_DEF = 310,
     FUNC_DEC = 311,
     EXT_DEC_LIST = 312,
     PARAM_LIST = 313,
     PARAM_DEC = 314,
     VAR_DEF = 315,
     DEC_LIST = 316,
     DEF_LIST = 317,
     COMP_STM = 318,
     STM_LIST = 319,
     EXP_STMT = 320,
     IF_THEN = 321,
     IF_THEN_ELSE = 322,
     STRUCTNAME = 323,
     STRUCT_DEF = 324,
     STRUCT_DEC = 325,
     FUNC_CALL = 326,
     ARGS = 327,
     FUNCTION = 328,
     PARAM = 329,
     ARG = 330,
     CALL = 331,
     LABEL = 332,
     GOTO = 333,
     JLT = 334,
     JLE = 335,
     JGT = 336,
     JGE = 337,
     EQ = 338,
     NEQ = 339,
     UMINUS = 340,
     LOWER_THEN_ELSE = 341
   };
#endif
/* Tokens.  */
#define INT 258
#define ID 259
#define RELOP 260
#define TYPE 261
#define FLOAT 262
#define CHAR 263
#define STRING 264
#define LP 265
#define RP 266
#define LC 267
#define RC 268
#define SEMI 269
#define COMMA 270
#define PLUS 271
#define MINUS 272
#define STAR 273
#define DIV 274
#define ASSIGNOP 275
#define AND 276
#define OR 277
#define NOT 278
#define IF 279
#define ELSE 280
#define WHILE 281
#define RETURN 282
#define FOR 283
#define SWITCH 284
#define CASE 285
#define COLON 286
#define DEFAULT 287
#define LB 288
#define RB 289
#define DPLUS 290
#define DMINUS 291
#define EXP_DPLUS 292
#define EXP_DMINUS 293
#define DPLUS_EXP 294
#define DMINUS_EXP 295
#define PLUS_ASSIGNOP 296
#define MINUS_ASSIGNOP 297
#define STAR_ASSIGNOP 298
#define DIV_ASSIGNOP 299
#define ARRAY_DEF 300
#define ARRAY_READ 301
#define BREAK 302
#define CONTINUE 303
#define FOR_DEC 304
#define DOT 305
#define STRUCT 306
#define STRUCT_READ 307
#define EXT_DEF_LIST 308
#define EXT_VAR_DEF 309
#define FUNC_DEF 310
#define FUNC_DEC 311
#define EXT_DEC_LIST 312
#define PARAM_LIST 313
#define PARAM_DEC 314
#define VAR_DEF 315
#define DEC_LIST 316
#define DEF_LIST 317
#define COMP_STM 318
#define STM_LIST 319
#define EXP_STMT 320
#define IF_THEN 321
#define IF_THEN_ELSE 322
#define STRUCTNAME 323
#define STRUCT_DEF 324
#define STRUCT_DEC 325
#define FUNC_CALL 326
#define ARGS 327
#define FUNCTION 328
#define PARAM 329
#define ARG 330
#define CALL 331
#define LABEL 332
#define GOTO 333
#define JLT 334
#define JLE 335
#define JGT 336
#define JGE 337
#define EQ 338
#define NEQ 339
#define UMINUS 340
#define LOWER_THEN_ELSE 341




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "parser.y"
{
	int    type_int;
	float  type_float;
        char   type_char[2];
        char   type_string[31];
	char   type_id[32];
	struct ASTNode *ptr;
}
/* Line 1529 of yacc.c.  */
#line 230 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
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
