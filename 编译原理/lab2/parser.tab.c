/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "parser.y" /* yacc.c:339  */

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"

extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct ASTNode *,int);

#line 79 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "parser.y" /* yacc.c:355  */

	int    type_int;
	float  type_float;
        char   type_char[2];
        char   type_string[31];
	char   type_id[32];
	struct ASTNode *ptr;

#line 214 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 245 "parser.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   603

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      85
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    62,    62,    67,    68,    71,    72,    73,    74,    77,
      78,    81,    82,    85,    90,    93,    94,    97,    98,   101,
     102,   105,   106,   109,   113,   116,   117,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   132,   133,   134,
     137,   140,   141,   144,   145,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     175,   176,   177,   180,   181
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
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
  "DIV_ASSIGNOP", "ARRAY_DEF", "ARRAY_READ", "BREAK", "CONTINUE", "DOT",
  "STRUCT", "STRUCT_READ", "EXT_DEF_LIST", "EXT_VAR_DEF", "FUNC_DEF",
  "FUNC_DEC", "EXT_DEC_LIST", "PARAM_LIST", "PARAM_DEC", "VAR_DEF",
  "DEC_LIST", "DEF_LIST", "COMP_STM", "STM_LIST", "EXP_STMT", "IF_THEN",
  "IF_THEN_ELSE", "STRUCTNAME", "STRUCT_DEF", "STRUCT_DEC", "FUNC_CALL",
  "ARGS", "FUNCTION", "PARAM", "ARG", "CALL", "LABEL", "GOTO", "JLT",
  "JLE", "JGT", "JGE", "EQ", "NEQ", "UMINUS", "LOWER_THEN_ELSE", "$accept",
  "program", "ExtDefList", "ExtDef", "StructSpecifier", "StructName",
  "Specifier", "ExtDecList", "VarDec", "FuncDec", "VarList", "ParamDec",
  "CompSt", "StmList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp",
  "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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
     335,   336,   337,   338,   339,   340
};
# endif

#define YYPACT_NINF -104

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-104)))

