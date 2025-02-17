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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         cppyyparse
#define yylex           cppyylex
#define yyerror         cppyyerror
#define yylval          cppyylval
#define yychar          cppyychar
#define yydebug         cppyydebug
#define yynerrs         cppyynerrs
#define yylloc          cppyylloc

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 7 "dtool/src/cppparser/cppBison.yxx"


#include "cppBisonDefs.h"
#include "cppParser.h"
#include "cppExpression.h"
#include "cppSimpleType.h"
#include "cppExtensionType.h"
#include "cppStructType.h"
#include "cppEnumType.h"
#include "cppFunctionType.h"
#include "cppTBDType.h"
#include "cppMakeProperty.h"
#include "cppMakeSeq.h"
#include "cppParameterList.h"
#include "cppInstance.h"
#include "cppClassTemplateParameter.h"
#include "cppTemplateParameterList.h"
#include "cppInstanceIdentifier.h"
#include "cppTypedefType.h"
#include "cppTypeDeclaration.h"
#include "cppVisibility.h"
#include "cppIdentifier.h"
#include "cppScope.h"
#include "cppTemplateScope.h"
#include "cppNamespace.h"
#include "cppUsing.h"

////////////////////////////////////////////////////////////////////
// Defining the interface to the parser.
////////////////////////////////////////////////////////////////////

CPPScope *current_scope = NULL;
CPPScope *global_scope = NULL;
CPPPreprocessor *current_lexer = NULL;

static CPPStructType *current_struct = NULL;
static CPPEnumType *current_enum = NULL;
static int current_storage_class = 0;
static CPPType *current_type = NULL;
static CPPExpression *current_expr = NULL;
static int publish_nest_level = 0;
static CPPVisibility publish_previous;
static YYLTYPE publish_loc;

static vector<CPPScope *> last_scopes;
static vector<int> last_storage_classes;
static vector<CPPStructType *> last_structs;

int yyparse();

#define YYERROR_VERBOSE

static void
yyerror(const string &msg) {
  current_lexer->error(msg, current_lexer->_last_token_loc);
}

static void
yyerror(YYLTYPE *loc, const string &msg) {
  current_lexer->error(msg, *loc);
}

static void
yyerror(const string &msg, YYLTYPE &loc) {
  current_lexer->error(msg, loc);
}

static void
yywarning(const string &msg, YYLTYPE &loc) {
  current_lexer->warning(msg, loc);
}

static int
yylex(YYSTYPE *lval, YYLTYPE *lloc) {
  CPPToken token = current_lexer->get_next_token();
  *lval = token._lval;
  *lloc = token._lloc;
  return token._token;
}

void
parse_cpp(CPPParser *cp) {
  CPPScope *old_scope = current_scope;
  CPPScope *old_global_scope = global_scope;
  CPPPreprocessor *old_lexer = current_lexer;

  current_scope = cp;
  global_scope = cp;
  current_lexer = cp;
  publish_nest_level = 0;
  yyparse();

  if (publish_nest_level != 0) {
    yyerror("Unclosed __begin_publish", publish_loc);
    publish_nest_level = 0;
  }

  current_scope = old_scope;
  global_scope = old_global_scope;
  current_lexer = old_lexer;

}

CPPExpression *
parse_const_expr(CPPPreprocessor *pp, CPPScope *new_current_scope,
                 CPPScope *new_global_scope) {
  CPPScope *old_scope = current_scope;
  CPPScope *old_global_scope = global_scope;
  CPPPreprocessor *old_lexer = current_lexer;
  CPPExpression *old_expr = current_expr;

  current_scope = new_current_scope;
  global_scope = new_global_scope;
  current_expr = (CPPExpression *)NULL;
  current_lexer = pp;
  yyparse();

  CPPExpression *result = current_expr;

  current_scope = old_scope;
  global_scope = old_global_scope;
  current_lexer = old_lexer;
  current_expr = old_expr;

  return result;
}

CPPType *
parse_type(CPPPreprocessor *pp, CPPScope *new_current_scope,
           CPPScope *new_global_scope) {
  CPPScope *old_scope = current_scope;
  CPPScope *old_global_scope = global_scope;
  CPPPreprocessor *old_lexer = current_lexer;
  CPPType *old_type = current_type;

  current_scope = new_current_scope;
  global_scope = new_global_scope;
  current_type = (CPPType *)NULL;
  current_lexer = pp;
  yyparse();

  CPPType *result = current_type;

  current_scope = old_scope;
  global_scope = old_global_scope;
  current_lexer = old_lexer;
  current_type = old_type;

  return result;
}

static void
push_scope(CPPScope *new_scope) {
  last_scopes.push_back(current_scope);
  if (new_scope != NULL) {
    current_scope = new_scope;
  }
}

static void
pop_scope() {
  assert(!last_scopes.empty());
  current_scope = last_scopes.back();
  last_scopes.pop_back();
}

static void
push_storage_class(int new_storage_class) {
  last_storage_classes.push_back(current_storage_class);
  current_storage_class = new_storage_class;
}

static void
pop_storage_class() {
  assert(!last_storage_classes.empty());
  current_storage_class = last_storage_classes.back();
  last_storage_classes.pop_back();
}

static void
push_struct(CPPStructType *new_struct) {
  last_structs.push_back(current_struct);
  current_struct = new_struct;
}

static void
pop_struct() {
  assert(!last_structs.empty());
  current_struct = last_structs.back();
  last_structs.pop_back();
}


/* Line 371 of yacc.c  */
#line 270 "built/tmp/cppBison.yxx.c"

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
   by #include "cppBison.yxx.h".  */
#ifndef YY_CPPYY_BUILT_TMP_CPPBISON_YXX_H_INCLUDED
# define YY_CPPYY_BUILT_TMP_CPPBISON_YXX_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int cppyydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     REAL = 258,
     INTEGER = 259,
     CHAR_TOK = 260,
     SIMPLE_STRING = 261,
     SIMPLE_IDENTIFIER = 262,
     STRING_LITERAL = 263,
     CUSTOM_LITERAL = 264,
     IDENTIFIER = 265,
     TYPENAME_IDENTIFIER = 266,
     SCOPING = 267,
     TYPEDEFNAME = 268,
     ELLIPSIS = 269,
     OROR = 270,
     ANDAND = 271,
     EQCOMPARE = 272,
     NECOMPARE = 273,
     LECOMPARE = 274,
     GECOMPARE = 275,
     LSHIFT = 276,
     RSHIFT = 277,
     POINTSAT_STAR = 278,
     DOT_STAR = 279,
     UNARY = 280,
     UNARY_NOT = 281,
     UNARY_NEGATE = 282,
     UNARY_MINUS = 283,
     UNARY_PLUS = 284,
     UNARY_STAR = 285,
     UNARY_REF = 286,
     POINTSAT = 287,
     SCOPE = 288,
     PLUSPLUS = 289,
     MINUSMINUS = 290,
     TIMESEQUAL = 291,
     DIVIDEEQUAL = 292,
     MODEQUAL = 293,
     PLUSEQUAL = 294,
     MINUSEQUAL = 295,
     OREQUAL = 296,
     ANDEQUAL = 297,
     XOREQUAL = 298,
     LSHIFTEQUAL = 299,
     RSHIFTEQUAL = 300,
     KW_ALIGNAS = 301,
     KW_ALIGNOF = 302,
     KW_AUTO = 303,
     KW_BEGIN_PUBLISH = 304,
     KW_BLOCKING = 305,
     KW_BOOL = 306,
     KW_CATCH = 307,
     KW_CHAR = 308,
     KW_CHAR16_T = 309,
     KW_CHAR32_T = 310,
     KW_CLASS = 311,
     KW_CONST = 312,
     KW_CONSTEXPR = 313,
     KW_CONST_CAST = 314,
     KW_DECLTYPE = 315,
     KW_DEFAULT = 316,
     KW_DELETE = 317,
     KW_DOUBLE = 318,
     KW_DYNAMIC_CAST = 319,
     KW_ELSE = 320,
     KW_END_PUBLISH = 321,
     KW_ENUM = 322,
     KW_EXTENSION = 323,
     KW_EXTERN = 324,
     KW_EXPLICIT = 325,
     KW_PUBLISHED = 326,
     KW_FALSE = 327,
     KW_FINAL = 328,
     KW_FLOAT = 329,
     KW_FRIEND = 330,
     KW_FOR = 331,
     KW_GOTO = 332,
     KW_IF = 333,
     KW_INLINE = 334,
     KW_INT = 335,
     KW_LONG = 336,
     KW_MAKE_MAP_PROPERTY = 337,
     KW_MAKE_PROPERTY = 338,
     KW_MAKE_PROPERTY2 = 339,
     KW_MAKE_SEQ = 340,
     KW_MAKE_SEQ_PROPERTY = 341,
     KW_MUTABLE = 342,
     KW_NAMESPACE = 343,
     KW_NEW = 344,
     KW_NOEXCEPT = 345,
     KW_NULLPTR = 346,
     KW_OPERATOR = 347,
     KW_OVERRIDE = 348,
     KW_PRIVATE = 349,
     KW_PROTECTED = 350,
     KW_PUBLIC = 351,
     KW_REGISTER = 352,
     KW_REINTERPRET_CAST = 353,
     KW_RETURN = 354,
     KW_SHORT = 355,
     KW_SIGNED = 356,
     KW_SIZEOF = 357,
     KW_STATIC = 358,
     KW_STATIC_ASSERT = 359,
     KW_STATIC_CAST = 360,
     KW_STRUCT = 361,
     KW_TEMPLATE = 362,
     KW_THREAD_LOCAL = 363,
     KW_THROW = 364,
     KW_TRUE = 365,
     KW_TRY = 366,
     KW_TYPEDEF = 367,
     KW_TYPEID = 368,
     KW_TYPENAME = 369,
     KW_UNION = 370,
     KW_UNSIGNED = 371,
     KW_USING = 372,
     KW_VIRTUAL = 373,
     KW_VOID = 374,
     KW_VOLATILE = 375,
     KW_WCHAR_T = 376,
     KW_WHILE = 377,
     START_CPP = 378,
     START_CONST_EXPR = 379,
     START_TYPE = 380
   };
