/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 3 "parser.y"

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"

extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct ASTNode *,int);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 290 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 315 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   580

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNRULES -- Number of states.  */
#define YYNSTATES  145

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   341

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    16,    20,    23,
      29,    32,    33,    35,    37,    39,    41,    45,    47,    52,
      57,    61,    63,    67,    70,    75,    76,    79,    82,    84,
      88,    94,   102,   108,   111,   114,   120,   122,   128,   129,
     132,   135,   139,   141,   145,   147,   151,   155,   159,   163,
     167,   171,   175,   179,   183,   188,   193,   198,   203,   206,
     209,   212,   215,   219,   222,   225,   230,   234,   236,   238,
     240,   242,   244,   249,   253,   257
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      88,     0,    -1,    89,    -1,    -1,    90,    89,    -1,    93,
      94,    14,    -1,    93,    14,    -1,    93,    96,    99,    -1,
       1,    14,    -1,    51,    92,    12,   103,    13,    -1,    51,
       4,    -1,    -1,     4,    -1,     6,    -1,    91,    -1,    95,
      -1,    95,    15,    94,    -1,     4,    -1,    95,    33,   107,
      34,    -1,     4,    10,    97,    11,    -1,     4,    10,    11,
      -1,    98,    -1,    98,    15,    97,    -1,    93,    95,    -1,
      12,   103,   100,    13,    -1,    -1,   101,   100,    -1,   107,
      14,    -1,    99,    -1,    27,   107,    14,    -1,    24,    10,
     107,    11,   101,    -1,    24,    10,   107,    11,   101,    25,
     101,    -1,    26,    10,   107,    11,   101,    -1,    47,    14,
      -1,    48,    14,    -1,    28,    10,   102,    11,   101,    -1,
      14,    -1,   107,    14,   107,    14,   107,    -1,    -1,   104,
     103,    -1,     1,    14,    -1,    93,   105,    14,    -1,   106,
      -1,   106,    15,   105,    -1,    95,    -1,    95,    20,   107,
      -1,   107,    20,   107,    -1,   107,    21,   107,    -1,   107,
      22,   107,    -1,   107,     5,   107,    -1,   107,    16,   107,
      -1,   107,    17,   107,    -1,   107,    18,   107,    -1,   107,
      19,   107,    -1,   107,    16,    20,   107,    -1,   107,    17,
      20,   107,    -1,   107,    18,    20,   107,    -1,   107,    19,
      20,   107,    -1,   107,    35,    -1,   107,    36,    -1,    35,
     107,    -1,    36,   107,    -1,    10,   107,    11,    -1,    17,
     107,    -1,    23,   107,    -1,     4,    10,   108,    11,    -1,
       4,    10,    11,    -1,     4,    -1,     3,    -1,     7,    -1,
       8,    -1,     9,    -1,   107,    33,   107,    34,    -1,   107,
      50,     4,    -1,   107,    15,   108,    -1,   107,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    62,    62,    67,    68,    71,    72,    73,    74,    77,
      78,    81,    82,    85,    90,    93,    94,    97,    98,   101,
     102,   105,   106,   109,   113,   116,   117,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   130,   133,   137,   138,
     139,   142,   145,   146,   149,   150,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   180,   181,   182,   185,   186
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "RELOP", "TYPE", "FLOAT",
  "CHAR", "STRING", "LP", "RP", "LC", "RC", "SEMI", "COMMA", "PLUS",
  "MINUS", "STAR", "DIV", "ASSIGNOP", "AND", "OR", "NOT", "IF", "ELSE",
  "WHILE", "RETURN", "FOR", "SWITCH", "CASE", "COLON", "DEFAULT", "LB",
  "RB", "DPLUS", "DMINUS", "EXP_DPLUS", "EXP_DMINUS", "DPLUS_EXP",
  "DMINUS_EXP", "PLUS_ASSIGNOP", "MINUS_ASSIGNOP", "STAR_ASSIGNOP",
  "DIV_ASSIGNOP", "ARRAY_DEF", "ARRAY_READ", "BREAK", "CONTINUE",
  "FOR_DEC", "DOT", "STRUCT", "STRUCT_READ", "EXT_DEF_LIST", "EXT_VAR_DEF",
  "FUNC_DEF", "FUNC_DEC", "EXT_DEC_LIST", "PARAM_LIST", "PARAM_DEC",
  "VAR_DEF", "DEC_LIST", "DEF_LIST", "COMP_STM", "STM_LIST", "EXP_STMT",
  "IF_THEN", "IF_THEN_ELSE", "STRUCTNAME", "STRUCT_DEF", "STRUCT_DEC",
  "FUNC_CALL", "ARGS", "FUNCTION", "PARAM", "ARG", "CALL", "LABEL", "GOTO",
  "JLT", "JLE", "JGT", "JGE", "EQ", "NEQ", "UMINUS", "LOWER_THEN_ELSE",
  "$accept", "program", "ExtDefList", "ExtDef", "StructSpecifier",
  "StructName", "Specifier", "ExtDecList", "VarDec", "FuncDec", "VarList",
  "ParamDec", "CompSt", "StmList", "Stmt", "FORDEC", "DefList", "Def",
  "DecList", "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    89,    89,    90,    90,    90,    90,    91,
      91,    92,    92,    93,    93,    94,    94,    95,    95,    96,
      96,    97,    97,    98,    99,   100,   100,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   102,   103,   103,
     103,   104,   105,   105,   106,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     2,     5,
       2,     0,     1,     1,     1,     1,     3,     1,     4,     4,
       3,     1,     3,     2,     4,     0,     2,     2,     1,     3,
       5,     7,     5,     2,     2,     5,     1,     5,     0,     2,
       2,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     4,     4,     4,     2,     2,
       2,     2,     3,     2,     2,     4,     3,     1,     1,     1,
       1,     1,     4,     3,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    13,    11,     0,     2,     0,    14,     0,     8,
      10,     0,     1,     4,    17,     6,     0,    15,     0,     0,
       0,     5,     0,     0,     0,     7,     0,     0,     0,     0,
      20,     0,     0,    21,    17,    16,    68,    67,    69,    70,
      71,     0,     0,     0,     0,     0,     0,    25,    40,    44,
       0,    42,     9,    39,    23,    19,     0,     0,     0,    63,
      64,    60,    61,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,    58,    59,     0,    36,     0,     0,     0,
       0,     0,     0,    28,     0,    25,     0,     0,    41,     0,
      22,    66,    75,     0,    62,    49,     0,    50,     0,    51,
       0,    52,     0,    53,    46,    47,    48,     0,    73,     0,
       0,     0,     0,    33,    34,    24,    26,    27,    45,    43,
       0,    65,    54,    55,    56,    57,    72,     0,     0,    29,
       0,     0,    74,     0,     0,     0,     0,    30,    32,    35,
       0,     0,     0,    31,    37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    11,    27,    16,    17,    18,
      32,    33,    83,    84,    85,   130,    28,    29,    50,    51,
      86,    93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -54