#define YYTABLE_NINF -38

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,   -10,  -104,    21,    27,  -104,     7,  -104,     2,  -104,
      -1,    24,  -104,  -104,    22,  -104,    19,    -5,    25,    11,
      20,  -104,    35,   546,    95,  -104,    48,    35,    58,    95,
    -104,    35,    61,    59,  -104,  -104,  -104,    66,  -104,  -104,
    -104,   546,   546,   546,   546,   546,    33,   143,  -104,   -18,
      69,    70,  -104,  -104,    51,  -104,     8,   445,   176,    45,
      45,    45,    45,   546,   462,   483,   504,   525,   546,   546,
     546,   546,  -104,  -104,  -104,    84,  -104,    80,    81,   546,
      82,    79,    86,  -104,    93,   143,   199,   546,  -104,    35,
    -104,  -104,   221,    99,  -104,   554,   546,   140,   546,   140,
     546,    45,   546,    45,   377,   411,   402,   242,  -104,   546,
     546,   266,   546,  -104,  -104,  -104,  -104,  -104,   377,  -104,
     546,  -104,   377,   377,   377,   377,  -104,   287,   308,  -104,
     332,  -104,   143,   143,   546,    88,  -104,   342,   143,   546,
    -104,   368,  -104
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    13,    11,     0,     2,     0,    14,     0,     8,
      10,     0,     1,     4,    17,     6,     0,    15,     0,     0,
       0,     5,     0,     0,     0,     7,     0,     0,     0,     0,
      20,     0,     0,    21,    17,    16,    67,    66,    68,    69,
      70,     0,     0,     0,     0,     0,     0,    25,    39,    43,
       0,    41,     9,    38,    23,    19,     0,     0,     0,    62,
      63,    59,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,    57,    58,     0,    36,     0,     0,     0,
       0,     0,     0,    28,     0,    25,     0,     0,    40,     0,
      22,    65,    74,     0,    61,    48,     0,    49,     0,    50,
       0,    51,     0,    52,    45,    46,    47,     0,    72,     0,
       0,     0,     0,    33,    34,    24,    26,    27,    44,    42,
       0,    64,    53,    54,    55,    56,    71,     0,     0,    29,
       0,    73,     0,     0,     0,    30,    32,     0,     0,     0,
      31,     0,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,  -104,    89,  -104,  -104,  -104,     3,    92,   -26,  -104,
      64,  -104,    97,    32,  -103,    36,  -104,    37,  -104,   -23,
       4
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    11,    27,    16,    17,    18,
      32,    33,    83,    84,    85,    28,    29,    50,    51,    86,
      93
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    49,    87,     8,     9,    54,    14,    -3,     1,     8,
      22,   -12,    26,     2,     2,    23,    15,     2,    58,    59,
      60,    61,    62,    31,   -37,    10,     2,    12,    23,   135,
     136,    30,    20,    21,    92,   140,    19,    24,    63,    34,
      95,    97,    99,   101,   103,   104,   105,   106,   107,    64,
      65,    66,    67,    68,    69,    70,   111,     3,     3,    31,
      47,     3,    48,    49,   118,    53,    71,    72,    73,    74,
       3,    52,    55,   122,    56,   123,    57,   124,    71,   125,
      73,    74,    75,    88,    23,    89,   127,   128,   108,   130,
     109,   110,   112,   113,    75,    13,    26,    92,   -37,   -37,
     114,     2,   -37,   -37,   -37,   -37,   115,   -37,   -37,   -37,
     121,   137,   -37,   138,    35,    25,   141,   116,   -37,   -37,
      90,   -37,   -37,   -37,   131,     0,   119,     0,     0,     0,
     -37,   -37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -37,   -37,     0,     3,    36,    37,     0,     0,
      38,    39,    40,    41,     0,    24,     0,    76,    66,    67,
      42,     0,     0,     0,     0,     0,    43,    77,     0,    78,
      79,    80,     0,    71,     0,    73,    74,     0,    44,    45,
       0,    63,     0,     0,     0,     0,     0,    94,     0,    75,
      81,    82,    64,    65,    66,    67,    68,    69,    70,     0,
       0,     0,     0,     0,    63,     0,     0,     0,     0,    71,
       0,    73,    74,   117,     0,    64,    65,    66,    67,    68,
      69,    70,     0,     0,     0,    75,    63,     0,     0,     0,
       0,     0,    71,     0,    73,    74,   120,    64,    65,    66,
      67,    68,    69,    70,     0,     0,     0,    63,    75,     0,
       0,     0,     0,     0,    71,     0,    73,    74,    64,    65,
      66,    67,    68,    69,    70,     0,     0,     0,     0,     0,
      75,    63,     0,     0,     0,    71,   126,    73,    74,     0,
     129,     0,    64,    65,    66,    67,    68,    69,    70,     0,
       0,    75,    63,     0,     0,     0,     0,     0,   132,    71,
       0,    73,    74,    64,    65,    66,    67,    68,    69,    70,
       0,     0,     0,    63,     0,    75,     0,     0,     0,   133,
      71,     0,    73,    74,    64,    65,    66,    67,    68,    69,
      70,     0,     0,     0,     0,     0,    75,    63,     0,     0,
       0,    71,     0,    73,    74,     0,   134,    63,    64,    65,
      66,    67,    68,    69,    70,     0,   139,    75,    64,    65,
      66,    67,    68,    69,    70,    71,     0,    73,    74,     0,
       0,     0,     0,    63,     0,    71,     0,    73,    74,   142,
       0,    75,    63,     0,    64,    65,    66,    67,    68,    69,
      70,    75,     0,    64,    65,    66,    67,    68,    69,    70,
       0,    71,     0,    73,    74,     0,     0,    63,     0,     0,
      71,     0,    73,    74,     0,     0,    63,    75,    64,    65,
      66,    67,     0,    69,     0,     0,    75,    64,    65,    66,
      67,     0,     0,     0,     0,    71,     0,    73,    74,     0,
       0,     0,     0,     0,    71,     0,    73,    74,    36,    37,
       0,    75,    38,    39,    40,    41,    91,     0,     0,     0,
      75,     0,    42,     0,     0,    36,    37,     0,    43,    38,
      39,    40,    41,     0,     0,     0,     0,     0,     0,    42,
      44,    45,    96,     0,     0,    43,    36,    37,     0,     0,
      38,    39,    40,    41,     0,     0,     0,    44,    45,     0,
      42,     0,     0,    98,     0,     0,    43,    36,    37,     0,
       0,    38,    39,    40,    41,     0,     0,     0,    44,    45,
       0,    42,     0,     0,   100,     0,     0,    43,    36,    37,
       0,     0,    38,    39,    40,    41,     0,     0,     0,    44,
      45,     0,    42,     0,     0,   102,     0,     0,    43,    36,
      37,     0,     0,    38,    39,    40,    41,     0,     0,     0,
      44,    45,     0,    42,     0,     0,     0,     0,     0,    43,
      64,    65,    66,    67,     0,     0,     0,     0,     0,     0,
       0,    44,    45,     0,     0,     0,     0,    71,     0,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    75
};

