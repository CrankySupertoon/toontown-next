/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         xyyparse
#define yylex           xyylex
#define yyerror         xyyerror
#define yylval          xyylval
#define yychar          xyychar
#define yydebug         xyydebug
#define yynerrs         xyynerrs

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 13 "pandatool/src/xfile/xParser.yxx"

#include "xLexerDefs.h"
#include "xParserDefs.h"
#include "xFile.h"
#include "xFileTemplate.h"
#include "xFileDataDef.h"
#include "xFileArrayDef.h"
#include "xFileDataNodeTemplate.h"
#include "xFileDataNodeReference.h"
#include "pointerTo.h"
#include "dcast.h"

// Because our token type contains objects of type string, which
// require correct copy construction (and not simply memcpying), we
// cannot use bison's built-in auto-stack-grow feature.  As an easy
// solution, we ensure here that we have enough yacc stack to start
// with, and that it doesn't ever try to grow.
#define YYINITDEPTH 1000
#define YYMAXDEPTH 1000

static XFile *x_file = (XFile *)NULL;
static XFileNode *current_node = (XFileNode *)NULL;
static PT(XFileDataDef) current_data_def = (XFileDataDef *)NULL;

////////////////////////////////////////////////////////////////////
// Defining the interface to the parser.
////////////////////////////////////////////////////////////////////

void
x_init_parser(istream &in, const string &filename, XFile &file) {
  x_file = &file;
  current_node = &file;
  x_init_lexer(in, filename);
}

void
x_cleanup_parser() {
  x_file = (XFile *)NULL;
  current_node = (XFileNode *)NULL;
}


/* Line 371 of yacc.c  */
#line 118 "built/tmp/xParser.yxx.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "xParser.yxx.h".  */
#ifndef YY_XYY_BUILT_TMP_XPARSER_YXX_H_INCLUDED
# define YY_XYY_BUILT_TMP_XPARSER_YXX_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int xyydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_NAME = 1,
     TOKEN_STRING = 2,
     TOKEN_INTEGER = 3,
     TOKEN_GUID = 5,
     TOKEN_INTEGER_LIST = 6,
     TOKEN_REALNUM_LIST = 7,
     TOKEN_OBRACE = 10,
     TOKEN_CBRACE = 11,
     TOKEN_OPAREN = 12,
     TOKEN_CPAREN = 13,
     TOKEN_OBRACKET = 14,
     TOKEN_CBRACKET = 15,
     TOKEN_OANGLE = 16,
     TOKEN_CANGLE = 17,
     TOKEN_DOT = 18,
     TOKEN_COMMA = 19,
     TOKEN_SEMICOLON = 20,
     TOKEN_TEMPLATE = 31,
     TOKEN_WORD = 40,
     TOKEN_DWORD = 41,
     TOKEN_FLOAT = 42,
     TOKEN_DOUBLE = 43,
     TOKEN_CHAR = 44,
     TOKEN_UCHAR = 45,
     TOKEN_SWORD = 46,
     TOKEN_SDWORD = 47,
     TOKEN_VOID = 48,
     TOKEN_LPSTR = 49,
     TOKEN_UNICODE = 50,
     TOKEN_CSTRING = 51,
     TOKEN_ARRAY = 52
   };