static const yytype_int16 yypact[] =
{
       6,   -10,   -54,    28,    10,   -54,     6,   -54,    57,   -54,
      -1,    15,   -54,   -54,    25,   -54,    46,    -7,    27,    23,
      19,   -54,    58,   537,    97,   -54,    51,    58,    24,    97,
     -54,    58,    61,    63,   -54,   -54,   -54,    66,   -54,   -54,
     -54,   537,   537,   537,   537,   537,    33,   143,   -54,   -18,
      70,    75,   -54,   -54,    52,   -54,     7,   440,   176,   -19,
     -19,   -19,   -19,   537,   451,   474,   495,   516,   537,   537,
     537,   537,   -54,   -54,   -54,    87,   -54,    82,    83,   537,
      84,    81,    85,   -54,    89,   143,   199,   537,   -54,    58,
     -54,   -54,   222,   101,   -54,   402,   537,   530,   537,   530,
     537,   -19,   537,   -19,   375,   123,   396,   243,   -54,   537,
     537,   266,   537,   -54,   -54,   -54,   -54,   -54,   375,   -54,
     537,   -54,   375,   375,   375,   375,   -54,   287,   308,   -54,
     104,   331,   -54,   143,   143,   143,   537,    71,   -54,   -54,
     354,   143,   537,   -54,   375
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   102,   -54,   -54,   -54,     3,    94,   -26,   -54,
      62,   -54,    99,    37,   -53,   -54,     4,   -54,    38,   -54,
     -23,     9
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -39
static const yytype_int16 yytable[] =
{
      46,    49,    87,     8,     9,    54,    -3,     1,    22,     8,
      12,   -12,     2,     2,    71,    23,    73,    74,    58,    59,
      60,    61,    62,    31,    26,     2,    23,    19,    47,     2,
      30,    75,    10,    53,    92,    20,   -38,    52,    63,    24,
      95,    97,    99,   101,   103,   104,   105,   106,   107,    64,
      65,    66,    67,    68,    69,    70,   111,     3,     3,    31,
      21,    14,    34,    49,   118,    48,    71,    72,    73,    74,
       3,    15,    55,   122,     3,   123,    57,   124,    56,   125,
     137,   138,   139,    75,    88,    23,   127,   128,   143,   131,
      89,   108,   109,   110,   112,   113,   141,    92,    26,   114,
     -38,   -38,   115,     2,   -38,   -38,   -38,   -38,    13,   -38,
     -38,   -38,   121,   140,   -38,   135,    35,    25,    90,   144,
     -38,   -38,   116,   -38,   -38,   -38,     0,   119,    63,   132,
       0,     0,   -38,   -38,     0,     0,     0,     0,     0,    64,
      65,    66,    67,     0,   -38,   -38,    36,    37,     3,     0,
      38,    39,    40,    41,     0,    24,    71,    76,    73,    74,
      42,     0,     0,     0,     0,     0,    43,    77,     0,    78,
      79,    80,     0,    75,     0,     0,     0,     0,    44,    45,
       0,    63,     0,     0,     0,     0,     0,    94,     0,     0,
      81,    82,    64,    65,    66,    67,    68,    69,    70,     0,
       0,     0,     0,     0,    63,     0,     0,     0,     0,    71,
       0,    73,    74,   117,     0,    64,    65,    66,    67,    68,
      69,    70,     0,     0,     0,     0,    75,    63,     0,     0,
       0,     0,    71,     0,    73,    74,     0,   120,    64,    65,
      66,    67,    68,    69,    70,     0,     0,     0,    63,    75,
       0,     0,     0,     0,     0,    71,     0,    73,    74,    64,
      65,    66,    67,    68,    69,    70,     0,     0,     0,     0,
       0,    63,    75,     0,     0,     0,    71,   126,    73,    74,
     129,     0,    64,    65,    66,    67,    68,    69,    70,     0,
       0,     0,    63,    75,     0,     0,     0,     0,   133,    71,
       0,    73,    74,    64,    65,    66,    67,    68,    69,    70,
       0,     0,     0,    63,     0,     0,    75,     0,     0,   134,
      71,     0,    73,    74,    64,    65,    66,    67,    68,    69,
      70,     0,     0,     0,     0,     0,    63,    75,     0,     0,
       0,    71,     0,    73,    74,   136,     0,    64,    65,    66,
      67,    68,    69,    70,     0,     0,     0,     0,    75,    63,
       0,     0,     0,     0,    71,     0,    73,    74,   142,     0,
      64,    65,    66,    67,    68,    69,    70,     0,     0,     0,
      63,    75,     0,     0,     0,     0,     0,    71,     0,    73,
      74,    64,    65,    66,    67,    68,    69,    70,     0,     0,
       0,    63,     0,     0,    75,     0,     0,     0,    71,     0,
      73,    74,    64,    65,    66,    67,     0,    69,    64,    65,
      66,    67,     0,     0,     0,    75,     0,     0,     0,    71,
       0,    73,    74,     0,     0,    71,     0,    73,    74,     0,
       0,     0,     0,    36,    37,     0,    75,    38,    39,    40,
      41,    91,    75,     0,    36,    37,     0,    42,    38,    39,
      40,    41,     0,    43,     0,     0,     0,     0,    42,     0,
       0,    96,     0,     0,    43,    44,    45,    36,    37,     0,
       0,    38,    39,    40,    41,     0,    44,    45,     0,     0,
       0,    42,     0,     0,    98,     0,     0,    43,    36,    37,
       0,     0,    38,    39,    40,    41,     0,     0,     0,    44,
      45,     0,    42,     0,     0,   100,     0,     0,    43,    36,
      37,     0,     0,    38,    39,    40,    41,     0,     0,     0,
      44,    45,     0,    42,     0,     0,   102,     0,     0,    43,
      36,    37,     0,     0,    38,    39,    40,    41,    66,    67,
       0,    44,    45,     0,    42,     0,     0,     0,     0,     0,
      43,     0,     0,    71,     0,    73,    74,     0,     0,     0,
       0,     0,    44,    45,     0,     0,     0,     0,     0,     0,
      75
};

static const yytype_int16 yycheck[] =
{
      23,    27,    20,     0,    14,    31,     0,     1,    15,     6,
       0,    12,     6,     6,    33,    33,    35,    36,    41,    42,
      43,    44,    45,    20,     1,     6,    33,    12,    24,     6,
      11,    50,     4,    29,    57,    10,    13,    13,     5,    12,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    16,
      17,    18,    19,    20,    21,    22,    79,    51,    51,    56,
      14,     4,     4,    89,    87,    14,    33,    34,    35,    36,
      51,    14,    11,    96,    51,    98,    10,   100,    15,   102,
     133,   134,   135,    50,    14,    33,   109,   110,   141,   112,
      15,     4,    10,    10,    10,    14,    25,   120,     1,    14,
       3,     4,    13,     6,     7,     8,     9,    10,     6,    12,
      13,    14,    11,   136,    17,    11,    22,    18,    56,   142,
      23,    24,    85,    26,    27,    28,    -1,    89,     5,   120,
      -1,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    16,
      17,    18,    19,    -1,    47,    48,     3,     4,    51,    -1,
       7,     8,     9,    10,    -1,    12,    33,    14,    35,    36,
      17,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    50,    -1,    -1,    -1,    -1,    35,    36,
      -1,     5,    -1,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      47,    48,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    33,
      -1,    35,    36,    14,    -1,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    50,     5,    -1,    -1,
      -1,    -1,    33,    -1,    35,    36,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,     5,    50,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,     5,    50,    -1,    -1,    -1,    33,    34,    35,    36,
      14,    -1,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,     5,    50,    -1,    -1,    -1,    -1,    11,    33,
      -1,    35,    36,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    -1,     5,    -1,    -1,    50,    -1,    -1,    11,
      33,    -1,    35,    36,    16,    17,    18,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,     5,    50,    -1,    -1,
      -1,    33,    -1,    35,    36,    14,    -1,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    50,     5,
      -1,    -1,    -1,    -1,    33,    -1,    35,    36,    14,    -1,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
       5,    50,    -1,    -1,    -1,    -1,    -1,    33,    -1,    35,
      36,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,     5,    -1,    -1,    50,    -1,    -1,    -1,    33,    -1,
      35,    36,    16,    17,    18,    19,    -1,    21,    16,    17,
      18,    19,    -1,    -1,    -1,    50,    -1,    -1,    -1,    33,
      -1,    35,    36,    -1,    -1,    33,    -1,    35,    36,    -1,
      -1,    -1,    -1,     3,     4,    -1,    50,     7,     8,     9,
      10,    11,    50,    -1,     3,     4,    -1,    17,     7,     8,
       9,    10,    -1,    23,    -1,    -1,    -1,    -1,    17,    -1,
      -1,    20,    -1,    -1,    23,    35,    36,     3,     4,    -1,
      -1,     7,     8,     9,    10,    -1,    35,    36,    -1,    -1,
      -1,    17,    -1,    -1,    20,    -1,    -1,    23,     3,     4,
      -1,    -1,     7,     8,     9,    10,    -1,    -1,    -1,    35,
      36,    -1,    17,    -1,    -1,    20,    -1,    -1,    23,     3,
       4,    -1,    -1,     7,     8,     9,    10,    -1,    -1,    -1,
      35,    36,    -1,    17,    -1,    -1,    20,    -1,    -1,    23,
       3,     4,    -1,    -1,     7,     8,     9,    10,    18,    19,
      -1,    35,    36,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    33,    -1,    35,    36,    -1,    -1,    -1,
      -1,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    51,    88,    89,    90,    91,    93,    14,
       4,    92,     0,    89,     4,    14,    94,    95,    96,    12,
      10,    14,    15,    33,    12,    99,     1,    93,   103,   104,
      11,    93,    97,    98,     4,    94,     3,     4,     7,     8,
       9,    10,    17,    23,    35,    36,   107,   103,    14,    95,
     105,   106,    13,   103,    95,    11,    15,    10,   107,   107,
     107,   107,   107,     5,    16,    17,    18,    19,    20,    21,
      22,    33,    34,    35,    36,    50,    14,    24,    26,    27,
      28,    47,    48,    99,   100,   101,   107,    20,    14,    15,
      97,    11,   107,   108,    11,   107,    20,   107,    20,   107,
      20,   107,    20,   107,   107,   107,   107,   107,     4,    10,
      10,   107,    10,    14,    14,    13,   100,    14,   107,   105,
      15,    11,   107,   107,   107,   107,    34,   107,   107,    14,
     102,   107,   108,    11,    11,    11,    14,   101,   101,   101,
     107,    25,    14,   101,   107
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 62 "parser.y"
    { //display($1,0); 
                         semantic_Analysis0((yyvsp[(1) - (1)].ptr));
                        ;}
    break;

  case 3:
#line 67 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 4:
#line 68 "parser.y"
    {(yyval.ptr)=mknode(2,EXT_DEF_LIST,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 5:
#line 71 "parser.y"
    {(yyval.ptr)=mknode(2,EXT_VAR_DEF,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr));;}
    break;

  case 6:
#line 72 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (2)].ptr);;}
    break;

  case 7:
#line 73 "parser.y"
    {(yyval.ptr)=mknode(3,FUNC_DEF,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 8:
#line 74 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 9:
#line 77 "parser.y"
    {(yyval.ptr)=mknode(2,STRUCT_DEF,yylineno,(yyvsp[(2) - (5)].ptr),(yyvsp[(4) - (5)].ptr));;}
    break;

  case 10:
#line 78 "parser.y"
    {(yyval.ptr)=mknode(1,STRUCT_DEC,yylineno,(yyvsp[(2) - (2)].type_id));strcpy((yyval.ptr)->type_id,(yyvsp[(2) - (2)].type_id));;}
    break;

  case 11:
#line 81 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 12:
#line 82 "parser.y"
    {(yyval.ptr)=mknode(0,STRUCTNAME,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 13:
#line 85 "parser.y"
    {(yyval.ptr)=mknode(0,TYPE,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));
                        if(!strcmp((yyvsp[(1) - (1)].type_id),"int")) (yyval.ptr)->type=INT;
                        if(!strcmp((yyvsp[(1) - (1)].type_id),"float")) (yyval.ptr)->type=FLOAT;
                        if(!strcmp((yyvsp[(1) - (1)].type_id),"char")) (yyval.ptr)->type=CHAR;
                        if(!strcmp((yyvsp[(1) - (1)].type_id),"string")) (yyval.ptr)->type=STRING;;}
    break;

  case 14:
#line 90 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 15:
#line 93 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 16:
#line 94 "parser.y"
    {(yyval.ptr)=mknode(2,EXT_DEC_LIST,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 17:
#line 97 "parser.y"
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 18:
#line 98 "parser.y"
    {(yyval.ptr)=mknode(2,ARRAY_DEF,yylineno,(yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr));;}
    break;

  case 19:
#line 101 "parser.y"
    {(yyval.ptr)=mknode(1,FUNC_DEC,yylineno,(yyvsp[(3) - (4)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id));;}
    break;

  case 20:
#line 102 "parser.y"
    {(yyval.ptr)=mknode(0,FUNC_DEC,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id));(yyval.ptr)->ptr[0]=NULL;;}
    break;

  case 21:
#line 105 "parser.y"
    {(yyval.ptr)=mknode(1,PARAM_LIST,yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;

  case 22:
#line 106 "parser.y"
    {(yyval.ptr)=mknode(2,PARAM_LIST,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 23:
#line 109 "parser.y"
    {(yyval.ptr)=mknode(2,PARAM_DEC,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 24:
#line 113 "parser.y"
    {(yyval.ptr)=mknode(2,COMP_STM,yylineno,(yyvsp[(2) - (4)].ptr),(yyvsp[(3) - (4)].ptr));;}
    break;

  case 25:
#line 116 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 26:
#line 117 "parser.y"
    {(yyval.ptr)=mknode(2,STM_LIST,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 27:
#line 120 "parser.y"
    {(yyval.ptr)=mknode(1,EXP_STMT,yylineno,(yyvsp[(1) - (2)].ptr));;}
    break;

  case 28:
#line 121 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 29:
#line 122 "parser.y"
    {(yyval.ptr)=mknode(1,RETURN,yylineno,(yyvsp[(2) - (3)].ptr));;}
    break;

  case 30:
#line 123 "parser.y"
    {(yyval.ptr)=mknode(2,IF_THEN,yylineno,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 31:
#line 124 "parser.y"
    {(yyval.ptr)=mknode(3,IF_THEN_ELSE,yylineno,(yyvsp[(3) - (7)].ptr),(yyvsp[(5) - (7)].ptr),(yyvsp[(7) - (7)].ptr));;}
    break;

  case 32:
#line 125 "parser.y"
    {(yyval.ptr)=mknode(2,WHILE,yylineno,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 33:
#line 126 "parser.y"
    {(yyval.ptr)=mknode(0,BREAK,yylineno);strcpy((yyval.ptr)->type_id,"BREAK");;}
    break;

  case 34:
#line 127 "parser.y"
    {(yyval.ptr)=mknode(0,CONTINUE,yylineno);strcpy((yyval.ptr)->type_id,"CONTINUE");;}
    break;

  case 35:
#line 128 "parser.y"
    {(yyval.ptr)=mknode(2,FOR,yylineno,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 36:
#line 130 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 37:
#line 133 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DEC, yylineno, (yyvsp[(1) - (5)].ptr), (yyvsp[(3) - (5)].ptr), (yyvsp[(5) - (5)].ptr));;}
    break;

  case 38:
#line 137 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 39:
#line 138 "parser.y"
    {(yyval.ptr)=mknode(2,DEF_LIST,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 40:
#line 139 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 41:
#line 142 "parser.y"
    {(yyval.ptr)=mknode(2,VAR_DEF,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr));;}
    break;

  case 42:
#line 145 "parser.y"
    {(yyval.ptr)=mknode(1,DEC_LIST,yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;

  case 43:
#line 146 "parser.y"
    {(yyval.ptr)=mknode(2,DEC_LIST,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 44:
#line 149 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 45:
#line 150 "parser.y"
    {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");;}
    break;

  case 46:
#line 153 "parser.y"
    {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");;}
    break;

  case 47:
#line 154 "parser.y"
    {(yyval.ptr)=mknode(2,AND,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"AND");;}
    break;

  case 48:
#line 155 "parser.y"
    {(yyval.ptr)=mknode(2,OR,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"OR");;}
    break;

  case 49:
#line 156 "parser.y"
    {(yyval.ptr)=mknode(2,RELOP,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(2) - (3)].type_id));;}
    break;

  case 50:
#line 157 "parser.y"
    {(yyval.ptr)=mknode(2,PLUS,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"PLUS");;}
    break;

  case 51:
#line 158 "parser.y"
    {(yyval.ptr)=mknode(2,MINUS,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"MINUS");;}
    break;

  case 52:
#line 159 "parser.y"
    {(yyval.ptr)=mknode(2,STAR,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"STAR");;}
    break;

  case 53:
#line 160 "parser.y"
    {(yyval.ptr)=mknode(2,DIV,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"DIV");;}
    break;

  case 54:
#line 161 "parser.y"
    {(yyval.ptr)=mknode(2,PLUS_ASSIGNOP,yylineno,(yyvsp[(1) - (4)].ptr),(yyvsp[(4) - (4)].ptr));strcpy((yyval.ptr)->type_id,"PLUS_ASSIGNOP");;}
    break;

  case 55:
#line 162 "parser.y"
    {(yyval.ptr)=mknode(2,MINUS_ASSIGNOP,yylineno,(yyvsp[(1) - (4)].ptr),(yyvsp[(4) - (4)].ptr));strcpy((yyval.ptr)->type_id,"MINUS_ASSIGNOP");;}
    break;

  case 56:
#line 163 "parser.y"
    {(yyval.ptr)=mknode(2,STAR_ASSIGNOP,yylineno,(yyvsp[(1) - (4)].ptr),(yyvsp[(4) - (4)].ptr));strcpy((yyval.ptr)->type_id,"STAR_ASSIGNOP");;}
    break;

  case 57:
#line 164 "parser.y"
    {(yyval.ptr)=mknode(2,DIV_ASSIGNOP,yylineno,(yyvsp[(1) - (4)].ptr),(yyvsp[(4) - (4)].ptr));strcpy((yyval.ptr)->type_id,"DIV_ASSIGNOP");;}
    break;

  case 58:
#line 165 "parser.y"
    {(yyval.ptr)=mknode(1,EXP_DPLUS,yylineno,(yyvsp[(1) - (2)].ptr));strcpy((yyval.ptr)->type_id,"EXP_DPLUS");;}
    break;

  case 59:
#line 166 "parser.y"
    {(yyval.ptr)=mknode(1,EXP_DMINUS,yylineno,(yyvsp[(1) - (2)].ptr));strcpy((yyval.ptr)->type_id,"EXP_DMINUS");;}
    break;

  case 60:
#line 167 "parser.y"
    {(yyval.ptr)=mknode(1,DPLUS_EXP,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"DPLUS_EXP");;}
    break;

  case 61:
#line 168 "parser.y"
    {(yyval.ptr)=mknode(1,DMINUS_EXP,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"DMINUS_EXP");;}
    break;

  case 62:
#line 169 "parser.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr);;}
    break;

  case 63:
#line 170 "parser.y"
    {(yyval.ptr)=mknode(1,UMINUS,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"UMINUS");;}
    break;

  case 64:
#line 171 "parser.y"
    {(yyval.ptr)=mknode(1,NOT,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"NOT");;}
    break;

  case 65:
#line 172 "parser.y"
    {(yyval.ptr)=mknode(1,FUNC_CALL,yylineno,(yyvsp[(3) - (4)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id));;}
    break;

  case 66:
#line 173 "parser.y"
    {(yyval.ptr)=mknode(0,FUNC_CALL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id));;}
    break;

  case 67:
#line 174 "parser.y"
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 68:
#line 175 "parser.y"
    {(yyval.ptr)=mknode(0,INT,yylineno);(yyval.ptr)->type_int=(yyvsp[(1) - (1)].type_int);(yyval.ptr)->type=INT;;}
    break;

  case 69:
#line 176 "parser.y"
    {(yyval.ptr)=mknode(0,FLOAT,yylineno);(yyval.ptr)->type_float=(yyvsp[(1) - (1)].type_float);(yyval.ptr)->type=FLOAT;;}
    break;

  case 70:
#line 177 "parser.y"
    {(yyval.ptr)=mknode(0,CHAR,yylineno);
                        if((yyvsp[(1) - (1)].type_char)[0]=='\\'){(yyval.ptr)->type_char[0]='\\';(yyval.ptr)->type_char[1]=(yyvsp[(1) - (1)].type_char)[1];(yyval.ptr)->type=CHAR;}
                        else{(yyval.ptr)->type_char[0]=(yyvsp[(1) - (1)].type_char)[0];(yyval.ptr)->type=CHAR;};}
    break;

  case 71:
#line 180 "parser.y"
    {(yyval.ptr)=mknode(0,STRING,yylineno);strcpy((yyval.ptr)->type_string,(yyvsp[(1) - (1)].type_string));(yyval.ptr)->type=STRING;;}
    break;

  case 72:
#line 181 "parser.y"
    {(yyval.ptr)=mknode(2,ARRAY_READ,yylineno,(yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr));;}
    break;

  case 73:
#line 182 "parser.y"
    {(yyval.ptr)=mknode(2,STRUCT_READ,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].type_id));strcpy((yyval.ptr)->type_id,(yyvsp[(3) - (3)].type_id));;}
    break;

  case 74:
#line 185 "parser.y"
    {(yyval.ptr)=mknode(2,ARGS,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 75:
#line 186 "parser.y"
    {(yyval.ptr)=mknode(1,ARGS,yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;


/* Line 1267 of yacc.c.  */
#line 2143 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 189 "parser.y"


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