static const yytype_int16 yycheck[] =
{
      23,    27,    20,     0,    14,    31,     4,     0,     1,     6,
      15,    12,     1,     6,     6,    33,    14,     6,    41,    42,
      43,    44,    45,    20,    13,     4,     6,     0,    33,   132,
     133,    11,    10,    14,    57,   138,    12,    12,     5,     4,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    16,
      17,    18,    19,    20,    21,    22,    79,    50,    50,    56,
      24,    50,    14,    89,    87,    29,    33,    34,    35,    36,
      50,    13,    11,    96,    15,    98,    10,   100,    33,   102,
      35,    36,    49,    14,    33,    15,   109,   110,     4,   112,
      10,    10,    10,    14,    49,     6,     1,   120,     3,     4,
      14,     6,     7,     8,     9,    10,    13,    12,    13,    14,
      11,   134,    17,    25,    22,    18,   139,    85,    23,    24,
      56,    26,    27,    28,   120,    -1,    89,    -1,    -1,    -1,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    50,     3,     4,    -1,    -1,
       7,     8,     9,    10,    -1,    12,    -1,    14,    18,    19,
      17,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    33,    -1,    35,    36,    -1,    35,    36,
      -1,     5,    -1,    -1,    -1,    -1,    -1,    11,    -1,    49,
      47,    48,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    33,
      -1,    35,    36,    14,    -1,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    49,     5,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    35,    36,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,     5,    49,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    35,    36,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      49,     5,    -1,    -1,    -1,    33,    34,    35,    36,    -1,
      14,    -1,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    49,     5,    -1,    -1,    -1,    -1,    -1,    11,    33,
      -1,    35,    36,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    -1,     5,    -1,    49,    -1,    -1,    -1,    11,
      33,    -1,    35,    36,    16,    17,    18,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    49,     5,    -1,    -1,
      -1,    33,    -1,    35,    36,    -1,    14,     5,    16,    17,
      18,    19,    20,    21,    22,    -1,    14,    49,    16,    17,
      18,    19,    20,    21,    22,    33,    -1,    35,    36,    -1,
      -1,    -1,    -1,     5,    -1,    33,    -1,    35,    36,    11,
      -1,    49,     5,    -1,    16,    17,    18,    19,    20,    21,
      22,    49,    -1,    16,    17,    18,    19,    20,    21,    22,
      -1,    33,    -1,    35,    36,    -1,    -1,     5,    -1,    -1,
      33,    -1,    35,    36,    -1,    -1,     5,    49,    16,    17,
      18,    19,    -1,    21,    -1,    -1,    49,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    35,    36,     3,     4,
      -1,    49,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      49,    -1,    17,    -1,    -1,     3,     4,    -1,    23,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      35,    36,    20,    -1,    -1,    23,     3,     4,    -1,    -1,
       7,     8,     9,    10,    -1,    -1,    -1,    35,    36,    -1,
      17,    -1,    -1,    20,    -1,    -1,    23,     3,     4,    -1,
      -1,     7,     8,     9,    10,    -1,    -1,    -1,    35,    36,
      -1,    17,    -1,    -1,    20,    -1,    -1,    23,     3,     4,
      -1,    -1,     7,     8,     9,    10,    -1,    -1,    -1,    35,
      36,    -1,    17,    -1,    -1,    20,    -1,    -1,    23,     3,
       4,    -1,    -1,     7,     8,     9,    10,    -1,    -1,    -1,
      35,    36,    -1,    17,    -1,    -1,    -1,    -1,    -1,    23,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    -1,    -1,    -1,    -1,    33,    -1,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    50,    87,    88,    89,    90,    92,    14,
       4,    91,     0,    88,     4,    14,    93,    94,    95,    12,
      10,    14,    15,    33,    12,    98,     1,    92,   101,   102,
      11,    92,    96,    97,     4,    93,     3,     4,     7,     8,
       9,    10,    17,    23,    35,    36,   105,   101,    14,    94,
     103,   104,    13,   101,    94,    11,    15,    10,   105,   105,
     105,   105,   105,     5,    16,    17,    18,    19,    20,    21,
      22,    33,    34,    35,    36,    49,    14,    24,    26,    27,
      28,    47,    48,    98,    99,   100,   105,    20,    14,    15,
      96,    11,   105,   106,    11,   105,    20,   105,    20,   105,
      20,   105,    20,   105,   105,   105,   105,   105,     4,    10,
      10,   105,    10,    14,    14,    13,    99,    14,   105,   103,
      15,    11,   105,   105,   105,   105,    34,   105,   105,    14,
     105,   106,    11,    11,    14,   100,   100,   105,    25,    14,
     100,   105,    11
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    88,    88,    89,    89,    89,    89,    90,
      90,    91,    91,    92,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    97,    98,    99,    99,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   101,   101,   101,
     102,   103,   103,   104,   104,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   106,   106
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     2,     5,
       2,     0,     1,     1,     1,     1,     3,     1,     4,     4,
       3,     1,     3,     2,     4,     0,     2,     2,     1,     3,
       5,     7,     5,     2,     2,     8,     1,     0,     2,     2,
       3,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     4,     4,     2,     2,     2,
       2,     3,     2,     2,     4,     3,     1,     1,     1,     1,
       1,     4,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
     '$$ = $1'.

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
#line 62 "parser.y" /* yacc.c:1646  */
    { //display($1,0); 
                         semantic_Analysis0((yyvsp[0].ptr));
                        }
#line 1626 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 67 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1632 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 68 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,EXT_DEF_LIST,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1638 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 71 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,EXT_VAR_DEF,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 1644 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 72 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[-1].ptr);}
#line 1650 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 73 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(3,FUNC_DEF,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 74 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1662 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 77 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,STRUCT_DEF,yylineno,(yyvsp[-3].ptr),(yyvsp[-1].ptr));}
#line 1668 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 78 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,STRUCT_DEC,yylineno,(yyvsp[0].type_id));strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 1674 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 81 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1680 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 82 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,STRUCTNAME,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 1686 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 85 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,TYPE,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));
                        if(!strcmp((yyvsp[0].type_id),"int")) (yyval.ptr)->type=INT;
                        if(!strcmp((yyvsp[0].type_id),"float")) (yyval.ptr)->type=FLOAT;
                        if(!strcmp((yyvsp[0].type_id),"char")) (yyval.ptr)->type=CHAR;
                        if(!strcmp((yyvsp[0].type_id),"string")) (yyval.ptr)->type=STRING;}