#endif
/* Tokens.  */
#define REAL 258
#define INTEGER 259
#define CHAR_TOK 260
#define SIMPLE_STRING 261
#define SIMPLE_IDENTIFIER 262
#define STRING_LITERAL 263
#define CUSTOM_LITERAL 264
#define IDENTIFIER 265
#define TYPENAME_IDENTIFIER 266
#define SCOPING 267
#define TYPEDEFNAME 268
#define ELLIPSIS 269
#define OROR 270
#define ANDAND 271
#define EQCOMPARE 272
#define NECOMPARE 273
#define LECOMPARE 274
#define GECOMPARE 275
#define LSHIFT 276
#define RSHIFT 277
#define POINTSAT_STAR 278
#define DOT_STAR 279
#define UNARY 280
#define UNARY_NOT 281
#define UNARY_NEGATE 282
#define UNARY_MINUS 283
#define UNARY_PLUS 284
#define UNARY_STAR 285
#define UNARY_REF 286
#define POINTSAT 287
#define SCOPE 288
#define PLUSPLUS 289
#define MINUSMINUS 290
#define TIMESEQUAL 291
#define DIVIDEEQUAL 292
#define MODEQUAL 293
#define PLUSEQUAL 294
#define MINUSEQUAL 295
#define OREQUAL 296
#define ANDEQUAL 297
#define XOREQUAL 298
#define LSHIFTEQUAL 299
#define RSHIFTEQUAL 300
#define KW_ALIGNAS 301
#define KW_ALIGNOF 302
#define KW_AUTO 303
#define KW_BEGIN_PUBLISH 304
#define KW_BLOCKING 305
#define KW_BOOL 306
#define KW_CATCH 307
#define KW_CHAR 308
#define KW_CHAR16_T 309
#define KW_CHAR32_T 310
#define KW_CLASS 311
#define KW_CONST 312
#define KW_CONSTEXPR 313
#define KW_CONST_CAST 314
#define KW_DECLTYPE 315
#define KW_DEFAULT 316
#define KW_DELETE 317
#define KW_DOUBLE 318
#define KW_DYNAMIC_CAST 319
#define KW_ELSE 320
#define KW_END_PUBLISH 321
#define KW_ENUM 322
#define KW_EXTENSION 323
#define KW_EXTERN 324
#define KW_EXPLICIT 325
#define KW_PUBLISHED 326
#define KW_FALSE 327
#define KW_FINAL 328
#define KW_FLOAT 329
#define KW_FRIEND 330
#define KW_FOR 331
#define KW_GOTO 332
#define KW_IF 333
#define KW_INLINE 334
#define KW_INT 335
#define KW_LONG 336
#define KW_MAKE_MAP_PROPERTY 337
#define KW_MAKE_PROPERTY 338
#define KW_MAKE_PROPERTY2 339
#define KW_MAKE_SEQ 340
#define KW_MAKE_SEQ_PROPERTY 341
#define KW_MUTABLE 342
#define KW_NAMESPACE 343
#define KW_NEW 344
#define KW_NOEXCEPT 345
#define KW_NULLPTR 346
#define KW_OPERATOR 347
#define KW_OVERRIDE 348
#define KW_PRIVATE 349
#define KW_PROTECTED 350
#define KW_PUBLIC 351
#define KW_REGISTER 352
#define KW_REINTERPRET_CAST 353
#define KW_RETURN 354
#define KW_SHORT 355
#define KW_SIGNED 356
#define KW_SIZEOF 357
#define KW_STATIC 358
#define KW_STATIC_ASSERT 359
#define KW_STATIC_CAST 360
#define KW_STRUCT 361
#define KW_TEMPLATE 362
#define KW_THREAD_LOCAL 363
#define KW_THROW 364
#define KW_TRUE 365
#define KW_TRY 366
#define KW_TYPEDEF 367
#define KW_TYPEID 368
#define KW_TYPENAME 369
#define KW_UNION 370
#define KW_UNSIGNED 371
#define KW_USING 372
#define KW_VIRTUAL 373
#define KW_VOID 374
#define KW_VOLATILE 375
#define KW_WCHAR_T 376
#define KW_WHILE 377
#define START_CPP 378
#define START_CONST_EXPR 379
#define START_TYPE 380



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
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


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int cppyyparse (void *YYPARSE_PARAM);
#else
int cppyyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int cppyyparse (void);
#else
int cppyyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_CPPYY_BUILT_TMP_CPPBISON_YXX_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 597 "built/tmp/cppBison.yxx.c"

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
#define YYFINAL  85
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5523

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  150
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  109
/* YYNRULES -- Number of rules.  */
#define YYNRULES  680
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1339

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   380

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   149,     2,     2,     2,   141,   134,     2,
     144,   146,   139,   137,   127,   138,   143,   140,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   129,   128,
     135,   130,   136,   131,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   145,     2,   148,   133,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   126,   132,   147,   142,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    14,    17,    20,    22,
      26,    31,    36,    37,    43,    45,    47,    49,    51,    53,
      56,    58,    60,    63,    66,    69,    72,    80,    90,   102,
     112,   124,   138,   148,   162,   172,   180,   186,   187,   191,
     193,   196,   200,   203,   206,   209,   212,   215,   218,   221,
     224,   227,   230,   233,   240,   242,   246,   248,   253,   255,
     259,   263,   267,   269,   270,   275,   276,   282,   285,   290,
     293,   298,   299,   304,   305,   311,   315,   318,   323,   326,
     331,   332,   339,   340,   347,   348,   356,   357,   369,   370,
     383,   384,   393,   394,   404,   406,   408,   410,   413,   416,
     419,   422,   427,   433,   435,   437,   439,   441,   443,   445,
     447,   449,   451,   453,   455,   457,   459,   461,   463,   465,
     467,   469,   471,   473,   475,   477,   479,   481,   483,   485,
     487,   489,   491,   493,   495,   497,   499,   501,   503,   506,
     509,   511,   513,   515,   517,   518,   525,   528,   530,   532,
     534,   538,   541,   546,   549,   554,   558,   563,   565,   567,
     569,   571,   574,   578,   581,   584,   587,   590,   593,   597,
     602,   606,   607,   614,   617,   621,   623,   627,   632,   634,
     636,   638,   642,   645,   647,   651,   653,   655,   657,   661,
     664,   666,   670,   672,   675,   677,   680,   682,   686,   692,
     696,   700,   702,   706,   710,   714,   718,   723,   725,   727,
     730,   732,   736,   740,   746,   750,   755,   761,   764,   766,
     768,   770,   772,   775,   778,   781,   784,   787,   791,   796,
     798,   800,   803,   806,   809,   812,   815,   819,   824,   832,
     836,   838,   841,   844,   847,   850,   853,   857,   862,   864,
     867,   870,   873,   876,   879,   883,   888,   894,   904,   914,
     924,   926,   928,   931,   933,   935,   937,   940,   945,   950,
     952,   954,   956,   959,   961,   963,   965,   968,   973,   976,
     981,   983,   985,   987,   990,   993,   996,  1001,  1003,  1005,
    1007,  1010,  1014,  1015,  1021,  1022,  1031,  1033,  1035,  1037,
    1039,  1042,  1046,  1048,  1051,  1054,  1057,  1061,  1065,  1069,
    1073,  1077,  1081,  1086,  1090,  1092,  1097,  1100,  1102,  1104,
    1106,  1110,  1116,  1118,  1121,  1126,  1128,  1131,  1134,  1136,
    1138,  1140,  1141,  1148,  1149,  1157,  1162,  1168,  1172,  1178,
    1183,  1185,  1187,  1189,  1191,  1193,  1195,  1197,  1199,  1201,
    1203,  1205,  1207,  1209,  1212,  1215,  1218,  1221,  1223,  1225,
    1228,  1230,  1231,  1234,  1236,  1239,  1241,  1243,  1245,  1247,
    1249,  1251,  1253,  1255,  1257,  1259,  1261,  1263,  1265,  1267,
    1269,  1271,  1273,  1275,  1277,  1279,  1281,  1283,  1285,  1287,
    1289,  1291,  1293,  1295,  1297,  1299,  1301,  1303,  1305,  1307,
    1309,  1311,  1313,  1315,  1317,  1319,  1321,  1323,  1325,  1327,
    1329,  1331,  1333,  1335,  1337,  1339,  1341,  1343,  1345,  1347,
    1349,  1351,  1353,  1355,  1357,  1359,  1361,  1363,  1365,  1367,
    1369,  1371,  1373,  1375,  1377,  1379,  1381,  1383,  1385,  1387,
    1389,  1391,  1393,  1395,  1397,  1399,  1401,  1403,  1405,  1407,
    1409,  1411,  1413,  1415,  1417,  1419,  1421,  1423,  1425,  1427,
    1429,  1431,  1433,  1435,  1437,  1439,  1441,  1443,  1445,  1447,
    1449,  1451,  1453,  1455,  1457,  1459,  1461,  1463,  1465,  1467,
    1469,  1471,  1473,  1475,  1477,  1479,  1481,  1483,  1485,  1489,
    1491,  1493,  1495,  1497,  1499,  1503,  1505,  1510,  1518,  1526,
    1534,  1542,  1547,  1552,  1555,  1558,  1561,  1564,  1567,  1570,
    1574,  1578,  1582,  1586,  1590,  1594,  1598,  1602,  1606,  1610,
    1614,  1618,  1622,  1626,  1630,  1634,  1640,  1645,  1650,  1654,
    1658,  1662,  1666,  1668,  1673,  1681,  1689,  1697,  1705,  1710,
    1715,  1720,  1725,  1730,  1735,  1740,  1745,  1750,  1755,  1760,
    1765,  1770,  1775,  1780,  1783,  1789,  1794,  1799,  1802,  1805,
    1808,  1811,  1814,  1817,  1821,  1825,  1829,  1833,  1837,  1841,
    1845,  1849,  1853,  1857,  1861,  1865,  1869,  1873,  1877,  1881,
    1885,  1889,  1895,  1900,  1905,  1909,  1913,  1917,  1921,  1923,
    1925,  1927,  1929,  1931,  1933,  1935,  1937,  1939,  1941,  1943,
    1952,  1964,  1966,  1971,  1979,  1987,  1995,  2003,  2008,  2013,
    2016,  2022,  2027,  2032,  2035,  2038,  2041,  2044,  2047,  2051,
    2055,  2059,  2063,  2067,  2071,  2075,  2079,  2083,  2087,  2091,
    2095,  2099,  2103,  2107,  2111,  2115,  2119,  2125,  2130,  2135,
    2139,  2143,  2147,  2151,  2153,  2155,  2157,  2159,  2161,  2163,
    2165,  2167,  2169,  2171,  2173,  2175,  2177,  2181,  2183,  2185,
    2188,  2190,  2192,  2195,  2198,  2200,  2202,  2204,  2206,  2208,
    2210,  2212,  2214,  2216,  2218,  2220,  2222,  2224,  2226,  2229,
    2232
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     151,     0,    -1,   123,   152,    -1,   124,   248,    -1,   125,
     216,    -1,   258,    -1,   152,   128,    -1,   152,   157,    -1,
     154,    -1,   153,   127,   154,    -1,   255,   144,   245,   146,
      -1,   255,   126,   245,   147,    -1,    -1,   160,   126,   156,
     152,   147,    -1,   163,    -1,   186,    -1,   155,    -1,   232,
      -1,   158,    -1,   112,   169,    -1,    49,    -1,    66,    -1,
      71,   129,    -1,    96,   129,    -1,    95,   129,    -1,    94,
     129,    -1,    83,   144,   255,   127,    10,   146,   128,    -1,
      83,   144,   255,   127,    10,   127,    10,   146,   128,    -1,
      83,   144,   255,   127,    10,   127,    10,   127,    10,   146,
     128,    -1,    86,   144,   255,   127,    10,   127,    10,   146,
     128,    -1,    86,   144,   255,   127,    10,   127,    10,   127,
      10,   146,   128,    -1,    86,   144,   255,   127,    10,   127,
      10,   127,    10,   127,    10,   146,   128,    -1,    84,   144,
     255,   127,    10,   127,    10,   146,   128,    -1,    84,   144,
     255,   127,    10,   127,    10,   127,    10,   127,    10,   146,
     128,    -1,    85,   144,   255,   127,    10,   127,    10,   146,
     128,    -1,   104,   144,   248,   127,   257,   146,   128,    -1,
     104,   144,   248,   146,   128,    -1,    -1,    75,   159,   157,
      -1,   258,    -1,    69,   160,    -1,    69,     6,   160,    -1,
     103,   160,    -1,    79,   160,    -1,   118,   160,    -1,    70,
     160,    -1,    97,   160,    -1,   120,   160,    -1,    87,   160,
      -1,    58,   160,    -1,    50,   160,    -1,    68,   160,    -1,
     108,   160,    -1,   145,   145,   161,   148,   148,   160,    -1,
     162,    -1,   162,   127,   161,    -1,   255,    -1,   255,   144,
     198,   146,    -1,   164,    -1,   160,   213,   128,    -1,   160,
     174,   202,    -1,   160,   177,   203,    -1,   235,    -1,    -1,
     160,   215,   165,   167,    -1,    -1,   160,    57,   215,   166,
     168,    -1,   194,   203,    -1,   194,   201,   127,   167,    -1,
     194,   203,    -1,   194,   201,   127,   168,    -1,    -1,   160,
     215,   170,   172,    -1,    -1,   160,    57,   215,   171,   173,
      -1,   160,   177,   203,    -1,   194,   203,    -1,   194,   201,
     127,   172,    -1,   194,   203,    -1,   194,   201,   127,   173,
      -1,    -1,    10,   144,   175,   196,   146,   183,    -1,    -1,
      11,   144,   176,   196,   146,   183,    -1,    -1,   142,   255,
     144,   178,   196,   146,   183,    -1,    -1,    11,   144,   139,
     192,   146,   144,   179,   196,   146,   183,   195,    -1,    -1,
      11,   144,    12,   139,   192,   146,   144,   180,   196,   146,
     183,   195,    -1,    -1,    92,   212,   208,   144,   181,   196,
     146,   183,    -1,    -1,    92,    57,   212,   208,   144,   182,
     196,   146,   183,    -1,    10,    -1,   258,    -1,    57,    -1,
     183,    90,    -1,   183,    73,    -1,   183,    93,    -1,   183,
      87,    -1,   183,   109,   144,   146,    -1,   183,   109,   144,
     255,   146,    -1,   149,    -1,   142,    -1,   139,    -1,   140,
      -1,   141,    -1,   137,    -1,   138,    -1,   132,    -1,   134,
      -1,   133,    -1,    15,    -1,    16,    -1,    17,    -1,    18,
      -1,    19,    -1,    20,    -1,   135,    -1,   136,    -1,    21,
      -1,    22,    -1,   130,    -1,   127,    -1,    34,    -1,    35,
      -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,    40,
      -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,    45,
      -1,    32,    -1,   145,   148,    -1,   144,   146,    -1,    89,
      -1,    62,    -1,   163,    -1,   186,    -1,    -1,   107,   187,
     135,   188,   136,   185,    -1,   107,   163,    -1,   258,    -1,
     189,    -1,   190,    -1,   189,   127,   190,    -1,    56,   255,
      -1,    56,   255,   130,   216,    -1,   114,   255,    -1,   114,
     255,   130,   216,    -1,   191,   209,   200,    -1,    57,   191,
     209,   200,    -1,   236,    -1,    10,    -1,    11,    -1,   256,
      -1,    92,   184,    -1,    92,     6,    10,    -1,    57,   192,
      -1,   120,   192,    -1,   139,   192,    -1,   134,   192,    -1,
      16,   192,    -1,    12,   139,   192,    -1,   192,   145,   244,
     148,    -1,   144,   192,   146,    -1,    -1,   192,   144,   193,
     198,   146,   183,    -1,   192,   195,    -1,   192,   129,     4,
      -1,   258,    -1,    32,   214,   211,    -1,    32,    57,   214,
     211,    -1,   258,    -1,    14,    -1,   197,    -1,   197,   127,
      14,    -1,   197,    14,    -1,   206,    -1,   197,   127,   206,
      -1,   258,    -1,    14,    -1,   199,    -1,   199,   127,    14,
      -1,   199,    14,    -1,   207,    -1,   199,   127,   207,    -1,
     258,    -1,   130,   247,    -1,   258,    -1,   130,   248,    -1,
     128,    -1,   126,   240,   147,    -1,   129,   153,   126,   240,
     147,    -1,   130,    61,   128,    -1,   130,    62,   128,    -1,
     128,    -1,   126,   240,   147,    -1,   130,   248,   128,    -1,
     130,    61,   128,    -1,   130,    62,   128,    -1,   130,   126,
     204,   147,    -1,   258,    -1,   205,    -1,   205,   127,    -1,
     248,    -1,   126,   204,   147,    -1,   205,   127,   248,    -1,
     205,   127,   126,   204,   147,    -1,   212,   209,   201,    -1,
      57,   212,   209,   201,    -1,    57,    97,   212,   209,   201,
      -1,    97,   206,    -1,   206,    -1,   250,    -1,   258,    -1,
     256,    -1,    57,   208,    -1,   120,   208,    -1,   139,   208,
      -1,   134,   208,    -1,    16,   208,    -1,    12,   139,   208,
      -1,   208,   145,   244,   148,    -1,   258,    -1,   256,    -1,
      57,   209,    -1,   120,   209,    -1,   139,   209,    -1,   134,
     209,    -1,    16,   209,    -1,    12,   139,   209,    -1,   209,
     145,   244,   148,    -1,   144,   209,   146,   144,   196,   146,
     183,    -1,   144,   209,   146,    -1,   258,    -1,    57,   210,
      -1,   120,   210,    -1,   139,   210,    -1,   134,   210,    -1,
      16,   210,    -1,    12,   139,   210,    -1,   210,   145,   244,
     148,    -1,   258,    -1,    57,   211,    -1,   120,   211,    -1,
     139,   210,    -1,   134,   210,    -1,    16,   210,    -1,    12,
     139,   210,    -1,   210,   145,   244,   148,    -1,   144,   196,
     146,   183,   195,    -1,   144,   139,   210,   146,   144,   196,
     146,   183,   195,    -1,   144,   134,   210,   146,   144,   196,
     146,   183,   195,    -1,   144,    16,   210,   146,   144,   196,
     146,   183,   195,    -1,   236,    -1,    11,    -1,   114,   255,
      -1,   217,    -1,   219,    -1,   225,    -1,   231,   255,    -1,
     230,   256,   129,   227,    -1,    60,   144,   248,   146,    -1,
      48,    -1,   236,    -1,    11,    -1,   114,   255,    -1,   217,
      -1,   219,    -1,   225,    -1,   231,   255,    -1,   230,   256,
     129,   227,    -1,   230,   255,    -1,    60,   144,   248,   146,
      -1,    48,    -1,   236,    -1,    11,    -1,   114,   255,    -1,
     231,   255,    -1,   230,   255,    -1,    60,   144,   248,   146,
      -1,    48,    -1,   213,    -1,    10,    -1,   212,   211,    -1,
      57,   212,   211,    -1,    -1,   231,   126,   218,   152,   147,
      -1,    -1,   231,   256,   220,   221,   222,   126,   152,   147,
      -1,   258,    -1,    73,    -1,   258,    -1,   223,    -1,   129,
     224,    -1,   223,   127,   224,    -1,   254,    -1,    96,   254,
      -1,    95,   254,    -1,    94,   254,    -1,   118,    96,   254,
      -1,   118,    95,   254,    -1,   118,    94,   254,    -1,    96,
     118,   254,    -1,    95,   118,   254,    -1,    94,   118,   254,
      -1,   226,   126,   229,   147,    -1,   230,   129,   227,    -1,
     230,    -1,   230,   256,   129,   227,    -1,   230,   256,    -1,
     237,    -1,    11,    -1,   258,    -1,   228,   255,   127,    -1,
     228,   255,   130,   248,   127,    -1,   228,    -1,   228,   255,
      -1,   228,   255,   130,   248,    -1,    67,    -1,    67,    56,
      -1,    67,   106,    -1,    56,    -1,   106,    -1,   115,    -1,
      -1,    88,   255,   126,   233,   152,   147,    -1,    -1,    79,
      88,   255,   126,   234,   152,   147,    -1,    88,   126,   152,
     147,    -1,    79,    88,   126,   152,   147,    -1,   117,   255,
     128,    -1,   117,   255,   130,   216,   128,    -1,   117,    88,
     255,   128,    -1,   237,    -1,   238,    -1,   239,    -1,    51,
      -1,    53,    -1,   121,    -1,    54,    -1,    55,    -1,   100,
      -1,    81,    -1,   116,    -1,   101,    -1,    80,    -1,   100,
     237,    -1,    81,   237,    -1,   116,   237,    -1,   101,   237,
      -1,    74,    -1,    63,    -1,    81,    63,    -1,   119,    -1,
      -1,   241,   242,    -1,   258,    -1,   242,   243,    -1,     3,
      -1,     4,    -1,     6,    -1,     8,    -1,     9,    -1,     5,
      -1,    10,    -1,    11,    -1,    12,    -1,     7,    -1,    14,
      -1,    15,    -1,    16,    -1,    17,    -1,    18,    -1,    19,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,    36,
      -1,    37,    -1,    38,    -1,    39,    -1,    40,    -1,    41,
      -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,    46,
      -1,    47,    -1,    48,    -1,    51,    -1,    52,    -1,    53,
      -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,    58,
      -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,
      -1,    64,    -1,    65,    -1,    67,    -1,    69,    -1,    70,
      -1,    72,    -1,    73,    -1,    74,    -1,    75,    -1,    76,
      -1,    77,    -1,    78,    -1,    79,    -1,    80,    -1,    81,
      -1,    87,    -1,    88,    -1,    89,    -1,    91,    -1,    92,
      -1,    93,    -1,    94,    -1,    95,    -1,    96,    -1,    71,
      -1,    97,    -1,    98,    -1,    99,    -1,   100,    -1,   101,
      -1,   102,    -1,   103,    -1,   104,    -1,   105,    -1,   106,
      -1,   108,    -1,   109,    -1,   110,    -1,   111,    -1,   112,
      -1,   113,    -1,   114,    -1,   115,    -1,   116,    -1,   117,
      -1,   118,    -1,   119,    -1,   120,    -1,   121,    -1,   122,
      -1,   137,    -1,   138,    -1,   139,    -1,   140,    -1,   134,
      -1,   132,    -1,   133,    -1,   149,    -1,   142,    -1,   130,
      -1,   141,    -1,   135,    -1,   136,    -1,   144,    -1,   146,
      -1,   143,    -1,   127,    -1,   128,    -1,   129,    -1,   145,
      -1,   148,    -1,   131,    -1,   126,   242,   147,    -1,   258,
      -1,   248,    -1,   258,    -1,   246,    -1,   248,    -1,   246,
     127,   248,    -1,   249,    -1,   144,   216,   146,   247,    -1,
     105,   135,   216,   136,   144,   246,   146,    -1,    64,   135,
     216,   136,   144,   246,   146,    -1,    59,   135,   216,   136,
     144,   246,   146,    -1,    98,   135,   216,   136,   144,   246,
     146,    -1,   102,   144,   216,   146,    -1,    47,   144,   216,
     146,    -1,   149,   247,    -1,   142,   247,    -1,   138,   247,
      -1,   137,   247,    -1,   139,   247,    -1,   134,   247,    -1,
     247,   139,   247,    -1,   247,   140,   247,    -1,   247,   141,
     247,    -1,   247,   137,   247,    -1,   247,   138,   247,    -1,
     247,   132,   247,    -1,   247,   133,   247,    -1,   247,   134,
     247,    -1,   247,    15,   247,    -1,   247,    16,   247,    -1,
     247,    17,   247,    -1,   247,    18,   247,    -1,   247,    19,
     247,    -1,   247,    20,   247,    -1,   247,    21,   247,    -1,
     247,    22,   247,    -1,   247,   131,   247,   129,   247,    -1,
     247,   145,   248,   148,    -1,   247,   144,   246,   146,    -1,
     247,   144,   146,    -1,   247,   143,   247,    -1,   247,    32,
     247,    -1,   144,   246,   146,    -1,   249,    -1,   144,   216,
     146,   248,    -1,   105,   135,   216,   136,   144,   246,   146,
      -1,    64,   135,   216,   136,   144,   246,   146,    -1,    59,
     135,   216,   136,   144,   246,   146,    -1,    98,   135,   216,
     136,   144,   246,   146,    -1,    11,   144,   245,   146,    -1,
      80,   144,   245,   146,    -1,    53,   144,   245,   146,    -1,
     121,   144,   245,   146,    -1,    54,   144,   245,   146,    -1,
      55,   144,   245,   146,    -1,    51,   144,   245,   146,    -1,
     100,   144,   245,   146,    -1,    81,   144,   245,   146,    -1,
     116,   144,   245,   146,    -1,   101,   144,   245,   146,    -1,
      74,   144,   245,   146,    -1,    63,   144,   245,   146,    -1,
     102,   144,   216,   146,    -1,    47,   144,   216,   146,    -1,
      89,   214,    -1,    89,   214,   144,   245,   146,    -1,   113,
     144,   216,   146,    -1,   113,   144,   248,   146,    -1,   149,
     248,    -1,   142,   248,    -1,   138,   248,    -1,   137,   248,
      -1,   139,   248,    -1,   134,   248,    -1,   248,   139,   248,
      -1,   248,   140,   248,    -1,   248,   141,   248,    -1,   248,
     137,   248,    -1,   248,   138,   248,    -1,   248,   132,   248,
      -1,   248,   133,   248,    -1,   248,   134,   248,    -1,   248,
      15,   248,    -1,   248,    16,   248,    -1,   248,    17,   248,
      -1,   248,    18,   248,    -1,   248,    19,   248,    -1,   248,
      20,   248,    -1,   248,   135,   248,    -1,   248,   136,   248,
      -1,   248,    21,   248,    -1,   248,    22,   248,    -1,   248,
     131,   248,   129,   248,    -1,   248,   145,   248,   148,    -1,
     248,   144,   246,   146,    -1,   248,   144,   146,    -1,   248,
     143,   248,    -1,   248,    32,   248,    -1,   144,   246,   146,
      -1,     4,    -1,   110,    -1,    72,    -1,     5,    -1,     3,
      -1,   257,    -1,     9,    -1,    10,    -1,    73,    -1,    93,
      -1,    91,    -1,   145,   252,   148,   183,   195,   126,   240,
     147,    -1,   145,   252,   148,   144,   196,   146,   183,   195,
     126,   240,   147,    -1,   251,    -1,   144,   216,   146,   248,
      -1,   105,   135,   216,   136,   144,   246,   146,    -1,    64,
     135,   216,   136,   144,   246,   146,    -1,    59,   135,   216,
     136,   144,   246,   146,    -1,    98,   135,   216,   136,   144,
     246,   146,    -1,   102,   144,   216,   146,    -1,    47,   144,
     216,   146,    -1,    89,   214,    -1,    89,   214,   144,   245,
     146,    -1,   113,   144,   216,   146,    -1,   113,   144,   248,
     146,    -1,   149,   248,    -1,   142,   248,    -1,   138,   248,
      -1,   137,   248,    -1,   134,   248,    -1,   250,   139,   248,
      -1,   250,   140,   248,    -1,   250,   141,   248,    -1,   250,
     137,   248,    -1,   250,   138,   248,    -1,   250,   132,   248,
      -1,   250,   133,   248,    -1,   250,   134,   248,    -1,   250,
      15,   248,    -1,   250,    16,   248,    -1,   250,    17,   248,
      -1,   250,    18,   248,    -1,   250,    19,   248,    -1,   250,
      20,   248,    -1,   250,   135,   248,    -1,   250,   136,   248,
      -1,   250,    21,   248,    -1,   250,    22,   248,    -1,   250,
     131,   248,   129,   248,    -1,   250,   145,   248,   148,    -1,
     250,   144,   246,   146,    -1,   250,   144,   146,    -1,   250,
     143,   248,    -1,   250,    32,   248,    -1,   144,   246,   146,
      -1,     4,    -1,   110,    -1,    72,    -1,     5,    -1,     3,
      -1,   257,    -1,     9,    -1,    10,    -1,    73,    -1,    93,
      -1,    91,    -1,   258,    -1,   253,    -1,   253,   127,   252,
      -1,   134,    -1,   130,    -1,   134,   255,    -1,   255,    -1,
     255,    -1,   231,   255,    -1,   114,   255,    -1,    10,    -1,
      11,    -1,    73,    -1,    93,    -1,   101,    -1,    74,    -1,
      96,    -1,    94,    -1,   103,    -1,    10,    -1,    11,    -1,
      93,    -1,     6,    -1,     8,    -1,   257,     6,    -1,   257,
       8,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   424,   424,   425,   429,   436,   437,   438,   442,   443,
     447,   451,   464,   463,   475,   476,   477,   478,   479,   480,
     481,   494,   503,   507,   515,   519,   523,   534,   555,   585,
     602,   630,   667,   689,   722,   744,   755,   769,   768,   783,
     787,   791,   802,   806,   810,   814,   818,   822,   826,   830,
     834,   838,   842,   846,   854,   855,   859,   860,   864,   868,
     877,   885,   893,   898,   897,   913,   912,   934,   942,   953,
     962,   976,   975,   991,   990,  1005,  1020,  1026,  1035,  1042,
    1055,  1054,  1079,  1078,  1106,  1105,  1136,  1135,  1154,  1153,
    1174,  1173,  1205,  1204,  1230,  1243,  1247,  1251,  1255,  1259,
    1263,  1268,  1272,  1283,  1287,  1291,  1295,  1299,  1303,  1307,
    1311,  1315,  1319,  1323,  1327,  1331,  1335,  1339,  1343,  1347,
    1351,  1355,  1359,  1363,  1367,  1371,  1375,  1379,  1383,  1387,
    1391,  1395,  1399,  1403,  1407,  1411,  1415,  1419,  1423,  1427,
    1431,  1435,  1442,  1443,  1448,  1447,  1455,  1459,  1460,  1464,
    1470,  1479,  1483,  1487,  1491,  1495,  1501,  1511,  1515,  1520,
    1532,  1536,  1550,  1565,  1570,  1575,  1580,  1585,  1590,  1595,
    1600,  1606,  1605,  1627,  1637,  1647,  1651,  1655,  1664,  1668,
    1673,  1677,  1682,  1690,  1695,  1703,  1707,  1712,  1716,  1721,
    1729,  1734,  1742,  1746,  1753,  1757,  1764,  1768,  1772,  1776,
    1780,  1787,  1791,  1795,  1799,  1803,  1807,  1814,  1815,  1816,
    1820,  1823,  1824,  1825,  1829,  1834,  1840,  1846,  1857,  1861,
    1871,  1875,  1879,  1884,  1889,  1894,  1899,  1904,  1909,  1917,
    1921,  1925,  1930,  1935,  1940,  1945,  1950,  1955,  1960,  1966,
    1974,  1978,  1983,  1988,  1993,  1998,  2003,  2008,  2016,  2020,
    2025,  2030,  2035,  2040,  2045,  2050,  2055,  2061,  2068,  2075,
    2085,  2089,  2097,  2101,  2105,  2109,  2113,  2129,  2145,  2154,
    2161,  2165,  2173,  2177,  2181,  2185,  2189,  2205,  2221,  2239,
    2248,  2255,  2259,  2267,  2271,  2287,  2303,  2312,  2319,  2323,
    2331,  2335,  2344,  2343,  2368,  2367,  2397,  2398,  2405,  2406,
    2410,  2411,  2415,  2419,  2423,  2427,  2431,  2435,  2439,  2443,
    2447,  2451,  2458,  2466,  2470,  2474,  2479,  2487,  2491,  2498,
    2499,  2504,  2511,  2512,  2517,  2525,  2529,  2533,  2540,  2544,
    2548,  2556,  2555,  2578,  2577,  2600,  2601,  2605,  2611,  2618,
    2627,  2628,  2629,  2633,  2637,  2641,  2645,  2649,  2653,  2658,
    2663,  2668,  2673,  2677,  2682,  2691,  2696,  2704,  2708,  2712,
    2720,  2730,  2730,  2740,  2741,  2745,  2746,  2747,  2748,  2749,
    2750,  2751,  2752,  2753,  2754,  2755,  2755,  2755,  2756,  2756,
    2756,  2756,  2757,  2757,  2757,  2757,  2757,  2758,  2758,  2758,
    2759,  2759,  2759,  2759,  2759,  2760,  2760,  2760,  2760,  2760,
    2761,  2761,  2761,  2761,  2761,  2762,  2762,  2762,  2762,  2762,
    2763,  2763,  2763,  2763,  2764,  2764,  2764,  2764,  2764,  2765,
    2765,  2765,  2765,  2765,  2766,  2766,  2766,  2766,  2766,  2766,
    2767,  2767,  2767,  2767,  2767,  2768,  2768,  2768,  2768,  2769,
    2769,  2769,  2769,  2770,  2770,  2770,  2770,  2770,  2771,  2771,
    2771,  2772,  2772,  2772,  2772,  2772,  2773,  2773,  2773,  2773,
    2773,  2774,  2774,  2774,  2774,  2774,  2777,  2777,  2777,  2777,
    2777,  2777,  2777,  2777,  2777,  2777,  2777,  2778,  2778,  2778,
    2778,  2778,  2778,  2778,  2778,  2778,  2778,  2779,  2779,  2783,
    2787,  2794,  2798,  2805,  2809,  2816,  2820,  2824,  2828,  2832,
    2836,  2840,  2844,  2848,  2852,  2856,  2860,  2864,  2868,  2872,
    2876,  2880,  2884,  2888,  2892,  2896,  2900,  2904,  2908,  2912,
    2916,  2920,  2924,  2928,  2932,  2936,  2940,  2944,  2948,  2952,
    2956,  2960,  2968,  2972,  2976,  2980,  2984,  2988,  2992,  3002,
    3008,  3014,  3020,  3026,  3032,  3038,  3045,  3052,  3059,  3066,
    3072,  3078,  3082,  3086,  3090,  3094,  3105,  3116,  3120,  3124,
    3128,  3132,  3136,  3140,  3144,  3148,  3152,  3156,  3160,  3164,
    3168,  3172,  3176,  3180,  3184,  3188,  3192,  3196,  3200,  3204,
    3208,  3212,  3216,  3220,  3224,  3228,  3232,  3236,  3243,  3247,
    3251,  3255,  3259,  3263,  3267,  3271,  3275,  3281,  3287,  3291,
    3295,  3309,  3313,  3317,  3321,  3325,  3329,  3333,  3337,  3341,
    3345,  3349,  3360,  3371,  3375,  3379,  3383,  3387,  3391,  3395,
    3399,  3403,  3407,  3411,  3415,  3419,  3423,  3427,  3431,  3435,
    3439,  3443,  3447,  3451,  3455,  3459,  3463,  3467,  3471,  3475,
    3479,  3483,  3487,  3494,  3498,  3502,  3506,  3510,  3514,  3518,
    3522,  3526,  3532,  3538,  3546,  3547,  3548,  3552,  3553,  3554,
    3555,  3559,  3567,  3575,  3603,  3607,  3611,  3615,  3619,  3625,
    3629,  3633,  3637,  3648,  3652,  3656,  3664,  3668,  3672,  3678,
    3689
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "REAL", "INTEGER", "CHAR_TOK",
  "SIMPLE_STRING", "SIMPLE_IDENTIFIER", "STRING_LITERAL", "CUSTOM_LITERAL",
  "IDENTIFIER", "TYPENAME_IDENTIFIER", "SCOPING", "TYPEDEFNAME",
  "ELLIPSIS", "OROR", "ANDAND", "EQCOMPARE", "NECOMPARE", "LECOMPARE",
  "GECOMPARE", "LSHIFT", "RSHIFT", "POINTSAT_STAR", "DOT_STAR", "UNARY",
  "UNARY_NOT", "UNARY_NEGATE", "UNARY_MINUS", "UNARY_PLUS", "UNARY_STAR",
  "UNARY_REF", "POINTSAT", "SCOPE", "PLUSPLUS", "MINUSMINUS", "TIMESEQUAL",
  "DIVIDEEQUAL", "MODEQUAL", "PLUSEQUAL", "MINUSEQUAL", "OREQUAL",
  "ANDEQUAL", "XOREQUAL", "LSHIFTEQUAL", "RSHIFTEQUAL", "KW_ALIGNAS",
  "KW_ALIGNOF", "KW_AUTO", "KW_BEGIN_PUBLISH", "KW_BLOCKING", "KW_BOOL",
  "KW_CATCH", "KW_CHAR", "KW_CHAR16_T", "KW_CHAR32_T", "KW_CLASS",
  "KW_CONST", "KW_CONSTEXPR", "KW_CONST_CAST", "KW_DECLTYPE", "KW_DEFAULT",
  "KW_DELETE", "KW_DOUBLE", "KW_DYNAMIC_CAST", "KW_ELSE", "KW_END_PUBLISH",
  "KW_ENUM", "KW_EXTENSION", "KW_EXTERN", "KW_EXPLICIT", "KW_PUBLISHED",
  "KW_FALSE", "KW_FINAL", "KW_FLOAT", "KW_FRIEND", "KW_FOR", "KW_GOTO",
  "KW_IF", "KW_INLINE", "KW_INT", "KW_LONG", "KW_MAKE_MAP_PROPERTY",
  "KW_MAKE_PROPERTY", "KW_MAKE_PROPERTY2", "KW_MAKE_SEQ",
  "KW_MAKE_SEQ_PROPERTY", "KW_MUTABLE", "KW_NAMESPACE", "KW_NEW",
  "KW_NOEXCEPT", "KW_NULLPTR", "KW_OPERATOR", "KW_OVERRIDE", "KW_PRIVATE",
  "KW_PROTECTED", "KW_PUBLIC", "KW_REGISTER", "KW_REINTERPRET_CAST",
  "KW_RETURN", "KW_SHORT", "KW_SIGNED", "KW_SIZEOF", "KW_STATIC",
  "KW_STATIC_ASSERT", "KW_STATIC_CAST", "KW_STRUCT", "KW_TEMPLATE",
  "KW_THREAD_LOCAL", "KW_THROW", "KW_TRUE", "KW_TRY", "KW_TYPEDEF",
  "KW_TYPEID", "KW_TYPENAME", "KW_UNION", "KW_UNSIGNED", "KW_USING",
  "KW_VIRTUAL", "KW_VOID", "KW_VOLATILE", "KW_WCHAR_T", "KW_WHILE",
  "START_CPP", "START_CONST_EXPR", "START_TYPE", "'{'", "','", "';'",
  "':'", "'='", "'?'", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'~'", "'.'", "'('", "'['", "')'", "'}'", "']'",
  "'!'", "$accept", "grammar", "cpp", "constructor_inits",
  "constructor_init", "extern_c", "$@1", "declaration",
  "friend_declaration", "$@2", "storage_class", "attribute_specifiers",
  "attribute_specifier", "type_like_declaration",
  "multiple_var_declaration", "$@3", "$@4",
  "multiple_instance_identifiers", "multiple_const_instance_identifiers",
  "typedef_declaration", "$@5", "$@6", "typedef_instance_identifiers",
  "typedef_const_instance_identifiers", "constructor_prototype", "$@7",
  "$@8", "function_prototype", "$@9", "$@10", "$@11", "$@12", "$@13",
  "function_post", "function_operator", "more_template_declaration",
  "template_declaration", "$@14", "template_formal_parameters",
  "template_nonempty_formal_parameters", "template_formal_parameter",
  "template_formal_parameter_type", "instance_identifier", "$@15",
  "instance_identifier_and_maybe_trailing_return_type",
  "maybe_trailing_return_type", "function_parameter_list",
  "function_parameters", "formal_parameter_list", "formal_parameters",
  "template_parameter_maybe_initialize", "maybe_initialize",
  "maybe_initialize_or_constructor_body",
  "maybe_initialize_or_function_body", "structure_init",
  "structure_init_body", "function_parameter", "formal_parameter",
  "not_paren_formal_parameter_identifier", "formal_parameter_identifier",
  "not_paren_empty_instance_identifier", "empty_instance_identifier",
  "type", "type_decl", "predefined_type", "var_type_decl", "full_type",
  "anonymous_struct", "$@16", "named_struct", "$@17", "maybe_final",
  "maybe_class_derivation", "class_derivation", "base_specification",
  "enum", "enum_decl", "enum_element_type", "enum_body_trailing_comma",
  "enum_body", "enum_keyword", "struct_keyword", "namespace_declaration",
  "$@18", "$@19", "using_declaration", "simple_type", "simple_int_type",
  "simple_float_type", "simple_void_type", "code", "$@20", "code_block",
  "element", "optional_const_expr", "optional_const_expr_comma",
  "const_expr_comma", "no_angle_bracket_const_expr", "const_expr",
  "const_operand", "formal_const_expr", "formal_const_operand",
  "capture_list", "capture", "class_derivation_name", "name",
  "name_no_final", "string_literal", "empty", YY_NULL
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   123,    44,    59,    58,
      61,    63,   124,    94,    38,    60,    62,    43,    45,    42,
      47,    37,   126,    46,    40,    91,    41,   125,    93,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   150,   151,   151,   151,   152,   152,   152,   153,   153,
     154,   154,   156,   155,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   159,   158,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   161,   161,   162,   162,   163,   163,
     163,   163,   163,   165,   164,   166,   164,   167,   167,   168,
     168,   170,   169,   171,   169,   169,   172,   172,   173,   173,
     175,   174,   176,   174,   178,   177,   179,   177,   180,   177,
     181,   177,   182,   177,   177,   183,   183,   183,   183,   183,
     183,   183,   183,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   185,   185,   187,   186,   186,   188,   188,   189,
     189,   190,   190,   190,   190,   190,   190,   191,   191,   191,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   193,   192,   194,   194,   195,   195,   195,   196,   196,
     196,   196,   196,   197,   197,   198,   198,   198,   198,   198,
     199,   199,   200,   200,   201,   201,   202,   202,   202,   202,
     202,   203,   203,   203,   203,   203,   203,   204,   204,   204,
     205,   205,   205,   205,   206,   206,   206,   206,   207,   207,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     210,   210,   210,   210,   210,   210,   210,   210,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   214,   214,   214,   214,   214,   214,   214,   215,   215,
     216,   216,   218,   217,   220,   219,   221,   221,   222,   222,
     223,   223,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   225,   226,   226,   226,   226,   227,   227,   228,
     228,   228,   229,   229,   229,   230,   230,   230,   231,   231,
     231,   233,   232,   234,   232,   232,   232,   235,   235,   235,
     236,   236,   236,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   238,   238,   238,
     239,   241,   240,   242,   242,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   244,
     244,   245,   245,   246,   246,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   252,   252,   252,   253,   253,   253,
     253,   254,   254,   254,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   256,   256,   256,   257,   257,   257,   257,
     258
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     2,     2,     1,     3,
       4,     4,     0,     5,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     2,     2,     2,     7,     9,    11,     9,
      11,    13,     9,    13,     9,     7,     5,     0,     3,     1,
       2,     3,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     6,     1,     3,     1,     4,     1,     3,
       3,     3,     1,     0,     4,     0,     5,     2,     4,     2,
       4,     0,     4,     0,     5,     3,     2,     4,     2,     4,
       0,     6,     0,     6,     0,     7,     0,    11,     0,    12,
       0,     8,     0,     9,     1,     1,     1,     2,     2,     2,
       2,     4,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     0,     6,     2,     1,     1,     1,
       3,     2,     4,     2,     4,     3,     4,     1,     1,     1,
       1,     2,     3,     2,     2,     2,     2,     2,     3,     4,
       3,     0,     6,     2,     3,     1,     3,     4,     1,     1,
       1,     3,     2,     1,     3,     1,     1,     1,     3,     2,
       1,     3,     1,     2,     1,     2,     1,     3,     5,     3,
       3,     1,     3,     3,     3,     3,     4,     1,     1,     2,
       1,     3,     3,     5,     3,     4,     5,     2,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     3,     4,     1,
       1,     2,     2,     2,     2,     2,     3,     4,     7,     3,
       1,     2,     2,     2,     2,     2,     3,     4,     1,     2,
       2,     2,     2,     2,     3,     4,     5,     9,     9,     9,
       1,     1,     2,     1,     1,     1,     2,     4,     4,     1,
       1,     1,     2,     1,     1,     1,     2,     4,     2,     4,
       1,     1,     1,     2,     2,     2,     4,     1,     1,     1,
       2,     3,     0,     5,     0,     8,     1,     1,     1,     1,
       2,     3,     1,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     4,     3,     1,     4,     2,     1,     1,     1,
       3,     5,     1,     2,     4,     1,     2,     2,     1,     1,
       1,     0,     6,     0,     7,     4,     5,     3,     5,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     1,     1,     2,
       1,     0,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     3,     1,     4,     7,     7,     7,
       7,     4,     4,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     4,     4,     3,     3,
       3,     3,     1,     4,     7,     7,     7,     7,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     2,     5,     4,     4,     2,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     4,     4,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     8,
      11,     1,     4,     7,     7,     7,     7,     4,     4,     2,
       5,     4,     4,     2,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     4,     4,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     2,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   680,     0,     0,     0,   680,     5,   592,   588,   591,
     676,   677,   594,   595,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   590,   596,     0,     0,     0,     0,   598,
     597,     0,     0,     0,     0,     0,   589,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   680,     0,     3,   532,
     593,   261,   269,   343,   344,   346,   347,   328,     0,     0,
     358,   325,   357,   352,   349,   348,   351,   329,     0,   330,
     350,   360,   345,   680,     4,   263,   264,   265,     0,   314,
       0,   260,   340,   341,   342,     1,    20,   680,   680,    21,
     680,   680,   680,     0,    37,   680,     0,     0,     0,     0,
     680,     0,     0,     0,     0,   680,   680,     0,   680,   680,
     680,     0,   680,   680,     6,     0,    16,     7,    18,     0,
      14,    58,    15,    17,    62,    39,   680,     0,   680,   680,
     680,   680,     0,   680,     0,   680,   680,   680,   282,   287,
       0,     0,   553,     0,     0,   281,     0,   680,   680,     0,
       0,     0,   680,   680,   562,   560,   559,   561,   558,   261,
     343,   344,   346,   347,   358,   357,   352,   349,   348,   351,
     350,   345,     0,     0,   493,   664,   665,   666,   669,   667,
     671,   670,   668,   672,   658,   657,     0,   655,   660,   654,
     557,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   678,   679,   680,     0,   326,   327,
     359,   349,   354,   353,   356,   262,   355,     0,   680,   680,
     680,   680,   680,   680,     0,   290,   248,   680,   673,   674,
     675,     0,   316,   664,   665,   667,   292,   266,   294,   680,
      50,    49,    51,   680,    40,    45,    22,   680,     0,    43,
       0,     0,     0,     0,    48,   680,     0,    25,    24,    23,
      46,    42,     0,     0,   146,     0,    52,     0,    19,     0,
       0,    44,    47,     0,   289,   271,   280,     0,     0,     0,
       0,    12,     0,     0,     0,   288,    63,   273,   274,   275,
     314,     0,   270,     0,   492,   491,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   283,   680,
     285,   284,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   587,   659,   680,   680,   571,   572,   573,
     574,   575,   576,   579,   580,   586,     0,   568,   569,   570,
     577,   578,   566,   567,   563,   564,   565,   585,   584,     0,
       0,   291,     0,   680,     0,   680,   680,   680,   680,   680,
     253,   240,     0,   249,     0,   250,   252,   251,   179,   680,
       0,     0,   680,   680,     0,   180,   183,   680,   178,   680,
     322,     0,   319,   318,   313,   317,     0,   680,   680,    41,
      38,   680,     0,     0,     0,     0,     0,   680,   331,     0,
     680,   289,   271,     0,     0,   288,    71,     0,   337,     0,
       0,    54,    56,    80,    82,   289,   271,    65,     0,     0,
     680,   272,   680,     0,   361,   196,     0,     0,    60,   361,
     201,     0,    61,    59,     0,   278,   316,   276,   538,   552,
     544,   540,   542,   543,     0,   550,     0,   549,   539,   546,
       0,     0,     0,   545,   548,   551,     0,   555,   556,   547,
     541,   533,   494,    96,   680,   680,    95,   656,     0,   583,
     582,   268,   254,   680,   245,   241,   242,   244,   243,   680,
       0,     0,   680,   217,     0,     0,   680,   182,     0,     0,
     680,   680,   680,   680,   680,   680,   680,   230,   229,     0,
     490,   489,   323,   312,   267,   680,   297,   680,   296,   680,
     333,     0,     0,     0,     0,   335,   680,     0,     0,   158,
     159,     0,     0,     0,     0,   148,   149,   680,   157,   147,
       0,    73,    75,     0,   339,     0,     0,     0,   680,   680,
       0,     0,   680,     0,     0,   680,     0,   680,   680,   680,
     680,   680,     0,   221,   220,   680,    84,     0,   680,     0,
       8,     0,     0,     0,     0,     0,     0,   680,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,   680,   680,
     160,     0,     0,     0,   286,   554,     0,     0,     0,     0,
      98,   100,    97,    99,     0,     0,   175,   581,   246,     0,
       0,   680,   680,     0,     0,   680,   181,   184,   680,   235,
     231,   232,   234,   233,     0,     0,   680,   214,   194,   255,
     320,     0,   293,     0,     0,   299,   298,   336,   680,     0,
       0,     0,     0,   680,     0,    36,   151,   680,   153,   680,
       0,   680,     0,    72,   680,   338,   680,    55,   647,   643,
     646,   649,   650,   186,     0,     0,     0,   645,   651,     0,
     653,   652,     0,     0,     0,   644,     0,     0,     0,     0,
       0,     0,     0,     0,   187,   218,   190,   219,   601,   648,
     185,     0,     0,     0,     0,    66,   680,   279,     0,   680,
     226,   222,   223,   225,   224,    90,   680,    13,   680,   197,
     362,   363,   361,     0,   680,   680,   199,   200,   202,   204,
     205,   680,     0,   208,   210,   207,   203,     0,   167,   163,
       0,   113,   114,   115,   116,   117,   118,   121,   122,   137,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   141,   140,   124,   123,   110,   112,   111,   119,
     120,   108,   109,   105,   106,   107,   104,     0,     0,   103,
     161,   164,   166,   165,     0,     0,   171,   680,   173,     0,
       0,    67,   277,     0,     0,     0,     0,   680,     0,   680,
       0,   361,   247,   680,   680,   215,   680,   680,   256,   236,
     239,   195,     0,   324,   671,     0,   670,     0,     0,   300,
       0,   302,   661,   680,     0,   680,     0,     0,     0,     0,
       0,   332,     0,     0,   680,     0,   142,   145,   143,   150,
       0,   155,   192,    74,   680,     0,    76,    53,     0,     0,
       0,   609,     0,     0,     0,     0,   617,   616,   615,   614,
       0,     0,   613,    57,   189,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   680,
       0,     0,   680,     0,    69,    92,   227,   680,     0,     0,
     365,   366,   370,   367,   374,   368,   369,   371,   372,   373,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   440,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,   438,   439,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   680,   482,   483,   484,   475,   487,   471,   472,   470,
     477,   478,   466,   467,   468,   469,   476,   474,   481,   479,
     485,   480,   486,   473,   364,     0,     9,     0,     0,     0,
     206,   209,   168,   162,   139,   138,   170,   174,   680,     0,
     195,     0,   536,   535,   537,   534,   680,   680,   176,   101,
       0,     0,     0,   216,     0,     0,   680,   237,   321,     0,
     305,     0,   304,     0,   303,   663,     0,     0,     0,   662,
     680,   301,   334,     0,    26,     0,     0,     0,    35,   152,
     156,   154,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   193,   495,     0,    78,     0,
       0,     0,     0,   680,     0,     0,     0,     0,     0,     0,
     642,   188,   191,   626,   627,   628,   629,   630,   631,   634,
     635,   641,     0,   623,   624,   625,   632,   633,   621,   622,
     618,   619,   620,   640,   639,     0,     0,    81,     0,    86,
      83,     0,   680,     0,   228,   680,     0,   198,    11,    10,
     211,   680,   212,     0,   169,    68,     0,   177,   102,   599,
     680,   680,   680,     0,   311,   310,   309,   308,   307,   306,
     295,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   508,   506,   505,   507,   504,     0,
       0,   503,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    77,   608,     0,     0,     0,     0,
     607,     0,   611,   612,   602,     0,   638,   637,    88,   680,
      70,     0,   680,    85,   488,     0,   680,   361,   680,   680,
     680,   680,     0,    27,     0,    32,    34,     0,    29,     0,
       0,     0,     0,     0,     0,     0,   531,   517,   518,   519,
     520,   521,   522,   523,   524,   530,     0,   514,   515,   516,
     512,   513,   509,   510,   511,   529,   528,     0,     0,    79,
       0,     0,   610,     0,     0,   636,   680,     0,   680,    91,
     213,   172,     0,   259,   258,   257,   238,     0,     0,     0,
       0,   502,     0,     0,     0,   501,     0,   496,     0,   527,
     526,     0,     0,     0,     0,     0,   680,    93,   600,    28,
       0,     0,    30,     0,     0,     0,     0,   525,   605,   604,
     606,   603,   680,   680,     0,     0,     0,     0,     0,     0,
     680,    87,    33,    31,   499,   498,   500,   497,    89
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,   569,   570,   116,   432,   117,   118,   257,
     119,   420,   421,   120,   121,   444,   553,   587,   695,   278,
     543,   652,   653,   833,   293,   549,   552,   294,   708,  1219,
    1276,   887,  1132,   475,   770,   827,   122,   275,   534,   535,
     536,   537,   588,  1028,   589,   605,   384,   385,   683,   684,
     831,   627,   438,   442,   722,   723,   386,   686,   562,   506,
     234,   235,    73,   415,   142,   296,    74,    75,   397,    76,
     398,   517,   634,   635,   809,    77,    78,   394,   390,   391,
      79,    80,   123,   526,   638,   124,    81,    82,    83,    84,
     567,   568,   710,  1014,   509,   303,   304,  1085,   174,    49,
     687,   688,   186,   187,   811,   812,   590,    50,   125
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -703
static const yytype_int16 yypact[] =
{
     362,  -703,  2822,  4474,    57,  3018,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -118,   -82,   -78,   -69,   -61,   -41,
     -13,   -30,    -4,  -703,  -703,   -18,    -2,     1,  4682,  -703,
    -703,    23,    59,    73,    89,   133,  -703,   141,   188,   199,
    2822,  2822,  2822,  2822,  2822,  1432,   585,  2822,  3762,  -703,
     189,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  4704,   213,
    -703,   -20,  -703,  -703,  1983,  2722,  2722,  -703,  1244,  -703,
    2722,  -703,  -703,    62,  -703,  -703,  -703,  -703,    66,    48,
     959,  -703,  -703,  -703,  -703,  -703,  -703,  5378,  5378,  -703,
    5378,   892,  5378,   160,  -703,  5335,   225,   227,   233,   251,
    5378,  2255,   191,   269,   272,  5378,  5378,   263,  5263,  5378,
    5378,  2691,  5378,  5378,  -703,    63,  -703,  -703,  -703,  3269,
    -703,  -703,  -703,  -703,  -703,  -703,  2822,  4474,  2822,  2822,
    2822,  2822,  4474,  2822,  4474,  2822,  2822,  2822,  -703,  -703,
     278,  1244,   289,  1244,  1244,  -703,  4474,  2822,  2822,  4474,
    4474,  1432,  2822,  2822,    79,    79,    79,    79,    79,  -118,
     -78,   -69,   -61,   -41,   -30,   -18,    -2,  2511,  2380,  2608,
    2625,   199,   309,   -83,  3762,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  1244,   310,   332,  -703,  -703,
      79,  2822,  2822,  2822,  2822,  2822,  2822,  2822,  2822,  2822,
    2822,  2822,  2822,  2822,  2822,  2822,  2822,  2822,  2822,  2822,
    2822,  2822,  2252,  2822,  -703,  -703,    62,  2822,  -703,  -703,
    -703,  2722,  -703,  -703,  -703,  -703,  -703,   322,   145,    62,
      62,   145,   145,  4033,   321,  -703,   324,  -703,  -703,  -703,
    -703,  1115,   342,    27,    64,    87,  -703,  -703,  -703,  5378,
    -703,  -703,  -703,  5378,  -703,  -703,  -703,  5231,  2349,  -703,
    1244,  1244,  1244,  1244,  -703,  -703,   363,  -703,  -703,  -703,
    -703,  -703,  2822,  3300,  -703,   346,  -703,  3376,  -703,  1244,
     115,  -703,  -703,  1244,   300,   348,  -703,  2943,   349,  4546,
    1244,  -703,  1244,   350,   148,   370,  -703,  -703,  -703,  -703,
     900,   959,  -703,   344,   381,  -703,   351,   378,   383,   384,
     385,   396,   388,   399,   392,   397,   398,  2822,  -703,  2822,
    -703,  -703,   413,   406,   407,   409,   425,   416,  3483,   417,
     418,  2822,  2822,  -703,  -703,   -24,   585,   935,  3983,  1311,
    1311,   117,   117,   729,   729,  -703,  3672,  4123,  4039,  1275,
     117,   117,   167,   167,    79,    79,    79,  -703,  -703,   -36,
    1126,  -703,  3504,   145,   441,   145,   145,   145,   145,   145,
     364,  -703,   321,  -703,   321,  -703,   364,   364,  -703,   145,
    4603,  4452,   145,   145,   435,    37,  -703,   623,  -703,  2822,
    1244,   436,  -703,  -703,  -703,  -703,  1115,  -703,   509,  -703,
    -703,  -703,   458,   466,   467,   470,   477,  4839,  -703,  3443,
    4236,   295,   464,  2943,   148,  -703,  -703,   481,  -703,  4474,
     468,   485,   471,  -703,    20,  -703,  -703,  -703,  2822,  4704,
     403,  -703,  -703,   474,  -703,  -703,  1244,    -9,  -703,  -703,
    -703,  1553,  -703,  -703,   529,  -703,   491,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,   479,  -703,   480,  -703,  -703,  -703,
    3522,   482,   483,  -703,  -703,  -703,   486,  -703,  -703,  -703,
    -703,    79,  3762,  -703,  4308,   932,  -703,  -703,  2822,  -703,
    -703,  -703,   364,   145,   364,   364,   364,   364,   364,  2822,
     -58,  4704,   623,  -703,    26,    35,   572,  -703,  4380,   492,
     623,   623,   623,   623,   623,   623,   -21,  -703,  -703,   484,
    3762,  -703,   -34,  -703,   510,  4895,  -703,   511,  -703,  4951,
    -703,   631,   633,   634,   637,  -703,  -703,   355,   523,  -703,
    -703,  1244,  2467,  1244,   516,   530,  -703,   623,  -703,  -703,
      20,  -703,  -703,   529,  -703,   528,   512,  1244,  2014,  4308,
     522,   529,  4308,   529,  3540,   403,   533,   403,   403,   403,
     403,   403,    95,  -703,  -703,  5007,  -703,   520,  -703,   210,
    -703,   -71,   546,   547,   537,   548,   549,  2366,  3707,   550,
     529,   529,  3133,   529,   529,   529,   529,  -703,   138,   308,
    -703,  1115,  2822,  2822,  -703,  -703,  2822,  2822,   539,  4625,
    -703,  -703,  -703,  -703,   543,   564,  -703,  3762,   364,   544,
     552,   623,   -21,   555,   556,   932,  -703,  -703,   623,   557,
     557,   557,   557,   557,   265,  2822,  2822,  -703,  -703,   558,
    -703,  2822,  -703,  4125,   568,   574,  -703,  -703,  -703,   -23,
     577,   579,   584,  5063,    41,  -703,   582,   623,   587,  5309,
    4236,    44,   529,  -703,   308,  -703,  5378,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,   601,   586,   611,  -703,  -703,  4682,
    -703,  -703,   612,   605,   615,  -703,   609,  2822,  2822,  2822,
    2822,  1432,  2822,   610,    78,  -703,  -703,  3804,  -703,   189,
    -703,   613,   529,   367,   614,  -703,   308,  -703,   273,   403,
     618,   618,   618,   618,   618,  -703,  2822,  -703,  4308,  -703,
    1867,  -703,  -703,  1244,  2822,  2822,  -703,  -703,  -703,  -703,
    -703,  2366,   619,   638,  3762,  -703,  -703,   529,   301,   301,
     748,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,   622,   621,  -703,
    -703,   301,   301,   301,   373,   766,  -703,  2822,  -703,  1553,
     645,  -703,   510,    17,    80,    98,   142,   572,  4682,    62,
     369,  -703,  -703,  4308,   -21,  -703,  4308,  4308,  -703,   557,
     629,  3762,   627,  3726,  4743,  4759,  4798,  1244,   426,  -703,
    1244,  -703,  -703,  -703,  4125,  5119,   767,   650,   769,   772,
     773,  -703,   657,  4474,    44,  4474,  -703,  -703,  -703,  -703,
    2936,  -703,  -703,  -703,   308,   660,  -703,  -703,  4474,  4474,
    4474,   647,  4474,  4474,  4474,  1432,    79,    79,    79,    79,
     654,   144,    79,  -703,  -703,  2133,  2822,  2822,  2822,  2822,
    2822,  2822,  2822,  2822,  2822,  2822,  2822,  2822,  2822,  2822,
    2822,  2822,  2822,  2822,  2822,  2822,  2822,  2480,  2822,   572,
     382,   661,   572,   674,  -703,  -703,   618,  4308,   656,   662,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,  -703,  -703,  -703,  -703,   659,  -703,   663,   665,   667,
    -703,  2594,   301,  -703,  -703,  -703,  -703,  -703,  2014,   668,
    3707,   529,  -703,  -703,  -703,  -703,   932,    62,  -703,  -703,
     669,   670,   682,  -703,   688,   689,  4308,  -703,  -703,  3147,
    -703,  3147,  -703,  3147,  -703,  -703,  3147,  3147,  3147,  -703,
    5175,  -703,  -703,   154,  -703,   175,   691,   176,  -703,  -703,
    -703,  -703,   694,   697,   705,   707,   699,   709,  2936,  2936,
    2936,  2936,  2936,  1432,  2936,  3935,  -703,   720,  -703,   529,
     706,   715,   717,  2822,   721,   719,   739,   730,  3575,  2822,
    -703,  -703,  -703,   935,  3983,  1311,  1311,   117,   117,   729,
     729,  -703,  3744,  4123,  4039,  1275,   117,   117,   167,   167,
      79,    79,    79,  -703,  -703,   196,  2034,   283,   733,  -703,
     283,   529,  4308,   736,  -703,   572,  1720,  -703,  -703,  -703,
    -703,  2366,  3762,   738,  -703,  -703,   753,  -703,  -703,  -703,
     572,   572,   572,   741,  -703,  -703,  -703,  -703,  -703,  -703,
    -703,   875,   760,   879,   764,   765,   884,   768,  4474,  4474,
    4474,  4474,  4474,  4474,   205,   205,   205,   205,   205,   749,
     198,   205,  2936,  2936,  2936,  2936,  2936,  2936,  2936,  2936,
    2936,  2936,  2936,  2936,  2936,  2936,  2936,  2936,  2936,  2936,
    2936,  2708,  2822,   529,  -703,  -703,   771,   774,   751,   775,
    -703,   777,  -703,  -703,    79,  2822,  -703,  -703,  -703,  4308,
    -703,   763,   572,   283,  -703,   761,   572,  -703,   932,   932,
     932,   572,   770,  -703,   785,  -703,  -703,   200,  -703,   795,
     781,   807,   809,   802,   813,  2936,  -703,  1567,  3965,  3088,
    3088,   462,   462,   762,   762,  -703,  3893,  2266,  4139,  4168,
     686,   686,   205,   205,   205,  -703,  -703,   201,  3164,  -703,
    2822,  2822,  -703,  2822,  2822,  3762,  4308,   812,   572,   283,
    -703,   283,   816,  -703,  -703,  -703,   283,   837,   903,   956,
     847,  -703,   832,   833,   834,  -703,   836,   205,  2936,  -703,
    -703,   206,   245,   247,   248,   835,   572,   283,  -703,  -703,
     838,   841,  -703,  2822,  2822,  2822,  2822,  3935,  -703,  -703,
    -703,  -703,   572,   932,   854,   855,   256,   257,   258,   262,
     932,  -703,  -703,  -703,  -703,  -703,  -703,  -703,  -703
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -703,  -703,  -222,  -703,   279,  -703,  -703,   734,  -703,  -703,
     -11,   450,  -703,   -99,  -703,  -703,  -703,   -33,  -132,  -703,
    -703,  -703,   -87,  -197,  -703,  -703,  -703,   731,  -703,  -703,
    -703,  -703,  -703,  -442,  -703,  -703,   358,  -703,  -703,  -703,
     361,   489,  -516,  -703,  -512,  -559,  -467,  -703,   -15,  -703,
     190,  -541,  -703,  -377,  -702,  -703,  -380,   161,  -309,  -206,
      85,  -191,   -42,   -95,  -579,  -227,    16,  -104,  -703,   -89,
    -703,  -703,  -703,  -703,   203,   -73,  -703,  -356,  -703,  -703,
     -14,    -7,  -703,  -703,  -703,  -703,    14,    51,  -703,  -703,
    -437,  -703,    24,  -703,  -472,  -125,   -27,  -260,   531,   277,
    -703,  -703,   687,  -703,  -698,   803,   811,  -514,    -1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -676
static const yytype_int16 yytable[] =
{
       6,   493,   574,   307,   308,   309,   310,   598,   312,   274,
     314,   315,   316,   644,   143,   297,   216,   609,   173,  1019,
     789,   144,   323,   324,   295,   361,   126,   329,   330,   778,
     298,   654,   550,   473,   689,   693,   218,   542,   373,   375,
     514,   696,   145,   407,   332,   189,   299,   214,   780,   215,
     416,   497,   572,   573,   615,   714,   798,    85,   238,   239,
     427,   172,   127,   333,   728,   729,   128,   771,   772,   773,
     774,   795,   236,   715,   227,   129,   250,   251,   228,   252,
     254,   255,   691,   130,   259,   694,   219,   489,   610,   264,
     841,   332,   854,   630,   270,   271,   631,   273,   276,   277,
    -673,   281,   282,   131,   816,   300,  1050,  1052,  1054,   625,
     479,   199,   301,   835,   133,   222,   223,   224,   617,   229,
     474,   226,   132,   817,   626,   305,   135,   305,   305,   305,
     305,   134,   305,   302,   305,   305,   305,  -674,   197,   198,
     834,   240,   136,   306,   332,   137,   305,   305,   311,   199,
     313,   305,   305,  -673,   802,   883,  -673,   364,   146,   551,
    -675,   365,   322,  1032,   498,   325,   326,   327,   685,   297,
     599,   489,   613,   297,   830,   515,   880,   241,   295,   519,
     489,   614,   230,   297,   298,   359,   541,   822,   298,   626,
    -674,   387,   237,  -674,   461,   214,   231,   215,   298,   199,
     299,   232,   366,   147,   299,   855,   233,   332,   283,  1037,
     565,  1022,   781,  -675,   299,   236,  -675,   148,   222,   223,
     224,   226,   211,   212,   213,   332,  1033,   371,   236,   236,
     371,   371,   388,   149,   888,   782,   392,  1190,   259,   705,
     706,   889,   399,   418,  1034,   419,   698,   430,   700,   701,
     702,   703,   704,  1043,   206,   207,   208,   209,   210,   300,
     211,   212,   213,   300,     6,   367,   301,   775,   150,   332,
     301,   332,   222,   300,   439,  1015,   440,   836,   441,   368,
     301,  1161,   776,   777,   369,   151,   612,   302,  1035,   256,
    1100,   302,   395,  1087,   619,   620,   621,   622,   623,   624,
    1162,   302,  1163,  1166,   643,  1029,   208,   209,   210,   297,
     211,   212,   213,   370,   372,   374,   376,   377,   305,   884,
     267,  1164,  1167,   332,   298,   332,  1042,  1289,   332,  1044,
    1045,   651,   152,   332,   476,   189,   712,   713,   492,   387,
     299,   689,  1216,   153,  1246,  1036,  1290,  1299,  1200,  1201,
    1202,  1154,  1318,  1155,  1041,  1156,   600,   217,  1157,  1158,
    1159,    10,   371,    11,   371,   371,   371,   371,   371,   260,
     601,   261,   332,   602,   332,   332,   603,   262,   371,   175,
     176,   371,   371,   332,   332,   332,   508,   555,   511,   332,
     886,  1319,   604,  1320,  1321,   263,     6,   518,   268,   300,
       6,   269,  1334,  1335,  1336,   794,   301,   272,  1337,   539,
     626,   800,   799,   238,   239,   556,   815,   885,   706,   557,
    1133,   -94,   317,   -94,   538,   -94,   -94,   302,   -94,   564,
     -94,     6,   387,   319,   439,   545,   440,  1127,   779,  1225,
    1130,   824,   177,   178,   423,   776,   777,   395,   482,   611,
     484,   485,   486,   487,   488,   331,   387,  1088,   335,   336,
     558,   363,   179,   180,   490,   181,   389,   494,   495,  -240,
     182,   396,   183,   388,   606,   685,   434,  1146,   435,   436,
     437,   410,   371,  1188,  1189,     1,     2,     3,   511,   408,
     448,   508,   424,   428,  1190,   476,   240,   449,   443,   508,
     508,   508,   508,   508,   508,   628,   387,   387,   332,   489,
     387,   776,   777,   881,   689,  1039,   636,   776,   777,  1026,
    1056,  1057,  1058,   559,   450,     6,   776,   777,  1128,   451,
     452,   453,   454,    48,   455,   456,   508,   560,   457,   238,
     239,   579,   561,   458,   459,   580,   538,   690,   388,   462,
     826,   388,   463,   464,   564,   465,   564,   564,   564,   564,
     564,   466,   467,   469,   470,   783,   784,   711,   608,   785,
     786,   154,   155,   156,   157,   158,   725,   654,   190,  1153,
     483,   496,   516,   513,   520,   143,   581,   606,   628,  1017,
    1018,  1060,   144,   521,   522,   175,   176,   523,  1038,  1195,
    1196,  1197,  1198,  1199,   524,  1200,  1201,  1202,   540,   544,
     508,   628,   547,   145,   606,   548,   546,   508,   566,   696,
     591,   582,   240,   592,   593,   511,   810,   596,   595,   473,
     597,   618,   629,   238,   239,   499,  -315,     6,   273,   500,
     633,   639,   395,   640,   641,   837,   508,   642,   685,   583,
     832,   645,   649,   628,   851,   143,   655,   650,   177,   178,
     656,   692,   144,   584,   538,  1221,   387,   709,   585,  1283,
    1284,  1285,   699,   586,   716,   717,   719,   720,   179,   180,
     501,   181,   328,   145,   718,   787,   182,   790,   183,   727,
     791,   834,   792,  1223,   813,   628,   793,   850,   564,   796,
     797,   814,   626,  -247,   818,   511,   819,   388,  1228,  1229,
    1230,   820,   823,   305,   305,   184,   240,   825,  1190,   185,
     725,   839,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   502,   360,   838,   840,   842,   362,   843,
     844,   387,  1277,   845,   387,   387,   853,   503,  1023,   879,
     882,   199,   504,   706,  1331,  1021,  1020,   505,  1024,  1025,
    1027,  1338,  1031,  1046,   143,  1047,   511,  1063,  1064,  1065,
    1279,   144,  1066,  1067,  1281,  1068,   476,  1089,   236,  1286,
    1282,  1093,   388,   628,  1190,   388,   388,   810,   810,   810,
    1099,  1131,   145,   409,  1134,  1129,  1137,   810,  1135,  1305,
    1138,  1139,     6,   387,  1140,  1148,  1144,  1149,  1174,  1175,
    1176,  1177,  1178,   832,  1181,  1197,  1198,  1199,  1150,  1200,
    1201,  1202,  1169,   628,  1151,  1152,  1307,  1165,  1168,  1069,
    1170,  1071,  1171,  1172,  1173,   387,  1147,  1203,   460,   188,
    1125,  1206,  1205,  1207,  1090,  1091,  1092,  1209,  1094,  1095,
    1096,  1097,   471,   472,  1323,  1210,   206,   207,   208,   209,
     210,   225,   211,   212,   213,  1211,  1212,  1218,   476,  1227,
    1330,   476,  1222,   247,  1226,  1232,   388,  1231,  1233,  1234,
     242,   248,  1235,  1236,  1237,  1245,  1238,  1272,   253,  1195,
    1196,  1197,  1198,  1199,   266,  1200,  1201,  1202,  1280,  1278,
     243,   244,  1288,  1310,   280,  1270,  1287,  1292,  1271,  1273,
     510,  1274,  1247,  1248,  1249,  1250,  1251,  1252,  1253,  1254,
    1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,
    1265,  1291,    87,  1293,   318,  1294,   320,   321,  1295,  1296,
      88,   192,   193,   194,   195,   196,   197,   198,  1306,   554,
      90,    91,    92,  1308,   599,  1309,  1311,   199,  1208,   243,
     244,   249,   578,   177,   178,  1312,  1313,  1314,  1315,   100,
    1316,  1322,  1332,  1333,  1324,  1297,   387,  1325,   334,   105,
     711,   400,  1016,   245,   180,   106,   181,   657,  1145,  1220,
     109,   182,  1204,   183,   387,   600,  1269,   828,   414,   607,
     112,   829,   113,  1143,  1070,  1136,  1102,  1061,     0,   601,
     510,   647,   602,   477,     0,   603,     0,   690,     0,   241,
       0,     0,   177,   178,     0,   606,   236,   115,  1317,     0,
       0,   604,   810,     0,   810,   388,   810,     0,     0,   810,
     810,   810,   245,   180,     0,   181,  1180,     0,     0,     0,
     182,   402,   183,   403,   404,   405,   406,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,     0,   211,   212,
     213,     0,   417,     0,     0,   246,   422,     0,     0,     0,
     387,     0,   305,   431,     0,   433,     0,     0,     0,  1179,
       0,     0,     0,   445,   447,     0,     0,  1086,   724,     0,
       0,   446,   248,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   393,     0,     0,     0,
       0,   388,     0,     0,   476,     0,     0,     0,     0,   188,
     725,   191,   192,   193,   194,   195,   196,   197,   198,   476,
     476,   476,     0,     0,     0,     0,   801,   510,   199,     0,
       0,     0,   803,     0,     0,     0,    53,     0,    54,    55,
      56,     0,     0,     0,  1267,     0,     0,   387,     0,     0,
       0,     0,     0,     0,  1239,  1240,  1241,  1242,  1243,  1244,
       0,     0,     0,   512,     0,    63,   221,     0,   507,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   846,   847,
     848,   849,     0,   852,     0,    65,    66,     0,   388,     0,
       0,   476,     0,     0,     0,   476,     0,   606,   606,   606,
     476,    70,     0,     0,   387,     0,    72,   510,     0,   571,
       0,   563,     0,  1301,  1302,     0,  1303,  1304,     0,     0,
       0,     0,   724,     0,   175,   176,     0,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,     0,   211,
     212,   213,     0,     0,   480,   388,     0,   476,     0,     0,
       0,     0,     0,     0,     0,     0,  1326,  1327,  1328,  1329,
       0,     0,   193,   194,   195,   196,   197,   198,     0,     0,
       0,     0,     0,   507,     0,   476,     0,   199,   510,     0,
    1030,   507,   507,   507,   507,   507,   507,   177,   178,     0,
       0,   476,   606,     0,     0,     0,     0,     0,     0,   606,
     195,   196,   197,   198,   646,     0,   648,   179,   180,     0,
     181,     0,     0,   199,     0,   182,     0,   183,   507,     0,
     422,     0,     0,     0,     0,  1086,  1086,  1086,  1086,  1086,
       0,  1086,     0,     0,     0,     0,   563,     0,   563,   563,
     563,   563,   563,     0,     0,     0,  1098,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1103,  1104,  1105,
    1106,  1107,  1108,  1109,  1110,  1111,  1112,  1113,  1114,  1115,
    1116,  1117,  1118,  1119,  1120,  1121,  1122,  1123,     0,  1126,
     204,   205,   206,   207,   208,   209,   210,     0,   211,   212,
     213,     0,   507,     0,     0,     0,     0,     0,     0,   507,
       0,     0,     0,     0,     0,     7,     8,     9,    10,     0,
      11,    12,    13,   159,     0,     0,   204,   205,   206,   207,
     208,   209,   210,     0,   211,   212,   213,     0,   507,  1086,
    1086,  1086,  1086,  1086,  1086,  1086,  1086,  1086,  1086,  1086,
    1086,  1086,  1086,  1086,  1086,  1086,  1086,  1086,     0,    15,
      52,     0,     0,   160,     0,   161,   162,   163,    57,    58,
       0,    20,    59,     0,     0,   164,    22,     0,     0,    61,
       0,     0,     0,     0,    23,    24,   165,     0,     0,     0,
     563,     0,   166,   167,     0,     0,   571,     0,     0,     0,
       0,    28,  1086,    29,     0,    30,     0,     0,     0,     0,
      31,     0,   168,   169,    34,     0,     0,    35,    67,     0,
       0,     0,    36,     0,     0,    37,    68,    69,   170,     0,
       0,    71,  1142,   171,     0,     0,     7,     8,     9,    10,
       0,    11,    12,    13,    14,     0,    40,     0,     0,    41,
      42,    43,     0,     0,    44,  1086,    45,    46,     0,     0,
       0,    47,     0,  1183,  1184,  1185,  1186,  1187,  1188,  1189,
       0,     0,     0,  1040,     0,     0,     0,     0,     0,  1190,
      15,     0,     0,     0,    16,     0,    17,    18,    19,     0,
    1055,     0,    20,  1059,   575,   576,    21,    22,     0,     0,
       0,     0,     0,     0,     0,    23,    24,    25,     0,     0,
    1214,     0,     0,    26,    27,     0,     0,     0,     0,     0,
       0,     0,    28,     0,    29,     0,    30,     0,     0,     0,
       0,    31,     0,    32,    33,    34,     0,     0,    35,     0,
       0,     0,     0,    36,     0,     0,    37,     0,     0,    38,
       0,     0,   724,     0,    39,     0,     0,     0,     0,   577,
       0,     0,     0,     0,     0,     0,     0,    40,     0,     0,
      41,    42,    43,     0,     0,    44,     0,    45,    46,  1192,
    1193,  1194,    47,     0,  1195,  1196,  1197,  1198,  1199,     0,
    1200,  1201,  1202,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   890,   891,   892,   893,   894,   895,   896,
     897,   898,   899,  1268,   900,   901,   902,   903,   904,   905,
     906,   907,   908,   909,   910,     0,  1275,     0,     0,     0,
       0,     0,   911,   912,   913,   914,   915,   916,   917,   918,
     919,   920,   921,   922,   923,   924,   925,   926,   927,     0,
       0,   928,   929,   930,   931,   932,   933,   934,   935,   936,
     937,   938,   939,   940,   941,   942,     0,   943,     0,   944,
     945,   946,   947,   948,   949,   950,   951,   952,   953,   954,
     955,   956,     0,     0,     0,     0,     0,   957,   958,   959,
       0,   960,   961,   962,   963,   964,   965,   966,   967,   968,
     969,   970,   971,   972,   973,   974,   975,     0,   976,   977,
     978,   979,   980,   981,   982,   983,   984,   985,   986,   987,
     988,   989,   990,     0,     0,     0,   991,   992,   993,   994,
     995,   996,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,
    1005,  1006,  1007,  1008,  1009,  1010,  1011,  1224,  1012,  1013,
     890,   891,   892,   893,   894,   895,   896,   897,   898,   899,
       0,   900,   901,   902,   903,   904,   905,   906,   907,   908,
     909,   910,     0,     0,     0,     0,     0,     0,     0,   911,
     912,   913,   914,   915,   916,   917,   918,   919,   920,   921,
     922,   923,   924,   925,   926,   927,     0,     0,   928,   929,
     930,   931,   932,   933,   934,   935,   936,   937,   938,   939,
     940,   941,   942,     0,   943,     0,   944,   945,   946,   947,
     948,   949,   950,   951,   952,   953,   954,   955,   956,     0,
       0,     0,     0,     0,   957,   958,   959,     0,   960,   961,
     962,   963,   964,   965,   966,   967,   968,   969,   970,   971,
     972,   973,   974,   975,     0,   976,   977,   978,   979,   980,
     981,   982,   983,   984,   985,   986,   987,   988,   989,   990,
       0,     0,     0,   991,   992,   993,   994,   995,   996,   997,
     998,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,
    1008,  1009,  1010,  1011,     0,  1012,  1013,   658,   659,   660,
      10,     0,    11,   661,   662,    51,     0,     0,   663,     0,
       0,     0,     0,     0,    53,     0,    54,    55,    56,     0,
       0,     0,     0,     0,     0,     0,   220,     0,     0,   191,
     192,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,   664,    52,    63,   221,    53,   199,    54,    55,    56,
      57,   380,     0,   665,    59,     0,     0,    60,   666,     0,
       0,    61,     0,    65,    66,     0,   667,   668,    62,     0,
       0,     0,     0,     0,    63,    64,     0,     0,     0,    70,
       0,     0,     0,   669,    72,   670,     0,   671,     0,     0,
       0,   381,   672,     0,    65,    66,   673,     0,     0,   674,
      67,     0,     0,     0,   675,     0,     0,   676,    68,    69,
      70,     0,     0,    71,     0,    72,   658,   659,   660,    10,
       0,    11,   661,   662,    51,     0,     0,  1101,   677,     0,
       0,   678,   679,     0,     0,     0,   680,     0,   681,     0,
       0,     0,     0,   682,     0,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,   211,   212,   213,
     664,    52,  1217,     0,    53,     0,    54,    55,    56,    57,
     380,     0,   665,    59,     0,     0,    60,   666,     0,     0,
      61,     0,     0,     0,     0,   667,   668,    62,     0,     0,
       0,     0,     0,    63,    64,     0,     0,     0,     0,     0,
       0,     0,   669,     0,   670,     0,   671,     0,     0,     0,
     381,   672,     0,    65,    66,   673,     0,     0,   674,    67,
       0,     0,     0,   675,     0,     0,   676,    68,    69,    70,
       0,     0,    71,     0,    72,     7,     8,     9,    10,     0,
      11,    12,    13,    14,     0,   175,   176,   677,     0,     0,
     678,   679,     0,     0,     0,   680,     0,   681,     0,     0,
       0,     0,   682,  1184,  1185,  1186,  1187,  1188,  1189,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1190,    15,
       0,     0,     0,    16,     0,    17,    18,    19,     0,     0,
       0,    20,     0,     0,     0,    21,    22,     0,     0,     0,
       0,     0,     0,     0,    23,    24,    25,     0,   177,   178,
       0,     0,    26,    27,     0,     0,     0,     0,     0,     0,
       0,    28,     0,    29,     0,    30,     0,     0,   179,   180,
      31,   181,    32,    33,    34,     0,   182,    35,   183,   175,
     176,     0,    36,     0,     0,    37,     0,     0,    38,     7,
       8,     9,    10,    39,    11,    12,    13,    14,     0,     0,
       0,   265,     0,     0,     0,     0,    40,     0,     0,    41,
      42,    43,     0,     0,    44,     0,    45,    46,   358,  1193,
    1194,    47,     0,  1195,  1196,  1197,  1198,  1199,     0,  1200,
    1201,  1202,     0,    15,     0,     0,     0,    16,     0,    17,
      18,    19,   177,   178,     0,    20,     0,     0,     0,    21,
      22,    53,     0,    54,    55,    56,     0,     0,    23,    24,
      25,     0,   179,   180,     0,   181,    26,    27,     0,     0,
     182,     0,   183,     0,     0,    28,     0,    29,     0,    30,
      63,   221,     0,     0,    31,     0,    32,    33,    34,     0,
       0,    35,     0,     0,     0,   401,    36,   529,   530,    37,
      65,    66,    38,     7,     8,     9,    10,    39,    11,    12,
      13,    14,   721,     0,     0,     0,    70,     0,     0,     0,
      40,    72,     0,    41,    42,    43,     0,     0,    44,     0,
      45,    46,     0,     0,     0,    47,     0,     0,    53,     0,
      54,    55,    56,     0,   147,     0,     0,    15,     0,     0,
      60,    16,     0,    17,    18,    19,     0,     0,     0,    20,
       0,    62,     0,    21,    22,     0,     0,    63,    64,     0,
       0,     0,    23,    24,    25,     0,     0,     0,     0,     0,
      26,    27,    53,     0,    54,    55,    56,    65,    66,    28,
       0,    29,     0,    30,   220,     0,     0,     0,    31,     0,
      32,    33,    34,    70,     0,    35,    71,     0,    72,     0,
      36,    63,   221,    37,     0,     0,    38,     7,     8,     9,
      10,    39,    11,    12,    13,    14,     0,     0,     0,     0,
       0,    65,    66,     0,    40,     0,     0,    41,    42,    43,
       0,     0,    44,     0,    45,    46,  1124,    70,     0,    47,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,    15,     0,     0,     0,    16,     0,    17,    18,    19,
       0,     0,     0,    20,     0,   137,     0,    21,    22,    53,
       0,    54,    55,    56,     0,     0,    23,    24,    25,     0,
       0,     0,     0,     0,    26,    27,    53,     0,    54,    55,
      56,     0,     0,    28,     0,    29,     0,    30,    63,   221,
       0,     0,    31,     0,    32,    33,    34,     0,     0,    35,
       0,   175,   176,     0,    36,    63,   221,    37,    65,    66,
      38,     7,     8,     9,    10,    39,    11,    12,    13,    14,
    1141,     0,     0,     0,    70,    65,    66,     0,    40,    72,
       0,    41,    42,    43,     0,     0,    44,     0,    45,    46,
       0,    70,     0,    47,     0,     0,    72,     0,     0,     0,
       0,     0,   148,     0,     0,    15,     0,     0,     0,    16,
       0,    17,    18,    19,   177,   178,     0,    20,     0,   152,
       0,    21,    22,    53,     0,    54,    55,    56,     0,   279,
      23,    24,    25,     0,   179,   180,     0,   181,    26,    27,
       0,     0,   182,     0,   183,     0,     0,    28,     0,    29,
       0,    30,    63,   221,     0,     0,    31,     0,    32,    33,
      34,     0,     0,    35,     0,     0,     0,     0,    36,     0,
       0,    37,    65,    66,    38,     7,     8,     9,    10,    39,
      11,    12,    13,    14,     0,     0,     0,     0,    70,     0,
       0,     0,    40,    72,     0,    41,    42,    43,     0,     0,
      44,     0,    45,    46,  1266,     0,     0,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
       0,     0,     0,    16,     0,    17,    18,    19,     0,     0,
       0,    20,     0,     0,     0,    21,    22,     0,     0,     0,
       0,     0,     0,     0,    23,    24,    25,     0,     0,     0,
       0,     0,    26,    27,     0,     0,     0,     0,     0,     0,
       0,    28,     0,    29,     0,    30,     0,     0,     0,     0,
      31,     0,    32,    33,    34,     0,     0,    35,     0,     0,
       0,     0,    36,     0,     0,    37,     0,     0,    38,     7,
       8,     9,    10,    39,    11,    12,    13,     0,     0,     0,
       0,     0,     0,   425,   426,     0,    40,     0,     0,    41,
      42,    43,     0,     0,    44,     0,    45,    46,     0,     0,
       0,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1072,     0,     0,     0,     0,     0,     0,
       0,   286,     0,     0,    53,  1073,    54,    55,    56,    57,
    1074,     0,     0,   288,     0,     0,    60,     0,    23,    24,
      61,     0,     0,     0,     0,     0,     0,    62,    -2,     0,
       0,     0,     0,    63,    64,     0,     0,    29,     0,    30,
       0,     0,     0,     0,  1075,     0,     0,     0,  1076,     0,
       0,  1077,     0,    65,    66,     0,    36,     0,     0,    67,
       0,     0,     0,     0,     0,     0,     0,   290,    69,    70,
       0,     0,    71,     0,    72,     0,     0,    86,    87,     0,
    1078,     0,     0,  1079,  1080,  1081,    88,     0,  1082,     0,
    1083,    46,     0,     0,    89,  1084,    90,    91,    92,    93,
       0,     0,     0,    94,     0,     0,     0,    95,     0,     0,
       0,    96,    97,    98,    99,   100,   101,  1186,  1187,  1188,
    1189,     0,   102,   103,   104,   105,     0,     0,     0,     0,
    1190,   106,   107,     0,     0,   108,   109,     0,     0,     0,
     110,     0,     0,     0,     0,   111,   112,     0,   113,   730,
       0,     0,     0,     0,     0,     0,   114,     0,   731,   732,
     733,   734,   735,   736,   737,   738,     0,   175,   176,     0,
       0,     0,     0,   115,     0,   739,     0,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,   750,   751,   191,
     192,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,     0,     0,     0,     0,   752,   199,     0,     0,     0,
       0,     0,     0,    57,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     177,   178,   753,     0,     0,  1195,  1196,  1197,  1198,  1199,
       0,  1200,  1201,  1202,     0,     0,     0,     0,     0,     0,
     179,   180,     0,   181,     0,     0,     0,     0,   182,     0,
     183,     0,     0,    67,     0,     0,     0,     0,     0,     0,
     754,   807,    69,   755,     0,   756,   757,   758,   759,   760,
     761,   762,   763,   764,   765,   766,     0,   767,   768,   284,
     285,     0,   769,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,   211,   212,   213,
     284,   285,  1300,     0,     0,     0,     0,   286,     0,     0,
      53,     0,    54,    55,    56,    57,   287,     0,     0,   288,
       0,     0,    60,     0,     0,     0,    61,     0,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,   286,    63,
      64,    53,     0,    54,    55,    56,    57,   287,     0,     0,
     288,   289,     0,    60,     0,     0,     0,    61,     0,    65,
      66,     0,     0,     0,    62,    67,     0,     0,     0,     0,
      63,    64,     0,   290,    69,    70,   411,   412,    71,     0,
      72,     0,   289,     0,     0,   291,     0,     0,     0,     0,
      65,    66,     0,     0,     0,     0,    67,     0,     0,     0,
       0,   292,     0,     0,   290,    69,    70,     0,     0,    71,
       0,    72,     0,     0,   286,     0,     0,    53,     0,    54,
      55,    56,    57,   413,     0,     0,   288,     0,     0,    60,
       0,     0,   292,    61,     0,     0,     0,     0,     0,     0,
      62,     0,     0,     0,     0,     0,    63,    64,   191,   192,
     193,   194,   195,   196,   197,   198,     0,     0,   289,     0,
       0,     0,     0,     0,     0,   199,    65,    66,     0,     0,
       0,     0,    67,     0,     0,     0,     0,     0,     0,     0,
     290,    69,    70,     0,     0,    71,     0,    72,   191,   192,
     193,   194,   195,   196,   197,   198,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   199,     0,     0,   292,   191,
     192,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   199,   191,   192,   193,
     194,   195,   196,   197,   198,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   199,   191,   192,   193,   194,   195,
     196,   197,   198,     0,     0,     0,     0,     0,     0,     0,
     527,     0,   199,     0,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,     0,   211,   212,   213,   528,
     191,   192,   193,   194,   195,   196,   197,   198,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   199,     0,     0,
       0,     0,     0,     0,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,     0,   211,   212,   213,   468,
       0,     0,     0,     0,     0,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,   211,   212,   213,
     481,     0,     0,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,     0,   211,   212,   213,   594,     0,
       0,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,     0,   211,   212,   213,   697,   191,   192,   193,
     194,   195,   196,   197,   198,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   199,     0,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,     0,   211,   212,
     213,  1213,   191,   192,   193,   194,   195,   196,   197,   198,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   199,
       0,   191,   192,   193,   194,   195,   196,   197,   198,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   199,   191,
     192,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   199,   191,   192,   193,
     194,   195,   196,   197,   198,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   199,     0,     0,     0,     0,     0,
       0,   478,     0,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,     0,   211,   212,   213,     0,   856,
     857,   858,   859,   860,   861,   862,   863,     0,     0,     0,
       0,     0,     0,     0,     0,   726,   864,     0,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,     0,
     211,   212,   213,  1048,     0,     0,     0,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,     0,   211,
     212,   213,     0,  1215,     0,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,   211,   212,   213,
       0,     0,     0,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,     0,   211,   212,   213,  1182,  1183,
    1184,  1185,  1186,  1187,  1188,  1189,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1190,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   865,   866,   867,   868,   869,
     870,   871,   872,   873,   874,   875,     0,   876,   877,   878,
    1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1184,  1185,  1186,  1187,  1188,  1189,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1190,     0,     0,
     193,   194,   195,   196,   197,   198,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   199,     0,     0,     0,     0,
       0,     0,  1298,     0,  1191,  1192,  1193,  1194,     0,     0,
    1195,  1196,  1197,  1198,  1199,     0,  1200,  1201,  1202,     0,
       0,     0,     0,     0,    51,     0,     0,   378,     0,   379,
       0,     0,     0,     0,     0,     0,   193,   194,   195,   196,
     197,   198,     0,     0,     0,     0,  1191,  1192,  1193,  1194,
       0,   199,  1195,  1196,  1197,  1198,  1199,     0,  1200,  1201,
    1202,    52,     0,     0,    53,     0,    54,    55,    56,    57,
     380,     0,     0,    59,     0,     0,    60,  1192,  1193,  1194,
      61,     0,  1195,  1196,  1197,  1198,  1199,    62,  1200,  1201,
    1202,     0,     0,    63,    64,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,     0,   211,   212,   213,     0,
     381,     0,     0,    65,    66,   175,   176,     0,     0,    67,
     193,   194,   195,   196,   197,   198,     0,    68,    69,    70,
       0,     0,    71,     0,    72,   199,  1184,  1185,  1186,  1187,
    1188,  1189,     0,     0,     0,     0,     0,   382,     0,     0,
       0,  1190,   383,   203,   204,   205,   206,   207,   208,   209,
     210,    57,   211,   212,   213,  1184,  1185,  1186,  1187,  1188,
    1189,     0,     0,     0,     0,     0,     0,     0,   177,   178,
    1190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   179,   804,
     805,   806,     0,     0,     0,     0,   182,     0,   183,     0,
       0,    67,     0,     0,     0,     0,     0,     0,     0,   807,
      69,     0,     0,   808,     0,     0,   529,   530,     0,     0,
       0,     0,     0,     0,     0,     0,   202,   203,   204,   205,
     206,   207,   208,   209,   210,     0,   211,   212,   213,     0,
       0,     0,     0,  1194,     0,     0,  1195,  1196,  1197,  1198,
    1199,     0,  1200,  1201,  1202,     0,     0,    53,     0,    54,
      55,    56,   531,   532,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,  1195,  1196,  1197,  1198,  1199,
      62,  1200,  1201,  1202,     0,     0,    63,    64,     0,    51,
       0,     0,   378,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    66,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     533,     0,    70,     0,     0,    71,    52,    72,     0,    53,
       0,    54,    55,    56,    57,   380,     0,     0,    59,     0,
       0,    60,     0,     0,     0,    61,     0,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,     0,    63,    64,
       0,    51,     0,     0,   616,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   381,     0,     0,    65,    66,
       0,     0,     0,     0,    67,     0,     0,     0,     0,     0,
       0,     0,    68,    69,    70,     0,     0,    71,    52,    72,
       0,    53,     0,    54,    55,    56,    57,   380,     0,     0,
      59,     0,     0,    60,     0,     0,     0,    61,     0,     0,
       0,     0,     0,     0,    62,     0,     0,     0,     0,     0,
      63,    64,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   381,     0,     0,
      65,    66,     0,     0,     0,    51,    67,     0,     0,     0,
       0,     0,     0,     0,    68,    69,    70,     0,     0,    71,
      52,    72,     0,    53,     0,    54,    55,    56,    57,   380,
       0,     0,    59,     0,     0,    60,     0,     0,     0,    61,
       0,     0,    52,     0,     0,    53,    62,    54,    55,    56,
      57,    58,    63,    64,    59,     0,     0,    60,     0,     0,
       0,    61,     0,     0,     0,     0,     0,     0,    62,   381,
       0,     0,    65,    66,    63,    64,     0,    51,    67,     0,
       0,     0,     0,     0,     0,     0,    68,    69,    70,     0,
       0,    71,     0,    72,    65,    66,     0,     0,     0,     0,
      67,     0,     0,     0,     0,     0,     0,     0,    68,    69,
      70,     0,     0,    71,    52,    72,     0,    53,     0,    54,
      55,    56,    57,   429,     0,     0,    59,     0,     0,    60,
       0,     0,     0,    61,    51,     0,     0,     0,     0,     0,
      62,     0,     0,     0,     0,     0,    63,    64,     0,     0,
       0,     0,     0,     0,     0,     0,   138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    66,     0,     0,
       0,    52,    67,     0,    53,     0,    54,    55,    56,    57,
      68,    69,    70,    59,     0,    71,    60,    72,     0,     0,
      61,     0,     0,   139,     0,     0,    53,    62,    54,    55,
      56,    57,   788,    63,    64,   140,     0,     0,    60,     0,
       0,     0,    61,   138,     0,     0,     0,     0,     0,    62,
     491,     0,     0,    65,    66,    63,    64,     0,     0,    67,
       0,     0,     0,     0,     0,    51,     0,    68,    69,    70,
       0,     0,    71,     0,    72,    65,    66,     0,     0,     0,
     139,    67,     0,    53,     0,    54,    55,    56,    57,   141,
      69,    70,   140,     0,    71,    60,    72,     0,     0,    61,
       0,     0,    52,   175,   176,    53,    62,    54,    55,    56,
      57,     0,    63,    64,    59,     0,     0,    60,     0,   175,
     176,    61,     0,     0,     0,     0,     0,     0,    62,     0,
       0,     0,    65,    66,    63,    64,     0,     0,    67,     0,
       0,     0,     0,     0,     0,     0,   141,    69,    70,    57,
       0,    71,     0,    72,    65,    66,     0,     0,   175,   176,
      67,     0,     0,     0,     0,    57,   177,   178,    68,    69,
      70,     0,     0,    71,     0,    72,     0,     0,     0,     0,
       0,     0,   177,   178,     0,     0,   179,   180,     0,   181,
       0,     0,     0,     0,   182,     0,   183,     0,     0,    67,
       0,     0,   179,   180,    57,   181,     0,   807,    69,     0,
     182,  1049,   183,     0,     0,    67,     0,     0,     0,     0,
       0,   177,   178,   807,    69,     0,     0,  1051,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86,    87,
       0,   179,   180,     0,   181,     0,     0,    88,     0,   182,
       0,   183,     0,     0,    67,    89,     0,    90,    91,    92,
      93,     0,   807,    69,    94,     0,  1053,     0,    95,     0,
       0,     0,    96,    97,    98,    99,   100,   101,     0,     0,
       0,     0,     0,   102,   103,   104,   105,     0,     0,     0,
       0,     0,   106,   107,    86,    87,   108,   109,     0,     0,
       0,   110,     0,    88,     0,     0,   111,   112,     0,   113,
       0,    89,     0,    90,    91,    92,    93,   114,     0,     0,
      94,     0,     0,     0,    95,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   115,     0,   525,     0,     0,   102,
     103,   104,   105,     0,     0,     0,     0,     0,   106,   107,
      86,    87,   108,   109,     0,     0,     0,   110,     0,    88,
       0,     0,   111,   112,     0,   113,     0,    89,     0,    90,
      91,    92,    93,   114,     0,     0,    94,     0,     0,     0,
      95,     0,     0,     0,    96,    97,    98,    99,   100,   101,
     115,     0,   632,     0,     0,   102,   103,   104,   105,     0,
       0,     0,     0,     0,   106,   107,    86,    87,   108,   109,
       0,     0,     0,   110,     0,    88,     0,     0,   111,   112,
       0,   113,     0,    89,     0,    90,    91,    92,    93,   114,
       0,     0,    94,     0,     0,     0,    95,     0,     0,     0,
      96,    97,    98,    99,   100,   101,   115,     0,   637,     0,
       0,   102,   103,   104,   105,     0,     0,     0,     0,     0,
     106,   107,    86,    87,   108,   109,     0,     0,     0,   110,
       0,    88,     0,     0,   111,   112,     0,   113,     0,    89,
       0,    90,    91,    92,    93,   114,     0,     0,    94,     0,
       0,     0,    95,     0,     0,     0,    96,    97,    98,    99,
     100,   101,   115,     0,   707,     0,     0,   102,   103,   104,
     105,     0,     0,     0,     0,     0,   106,   107,    86,    87,
     108,   109,     0,     0,     0,   110,     0,    88,     0,     0,
     111,   112,     0,   113,     0,    89,     0,    90,    91,    92,
      93,   114,     0,     0,    94,     0,     0,     0,    95,     0,
       0,     0,    96,    97,    98,    99,   100,   101,   115,     0,
     821,     0,     0,   102,   103,   104,   105,     0,     0,     0,
       0,     0,   106,   107,    86,    87,   108,   109,     0,     0,
       0,   110,     0,    88,     0,     0,   111,   112,     0,   113,
       0,    89,     0,    90,    91,    92,    93,   114,     0,     0,
      94,     0,     0,     0,    95,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   115,     0,  1062,     0,     0,   102,
     103,   104,   105,     0,     0,     0,     0,     0,   106,   107,
      86,    87,   108,   109,     0,     0,     0,   110,     0,    88,
       0,     0,   111,   112,     0,   113,     0,    89,     0,    90,
      91,    92,    93,   114,     0,     0,    94,     0,     0,     0,
      95,     0,     0,    87,    96,    97,    98,    99,   100,   101,
     115,    88,  1160,     0,     0,   102,   103,   104,   105,     0,
       0,    90,    91,    92,   106,   107,     0,     0,   108,   109,
       0,     0,   249,   110,     0,     0,     0,     0,   111,   112,
     100,   113,     0,     0,     0,     0,     0,     0,     0,    87,
     105,     0,     0,     0,     0,     0,   106,    88,     0,     0,
       0,   109,     0,     0,     0,     0,   115,    90,    91,    92,
     111,   112,     0,   113,     0,    87,     0,     0,   249,     0,
       0,     0,     0,    88,     0,     0,   100,     0,  -144,     0,
       0,     0,     0,    90,    91,    92,   105,     0,   115,     0,
       0,     0,   106,     0,   249,     0,   108,   109,     0,     0,
       0,     0,   100,   258,     0,     0,   111,   112,    87,   113,
       0,     0,   105,     0,     0,     0,    88,     0,   106,     0,
       0,     0,     0,   109,     0,     0,    90,    91,    92,     0,
       0,     0,     0,   112,   115,   113,     0,   249,     0,     0,
       0,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,     0,     0,     0,     0,
     115,   106,     0,     0,     0,     0,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,     0,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-703)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,   381,   439,   128,   129,   130,   131,   474,   133,   108,
     135,   136,   137,   527,    28,   119,    58,   489,    45,   721,
     599,    28,   147,   148,   119,   216,   144,   152,   153,   588,
     119,   543,    12,    57,   548,   551,    56,   414,   229,   230,
     396,   553,    28,   265,   127,    46,   119,     6,   589,     8,
     277,    14,    61,    62,   496,   126,   615,     0,    10,    11,
     287,    45,   144,   146,   580,   581,   144,   583,   584,   585,
     586,   612,    73,   144,    12,   144,    87,    88,    16,    90,
      91,    92,   549,   144,    95,   552,   106,   145,   146,   100,
     669,   127,    14,   127,   105,   106,   130,   108,   109,   110,
      73,   112,   113,   144,   127,   119,   804,   805,   806,   130,
     146,    32,   119,   654,   144,    64,    65,    66,   498,    57,
     144,    70,   135,   146,   145,   126,   144,   128,   129,   130,
     131,   135,   133,   119,   135,   136,   137,    73,    21,    22,
     652,    93,   144,   127,   127,   144,   147,   148,   132,    32,
     134,   152,   153,   126,   626,   696,   129,    12,   135,   139,
      73,    16,   146,   146,   127,   149,   150,   151,   548,   273,
      32,   145,   146,   277,   130,   397,   692,   129,   273,   401,
     145,   146,   120,   287,   273,   212,   413,   146,   277,   145,
     126,   233,   126,   129,   319,     6,   134,     8,   287,    32,
     273,   139,    57,   144,   277,   127,   144,   127,   145,   788,
     432,   727,   589,   126,   287,   216,   129,   144,   167,   168,
     169,   170,   143,   144,   145,   127,   146,   228,   229,   230,
     231,   232,   233,   144,   706,   591,   237,    32,   249,   144,
     145,   708,   253,   128,   146,   130,   555,   289,   557,   558,
     559,   560,   561,   794,   137,   138,   139,   140,   141,   273,
     143,   144,   145,   277,   265,   120,   273,   129,   135,   127,
     277,   127,   221,   287,   126,   712,   128,   654,   130,   134,
     287,   127,   144,   145,   139,   144,   492,   273,   146,   129,
     146,   277,   241,   834,   500,   501,   502,   503,   504,   505,
     146,   287,   127,   127,   526,   777,   139,   140,   141,   413,
     143,   144,   145,   228,   229,   230,   231,   232,   319,   696,
     129,   146,   146,   127,   413,   127,   793,   127,   127,   796,
     797,   537,   144,   127,   335,   336,   126,   127,   380,   381,
     413,   855,   146,   144,   146,   787,   146,   146,   143,   144,
     145,  1049,   146,  1051,   791,  1053,    73,   144,  1056,  1057,
    1058,     6,   363,     8,   365,   366,   367,   368,   369,   144,
      87,   144,   127,    90,   127,   127,    93,   144,   379,    10,
      11,   382,   383,   127,   127,   127,   387,   429,   389,   127,
     699,   146,   109,   146,   146,   144,   397,   398,   129,   413,
     401,   129,   146,   146,   146,   611,   413,   144,   146,   410,
     145,   146,   618,    10,    11,    12,   638,   144,   145,    16,
     887,   126,   144,   128,   410,   130,   126,   413,   128,   430,
     130,   432,   474,   144,   126,   419,   128,   879,   130,  1141,
     882,   647,    73,    74,   144,   144,   145,   396,   363,   491,
     365,   366,   367,   368,   369,   146,   498,   834,   148,   127,
      57,   139,    93,    94,   379,    96,   145,   382,   383,   145,
     101,   129,   103,   474,   475,   855,   126,  1036,   128,   129,
     130,   135,   483,    21,    22,   123,   124,   125,   489,   126,
     146,   492,   144,   144,    32,   496,    93,   146,   128,   500,
     501,   502,   503,   504,   505,   506,   548,   549,   127,   145,
     552,   144,   145,   146,  1028,   146,   517,   144,   145,   146,
      94,    95,    96,   120,   146,   526,   144,   145,   146,   146,
     146,   146,   136,     2,   146,   136,   537,   134,   146,    10,
      11,    12,   139,   146,   146,    16,   532,   548,   549,   136,
     649,   552,   146,   146,   555,   146,   557,   558,   559,   560,
     561,   136,   146,   146,   146,   592,   593,   568,   483,   596,
     597,    40,    41,    42,    43,    44,   577,  1089,    47,  1046,
     139,   146,    73,   147,   126,   599,    57,   588,   589,   714,
     715,   813,   599,   127,   127,    10,    11,   127,   789,   137,
     138,   139,   140,   141,   127,   143,   144,   145,   144,   128,
     611,   612,   127,   599,   615,   144,   148,   618,   144,  1131,
     129,    92,    93,   144,   144,   626,   633,   144,   146,    57,
     144,   139,   148,    10,    11,    12,   126,   638,   649,    16,
     129,    10,   591,    10,    10,   656,   647,    10,  1028,   120,
     651,   128,   136,   654,   681,   669,   128,   127,    73,    74,
     148,   139,   669,   134,   650,  1132,   708,   147,   139,  1228,
    1229,  1230,   139,   144,   128,   128,   128,   128,    93,    94,
      57,    96,   151,   669,   147,   146,   101,   144,   103,   139,
     126,  1203,   148,  1135,   126,   696,   144,   681,   699,   144,
     144,   127,   145,   145,   127,   706,   127,   708,  1150,  1151,
    1152,   127,   130,   714,   715,   130,    93,   130,    32,   134,
     721,   135,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   120,   213,   144,   135,   135,   217,   144,
     135,   793,  1219,   144,   796,   797,   146,   134,    10,   146,
     146,    32,   139,   145,  1323,   127,   147,   144,   146,   148,
       4,  1330,   127,   144,   788,   148,   777,    10,   128,    10,
    1222,   788,    10,    10,  1226,   128,   787,   127,   789,  1231,
    1227,   144,   793,   794,    32,   796,   797,   804,   805,   806,
     146,   127,   788,   272,   148,   144,   147,   814,   146,  1276,
     147,   146,   813,   855,   147,   146,   148,   147,  1078,  1079,
    1080,  1081,  1082,   824,  1084,   139,   140,   141,   146,   143,
     144,   145,   135,   834,   146,   146,  1278,   146,   144,   823,
     135,   825,   135,   144,   135,   887,  1037,   127,   317,    46,
     877,   136,   146,   136,   838,   839,   840,   136,   842,   843,
     844,   845,   331,   332,  1306,   146,   137,   138,   139,   140,
     141,    68,   143,   144,   145,   136,   146,   144,   879,   126,
    1322,   882,   146,    80,   146,    10,   887,   146,   128,    10,
      79,    80,   128,   128,    10,   146,   128,   146,     6,   137,
     138,   139,   140,   141,   101,   143,   144,   145,   147,   146,
      10,    11,   127,    10,   111,   144,   146,   136,   144,   144,
     389,   144,  1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,
    1190,  1191,  1192,  1193,  1194,  1195,  1196,  1197,  1198,  1199,
    1200,   146,    50,   136,   141,   136,   143,   144,   146,   136,
      58,    16,    17,    18,    19,    20,    21,    22,   146,   428,
      68,    69,    70,   147,    32,   128,    10,    32,  1093,    10,
      11,    79,   441,    73,    74,   128,   144,   144,   144,    87,
     144,   146,   128,   128,   146,  1245,  1028,   146,   185,    97,
     991,   257,   713,    93,    94,   103,    96,   547,  1031,  1131,
     108,   101,  1089,   103,  1046,    73,  1203,   649,   277,   478,
     118,   650,   120,  1028,   824,   991,   855,   814,    -1,    87,
     489,   532,    90,   336,    -1,    93,    -1,  1028,    -1,   129,
      -1,    -1,    73,    74,    -1,  1036,  1037,   145,  1298,    -1,
      -1,   109,  1049,    -1,  1051,  1046,  1053,    -1,    -1,  1056,
    1057,  1058,    93,    94,    -1,    96,  1083,    -1,    -1,    -1,
     101,   258,   103,   260,   261,   262,   263,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,    -1,   143,   144,
     145,    -1,   279,    -1,    -1,   126,   283,    -1,    -1,    -1,
    1132,    -1,  1093,   290,    -1,   292,    -1,    -1,    -1,  1083,
      -1,    -1,    -1,   300,   301,    -1,    -1,   830,   577,    -1,
      -1,   300,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,  1132,    -1,    -1,  1135,    -1,    -1,    -1,    -1,   336,
    1141,    15,    16,    17,    18,    19,    20,    21,    22,  1150,
    1151,  1152,    -1,    -1,    -1,    -1,   625,   626,    32,    -1,
      -1,    -1,   631,    -1,    -1,    -1,    51,    -1,    53,    54,
      55,    -1,    -1,    -1,  1201,    -1,    -1,  1219,    -1,    -1,
      -1,    -1,    -1,    -1,  1168,  1169,  1170,  1171,  1172,  1173,
      -1,    -1,    -1,   390,    -1,    80,    81,    -1,   387,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   677,   678,
     679,   680,    -1,   682,    -1,   100,   101,    -1,  1219,    -1,
      -1,  1222,    -1,    -1,    -1,  1226,    -1,  1228,  1229,  1230,
    1231,   116,    -1,    -1,  1276,    -1,   121,   706,    -1,   436,
      -1,   430,    -1,  1270,  1271,    -1,  1273,  1274,    -1,    -1,
      -1,    -1,   721,    -1,    10,    11,    -1,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,    -1,   143,
     144,   145,    -1,    -1,   148,  1276,    -1,  1278,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1313,  1314,  1315,  1316,
      -1,    -1,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,   492,    -1,  1306,    -1,    32,   777,    -1,
     779,   500,   501,   502,   503,   504,   505,    73,    74,    -1,
      -1,  1322,  1323,    -1,    -1,    -1,    -1,    -1,    -1,  1330,
      19,    20,    21,    22,   531,    -1,   533,    93,    94,    -1,
      96,    -1,    -1,    32,    -1,   101,    -1,   103,   537,    -1,
     547,    -1,    -1,    -1,    -1,  1078,  1079,  1080,  1081,  1082,
      -1,  1084,    -1,    -1,    -1,    -1,   555,    -1,   557,   558,
     559,   560,   561,    -1,    -1,    -1,   845,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   856,   857,   858,
     859,   860,   861,   862,   863,   864,   865,   866,   867,   868,
     869,   870,   871,   872,   873,   874,   875,   876,    -1,   878,
     135,   136,   137,   138,   139,   140,   141,    -1,   143,   144,
     145,    -1,   611,    -1,    -1,    -1,    -1,    -1,    -1,   618,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    -1,    -1,   135,   136,   137,   138,
     139,   140,   141,    -1,   143,   144,   145,    -1,   647,  1182,
    1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,  1192,
    1193,  1194,  1195,  1196,  1197,  1198,  1199,  1200,    -1,    47,
      48,    -1,    -1,    51,    -1,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    -1,    63,    64,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
     699,    -1,    80,    81,    -1,    -1,   713,    -1,    -1,    -1,
      -1,    89,  1245,    91,    -1,    93,    -1,    -1,    -1,    -1,
      98,    -1,   100,   101,   102,    -1,    -1,   105,   106,    -1,
      -1,    -1,   110,    -1,    -1,   113,   114,   115,   116,    -1,
      -1,   119,  1021,   121,    -1,    -1,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    -1,   134,    -1,    -1,   137,
     138,   139,    -1,    -1,   142,  1298,   144,   145,    -1,    -1,
      -1,   149,    -1,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    -1,   790,    -1,    -1,    -1,    -1,    -1,    32,
      47,    -1,    -1,    -1,    51,    -1,    53,    54,    55,    -1,
     807,    -1,    59,   810,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
    1099,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    91,    -1,    93,    -1,    -1,    -1,
      -1,    98,    -1,   100,   101,   102,    -1,    -1,   105,    -1,
      -1,    -1,    -1,   110,    -1,    -1,   113,    -1,    -1,   116,
      -1,    -1,  1141,    -1,   121,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   134,    -1,    -1,
     137,   138,   139,    -1,    -1,   142,    -1,   144,   145,   132,
     133,   134,   149,    -1,   137,   138,   139,   140,   141,    -1,
     143,   144,   145,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,  1202,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,  1215,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    -1,    67,    -1,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,
      -1,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    -1,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    -1,    -1,    -1,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    -1,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    -1,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    -1,    -1,    -1,    87,    88,    89,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    -1,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,    -1,   148,   149,     3,     4,     5,
       6,    -1,     8,     9,    10,    11,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    47,    48,    80,    81,    51,    32,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    -1,    63,    64,    -1,
      -1,    67,    -1,   100,   101,    -1,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,   116,
      -1,    -1,    -1,    89,   121,    91,    -1,    93,    -1,    -1,
      -1,    97,    98,    -1,   100,   101,   102,    -1,    -1,   105,
     106,    -1,    -1,    -1,   110,    -1,    -1,   113,   114,   115,
     116,    -1,    -1,   119,    -1,   121,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    -1,    -1,    14,   134,    -1,
      -1,   137,   138,    -1,    -1,    -1,   142,    -1,   144,    -1,
      -1,    -1,    -1,   149,    -1,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,    -1,   143,   144,   145,
      47,    48,   148,    -1,    51,    -1,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    -1,    63,    64,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    91,    -1,    93,    -1,    -1,    -1,
      97,    98,    -1,   100,   101,   102,    -1,    -1,   105,   106,
      -1,    -1,    -1,   110,    -1,    -1,   113,   114,   115,   116,
      -1,    -1,   119,    -1,   121,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    -1,    10,    11,   134,    -1,    -1,
     137,   138,    -1,    -1,    -1,   142,    -1,   144,    -1,    -1,
      -1,    -1,   149,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    47,
      -1,    -1,    -1,    51,    -1,    53,    54,    55,    -1,    -1,
      -1,    59,    -1,    -1,    -1,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    73,    74,
      -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    91,    -1,    93,    -1,    -1,    93,    94,
      98,    96,   100,   101,   102,    -1,   101,   105,   103,    10,
      11,    -1,   110,    -1,    -1,   113,    -1,    -1,   116,     3,
       4,     5,     6,   121,     8,     9,    10,    11,    -1,    -1,
      -1,   126,    -1,    -1,    -1,    -1,   134,    -1,    -1,   137,
     138,   139,    -1,    -1,   142,    -1,   144,   145,   146,   133,
     134,   149,    -1,   137,   138,   139,   140,   141,    -1,   143,
     144,   145,    -1,    47,    -1,    -1,    -1,    51,    -1,    53,
      54,    55,    73,    74,    -1,    59,    -1,    -1,    -1,    63,
      64,    51,    -1,    53,    54,    55,    -1,    -1,    72,    73,
      74,    -1,    93,    94,    -1,    96,    80,    81,    -1,    -1,
     101,    -1,   103,    -1,    -1,    89,    -1,    91,    -1,    93,
      80,    81,    -1,    -1,    98,    -1,   100,   101,   102,    -1,
      -1,   105,    -1,    -1,    -1,   126,   110,    10,    11,   113,
     100,   101,   116,     3,     4,     5,     6,   121,     8,     9,
      10,    11,   126,    -1,    -1,    -1,   116,    -1,    -1,    -1,
     134,   121,    -1,   137,   138,   139,    -1,    -1,   142,    -1,
     144,   145,    -1,    -1,    -1,   149,    -1,    -1,    51,    -1,
      53,    54,    55,    -1,   144,    -1,    -1,    47,    -1,    -1,
      63,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    59,
      -1,    74,    -1,    63,    64,    -1,    -1,    80,    81,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      80,    81,    51,    -1,    53,    54,    55,   100,   101,    89,
      -1,    91,    -1,    93,    63,    -1,    -1,    -1,    98,    -1,
     100,   101,   102,   116,    -1,   105,   119,    -1,   121,    -1,
     110,    80,    81,   113,    -1,    -1,   116,     3,     4,     5,
       6,   121,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,   100,   101,    -1,   134,    -1,    -1,   137,   138,   139,
      -1,    -1,   142,    -1,   144,   145,   146,   116,    -1,   149,
      -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    59,    -1,   144,    -1,    63,    64,    51,
      -1,    53,    54,    55,    -1,    -1,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    80,    81,    51,    -1,    53,    54,
      55,    -1,    -1,    89,    -1,    91,    -1,    93,    80,    81,
      -1,    -1,    98,    -1,   100,   101,   102,    -1,    -1,   105,
      -1,    10,    11,    -1,   110,    80,    81,   113,   100,   101,
     116,     3,     4,     5,     6,   121,     8,     9,    10,    11,
     126,    -1,    -1,    -1,   116,   100,   101,    -1,   134,   121,
      -1,   137,   138,   139,    -1,    -1,   142,    -1,   144,   145,
      -1,   116,    -1,   149,    -1,    -1,   121,    -1,    -1,    -1,
      -1,    -1,   144,    -1,    -1,    47,    -1,    -1,    -1,    51,
      -1,    53,    54,    55,    73,    74,    -1,    59,    -1,   144,
      -1,    63,    64,    51,    -1,    53,    54,    55,    -1,    88,
      72,    73,    74,    -1,    93,    94,    -1,    96,    80,    81,
      -1,    -1,   101,    -1,   103,    -1,    -1,    89,    -1,    91,
      -1,    93,    80,    81,    -1,    -1,    98,    -1,   100,   101,
     102,    -1,    -1,   105,    -1,    -1,    -1,    -1,   110,    -1,
      -1,   113,   100,   101,   116,     3,     4,     5,     6,   121,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,   116,    -1,
      -1,    -1,   134,   121,    -1,   137,   138,   139,    -1,    -1,
     142,    -1,   144,   145,   146,    -1,    -1,   149,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    51,    -1,    53,    54,    55,    -1,    -1,
      -1,    59,    -1,    -1,    -1,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    91,    -1,    93,    -1,    -1,    -1,    -1,
      98,    -1,   100,   101,   102,    -1,    -1,   105,    -1,    -1,
      -1,    -1,   110,    -1,    -1,   113,    -1,    -1,   116,     3,
       4,     5,     6,   121,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    10,    11,    -1,   134,    -1,    -1,   137,
     138,   139,    -1,    -1,   142,    -1,   144,   145,    -1,    -1,
      -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    51,    59,    53,    54,    55,    56,
      64,    -1,    -1,    60,    -1,    -1,    63,    -1,    72,    73,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    74,     0,    -1,
      -1,    -1,    -1,    80,    81,    -1,    -1,    91,    -1,    93,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,   102,    -1,
      -1,   105,    -1,   100,   101,    -1,   110,    -1,    -1,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,   115,   116,
      -1,    -1,   119,    -1,   121,    -1,    -1,    49,    50,    -1,
     134,    -1,    -1,   137,   138,   139,    58,    -1,   142,    -1,
     144,   145,    -1,    -1,    66,   149,    68,    69,    70,    71,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    -1,    -1,
      -1,    83,    84,    85,    86,    87,    88,    19,    20,    21,
      22,    -1,    94,    95,    96,    97,    -1,    -1,    -1,    -1,
      32,   103,   104,    -1,    -1,   107,   108,    -1,    -1,    -1,
     112,    -1,    -1,    -1,    -1,   117,   118,    -1,   120,     6,
      -1,    -1,    -1,    -1,    -1,    -1,   128,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    10,    11,    -1,
      -1,    -1,    -1,   145,    -1,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    89,    -1,    -1,   137,   138,   139,   140,   141,
      -1,   143,   144,   145,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    94,    -1,    96,    -1,    -1,    -1,    -1,   101,    -1,
     103,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,
     127,   114,   115,   130,    -1,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,    -1,   144,   145,    10,
      11,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,    -1,   143,   144,   145,
      10,    11,   148,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      51,    -1,    53,    54,    55,    56,    57,    -1,    -1,    60,
      -1,    -1,    63,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    48,    80,
      81,    51,    -1,    53,    54,    55,    56,    57,    -1,    -1,
      60,    92,    -1,    63,    -1,    -1,    -1,    67,    -1,   100,
     101,    -1,    -1,    -1,    74,   106,    -1,    -1,    -1,    -1,
      80,    81,    -1,   114,   115,   116,    10,    11,   119,    -1,
     121,    -1,    92,    -1,    -1,   126,    -1,    -1,    -1,    -1,
     100,   101,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,
      -1,   142,    -1,    -1,   114,   115,   116,    -1,    -1,   119,
      -1,   121,    -1,    -1,    48,    -1,    -1,    51,    -1,    53,
      54,    55,    56,    57,    -1,    -1,    60,    -1,    -1,    63,
      -1,    -1,   142,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    80,    81,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    32,   100,   101,    -1,    -1,
      -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     114,   115,   116,    -1,    -1,   119,    -1,   121,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,   142,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     127,    -1,    32,    -1,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,    -1,   143,   144,   145,   146,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,    -1,   143,   144,   145,   146,
      -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,    -1,   143,   144,   145,
     146,    -1,    -1,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,    -1,   143,   144,   145,   146,    -1,
      -1,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,    -1,   143,   144,   145,   146,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,    -1,   143,   144,
     145,   146,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,   129,    -1,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,    -1,   143,   144,   145,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,    32,    -1,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,    -1,
     143,   144,   145,   127,    -1,    -1,    -1,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,    -1,   143,
     144,   145,    -1,   129,    -1,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,    -1,   143,   144,   145,
      -1,    -1,    -1,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,    -1,   143,   144,   145,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,    -1,   143,   144,   145,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      17,    18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,   129,    -1,   131,   132,   133,   134,    -1,    -1,
     137,   138,   139,   140,   141,    -1,   143,   144,   145,    -1,
      -1,    -1,    -1,    -1,    11,    -1,    -1,    14,    -1,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,   131,   132,   133,   134,
      -1,    32,   137,   138,   139,   140,   141,    -1,   143,   144,
     145,    48,    -1,    -1,    51,    -1,    53,    54,    55,    56,
      57,    -1,    -1,    60,    -1,    -1,    63,   132,   133,   134,
      67,    -1,   137,   138,   139,   140,   141,    74,   143,   144,
     145,    -1,    -1,    80,    81,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,    -1,   143,   144,   145,    -1,
      97,    -1,    -1,   100,   101,    10,    11,    -1,    -1,   106,
      17,    18,    19,    20,    21,    22,    -1,   114,   115,   116,
      -1,    -1,   119,    -1,   121,    32,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,   134,    -1,    -1,
      -1,    32,   139,   134,   135,   136,   137,   138,   139,   140,
     141,    56,   143,   144,   145,    17,    18,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,
      95,    96,    -1,    -1,    -1,    -1,   101,    -1,   103,    -1,
      -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,
     115,    -1,    -1,   118,    -1,    -1,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   133,   134,   135,   136,
     137,   138,   139,   140,   141,    -1,   143,   144,   145,    -1,
      -1,    -1,    -1,   134,    -1,    -1,   137,   138,   139,   140,
     141,    -1,   143,   144,   145,    -1,    -1,    51,    -1,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    -1,   137,   138,   139,   140,   141,
      74,   143,   144,   145,    -1,    -1,    80,    81,    -1,    11,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     114,    -1,   116,    -1,    -1,   119,    48,   121,    -1,    51,
      -1,    53,    54,    55,    56,    57,    -1,    -1,    60,    -1,
      -1,    63,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    80,    81,
      -1,    11,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,   100,   101,
      -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   114,   115,   116,    -1,    -1,   119,    48,   121,
      -1,    51,    -1,    53,    54,    55,    56,    57,    -1,    -1,
      60,    -1,    -1,    63,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      80,    81,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,
     100,   101,    -1,    -1,    -1,    11,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,   115,   116,    -1,    -1,   119,
      48,   121,    -1,    51,    -1,    53,    54,    55,    56,    57,
      -1,    -1,    60,    -1,    -1,    63,    -1,    -1,    -1,    67,
      -1,    -1,    48,    -1,    -1,    51,    74,    53,    54,    55,
      56,    57,    80,    81,    60,    -1,    -1,    63,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    74,    97,
      -1,    -1,   100,   101,    80,    81,    -1,    11,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,   115,   116,    -1,
      -1,   119,    -1,   121,   100,   101,    -1,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,   115,
     116,    -1,    -1,   119,    48,   121,    -1,    51,    -1,    53,
      54,    55,    56,    57,    -1,    -1,    60,    -1,    -1,    63,
      -1,    -1,    -1,    67,    11,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,    -1,
      -1,    48,   106,    -1,    51,    -1,    53,    54,    55,    56,
     114,   115,   116,    60,    -1,   119,    63,   121,    -1,    -1,
      67,    -1,    -1,    48,    -1,    -1,    51,    74,    53,    54,
      55,    56,    57,    80,    81,    60,    -1,    -1,    63,    -1,
      -1,    -1,    67,    11,    -1,    -1,    -1,    -1,    -1,    74,
      97,    -1,    -1,   100,   101,    80,    81,    -1,    -1,   106,
      -1,    -1,    -1,    -1,    -1,    11,    -1,   114,   115,   116,
      -1,    -1,   119,    -1,   121,   100,   101,    -1,    -1,    -1,
      48,   106,    -1,    51,    -1,    53,    54,    55,    56,   114,
     115,   116,    60,    -1,   119,    63,   121,    -1,    -1,    67,
      -1,    -1,    48,    10,    11,    51,    74,    53,    54,    55,
      56,    -1,    80,    81,    60,    -1,    -1,    63,    -1,    10,
      11,    67,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,   100,   101,    80,    81,    -1,    -1,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,   115,   116,    56,
      -1,   119,    -1,   121,   100,   101,    -1,    -1,    10,    11,
     106,    -1,    -1,    -1,    -1,    56,    73,    74,   114,   115,
     116,    -1,    -1,   119,    -1,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    -1,    -1,    93,    94,    -1,    96,
      -1,    -1,    -1,    -1,   101,    -1,   103,    -1,    -1,   106,
      -1,    -1,    93,    94,    56,    96,    -1,   114,   115,    -1,
     101,   118,   103,    -1,    -1,   106,    -1,    -1,    -1,    -1,
      -1,    73,    74,   114,   115,    -1,    -1,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      -1,    93,    94,    -1,    96,    -1,    -1,    58,    -1,   101,
      -1,   103,    -1,    -1,   106,    66,    -1,    68,    69,    70,
      71,    -1,   114,   115,    75,    -1,   118,    -1,    79,    -1,
      -1,    -1,    83,    84,    85,    86,    87,    88,    -1,    -1,
      -1,    -1,    -1,    94,    95,    96,    97,    -1,    -1,    -1,
      -1,    -1,   103,   104,    49,    50,   107,   108,    -1,    -1,
      -1,   112,    -1,    58,    -1,    -1,   117,   118,    -1,   120,
      -1,    66,    -1,    68,    69,    70,    71,   128,    -1,    -1,
      75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,    84,
      85,    86,    87,    88,   145,    -1,   147,    -1,    -1,    94,
      95,    96,    97,    -1,    -1,    -1,    -1,    -1,   103,   104,
      49,    50,   107,   108,    -1,    -1,    -1,   112,    -1,    58,
      -1,    -1,   117,   118,    -1,   120,    -1,    66,    -1,    68,
      69,    70,    71,   128,    -1,    -1,    75,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    83,    84,    85,    86,    87,    88,
     145,    -1,   147,    -1,    -1,    94,    95,    96,    97,    -1,
      -1,    -1,    -1,    -1,   103,   104,    49,    50,   107,   108,
      -1,    -1,    -1,   112,    -1,    58,    -1,    -1,   117,   118,
      -1,   120,    -1,    66,    -1,    68,    69,    70,    71,   128,
      -1,    -1,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      83,    84,    85,    86,    87,    88,   145,    -1,   147,    -1,
      -1,    94,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,
     103,   104,    49,    50,   107,   108,    -1,    -1,    -1,   112,
      -1,    58,    -1,    -1,   117,   118,    -1,   120,    -1,    66,
      -1,    68,    69,    70,    71,   128,    -1,    -1,    75,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    83,    84,    85,    86,
      87,    88,   145,    -1,   147,    -1,    -1,    94,    95,    96,
      97,    -1,    -1,    -1,    -1,    -1,   103,   104,    49,    50,
     107,   108,    -1,    -1,    -1,   112,    -1,    58,    -1,    -1,
     117,   118,    -1,   120,    -1,    66,    -1,    68,    69,    70,
      71,   128,    -1,    -1,    75,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    83,    84,    85,    86,    87,    88,   145,    -1,
     147,    -1,    -1,    94,    95,    96,    97,    -1,    -1,    -1,
      -1,    -1,   103,   104,    49,    50,   107,   108,    -1,    -1,
      -1,   112,    -1,    58,    -1,    -1,   117,   118,    -1,   120,
      -1,    66,    -1,    68,    69,    70,    71,   128,    -1,    -1,
      75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,    84,
      85,    86,    87,    88,   145,    -1,   147,    -1,    -1,    94,
      95,    96,    97,    -1,    -1,    -1,    -1,    -1,   103,   104,
      49,    50,   107,   108,    -1,    -1,    -1,   112,    -1,    58,
      -1,    -1,   117,   118,    -1,   120,    -1,    66,    -1,    68,
      69,    70,    71,   128,    -1,    -1,    75,    -1,    -1,    -1,
      79,    -1,    -1,    50,    83,    84,    85,    86,    87,    88,
     145,    58,   147,    -1,    -1,    94,    95,    96,    97,    -1,
      -1,    68,    69,    70,   103,   104,    -1,    -1,   107,   108,
      -1,    -1,    79,   112,    -1,    -1,    -1,    -1,   117,   118,
      87,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      97,    -1,    -1,    -1,    -1,    -1,   103,    58,    -1,    -1,
      -1,   108,    -1,    -1,    -1,    -1,   145,    68,    69,    70,
     117,   118,    -1,   120,    -1,    50,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    87,    -1,   135,    -1,
      -1,    -1,    -1,    68,    69,    70,    97,    -1,   145,    -1,
      -1,    -1,   103,    -1,    79,    -1,   107,   108,    -1,    -1,
      -1,    -1,    87,    88,    -1,    -1,   117,   118,    50,   120,
      -1,    -1,    97,    -1,    -1,    -1,    58,    -1,   103,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    68,    69,    70,    -1,
      -1,    -1,    -1,   118,   145,   120,    -1,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,    -1,    -1,
     145,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   118,    -1,   120,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   145
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   123,   124,   125,   151,   152,   258,     3,     4,     5,
       6,     8,     9,    10,    11,    47,    51,    53,    54,    55,
      59,    63,    64,    72,    73,    74,    80,    81,    89,    91,
      93,    98,   100,   101,   102,   105,   110,   113,   116,   121,
     134,   137,   138,   139,   142,   144,   145,   149,   248,   249,
     257,    11,    48,    51,    53,    54,    55,    56,    57,    60,
      63,    67,    74,    80,    81,   100,   101,   106,   114,   115,
     116,   119,   121,   212,   216,   217,   219,   225,   226,   230,
     231,   236,   237,   238,   239,     0,    49,    50,    58,    66,
      68,    69,    70,    71,    75,    79,    83,    84,    85,    86,
      87,    88,    94,    95,    96,    97,   103,   104,   107,   108,
     112,   117,   118,   120,   128,   145,   155,   157,   158,   160,
     163,   164,   186,   232,   235,   258,   144,   144,   144,   144,
     144,   144,   135,   144,   135,   144,   144,   144,    11,    48,
      60,   114,   214,   230,   231,   236,   135,   144,   144,   144,
     135,   144,   144,   144,   248,   248,   248,   248,   248,    11,
      51,    53,    54,    55,    63,    74,    80,    81,   100,   101,
     116,   121,   216,   246,   248,    10,    11,    73,    74,    93,
      94,    96,   101,   103,   130,   134,   252,   253,   255,   258,
     248,    15,    16,    17,    18,    19,    20,    21,    22,    32,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   143,   144,   145,     6,     8,   212,   144,    56,   106,
      63,    81,   237,   237,   237,   255,   237,    12,    16,    57,
     120,   134,   139,   144,   210,   211,   258,   126,    10,    11,
      93,   129,   256,    10,    11,    93,   126,   255,   256,    79,
     160,   160,   160,     6,   160,   160,   129,   159,    88,   160,
     144,   144,   144,   144,   160,   126,   255,   129,   129,   129,
     160,   160,   144,   160,   163,   187,   160,   160,   169,    88,
     255,   160,   160,   145,    10,    11,    48,    57,    60,    92,
     114,   126,   142,   174,   177,   213,   215,   217,   219,   225,
     230,   231,   236,   245,   246,   258,   216,   245,   245,   245,
     245,   216,   245,   216,   245,   245,   245,   144,   255,   144,
     255,   255,   216,   245,   245,   216,   216,   216,   248,   245,
     245,   146,   127,   146,   255,   148,   127,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   146,   246,
     248,   211,   248,   139,    12,    16,    57,   120,   134,   139,
     210,   258,   210,   211,   210,   211,   210,   210,    14,    16,
      57,    97,   134,   139,   196,   197,   206,   212,   258,   145,
     228,   229,   258,    11,   227,   237,   129,   218,   220,   160,
     157,   126,   255,   255,   255,   255,   255,   152,   126,   248,
     135,    10,    11,    57,   177,   213,   215,   255,   128,   130,
     161,   162,   255,   144,   144,    10,    11,   215,   144,    57,
     212,   255,   156,   255,   126,   128,   129,   130,   202,   126,
     128,   130,   203,   128,   165,   255,   256,   255,   146,   146,
     146,   146,   146,   146,   136,   146,   136,   146,   146,   146,
     248,   245,   136,   146,   146,   146,   136,   146,   146,   146,
     146,   248,   248,    57,   144,   183,   258,   252,   129,   146,
     148,   146,   210,   139,   210,   210,   210,   210,   210,   145,
     210,    97,   212,   206,   210,   210,   146,    14,   127,    12,
      16,    57,   120,   134,   139,   144,   209,   256,   258,   244,
     248,   258,   255,   147,   227,   152,    73,   221,   258,   152,
     126,   127,   127,   127,   127,   147,   233,   127,   146,    10,
      11,    56,    57,   114,   188,   189,   190,   191,   236,   258,
     144,   215,   203,   170,   128,   216,   148,   127,   144,   175,
      12,   139,   176,   166,   248,   212,    12,    16,    57,   120,
     134,   139,   208,   256,   258,   152,   144,   240,   241,   153,
     154,   255,    61,    62,   240,    61,    62,   126,   248,    12,
      16,    57,    92,   120,   134,   139,   144,   167,   192,   194,
     256,   129,   144,   144,   146,   146,   144,   144,   196,    32,
      73,    87,    90,    93,   109,   195,   258,   248,   210,   244,
     146,   212,   209,   146,   146,   183,    14,   206,   139,   209,
     209,   209,   209,   209,   209,   130,   145,   201,   258,   148,
     127,   130,   147,   129,   222,   223,   258,   147,   234,    10,
      10,    10,    10,   152,   257,   128,   255,   191,   255,   136,
     127,   209,   171,   172,   194,   128,   148,   161,     3,     4,
       5,     9,    10,    14,    47,    59,    64,    72,    73,    89,
      91,    93,    98,   102,   105,   110,   113,   134,   137,   138,
     142,   144,   149,   198,   199,   206,   207,   250,   251,   257,
     258,   196,   139,   192,   196,   168,   194,   146,   208,   139,
     208,   208,   208,   208,   208,   144,   145,   147,   178,   147,
     242,   258,   126,   127,   126,   144,   128,   128,   147,   128,
     128,   126,   204,   205,   248,   258,   128,   139,   192,   192,
       6,    15,    16,    17,    18,    19,    20,    21,    22,    32,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    62,    89,   127,   130,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   144,   145,   149,
     184,   192,   192,   192,   192,   129,   144,   145,   195,   130,
     201,   203,   227,   246,   246,   246,   246,   146,    57,   214,
     144,   126,   148,   144,   209,   201,   144,   144,   195,   209,
     146,   248,   244,   248,    94,    95,    96,   114,   118,   224,
     231,   254,   255,   126,   127,   152,   127,   146,   127,   127,
     127,   147,   146,   130,   209,   130,   163,   185,   186,   190,
     130,   200,   258,   173,   194,   201,   203,   160,   144,   135,
     135,   214,   135,   144,   135,   144,   248,   248,   248,   248,
     216,   246,   248,   146,    14,   127,    15,    16,    17,    18,
      19,    20,    21,    22,    32,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   143,   144,   145,   146,
     192,   146,   146,   201,   203,   144,   208,   181,   244,   196,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    67,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    87,    88,    89,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   148,   149,   243,   240,   154,   245,   245,   204,
     147,   127,   192,    10,   146,   148,   146,     4,   193,   244,
     248,   127,   146,   146,   146,   146,   183,   214,   211,   146,
     255,   240,   196,   201,   196,   196,   144,   148,   127,   118,
     254,   118,   254,   118,   254,   255,    94,    95,    96,   255,
     152,   224,   147,    10,   128,    10,    10,    10,   128,   216,
     200,   216,    47,    59,    64,    98,   102,   105,   134,   137,
     138,   139,   142,   144,   149,   247,   249,   201,   203,   127,
     216,   216,   216,   144,   216,   216,   216,   216,   248,   146,
     146,    14,   207,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   146,   246,   248,   183,   146,   144,
     183,   127,   182,   196,   148,   146,   242,   147,   147,   146,
     147,   126,   248,   198,   148,   167,   195,   211,   146,   147,
     146,   146,   146,   196,   254,   254,   254,   254,   254,   254,
     147,   127,   146,   127,   146,   146,   127,   146,   144,   135,
     135,   135,   144,   135,   247,   247,   247,   247,   247,   216,
     246,   247,    15,    16,    17,    18,    19,    20,    21,    22,
      32,   131,   132,   133,   134,   137,   138,   139,   140,   141,
     143,   144,   145,   127,   172,   146,   136,   136,   245,   136,
     146,   136,   146,   146,   248,   129,   146,   148,   144,   179,
     168,   196,   146,   183,   147,   204,   146,   126,   183,   183,
     183,   146,    10,   128,    10,   128,   128,    10,   128,   216,
     216,   216,   216,   216,   216,   146,   146,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   146,   246,   248,   173,
     144,   144,   146,   144,   144,   248,   180,   196,   146,   183,
     147,   183,   240,   195,   195,   195,   183,   146,   127,   127,
     146,   146,   136,   136,   136,   146,   136,   247,   129,   146,
     148,   246,   246,   246,   246,   196,   146,   183,   147,   128,
      10,    10,   128,   144,   144,   144,   144,   247,   146,   146,
     146,   146,   146,   183,   146,   146,   246,   246,   246,   246,
     183,   195,   128,   128,   146,   146,   146,   146,   195
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
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
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
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
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc = yyloc_default;


    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

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
        case 3:
/* Line 1792 of yacc.c  */
#line 426 "dtool/src/cppparser/cppBison.yxx"
    {
  current_expr = (yyvsp[(2) - (2)].u.expr);
}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 430 "dtool/src/cppparser/cppBison.yxx"
    {
  current_type = (yyvsp[(2) - (2)].u.type);
}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 448 "dtool/src/cppparser/cppBison.yxx"
    {
  delete (yyvsp[(3) - (4)].u.expr);
}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 452 "dtool/src/cppparser/cppBison.yxx"
    {
  delete (yyvsp[(3) - (4)].u.expr);
}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 464 "dtool/src/cppparser/cppBison.yxx"
    {
  push_storage_class((current_storage_class & ~CPPInstance::SC_c_binding) |
                     ((yyvsp[(1) - (2)].u.integer) & CPPInstance::SC_c_binding));
}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 469 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_storage_class();
}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 482 "dtool/src/cppparser/cppBison.yxx"
    {
  if (publish_nest_level != 0) {
    yyerror("Unclosed __begin_publish", publish_loc);
    publish_nest_level = 0;
    current_scope->set_current_vis(V_public);
  }

  publish_previous = current_scope->get_current_vis();
  publish_loc = (yylsp[(1) - (1)]);
  publish_nest_level++;
  current_scope->set_current_vis(V_published);
}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 495 "dtool/src/cppparser/cppBison.yxx"
    {
  if (publish_nest_level != 1) {
    yyerror("Unmatched __end_publish", (yylsp[(1) - (1)]));
  } else {
    current_scope->set_current_vis(publish_previous);
  }
  publish_nest_level = 0;
}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 504 "dtool/src/cppparser/cppBison.yxx"
    {
  current_scope->set_current_vis(V_published);
}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 508 "dtool/src/cppparser/cppBison.yxx"
    {
  if (publish_nest_level > 0) {
    current_scope->set_current_vis(V_published);
  } else {
    current_scope->set_current_vis(V_public);
  }
}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 516 "dtool/src/cppparser/cppBison.yxx"
    {
  current_scope->set_current_vis(V_protected);
}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 520 "dtool/src/cppparser/cppBison.yxx"
    {
  current_scope->set_current_vis(V_private);
}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 524 "dtool/src/cppparser/cppBison.yxx"
    {

  CPPDeclaration *getter = (yyvsp[(5) - (7)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == (CPPDeclaration *)NULL || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[(5) - (7)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (7)]));
  }

  CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[(3) - (7)].u.identifier), getter->as_function_group(), NULL, current_scope, (yylsp[(1) - (7)]).file);
  current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[(1) - (7)]));
}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 535 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPDeclaration *getter = (yyvsp[(5) - (9)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == (CPPDeclaration *)NULL || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[(5) - (9)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (9)]));

  } else {
    CPPDeclaration *setter = (yyvsp[(7) - (9)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    CPPFunctionGroup *setter_func = NULL;

    if (setter == (CPPDeclaration *)NULL || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("Reference to non-existent or invalid setter: " + (yyvsp[(7) - (9)].u.identifier)->get_fully_scoped_name(), (yylsp[(7) - (9)]));
    } else {
      setter_func = setter->as_function_group();
    }

    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[(3) - (9)].u.identifier), getter->as_function_group(),
                                                         setter_func, current_scope, (yylsp[(1) - (9)]).file);
    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[(1) - (9)]));
  }
}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 556 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPDeclaration *getter = (yyvsp[(5) - (11)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == (CPPDeclaration *)NULL || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[(5) - (11)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (11)]));

  } else {
    CPPDeclaration *setter = (yyvsp[(7) - (11)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    CPPFunctionGroup *setter_func = NULL;

    if (setter == (CPPDeclaration *)NULL || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("Reference to non-existent or invalid setter: " + (yyvsp[(7) - (11)].u.identifier)->get_fully_scoped_name(), (yylsp[(7) - (11)]));
    } else {
      setter_func = setter->as_function_group();
    }

    CPPDeclaration *deleter = (yyvsp[(9) - (11)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (deleter == (CPPDeclaration *)NULL || deleter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid delete method: " + (yyvsp[(9) - (11)].u.identifier)->get_fully_scoped_name(), (yylsp[(9) - (11)]));
      deleter = NULL;
    }

    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[(3) - (11)].u.identifier), getter->as_function_group(),
                                                         setter_func, current_scope, (yylsp[(1) - (11)]).file);
    if (deleter) {
      make_property->_del_function = deleter->as_function_group();
    }
    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[(1) - (11)]));
  }
}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 586 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPDeclaration *length_getter = (yyvsp[(5) - (9)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == (CPPDeclaration *)NULL || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[(5) - (9)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (9)]));
    length_getter = NULL;
  }

  CPPDeclaration *getter = (yyvsp[(7) - (9)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == (CPPDeclaration *)NULL || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[(7) - (9)].u.identifier)->get_fully_scoped_name(), (yylsp[(7) - (9)]));
  }

  CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[(3) - (9)].u.identifier), getter->as_function_group(), NULL, current_scope, (yylsp[(1) - (9)]).file);
  make_property->_length_function = length_getter->as_function_group();
  current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[(1) - (9)]));
}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 603 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPDeclaration *length_getter = (yyvsp[(5) - (11)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == (CPPDeclaration *)NULL || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[(5) - (11)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (11)]));
    length_getter = NULL;
  }

  CPPDeclaration *getter = (yyvsp[(7) - (11)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == (CPPDeclaration *)NULL || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[(7) - (11)].u.identifier)->get_fully_scoped_name(), (yylsp[(7) - (11)]));

  } else {
    CPPDeclaration *setter = (yyvsp[(9) - (11)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    CPPFunctionGroup *setter_func = NULL;

    if (setter == (CPPDeclaration *)NULL || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("Reference to non-existent or invalid setter: " + (yyvsp[(9) - (11)].u.identifier)->get_fully_scoped_name(), (yylsp[(9) - (11)]));
    } else {
      setter_func = setter->as_function_group();
    }

    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[(3) - (11)].u.identifier), getter->as_function_group(),
                                                         setter_func, current_scope, (yylsp[(1) - (11)]).file);
    make_property->_length_function = length_getter->as_function_group();
    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[(1) - (11)]));
  }
}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 631 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPDeclaration *length_getter = (yyvsp[(5) - (13)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == (CPPDeclaration *)NULL || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[(5) - (13)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (13)]));
    length_getter = NULL;
  }

  CPPDeclaration *getter = (yyvsp[(7) - (13)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == (CPPDeclaration *)NULL || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[(7) - (13)].u.identifier)->get_fully_scoped_name(), (yylsp[(7) - (13)]));

  } else {
    CPPDeclaration *setter = (yyvsp[(9) - (13)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    CPPFunctionGroup *setter_func = NULL;

    if (setter == (CPPDeclaration *)NULL || setter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("Reference to non-existent or invalid setter: " + (yyvsp[(9) - (13)].u.identifier)->get_fully_scoped_name(), (yylsp[(9) - (13)]));
    } else {
      setter_func = setter->as_function_group();
    }

    CPPDeclaration *deleter = (yyvsp[(11) - (13)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
    if (deleter == (CPPDeclaration *)NULL || deleter->get_subtype() != CPPDeclaration::ST_function_group) {
      yyerror("reference to non-existent or invalid delete method: " + (yyvsp[(11) - (13)].u.identifier)->get_fully_scoped_name(), (yylsp[(11) - (13)]));
      deleter = NULL;
    }

    CPPMakeProperty *make_property = new CPPMakeProperty((yyvsp[(3) - (13)].u.identifier), getter->as_function_group(),
                                                         setter_func, current_scope, (yylsp[(1) - (13)]).file);
    make_property->_length_function = length_getter->as_function_group();
    if (deleter) {
      make_property->_del_function = deleter->as_function_group();
    }
    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[(1) - (13)]));
  }
}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 668 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPDeclaration *hasser = (yyvsp[(5) - (9)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (hasser == (CPPDeclaration *)NULL || hasser->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid has-function: " + (yyvsp[(5) - (9)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (9)]));
  }

  CPPDeclaration *getter = (yyvsp[(7) - (9)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == (CPPDeclaration *)NULL || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[(7) - (9)].u.identifier)->get_fully_scoped_name(), (yylsp[(7) - (9)]));
  }

  if (hasser && getter) {
    CPPMakeProperty *make_property;
    make_property = new CPPMakeProperty((yyvsp[(3) - (9)].u.identifier),
                                        hasser->as_function_group(),
                                        getter->as_function_group(),
                                        NULL, NULL,
                                        current_scope, (yylsp[(1) - (9)]).file);
    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[(1) - (9)]));
  }
}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 690 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPDeclaration *hasser = (yyvsp[(5) - (13)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (hasser == (CPPDeclaration *)NULL || hasser->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid has-function: " + (yyvsp[(5) - (13)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (13)]));
  }

  CPPDeclaration *getter = (yyvsp[(7) - (13)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (getter == (CPPDeclaration *)NULL || getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid getter: " + (yyvsp[(7) - (13)].u.identifier)->get_fully_scoped_name(), (yylsp[(7) - (13)]));
  }

  CPPDeclaration *setter = (yyvsp[(9) - (13)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (setter == (CPPDeclaration *)NULL || setter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid setter: " + (yyvsp[(9) - (13)].u.identifier)->get_fully_scoped_name(), (yylsp[(9) - (13)]));
  }

  CPPDeclaration *clearer = (yyvsp[(11) - (13)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (clearer == (CPPDeclaration *)NULL || clearer->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("Reference to non-existent or invalid clear-function: " + (yyvsp[(11) - (13)].u.identifier)->get_fully_scoped_name(), (yylsp[(11) - (13)]));
  }

  if (hasser && getter && setter && clearer) {
    CPPMakeProperty *make_property;
    make_property = new CPPMakeProperty((yyvsp[(3) - (13)].u.identifier),
                                        hasser->as_function_group(),
                                        getter->as_function_group(),
                                        setter->as_function_group(),
                                        clearer->as_function_group(),
                                        current_scope, (yylsp[(1) - (13)]).file);
    current_scope->add_declaration(make_property, global_scope, current_lexer, (yylsp[(1) - (13)]));
  }
}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 723 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPDeclaration *length_getter = (yyvsp[(5) - (9)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (length_getter == (CPPDeclaration *)NULL || length_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid length method: " + (yyvsp[(5) - (9)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (9)]));
    length_getter = NULL;
  }

  CPPDeclaration *element_getter = (yyvsp[(7) - (9)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (element_getter == (CPPDeclaration *)NULL || element_getter->get_subtype() != CPPDeclaration::ST_function_group) {
    yyerror("reference to non-existent or invalid element method: " + (yyvsp[(7) - (9)].u.identifier)->get_fully_scoped_name(), (yylsp[(5) - (9)]));
    element_getter = NULL;
  }

  if (length_getter != (CPPDeclaration *)NULL && element_getter != (CPPDeclaration *)NULL) {
    CPPMakeSeq *make_seq = new CPPMakeSeq((yyvsp[(3) - (9)].u.identifier),
                                          length_getter->as_function_group(),
                                          element_getter->as_function_group(),
                                          current_scope, (yylsp[(1) - (9)]).file);
    current_scope->add_declaration(make_seq, global_scope, current_lexer, (yylsp[(1) - (9)]));
  }
}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 745 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPExpression::Result result = (yyvsp[(3) - (7)].u.expr)->evaluate();
  if (result._type == CPPExpression::RT_error) {
    yywarning("static_assert requires a constant expression", (yylsp[(3) - (7)]));
  } else if (!result.as_boolean()) {
    stringstream str;
    str << *(yyvsp[(5) - (7)].u.expr);
    yywarning("static_assert failed: " + str.str(), (yylsp[(3) - (7)]));
  }
}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 756 "dtool/src/cppparser/cppBison.yxx"
    {
  // This alternative version of static_assert was introduced in C++17.
  CPPExpression::Result result = (yyvsp[(3) - (5)].u.expr)->evaluate();
  if (result._type == CPPExpression::RT_error) {
    yywarning("static_assert requires a constant expression", (yylsp[(3) - (5)]));
  } else if (!result.as_boolean()) {
    yywarning("static_assert failed", (yylsp[(3) - (5)]));
  }
}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 769 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPScope *new_scope = new CPPScope(current_scope, CPPNameComponent("temp"),
                                     V_public);
  push_scope(new_scope);
}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 775 "dtool/src/cppparser/cppBison.yxx"
    {
  delete current_scope;
  pop_scope();
}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 784 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = 0;
}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 788 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_extern;
}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 792 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(3) - (3)].u.integer) | (int)CPPInstance::SC_extern;
  if ((yyvsp[(2) - (3)].str) == "C") {
    (yyval.u.integer) |= (int)CPPInstance::SC_c_binding;
  } else if ((yyvsp[(2) - (3)].str) == "C++") {
    (yyval.u.integer) &= ~(int)CPPInstance::SC_c_binding;
  } else {
    yywarning("Ignoring unknown linkage type \"" + (yyvsp[(2) - (3)].str) + "\"", (yylsp[(2) - (3)]));
  }
}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 803 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_static;
}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 807 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_inline;
}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 811 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_virtual;
}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 815 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_explicit;
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 819 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_register;
}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 823 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_volatile;
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 827 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_mutable;
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 831 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_constexpr;
}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 835 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_blocking;
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 839 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_extension;
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 843 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(2) - (2)].u.integer) | (int)CPPInstance::SC_thread_local;
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 847 "dtool/src/cppparser/cppBison.yxx"
    {
  // Ignore attribute specifiers for now.
  (yyval.u.integer) = (yyvsp[(6) - (6)].u.integer);
}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 865 "dtool/src/cppparser/cppBison.yxx"
    {
  /* multiple_var_declaration adds itself to the scope. */
}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 869 "dtool/src/cppparser/cppBison.yxx"
    {
  // We don't really care about the storage class here.  In fact, it's
  // not actually legal to define a class or struct using a particular
  // storage class, but we require it just to help yacc out in its
  // parsing.

  current_scope->add_declaration((yyvsp[(2) - (3)].u.decl), global_scope, current_lexer, (yylsp[(2) - (3)]));
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 878 "dtool/src/cppparser/cppBison.yxx"
    {
  if ((yyvsp[(2) - (3)].u.instance) != (CPPInstance *)NULL) {
    (yyvsp[(2) - (3)].u.instance)->_storage_class |= (current_storage_class | (yyvsp[(1) - (3)].u.integer));
    current_scope->add_declaration((yyvsp[(2) - (3)].u.instance), global_scope, current_lexer, (yylsp[(2) - (3)]));
    (yyvsp[(2) - (3)].u.instance)->set_initializer((yyvsp[(3) - (3)].u.expr));
  }
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 886 "dtool/src/cppparser/cppBison.yxx"
    {
  if ((yyvsp[(2) - (3)].u.instance) != (CPPInstance *)NULL) {
    (yyvsp[(2) - (3)].u.instance)->_storage_class |= (current_storage_class | (yyvsp[(1) - (3)].u.integer));
    current_scope->add_declaration((yyvsp[(2) - (3)].u.instance), global_scope, current_lexer, (yylsp[(2) - (3)]));
    (yyvsp[(2) - (3)].u.instance)->set_initializer((yyvsp[(3) - (3)].u.expr));
  }
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 898 "dtool/src/cppparser/cppBison.yxx"
    {
  // We don't need to push/pop type, because we can't nest
  // multiple_var_declarations.
  if ((yyvsp[(2) - (2)].u.decl)->as_type_declaration()) {
    current_type = (yyvsp[(2) - (2)].u.decl)->as_type_declaration()->_type;
  } else {
    current_type = (yyvsp[(2) - (2)].u.decl)->as_type();
  }
  push_storage_class((yyvsp[(1) - (2)].u.integer));
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 909 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_storage_class();
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 913 "dtool/src/cppparser/cppBison.yxx"
    {
  // We don't need to push/pop type, because we can't nest
  // multiple_var_declarations.
  if ((yyvsp[(3) - (3)].u.decl)->as_type_declaration()) {
    current_type = (yyvsp[(3) - (3)].u.decl)->as_type_declaration()->_type;
  } else {
    current_type = (yyvsp[(3) - (3)].u.decl)->as_type();
  }
  push_storage_class((yyvsp[(1) - (3)].u.integer));
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 924 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_storage_class();
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 935 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPInstance *inst = new CPPInstance(current_type, (yyvsp[(1) - (2)].u.inst_ident),
                                      current_storage_class,
                                      (yylsp[(1) - (2)]).file);
  inst->set_initializer((yyvsp[(2) - (2)].u.expr));
  current_scope->add_declaration(inst, global_scope, current_lexer, (yylsp[(1) - (2)]));
}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 943 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPInstance *inst = new CPPInstance(current_type, (yyvsp[(1) - (4)].u.inst_ident),
                                      current_storage_class,
                                      (yylsp[(1) - (4)]).file);
  inst->set_initializer((yyvsp[(2) - (4)].u.expr));
  current_scope->add_declaration(inst, global_scope, current_lexer, (yylsp[(1) - (4)]));
}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 954 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyvsp[(1) - (2)].u.inst_ident)->add_modifier(IIT_const);
  CPPInstance *inst = new CPPInstance(current_type, (yyvsp[(1) - (2)].u.inst_ident),
                                      current_storage_class,
                                      (yylsp[(1) - (2)]).file);
  inst->set_initializer((yyvsp[(2) - (2)].u.expr));
  current_scope->add_declaration(inst, global_scope, current_lexer, (yylsp[(1) - (2)]));
}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 963 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyvsp[(1) - (4)].u.inst_ident)->add_modifier(IIT_const);
  CPPInstance *inst = new CPPInstance(current_type, (yyvsp[(1) - (4)].u.inst_ident),
                                      current_storage_class,
                                      (yylsp[(1) - (4)]).file);
  inst->set_initializer((yyvsp[(2) - (4)].u.expr));
  current_scope->add_declaration(inst, global_scope, current_lexer, (yylsp[(1) - (4)]));
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 976 "dtool/src/cppparser/cppBison.yxx"
    {
  // We don't need to push/pop type, because we can't nest
  // multiple_var_declarations.
  if ((yyvsp[(2) - (2)].u.decl)->as_type_declaration()) {
    current_type = (yyvsp[(2) - (2)].u.decl)->as_type_declaration()->_type;
  } else {
    current_type = (yyvsp[(2) - (2)].u.decl)->as_type();
  }
  push_storage_class((yyvsp[(1) - (2)].u.integer));
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 987 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_storage_class();
}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 991 "dtool/src/cppparser/cppBison.yxx"
    {
  // We don't need to push/pop type, because we can't nest
  // multiple_var_declarations.
  if ((yyvsp[(3) - (3)].u.decl)->as_type_declaration()) {
    current_type = (yyvsp[(3) - (3)].u.decl)->as_type_declaration()->_type;
  } else {
    current_type = (yyvsp[(3) - (3)].u.decl)->as_type();
  }
  push_storage_class((yyvsp[(1) - (3)].u.integer));
}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 1002 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_storage_class();
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 1006 "dtool/src/cppparser/cppBison.yxx"
    {
  if ((yyvsp[(2) - (3)].u.instance) != (CPPDeclaration *)NULL) {
    CPPInstance *inst = (yyvsp[(2) - (3)].u.instance)->as_instance();
    if (inst != (CPPInstance *)NULL) {
      inst->_storage_class |= (current_storage_class | (yyvsp[(1) - (3)].u.integer));
      current_scope->add_declaration(inst, global_scope, current_lexer, (yylsp[(2) - (3)]));
      CPPTypedefType *typedef_type = new CPPTypedefType(inst->_type, inst->_ident, current_scope);
      current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[(2) - (3)]));
    }
  }
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 1021 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *target_type = current_type;
  CPPTypedefType *typedef_type = new CPPTypedefType(target_type, (yyvsp[(1) - (2)].u.inst_ident), current_scope, (yylsp[(1) - (2)]).file);
  current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[(1) - (2)]));
}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 1027 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *target_type = current_type;
  CPPTypedefType *typedef_type = new CPPTypedefType(target_type, (yyvsp[(1) - (4)].u.inst_ident), current_scope, (yylsp[(1) - (4)]).file);
  current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[(1) - (4)]));
}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 1036 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyvsp[(1) - (2)].u.inst_ident)->add_modifier(IIT_const);
  CPPType *target_type = current_type;
  CPPTypedefType *typedef_type = new CPPTypedefType(target_type, (yyvsp[(1) - (2)].u.inst_ident), current_scope, (yylsp[(1) - (2)]).file);
  current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[(1) - (2)]));
}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 1043 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyvsp[(1) - (4)].u.inst_ident)->add_modifier(IIT_const);
  CPPType *target_type = current_type;
  CPPTypedefType *typedef_type = new CPPTypedefType(target_type, (yyvsp[(1) - (4)].u.inst_ident), current_scope, (yylsp[(1) - (4)]).file);
  current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[(1) - (4)]));
}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 1055 "dtool/src/cppparser/cppBison.yxx"
    {
  push_scope((yyvsp[(1) - (2)].u.identifier)->get_scope(current_scope, global_scope));
}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 1059 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type;
  if ((yyvsp[(1) - (6)].u.identifier)->get_simple_name() == current_scope->get_simple_name() ||
      (yyvsp[(1) - (6)].u.identifier)->get_simple_name() == string("~") + current_scope->get_simple_name()) {
    // This is a constructor, and has no return.
    type = new CPPSimpleType(CPPSimpleType::T_void);
  } else {
    // This isn't a constructor, so it has an implicit return type of
    // int.
    yywarning("function has no return type, assuming int", (yylsp[(1) - (6)]));
    type = new CPPSimpleType(CPPSimpleType::T_int);
  }
  pop_scope();

  CPPInstanceIdentifier *ii = new CPPInstanceIdentifier((yyvsp[(1) - (6)].u.identifier));
  ii->add_func_modifier((yyvsp[(4) - (6)].u.param_list), (yyvsp[(6) - (6)].u.integer));

  (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[(1) - (6)]).file);
}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 1079 "dtool/src/cppparser/cppBison.yxx"
    {
  push_scope((yyvsp[(1) - (2)].u.identifier)->get_scope(current_scope, global_scope));
}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 1083 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_scope();
  CPPType *type;
  if ((yyvsp[(1) - (6)].u.identifier)->get_simple_name() == current_scope->get_simple_name()) {
    // This is a constructor, and has no return.
    type = new CPPSimpleType(CPPSimpleType::T_void);
  } else {
    // This isn't a constructor, so it has an implicit return type of
    // int.
    type = new CPPSimpleType(CPPSimpleType::T_int);
  }

  CPPInstanceIdentifier *ii = new CPPInstanceIdentifier((yyvsp[(1) - (6)].u.identifier));
  ii->add_func_modifier((yyvsp[(4) - (6)].u.param_list), (yyvsp[(6) - (6)].u.integer));

  (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[(1) - (6)]).file);
}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 1106 "dtool/src/cppparser/cppBison.yxx"
    {
  push_scope((yyvsp[(2) - (3)].u.identifier)->get_scope(current_scope, global_scope));
}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 1110 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_scope();
  if ((yyvsp[(2) - (7)].u.identifier)->is_scoped()) {
    yyerror("Invalid destructor name: ~" + (yyvsp[(2) - (7)].u.identifier)->get_fully_scoped_name(), (yylsp[(2) - (7)]));
  } else {
    CPPIdentifier *ident =
      new CPPIdentifier("~" + (yyvsp[(2) - (7)].u.identifier)->get_simple_name(), (yylsp[(2) - (7)]));
    delete (yyvsp[(2) - (7)].u.identifier);

    CPPType *type;
    type = new CPPSimpleType(CPPSimpleType::T_void);

    CPPInstanceIdentifier *ii = new CPPInstanceIdentifier(ident);
    ii->add_func_modifier((yyvsp[(5) - (7)].u.param_list), (yyvsp[(7) - (7)].u.integer));

    (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[(2) - (7)]).file);
  }
}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 1136 "dtool/src/cppparser/cppBison.yxx"
    {
  push_scope((yyvsp[(4) - (6)].u.inst_ident)->get_scope(current_scope, global_scope));
}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 1140 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_scope();
  CPPType *type = (yyvsp[(1) - (11)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type == NULL) {
    yyerror(string("internal error resolving type ") + (yyvsp[(1) - (11)].u.identifier)->get_fully_scoped_name(), (yylsp[(1) - (11)]));
  }
  assert(type != NULL);

  CPPInstanceIdentifier *ii = (yyvsp[(4) - (11)].u.inst_ident);
  ii->add_modifier(IIT_pointer);
  ii->add_func_modifier((yyvsp[(8) - (11)].u.param_list), (yyvsp[(10) - (11)].u.integer));
  (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[(1) - (11)]).file);
}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 1154 "dtool/src/cppparser/cppBison.yxx"
    {
  push_scope((yyvsp[(5) - (7)].u.inst_ident)->get_scope(current_scope, global_scope));
}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 1158 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_scope();
  CPPType *type = (yyvsp[(1) - (12)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type == NULL) {
    yyerror(string("internal error resolving type ") + (yyvsp[(1) - (12)].u.identifier)->get_fully_scoped_name(), (yylsp[(1) - (12)]));
  }
  assert(type != NULL);

  CPPInstanceIdentifier *ii = (yyvsp[(5) - (12)].u.inst_ident);
  ii->add_scoped_pointer_modifier((yyvsp[(3) - (12)].u.identifier));
  ii->add_func_modifier((yyvsp[(9) - (12)].u.param_list), (yyvsp[(11) - (12)].u.integer));
  (yyval.u.instance) = new CPPInstance(type, ii, 0, (yylsp[(1) - (12)]).file);
}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 1174 "dtool/src/cppparser/cppBison.yxx"
    {
  if ((yyvsp[(1) - (4)].u.identifier) != NULL) {
    push_scope((yyvsp[(1) - (4)].u.identifier)->get_scope(current_scope, global_scope));
  }
}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 1180 "dtool/src/cppparser/cppBison.yxx"
    {
  if ((yyvsp[(1) - (8)].u.identifier) != NULL) {
    pop_scope();
  }

  // We use formal_parameter_identifier, because that can match a type
  // name with or without an identifier, but especially without, which
  // is what follows the keyword "operator" in a typecast function.
  // As an added bonus, the type of the formal_parameter will be the
  // typecast type, i.e. the return type of the typecast function.

  // We give typecast operators the name "operator typecast <name>",
  // where <name> is a simple name of the type to be typecast.  Use
  // the method's return type to determine the full type description.
  string name = "operator typecast " + (yyvsp[(2) - (8)].u.type)->get_simple_name();
  CPPIdentifier *ident = (yyvsp[(1) - (8)].u.identifier);
  if (ident == NULL) {
    ident = new CPPIdentifier(name, (yylsp[(2) - (8)]));
  } else {
    ident->add_name(name);
  }
  (yyval.u.instance) = CPPInstance::make_typecast_function
    (new CPPInstance((yyvsp[(2) - (8)].u.type), (yyvsp[(3) - (8)].u.inst_ident), 0, (yylsp[(3) - (8)]).file), ident, (yyvsp[(6) - (8)].u.param_list), (yyvsp[(8) - (8)].u.integer));
}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 1205 "dtool/src/cppparser/cppBison.yxx"
    {
  if ((yyvsp[(1) - (5)].u.identifier) != NULL) {
    push_scope((yyvsp[(1) - (5)].u.identifier)->get_scope(current_scope, global_scope));
  }
}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1211 "dtool/src/cppparser/cppBison.yxx"
    {
  if ((yyvsp[(1) - (9)].u.identifier) != NULL) {
    pop_scope();
  }

  CPPIdentifier *ident = (yyvsp[(1) - (9)].u.identifier);
  if (ident == NULL) {
    ident = new CPPIdentifier("operator typecast", (yylsp[(4) - (9)]));
  } else {
    ident->add_name("operator typecast");
  }
  (yyvsp[(4) - (9)].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.instance) = CPPInstance::make_typecast_function
    (new CPPInstance((yyvsp[(3) - (9)].u.type), (yyvsp[(4) - (9)].u.inst_ident), 0, (yylsp[(4) - (9)]).file), ident, (yyvsp[(7) - (9)].u.param_list), (yyvsp[(9) - (9)].u.integer));
}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1231 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPDeclaration *decl =
    (yyvsp[(1) - (1)].u.identifier)->find_symbol(current_scope, global_scope, current_lexer);
  if (decl != (CPPDeclaration *)NULL) {
    (yyval.u.instance) = decl->as_instance();
  } else {
    (yyval.u.instance) = (CPPInstance *)NULL;
  }
}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1244 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = 0;
}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1248 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (int)CPPFunctionType::F_const_method;
}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1252 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (int)CPPFunctionType::F_noexcept;
}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 1256 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (int)CPPFunctionType::F_final;
}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 1260 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (int)CPPFunctionType::F_override;
}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 1264 "dtool/src/cppparser/cppBison.yxx"
    {
  // Used for lambdas, currently ignored.
  (yyval.u.integer) = 0;
}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1269 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(1) - (4)].u.integer);
}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 1273 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.integer) = (yyvsp[(1) - (5)].u.integer);
}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 1284 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "!";
}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1288 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "~";
}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1292 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "*";
}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1296 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "/";
}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1300 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "%";
}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1304 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "+";
}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1308 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "-";
}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1312 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "|";
}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1316 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "&";
}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1320 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "^";
}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1324 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "||";
}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1328 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "&&";
}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1332 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "==";
}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1336 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "!=";
}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1340 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "<=";
}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1344 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = ">=";
}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1348 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "<";
}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1352 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = ">";
}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1356 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "<<";
}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1360 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = ">>";
}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1364 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "=";
}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1368 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = ",";
}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1372 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "++";
}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1376 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "--";
}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1380 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "*=";
}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1384 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "/=";
}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1388 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "%=";
}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1392 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "+=";
}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1396 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "-=";
}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1400 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "|=";
}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1404 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "&=";
}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1408 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "^=";
}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1412 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "<<=";
}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1416 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = ">>=";
}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1420 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "->";
}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1424 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "[]";
}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1428 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "()";
}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1432 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "new";
}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1436 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.str) = "delete";
}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1448 "dtool/src/cppparser/cppBison.yxx"
    {
  push_scope(new CPPTemplateScope(current_scope));
}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1452 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_scope();
}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1465 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPTemplateScope *ts = current_scope->as_template_scope();
  assert(ts != NULL);
  ts->add_template_parameter((yyvsp[(1) - (1)].u.decl));
}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1471 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPTemplateScope *ts = current_scope->as_template_scope();
  assert(ts != NULL);
  ts->add_template_parameter((yyvsp[(3) - (3)].u.decl));
}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1480 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = CPPType::new_type(new CPPClassTemplateParameter((yyvsp[(2) - (2)].u.identifier)));
}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1484 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = CPPType::new_type(new CPPClassTemplateParameter((yyvsp[(2) - (4)].u.identifier), (yyvsp[(4) - (4)].u.type)));
}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1488 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = CPPType::new_type(new CPPClassTemplateParameter((yyvsp[(2) - (2)].u.identifier)));
}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1492 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = CPPType::new_type(new CPPClassTemplateParameter((yyvsp[(2) - (4)].u.identifier), (yyvsp[(4) - (4)].u.type)));
}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1496 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPInstance *inst = new CPPInstance((yyvsp[(1) - (3)].u.type), (yyvsp[(2) - (3)].u.inst_ident), 0, (yylsp[(2) - (3)]).file);
  inst->set_initializer((yyvsp[(3) - (3)].u.expr));
  (yyval.u.decl) = inst;
}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1502 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyvsp[(3) - (4)].u.inst_ident)->add_modifier(IIT_const);
  CPPInstance *inst = new CPPInstance((yyvsp[(2) - (4)].u.type), (yyvsp[(3) - (4)].u.inst_ident), 0, (yylsp[(3) - (4)]).file);
  inst->set_initializer((yyvsp[(4) - (4)].u.expr));
  (yyval.u.decl) = inst;
}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1512 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type((yyvsp[(1) - (1)].u.simple_type));
}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1516 "dtool/src/cppparser/cppBison.yxx"
    {
  yywarning("Not a type: " + (yyvsp[(1) - (1)].u.identifier)->get_fully_scoped_name(), (yylsp[(1) - (1)]));
  (yyval.u.type) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_unknown));
}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1521 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = (yyvsp[(1) - (1)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.type) == NULL) {
    yyerror(string("internal error resolving type ") + (yyvsp[(1) - (1)].u.identifier)->get_fully_scoped_name(), (yylsp[(1) - (1)]));
  }
  assert((yyval.u.type) != NULL);
}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1533 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((yyvsp[(1) - (1)].u.identifier));
}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1537 "dtool/src/cppparser/cppBison.yxx"
    {
  // For an operator function.  We implement this simply by building a
  // ficticious name for the function; in other respects it's just
  // like a regular function.
  CPPIdentifier *ident = (yyvsp[(1) - (2)].u.identifier);
  if (ident == NULL) {
    ident = new CPPIdentifier("operator "+(yyvsp[(2) - (2)].str), (yylsp[(2) - (2)]));
  } else {
    ident->_names.push_back("operator "+(yyvsp[(2) - (2)].str));
  }

  (yyval.u.inst_ident) = new CPPInstanceIdentifier(ident);
}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1551 "dtool/src/cppparser/cppBison.yxx"
    {
  // A C++11 literal operator.
  if (!(yyvsp[(2) - (3)].str).empty()) {
    yyerror("expected empty string", (yylsp[(2) - (3)]));
  }
  CPPIdentifier *ident = (yyvsp[(1) - (3)].u.identifier);
  if (ident == NULL) {
    ident = new CPPIdentifier("operator \"\" "+(yyvsp[(3) - (3)].u.identifier)->get_simple_name(), (yylsp[(3) - (3)]));
  } else {
    ident->_names.push_back("operator \"\" "+(yyvsp[(3) - (3)].u.identifier)->get_simple_name());
  }

  (yyval.u.inst_ident) = new CPPInstanceIdentifier(ident);
}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1566 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1571 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1576 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1581 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1586 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1591 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(3) - (3)].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[(1) - (3)].u.identifier));
}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1596 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(1) - (4)].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[(3) - (4)].u.expr));
}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1601 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (3)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1606 "dtool/src/cppparser/cppBison.yxx"
    {
  push_scope((yyvsp[(1) - (2)].u.inst_ident)->get_scope(current_scope, global_scope));
}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1610 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_scope();
  (yyval.u.inst_ident) = (yyvsp[(1) - (6)].u.inst_ident);
  if ((yyvsp[(4) - (6)].u.param_list)->is_parameter_expr() && (yyvsp[(6) - (6)].u.integer) == 0) {
    // Oops, this must have been an instance declaration with a
    // parameter list, not a function prototype.
    (yyval.u.inst_ident)->add_initializer_modifier((yyvsp[(4) - (6)].u.param_list));

  } else {
    // This was (probably) a function prototype.
    (yyval.u.inst_ident)->add_func_modifier((yyvsp[(4) - (6)].u.param_list), (yyvsp[(6) - (6)].u.integer));
  }
}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1628 "dtool/src/cppparser/cppBison.yxx"
    {
  // This is handled a bit awkwardly right now.  Ideally it'd be wrapped
  // up in the instance_identifier rule, but then more needs to happen in
  // order to avoid shift/reduce conflicts.
  if ((yyvsp[(2) - (2)].u.type) != NULL) {
    (yyvsp[(1) - (2)].u.inst_ident)->add_trailing_return_type((yyvsp[(2) - (2)].u.type));
  }
  (yyval.u.inst_ident) = (yyvsp[(1) - (2)].u.inst_ident);
}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1638 "dtool/src/cppparser/cppBison.yxx"
    {
  // Bitfield definition.
  (yyvsp[(1) - (3)].u.inst_ident)->_bit_width = (yyvsp[(3) - (3)].u.integer);
  (yyval.u.inst_ident) = (yyvsp[(1) - (3)].u.inst_ident);
}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1648 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = NULL;
}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1652 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = (yyvsp[(3) - (3)].u.inst_ident)->unroll_type((yyvsp[(2) - (3)].u.type));
}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1656 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyvsp[(4) - (4)].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.type) = (yyvsp[(4) - (4)].u.inst_ident)->unroll_type((yyvsp[(3) - (4)].u.type));
}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1665 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = new CPPParameterList;
}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1669 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = new CPPParameterList;
  (yyval.u.param_list)->_includes_ellipsis = true;
}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1674 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = (yyvsp[(1) - (1)].u.param_list);
}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1678 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = (yyvsp[(1) - (3)].u.param_list);
  (yyval.u.param_list)->_includes_ellipsis = true;
}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1683 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = (yyvsp[(1) - (2)].u.param_list);
  (yyval.u.param_list)->_includes_ellipsis = true;
}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1691 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = new CPPParameterList;
  (yyval.u.param_list)->_parameters.push_back((yyvsp[(1) - (1)].u.instance));
}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1696 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = (yyvsp[(1) - (3)].u.param_list);
  (yyval.u.param_list)->_parameters.push_back((yyvsp[(3) - (3)].u.instance));
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1704 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = new CPPParameterList;
}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1708 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = new CPPParameterList;
  (yyval.u.param_list)->_includes_ellipsis = true;
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1713 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = (yyvsp[(1) - (1)].u.param_list);
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1717 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = (yyvsp[(1) - (3)].u.param_list);
  (yyval.u.param_list)->_includes_ellipsis = true;
}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1722 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = (yyvsp[(1) - (2)].u.param_list);
  (yyval.u.param_list)->_includes_ellipsis = true;
}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1730 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = new CPPParameterList;
  (yyval.u.param_list)->_parameters.push_back((yyvsp[(1) - (1)].u.instance));
}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1735 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.param_list) = (yyvsp[(1) - (3)].u.param_list);
  (yyval.u.param_list)->_parameters.push_back((yyvsp[(3) - (3)].u.instance));
}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1743 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1747 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(2) - (2)].u.expr);
}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1754 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1758 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(2) - (2)].u.expr);
}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1765 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1769 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1773 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1777 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_default());
}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1781 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_delete());
}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1788 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1792 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1796 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(2) - (3)].u.expr);
}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1800 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_default());
}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1804 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_delete());
}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1808 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1821 "dtool/src/cppparser/cppBison.yxx"
    {
}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1830 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.instance) = new CPPInstance((yyvsp[(1) - (3)].u.type), (yyvsp[(2) - (3)].u.inst_ident), 0, (yylsp[(2) - (3)]).file);
  (yyval.u.instance)->set_initializer((yyvsp[(3) - (3)].u.expr));
}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1835 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyvsp[(3) - (4)].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.instance) = new CPPInstance((yyvsp[(2) - (4)].u.type), (yyvsp[(3) - (4)].u.inst_ident), 0, (yylsp[(3) - (4)]).file);
  (yyval.u.instance)->set_initializer((yyvsp[(4) - (4)].u.expr));
}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1841 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyvsp[(4) - (5)].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.instance) = new CPPInstance((yyvsp[(3) - (5)].u.type), (yyvsp[(4) - (5)].u.inst_ident), 0, (yylsp[(3) - (5)]).file);
  (yyval.u.instance)->set_initializer((yyvsp[(5) - (5)].u.expr));
}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1847 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.instance) = (yyvsp[(2) - (2)].u.instance);
}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1858 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.instance) = (yyvsp[(1) - (1)].u.instance);
}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1862 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_parameter));
  (yyval.u.instance) = new CPPInstance(type, "expr");
  (yyval.u.instance)->set_initializer((yyvsp[(1) - (1)].u.expr));
}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1872 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((CPPIdentifier *)NULL);
}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1876 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((yyvsp[(1) - (1)].u.identifier));
}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1880 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1885 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1890 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1895 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1900 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1905 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(3) - (3)].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[(1) - (3)].u.identifier));
}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1910 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(1) - (4)].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[(3) - (4)].u.expr));
}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1918 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((CPPIdentifier *)NULL);
}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1922 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((yyvsp[(1) - (1)].u.identifier));
}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1926 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1931 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1936 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1941 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1946 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1951 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(3) - (3)].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[(1) - (3)].u.identifier));
}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1956 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(1) - (4)].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[(3) - (4)].u.expr));
}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1961 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (7)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[(5) - (7)].u.param_list), (yyvsp[(7) - (7)].u.integer));
}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1967 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (3)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 1975 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((CPPIdentifier *)NULL);
}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 1979 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1984 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1989 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1994 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1999 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 2004 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(3) - (3)].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[(1) - (3)].u.identifier));
}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 2009 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(1) - (4)].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[(3) - (4)].u.expr));
}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 2017 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((CPPIdentifier *)NULL);
}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 2021 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_const);
}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 2026 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_volatile);
}
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 2031 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 2036 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 2041 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(2) - (2)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
}
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 2046 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(3) - (3)].u.inst_ident);
  (yyval.u.inst_ident)->add_scoped_pointer_modifier((yyvsp[(1) - (3)].u.identifier));
}
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 2051 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(1) - (4)].u.inst_ident);
  (yyval.u.inst_ident)->add_array_modifier((yyvsp[(3) - (4)].u.expr));
}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 2056 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = new CPPInstanceIdentifier((CPPIdentifier *)NULL);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[(2) - (5)].u.param_list), (yyvsp[(4) - (5)].u.integer), (yyvsp[(5) - (5)].u.type));
}
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 2062 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(3) - (9)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_pointer);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[(6) - (9)].u.param_list), (yyvsp[(8) - (9)].u.integer), (yyvsp[(9) - (9)].u.type));
}
    break;

  case 258:
/* Line 1792 of yacc.c  */
#line 2069 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(3) - (9)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_reference);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[(6) - (9)].u.param_list), (yyvsp[(8) - (9)].u.integer), (yyvsp[(9) - (9)].u.type));
}
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 2076 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.inst_ident) = (yyvsp[(3) - (9)].u.inst_ident);
  (yyval.u.inst_ident)->add_modifier(IIT_rvalue_reference);
  (yyval.u.inst_ident)->add_modifier(IIT_paren);
  (yyval.u.inst_ident)->add_func_modifier((yyvsp[(6) - (9)].u.param_list), (yyvsp[(8) - (9)].u.integer), (yyvsp[(9) - (9)].u.type));
}
    break;

  case 260:
/* Line 1792 of yacc.c  */
#line 2086 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type((yyvsp[(1) - (1)].u.simple_type));
}
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 2090 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = (yyvsp[(1) - (1)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.type) == NULL) {
    yyerror(string("internal error resolving type ") + (yyvsp[(1) - (1)].u.identifier)->get_fully_scoped_name(), (yylsp[(1) - (1)]));
  }
  assert((yyval.u.type) != NULL);
}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 2098 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type(new CPPTBDType((yyvsp[(2) - (2)].u.identifier)));
}
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 2102 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type((yyvsp[(1) - (1)].u.struct_type));
}
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 2106 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type((yyvsp[(1) - (1)].u.struct_type));
}
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 2110 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type((yyvsp[(1) - (1)].u.enum_type));
}
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 2114 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type = (yyvsp[(2) - (2)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != NULL) {
    (yyval.u.type) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[(1) - (2)].u.extension_enum), (yyvsp[(2) - (2)].u.identifier), current_scope, (yylsp[(1) - (2)]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[(2) - (2)].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != NULL) {
      scope->define_extension_type(et);
    }
    (yyval.u.type) = et;
  }
}
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 2130 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type = (yyvsp[(2) - (4)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != NULL) {
    (yyval.u.type) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[(1) - (4)].u.extension_enum), (yyvsp[(2) - (4)].u.identifier), current_scope, (yylsp[(1) - (4)]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[(2) - (4)].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != NULL) {
      scope->define_extension_type(et);
    }
    (yyval.u.type) = et;
  }
}
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 2146 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = (yyvsp[(3) - (4)].u.expr)->determine_type();
  if ((yyval.u.type) == (CPPType *)NULL) {
    stringstream str;
    str << *(yyvsp[(3) - (4)].u.expr);
    yyerror("could not determine type of " + str.str(), (yylsp[(3) - (4)]));
  }
}
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 2155 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_auto));
}
    break;

  case 270:
/* Line 1792 of yacc.c  */
#line 2162 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = CPPType::new_type((yyvsp[(1) - (1)].u.simple_type));
}
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 2166 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = (yyvsp[(1) - (1)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.decl) == NULL) {
    yyerror(string("internal error resolving type ") + (yyvsp[(1) - (1)].u.identifier)->get_fully_scoped_name(), (yylsp[(1) - (1)]));
  }
  assert((yyval.u.decl) != NULL);
}
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 2174 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = CPPType::new_type(new CPPTBDType((yyvsp[(2) - (2)].u.identifier)));
}
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 2178 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = CPPType::new_type((yyvsp[(1) - (1)].u.struct_type));
}
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 2182 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = new CPPTypeDeclaration(CPPType::new_type((yyvsp[(1) - (1)].u.struct_type)));
}
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 2186 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = new CPPTypeDeclaration(CPPType::new_type((yyvsp[(1) - (1)].u.enum_type)));
}
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 2190 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type = (yyvsp[(2) - (2)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != NULL) {
    (yyval.u.decl) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[(1) - (2)].u.extension_enum), (yyvsp[(2) - (2)].u.identifier), current_scope, (yylsp[(1) - (2)]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[(2) - (2)].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != NULL) {
      scope->define_extension_type(et);
    }
    (yyval.u.decl) = et;
  }
}
    break;

  case 277:
/* Line 1792 of yacc.c  */
#line 2206 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type = (yyvsp[(2) - (4)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != NULL) {
    (yyval.u.decl) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[(1) - (4)].u.extension_enum), (yyvsp[(2) - (4)].u.identifier), current_scope, (yylsp[(1) - (4)]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[(2) - (4)].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != NULL) {
      scope->define_extension_type(et);
    }
    (yyval.u.decl) = et;
  }
}
    break;

  case 278:
/* Line 1792 of yacc.c  */
#line 2222 "dtool/src/cppparser/cppBison.yxx"
    {
  yywarning(string("C++ does not permit forward declaration of untyped enum ") + (yyvsp[(2) - (2)].u.identifier)->get_fully_scoped_name(), (yylsp[(1) - (2)]));

  CPPType *type = (yyvsp[(2) - (2)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != NULL) {
    (yyval.u.decl) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[(1) - (2)].u.extension_enum), (yyvsp[(2) - (2)].u.identifier), current_scope, (yylsp[(1) - (2)]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[(2) - (2)].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != NULL) {
      scope->define_extension_type(et);
    }
    (yyval.u.decl) = et;
  }
}
    break;

  case 279:
/* Line 1792 of yacc.c  */
#line 2240 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = (yyvsp[(3) - (4)].u.expr)->determine_type();
  if ((yyval.u.decl) == (CPPType *)NULL) {
    stringstream str;
    str << *(yyvsp[(3) - (4)].u.expr);
    yyerror("could not determine type of " + str.str(), (yylsp[(3) - (4)]));
  }
}
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 2249 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_auto));
}
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 2256 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type((yyvsp[(1) - (1)].u.simple_type));
}
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 2260 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = (yyvsp[(1) - (1)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if ((yyval.u.type) == NULL) {
    yyerror(string("internal error resolving type ") + (yyvsp[(1) - (1)].u.identifier)->get_fully_scoped_name(), (yylsp[(1) - (1)]));
  }
  assert((yyval.u.type) != NULL);
}
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 2268 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type(new CPPTBDType((yyvsp[(2) - (2)].u.identifier)));
}
    break;

  case 284:
/* Line 1792 of yacc.c  */
#line 2272 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type = (yyvsp[(2) - (2)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != NULL) {
    (yyval.u.type) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[(1) - (2)].u.extension_enum), (yyvsp[(2) - (2)].u.identifier), current_scope, (yylsp[(1) - (2)]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[(2) - (2)].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != NULL) {
      scope->define_extension_type(et);
    }
    (yyval.u.type) = et;
  }
}
    break;

  case 285:
/* Line 1792 of yacc.c  */
#line 2288 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type = (yyvsp[(2) - (2)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type != NULL) {
    (yyval.u.type) = type;
  } else {
    CPPExtensionType *et =
      CPPType::new_type(new CPPExtensionType((yyvsp[(1) - (2)].u.extension_enum), (yyvsp[(2) - (2)].u.identifier), current_scope, (yylsp[(1) - (2)]).file))
      ->as_extension_type();
    CPPScope *scope = (yyvsp[(2) - (2)].u.identifier)->get_scope(current_scope, global_scope);
    if (scope != NULL) {
      scope->define_extension_type(et);
    }
    (yyval.u.type) = et;
  }
}
    break;

  case 286:
/* Line 1792 of yacc.c  */
#line 2304 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = (yyvsp[(3) - (4)].u.expr)->determine_type();
  if ((yyval.u.type) == (CPPType *)NULL) {
    stringstream str;
    str << *(yyvsp[(3) - (4)].u.expr);
    yyerror("could not determine type of " + str.str(), (yylsp[(3) - (4)]));
  }
}
    break;

  case 287:
/* Line 1792 of yacc.c  */
#line 2313 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_auto));
}
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 2320 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.decl) = (yyvsp[(1) - (1)].u.decl);
}
    break;

  case 289:
/* Line 1792 of yacc.c  */
#line 2324 "dtool/src/cppparser/cppBison.yxx"
    {
  yyerror(string("unknown type '") + (yyvsp[(1) - (1)].u.identifier)->get_fully_scoped_name() + "'", (yylsp[(1) - (1)]));

  (yyval.u.decl) = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_unknown));
}
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 2332 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = (yyvsp[(2) - (2)].u.inst_ident)->unroll_type((yyvsp[(1) - (2)].u.type));
}
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 2336 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyvsp[(3) - (3)].u.inst_ident)->add_modifier(IIT_const);
  (yyval.u.type) = (yyvsp[(3) - (3)].u.inst_ident)->unroll_type((yyvsp[(2) - (3)].u.type));
}
    break;

  case 292:
/* Line 1792 of yacc.c  */
#line 2344 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPVisibility starting_vis =
  ((yyvsp[(1) - (2)].u.extension_enum) == CPPExtensionType::T_class) ? V_private : V_public;

  CPPScope *new_scope = new CPPScope(current_scope, CPPNameComponent("anon"),
                                     starting_vis);
  CPPStructType *st = new CPPStructType((yyvsp[(1) - (2)].u.extension_enum), NULL, current_scope,
                                        new_scope, (yylsp[(1) - (2)]).file);
  new_scope->set_struct_type(st);

  push_scope(new_scope);
  push_struct(st);
}
    break;

  case 293:
/* Line 1792 of yacc.c  */
#line 2358 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.struct_type) = current_struct;
  current_struct->_incomplete = false;
  pop_struct();
  pop_scope();
}
    break;

  case 294:
/* Line 1792 of yacc.c  */
#line 2368 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPVisibility starting_vis =
  ((yyvsp[(1) - (2)].u.extension_enum) == CPPExtensionType::T_class) ? V_private : V_public;

  CPPScope *scope = (yyvsp[(2) - (2)].u.identifier)->get_scope(current_scope, global_scope, current_lexer);
  if (scope == NULL) {
    scope = current_scope;
  }
  CPPScope *new_scope = new CPPScope(scope, (yyvsp[(2) - (2)].u.identifier)->_names.back(),
                                     starting_vis);

  CPPStructType *st = new CPPStructType((yyvsp[(1) - (2)].u.extension_enum), (yyvsp[(2) - (2)].u.identifier), current_scope,
                                        new_scope, (yylsp[(1) - (2)]).file);
  new_scope->set_struct_type(st);
  current_scope->define_extension_type(st);

  push_scope(new_scope);
  push_struct(st);
}
    break;

  case 295:
/* Line 1792 of yacc.c  */
#line 2388 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.struct_type) = current_struct;
  current_struct->_incomplete = false;
  pop_struct();
  pop_scope();
}
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 2399 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->_final = true;
}
    break;

  case 302:
/* Line 1792 of yacc.c  */
#line 2416 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(1) - (1)].u.type), V_unknown, false);
}
    break;

  case 303:
/* Line 1792 of yacc.c  */
#line 2420 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(2) - (2)].u.type), V_public, false);
}
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 2424 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(2) - (2)].u.type), V_protected, false);
}
    break;

  case 305:
/* Line 1792 of yacc.c  */
#line 2428 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(2) - (2)].u.type), V_private, false);
}
    break;

  case 306:
/* Line 1792 of yacc.c  */
#line 2432 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(3) - (3)].u.type), V_public, true);
}
    break;

  case 307:
/* Line 1792 of yacc.c  */
#line 2436 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(3) - (3)].u.type), V_protected, true);
}
    break;

  case 308:
/* Line 1792 of yacc.c  */
#line 2440 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(3) - (3)].u.type), V_private, true);
}
    break;

  case 309:
/* Line 1792 of yacc.c  */
#line 2444 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(3) - (3)].u.type), V_public, true);
}
    break;

  case 310:
/* Line 1792 of yacc.c  */
#line 2448 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(3) - (3)].u.type), V_protected, true);
}
    break;

  case 311:
/* Line 1792 of yacc.c  */
#line 2452 "dtool/src/cppparser/cppBison.yxx"
    {
  current_struct->append_derivation((yyvsp[(3) - (3)].u.type), V_private, true);
}
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 2459 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.enum_type) = current_enum;
  current_enum = NULL;
}
    break;

  case 313:
/* Line 1792 of yacc.c  */
#line 2467 "dtool/src/cppparser/cppBison.yxx"
    {
  current_enum = new CPPEnumType((yyvsp[(1) - (3)].u.extension_enum), NULL, (yyvsp[(3) - (3)].u.type), current_scope, NULL, (yylsp[(1) - (3)]).file);
}
    break;

  case 314:
/* Line 1792 of yacc.c  */
#line 2471 "dtool/src/cppparser/cppBison.yxx"
    {
  current_enum = new CPPEnumType((yyvsp[(1) - (1)].u.extension_enum), NULL, current_scope, NULL, (yylsp[(1) - (1)]).file);
}
    break;

  case 315:
/* Line 1792 of yacc.c  */
#line 2475 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPScope *new_scope = new CPPScope(current_scope, (yyvsp[(2) - (4)].u.identifier)->_names.back(), V_public);
  current_enum = new CPPEnumType((yyvsp[(1) - (4)].u.extension_enum), (yyvsp[(2) - (4)].u.identifier), (yyvsp[(4) - (4)].u.type), current_scope, new_scope, (yylsp[(1) - (4)]).file);
}
    break;

  case 316:
/* Line 1792 of yacc.c  */
#line 2480 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPScope *new_scope = new CPPScope(current_scope, (yyvsp[(2) - (2)].u.identifier)->_names.back(), V_public);
  current_enum = new CPPEnumType((yyvsp[(1) - (2)].u.extension_enum), (yyvsp[(2) - (2)].u.identifier), current_scope, new_scope, (yylsp[(1) - (2)]).file);
}
    break;

  case 317:
/* Line 1792 of yacc.c  */
#line 2488 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type((yyvsp[(1) - (1)].u.simple_type));
}
    break;

  case 318:
/* Line 1792 of yacc.c  */
#line 2492 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = (yyvsp[(1) - (1)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
}
    break;

  case 320:
/* Line 1792 of yacc.c  */
#line 2500 "dtool/src/cppparser/cppBison.yxx"
    {
  assert(current_enum != NULL);
  current_enum->add_element((yyvsp[(2) - (3)].u.identifier)->get_simple_name(), NULL, current_lexer, (yylsp[(2) - (3)]));
}
    break;

  case 321:
/* Line 1792 of yacc.c  */
#line 2505 "dtool/src/cppparser/cppBison.yxx"
    {
  assert(current_enum != NULL);
  current_enum->add_element((yyvsp[(2) - (5)].u.identifier)->get_simple_name(), (yyvsp[(4) - (5)].u.expr), current_lexer, (yylsp[(2) - (5)]));
}
    break;

  case 323:
/* Line 1792 of yacc.c  */
#line 2513 "dtool/src/cppparser/cppBison.yxx"
    {
  assert(current_enum != NULL);
  current_enum->add_element((yyvsp[(2) - (2)].u.identifier)->get_simple_name(), NULL, current_lexer, (yylsp[(2) - (2)]));
}
    break;

  case 324:
/* Line 1792 of yacc.c  */
#line 2518 "dtool/src/cppparser/cppBison.yxx"
    {
  assert(current_enum != NULL);
  current_enum->add_element((yyvsp[(2) - (4)].u.identifier)->get_simple_name(), (yyvsp[(4) - (4)].u.expr), current_lexer, (yylsp[(2) - (4)]));
}
    break;

  case 325:
/* Line 1792 of yacc.c  */
#line 2526 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.extension_enum) = CPPExtensionType::T_enum;
}
    break;

  case 326:
/* Line 1792 of yacc.c  */
#line 2530 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.extension_enum) = CPPExtensionType::T_enum_class;
}
    break;

  case 327:
/* Line 1792 of yacc.c  */
#line 2534 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.extension_enum) = CPPExtensionType::T_enum_struct;
}
    break;

  case 328:
/* Line 1792 of yacc.c  */
#line 2541 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.extension_enum) = CPPExtensionType::T_class;
}
    break;

  case 329:
/* Line 1792 of yacc.c  */
#line 2545 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.extension_enum) = CPPExtensionType::T_struct;
}
    break;

  case 330:
/* Line 1792 of yacc.c  */
#line 2549 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.extension_enum) = CPPExtensionType::T_union;
}
    break;

  case 331:
/* Line 1792 of yacc.c  */
#line 2556 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPScope *scope = (yyvsp[(2) - (3)].u.identifier)->find_scope(current_scope, global_scope, current_lexer);
  if (scope == NULL) {
    // This must be a new namespace declaration.
    CPPScope *parent_scope =
      (yyvsp[(2) - (3)].u.identifier)->get_scope(current_scope, global_scope, current_lexer);
    if (parent_scope == NULL) {
      parent_scope = current_scope;
    }
    scope = new CPPScope(parent_scope, (yyvsp[(2) - (3)].u.identifier)->_names.back(), V_public);
  }

  CPPNamespace *nspace = new CPPNamespace((yyvsp[(2) - (3)].u.identifier), scope, (yylsp[(1) - (3)]).file);
  current_scope->add_declaration(nspace, global_scope, current_lexer, (yylsp[(1) - (3)]));
  current_scope->define_namespace(nspace);
  push_scope(scope);
}
    break;

  case 332:
/* Line 1792 of yacc.c  */
#line 2574 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_scope();
}
    break;

  case 333:
/* Line 1792 of yacc.c  */
#line 2578 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPScope *scope = (yyvsp[(3) - (4)].u.identifier)->find_scope(current_scope, global_scope, current_lexer);
  if (scope == NULL) {
    // This must be a new namespace declaration.
    CPPScope *parent_scope =
      (yyvsp[(3) - (4)].u.identifier)->get_scope(current_scope, global_scope, current_lexer);
    if (parent_scope == NULL) {
      parent_scope = current_scope;
    }
    scope = new CPPScope(parent_scope, (yyvsp[(3) - (4)].u.identifier)->_names.back(), V_public);
  }

  CPPNamespace *nspace = new CPPNamespace((yyvsp[(3) - (4)].u.identifier), scope, (yylsp[(2) - (4)]).file);
  nspace->_is_inline = true;
  current_scope->add_declaration(nspace, global_scope, current_lexer, (yylsp[(2) - (4)]));
  current_scope->define_namespace(nspace);
  push_scope(scope);
}
    break;

  case 334:
/* Line 1792 of yacc.c  */
#line 2597 "dtool/src/cppparser/cppBison.yxx"
    {
  pop_scope();
}
    break;

  case 337:
/* Line 1792 of yacc.c  */
#line 2606 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPUsing *using_decl = new CPPUsing((yyvsp[(2) - (3)].u.identifier), false, (yylsp[(1) - (3)]).file);
  current_scope->add_declaration(using_decl, global_scope, current_lexer, (yylsp[(1) - (3)]));
  current_scope->add_using(using_decl, global_scope, current_lexer);
}
    break;

  case 338:
/* Line 1792 of yacc.c  */
#line 2612 "dtool/src/cppparser/cppBison.yxx"
    {
  // This is really just an alternative way to declare a typedef.
  CPPTypedefType *typedef_type = new CPPTypedefType((yyvsp[(4) - (5)].u.type), (yyvsp[(2) - (5)].u.identifier), current_scope);
  typedef_type->_using = true;
  current_scope->add_declaration(CPPType::new_type(typedef_type), global_scope, current_lexer, (yylsp[(1) - (5)]));
}
    break;

  case 339:
/* Line 1792 of yacc.c  */
#line 2619 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPUsing *using_decl = new CPPUsing((yyvsp[(3) - (4)].u.identifier), true, (yylsp[(1) - (4)]).file);
  current_scope->add_declaration(using_decl, global_scope, current_lexer, (yylsp[(1) - (4)]));
  current_scope->add_using(using_decl, global_scope, current_lexer);
}
    break;

  case 343:
/* Line 1792 of yacc.c  */
#line 2634 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_bool);
}
    break;

  case 344:
/* Line 1792 of yacc.c  */
#line 2638 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_char);
}
    break;

  case 345:
/* Line 1792 of yacc.c  */
#line 2642 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_wchar_t);
}
    break;

  case 346:
/* Line 1792 of yacc.c  */
#line 2646 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_char16_t);
}
    break;

  case 347:
/* Line 1792 of yacc.c  */
#line 2650 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_char32_t);
}
    break;

  case 348:
/* Line 1792 of yacc.c  */
#line 2654 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int,
                         CPPSimpleType::F_short);
}
    break;

  case 349:
/* Line 1792 of yacc.c  */
#line 2659 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int,
                         CPPSimpleType::F_long);
}
    break;

  case 350:
/* Line 1792 of yacc.c  */
#line 2664 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int,
                         CPPSimpleType::F_unsigned);
}
    break;

  case 351:
/* Line 1792 of yacc.c  */
#line 2669 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int,
                         CPPSimpleType::F_signed);
}
    break;

  case 352:
/* Line 1792 of yacc.c  */
#line 2674 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_int);
}
    break;

  case 353:
/* Line 1792 of yacc.c  */
#line 2678 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = (yyvsp[(2) - (2)].u.simple_type);
  (yyval.u.simple_type)->_flags |= CPPSimpleType::F_short;
}
    break;

  case 354:
/* Line 1792 of yacc.c  */
#line 2683 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = (yyvsp[(2) - (2)].u.simple_type);
  if ((yyval.u.simple_type)->_flags & CPPSimpleType::F_long) {
    (yyval.u.simple_type)->_flags |= CPPSimpleType::F_longlong;
  } else {
    (yyval.u.simple_type)->_flags |= CPPSimpleType::F_long;
  }
}
    break;

  case 355:
/* Line 1792 of yacc.c  */
#line 2692 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = (yyvsp[(2) - (2)].u.simple_type);
  (yyval.u.simple_type)->_flags |= CPPSimpleType::F_unsigned;
}
    break;

  case 356:
/* Line 1792 of yacc.c  */
#line 2697 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = (yyvsp[(2) - (2)].u.simple_type);
  (yyval.u.simple_type)->_flags |= CPPSimpleType::F_signed;
}
    break;

  case 357:
/* Line 1792 of yacc.c  */
#line 2705 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_float);
}
    break;

  case 358:
/* Line 1792 of yacc.c  */
#line 2709 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_double);
}
    break;

  case 359:
/* Line 1792 of yacc.c  */
#line 2713 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_double,
                         CPPSimpleType::F_long);
}
    break;

  case 360:
/* Line 1792 of yacc.c  */
#line 2721 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.simple_type) = new CPPSimpleType(CPPSimpleType::T_void);
}
    break;

  case 361:
/* Line 1792 of yacc.c  */
#line 2730 "dtool/src/cppparser/cppBison.yxx"
    {
  current_lexer->_resolve_identifiers = false;
}
    break;

  case 362:
/* Line 1792 of yacc.c  */
#line 2734 "dtool/src/cppparser/cppBison.yxx"
    {
  current_lexer->_resolve_identifiers = true;
}
    break;

  case 465:
/* Line 1792 of yacc.c  */
#line 2775 "dtool/src/cppparser/cppBison.yxx"
    {
}
    break;

  case 489:
/* Line 1792 of yacc.c  */
#line 2784 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 490:
/* Line 1792 of yacc.c  */
#line 2788 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 491:
/* Line 1792 of yacc.c  */
#line 2795 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (CPPExpression *)NULL;
}
    break;

  case 492:
/* Line 1792 of yacc.c  */
#line 2799 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 493:
/* Line 1792 of yacc.c  */
#line 2806 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 494:
/* Line 1792 of yacc.c  */
#line 2810 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(',', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 495:
/* Line 1792 of yacc.c  */
#line 2817 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 496:
/* Line 1792 of yacc.c  */
#line 2821 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(2) - (4)].u.type), (yyvsp[(4) - (4)].u.expr)));
}
    break;

  case 497:
/* Line 1792 of yacc.c  */
#line 2825 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_static_cast));
}
    break;

  case 498:
/* Line 1792 of yacc.c  */
#line 2829 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_dynamic_cast));
}
    break;

  case 499:
/* Line 1792 of yacc.c  */
#line 2833 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_const_cast));
}
    break;

  case 500:
/* Line 1792 of yacc.c  */
#line 2837 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_reinterpret_cast));
}
    break;

  case 501:
/* Line 1792 of yacc.c  */
#line 2841 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func((yyvsp[(3) - (4)].u.type)));
}
    break;

  case 502:
/* Line 1792 of yacc.c  */
#line 2845 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::alignof_func((yyvsp[(3) - (4)].u.type)));
}
    break;

  case 503:
/* Line 1792 of yacc.c  */
#line 2849 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_NOT, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 504:
/* Line 1792 of yacc.c  */
#line 2853 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_NEGATE, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 505:
/* Line 1792 of yacc.c  */
#line 2857 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_MINUS, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 506:
/* Line 1792 of yacc.c  */
#line 2861 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_PLUS, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 507:
/* Line 1792 of yacc.c  */
#line 2865 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_STAR, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 508:
/* Line 1792 of yacc.c  */
#line 2869 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_REF, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 509:
/* Line 1792 of yacc.c  */
#line 2873 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('*', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 510:
/* Line 1792 of yacc.c  */
#line 2877 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('/', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 511:
/* Line 1792 of yacc.c  */
#line 2881 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('%', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 512:
/* Line 1792 of yacc.c  */
#line 2885 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('+', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 513:
/* Line 1792 of yacc.c  */
#line 2889 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('-', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 514:
/* Line 1792 of yacc.c  */
#line 2893 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('|', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 515:
/* Line 1792 of yacc.c  */
#line 2897 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('^', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 516:
/* Line 1792 of yacc.c  */
#line 2901 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('&', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 517:
/* Line 1792 of yacc.c  */
#line 2905 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(OROR, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 518:
/* Line 1792 of yacc.c  */
#line 2909 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(ANDAND, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 519:
/* Line 1792 of yacc.c  */
#line 2913 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(EQCOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 520:
/* Line 1792 of yacc.c  */
#line 2917 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(NECOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 521:
/* Line 1792 of yacc.c  */
#line 2921 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(LECOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 522:
/* Line 1792 of yacc.c  */
#line 2925 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(GECOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 523:
/* Line 1792 of yacc.c  */
#line 2929 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(LSHIFT, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 524:
/* Line 1792 of yacc.c  */
#line 2933 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(RSHIFT, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 525:
/* Line 1792 of yacc.c  */
#line 2937 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('?', (yyvsp[(1) - (5)].u.expr), (yyvsp[(3) - (5)].u.expr), (yyvsp[(5) - (5)].u.expr));
}
    break;

  case 526:
/* Line 1792 of yacc.c  */
#line 2941 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('[', (yyvsp[(1) - (4)].u.expr), (yyvsp[(3) - (4)].u.expr));
}
    break;

  case 527:
/* Line 1792 of yacc.c  */
#line 2945 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[(1) - (4)].u.expr), (yyvsp[(3) - (4)].u.expr));
}
    break;

  case 528:
/* Line 1792 of yacc.c  */
#line 2949 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[(1) - (3)].u.expr));
}
    break;

  case 529:
/* Line 1792 of yacc.c  */
#line 2953 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('.', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 530:
/* Line 1792 of yacc.c  */
#line 2957 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(POINTSAT, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 531:
/* Line 1792 of yacc.c  */
#line 2961 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(2) - (3)].u.expr);
}
    break;

  case 532:
/* Line 1792 of yacc.c  */
#line 2969 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 533:
/* Line 1792 of yacc.c  */
#line 2973 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(2) - (4)].u.type), (yyvsp[(4) - (4)].u.expr)));
}
    break;

  case 534:
/* Line 1792 of yacc.c  */
#line 2977 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_static_cast));
}
    break;

  case 535:
/* Line 1792 of yacc.c  */
#line 2981 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_dynamic_cast));
}
    break;

  case 536:
/* Line 1792 of yacc.c  */
#line 2985 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_const_cast));
}
    break;

  case 537:
/* Line 1792 of yacc.c  */
#line 2989 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_reinterpret_cast));
}
    break;

  case 538:
/* Line 1792 of yacc.c  */
#line 2993 "dtool/src/cppparser/cppBison.yxx"
    {
  // A constructor call.
  CPPType *type = (yyvsp[(1) - (4)].u.identifier)->find_type(current_scope, global_scope, false, current_lexer);
  if (type == NULL) {
    yyerror(string("internal error resolving type ") + (yyvsp[(1) - (4)].u.identifier)->get_fully_scoped_name(), (yylsp[(1) - (4)]));
  }
  assert(type != NULL);
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 539:
/* Line 1792 of yacc.c  */
#line 3003 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 540:
/* Line 1792 of yacc.c  */
#line 3009 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_char));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 541:
/* Line 1792 of yacc.c  */
#line 3015 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_wchar_t));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 542:
/* Line 1792 of yacc.c  */
#line 3021 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_char16_t));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 543:
/* Line 1792 of yacc.c  */
#line 3027 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_char32_t));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 544:
/* Line 1792 of yacc.c  */
#line 3033 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_bool));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 545:
/* Line 1792 of yacc.c  */
#line 3039 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int,
                                        CPPSimpleType::F_short));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 546:
/* Line 1792 of yacc.c  */
#line 3046 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int,
                                        CPPSimpleType::F_long));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 547:
/* Line 1792 of yacc.c  */
#line 3053 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int,
                                        CPPSimpleType::F_unsigned));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 548:
/* Line 1792 of yacc.c  */
#line 3060 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int,
                                        CPPSimpleType::F_signed));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 549:
/* Line 1792 of yacc.c  */
#line 3067 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_float));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 550:
/* Line 1792 of yacc.c  */
#line 3073 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type =
    CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_double));
  (yyval.u.expr) = new CPPExpression(CPPExpression::construct_op(type, (yyvsp[(3) - (4)].u.expr)));
}
    break;

  case 551:
/* Line 1792 of yacc.c  */
#line 3079 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func((yyvsp[(3) - (4)].u.type)));
}
    break;

  case 552:
/* Line 1792 of yacc.c  */
#line 3083 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::alignof_func((yyvsp[(3) - (4)].u.type)));
}
    break;

  case 553:
/* Line 1792 of yacc.c  */
#line 3087 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::new_op((yyvsp[(2) - (2)].u.type)));
}
    break;

  case 554:
/* Line 1792 of yacc.c  */
#line 3091 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::new_op((yyvsp[(2) - (5)].u.type), (yyvsp[(4) - (5)].u.expr)));
}
    break;

  case 555:
/* Line 1792 of yacc.c  */
#line 3095 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPIdentifier ident("");
  ident.add_name("std");
  ident.add_name("type_info");
  CPPType *std_type_info = ident.find_type(current_scope, global_scope, false, current_lexer);
  if (!std_type_info) {
    yywarning("cannot use typeid before including <typeinfo>", (yylsp[(1) - (4)]));
  }
  (yyval.u.expr) = new CPPExpression(CPPExpression::typeid_op((yyvsp[(3) - (4)].u.type), std_type_info));
}
    break;

  case 556:
/* Line 1792 of yacc.c  */
#line 3106 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPIdentifier ident("");
  ident.add_name("std");
  ident.add_name("type_info");
  CPPType *std_type_info = ident.find_type(current_scope, global_scope, false, current_lexer);
  if (!std_type_info) {
    yywarning("cannot use typeid before including <typeinfo>", (yylsp[(1) - (4)]));
  }
  (yyval.u.expr) = new CPPExpression(CPPExpression::typeid_op((yyvsp[(3) - (4)].u.expr), std_type_info));
}
    break;

  case 557:
/* Line 1792 of yacc.c  */
#line 3117 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_NOT, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 558:
/* Line 1792 of yacc.c  */
#line 3121 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_NEGATE, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 559:
/* Line 1792 of yacc.c  */
#line 3125 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_MINUS, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 560:
/* Line 1792 of yacc.c  */
#line 3129 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_PLUS, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 561:
/* Line 1792 of yacc.c  */
#line 3133 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_STAR, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 562:
/* Line 1792 of yacc.c  */
#line 3137 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_REF, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 563:
/* Line 1792 of yacc.c  */
#line 3141 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('*', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 564:
/* Line 1792 of yacc.c  */
#line 3145 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('/', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 565:
/* Line 1792 of yacc.c  */
#line 3149 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('%', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 566:
/* Line 1792 of yacc.c  */
#line 3153 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('+', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 567:
/* Line 1792 of yacc.c  */
#line 3157 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('-', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 568:
/* Line 1792 of yacc.c  */
#line 3161 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('|', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 569:
/* Line 1792 of yacc.c  */
#line 3165 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('^', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 570:
/* Line 1792 of yacc.c  */
#line 3169 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('&', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 571:
/* Line 1792 of yacc.c  */
#line 3173 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(OROR, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 572:
/* Line 1792 of yacc.c  */
#line 3177 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(ANDAND, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 573:
/* Line 1792 of yacc.c  */
#line 3181 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(EQCOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 574:
/* Line 1792 of yacc.c  */
#line 3185 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(NECOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 575:
/* Line 1792 of yacc.c  */
#line 3189 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(LECOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 576:
/* Line 1792 of yacc.c  */
#line 3193 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(GECOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 577:
/* Line 1792 of yacc.c  */
#line 3197 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('<', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 578:
/* Line 1792 of yacc.c  */
#line 3201 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('>', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 579:
/* Line 1792 of yacc.c  */
#line 3205 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(LSHIFT, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 580:
/* Line 1792 of yacc.c  */
#line 3209 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(RSHIFT, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 581:
/* Line 1792 of yacc.c  */
#line 3213 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('?', (yyvsp[(1) - (5)].u.expr), (yyvsp[(3) - (5)].u.expr), (yyvsp[(5) - (5)].u.expr));
}
    break;

  case 582:
/* Line 1792 of yacc.c  */
#line 3217 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('[', (yyvsp[(1) - (4)].u.expr), (yyvsp[(3) - (4)].u.expr));
}
    break;

  case 583:
/* Line 1792 of yacc.c  */
#line 3221 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[(1) - (4)].u.expr), (yyvsp[(3) - (4)].u.expr));
}
    break;

  case 584:
/* Line 1792 of yacc.c  */
#line 3225 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[(1) - (3)].u.expr));
}
    break;

  case 585:
/* Line 1792 of yacc.c  */
#line 3229 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('.', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 586:
/* Line 1792 of yacc.c  */
#line 3233 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(POINTSAT, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 587:
/* Line 1792 of yacc.c  */
#line 3237 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(2) - (3)].u.expr);
}
    break;

  case 588:
/* Line 1792 of yacc.c  */
#line 3244 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression((yyvsp[(1) - (1)].u.integer));
}
    break;

  case 589:
/* Line 1792 of yacc.c  */
#line 3248 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(true);
}
    break;

  case 590:
/* Line 1792 of yacc.c  */
#line 3252 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(false);
}
    break;

  case 591:
/* Line 1792 of yacc.c  */
#line 3256 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression((yyvsp[(1) - (1)].u.integer));
}
    break;

  case 592:
/* Line 1792 of yacc.c  */
#line 3260 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression((yyvsp[(1) - (1)].u.real));
}
    break;

  case 593:
/* Line 1792 of yacc.c  */
#line 3264 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 594:
/* Line 1792 of yacc.c  */
#line 3268 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 595:
/* Line 1792 of yacc.c  */
#line 3272 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression((yyvsp[(1) - (1)].u.identifier), current_scope, global_scope, current_lexer);
}
    break;

  case 596:
/* Line 1792 of yacc.c  */
#line 3276 "dtool/src/cppparser/cppBison.yxx"
    {
  // A variable named "final".  C++11 explicitly permits this.
  CPPIdentifier *ident = new CPPIdentifier("final", (yylsp[(1) - (1)]));
  (yyval.u.expr) = new CPPExpression(ident, current_scope, global_scope, current_lexer);
}
    break;

  case 597:
/* Line 1792 of yacc.c  */
#line 3282 "dtool/src/cppparser/cppBison.yxx"
    {
  // A variable named "override".  C++11 explicitly permits this.
  CPPIdentifier *ident = new CPPIdentifier("override", (yylsp[(1) - (1)]));
  (yyval.u.expr) = new CPPExpression(ident, current_scope, global_scope, current_lexer);
}
    break;

  case 598:
/* Line 1792 of yacc.c  */
#line 3288 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_nullptr());
}
    break;

  case 599:
/* Line 1792 of yacc.c  */
#line 3292 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = NULL;
}
    break;

  case 600:
/* Line 1792 of yacc.c  */
#line 3296 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = NULL;
}
    break;

  case 601:
/* Line 1792 of yacc.c  */
#line 3310 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 602:
/* Line 1792 of yacc.c  */
#line 3314 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(2) - (4)].u.type), (yyvsp[(4) - (4)].u.expr)));
}
    break;

  case 603:
/* Line 1792 of yacc.c  */
#line 3318 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_static_cast));
}
    break;

  case 604:
/* Line 1792 of yacc.c  */
#line 3322 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_dynamic_cast));
}
    break;

  case 605:
/* Line 1792 of yacc.c  */
#line 3326 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_const_cast));
}
    break;

  case 606:
/* Line 1792 of yacc.c  */
#line 3330 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::typecast_op((yyvsp[(3) - (7)].u.type), (yyvsp[(6) - (7)].u.expr), CPPExpression::T_reinterpret_cast));
}
    break;

  case 607:
/* Line 1792 of yacc.c  */
#line 3334 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::sizeof_func((yyvsp[(3) - (4)].u.type)));
}
    break;

  case 608:
/* Line 1792 of yacc.c  */
#line 3338 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::alignof_func((yyvsp[(3) - (4)].u.type)));
}
    break;

  case 609:
/* Line 1792 of yacc.c  */
#line 3342 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::new_op((yyvsp[(2) - (2)].u.type)));
}
    break;

  case 610:
/* Line 1792 of yacc.c  */
#line 3346 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::new_op((yyvsp[(2) - (5)].u.type), (yyvsp[(4) - (5)].u.expr)));
}
    break;

  case 611:
/* Line 1792 of yacc.c  */
#line 3350 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPIdentifier ident("");
  ident.add_name("std");
  ident.add_name("type_info");
  CPPType *std_type_info = ident.find_type(current_scope, global_scope, false, current_lexer);
  if (!std_type_info) {
    yywarning("cannot use typeid before including <typeinfo>", (yylsp[(1) - (4)]));
  }
  (yyval.u.expr) = new CPPExpression(CPPExpression::typeid_op((yyvsp[(3) - (4)].u.type), std_type_info));
}
    break;

  case 612:
/* Line 1792 of yacc.c  */
#line 3361 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPIdentifier ident("");
  ident.add_name("std");
  ident.add_name("type_info");
  CPPType *std_type_info = ident.find_type(current_scope, global_scope, false, current_lexer);
  if (!std_type_info) {
    yywarning("cannot use typeid before including <typeinfo>", (yylsp[(1) - (4)]));
  }
  (yyval.u.expr) = new CPPExpression(CPPExpression::typeid_op((yyvsp[(3) - (4)].u.expr), std_type_info));
}
    break;

  case 613:
/* Line 1792 of yacc.c  */
#line 3372 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_NOT, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 614:
/* Line 1792 of yacc.c  */
#line 3376 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_NEGATE, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 615:
/* Line 1792 of yacc.c  */
#line 3380 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_MINUS, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 616:
/* Line 1792 of yacc.c  */
#line 3384 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_PLUS, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 617:
/* Line 1792 of yacc.c  */
#line 3388 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(UNARY_REF, (yyvsp[(2) - (2)].u.expr));
}
    break;

  case 618:
/* Line 1792 of yacc.c  */
#line 3392 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('*', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 619:
/* Line 1792 of yacc.c  */
#line 3396 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('/', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 620:
/* Line 1792 of yacc.c  */
#line 3400 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('%', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 621:
/* Line 1792 of yacc.c  */
#line 3404 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('+', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 622:
/* Line 1792 of yacc.c  */
#line 3408 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('-', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 623:
/* Line 1792 of yacc.c  */
#line 3412 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('|', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 624:
/* Line 1792 of yacc.c  */
#line 3416 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('^', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 625:
/* Line 1792 of yacc.c  */
#line 3420 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('&', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 626:
/* Line 1792 of yacc.c  */
#line 3424 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(OROR, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 627:
/* Line 1792 of yacc.c  */
#line 3428 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(ANDAND, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 628:
/* Line 1792 of yacc.c  */
#line 3432 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(EQCOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 629:
/* Line 1792 of yacc.c  */
#line 3436 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(NECOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 630:
/* Line 1792 of yacc.c  */
#line 3440 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(LECOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 631:
/* Line 1792 of yacc.c  */
#line 3444 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(GECOMPARE, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 632:
/* Line 1792 of yacc.c  */
#line 3448 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('<', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 633:
/* Line 1792 of yacc.c  */
#line 3452 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('>', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 634:
/* Line 1792 of yacc.c  */
#line 3456 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(LSHIFT, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 635:
/* Line 1792 of yacc.c  */
#line 3460 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(RSHIFT, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 636:
/* Line 1792 of yacc.c  */
#line 3464 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('?', (yyvsp[(1) - (5)].u.expr), (yyvsp[(3) - (5)].u.expr), (yyvsp[(5) - (5)].u.expr));
}
    break;

  case 637:
/* Line 1792 of yacc.c  */
#line 3468 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('[', (yyvsp[(1) - (4)].u.expr), (yyvsp[(3) - (4)].u.expr));
}
    break;

  case 638:
/* Line 1792 of yacc.c  */
#line 3472 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[(1) - (4)].u.expr), (yyvsp[(3) - (4)].u.expr));
}
    break;

  case 639:
/* Line 1792 of yacc.c  */
#line 3476 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('f', (yyvsp[(1) - (3)].u.expr));
}
    break;

  case 640:
/* Line 1792 of yacc.c  */
#line 3480 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression('.', (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 641:
/* Line 1792 of yacc.c  */
#line 3484 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(POINTSAT, (yyvsp[(1) - (3)].u.expr), (yyvsp[(3) - (3)].u.expr));
}
    break;

  case 642:
/* Line 1792 of yacc.c  */
#line 3488 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(2) - (3)].u.expr);
}
    break;

  case 643:
/* Line 1792 of yacc.c  */
#line 3495 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression((yyvsp[(1) - (1)].u.integer));
}
    break;

  case 644:
/* Line 1792 of yacc.c  */
#line 3499 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(true);
}
    break;

  case 645:
/* Line 1792 of yacc.c  */
#line 3503 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(false);
}
    break;

  case 646:
/* Line 1792 of yacc.c  */
#line 3507 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression((yyvsp[(1) - (1)].u.integer));
}
    break;

  case 647:
/* Line 1792 of yacc.c  */
#line 3511 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression((yyvsp[(1) - (1)].u.real));
}
    break;

  case 648:
/* Line 1792 of yacc.c  */
#line 3515 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 649:
/* Line 1792 of yacc.c  */
#line 3519 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 650:
/* Line 1792 of yacc.c  */
#line 3523 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression((yyvsp[(1) - (1)].u.identifier), current_scope, global_scope, current_lexer);
}
    break;

  case 651:
/* Line 1792 of yacc.c  */
#line 3527 "dtool/src/cppparser/cppBison.yxx"
    {
  // A variable named "final".  C++11 explicitly permits this.
  CPPIdentifier *ident = new CPPIdentifier("final", (yylsp[(1) - (1)]));
  (yyval.u.expr) = new CPPExpression(ident, current_scope, global_scope, current_lexer);
}
    break;

  case 652:
/* Line 1792 of yacc.c  */
#line 3533 "dtool/src/cppparser/cppBison.yxx"
    {
  // A variable named "override".  C++11 explicitly permits this.
  CPPIdentifier *ident = new CPPIdentifier("override", (yylsp[(1) - (1)]));
  (yyval.u.expr) = new CPPExpression(ident, current_scope, global_scope, current_lexer);
}
    break;

  case 653:
/* Line 1792 of yacc.c  */
#line 3539 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression(CPPExpression::get_nullptr());
}
    break;

  case 661:
/* Line 1792 of yacc.c  */
#line 3560 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type = (yyvsp[(1) - (1)].u.identifier)->find_type(current_scope, global_scope, true);
  if (type == NULL) {
    type = CPPType::new_type(new CPPTBDType((yyvsp[(1) - (1)].u.identifier)));
  }
  (yyval.u.type) = type;
}
    break;

  case 662:
/* Line 1792 of yacc.c  */
#line 3568 "dtool/src/cppparser/cppBison.yxx"
    {
  CPPType *type = (yyvsp[(2) - (2)].u.identifier)->find_type(current_scope, global_scope, true, current_lexer);
  if (type == NULL) {
    type = CPPType::new_type(new CPPTBDType((yyvsp[(2) - (2)].u.identifier)));
  }
  (yyval.u.type) = type;
}
    break;

  case 663:
/* Line 1792 of yacc.c  */
#line 3576 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.type) = CPPType::new_type(new CPPTBDType((yyvsp[(2) - (2)].u.identifier)));
}
    break;

  case 664:
/* Line 1792 of yacc.c  */
#line 3604 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = (yyvsp[(1) - (1)].u.identifier);
}
    break;

  case 665:
/* Line 1792 of yacc.c  */
#line 3608 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = (yyvsp[(1) - (1)].u.identifier);
}
    break;

  case 666:
/* Line 1792 of yacc.c  */
#line 3612 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = new CPPIdentifier("final", (yylsp[(1) - (1)]));
}
    break;

  case 667:
/* Line 1792 of yacc.c  */
#line 3616 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = new CPPIdentifier("override", (yylsp[(1) - (1)]));
}
    break;

  case 668:
/* Line 1792 of yacc.c  */
#line 3620 "dtool/src/cppparser/cppBison.yxx"
    {
  // This is not a keyword in Python, so it is useful to be able to use this
  // in MAKE_PROPERTY definitions, etc.
  (yyval.u.identifier) = new CPPIdentifier("signed", (yylsp[(1) - (1)]));
}
    break;

  case 669:
/* Line 1792 of yacc.c  */
#line 3626 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = new CPPIdentifier("float", (yylsp[(1) - (1)]));
}
    break;

  case 670:
/* Line 1792 of yacc.c  */
#line 3630 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = new CPPIdentifier("public", (yylsp[(1) - (1)]));
}
    break;

  case 671:
/* Line 1792 of yacc.c  */
#line 3634 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = new CPPIdentifier("private", (yylsp[(1) - (1)]));
}
    break;

  case 672:
/* Line 1792 of yacc.c  */
#line 3638 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = new CPPIdentifier("static", (yylsp[(1) - (1)]));
}
    break;

  case 673:
/* Line 1792 of yacc.c  */
#line 3649 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = (yyvsp[(1) - (1)].u.identifier);
}
    break;

  case 674:
/* Line 1792 of yacc.c  */
#line 3653 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = (yyvsp[(1) - (1)].u.identifier);
}
    break;

  case 675:
/* Line 1792 of yacc.c  */
#line 3657 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.identifier) = new CPPIdentifier("override", (yylsp[(1) - (1)]));
}
    break;

  case 676:
/* Line 1792 of yacc.c  */
#line 3665 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = new CPPExpression((yyvsp[(1) - (1)].str));
}
    break;

  case 677:
/* Line 1792 of yacc.c  */
#line 3669 "dtool/src/cppparser/cppBison.yxx"
    {
  (yyval.u.expr) = (yyvsp[(1) - (1)].u.expr);
}
    break;

  case 678:
/* Line 1792 of yacc.c  */
#line 3673 "dtool/src/cppparser/cppBison.yxx"
    {
  // The right string takes on the literal type of the left.
  (yyval.u.expr) = (yyvsp[(1) - (2)].u.expr);
  (yyval.u.expr)->_str += (yyvsp[(2) - (2)].str);
}
    break;

  case 679:
/* Line 1792 of yacc.c  */
#line 3679 "dtool/src/cppparser/cppBison.yxx"
    {
  // We have to check that the two literal types match up.
  (yyval.u.expr) = (yyvsp[(1) - (2)].u.expr);
  if ((yyvsp[(2) - (2)].u.expr)->_type != CPPExpression::T_string && (yyvsp[(2) - (2)].u.expr)->_type != (yyvsp[(1) - (2)].u.expr)->_type) {
    yywarning("cannot concatenate two string literals of different types", (yyloc));
  }
  (yyval.u.expr)->_str += (yyvsp[(2) - (2)].u.expr)->_str;
}
    break;


/* Line 1792 of yacc.c  */
#line 8881 "built/tmp/cppBison.yxx.c"
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