#endif
/* Tokens.  */
#define TOKEN_NAME 1
#define TOKEN_STRING 2
#define TOKEN_INTEGER 3
#define TOKEN_GUID 5
#define TOKEN_INTEGER_LIST 6
#define TOKEN_REALNUM_LIST 7
#define TOKEN_OBRACE 10
#define TOKEN_CBRACE 11
#define TOKEN_OPAREN 12
#define TOKEN_CPAREN 13
#define TOKEN_OBRACKET 14
#define TOKEN_CBRACKET 15
#define TOKEN_OANGLE 16
#define TOKEN_CANGLE 17
#define TOKEN_DOT 18
#define TOKEN_COMMA 19
#define TOKEN_SEMICOLON 20
#define TOKEN_TEMPLATE 31
#define TOKEN_WORD 40
#define TOKEN_DWORD 41
#define TOKEN_FLOAT 42
#define TOKEN_DOUBLE 43
#define TOKEN_CHAR 44
#define TOKEN_UCHAR 45
#define TOKEN_SWORD 46
#define TOKEN_SDWORD 47
#define TOKEN_VOID 48
#define TOKEN_LPSTR 49
#define TOKEN_UNICODE 50
#define TOKEN_CSTRING 51
#define TOKEN_ARRAY 52



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE xyylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int xyyparse (void *YYPARSE_PARAM);
#else
int xyyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int xyyparse (void);
#else
int xyyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_XYY_BUILT_TMP_XPARSER_YXX_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 249 "built/tmp/xParser.yxx.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   114

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  100

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   257

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     3,     4,     5,     2,     6,     7,     8,     2,     2,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    20,     2,     2,     2,     2,     2,     2,     2,     2,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    15,    23,    28,
      30,    32,    34,    36,    38,    40,    43,    45,    47,    49,
      53,    58,    62,    64,    66,    68,    70,    72,    74,    76,
      78,    80,    82,    84,    87,    90,    92,    95,    99,   101,
     103,   105,   108,   110,   113,   115,   117,   120,   123,   125,
     127,   129,   131,   133,   137,   138,   146,   148,   151,   155,
     157,   159,   161,   164,   166,   168,   170,   172,   174,   176,
     178,   181
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    68,    -1,    35,    36,    -1,    35,    59,
      -1,    35,    10,    -1,    -1,    20,    53,     9,    56,    37,
      38,    10,    -1,    39,    13,    40,    14,    -1,    41,    -1,
      68,    -1,    41,    -1,    58,    -1,    51,    -1,    42,    -1,
      41,    42,    -1,    43,    -1,    44,    -1,    45,    -1,    46,
      55,    19,    -1,    33,    47,    48,    19,    -1,    53,    55,
      19,    -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,
      25,    -1,    26,    -1,    27,    -1,    28,    -1,    30,    -1,
      31,    -1,    32,    -1,    46,    54,    -1,    53,    54,    -1,
      49,    -1,    48,    49,    -1,    13,    50,    14,    -1,     5,
      -1,    54,    -1,    52,    -1,    51,    52,    -1,    53,    -1,
      53,    56,    -1,     3,    -1,     3,    -1,    54,     3,    -1,
      54,     5,    -1,    68,    -1,    54,    -1,     6,    -1,    68,
      -1,    56,    -1,    17,    17,    17,    -1,    -1,    53,    55,
       9,    60,    57,    61,    10,    -1,    68,    -1,    61,    62,
      -1,     9,    67,    10,    -1,    59,    -1,    63,    -1,    64,
      -1,    65,    66,    -1,    66,    -1,     7,    -1,     8,    -1,
       4,    -1,    19,    -1,    18,    -1,    54,    -1,    54,    56,
      -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   109,   109,   110,   111,   112,   117,   116,   131,   132,
     136,   137,   141,   145,   149,   150,   154,   155,   156,   160,
     168,   172,   185,   189,   193,   197,   201,   205,   209,   213,
     217,   221,   225,   232,   237,   250,   251,   255,   259,   263,
     275,   278,   284,   293,   309,   313,   314,   318,   325,   329,
     333,   337,   341,   345,   350,   349,   377,   378,   382,   387,
     391,   399,   407,   415,   421,   425,   429,   433,   434,   438,
     447,   463
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_NAME", "TOKEN_STRING",
  "TOKEN_INTEGER", "TOKEN_GUID", "TOKEN_INTEGER_LIST",
  "TOKEN_REALNUM_LIST", "TOKEN_OBRACE", "TOKEN_CBRACE", "TOKEN_OPAREN",
  "TOKEN_CPAREN", "TOKEN_OBRACKET", "TOKEN_CBRACKET", "TOKEN_OANGLE",
  "TOKEN_CANGLE", "TOKEN_DOT", "TOKEN_COMMA", "TOKEN_SEMICOLON",
  "TOKEN_TEMPLATE", "TOKEN_WORD", "TOKEN_DWORD", "TOKEN_FLOAT",
  "TOKEN_DOUBLE", "TOKEN_CHAR", "TOKEN_UCHAR", "TOKEN_SWORD",
  "TOKEN_SDWORD", "TOKEN_VOID", "TOKEN_LPSTR", "TOKEN_UNICODE",
  "TOKEN_CSTRING", "TOKEN_ARRAY", "$accept", "xfile", "template", "@1",
  "template_parts", "template_members_part", "template_option_info",
  "template_members_list", "template_members", "primitive", "array",
  "template_reference", "primitive_type", "array_data_type",
  "dimension_list", "dimension", "dimension_size", "template_option_list",
  "template_option_part", "singleword_name", "multiword_name",
  "optional_multiword_name", "class_id", "optional_class_id", "ellipsis",
  "object", "@2", "data_parts_list", "data_part", "integer_list",
  "realnum_list", "string", "list_separator", "data_reference", "empty", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,     1,     2,     3,     5,     6,     7,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      31,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    35,    35,    35,    37,    36,    38,    38,
      39,    39,    40,    40,    41,    41,    42,    42,    42,    43,
      44,    45,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    47,    47,    48,    48,    49,    50,    50,
      51,    51,    52,    52,    53,    54,    54,    54,    55,    55,
      56,    57,    57,    58,    60,    59,    61,    61,    62,    62,
      62,    62,    62,    62,    63,    64,    65,    66,    66,    67,
      67,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     0,     7,     4,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     3,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     2,     3,     1,     1,
       1,     2,     1,     2,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     3,     0,     7,     1,     2,     3,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      71,     0,     2,     1,    44,     5,     0,     3,    71,     4,
       0,    45,    49,     0,    48,     0,    46,    47,    54,    50,
       6,    71,    71,    52,    71,    51,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,     0,     0,
       9,    14,    16,    17,    18,    71,    71,    10,     0,    56,
       0,     0,     0,     7,     0,    15,     0,     0,    66,    64,
      65,     0,    55,    68,    67,    59,    57,    60,    61,     0,
      63,    33,     0,     0,    35,    34,     0,     0,    13,    40,
      42,    12,    19,    21,    69,     0,    62,    38,     0,    39,
      20,    36,     0,     8,    41,    43,    70,    58,    37,    53
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     7,    22,    38,    39,    77,    40,    41,    42,
      43,    44,    45,    51,    73,    74,    88,    78,    79,     8,
      12,    13,    20,    24,    81,     9,    21,    48,    66,    67,
      68,    69,    70,    85,    14
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -48
static const yytype_int8 yypact[] =
{
     -48,     8,   -48,   -48,   -48,   -48,     9,   -48,    40,   -48,
      41,   -48,     4,    42,   -48,    43,   -48,   -48,   -48,   -48,
     -48,    43,    52,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   -48,   -48,   -48,   -48,    65,    44,    39,
      14,   -48,   -48,   -48,   -48,    40,    40,   -48,    95,   -48,
      40,    45,    40,   -48,     3,   -48,    34,    37,   -48,   -48,
     -48,    40,   -48,   -48,   -48,   -48,   -48,   -48,   -48,    11,
     -48,     4,    10,    -9,   -48,     4,    46,    47,     9,   -48,
      43,   -48,   -48,   -48,    16,    49,   -48,   -48,    48,     4,
     -48,   -48,    50,   -48,   -48,   -48,   -48,   -48,   -48,   -48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,    17,   -48,
     -48,   -48,    28,   -48,   -48,    -7,   -48,   -48,    -8,    -6,
     -47,   -13,   -20,   -48,   -48,    21,   -48,   -48,   -48,   -48,
     -48,   -48,    12,   -48,     2
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -12
static const yytype_int8 yytable[] =
{
      10,    23,     2,    71,    72,    75,     4,    16,     3,    17,
      90,     4,     4,    11,    84,    87,    46,     4,     5,    16,
      76,    17,    19,    25,    47,    89,    49,   -11,     6,    63,
      64,    52,    56,    57,    46,    26,    27,    28,    29,    30,
      31,    32,    33,    11,    34,    35,    36,    37,    80,    19,
      15,    18,    54,    82,    53,     4,    83,    55,    72,    97,
      95,    93,    98,    92,    96,    50,    91,    99,     4,    65,
      94,     0,    80,    26,    27,    28,    29,    30,    31,    32,
      33,    86,    34,    35,    36,    37,    26,    27,    28,    29,
      30,    31,    32,    33,     0,    34,    35,    36,     4,    58,
       0,     0,    59,    60,    61,    62,     0,     0,     0,     0,
       0,     0,     0,    63,    64
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-48)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       6,    21,     0,    50,    13,    52,     3,     3,     0,     5,
      19,     3,     3,     3,    61,     5,    22,     3,    10,     3,
      17,     5,     6,    21,    22,    72,    24,    13,    20,    18,
      19,    37,    45,    46,    40,    21,    22,    23,    24,    25,
      26,    27,    28,     3,    30,    31,    32,    33,    54,     6,
       9,     9,    13,    19,    10,     3,    19,    40,    13,    10,
      80,    14,    14,    17,    84,    37,    73,    17,     3,    48,
      78,    -1,    78,    21,    22,    23,    24,    25,    26,    27,
      28,    69,    30,    31,    32,    33,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    30,    31,    32,     3,     4,
      -1,    -1,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    19
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    35,    68,     0,     3,    10,    20,    36,    53,    59,
      53,     3,    54,    55,    68,     9,     3,     5,     9,     6,
      56,    60,    37,    56,    57,    68,    21,    22,    23,    24,
      25,    26,    27,    28,    30,    31,    32,    33,    38,    39,
      41,    42,    43,    44,    45,    46,    53,    68,    61,    68,
      46,    47,    53,    10,    13,    42,    55,    55,     4,     7,
       8,     9,    10,    18,    19,    59,    62,    63,    64,    65,
      66,    54,    13,    48,    49,    54,    17,    40,    51,    52,
      53,    58,    19,    19,    54,    67,    66,     5,    50,    54,
      19,    49,    17,    14,    52,    56,    56,    10,    14,    17
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:
/* Line 1792 of yacc.c  */
#line 117 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.node) = current_node;
  XFileTemplate *templ = new XFileTemplate(x_file, (yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].guid));
  current_node->add_child(templ);
  current_node = templ;
}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 124 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.node) = current_node;
  current_node = (yyvsp[(5) - (7)].u.node);
}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 142 "pandatool/src/xfile/xParser.yxx"
    {
  DCAST(XFileTemplate, current_node)->set_open(true);
}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 161 "pandatool/src/xfile/xParser.yxx"
    {
  current_data_def = new XFileDataDef(x_file, (yyvsp[(2) - (3)].str), (yyvsp[(1) - (3)].u.primitive_type));
  current_node->add_child(current_data_def);
}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 173 "pandatool/src/xfile/xParser.yxx"
    {
  XFileTemplate *xtemplate = x_file->find_template((yyvsp[(1) - (3)].str));
  if (xtemplate == (XFileTemplate *)NULL) {
    yyerror("Unknown template: " + (yyvsp[(1) - (3)].str));
  } else {
    current_data_def = new XFileDataDef(x_file, (yyvsp[(2) - (3)].str), XFileDataDef::T_template, xtemplate);
    current_node->add_child(current_data_def);
  }
}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 186 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_word;
}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 190 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_dword;
}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 194 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_float;
}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 198 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_double;
}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 202 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_char;
}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 206 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_uchar;
}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 210 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_sword;
}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 214 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_sdword;
}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 218 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_string;
}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 222 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_unicode;
}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 226 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.u.primitive_type) = XFileDataDef::T_cstring;
}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 233 "pandatool/src/xfile/xParser.yxx"
    {
  current_data_def = new XFileDataDef(x_file, (yyvsp[(2) - (2)].str), (yyvsp[(1) - (2)].u.primitive_type));
  current_node->add_child(current_data_def);
}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 238 "pandatool/src/xfile/xParser.yxx"
    {
  XFileTemplate *xtemplate = x_file->find_template((yyvsp[(1) - (2)].str));
  if (xtemplate == (XFileTemplate *)NULL) {
    yyerror("Unknown template: " + (yyvsp[(1) - (2)].str));
  } else {
    current_data_def = new XFileDataDef(x_file, (yyvsp[(2) - (2)].str), XFileDataDef::T_template, xtemplate);
    current_node->add_child(current_data_def);
  }
}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 260 "pandatool/src/xfile/xParser.yxx"
    {
  current_data_def->add_array_def(XFileArrayDef((yyvsp[(1) - (1)].u.number)));
}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 264 "pandatool/src/xfile/xParser.yxx"
    {
  XFileNode *data_def = current_node->find_child((yyvsp[(1) - (1)].str));
  if (data_def == (XFileNode *)NULL) {
    yyerror("Unknown identifier: " + (yyvsp[(1) - (1)].str));
  } else {
    current_data_def->add_array_def(XFileArrayDef(DCAST(XFileDataDef, data_def)));
  }
}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 276 "pandatool/src/xfile/xParser.yxx"
    {
}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 279 "pandatool/src/xfile/xParser.yxx"
    {
}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 285 "pandatool/src/xfile/xParser.yxx"
    {
  XFileTemplate *xtemplate = x_file->find_template((yyvsp[(1) - (1)].str));
  if (xtemplate == (XFileTemplate *)NULL) {
    yyerror("Unknown template: " + (yyvsp[(1) - (1)].str));
  } else {
    DCAST(XFileTemplate, current_node)->add_option(xtemplate);
  }
}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 294 "pandatool/src/xfile/xParser.yxx"
    {
  XFileTemplate *xtemplate = x_file->find_template((yyvsp[(2) - (2)].guid));
  if (xtemplate == (XFileTemplate *)NULL) {
    yyerror("Unknown template: " + (yyvsp[(1) - (2)].str));
  } else {
    if (xtemplate->get_name() != (yyvsp[(1) - (2)].str)) {
      xyywarning("GUID identifies template " + xtemplate->get_name() +
                 ", not " + (yyvsp[(1) - (2)].str));
    }
    DCAST(XFileTemplate, current_node)->add_option(xtemplate);
  }
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 315 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.str) = (yyvsp[(1) - (2)].str) + " " + (yyvsp[(2) - (2)].str);
}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 319 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.str) = (yyvsp[(1) - (2)].str) + " " + (yyvsp[(2) - (2)].str);
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 326 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.str) = string();
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 338 "pandatool/src/xfile/xParser.yxx"
    {
  (yyval.guid) = WindowsGuid();
}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 350 "pandatool/src/xfile/xParser.yxx"
    {
  XFileTemplate *xtemplate = x_file->find_template((yyvsp[(1) - (3)].str));
  (yyval.u.node) = current_node;
  
  if (xtemplate == (XFileTemplate *)NULL) {
    yyerror("Unknown template: " + (yyvsp[(1) - (3)].str));
  } else {
    XFileDataNodeTemplate *templ = 
      new XFileDataNodeTemplate(x_file, (yyvsp[(2) - (3)].str), xtemplate);
    current_node->add_child(templ);
    current_node = templ;
  }
}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 364 "pandatool/src/xfile/xParser.yxx"
    {
  if (current_node->is_exact_type(XFileDataNodeTemplate::get_class_type())) {
    XFileDataNodeTemplate *current_template = 
      DCAST(XFileDataNodeTemplate, current_node);
    current_template->finalize_parse_data();
  }

  (yyval.u.node) = current_node;
  current_node = (yyvsp[(4) - (7)].u.node);
}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 383 "pandatool/src/xfile/xParser.yxx"
    {
  // nested references should be added as children too.
  current_node->add_child((yyvsp[(2) - (3)].u.node));
}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 388 "pandatool/src/xfile/xParser.yxx"
    {
  // nested objects are just quietly added as children.
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 392 "pandatool/src/xfile/xParser.yxx"
    {
  if (current_node->is_exact_type(XFileDataNodeTemplate::get_class_type())) {
    XFileDataNodeTemplate *current_template = 
      DCAST(XFileDataNodeTemplate, current_node);
    current_template->add_parse_int((yyvsp[(1) - (1)].int_list));
  }
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 400 "pandatool/src/xfile/xParser.yxx"
    {
  if (current_node->is_exact_type(XFileDataNodeTemplate::get_class_type())) {
    XFileDataNodeTemplate *current_template = 
      DCAST(XFileDataNodeTemplate, current_node);
    current_template->add_parse_double((yyvsp[(1) - (1)].double_list));
  }
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 408 "pandatool/src/xfile/xParser.yxx"
    {
  if (current_node->is_exact_type(XFileDataNodeTemplate::get_class_type())) {
    XFileDataNodeTemplate *current_template = 
      DCAST(XFileDataNodeTemplate, current_node);
    current_template->add_parse_string((yyvsp[(1) - (2)].str));
  }
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 416 "pandatool/src/xfile/xParser.yxx"
    {
}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 439 "pandatool/src/xfile/xParser.yxx"
    {
  XFileDataNodeTemplate *data_object = x_file->find_data_object((yyvsp[(1) - (1)].str));
  if (data_object == (XFileDataObject *)NULL) {
    yyerror("Unknown data_object: " + (yyvsp[(1) - (1)].str));
  }

  (yyval.u.node) = new XFileDataNodeReference(data_object);
}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 448 "pandatool/src/xfile/xParser.yxx"
    {
  XFileDataNodeTemplate *data_object = x_file->find_data_object((yyvsp[(2) - (2)].guid));
  if (data_object == (XFileDataObject *)NULL) {
    yyerror("Unknown data_object: " + (yyvsp[(1) - (2)].str));
  } else {
    if (data_object->get_name() != (yyvsp[(1) - (2)].str)) {
      xyywarning("GUID identifies data_object " + data_object->get_name() +
                 ", not " + (yyvsp[(1) - (2)].str));
    }
  }

  (yyval.u.node) = new XFileDataNodeReference(data_object);
}
    break;


/* Line 1792 of yacc.c  */
#line 1926 "built/tmp/xParser.yxx.c"
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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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