#line 1696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 90 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 93 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1708 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 94 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,EXT_DEC_LIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1714 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 97 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 1720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 98 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,ARRAY_DEF,yylineno,(yyvsp[-3].ptr),(yyvsp[-1].ptr));}
#line 1726 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 101 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,FUNC_DEC,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-3].type_id));}
#line 1732 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 102 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,FUNC_DEC,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-2].type_id));(yyval.ptr)->ptr[0]=NULL;}
#line 1738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 105 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,PARAM_LIST,yylineno,(yyvsp[0].ptr));}
#line 1744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 106 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,PARAM_LIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1750 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 109 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,PARAM_DEC,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1756 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 113 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,COMP_STM,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 1762 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 116 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL; }
#line 1768 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 117 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,STM_LIST,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 120 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,EXP_STMT,yylineno,(yyvsp[-1].ptr));}
#line 1780 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 121 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1786 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 122 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,RETURN,yylineno,(yyvsp[-1].ptr));}
#line 1792 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 123 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,IF_THEN,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1798 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 124 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(3,IF_THEN_ELSE,yylineno,(yyvsp[-4].ptr),(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1804 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 125 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,WHILE,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1810 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 126 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,BREAK,yylineno);strcpy((yyval.ptr)->type_id,"BREAK");}
#line 1816 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 127 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,CONTINUE,yylineno);strcpy((yyval.ptr)->type_id,"CONTINUE");}
#line 1822 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 128 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(3,FOR,yylineno,(yyvsp[-5].ptr),(yyvsp[-3].ptr),(yyvsp[-1].ptr));}
#line 1828 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 129 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1834 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 132 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL; }
#line 1840 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 133 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,DEF_LIST,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1846 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 134 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1852 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 137 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,VAR_DEF,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 1858 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 140 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,DEC_LIST,yylineno,(yyvsp[0].ptr));}
#line 1864 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 141 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,DEC_LIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1870 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 144 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1876 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 145 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");}
#line 1882 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 148 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");}
#line 1888 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 149 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,AND,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"AND");}
#line 1894 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 150 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,OR,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"OR");}
#line 1900 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 151 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,RELOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));}
#line 1906 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 152 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,PLUS,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"PLUS");}
#line 1912 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 153 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,MINUS,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"MINUS");}
#line 1918 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 154 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,STAR,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"STAR");}
#line 1924 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 155 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,DIV,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"DIV");}
#line 1930 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 156 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,PLUS_ASSIGNOP,yylineno,(yyvsp[-3].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"PLUS_ASSIGNOP");}
#line 1936 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 157 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,MINUS_ASSIGNOP,yylineno,(yyvsp[-3].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"MINUS_ASSIGNOP");}
#line 1942 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 158 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,STAR_ASSIGNOP,yylineno,(yyvsp[-3].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"STAR_ASSIGNOP");}
#line 1948 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 159 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,DIV_ASSIGNOP,yylineno,(yyvsp[-3].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"DIV_ASSIGNOP");}
#line 1954 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 160 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,EXP_DPLUS,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,"EXP_DPLUS");}
#line 1960 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 161 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,EXP_DMINUS,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,"EXP_DMINUS");}
#line 1966 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 162 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,DPLUS_EXP,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"DPLUS_EXP");}
#line 1972 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 163 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,DMINUS_EXP,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"DMINUS_EXP");}
#line 1978 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 164 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[-1].ptr);}
#line 1984 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 165 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,UMINUS,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"UMINUS");}
#line 1990 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 166 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,NOT,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"NOT");}
#line 1996 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 167 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,FUNC_CALL,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-3].type_id));}
#line 2002 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 168 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,FUNC_CALL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-2].type_id));}
#line 2008 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 169 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 2014 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 170 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,INT,yylineno);(yyval.ptr)->type_int=(yyvsp[0].type_int);(yyval.ptr)->type=INT;}
#line 2020 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 171 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,FLOAT,yylineno);(yyval.ptr)->type_float=(yyvsp[0].type_float);(yyval.ptr)->type=FLOAT;}
#line 2026 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 172 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,CHAR,yylineno);
                        if((yyvsp[0].type_char)[0]=='\\'){(yyval.ptr)->type_char[0]='\\';(yyval.ptr)->type_char[1]=(yyvsp[0].type_char)[1];(yyval.ptr)->type=CHAR;}
                        else{(yyval.ptr)->type_char[0]=(yyvsp[0].type_char)[0];(yyval.ptr)->type=CHAR;}}
#line 2034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 175 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,STRING,yylineno);strcpy((yyval.ptr)->type_string,(yyvsp[0].type_string));(yyval.ptr)->type=STRING;}
#line 2040 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 176 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,ARRAY_READ,yylineno,(yyvsp[-3].ptr),(yyvsp[-1].ptr));}
#line 2046 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 177 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,STRUCT_READ,yylineno,(yyvsp[-2].ptr),(yyvsp[0].type_id));strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 2052 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 180 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,ARGS,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 2058 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 181 "parser.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,ARGS,yylineno,(yyvsp[0].ptr));}
#line 2064 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2068 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 184 "parser.y" /* yacc.c:1906  */


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

