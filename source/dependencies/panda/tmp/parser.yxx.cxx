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
#define yyparse         eggyyparse
#define yylex           eggyylex
#define yyerror         eggyyerror
#define yylval          eggyylval
#define yychar          eggyychar
#define yydebug         eggyydebug
#define yynerrs         eggyynerrs

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 7 "panda/src/egg/parser.yxx"


#include "pandabase.h"
#include "config_egg.h"
#include "parserDefs.h"
#include "lexerDefs.h"
#include "eggObject.h"
#include "eggGroup.h"
#include "eggVertex.h"
#include "eggVertexPool.h"
#include "eggVertexUV.h"
#include "eggVertexAux.h"
#include "eggPolygon.h"
#include "eggCompositePrimitive.h"
#include "eggTriangleFan.h"
#include "eggTriangleStrip.h"
#include "eggPatch.h"
#include "eggPoint.h"
#include "eggLine.h"
#include "eggNurbsSurface.h"
#include "eggNurbsCurve.h"
#include "eggTable.h"
#include "eggSAnimData.h"
#include "eggXfmSAnim.h"
#include "eggXfmAnimData.h"
#include "eggTexture.h"
#include "eggMaterial.h"
#include "eggComment.h"
#include "eggCoordinateSystem.h"
#include "eggExternalReference.h"
#include "eggData.h"
#include "eggAnimPreload.h"
#include "eggTransform.h"
#include "pt_EggTexture.h"
#include "pt_EggMaterial.h"

#include "string_utils.h"
#include "filename.h"
#include "luse.h"
#include "lmatrix.h"
#include "coordinateSystem.h"
#include "pvector.h"
#include "dcast.h"
#include "thread.h"

// Because our token type contains objects of type string, which
// require correct copy construction (and not simply memcpying), we
// cannot use bison's built-in auto-stack-grow feature.  As an easy
// solution, we ensure here that we have enough yacc stack to start
// with, and that it doesn't ever try to grow.
#define YYINITDEPTH 1000
#define YYMAXDEPTH 1000

// We need a stack of EggObject pointers.  Each time we encounter a
// nested EggObject of some kind, we'll allocate a new one of these
// and push it onto the stack.  At any given time, the top of the
// stack is the EggObject we are currently scanning.

typedef pvector< PT(EggObject) > EggStack;
static EggStack egg_stack;

// This is used just when parsing a <Transform> or <DefaultPose> entry.
static EggTransform *egg_top_transform;

// There's one "top-level" egg node, which is where we should parent
// things (e.g. implicit textures) encountered in the egg file that
// don't have an explicit place in the tree.  If this is NULL, such
// things won't be parented anywhere.
static EggGroupNode *egg_top_node;

// We need a table mapping vertex pool names to vertex pools.
typedef pmap<string,  PT(EggVertexPool) > VertexPools;
static VertexPools vertex_pools;

// And another one mapping texture names to textures.
typedef pmap<string,  PT_EggTexture > Textures;
static Textures textures;

// And again for material names to materials.
typedef pmap<string,  PT_EggMaterial > Materials;
static Materials materials;

// Group names to groups.
typedef pmap<string,  PT(EggGroup) > Groups;
static Groups groups;

// We need to be able to save the index number requested for a vertex
// temporarily.
static int vertex_index;

// We need to hold a matrix for a little bit while parsing the
// <Transform> entries.
static LMatrix3d matrix_2d;


////////////////////////////////////////////////////////////////////
// Defining the interface to the parser.
////////////////////////////////////////////////////////////////////

void
egg_init_parser(istream &in, const string &filename,
                EggObject *tos, EggGroupNode *top_node) {
  egg_init_lexer(in, filename);

  egg_stack.clear();
  vertex_pools.clear();
  textures.clear();
  materials.clear();
  groups.clear();

  egg_stack.push_back(tos);
  egg_top_node = top_node;
}

void
egg_cleanup_parser() {
  // Check for undefined vertex pools.
  VertexPools::const_iterator vpi;
  for (vpi = vertex_pools.begin(); vpi != vertex_pools.end(); ++vpi) {
    EggVertexPool *pool = (*vpi).second;
    if (pool->has_forward_vertices()) {
      if (!pool->has_defined_vertices()) {
        eggyyerror("Undefined vertex pool " + pool->get_name());
      } else {
        eggyyerror("Undefined vertices in pool " + pool->get_name());

        egg_cat.error(false)
          << "Undefined vertex index numbers:";
        EggVertexPool::const_iterator vi;
        for (vi = pool->begin(); vi != pool->end(); ++vi) {
          EggVertex *vertex = (*vi);
          if (vertex->is_forward_reference()) {
            egg_cat.error(false)
              << " " << vertex->get_index();
          }
        }
        egg_cat.error(false)
          << "\n";
      }
    }
  }

  // Clean these out after we're done, so we don't keep big memory
  // structures around needlessly.
  egg_stack.clear();
  vertex_pools.clear();
  textures.clear();
  materials.clear();
  groups.clear();
}


/* Line 371 of yacc.c  */
#line 228 "built/tmp/parser.yxx.c"

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
   by #include "parser.yxx.h".  */
#ifndef YY_EGGYY_BUILT_TMP_PARSER_YXX_H_INCLUDED
# define YY_EGGYY_BUILT_TMP_PARSER_YXX_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int eggyydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EGG_NUMBER = 258,
     EGG_ULONG = 259,
     EGG_STRING = 260,
     ANIMPRELOAD = 261,
     BEZIERCURVE = 262,
     BFACE = 263,
     BILLBOARD = 264,
     BILLBOARDCENTER = 265,
     BINORMAL = 266,
     BUNDLE = 267,
     CLOSED = 268,
     COLLIDE = 269,
     COMMENT = 270,
     COMPONENT = 271,
     COORDSYSTEM = 272,
     CV = 273,
     DART = 274,
     DNORMAL = 275,
     DRGBA = 276,
     DUV = 277,
     DXYZ = 278,
     DCS = 279,
     DISTANCE = 280,
     DTREF = 281,
     DYNAMICVERTEXPOOL = 282,
     EXTERNAL_FILE = 283,
     GROUP = 284,
     DEFAULTPOSE = 285,
     JOINT = 286,
     KNOTS = 287,
     INCLUDE = 288,
     INSTANCE = 289,
     LINE = 290,
     LOOP = 291,
     MATERIAL = 292,
     MATRIX3 = 293,
     MATRIX4 = 294,
     MODEL = 295,
     MREF = 296,
     NORMAL = 297,
     NURBSCURVE = 298,
     NURBSSURFACE = 299,
     OBJECTTYPE = 300,
     ORDER = 301,
     OUTTANGENT = 302,
     PATCH = 303,
     POINTLIGHT = 304,
     POLYGON = 305,
     REF = 306,
     RGBA = 307,
     ROTATE = 308,
     ROTX = 309,
     ROTY = 310,
     ROTZ = 311,
     SANIM = 312,
     SCALAR = 313,
     SCALE = 314,
     SEQUENCE = 315,
     SHADING = 316,
     SWITCH = 317,
     SWITCHCONDITION = 318,
     TABLE = 319,
     TABLE_V = 320,
     TAG = 321,
     TANGENT = 322,
     TEXLIST = 323,
     TEXTURE = 324,
     TLENGTHS = 325,
     TRANSFORM = 326,
     TRANSLATE = 327,
     TREF = 328,
     TRIANGLEFAN = 329,
     TRIANGLESTRIP = 330,
     TRIM = 331,
     TXT = 332,
     UKNOTS = 333,
     UV = 334,
     AUX = 335,
     VKNOTS = 336,
     VERTEX = 337,
     VERTEXANIM = 338,
     VERTEXPOOL = 339,
     VERTEXREF = 340,
     XFMANIM = 341,
     XFMSANIM = 342,
     START_EGG = 343,
     START_GROUP_BODY = 344,
     START_TEXTURE_BODY = 345,
     START_PRIMITIVE_BODY = 346
   };
#endif
/* Tokens.  */
#define EGG_NUMBER 258
#define EGG_ULONG 259
#define EGG_STRING 260
#define ANIMPRELOAD 261
#define BEZIERCURVE 262
#define BFACE 263
#define BILLBOARD 264
#define BILLBOARDCENTER 265
#define BINORMAL 266
#define BUNDLE 267
#define CLOSED 268
#define COLLIDE 269
#define COMMENT 270
#define COMPONENT 271
#define COORDSYSTEM 272
#define CV 273
#define DART 274
#define DNORMAL 275
#define DRGBA 276
#define DUV 277
#define DXYZ 278
#define DCS 279
#define DISTANCE 280
#define DTREF 281
#define DYNAMICVERTEXPOOL 282
#define EXTERNAL_FILE 283
#define GROUP 284
#define DEFAULTPOSE 285
#define JOINT 286
#define KNOTS 287
#define INCLUDE 288
#define INSTANCE 289
#define LINE 290
#define LOOP 291
#define MATERIAL 292
#define MATRIX3 293
#define MATRIX4 294
#define MODEL 295
#define MREF 296
#define NORMAL 297
#define NURBSCURVE 298
#define NURBSSURFACE 299
#define OBJECTTYPE 300
#define ORDER 301
#define OUTTANGENT 302
#define PATCH 303
#define POINTLIGHT 304
#define POLYGON 305
#define REF 306
#define RGBA 307
#define ROTATE 308
#define ROTX 309
#define ROTY 310
#define ROTZ 311
#define SANIM 312
#define SCALAR 313
#define SCALE 314
#define SEQUENCE 315
#define SHADING 316
#define SWITCH 317
#define SWITCHCONDITION 318
#define TABLE 319
#define TABLE_V 320
#define TAG 321
#define TANGENT 322
#define TEXLIST 323
#define TEXTURE 324
#define TLENGTHS 325
#define TRANSFORM 326
#define TRANSLATE 327
#define TREF 328
#define TRIANGLEFAN 329
#define TRIANGLESTRIP 330
#define TRIM 331
#define TXT 332
#define UKNOTS 333
#define UV 334
#define AUX 335
#define VKNOTS 336
#define VERTEX 337
#define VERTEXANIM 338
#define VERTEXPOOL 339
#define VERTEXREF 340
#define XFMANIM 341
#define XFMSANIM 342
#define START_EGG 343
#define START_GROUP_BODY 344
#define START_TEXTURE_BODY 345
#define START_PRIMITIVE_BODY 346



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE eggyylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int eggyyparse (void *YYPARSE_PARAM);
#else
int eggyyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int eggyyparse (void);
#else
int eggyyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_EGGYY_BUILT_TMP_PARSER_YXX_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 475 "built/tmp/parser.yxx.c"

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1536

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  127
/* YYNRULES -- Number of rules.  */
#define YYNRULES  277
/* YYNRULES -- Number of states.  */
#define YYNSTATES  763

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   346

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
       2,     2,     2,    92,     2,    93,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    17,    20,    22,
      24,    26,    28,    30,    32,    34,    36,    38,    40,    42,
      44,    46,    48,    50,    52,    54,    56,    58,    63,    69,
      70,    78,    80,    87,    90,    91,    98,   100,   107,   113,
     120,   121,   128,   130,   133,   134,   140,   141,   148,   150,
     153,   157,   162,   163,   171,   172,   180,   186,   192,   201,
     210,   213,   217,   225,   233,   241,   250,   258,   267,   268,
     273,   277,   286,   295,   300,   310,   320,   321,   328,   329,
     336,   337,   344,   346,   353,   359,   367,   375,   381,   387,
     393,   399,   405,   411,   417,   424,   430,   433,   436,   439,
     442,   448,   451,   453,   455,   458,   459,   465,   466,   472,
     474,   477,   480,   483,   486,   489,   492,   495,   498,   501,
     504,   507,   510,   516,   523,   528,   533,   538,   543,   551,
     557,   564,   569,   574,   576,   586,   591,   593,   610,   620,
     622,   629,   634,   646,   659,   660,   667,   668,   675,   676,
     683,   684,   691,   692,   699,   700,   707,   708,   715,   716,
     723,   725,   731,   737,   739,   740,   748,   754,   760,   766,
     769,   775,   781,   787,   794,   796,   802,   808,   814,   817,
     823,   829,   835,   841,   847,   853,   856,   862,   869,   871,
     877,   883,   889,   892,   898,   904,   910,   916,   922,   929,
     931,   933,   935,   939,   948,   957,   962,   972,   982,   984,
     993,   996,   998,  1000,  1002,  1008,  1010,  1013,  1015,  1017,
    1018,  1025,  1026,  1033,  1035,  1038,  1041,  1044,  1047,  1050,
    1051,  1058,  1060,  1067,  1073,  1074,  1081,  1083,  1090,  1096,
    1097,  1104,  1106,  1113,  1116,  1117,  1124,  1126,  1133,  1135,
    1138,  1140,  1143,  1145,  1147,  1149,  1151,  1153,  1155,  1157,
    1159,  1161,  1163,  1165,  1167,  1169,  1171,  1173,  1175,  1177,
    1180,  1182,  1184,  1186,  1188,  1190,  1192,  1194
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      95,     0,    -1,    88,    96,    -1,    89,   126,    -1,    90,
     102,    -1,    91,   169,    -1,   220,    -1,    96,    97,    -1,
      98,    -1,    99,    -1,   100,    -1,   103,    -1,   106,    -1,
     107,    -1,   120,    -1,   122,    -1,   124,    -1,   152,    -1,
     154,    -1,   156,    -1,   158,    -1,   160,    -1,   162,    -1,
     164,    -1,   166,    -1,   187,    -1,   201,    -1,    17,    92,
     212,    93,    -1,    15,   211,    92,   215,    93,    -1,    -1,
      69,   210,    92,   212,   101,   102,    93,    -1,   220,    -1,
     102,    58,   210,    92,   218,    93,    -1,   102,   129,    -1,
      -1,    37,   210,    92,   104,   105,    93,    -1,   220,    -1,
     105,    58,   210,    92,   218,    93,    -1,    28,   211,    92,
     212,    93,    -1,   214,    28,   211,    92,   212,    93,    -1,
      -1,    84,   210,   108,    92,   109,    93,    -1,   220,    -1,
     109,   110,    -1,    -1,    82,   111,    92,   113,    93,    -1,
      -1,    82,   219,   112,    92,   113,    93,    -1,   217,    -1,
     217,   217,    -1,   217,   217,   217,    -1,   217,   217,   217,
     217,    -1,    -1,   113,    79,   211,    92,   114,   116,    93,
      -1,    -1,   113,    80,   210,    92,   115,   117,    93,    -1,
     113,    42,    92,   118,    93,    -1,   113,    52,    92,   119,
      93,    -1,   113,    23,   214,    92,   217,   217,   217,    93,
      -1,   113,    23,    92,   214,   217,   217,   217,    93,    -1,
     217,   217,    -1,   217,   217,   217,    -1,   116,    67,    92,
     217,   217,   217,    93,    -1,   116,    11,    92,   217,   217,
     217,    93,    -1,   116,    22,   214,    92,   217,   217,    93,
      -1,   116,    22,   214,    92,   217,   217,   217,    93,    -1,
     116,    22,    92,   214,   217,   217,    93,    -1,   116,    22,
      92,   214,   217,   217,   217,    93,    -1,    -1,   217,   217,
     217,   217,    -1,   217,   217,   217,    -1,   118,    20,   214,
      92,   217,   217,   217,    93,    -1,   118,    20,    92,   214,
     217,   217,   217,    93,    -1,   217,   217,   217,   217,    -1,
     119,    21,   214,    92,   217,   217,   217,   217,    93,    -1,
     119,    21,    92,   214,   217,   217,   217,   217,    93,    -1,
      -1,    29,   211,   121,    92,   126,    93,    -1,    -1,    31,
     211,   123,    92,   126,    93,    -1,    -1,    34,   211,   125,
      92,   126,    93,    -1,   220,    -1,   126,    58,   210,    92,
     218,    93,    -1,   126,     9,    92,   214,    93,    -1,   126,
      10,    92,   217,   217,   217,    93,    -1,   126,    14,   211,
      92,   127,   128,    93,    -1,   126,    24,    92,   219,    93,
      -1,   126,    24,    92,     5,    93,    -1,   126,    19,    92,
     219,    93,    -1,   126,    19,    92,     5,    93,    -1,   126,
      62,    92,   219,    93,    -1,   126,    45,    92,   212,    93,
      -1,   126,    40,    92,   219,    93,    -1,   126,    66,   211,
      92,   215,    93,    -1,   126,    68,    92,   219,    93,    -1,
     126,   129,    -1,   126,   131,    -1,   126,   148,    -1,   126,
     150,    -1,   126,    51,    92,   209,    93,    -1,   126,    97,
      -1,   214,    -1,   220,    -1,   128,   214,    -1,    -1,    71,
     130,    92,   133,    93,    -1,    -1,    30,   132,    92,   133,
      93,    -1,   220,    -1,   133,   134,    -1,   133,   135,    -1,
     133,   136,    -1,   133,   137,    -1,   133,   138,    -1,   133,
     139,    -1,   133,   140,    -1,   133,   141,    -1,   133,   142,
      -1,   133,   143,    -1,   133,   144,    -1,   133,   146,    -1,
      72,    92,   217,   217,    93,    -1,    72,    92,   217,   217,
     217,    93,    -1,    53,    92,   217,    93,    -1,    54,    92,
     217,    93,    -1,    55,    92,   217,    93,    -1,    56,    92,
     217,    93,    -1,    53,    92,   217,   217,   217,   217,    93,
      -1,    59,    92,   217,   217,    93,    -1,    59,    92,   217,
     217,   217,    93,    -1,    59,    92,   217,    93,    -1,    38,
      92,   145,    93,    -1,   220,    -1,   217,   217,   217,   217,
     217,   217,   217,   217,   217,    -1,    39,    92,   147,    93,
      -1,   220,    -1,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,    -1,
      85,    92,   204,   149,    51,    92,   208,    93,    93,    -1,
     220,    -1,   149,    58,   210,    92,   218,    93,    -1,    63,
      92,   151,    93,    -1,    25,    92,   217,   217,    82,    92,
     217,   217,   217,    93,    93,    -1,    25,    92,   217,   217,
     217,    82,    92,   217,   217,   217,    93,    93,    -1,    -1,
      50,   211,   153,    92,   169,    93,    -1,    -1,    74,   211,
     155,    92,   169,    93,    -1,    -1,    75,   211,   157,    92,
     169,    93,    -1,    -1,    48,   211,   159,    92,   169,    93,
      -1,    -1,    49,   211,   161,    92,   169,    93,    -1,    -1,
      35,   211,   163,    92,   169,    93,    -1,    -1,    44,   211,
     165,    92,   171,    93,    -1,    -1,    43,   211,   167,    92,
     172,    93,    -1,   220,    -1,   168,    42,    92,   176,    93,
      -1,   168,    52,    92,   177,    93,    -1,   220,    -1,    -1,
     169,    16,   219,    92,   170,   168,    93,    -1,   169,    73,
      92,   173,    93,    -1,   169,    69,    92,   174,    93,    -1,
     169,    41,    92,   175,    93,    -1,   169,   179,    -1,   169,
      42,    92,   176,    93,    -1,   169,    52,    92,   177,    93,
      -1,   169,     8,    92,   178,    93,    -1,   169,    58,   210,
      92,   218,    93,    -1,   220,    -1,   171,    73,    92,   173,
      93,    -1,   171,    69,    92,   174,    93,    -1,   171,    41,
      92,   175,    93,    -1,   171,   179,    -1,   171,    42,    92,
     176,    93,    -1,   171,    52,    92,   177,    93,    -1,   171,
       8,    92,   178,    93,    -1,   171,    46,    92,   180,    93,
      -1,   171,    78,    92,   181,    93,    -1,   171,    81,    92,
     182,    93,    -1,   171,   166,    -1,   171,    76,    92,   183,
      93,    -1,   171,    58,   210,    92,   218,    93,    -1,   220,
      -1,   172,    73,    92,   173,    93,    -1,   172,    69,    92,
     174,    93,    -1,   172,    41,    92,   175,    93,    -1,   172,
     179,    -1,   172,    42,    92,   176,    93,    -1,   172,    52,
      92,   177,    93,    -1,   172,     8,    92,   178,    93,    -1,
     172,    46,    92,   185,    93,    -1,   172,    32,    92,   186,
      93,    -1,   172,    58,   210,    92,   218,    93,    -1,   206,
      -1,   210,    -1,   207,    -1,   217,   217,   217,    -1,   176,
      20,   214,    92,   217,   217,   217,    93,    -1,   176,    20,
      92,   214,   217,   217,   217,    93,    -1,   217,   217,   217,
     217,    -1,   177,    21,   214,    92,   217,   217,   217,   217,
      93,    -1,   177,    21,    92,   214,   217,   217,   217,   217,
      93,    -1,   219,    -1,    85,    92,   204,    51,    92,   208,
      93,    93,    -1,   219,   219,    -1,   205,    -1,   205,    -1,
     220,    -1,   183,    36,    92,   184,    93,    -1,   220,    -1,
     184,   166,    -1,   219,    -1,   205,    -1,    -1,    64,   211,
     188,    92,   191,    93,    -1,    -1,    12,   211,   190,    92,
     191,    93,    -1,   220,    -1,   191,   187,    -1,   191,   189,
      -1,   191,   192,    -1,   191,   195,    -1,   191,   198,    -1,
      -1,    57,   211,   193,    92,   194,    93,    -1,   220,    -1,
     194,    58,   210,    92,   218,    93,    -1,   194,    65,    92,
     205,    93,    -1,    -1,    86,   211,   196,    92,   197,    93,
      -1,   220,    -1,   197,    58,   210,    92,   218,    93,    -1,
     197,    65,    92,   205,    93,    -1,    -1,    87,   211,   199,
      92,   200,    93,    -1,   220,    -1,   200,    58,   210,    92,
     218,    93,    -1,   200,   192,    -1,    -1,     6,   211,   202,
      92,   203,    93,    -1,   220,    -1,   203,    58,   210,    92,
     218,    93,    -1,   220,    -1,   204,   219,    -1,   220,    -1,
     205,   217,    -1,   210,    -1,   210,    -1,   210,    -1,   210,
      -1,   220,    -1,   214,    -1,   213,    -1,   220,    -1,   214,
      -1,   220,    -1,   214,    -1,     3,    -1,     4,    -1,     5,
      -1,   220,    -1,   216,    -1,   214,    -1,   216,   214,    -1,
       3,    -1,     4,    -1,     3,    -1,     4,    -1,     5,    -1,
       3,    -1,     4,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   235,   235,   236,   237,   238,   249,   250,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   295,   318,   333,
     332,   360,   361,   716,   728,   727,   754,   755,   876,   883,
     904,   903,   943,   944,   956,   955,   967,   966,  1012,  1016,
    1020,  1024,  1029,  1028,  1044,  1043,  1058,  1059,  1060,  1068,
    1087,  1091,  1095,  1103,  1111,  1119,  1127,  1135,  1152,  1153,
    1167,  1171,  1179,  1197,  1201,  1209,  1228,  1227,  1253,  1252,
    1274,  1273,  1298,  1299,  1447,  1459,  1464,  1471,  1477,  1490,
    1497,  1510,  1516,  1522,  1528,  1533,  1539,  1540,  1541,  1542,
    1543,  1552,  1566,  1596,  1597,  1620,  1619,  1636,  1635,  1656,
    1657,  1658,  1659,  1660,  1661,  1662,  1663,  1664,  1665,  1666,
    1667,  1668,  1672,  1679,  1686,  1693,  1700,  1707,  1714,  1721,
    1728,  1735,  1742,  1746,  1747,  1759,  1763,  1764,  1786,  1819,
    1823,  1848,  1860,  1865,  1883,  1882,  1902,  1901,  1921,  1920,
    1940,  1939,  1959,  1958,  1978,  1977,  1997,  1996,  2016,  2015,
    2035,  2036,  2037,  2048,  2050,  2049,  2070,  2071,  2072,  2073,
    2074,  2075,  2076,  2077,  2152,  2153,  2154,  2155,  2156,  2157,
    2158,  2159,  2160,  2161,  2162,  2163,  2169,  2170,  2236,  2237,
    2238,  2239,  2240,  2241,  2242,  2243,  2244,  2245,  2246,  2317,
    2334,  2374,  2391,  2395,  2403,  2421,  2425,  2433,  2451,  2467,
    2498,  2516,  2536,  2556,  2561,  2572,  2578,  2597,  2613,  2635,
    2634,  2658,  2657,  2678,  2679,  2683,  2687,  2691,  2695,  2711,
    2710,  2731,  2732,  2744,  2759,  2758,  2779,  2780,  2797,  2812,
    2811,  2832,  2833,  2848,  2864,  2863,  2884,  2885,  2909,  2913,
    2927,  2931,  2945,  2966,  2987,  3012,  3033,  3038,  3050,  3062,
    3067,  3078,  3082,  3096,  3100,  3104,  3117,  3121,  3137,  3141,
    3155,  3156,  3171,  3177,  3183,  3200,  3208,  3214
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EGG_NUMBER", "EGG_ULONG", "EGG_STRING",
  "ANIMPRELOAD", "BEZIERCURVE", "BFACE", "BILLBOARD", "BILLBOARDCENTER",
  "BINORMAL", "BUNDLE", "CLOSED", "COLLIDE", "COMMENT", "COMPONENT",
  "COORDSYSTEM", "CV", "DART", "DNORMAL", "DRGBA", "DUV", "DXYZ", "DCS",
  "DISTANCE", "DTREF", "DYNAMICVERTEXPOOL", "EXTERNAL_FILE", "GROUP",
  "DEFAULTPOSE", "JOINT", "KNOTS", "INCLUDE", "INSTANCE", "LINE", "LOOP",
  "MATERIAL", "MATRIX3", "MATRIX4", "MODEL", "MREF", "NORMAL",
  "NURBSCURVE", "NURBSSURFACE", "OBJECTTYPE", "ORDER", "OUTTANGENT",
  "PATCH", "POINTLIGHT", "POLYGON", "REF", "RGBA", "ROTATE", "ROTX",
  "ROTY", "ROTZ", "SANIM", "SCALAR", "SCALE", "SEQUENCE", "SHADING",
  "SWITCH", "SWITCHCONDITION", "TABLE", "TABLE_V", "TAG", "TANGENT",
  "TEXLIST", "TEXTURE", "TLENGTHS", "TRANSFORM", "TRANSLATE", "TREF",
  "TRIANGLEFAN", "TRIANGLESTRIP", "TRIM", "TXT", "UKNOTS", "UV", "AUX",
  "VKNOTS", "VERTEX", "VERTEXANIM", "VERTEXPOOL", "VERTEXREF", "XFMANIM",
  "XFMSANIM", "START_EGG", "START_GROUP_BODY", "START_TEXTURE_BODY",
  "START_PRIMITIVE_BODY", "'{'", "'}'", "$accept", "grammar", "egg",
  "node", "coordsystem", "comment", "texture", "$@1", "texture_body",
  "material", "$@2", "material_body", "external_reference", "vertex_pool",
  "$@3", "vertex_pool_body", "vertex", "$@4", "$@5", "vertex_body", "$@6",
  "$@7", "vertex_uv_body", "vertex_aux_body", "vertex_normal_body",
  "vertex_color_body", "group", "$@8", "joint", "$@9", "instance", "$@10",
  "group_body", "cs_type", "collide_flags", "transform", "$@11",
  "default_pose", "$@12", "transform_body", "translate2d", "translate3d",
  "rotate2d", "rotx", "roty", "rotz", "rotate3d", "scale2d", "scale3d",
  "uniform_scale", "matrix3", "matrix3_body", "matrix4", "matrix4_body",
  "group_vertex_ref", "group_vertex_membership", "switchcondition",
  "switchcondition_body", "polygon", "$@13", "trianglefan", "$@14",
  "trianglestrip", "$@15", "patch", "$@16", "point_light", "$@17", "line",
  "$@18", "nurbs_surface", "$@19", "nurbs_curve", "$@20",
  "primitive_component_body", "primitive_body", "$@21",
  "nurbs_surface_body", "nurbs_curve_body", "primitive_tref_body",
  "primitive_texture_body", "primitive_material_body",
  "primitive_normal_body", "primitive_color_body", "primitive_bface_body",
  "primitive_vertex_ref", "nurbs_surface_order_body",
  "nurbs_surface_uknots_body", "nurbs_surface_vknots_body",
  "nurbs_surface_trim_body", "nurbs_surface_trim_loop_body",
  "nurbs_curve_order_body", "nurbs_curve_knots_body", "table", "$@22",
  "bundle", "$@23", "table_body", "sanim", "$@24", "sanim_body", "xfmanim",
  "$@25", "xfmanim_body", "xfm_s_anim", "$@26", "xfm_s_anim_body",
  "anim_preload", "$@27", "anim_preload_body", "integer_list", "real_list",
  "texture_name", "material_name", "vertex_pool_name", "group_name",
  "required_name", "optional_name", "required_string", "optional_string",
  "string", "repeated_string", "repeated_string_body", "real",
  "real_or_string", "integer", "empty", YY_NULL
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
     345,   346,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    95,    95,    96,    96,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    98,    99,   101,
     100,   102,   102,   102,   104,   103,   105,   105,   106,   106,
     108,   107,   109,   109,   111,   110,   112,   110,   113,   113,
     113,   113,   114,   113,   115,   113,   113,   113,   113,   113,
     116,   116,   116,   116,   116,   116,   116,   116,   117,   117,
     118,   118,   118,   119,   119,   119,   121,   120,   123,   122,
     125,   124,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   127,   128,   128,   130,   129,   132,   131,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   145,   146,   147,   147,   148,   149,
     149,   150,   151,   151,   153,   152,   155,   154,   157,   156,
     159,   158,   161,   160,   163,   162,   165,   164,   167,   166,
     168,   168,   168,   169,   170,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   173,
     174,   175,   176,   176,   176,   177,   177,   177,   178,   179,
     180,   181,   182,   183,   183,   184,   184,   185,   186,   188,
     187,   190,   189,   191,   191,   191,   191,   191,   191,   193,
     192,   194,   194,   194,   196,   195,   197,   197,   197,   199,
     198,   200,   200,   200,   202,   201,   203,   203,   204,   204,
     205,   205,   206,   207,   208,   209,   210,   210,   211,   212,
     212,   213,   213,   214,   214,   214,   215,   215,   216,   216,
     217,   217,   218,   218,   218,   219,   219,   220
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     5,     0,
       7,     1,     6,     2,     0,     6,     1,     6,     5,     6,
       0,     6,     1,     2,     0,     5,     0,     6,     1,     2,
       3,     4,     0,     7,     0,     7,     5,     5,     8,     8,
       2,     3,     7,     7,     7,     8,     7,     8,     0,     4,
       3,     8,     8,     4,     9,     9,     0,     6,     0,     6,
       0,     6,     1,     6,     5,     7,     7,     5,     5,     5,
       5,     5,     5,     5,     6,     5,     2,     2,     2,     2,
       5,     2,     1,     1,     2,     0,     5,     0,     5,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     5,     6,     4,     4,     4,     4,     7,     5,
       6,     4,     4,     1,     9,     4,     1,    16,     9,     1,
       6,     4,    11,    12,     0,     6,     0,     6,     0,     6,
       0,     6,     0,     6,     0,     6,     0,     6,     0,     6,
       1,     5,     5,     1,     0,     7,     5,     5,     5,     2,
       5,     5,     5,     6,     1,     5,     5,     5,     2,     5,
       5,     5,     5,     5,     5,     2,     5,     6,     1,     5,
       5,     5,     2,     5,     5,     5,     5,     5,     6,     1,
       1,     1,     3,     8,     8,     4,     9,     9,     1,     8,
       2,     1,     1,     1,     5,     1,     2,     1,     1,     0,
       6,     0,     6,     1,     2,     2,     2,     2,     2,     0,
       6,     1,     6,     5,     0,     6,     1,     6,     5,     0,
       6,     1,     6,     2,     0,     6,     1,     6,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   277,   277,   277,   277,     0,     2,     6,     3,    82,
       4,    31,     5,   163,     1,   263,   264,   265,   277,   277,
       0,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,   277,   277,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     0,     0,     0,
     277,     0,     0,   107,     0,     0,     0,   277,     0,     0,
     277,     0,   105,     0,   101,    96,    97,    98,    99,   277,
      33,     0,     0,     0,     0,     0,   277,     0,     0,     0,
     169,   244,   258,   262,   261,     0,   277,     0,    76,    78,
      80,   154,     0,   257,   256,   158,   156,   150,   152,   144,
     219,     0,   146,   148,    40,   277,     0,     0,     0,     0,
       0,     0,     0,   277,   277,     0,     0,     0,     0,     0,
       0,   277,     0,     0,   275,   276,     0,   277,     0,     0,
       0,   277,   277,   277,     0,   277,     0,   260,   259,   277,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,   277,     0,     0,     0,     0,     0,   270,   271,     0,
       0,     0,     0,     0,     0,   277,     0,     0,     0,   255,
       0,     0,     0,     0,   277,     0,   277,   277,   248,     0,
       0,   208,   164,     0,   201,   253,     0,     0,     0,     0,
       0,     0,   200,     0,   199,   252,     0,   277,   268,     0,
     267,   266,    27,     0,   277,   277,   277,   277,   277,   277,
     277,   277,   277,   277,   277,    29,   277,   277,   277,   277,
      84,     0,   277,   102,    90,    89,    88,    87,     0,   109,
      93,    92,   100,   272,   273,   274,     0,    91,     0,   141,
       0,    95,     0,     0,   249,   139,     0,   172,   277,   168,
       0,   170,     0,     0,   171,     0,     0,   167,   166,     0,
       0,   246,    28,   269,    38,     0,     0,     0,     0,     0,
      36,     0,   188,     0,   174,     0,     0,     0,     0,   223,
     277,     0,     0,     0,    42,     0,     0,     0,   103,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      83,     0,    94,   106,     0,   277,    32,     0,   160,     0,
       0,   202,     0,     0,     0,   173,   277,   277,   245,    77,
      79,    81,   155,   277,    35,     0,     0,     0,     0,     0,
       0,   277,     0,     0,   159,   192,     0,     0,     0,     0,
       0,   277,     0,     0,     0,     0,     0,   157,   185,   178,
     151,   153,   145,   277,   277,   277,   277,   220,   224,   225,
     226,   227,   228,     0,   147,   149,    44,    41,    43,    39,
      85,    86,   104,   277,   277,     0,     0,     0,     0,     0,
       0,     0,   277,     0,     0,     0,   165,     0,     0,     0,
       0,   205,     0,   254,     0,     0,     0,   277,   277,     0,
       0,     0,     0,   277,   277,     0,   277,     0,     0,     0,
       0,   277,   277,   277,   277,   277,   221,   229,   234,   239,
      30,     0,    46,     0,     0,   133,     0,     0,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     218,   250,     0,     0,     0,   217,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     213,     0,   211,     0,   212,     0,     0,     0,     0,     0,
       0,   132,     0,   135,     0,   124,     0,   125,   126,   127,
     131,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   209,     0,     0,   195,   197,   251,   191,
     193,   196,   194,     0,   190,   189,   181,   177,   179,   182,
     210,   180,     0,   176,   175,     0,   186,   183,   184,   277,
     277,   277,   277,     0,    48,     0,     0,     0,     0,   129,
       0,   122,     0,     0,     0,   138,   140,   161,   162,     0,
       0,     0,     0,   247,    37,   198,   187,   277,     0,     0,
     231,     0,   236,     0,   241,     0,     0,     0,   277,   277,
      45,    49,     0,     0,     0,     0,   130,   123,     0,     0,
     204,   203,     0,     0,     0,   215,   222,   277,     0,   230,
     277,     0,   235,   277,   240,   243,     0,     0,     0,     0,
       0,     0,    50,    47,     0,     0,   128,     0,     0,   207,
     206,   214,   216,     0,   277,     0,   277,     0,     0,     0,
       0,     0,     0,     0,    52,    54,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    56,
       0,     0,    57,     0,     0,    68,     0,     0,   142,     0,
       0,   233,     0,   238,     0,     0,     0,     0,     0,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   143,
     232,   237,   242,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     0,    53,    60,    55,     0,   134,     0,    59,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    72,    71,     0,     0,     0,     0,     0,     0,     0,
      75,    74,    63,    66,     0,    64,     0,    62,     0,    67,
      65,     0,   137
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,    74,    38,    39,    40,   290,    10,    41,
     218,   279,    42,    43,   164,   293,   388,   441,   500,   553,
     664,   665,   683,   685,   640,   642,    44,   150,    45,   151,
      46,   152,     8,   232,   297,    75,   130,    76,   121,   238,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   443,   319,   446,    77,   253,    78,   183,    47,   159,
      48,   162,    49,   163,    50,   157,    51,   158,    52,   153,
      53,   156,    54,   155,   327,    12,   258,   283,   281,   203,
     201,   193,   196,   198,   190,    90,   483,   491,   493,   489,
     604,   474,   469,    55,   160,   379,   495,   288,   380,   496,
     579,   381,   497,   581,   382,   498,   583,    56,   144,   270,
     187,   470,   204,   194,   412,   178,   195,    91,   146,    92,
     103,   209,   210,   528,   246,   191,   104
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -430
static const yytype_int16 yypact[] =
{
     245,  -430,  -430,  -430,  -430,    14,   794,  -430,  1451,  -430,
     168,  -430,   535,  -430,  -430,  -430,  -430,  -430,   271,   271,
     -61,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,     9,   -17,   -12,
     271,     6,    10,  -430,    12,    42,    46,   271,    74,   106,
     271,   125,  -430,   155,  -430,  -430,  -430,  -430,  -430,   271,
    -430,   187,   228,   188,   190,   198,   271,   203,   204,   208,
    -430,  -430,  -430,  -430,  -430,   209,   271,   219,  -430,  -430,
    -430,  -430,   223,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,   227,  -430,  -430,  -430,   271,   271,   255,   229,   342,
     345,   230,   228,   271,   271,   235,   228,   137,   236,   228,
     239,  -430,   246,   228,  -430,  -430,   259,   271,   255,   255,
     261,   271,   271,  -430,   267,   271,    57,  -430,  -430,   271,
     272,   273,   274,   279,  -430,   281,   283,   284,   287,   288,
     289,   271,   290,   297,   298,   300,   127,  -430,  -430,   255,
     271,   224,   270,   302,   314,  -430,   315,   322,   325,  -430,
     353,   330,   301,   332,   271,   333,  -430,   228,  -430,   353,
     335,  -430,  -430,   338,  -430,  -430,    32,   255,    92,   255,
     353,   346,  -430,   348,  -430,  -430,   128,  -430,  -430,   349,
     271,  -430,  -430,   352,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,   271,
    -430,   255,  -430,  -430,  -430,  -430,  -430,  -430,   381,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,   356,  -430,   255,  -430,
     361,  -430,   441,   164,  -430,  -430,   362,  -430,  -430,  -430,
      69,  -430,   255,    73,  -430,   255,   365,  -430,  -430,   354,
      53,  -430,  -430,  -430,  -430,   975,  1184,  1378,   225,    70,
    -430,   145,  -430,   167,  -430,   247,   336,   375,    95,  -430,
    -430,   435,   495,   134,  -430,   366,   368,    44,  -430,   377,
     380,   386,   389,   390,   391,   392,   393,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,   255,  -430,  -430,   394,   271,  -430,    37,  -430,   271,
     396,  -430,   271,   397,   255,  -430,   271,   271,  -430,  -430,
    -430,  -430,  -430,   271,  -430,   398,   399,   400,   406,   407,
     409,   271,   414,   418,  -430,  -430,   420,   425,   426,   427,
     429,   271,   434,   437,   438,   439,   440,  -430,  -430,  -430,
    -430,  -430,  -430,   271,   271,   271,   271,  -430,  -430,  -430,
    -430,  -430,  -430,   153,  -430,  -430,   228,  -430,  -430,  -430,
    -430,  -430,  -430,   255,   255,   255,   255,   255,   255,   255,
     255,    66,   271,   443,   446,   447,  -430,   255,   255,   255,
     255,  -430,   448,  -430,   450,   452,   228,  -430,   271,   255,
     228,   255,   453,   271,   271,   228,   271,   255,   228,   255,
     454,   271,   271,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,   456,  -430,   457,   255,  -430,   459,   255,  -430,     4,
     461,   462,   463,     7,   255,   470,   257,   472,   353,   255,
     255,   255,   255,   255,   255,   476,   353,   353,   477,   478,
     255,  -430,   479,    43,   480,  -430,    97,   353,   485,   488,
     490,   491,    83,   492,   228,   102,   353,   493,   496,     8,
    -430,   497,   255,   498,   255,   471,   500,   503,   506,   255,
     508,  -430,   255,  -430,   255,  -430,   255,  -430,  -430,  -430,
    -430,    47,    52,   255,   511,   512,   513,    96,   103,   255,
     255,   255,   255,  -430,   514,   516,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,   518,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,   519,  -430,  -430,   521,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,   250,   255,   255,   255,   255,   255,  -430,
     522,  -430,   523,   255,   255,  -430,  -430,  -430,  -430,   524,
     525,   255,   255,  -430,  -430,  -430,  -430,  -430,   142,   179,
    -430,   191,  -430,   100,  -430,    79,   527,   531,   271,   271,
    -430,   255,   262,   255,   255,   533,  -430,  -430,   255,   255,
    -430,  -430,   536,   537,    76,  -430,  -430,   271,   532,  -430,
     271,   540,  -430,   271,  -430,  -430,   271,   541,   255,   255,
     542,   543,   255,  -430,   255,   255,  -430,   544,   255,  -430,
    -430,  -430,  -430,   546,  -430,   547,  -430,   548,   255,   255,
     101,   255,   108,   255,  -430,  -430,  -430,   255,   255,   550,
     552,   353,    54,   353,    56,   353,   255,   255,    82,  -430,
     255,    88,  -430,   255,   255,   255,   255,   255,  -430,   554,
     555,  -430,   556,  -430,   560,   255,   255,   271,   562,  -430,
     271,   564,   255,    77,   255,   565,   255,   255,   255,  -430,
    -430,  -430,  -430,   568,   569,   255,   255,   255,   255,  -430,
     572,    91,   573,  -430,   255,  -430,   255,  -430,   255,  -430,
    -430,   255,   255,   255,   255,   255,   271,   580,   255,  -430,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
    -430,   255,   582,   583,   255,   255,   255,   255,   255,   255,
     255,  -430,  -430,   584,   587,   588,    58,    63,   589,   255,
    -430,  -430,  -430,  -430,   590,  -430,   591,  -430,   255,  -430,
    -430,   255,  -430
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -430,  -430,  -430,   178,  -430,  -430,  -430,  -430,    64,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -117,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,   146,  -430,  -430,    -9,  -430,  -430,  -430,   341,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
    -430,  -430,  -279,  -430,  -430,    86,  -430,  -430,  -430,  -310,
    -263,  -165,  -292,  -179,  -204,   -19,  -430,  -430,  -430,  -430,
    -430,  -430,  -430,  -285,  -430,  -430,  -430,   -16,   -43,  -430,
    -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,  -430,
     530,  -429,  -430,  -430,   147,  -430,   760,    11,   -96,  -430,
      -6,   430,  -430,     3,  -180,   -14,   744
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      57,    80,    57,   378,   368,   492,   494,   167,   168,   256,
     167,   168,    93,    93,    14,    93,    93,    93,    93,    93,
     266,    93,    93,    93,    93,    93,    93,   177,    93,    93,
      95,    96,    97,    98,    99,   100,   101,   115,   105,   106,
     107,   108,   109,   110,   545,   112,   113,    15,    16,    17,
     167,   168,   260,   213,    93,   167,   168,   167,   168,   167,
     168,   167,   168,   260,    93,   225,   167,   168,   136,   167,
     168,   118,    15,    16,    17,   116,    15,    16,    17,   404,
     117,   128,    15,    16,    17,    15,    16,    17,   700,   405,
     147,    15,    16,    17,    15,    16,    17,   505,   119,   701,
     510,   546,   120,   260,   122,   172,   174,   373,   176,    93,
     166,   337,   181,   263,   479,   185,   260,   147,   263,    27,
     169,   658,   488,   263,   263,   261,   165,   473,   343,   661,
     406,   134,   135,   295,   123,   482,   530,   391,   124,   208,
     559,   197,   199,   147,   702,   561,   338,   671,   455,   673,
     212,   753,   374,   345,   373,   147,   755,   374,   613,    32,
     478,   329,   182,   344,   233,   332,   126,   517,   487,   631,
     703,   616,   231,   254,   677,   356,   538,   346,   208,   269,
     680,   375,   376,   716,    37,   264,   347,   348,   377,   567,
     532,   349,   254,   614,   659,   541,   568,   350,   127,   374,
     262,   662,   265,   351,   273,   652,    32,   654,   357,   358,
      27,    79,   468,   359,   352,   324,   386,   129,   353,   360,
     230,   480,   325,   147,    72,   361,    79,   387,   375,   376,
      89,   134,   135,    81,   296,   606,   362,   607,   354,    72,
     363,    82,   476,   364,   608,   365,   440,   131,   366,   610,
     485,   321,    89,   472,   330,    81,   611,   333,   167,   168,
     367,   481,   355,    82,   369,   331,    83,    84,   334,    57,
      57,    57,   609,   585,    15,    16,    17,    85,   516,   133,
     137,   518,   138,    86,   612,   585,   524,   525,    83,    84,
     139,   392,   586,   378,    87,   141,   142,   533,    88,    85,
     143,   145,   587,   278,   586,    86,   542,   285,   286,   287,
      89,   149,   291,   292,   587,   154,    87,   234,   342,   161,
      88,   170,   175,   407,   401,   632,   409,   180,   184,   588,
     589,   186,    89,     1,     2,     3,     4,   411,   189,   514,
     370,   588,   589,   590,    81,   134,   135,   171,   134,   135,
     173,   192,    82,   200,   383,   623,   243,   244,   245,   207,
     275,   276,   277,   235,   214,   215,   216,    93,    93,    93,
      93,   217,   442,   219,    80,   220,   221,    83,    84,   222,
     223,   224,   226,    81,   436,   437,   438,   439,    85,   227,
     228,    82,   229,   248,    86,   236,   444,   447,   449,   450,
     451,   452,   453,   454,   456,    87,   475,   237,   240,    88,
     461,   462,   463,   464,   484,   241,    83,    84,   242,   299,
     300,    89,   197,   247,   199,   249,   251,    85,   257,   371,
     197,   259,   199,    86,   301,   302,   303,   304,   592,   267,
     305,   268,   272,    81,    87,   274,   336,   502,    88,   320,
     504,    82,   506,   306,   322,   326,   511,   512,   335,   389,
      89,   390,   197,   199,   519,   520,   521,   522,   372,   393,
     540,   670,   394,   672,   307,   674,    83,    84,   395,   299,
     300,   396,   397,   398,   399,   400,   402,    85,   408,   410,
     416,   417,   418,    86,   301,   302,   303,   304,   419,   420,
     305,   421,   554,    81,    87,   556,   423,   557,    88,   558,
     424,    82,   425,   306,   560,   562,   563,   426,   427,   428,
      89,   429,   569,   570,   571,   572,   431,   252,   384,   432,
     433,   434,   435,   578,   323,   458,    83,    84,   459,   460,
     615,   465,   466,    81,   467,   477,   486,    85,   499,   457,
     501,    82,   503,    86,   507,   508,   509,   591,   554,   593,
     594,   595,   513,   549,    87,   515,   598,   599,    88,   523,
     526,   527,   529,   531,   602,   603,    83,    84,   534,   617,
      89,   535,    93,   536,   537,   539,   543,    85,   385,   544,
     547,   548,   550,    86,   622,   551,   624,   625,   552,   620,
     555,   627,   628,   564,    87,   565,   566,   573,    88,   574,
     638,   575,   576,   577,   250,   596,   597,   600,   601,   618,
      89,   641,   643,   619,   634,   646,   626,   647,   648,   629,
     630,   650,   636,   639,   644,   645,     0,   649,   651,   653,
     655,   656,   657,   668,   660,   669,   663,   689,   690,   691,
     666,   667,   678,   692,   696,   681,   698,     0,   705,   675,
     676,   709,   710,   679,   715,   718,   682,   684,   686,   687,
     688,   695,   728,   206,   697,   741,   742,   750,   693,   694,
     751,   752,   757,   759,   760,   699,     0,   704,     0,   706,
     707,   708,     0,     0,     0,   717,     0,     0,   711,   712,
     713,   714,     0,     0,     0,     0,     0,   719,     0,   720,
     727,   721,     0,     0,   722,   723,   724,   725,   726,     0,
       0,   729,     0,   730,   731,   732,   733,   734,   735,   736,
     737,   738,   739,     0,   740,     0,     0,   743,   744,   745,
     746,   747,   748,   749,     0,     7,     9,    11,    13,   754,
     756,     0,   758,     0,     0,     0,     0,     0,     0,     0,
       0,   761,    94,    94,   762,    94,    94,    94,    94,    94,
       0,    94,    94,    94,    94,    94,    94,     0,    94,    94,
       0,     0,     0,     0,     0,     0,   102,     0,     0,     0,
       0,     0,     0,   111,     0,     0,   114,    15,    16,    17,
      18,     0,     0,     0,    94,     0,     0,     0,     0,    19,
       0,    20,     0,     0,    94,     0,     0,     0,     0,     0,
       0,     0,    21,    22,     0,    23,     0,   125,    24,    25,
       0,    26,     0,     0,     0,     0,     0,    27,    28,   132,
     148,     0,    29,    30,    31,     0,   140,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,    94,
       0,     0,     0,    33,     0,     0,     0,   148,    34,    35,
       0,     0,     0,     0,     0,   188,     0,     0,    36,     0,
       0,     0,     0,     0,   179,     0,     0,   188,     0,   211,
       0,     0,     0,   148,     0,     0,     0,     0,     0,     0,
       0,   202,   205,     0,     0,   148,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   239,
       0,     0,     0,     0,     0,     0,     0,     0,   211,     0,
     239,   255,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,     0,     0,     0,     0,     0,     0,     9,     9,
       9,    13,   280,   282,   284,    13,    13,    13,   289,     0,
      13,    13,   294,   148,     0,     0,   298,     0,    15,    16,
      17,    18,     0,     0,    58,    59,     0,     0,     0,    60,
      19,     0,    20,     0,    61,     0,     0,     0,     0,    62,
       0,     0,   328,    21,    22,    63,    23,     0,     0,    24,
      25,     0,    26,     0,     0,    64,     0,     0,    27,    28,
      65,     0,     0,    29,    30,    31,    66,     0,     0,     0,
       0,     0,     0,    67,    11,     0,     0,    68,    69,    32,
       0,    70,     0,    71,    33,     0,    72,     0,     0,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      73,     0,     0,     0,     0,     0,     0,     0,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   403,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   413,   414,     0,     0,
       0,     0,     0,   415,     0,     0,     0,     0,     0,     0,
       0,   422,     0,     0,     0,     0,     0,    94,    94,    94,
      94,   430,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   445,   448,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   471,   413,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   490,   471,   471,
       0,     0,     0,   202,   205,     0,     0,    15,    16,    17,
      18,   202,   205,    58,    59,     0,     0,     0,    60,    19,
       0,    20,     0,    61,     0,     0,     0,     0,    62,     0,
       0,     0,    21,    22,    63,    23,     0,     0,    24,    25,
       0,    26,     0,     0,    64,     0,     0,    27,    28,    65,
       0,     0,    29,    30,    31,    66,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,    68,    69,    32,     0,
      70,     0,    71,    33,     0,    72,     0,     0,    34,    35,
       0,     0,     0,     0,     0,     0,     0,     0,    36,    73,
       0,     0,     0,     0,     0,     0,     0,   340,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   289,   580,   582,   584,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   605,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   621,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   633,     0,     0,
     635,     0,     0,   637,     0,     0,     0,     0,   471,     0,
     471,    15,    16,    17,    18,     0,     0,    58,    59,     0,
       0,     0,    60,    19,     0,    20,     0,    61,     0,     0,
       0,     0,    62,     0,     0,     0,    21,    22,    63,    23,
       0,     0,    24,    25,     0,    26,     0,     0,    64,     0,
       0,    27,    28,    65,     0,     0,    29,    30,    31,    66,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
      68,    69,    32,     0,    70,     0,    71,    33,     0,    72,
       0,     0,    34,    35,    15,    16,    17,    18,     0,     0,
      58,    59,    36,    73,     0,    60,    19,     0,    20,     0,
      61,   341,     0,     0,     0,    62,     0,     0,     0,    21,
      22,    63,    23,     0,     0,    24,    25,     0,    26,     0,
       0,    64,     0,     0,    27,    28,    65,     0,     0,    29,
      30,    31,    66,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,    68,    69,    32,     0,    70,     0,    71,
      33,     0,    72,     0,     0,    34,    35,     0,     0,     0,
       0,     0,     0,     0,     0,    36,    73
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-430)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       6,    10,     8,   288,   283,   434,   435,     3,     4,   189,
       3,     4,    18,    19,     0,    21,    22,    23,    24,    25,
     200,    27,    28,    29,    30,    31,    32,   123,    34,    35,
      19,    92,    21,    22,    23,    24,    25,    28,    27,    28,
      29,    30,    31,    32,    36,    34,    35,     3,     4,     5,
       3,     4,    20,   149,    60,     3,     4,     3,     4,     3,
       4,     3,     4,    20,    70,   161,     3,     4,    82,     3,
       4,    60,     3,     4,     5,    92,     3,     4,     5,    42,
      92,    70,     3,     4,     5,     3,     4,     5,    11,    52,
      96,     3,     4,     5,     3,     4,     5,    93,    92,    22,
      93,    93,    92,    20,    92,   119,   120,    12,   122,   115,
     116,    58,   126,    21,   424,   129,    20,   123,    21,    43,
     117,    20,   432,    21,    21,    93,   115,   419,    58,    21,
      93,     3,     4,   229,    92,   427,    93,    93,    92,   145,
      93,   138,   139,   149,    67,    93,    93,    93,    82,    93,
      93,    93,    57,     8,    12,   161,    93,    57,    58,    64,
     423,    92,    25,    93,   170,    92,    92,   459,   431,    93,
      93,    92,   169,   187,    92,     8,    93,    32,   184,    51,
      92,    86,    87,    92,     6,    93,    41,    42,    93,    93,
      93,    46,   206,    93,    93,    93,    93,    52,    92,    57,
     197,    93,   199,    58,   210,   634,    64,   636,    41,    42,
      43,    58,   416,    46,    69,    51,    82,    92,    73,    52,
      93,   425,    58,   229,    71,    58,    58,    93,    86,    87,
      85,     3,     4,     8,   231,    93,    69,    58,    93,    71,
      73,    16,   421,    76,    65,    78,    93,    92,    81,    58,
     429,   248,    85,   418,   260,     8,    65,   263,     3,     4,
      93,   426,   281,    16,   283,   262,    41,    42,   265,   275,
     276,   277,    93,    23,     3,     4,     5,    52,   458,    92,
      92,   460,    92,    58,    93,    23,   466,   467,    41,    42,
      92,   297,    42,   578,    69,    92,    92,   477,    73,    52,
      92,    92,    52,   217,    42,    58,   486,   221,   222,   223,
      85,    92,   226,   227,    52,    92,    69,    93,    93,    92,
      73,    92,    92,   329,   321,   604,   332,    92,    92,    79,
      80,    92,    85,    88,    89,    90,    91,   334,    92,    82,
      93,    79,    80,    93,     8,     3,     4,     5,     3,     4,
       5,    92,    16,    92,   290,    93,     3,     4,     5,    92,
     214,   215,   216,    93,    92,    92,    92,   373,   374,   375,
     376,    92,   386,    92,   383,    92,    92,    41,    42,    92,
      92,    92,    92,     8,   373,   374,   375,   376,    52,    92,
      92,    16,    92,    92,    58,    93,   393,   394,   395,   396,
     397,   398,   399,   400,   401,    69,   420,    93,    93,    73,
     407,   408,   409,   410,   428,    93,    41,    42,    93,    38,
      39,    85,   419,    93,   421,    93,    93,    52,    93,    93,
     427,    93,   429,    58,    53,    54,    55,    56,   555,    93,
      59,    93,    93,     8,    69,    93,    92,   444,    73,    93,
     447,    16,   449,    72,    93,    93,   453,   454,    93,    93,
      85,    93,   459,   460,   461,   462,   463,   464,    93,    92,
     484,   651,    92,   653,    93,   655,    41,    42,    92,    38,
      39,    92,    92,    92,    92,    92,    92,    52,    92,    92,
      92,    92,    92,    58,    53,    54,    55,    56,    92,    92,
      59,    92,   499,     8,    69,   502,    92,   504,    73,   506,
      92,    16,    92,    72,   511,   512,   513,    92,    92,    92,
      85,    92,   519,   520,   521,   522,    92,   186,    93,    92,
      92,    92,    92,   549,    93,    92,    41,    42,    92,    92,
     583,    93,    92,     8,    92,    92,    92,    52,    92,   402,
      93,    16,    93,    58,    93,    93,    93,   554,   555,   556,
     557,   558,    92,    92,    69,    93,   563,   564,    73,    93,
      93,    93,    93,    93,   571,   572,    41,    42,    93,   585,
      85,    93,   588,    93,    93,    93,    93,    52,    93,    93,
      93,    93,    92,    58,   591,    92,   593,   594,    92,   588,
      92,   598,   599,    92,    69,    93,    93,    93,    73,    93,
     616,    93,    93,    92,   184,    93,    93,    93,    93,    92,
      85,   618,   619,    92,    92,   622,    93,   624,   625,    93,
      93,   628,    92,    92,    92,    92,    -1,    93,    92,    92,
      92,   638,   639,    93,   641,    93,   643,    93,    93,    93,
     647,   648,   658,    93,    92,   661,    92,    -1,    93,   656,
     657,    93,    93,   660,    92,    92,   663,   664,   665,   666,
     667,   677,    92,   143,   680,    93,    93,    93,   675,   676,
      93,    93,    93,    93,    93,   682,    -1,   684,    -1,   686,
     687,   688,    -1,    -1,    -1,   701,    -1,    -1,   695,   696,
     697,   698,    -1,    -1,    -1,    -1,    -1,   704,    -1,   706,
     716,   708,    -1,    -1,   711,   712,   713,   714,   715,    -1,
      -1,   718,    -1,   720,   721,   722,   723,   724,   725,   726,
     727,   728,   729,    -1,   731,    -1,    -1,   734,   735,   736,
     737,   738,   739,   740,    -1,     1,     2,     3,     4,   746,
     747,    -1,   749,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   758,    18,    19,   761,    21,    22,    23,    24,    25,
      -1,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    36,     3,     4,     5,
       6,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    15,
      -1,    17,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    29,    -1,    31,    -1,    67,    34,    35,
      -1,    37,    -1,    -1,    -1,    -1,    -1,    43,    44,    79,
      96,    -1,    48,    49,    50,    -1,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,   115,
      -1,    -1,    -1,    69,    -1,    -1,    -1,   123,    74,    75,
      -1,    -1,    -1,    -1,    -1,   131,    -1,    -1,    84,    -1,
      -1,    -1,    -1,    -1,   124,    -1,    -1,   143,    -1,   145,
      -1,    -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,   142,    -1,    -1,   161,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,
     186,   187,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   207,    -1,    -1,    -1,    -1,    -1,    -1,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,    -1,
     226,   227,   228,   229,    -1,    -1,   232,    -1,     3,     4,
       5,     6,    -1,    -1,     9,    10,    -1,    -1,    -1,    14,
      15,    -1,    17,    -1,    19,    -1,    -1,    -1,    -1,    24,
      -1,    -1,   258,    28,    29,    30,    31,    -1,    -1,    34,
      35,    -1,    37,    -1,    -1,    40,    -1,    -1,    43,    44,
      45,    -1,    -1,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    58,   290,    -1,    -1,    62,    63,    64,
      -1,    66,    -1,    68,    69,    -1,    71,    -1,    -1,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   325,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   336,   337,    -1,    -1,
      -1,    -1,    -1,   343,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   351,    -1,    -1,    -1,    -1,    -1,   373,   374,   375,
     376,   361,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   393,   394,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   417,   402,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,   434,   435,
      -1,    -1,    -1,   423,   424,    -1,    -1,     3,     4,     5,
       6,   431,   432,     9,    10,    -1,    -1,    -1,    14,    15,
      -1,    17,    -1,    19,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    28,    29,    30,    31,    -1,    -1,    34,    35,
      -1,    37,    -1,    -1,    40,    -1,    -1,    43,    44,    45,
      -1,    -1,    48,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    62,    63,    64,    -1,
      66,    -1,    68,    69,    -1,    71,    -1,    -1,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   549,   550,   551,   552,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   577,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   588,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   589,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   607,    -1,    -1,
     610,    -1,    -1,   613,    -1,    -1,    -1,    -1,   634,    -1,
     636,     3,     4,     5,     6,    -1,    -1,     9,    10,    -1,
      -1,    -1,    14,    15,    -1,    17,    -1,    19,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    28,    29,    30,    31,
      -1,    -1,    34,    35,    -1,    37,    -1,    -1,    40,    -1,
      -1,    43,    44,    45,    -1,    -1,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      62,    63,    64,    -1,    66,    -1,    68,    69,    -1,    71,
      -1,    -1,    74,    75,     3,     4,     5,     6,    -1,    -1,
       9,    10,    84,    85,    -1,    14,    15,    -1,    17,    -1,
      19,    93,    -1,    -1,    -1,    24,    -1,    -1,    -1,    28,
      29,    30,    31,    -1,    -1,    34,    35,    -1,    37,    -1,
      -1,    40,    -1,    -1,    43,    44,    45,    -1,    -1,    48,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    62,    63,    64,    -1,    66,    -1,    68,
      69,    -1,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    88,    89,    90,    91,    95,    96,   220,   126,   220,
     102,   220,   169,   220,     0,     3,     4,     5,     6,    15,
      17,    28,    29,    31,    34,    35,    37,    43,    44,    48,
      49,    50,    64,    69,    74,    75,    84,    97,    98,    99,
     100,   103,   106,   107,   120,   122,   124,   152,   154,   156,
     158,   160,   162,   164,   166,   187,   201,   214,     9,    10,
      14,    19,    24,    30,    40,    45,    51,    58,    62,    63,
      66,    68,    71,    85,    97,   129,   131,   148,   150,    58,
     129,     8,    16,    41,    42,    52,    58,    69,    73,    85,
     179,   211,   213,   214,   220,   211,    92,   211,   211,   211,
     211,   211,   210,   214,   220,   211,   211,   211,   211,   211,
     211,   210,   211,   211,   210,    28,    92,    92,   211,    92,
      92,   132,    92,    92,    92,   210,    92,    92,   211,    92,
     130,    92,   210,    92,     3,     4,   219,    92,    92,    92,
     210,    92,    92,    92,   202,    92,   212,   214,   220,    92,
     121,   123,   125,   163,    92,   167,   165,   159,   161,   153,
     188,    92,   155,   157,   108,   211,   214,     3,     4,   217,
      92,     5,   219,     5,   219,    92,   219,   212,   209,   210,
      92,   219,    25,   151,    92,   219,    92,   204,   220,    92,
     178,   219,    92,   175,   207,   210,   176,   217,   177,   217,
      92,   174,   210,   173,   206,   210,   204,    92,   214,   215,
     216,   220,    93,   212,    92,    92,    92,    92,   104,    92,
      92,    92,    92,    92,    92,   212,    92,    92,    92,    92,
      93,   217,   127,   214,    93,    93,    93,    93,   133,   220,
      93,    93,    93,     3,     4,     5,   218,    93,    92,    93,
     215,    93,   133,   149,   219,   220,   218,    93,   170,    93,
      20,    93,   217,    21,    93,   217,   218,    93,    93,    51,
     203,   220,    93,   214,    93,   126,   126,   126,   169,   105,
     220,   172,   220,   171,   220,   169,   169,   169,   191,   220,
     101,   169,   169,   109,   220,   212,   217,   128,   220,    38,
      39,    53,    54,    55,    56,    59,    72,    93,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   146,
      93,   217,    93,    93,    51,    58,    93,   168,   220,    92,
     214,   217,    92,   214,   217,    93,    92,    58,    93,    93,
      93,    93,    93,    58,    93,     8,    32,    41,    42,    46,
      52,    58,    69,    73,    93,   179,     8,    41,    42,    46,
      52,    58,    69,    73,    76,    78,    81,    93,   166,   179,
      93,    93,    93,    12,    57,    86,    87,    93,   187,   189,
     192,   195,   198,   102,    93,    93,    82,    93,   110,    93,
      93,    93,   214,    92,    92,    92,    92,    92,    92,    92,
      92,   217,    92,   210,    42,    52,    93,   214,    92,   214,
      92,   217,   208,   210,   210,   210,    92,    92,    92,    92,
      92,    92,   210,    92,    92,    92,    92,    92,    92,    92,
     210,    92,    92,    92,    92,    92,   211,   211,   211,   211,
      93,   111,   219,   145,   217,   220,   147,   217,   220,   217,
     217,   217,   217,   217,   217,    82,   217,   208,    92,    92,
      92,   217,   217,   217,   217,    93,    92,    92,   178,   186,
     205,   220,   175,   176,   185,   219,   177,    92,   174,   173,
     178,   175,   176,   180,   219,   177,    92,   174,   173,   183,
     220,   181,   205,   182,   205,   190,   193,   196,   199,    92,
     112,    93,   217,    93,   217,    93,   217,    93,    93,    93,
      93,   217,   217,    92,    82,    93,   218,   176,   177,   217,
     217,   217,   217,    93,   218,   218,    93,    93,   217,    93,
      93,    93,    93,   218,    93,    93,    93,    93,    93,    93,
     219,    93,   218,    93,    93,    36,    93,    93,    93,    92,
      92,    92,    92,   113,   217,    92,   217,   217,   217,    93,
     217,    93,   217,   217,    92,    93,    93,    93,    93,   217,
     217,   217,   217,    93,    93,    93,    93,    92,   191,   194,
     220,   197,   220,   200,   220,    23,    42,    52,    79,    80,
      93,   217,   113,   217,   217,   217,    93,    93,   217,   217,
      93,    93,   217,   217,   184,   220,    93,    58,    65,    93,
      58,    65,    93,    58,    93,   192,    92,   214,    92,    92,
     211,   210,   217,    93,   217,   217,    93,   217,   217,    93,
      93,    93,   166,   210,    92,   210,    92,   210,   214,    92,
     118,   217,   119,   217,    92,    92,   217,   217,   217,    93,
     217,    92,   205,    92,   205,    92,   217,   217,    20,    93,
     217,    21,    93,   217,   114,   115,   217,   217,    93,    93,
     218,    93,   218,    93,   218,   217,   217,    92,   214,   217,
      92,   214,   217,   116,   217,   117,   217,   217,   217,    93,
      93,    93,    93,   217,   217,   214,    92,   214,    92,   217,
      11,    22,    67,    93,   217,    93,   217,   217,   217,    93,
      93,   217,   217,   217,   217,    92,    92,   214,    92,   217,
     217,   217,   217,   217,   217,   217,   217,   214,    92,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,    93,    93,   217,   217,   217,   217,   217,   217,   217,
      93,    93,    93,    93,   217,    93,   217,    93,   217,    93,
      93,   217,   217
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
        case 7:
/* Line 1792 of yacc.c  */
#line 251 "panda/src/egg/parser.yxx"
    {
  assert(!egg_stack.empty());
  DCAST(EggData, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[(2) - (2)]._egg)));
}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 296 "panda/src/egg/parser.yxx"
    {
  string strval = (yyvsp[(3) - (4)]._string);
  EggCoordinateSystem *cs = new EggCoordinateSystem;

  CoordinateSystem f = parse_coordinate_system_string(strval);
  if (f == CS_invalid) {
    eggyywarning("Unknown coordinate system " + strval);
  } else {
    cs->set_value(f);
  }
  (yyval._egg) = cs;
}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 319 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = new EggComment((yyvsp[(2) - (5)]._string), (yyvsp[(4) - (5)]._string));
}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 333 "panda/src/egg/parser.yxx"
    {
  string tref_name = (yyvsp[(2) - (4)]._string);
  Filename filename = (yyvsp[(4) - (4)]._string);
  EggTexture *texture = new EggTexture(tref_name, filename);

  if (textures.find(tref_name) != textures.end()) {
    eggyywarning("Duplicate texture name " + tref_name);
  }
  textures[tref_name] = texture;

  egg_stack.push_back(texture);
}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 346 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 362 "panda/src/egg/parser.yxx"
    {
  EggTexture *texture = DCAST(EggTexture, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);
  string strval = (yyvsp[(5) - (6)]._string);

  if (cmp_nocase_uh(name, "type") == 0) {
    EggTexture::TextureType tt = EggTexture::string_texture_type(strval);
    if (tt == EggTexture::TT_unspecified) {
      eggyywarning("Unknown texture texture_type " + strval);
    } else {
      texture->set_texture_type(tt);
    }

  } else if (cmp_nocase_uh(name, "format") == 0) {
    EggTexture::Format f = EggTexture::string_format(strval);
    if (f == EggTexture::F_unspecified) {
      eggyywarning("Unknown texture format " + strval);
    } else {
      texture->set_format(f);
    }

  } else if (cmp_nocase_uh(name, "compression") == 0) {
    EggTexture::CompressionMode w = EggTexture::string_compression_mode(strval);
    if (w == EggTexture::CM_default) {
      eggyywarning("Unknown texture compression mode " + strval);
    } else {
      texture->set_compression_mode(w);
    }

  } else if (cmp_nocase_uh(name, "wrap") == 0) {
    EggTexture::WrapMode w = EggTexture::string_wrap_mode(strval);
    if (w == EggTexture::WM_unspecified) {
      eggyywarning("Unknown texture wrap mode " + strval);
    } else {
      texture->set_wrap_mode(w);
    }

  } else if (cmp_nocase_uh(name, "wrapu") == 0) {
    EggTexture::WrapMode w = EggTexture::string_wrap_mode(strval);
    if (w == EggTexture::WM_unspecified) {
      eggyywarning("Unknown texture wrap mode " + strval);
    } else {
      texture->set_wrap_u(w);
    }

  } else if (cmp_nocase_uh(name, "wrapv") == 0) {
    EggTexture::WrapMode w = EggTexture::string_wrap_mode(strval);
    if (w == EggTexture::WM_unspecified) {
      eggyywarning("Unknown texture wrap mode " + strval);
    } else {
      texture->set_wrap_v(w);
    }

  } else if (cmp_nocase_uh(name, "minfilter") == 0) {
    EggTexture::FilterType f = EggTexture::string_filter_type(strval);
    if (f == EggTexture::FT_unspecified) {
      eggyywarning("Unknown texture filter type " + strval);
    } else {
      texture->set_minfilter(f);
    }

  } else if (cmp_nocase_uh(name, "magfilter") == 0) {
    EggTexture::FilterType f = EggTexture::string_filter_type(strval);
    if (f == EggTexture::FT_unspecified) {
      eggyywarning("Unknown texture filter type " + strval);
    } else {
      texture->set_magfilter(f);
    }

  } else if (cmp_nocase_uh(name, "anisotropic_degree") == 0) {
    texture->set_anisotropic_degree((int)value);

  } else if (cmp_nocase_uh(name, "envtype") == 0) {
    EggTexture::EnvType e = EggTexture::string_env_type(strval);
    if (e == EggTexture::ET_unspecified) {
      eggyywarning("Unknown texture env type " + strval);
    } else {
      texture->set_env_type(e);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb") == 0) {
    EggTexture::CombineMode cm = EggTexture::string_combine_mode(strval);
    if (cm == EggTexture::CM_unspecified) {
      eggyywarning("Unknown combine mode " + strval);
    } else {
      texture->set_combine_mode(EggTexture::CC_rgb, cm);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-source0") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_rgb, 0, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-operand0") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_rgb, 0, co);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-source1") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_rgb, 1, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-operand1") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_rgb, 1, co);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-source2") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_rgb, 2, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-rgb-operand2") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_rgb, 2, co);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha") == 0) {
    EggTexture::CombineMode cm = EggTexture::string_combine_mode(strval);
    if (cm == EggTexture::CM_unspecified) {
      eggyywarning("Unknown combine mode " + strval);
    } else {
      texture->set_combine_mode(EggTexture::CC_alpha, cm);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-source0") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_alpha, 0, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-operand0") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_alpha, 0, co);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-source1") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_alpha, 1, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-operand1") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_alpha, 1, co);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-source2") == 0) {
    EggTexture::CombineSource cs = EggTexture::string_combine_source(strval);
    if (cs == EggTexture::CS_unspecified) {
      eggyywarning("Unknown combine source " + strval);
    } else {
      texture->set_combine_source(EggTexture::CC_alpha, 2, cs);
    }

  } else if (cmp_nocase_uh(name, "combine-alpha-operand2") == 0) {
    EggTexture::CombineOperand co = EggTexture::string_combine_operand(strval);
    if (co == EggTexture::CO_unspecified) {
      eggyywarning("Unknown combine operand " + strval);
    } else {
      texture->set_combine_operand(EggTexture::CC_alpha, 2, co);
    }

  } else if (cmp_nocase_uh(name, "saved_result") == 0) {
    texture->set_saved_result(((int)value) != 0);

  } else if (cmp_nocase_uh(name, "tex_gen") == 0) {
    EggTexture::TexGen tex_gen = EggTexture::string_tex_gen(strval);
    if (tex_gen == EggTexture::TG_unspecified) {
      eggyywarning("Unknown tex-gen " + strval);
    } else {
      texture->set_tex_gen(tex_gen);
    }

  } else if (cmp_nocase_uh(name, "quality_level") == 0) {
    EggTexture::QualityLevel quality_level = EggTexture::string_quality_level(strval);
    if (quality_level == EggTexture::QL_unspecified) {
      eggyywarning("Unknown quality-level " + strval);
    } else {
      texture->set_quality_level(quality_level);
    }

  } else if (cmp_nocase_uh(name, "stage_name") == 0) {
    texture->set_stage_name(strval);

  } else if (cmp_nocase_uh(name, "priority") == 0) {
    texture->set_priority((int)value);

  } else if (cmp_nocase_uh(name, "multiview") == 0) {
    texture->set_multiview(((int)value) != 0);

  } else if (cmp_nocase_uh(name, "num_views") == 0) {
    int int_value = (int)value;
    if (int_value < 1) {
      eggyyerror("Invalid num-views value " + strval);
    } else {
      texture->set_num_views(int_value);
    }

  } else if (cmp_nocase_uh(name, "blendr") == 0) {
    LColor color = texture->get_color();
    color[0] = value;
    texture->set_color(color);

  } else if (cmp_nocase_uh(name, "blendg") == 0) {
    LColor color = texture->get_color();
    color[1] = value;
    texture->set_color(color);

  } else if (cmp_nocase_uh(name, "blendb") == 0) {
    LColor color = texture->get_color();
    color[2] = value;
    texture->set_color(color);

  } else if (cmp_nocase_uh(name, "blenda") == 0) {
    LColor color = texture->get_color();
    color[3] = value;
    texture->set_color(color);

  } else if (cmp_nocase_uh(name, "borderr") == 0) {
    LColor border_color = texture->get_border_color();
    border_color[0] = value;
    texture->set_border_color(border_color);

  } else if (cmp_nocase_uh(name, "borderg") == 0) {
    LColor border_color = texture->get_border_color();
    border_color[1] = value;
    texture->set_border_color(border_color);

  } else if (cmp_nocase_uh(name, "borderb") == 0) {
    LColor border_color = texture->get_border_color();
    border_color[2] = value;
    texture->set_border_color(border_color);

  } else if (cmp_nocase_uh(name, "bordera") == 0) {
    LColor border_color = texture->get_border_color();
    border_color[3] = value;
    texture->set_border_color(border_color);

  } else if (cmp_nocase_uh(name, "uv_name") == 0) {
    texture->set_uv_name(strval);

  } else if (cmp_nocase_uh(name, "rgb_scale") == 0) {
    int int_value = (int)value;
    if (int_value != 1 && int_value != 2 && int_value != 4) {
      eggyyerror("Invalid rgb-scale value " + strval);
    } else {
      texture->set_rgb_scale(int_value);
    }

  } else if (cmp_nocase_uh(name, "alpha_scale") == 0) {
    int int_value = (int)value;
    if (int_value != 1 && int_value != 2 && int_value != 4) {
      eggyyerror("Invalid alpha-scale value " + strval);
    } else {
      texture->set_alpha_scale(int_value);
    }

  } else if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      texture->set_alpha_mode(a);
    }

  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      texture->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      texture->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      texture->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    texture->set_depth_offset((int)value);

  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    texture->set_draw_order((int)value);

  } else if (cmp_nocase_uh(name, "bin") == 0) {
    texture->set_bin(strval);

  } else if (cmp_nocase_uh(name, "alpha_file") == 0) {
    texture->set_alpha_filename(strval);

  } else if (cmp_nocase_uh(name, "alpha_file_channel") == 0) {
    texture->set_alpha_file_channel((int)value);

  } else if (cmp_nocase_uh(name, "read_mipmaps") == 0) {
    texture->set_read_mipmaps(((int)value) != 0);

  } else if (cmp_nocase_uh(name, "min_lod") == 0) {
    texture->set_min_lod(value);

  } else if (cmp_nocase_uh(name, "max_lod") == 0) {
    texture->set_max_lod(value);

  } else if (cmp_nocase_uh(name, "lod_bias") == 0) {
    texture->set_lod_bias(value);

  } else {
    eggyywarning("Unsupported texture scalar: " + name);
  }
}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 728 "panda/src/egg/parser.yxx"
    {
  string mref_name = (yyvsp[(2) - (3)]._string);
  EggMaterial *material = new EggMaterial(mref_name);

  if (materials.find(mref_name) != materials.end()) {
    eggyywarning("Duplicate material name " + mref_name);
  }
  materials[mref_name] = material;

  egg_stack.push_back(material);
}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 740 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 756 "panda/src/egg/parser.yxx"
    {
  EggMaterial *material = DCAST(EggMaterial, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);

  if (cmp_nocase_uh(name, "baser") == 0) {
    LColor base = material->get_base();
    base[0] = value;
    material->set_base(base);
  } else if (cmp_nocase_uh(name, "baseg") == 0) {
    LColor base = material->get_base();
    base[1] = value;
    material->set_base(base);
  } else if (cmp_nocase_uh(name, "baseb") == 0) {
    LColor base = material->get_base();
    base[2] = value;
    material->set_base(base);
  } else if (cmp_nocase_uh(name, "basea") == 0) {
    LColor base = material->get_base();
    base[3] = value;
    material->set_base(base);

  } else if (cmp_nocase_uh(name, "diffr") == 0) {
    LColor diff = material->get_diff();
    diff[0] = value;
    material->set_diff(diff);
  } else if (cmp_nocase_uh(name, "diffg") == 0) {
    LColor diff = material->get_diff();
    diff[1] = value;
    material->set_diff(diff);
  } else if (cmp_nocase_uh(name, "diffb") == 0) {
    LColor diff = material->get_diff();
    diff[2] = value;
    material->set_diff(diff);
  } else if (cmp_nocase_uh(name, "diffa") == 0) {
    LColor diff = material->get_diff();
    diff[3] = value;
    material->set_diff(diff);

  } else if (cmp_nocase_uh(name, "ambr") == 0) {
    LColor amb = material->get_amb();
    amb[0] = value;
    material->set_amb(amb);
  } else if (cmp_nocase_uh(name, "ambg") == 0) {
    LColor amb = material->get_amb();
    amb[1] = value;
    material->set_amb(amb);
  } else if (cmp_nocase_uh(name, "ambb") == 0) {
    LColor amb = material->get_amb();
    amb[2] = value;
    material->set_amb(amb);
  } else if (cmp_nocase_uh(name, "amba") == 0) {
    LColor amb = material->get_amb();
    amb[3] = value;
    material->set_amb(amb);

  } else if (cmp_nocase_uh(name, "emitr") == 0) {
    LColor emit = material->get_emit();
    emit[0] = value;
    material->set_emit(emit);
  } else if (cmp_nocase_uh(name, "emitg") == 0) {
    LColor emit = material->get_emit();
    emit[1] = value;
    material->set_emit(emit);
  } else if (cmp_nocase_uh(name, "emitb") == 0) {
    LColor emit = material->get_emit();
    emit[2] = value;
    material->set_emit(emit);
  } else if (cmp_nocase_uh(name, "emita") == 0) {
    LColor emit = material->get_emit();
    emit[3] = value;
    material->set_emit(emit);

  } else if (cmp_nocase_uh(name, "specr") == 0) {
    LColor spec = material->get_spec();
    spec[0] = value;
    material->set_spec(spec);
  } else if (cmp_nocase_uh(name, "specg") == 0) {
    LColor spec = material->get_spec();
    spec[1] = value;
    material->set_spec(spec);
  } else if (cmp_nocase_uh(name, "specb") == 0) {
    LColor spec = material->get_spec();
    spec[2] = value;
    material->set_spec(spec);
  } else if (cmp_nocase_uh(name, "speca") == 0) {
    LColor spec = material->get_spec();
    spec[3] = value;
    material->set_spec(spec);

  } else if (cmp_nocase_uh(name, "shininess") == 0) {
    material->set_shininess(value);

  } else if (cmp_nocase_uh(name, "roughness") == 0) {
    material->set_roughness(value);

  } else if (cmp_nocase_uh(name, "metallic") == 0) {
    material->set_metallic(value);

  } else if (cmp_nocase_uh(name, "ior") == 0) {
    material->set_ior(value);

  } else if (cmp_nocase_uh(name, "local") == 0) {
    material->set_local(value != 0.0);

  } else {
    eggyywarning("Unsupported material scalar: " + name);
  }
}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 877 "panda/src/egg/parser.yxx"
    {
  string node_name = (yyvsp[(2) - (5)]._string);
  Filename filename = (yyvsp[(4) - (5)]._string);
  EggExternalReference *ref = new EggExternalReference(node_name, filename);
  (yyval._egg) = ref;
}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 884 "panda/src/egg/parser.yxx"
    {
  if (cmp_nocase_uh((yyvsp[(1) - (6)]._string), "group") != 0) {
    eggyyerror("keyword 'group' expected");
  }
  string node_name = (yyvsp[(3) - (6)]._string);
  Filename filename = (yyvsp[(5) - (6)]._string);
  EggExternalReference *ref = new EggExternalReference(node_name, filename);
  (yyval._egg) = ref;
}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 904 "panda/src/egg/parser.yxx"
    {
  string name = (yyvsp[(2) - (2)]._string);
  EggVertexPool *pool = NULL;

  VertexPools::const_iterator vpi = vertex_pools.find(name);
  if (vpi != vertex_pools.end()) {
    pool = (*vpi).second;
    if (pool->has_defined_vertices()) {
      eggyywarning("Duplicate vertex pool name " + name);
      pool = new EggVertexPool(name);
      // The egg syntax starts counting at 1 by convention.
      pool->set_highest_index(0);
      vertex_pools[name] = pool;
    }
  } else {
    pool = new EggVertexPool(name);
    // The egg syntax starts counting at 1 by convention.
    pool->set_highest_index(0);
    vertex_pools[name] = pool;
  }

  egg_stack.push_back(pool);
}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 928 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 956 "panda/src/egg/parser.yxx"
    {
  egg_stack.push_back(new EggVertex);
}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 960 "panda/src/egg/parser.yxx"
    {
  PT(EggVertex) vtx = DCAST(EggVertex, egg_stack.back());
  egg_stack.pop_back();

  DCAST(EggVertexPool, egg_stack.back())->add_vertex(vtx);
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 967 "panda/src/egg/parser.yxx"
    {
  vertex_index = (int)(yyvsp[(2) - (2)]._number);
  EggVertexPool *pool = DCAST(EggVertexPool, egg_stack.back());

  if (vertex_index < 0) {
    ostringstream errmsg;
    errmsg << "Ignoring invalid vertex index " << vertex_index
           << " in vertex pool " << pool->get_name() << ends;
    eggyywarning(errmsg);
    vertex_index = -1;

  } else if (pool->has_vertex(vertex_index)) {
    ostringstream errmsg;
    errmsg << "Ignoring duplicate vertex index " << vertex_index
           << " in vertex pool " << pool->get_name() << ends;
    eggyywarning(errmsg);
    vertex_index = -1;
  }

  // Even if we didn't like the vertex index number, we still need to
  // go ahead and parse the vertex.  We just won't save it.

  egg_stack.push_back(new EggVertex);
}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 992 "panda/src/egg/parser.yxx"
    {
  PT(EggVertex) vtx = DCAST(EggVertex, egg_stack.back());
  egg_stack.pop_back();

  EggVertexPool *pool = DCAST(EggVertexPool, egg_stack.back());
  if (vertex_index != -1) {
    pool->add_vertex(vtx, vertex_index);
  }
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 1013 "panda/src/egg/parser.yxx"
    {
  DCAST(EggVertex, egg_stack.back())->set_pos((yyvsp[(1) - (1)]._number));
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 1017 "panda/src/egg/parser.yxx"
    {
  DCAST(EggVertex, egg_stack.back())->set_pos(LPoint2d((yyvsp[(1) - (2)]._number), (yyvsp[(2) - (2)]._number)));
}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 1021 "panda/src/egg/parser.yxx"
    {
  DCAST(EggVertex, egg_stack.back())->set_pos(LPoint3d((yyvsp[(1) - (3)]._number), (yyvsp[(2) - (3)]._number), (yyvsp[(3) - (3)]._number)));
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 1025 "panda/src/egg/parser.yxx"
    {
  DCAST(EggVertex, egg_stack.back())->set_pos(LPoint4d((yyvsp[(1) - (4)]._number), (yyvsp[(2) - (4)]._number), (yyvsp[(3) - (4)]._number), (yyvsp[(4) - (4)]._number)));
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 1029 "panda/src/egg/parser.yxx"
    {
  EggVertex *vertex = DCAST(EggVertex, egg_stack.back());
  EggVertexUV *uv = new EggVertexUV((yyvsp[(3) - (4)]._string), LTexCoordd::zero());
  egg_stack.push_back(uv);
  if (vertex->has_uv((yyvsp[(3) - (4)]._string))) {
    eggyywarning("Ignoring repeated UV name " + (yyvsp[(3) - (4)]._string));
  } else {
    vertex->set_uv_obj(uv);
  }
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 1040 "panda/src/egg/parser.yxx"
    {
  egg_stack.pop_back();
}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 1044 "panda/src/egg/parser.yxx"
    {
  EggVertex *vertex = DCAST(EggVertex, egg_stack.back());
  EggVertexAux *aux = new EggVertexAux((yyvsp[(3) - (4)]._string), LVecBase4d::zero());
  egg_stack.push_back(aux);
  if (vertex->has_aux((yyvsp[(3) - (4)]._string))) {
    eggyywarning("Ignoring repeated Aux name " + (yyvsp[(3) - (4)]._string));
  } else {
    vertex->set_aux_obj(aux);
  }
}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 1055 "panda/src/egg/parser.yxx"
    {
  egg_stack.pop_back();
}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 1061 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertex, egg_stack.back())->_dxyzs.
    insert(EggMorphVertex((yyvsp[(3) - (8)]._string), LVector3d((yyvsp[(5) - (8)]._number), (yyvsp[(6) - (8)]._number), (yyvsp[(7) - (8)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(3) - (8)]._string));
  }
}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 1069 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertex, egg_stack.back())->_dxyzs.
    insert(EggMorphVertex((yyvsp[(4) - (8)]._string), LVector3d((yyvsp[(5) - (8)]._number), (yyvsp[(6) - (8)]._number), (yyvsp[(7) - (8)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(4) - (8)]._string));
  }
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 1088 "panda/src/egg/parser.yxx"
    {
  DCAST(EggVertexUV, egg_stack.back())->set_uv(LTexCoordd((yyvsp[(1) - (2)]._number), (yyvsp[(2) - (2)]._number)));
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 1092 "panda/src/egg/parser.yxx"
    {
  DCAST(EggVertexUV, egg_stack.back())->set_uvw(LVecBase3d((yyvsp[(1) - (3)]._number), (yyvsp[(2) - (3)]._number), (yyvsp[(3) - (3)]._number)));
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 1096 "panda/src/egg/parser.yxx"
    {
  if (DCAST(EggVertexUV, egg_stack.back())->has_tangent()) {
    eggyywarning("Ignoring repeated tangent");
  } else {
    DCAST(EggVertexUV, egg_stack.back())->set_tangent(LNormald((yyvsp[(4) - (7)]._number), (yyvsp[(5) - (7)]._number), (yyvsp[(6) - (7)]._number)));
  }
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 1104 "panda/src/egg/parser.yxx"
    {
  if (DCAST(EggVertexUV, egg_stack.back())->has_binormal()) {
    eggyywarning("Ignoring repeated binormal");
  } else {
    DCAST(EggVertexUV, egg_stack.back())->set_binormal(LNormald((yyvsp[(4) - (7)]._number), (yyvsp[(5) - (7)]._number), (yyvsp[(6) - (7)]._number)));
  }
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 1112 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertexUV, egg_stack.back())->_duvs.
    insert(EggMorphTexCoord((yyvsp[(3) - (7)]._string), LVector3d((yyvsp[(5) - (7)]._number), (yyvsp[(6) - (7)]._number), 0.0))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(3) - (7)]._string));
  }
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 1120 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertexUV, egg_stack.back())->_duvs.
    insert(EggMorphTexCoord((yyvsp[(3) - (8)]._string), LVector3d((yyvsp[(5) - (8)]._number), (yyvsp[(6) - (8)]._number), (yyvsp[(7) - (8)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(3) - (8)]._string));
  }
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 1128 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertexUV, egg_stack.back())->_duvs.
    insert(EggMorphTexCoord((yyvsp[(4) - (7)]._string), LVector3d((yyvsp[(5) - (7)]._number), (yyvsp[(6) - (7)]._number), 0.0))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(4) - (7)]._string));
  }
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 1136 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertexUV, egg_stack.back())->_duvs.
    insert(EggMorphTexCoord((yyvsp[(4) - (8)]._string), LVector3d((yyvsp[(5) - (8)]._number), (yyvsp[(6) - (8)]._number), (yyvsp[(7) - (8)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(4) - (8)]._string));
  }
}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 1154 "panda/src/egg/parser.yxx"
    {
  DCAST(EggVertexAux, egg_stack.back())->set_aux(LVecBase4d((yyvsp[(1) - (4)]._number), (yyvsp[(2) - (4)]._number), (yyvsp[(3) - (4)]._number), (yyvsp[(4) - (4)]._number)));
}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 1168 "panda/src/egg/parser.yxx"
    {
  DCAST(EggVertex, egg_stack.back())->set_normal(LNormald((yyvsp[(1) - (3)]._number), (yyvsp[(2) - (3)]._number), (yyvsp[(3) - (3)]._number)));
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 1172 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertex, egg_stack.back())->_dnormals.
    insert(EggMorphNormal((yyvsp[(3) - (8)]._string), LVector3d((yyvsp[(5) - (8)]._number), (yyvsp[(6) - (8)]._number), (yyvsp[(7) - (8)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(3) - (8)]._string));
  }
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 1180 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertex, egg_stack.back())->_dnormals.
    insert(EggMorphNormal((yyvsp[(4) - (8)]._string), LVector3d((yyvsp[(5) - (8)]._number), (yyvsp[(6) - (8)]._number), (yyvsp[(7) - (8)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(4) - (8)]._string));
  }
}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 1198 "panda/src/egg/parser.yxx"
    {
  DCAST(EggVertex, egg_stack.back())->set_color(LColor((yyvsp[(1) - (4)]._number), (yyvsp[(2) - (4)]._number), (yyvsp[(3) - (4)]._number), (yyvsp[(4) - (4)]._number)));
}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 1202 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertex, egg_stack.back())->_drgbas.
    insert(EggMorphColor((yyvsp[(3) - (9)]._string), LVector4((yyvsp[(5) - (9)]._number), (yyvsp[(6) - (9)]._number), (yyvsp[(7) - (9)]._number), (yyvsp[(8) - (9)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(3) - (9)]._string));
  }
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 1210 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggVertex, egg_stack.back())->_drgbas.
    insert(EggMorphColor((yyvsp[(4) - (9)]._string), LVector4((yyvsp[(5) - (9)]._number), (yyvsp[(6) - (9)]._number), (yyvsp[(7) - (9)]._number), (yyvsp[(8) - (9)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(4) - (9)]._string));
  }
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 1228 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = new EggGroup((yyvsp[(2) - (2)]._string));
  egg_stack.push_back(group);
}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 1233 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  (yyval._egg) = group;
  egg_stack.pop_back();
  if (group->has_name()) {
    groups[group->get_name()] = group;
  }
  Thread::consider_yield();
}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 1253 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = new EggGroup((yyvsp[(2) - (2)]._string));
  group->set_group_type(EggGroup::GT_joint);
  egg_stack.push_back(group);
}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 1259 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 1274 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = new EggGroup((yyvsp[(2) - (2)]._string));
  group->set_group_type(EggGroup::GT_instance);
  egg_stack.push_back(group);
}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 1280 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  (yyval._egg) = group;
  egg_stack.pop_back();
  if (group->has_name()) {
    groups[group->get_name()] = group;
  }
}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 1300 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);
  unsigned long ulong_value = (yyvsp[(5) - (6)]._ulong);
  string strval = (yyvsp[(5) - (6)]._string);

  if (cmp_nocase_uh(name, "fps") == 0) {
    group->set_switch_fps(value);

  } else if (cmp_nocase_uh(name, "no_fog") == 0) {
    group->set_nofog_flag(value != 0);

  } else if (cmp_nocase_uh(name, "decal") == 0) {
    group->set_decal_flag(value != 0);

  } else if (cmp_nocase_uh(name, "direct") == 0) {
    group->set_direct_flag(value != 0);

  } else if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      group->set_alpha_mode(a);
    }

  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      group->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      group->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      group->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    group->set_depth_offset(ulong_value);

  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    group->set_draw_order(ulong_value);

  } else if (cmp_nocase_uh(name, "bin") == 0) {
    group->set_bin(strval);

  } else if (cmp_nocase_uh(name, "collide_mask") == 0) {
    group->set_collide_mask(group->get_collide_mask() | ulong_value);

  } else if (cmp_nocase_uh(name, "from_collide_mask") == 0) {
    group->set_from_collide_mask(group->get_from_collide_mask() | ulong_value);

  } else if (cmp_nocase_uh(name, "into_collide_mask") == 0) {
    group->set_into_collide_mask(group->get_into_collide_mask() | ulong_value);

  } else if (cmp_nocase_uh(name, "portal") == 0) {
    group->set_portal_flag(value != 0);

  } else if (cmp_nocase_uh(name, "occluder") == 0) {
    group->set_occluder_flag(value != 0);

  } else if (cmp_nocase_uh(name, "polylight") == 0) {
    group->set_polylight_flag(value != 0);

  } else if (cmp_nocase_uh(name, "indexed") == 0) {
    group->set_indexed_flag(value != 0);

  } else if (cmp_nocase_uh(name, "scroll_u") == 0) {
    group->set_scroll_u(value);

  } else if (cmp_nocase_uh(name, "scroll_v") == 0) {
    group->set_scroll_v(value);

  } else if (cmp_nocase_uh(name, "scroll_w") == 0) {
    group->set_scroll_w(value);

  } else if (cmp_nocase_uh(name, "scroll_r") == 0) {
    group->set_scroll_r(value);

  } else if (cmp_nocase_uh(name, "blend") == 0) {
    EggGroup::BlendMode blend_mode =
      EggGroup::string_blend_mode(strval);
    if (blend_mode == EggGroup::BM_unspecified) {
      eggyywarning("Unknown blend mode " + strval);
    } else {
      group->set_blend_mode(blend_mode);
    }

  } else if (cmp_nocase_uh(name, "blendop_a") == 0) {
    EggGroup::BlendOperand blend_operand =
      EggGroup::string_blend_operand(strval);
    if (blend_operand == EggGroup::BO_unspecified) {
      eggyywarning("Unknown blend operand " + strval);
    } else {
      group->set_blend_operand_a(blend_operand);
    }

  } else if (cmp_nocase_uh(name, "blendop_b") == 0) {
    EggGroup::BlendOperand blend_operand =
      EggGroup::string_blend_operand(strval);
    if (blend_operand == EggGroup::BO_unspecified) {
      eggyywarning("Unknown blend operand " + strval);
    } else {
      group->set_blend_operand_b(blend_operand);
    }

  } else if (cmp_nocase_uh(name, "blendr") == 0) {
    LColor color = group->get_blend_color();
    color[0] = value;
    group->set_blend_color(color);

  } else if (cmp_nocase_uh(name, "blendg") == 0) {
    LColor color = group->get_blend_color();
    color[1] = value;
    group->set_blend_color(color);

  } else if (cmp_nocase_uh(name, "blendb") == 0) {
    LColor color = group->get_blend_color();
    color[2] = value;
    group->set_blend_color(color);

  } else if (cmp_nocase_uh(name, "blenda") == 0) {
    LColor color = group->get_blend_color();
    color[3] = value;
    group->set_blend_color(color);

  } else {
    eggyywarning("Unknown group scalar " + name);
  }
}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 1448 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[(4) - (5)]._string);

  EggGroup::BillboardType f = EggGroup::string_billboard_type(strval);
  if (f == EggGroup::BT_none) {
    eggyywarning("Unknown billboard type " + strval);
  } else {
    group->set_billboard_type(f);
  }
}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 1460 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  group->set_billboard_center(LPoint3d((yyvsp[(4) - (7)]._number), (yyvsp[(5) - (7)]._number), (yyvsp[(6) - (7)]._number)));
}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 1465 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string name = (yyvsp[(3) - (7)]._string);

  group->set_collision_name(name);
}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 1472 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[(4) - (5)]._number);
  group->set_dcs_type(value!=0 ? EggGroup::DC_default : EggGroup::DC_none);
}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 1478 "panda/src/egg/parser.yxx"
    {
  // The special flavor of DCS, with { sync } or { nosync }.
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[(4) - (5)]._string);

  EggGroup::DCSType f = EggGroup::string_dcs_type(strval);
  if (f == EggGroup::DC_unspecified) {
    eggyywarning("Unknown DCS type " + strval);
  } else {
    group->set_dcs_type(f);
  }
}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 1491 "panda/src/egg/parser.yxx"
    {
  // The traditional flavor of DART, with { 0 } or { 1 }.
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[(4) - (5)]._number);
  group->set_dart_type(value!=0 ? EggGroup::DT_default : EggGroup::DT_none);
}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 1498 "panda/src/egg/parser.yxx"
    {
  // The special flavor of DART, with { sync } or { nosync }.
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[(4) - (5)]._string);

  EggGroup::DartType f = EggGroup::string_dart_type(strval);
  if (f == EggGroup::DT_none) {
    eggyywarning("Unknown dart type " + strval);
  } else {
    group->set_dart_type(f);
  }
}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 1511 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[(4) - (5)]._number);
  group->set_switch_flag(value!=0);
}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 1517 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string type = (yyvsp[(4) - (5)]._string);
  group->add_object_type(type);
}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1523 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[(4) - (5)]._number);
  group->set_model_flag(value!=0);
}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1529 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  group->set_tag((yyvsp[(3) - (6)]._string), (yyvsp[(5) - (6)]._string));
}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1534 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  int value = (int)(yyvsp[(4) - (5)]._number);
  group->set_texlist_flag(value!=0);
}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 1544 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  if (group->get_group_type() != EggGroup::GT_instance) {
    eggyyerror("<Ref> valid only within <Instance>");
  } else if ((yyvsp[(4) - (5)]._egg) != (EggObject *)NULL) {
    group->add_group_ref(DCAST(EggGroup, (yyvsp[(4) - (5)]._egg)));
  }
}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1553 "panda/src/egg/parser.yxx"
    {
  DCAST(EggGroup, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[(2) - (2)]._egg)));
}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 1567 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[(1) - (1)]._string);

  EggGroup::CollisionSolidType f = EggGroup::string_cs_type(strval);
  if (f == EggGroup::CST_none) {
    eggyywarning("Unknown collision solid type " + strval);
  } else {
    if (f == EggGroup::CST_polyset && group->get_cs_type() != EggGroup::CST_none) {
      // By convention, a CST_polyset doesn't replace any existing
      // contradictory type, so ignore it if this happens.  This
      // allows the artist to place, for instance, <ObjectType> {
      // sphere } and <ObjectType> { trigger } together.

    } else {
      group->set_cs_type(f);
    }
  }
}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1598 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  string strval = (yyvsp[(2) - (2)]._string);

  EggGroup::CollideFlags f = EggGroup::string_collide_flags(strval);
  if (f == EggGroup::CF_none) {
    eggyywarning("Unknown collision flag " + strval);
  } else {
    group->set_collide_flags(group->get_collide_flags() | f);
  }
}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1620 "panda/src/egg/parser.yxx"
    {
  egg_top_transform = egg_stack.back()->as_transform();
  egg_top_transform->clear_transform();
}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1636 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  if (group->get_group_type() != EggGroup::GT_joint) {
    eggyywarning("Unexpected <DefaultPose> outside of <Joint>");
  }
  egg_top_transform = &group->modify_default_pose();
  egg_top_transform->clear_transform();
}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1673 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_translate2d(LVector2d((yyvsp[(3) - (5)]._number), (yyvsp[(4) - (5)]._number)));
}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1680 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_translate3d(LVector3d((yyvsp[(3) - (6)]._number), (yyvsp[(4) - (6)]._number), (yyvsp[(5) - (6)]._number)));
}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1687 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_rotate2d((yyvsp[(3) - (4)]._number));
}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1694 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_rotx((yyvsp[(3) - (4)]._number));
}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1701 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_roty((yyvsp[(3) - (4)]._number));
}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1708 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_rotz((yyvsp[(3) - (4)]._number));
}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1715 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_rotate3d((yyvsp[(3) - (7)]._number), LVector3d((yyvsp[(4) - (7)]._number), (yyvsp[(5) - (7)]._number), (yyvsp[(6) - (7)]._number)));
}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1722 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_scale2d(LVecBase2d((yyvsp[(3) - (5)]._number), (yyvsp[(4) - (5)]._number)));
}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1729 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_scale3d(LVecBase3d((yyvsp[(3) - (6)]._number), (yyvsp[(4) - (6)]._number), (yyvsp[(5) - (6)]._number)));
}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1736 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_uniform_scale((yyvsp[(3) - (4)]._number));
}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1750 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_matrix3
    (LMatrix3d((yyvsp[(1) - (9)]._number), (yyvsp[(2) - (9)]._number), (yyvsp[(3) - (9)]._number),
               (yyvsp[(4) - (9)]._number), (yyvsp[(5) - (9)]._number), (yyvsp[(6) - (9)]._number),
               (yyvsp[(7) - (9)]._number), (yyvsp[(8) - (9)]._number), (yyvsp[(9) - (9)]._number)));
}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1768 "panda/src/egg/parser.yxx"
    {
  egg_top_transform->add_matrix4
    (LMatrix4d((yyvsp[(1) - (16)]._number), (yyvsp[(2) - (16)]._number), (yyvsp[(3) - (16)]._number), (yyvsp[(4) - (16)]._number),
               (yyvsp[(5) - (16)]._number), (yyvsp[(6) - (16)]._number), (yyvsp[(7) - (16)]._number), (yyvsp[(8) - (16)]._number),
               (yyvsp[(9) - (16)]._number), (yyvsp[(10) - (16)]._number), (yyvsp[(11) - (16)]._number), (yyvsp[(12) - (16)]._number),
               (yyvsp[(13) - (16)]._number), (yyvsp[(14) - (16)]._number), (yyvsp[(15) - (16)]._number), (yyvsp[(16) - (16)]._number)));
}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1787 "panda/src/egg/parser.yxx"
    {
  if ((yyvsp[(7) - (9)]._egg) != (EggVertexPool *)NULL) {
    EggVertexPool *pool = DCAST(EggVertexPool, (yyvsp[(7) - (9)]._egg));
    EggGroup *group = DCAST(EggGroup, egg_stack.back());
    PTA_double nums = (yyvsp[(3) - (9)]._number_list);
    double membership = (yyvsp[(4) - (9)]._number);

    for (int i = 0; i < (int)nums.size(); i++) {
      int index = (int)nums[i];
      EggVertex *vertex = pool->get_forward_vertex(index);
      if (vertex == NULL) {
        ostringstream errmsg;
        errmsg << "No vertex " << index << " in pool " << pool->get_name()
               << ends;
        eggyyerror(errmsg);
      } else {
        group->ref_vertex(vertex, membership);
      }
    }
  }
}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1820 "panda/src/egg/parser.yxx"
    {
  (yyval._number) = 1.0;
}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1824 "panda/src/egg/parser.yxx"
    {
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);
  double result = (yyvsp[(1) - (6)]._number);

  if (cmp_nocase_uh(name, "membership") == 0) {
    result = value;
  } else {
    eggyywarning("Unknown group vertex scalar " + name);
  }

  (yyval._number) = result;
}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1861 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  group->set_lod(EggSwitchConditionDistance((yyvsp[(3) - (11)]._number), (yyvsp[(4) - (11)]._number), LPoint3d((yyvsp[(7) - (11)]._number), (yyvsp[(8) - (11)]._number), (yyvsp[(9) - (11)]._number))));
}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1866 "panda/src/egg/parser.yxx"
    {
  EggGroup *group = DCAST(EggGroup, egg_stack.back());
  group->set_lod(EggSwitchConditionDistance((yyvsp[(3) - (12)]._number), (yyvsp[(4) - (12)]._number), LPoint3d((yyvsp[(8) - (12)]._number), (yyvsp[(9) - (12)]._number), (yyvsp[(10) - (12)]._number)), (yyvsp[(5) - (12)]._number)));
}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1883 "panda/src/egg/parser.yxx"
    {
  egg_stack.push_back(new EggPolygon((yyvsp[(2) - (2)]._string)));
}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1887 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1902 "panda/src/egg/parser.yxx"
    {
  egg_stack.push_back(new EggTriangleFan((yyvsp[(2) - (2)]._string)));
}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1906 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1921 "panda/src/egg/parser.yxx"
    {
  egg_stack.push_back(new EggTriangleStrip((yyvsp[(2) - (2)]._string)));
}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1925 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1940 "panda/src/egg/parser.yxx"
    {
  egg_stack.push_back(new EggPatch((yyvsp[(2) - (2)]._string)));
}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1944 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1959 "panda/src/egg/parser.yxx"
    {
  egg_stack.push_back(new EggPoint((yyvsp[(2) - (2)]._string)));
}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1963 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1978 "panda/src/egg/parser.yxx"
    {
  egg_stack.push_back(new EggLine((yyvsp[(2) - (2)]._string)));
}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1982 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1997 "panda/src/egg/parser.yxx"
    {
  egg_stack.push_back(new EggNurbsSurface((yyvsp[(2) - (2)]._string)));
}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 2001 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 2016 "panda/src/egg/parser.yxx"
    {
  egg_stack.push_back(new EggNurbsCurve((yyvsp[(2) - (2)]._string)));
}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 2020 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 2050 "panda/src/egg/parser.yxx"
    {
  if (!egg_stack.back()->is_of_type(EggCompositePrimitive::get_class_type())) {
    eggyyerror("Not a composite primitive; components are not allowed here.");
  } else {
    PT(EggCompositePrimitive) comp = DCAST(EggCompositePrimitive, egg_stack.back());
    if ((yyvsp[(3) - (4)]._number) < 0 || (yyvsp[(3) - (4)]._number) >= comp->get_num_components()) {
      eggyyerror("Invalid component number");
    }
  }
  // We temporarily add an EggPolygon to the stack, just to receive
  // the component attributes.
  egg_stack.push_back(new EggPolygon);
}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 2064 "panda/src/egg/parser.yxx"
    {
  PT(EggPrimitive) prim = DCAST(EggPrimitive, egg_stack.back());
  egg_stack.pop_back();
  PT(EggCompositePrimitive) comp = DCAST(EggCompositePrimitive, egg_stack.back());
  comp->set_component((int)(yyvsp[(3) - (7)]._number), prim);
}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 2078 "panda/src/egg/parser.yxx"
    {
  EggPrimitive *primitive = DCAST(EggPrimitive, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);
  string strval = (yyvsp[(5) - (6)]._string);

  if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      primitive->set_alpha_mode(a);
    }
  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      primitive->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      primitive->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      primitive->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    primitive->set_depth_offset((int)value);
  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    primitive->set_draw_order((int)value);
  } else if (cmp_nocase_uh(name, "bin") == 0) {
    primitive->set_bin(strval);
  } else if (cmp_nocase_uh(name, "thick") == 0) {
    if (primitive->is_of_type(EggLine::get_class_type())) {
      DCAST(EggLine, primitive)->set_thick(value);
    } else if (primitive->is_of_type(EggPoint::get_class_type())) {
      DCAST(EggPoint, primitive)->set_thick(value);
    } else {
      eggyywarning("scalar thick is only meaningful for points and lines.");
    }
  } else if (cmp_nocase_uh(name, "perspective") == 0) {
    if (primitive->is_of_type(EggPoint::get_class_type())) {
      DCAST(EggPoint, primitive)->set_perspective(value != 0);
    } else {
      eggyywarning("scalar perspective is only meaningful for points.");
    }
  } else {
    eggyywarning("Unknown scalar " + name);
  }
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 2164 "panda/src/egg/parser.yxx"
    {
  EggNurbsCurve *curve = DCAST(EggNurbsCurve, (yyvsp[(2) - (2)]._egg));
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  nurbs->_curves_on_surface.push_back(curve);
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 2171 "panda/src/egg/parser.yxx"
    {
  EggNurbsSurface *primitive = DCAST(EggNurbsSurface, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);
  string strval = (yyvsp[(5) - (6)]._string);

  if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      primitive->set_alpha_mode(a);
    }
  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      primitive->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      primitive->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      primitive->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    primitive->set_depth_offset((int)value);
  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    primitive->set_draw_order((int)value);
  } else if (cmp_nocase_uh(name, "bin") == 0) {
    primitive->set_bin(strval);
  } else if (cmp_nocase_uh(name, "u_subdiv") == 0) {
    primitive->set_u_subdiv((int)value);
  } else if (cmp_nocase_uh(name, "v_subdiv") == 0) {
    primitive->set_v_subdiv((int)value);
  } else {
    eggyywarning("Unknown scalar " + name);
  }
}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 2247 "panda/src/egg/parser.yxx"
    {
  EggNurbsCurve *primitive = DCAST(EggNurbsCurve, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);
  string strval = (yyvsp[(5) - (6)]._string);

  if (cmp_nocase_uh(name, "alpha") == 0) {
    EggRenderMode::AlphaMode a = EggRenderMode::string_alpha_mode(strval);
    if (a == EggRenderMode::AM_unspecified) {
      eggyywarning("Unknown alpha mode " + strval);
    } else {
      primitive->set_alpha_mode(a);
    }
  } else if (cmp_nocase_uh(name, "depth_write") == 0) {
    EggRenderMode::DepthWriteMode m =
      EggRenderMode::string_depth_write_mode(strval);
    if (m == EggRenderMode::DWM_unspecified) {
      eggyywarning("Unknown depth-write mode " + strval);
    } else {
      primitive->set_depth_write_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_test") == 0) {
    EggRenderMode::DepthTestMode m =
      EggRenderMode::string_depth_test_mode(strval);
    if (m == EggRenderMode::DTM_unspecified) {
      eggyywarning("Unknown depth-test mode " + strval);
    } else {
      primitive->set_depth_test_mode(m);
    }

  } else if (cmp_nocase_uh(name, "visibility") == 0) {
    EggRenderMode::VisibilityMode m =
      EggRenderMode::string_visibility_mode(strval);
    if (m == EggRenderMode::VM_unspecified) {
      eggyywarning("Unknown visibility mode " + strval);
    } else {
      primitive->set_visibility_mode(m);
    }

  } else if (cmp_nocase_uh(name, "depth_offset") == 0) {
    primitive->set_depth_offset((int)value);
  } else if (cmp_nocase_uh(name, "draw_order") == 0) {
    primitive->set_draw_order((int)value);
  } else if (cmp_nocase_uh(name, "bin") == 0) {
    primitive->set_bin(strval);
  } else if (cmp_nocase_uh(name, "subdiv") == 0) {
    primitive->set_subdiv((int)value);
  } else if (cmp_nocase_uh(name, "type") == 0) {
    EggCurve::CurveType a = EggCurve::string_curve_type(strval);
    if (a == EggCurve::CT_none) {
      eggyywarning("Unknown curve type " + strval);
    } else {
      primitive->set_curve_type(a);
    }

  } else {
    eggyywarning("Unknown scalar " + name);
  }
}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 2318 "panda/src/egg/parser.yxx"
    {
  if ((yyvsp[(1) - (1)]._egg) != (EggTexture *)NULL) {
    EggTexture *texture = DCAST(EggTexture, (yyvsp[(1) - (1)]._egg));
    DCAST(EggPrimitive, egg_stack.back())->add_texture(texture);
  }
}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 2335 "panda/src/egg/parser.yxx"
    {
  EggTexture *texture = NULL;

  // Defining a texture on-the-fly.
  Filename filename = (yyvsp[(1) - (1)]._string);
  string tref_name = filename.get_basename();

  Textures::iterator vpi = textures.find(tref_name);
  if (vpi == textures.end()) {
    // The texture was not yet defined.  Define it.
    texture = new EggTexture(tref_name, filename);
    textures[tref_name] = texture;

    if (egg_top_node != NULL) {
      egg_top_node->add_child(texture);
    }

  } else {
    // The texture already existed.  Use it.
    texture = (*vpi).second;
    if (filename != texture->get_filename()) {
      eggyywarning(string("Using previous path: ") +
                   texture->get_filename().get_fullpath());
    }
  }

  nassertr(texture != NULL, 0);
  DCAST(EggPrimitive, egg_stack.back())->add_texture(texture);
}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 2375 "panda/src/egg/parser.yxx"
    {
  if ((yyvsp[(1) - (1)]._egg) != (EggMaterial *)NULL) {
    EggMaterial *material = DCAST(EggMaterial, (yyvsp[(1) - (1)]._egg));
    DCAST(EggPrimitive, egg_stack.back())->set_material(material);
  }
}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 2392 "panda/src/egg/parser.yxx"
    {
  DCAST(EggPrimitive, egg_stack.back())->set_normal(LNormald((yyvsp[(1) - (3)]._number), (yyvsp[(2) - (3)]._number), (yyvsp[(3) - (3)]._number)));
}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 2396 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggPrimitive, egg_stack.back())->_dnormals.
    insert(EggMorphNormal((yyvsp[(3) - (8)]._string), LVector3d((yyvsp[(5) - (8)]._number), (yyvsp[(6) - (8)]._number), (yyvsp[(7) - (8)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(3) - (8)]._string));
  }
}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 2404 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggPrimitive, egg_stack.back())->_dnormals.
    insert(EggMorphNormal((yyvsp[(4) - (8)]._string), LVector3d((yyvsp[(5) - (8)]._number), (yyvsp[(6) - (8)]._number), (yyvsp[(7) - (8)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(4) - (8)]._string));
  }
}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 2422 "panda/src/egg/parser.yxx"
    {
  DCAST(EggPrimitive, egg_stack.back())->set_color(LColor((yyvsp[(1) - (4)]._number), (yyvsp[(2) - (4)]._number), (yyvsp[(3) - (4)]._number), (yyvsp[(4) - (4)]._number)));
}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 2426 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggPrimitive, egg_stack.back())->_drgbas.
    insert(EggMorphColor((yyvsp[(3) - (9)]._string), LVector4((yyvsp[(5) - (9)]._number), (yyvsp[(6) - (9)]._number), (yyvsp[(7) - (9)]._number), (yyvsp[(8) - (9)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(3) - (9)]._string));
  }
}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 2434 "panda/src/egg/parser.yxx"
    {
  bool inserted = DCAST(EggPrimitive, egg_stack.back())->_drgbas.
    insert(EggMorphColor((yyvsp[(4) - (9)]._string), LVector4((yyvsp[(5) - (9)]._number), (yyvsp[(6) - (9)]._number), (yyvsp[(7) - (9)]._number), (yyvsp[(8) - (9)]._number)))).second;
  if (!inserted) {
    eggyywarning("Ignoring repeated morph name " + (yyvsp[(4) - (9)]._string));
  }
}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 2452 "panda/src/egg/parser.yxx"
    {
  EggPrimitive *primitive = DCAST(EggPrimitive, egg_stack.back());
  int value = (int)(yyvsp[(1) - (1)]._number);
  primitive->set_bface_flag(value!=0);
}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 2468 "panda/src/egg/parser.yxx"
    {
  if ((yyvsp[(6) - (8)]._egg) != (EggVertexPool *)NULL) {
    EggVertexPool *pool = DCAST(EggVertexPool, (yyvsp[(6) - (8)]._egg));
    EggPrimitive *prim = DCAST(EggPrimitive, egg_stack.back());
    PTA_double nums = (yyvsp[(3) - (8)]._number_list);

    for (int i = 0; i < (int)nums.size(); i++) {
      int index = (int)nums[i];
      EggVertex *vertex = pool->get_forward_vertex(index);
      if (vertex == NULL) {
        ostringstream errmsg;
        errmsg << "No vertex " << index << " in pool " << pool->get_name()
               << ends;
        eggyyerror(errmsg);
      } else {
        prim->add_vertex(vertex);
      }
    }
  }
}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 2499 "panda/src/egg/parser.yxx"
    {
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  int u_order = (int)(yyvsp[(1) - (2)]._number);
  int v_order = (int)(yyvsp[(2) - (2)]._number);
  nurbs->set_u_order(u_order);
  nurbs->set_v_order(v_order);
}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 2517 "panda/src/egg/parser.yxx"
    {
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  PTA_double nums = (yyvsp[(1) - (1)]._number_list);

  nurbs->set_num_u_knots(nums.size());
  for (int i = 0; i < (int)nums.size(); i++) {
    nurbs->set_u_knot(i, nums[i]);
  }
}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 2537 "panda/src/egg/parser.yxx"
    {
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  PTA_double nums = (yyvsp[(1) - (1)]._number_list);

  nurbs->set_num_v_knots(nums.size());
  for (int i = 0; i < (int)nums.size(); i++) {
    nurbs->set_v_knot(i, nums[i]);
  }
}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 2557 "panda/src/egg/parser.yxx"
    {
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  nurbs->_trims.push_back(EggNurbsSurface::Trim());
}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 2573 "panda/src/egg/parser.yxx"
    {
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  nassertr(!nurbs->_trims.empty(), 0);
  nurbs->_trims.back().push_back(EggNurbsSurface::Loop());
}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 2579 "panda/src/egg/parser.yxx"
    {
  EggNurbsSurface *nurbs = DCAST(EggNurbsSurface, egg_stack.back());
  nassertr(!nurbs->_trims.empty(), 0);
  nassertr(!nurbs->_trims.back().empty(), 0);
  EggNurbsCurve *curve = DCAST(EggNurbsCurve, (yyvsp[(2) - (2)]._egg));
  nurbs->_trims.back().back().push_back(curve);
}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 2598 "panda/src/egg/parser.yxx"
    {
  EggNurbsCurve *nurbs = DCAST(EggNurbsCurve, egg_stack.back());
  int order = (int)(yyvsp[(1) - (1)]._number);
  nurbs->set_order(order);
}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 2614 "panda/src/egg/parser.yxx"
    {
  EggNurbsCurve *nurbs = DCAST(EggNurbsCurve, egg_stack.back());
  PTA_double nums = (yyvsp[(1) - (1)]._number_list);

  nurbs->set_num_knots(nums.size());
  for (int i = 0; i < (int)nums.size(); i++) {
    nurbs->set_knot(i, nums[i]);
  }
}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 2635 "panda/src/egg/parser.yxx"
    {
  EggTable *table = new EggTable((yyvsp[(2) - (2)]._string));
  table->set_table_type(EggTable::TT_table);
  egg_stack.push_back(table);
}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 2641 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
  Thread::consider_yield();
}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 2658 "panda/src/egg/parser.yxx"
    {
  EggTable *table = new EggTable((yyvsp[(2) - (2)]._string));
  table->set_table_type(EggTable::TT_bundle);
  egg_stack.push_back(table);
}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 2664 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 2680 "panda/src/egg/parser.yxx"
    {
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[(2) - (2)]._egg)));
}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 2684 "panda/src/egg/parser.yxx"
    {
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[(2) - (2)]._egg)));
}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 2688 "panda/src/egg/parser.yxx"
    {
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[(2) - (2)]._egg)));
}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 2692 "panda/src/egg/parser.yxx"
    {
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[(2) - (2)]._egg)));
}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 2696 "panda/src/egg/parser.yxx"
    {
  DCAST(EggTable, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[(2) - (2)]._egg)));
}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 2711 "panda/src/egg/parser.yxx"
    {
  EggSAnimData *anim_data = new EggSAnimData((yyvsp[(2) - (2)]._string));
  egg_stack.push_back(anim_data);
}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 2716 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 2733 "panda/src/egg/parser.yxx"
    {
  EggSAnimData *anim_data = DCAST(EggSAnimData, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);

  if (cmp_nocase_uh(name, "fps") == 0) {
    anim_data->set_fps(value);
  } else {
    eggyywarning("Unsupported S$Anim scalar: " + name);
  }
}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 2745 "panda/src/egg/parser.yxx"
    {
  DCAST(EggSAnimData, egg_stack.back())->set_data((yyvsp[(4) - (5)]._number_list));
}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 2759 "panda/src/egg/parser.yxx"
    {
  EggXfmAnimData *anim_data = new EggXfmAnimData((yyvsp[(2) - (2)]._string));
  egg_stack.push_back(anim_data);
}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 2764 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 2781 "panda/src/egg/parser.yxx"
    {
  EggXfmAnimData *anim_data = DCAST(EggXfmAnimData, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);
  string strval = (yyvsp[(5) - (6)]._string);

  if (cmp_nocase_uh(name, "fps") == 0) {
    anim_data->set_fps(value);
  } else if (cmp_nocase_uh(name, "order") == 0) {
    anim_data->set_order(strval);
  } else if (cmp_nocase_uh(name, "contents") == 0) {
    anim_data->set_contents(strval);
  } else {
    eggyywarning("Unsupported Xfm$Anim scalar: " + name);
  }
}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 2798 "panda/src/egg/parser.yxx"
    {
  DCAST(EggXfmAnimData, egg_stack.back())->set_data((yyvsp[(4) - (5)]._number_list));
}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 2812 "panda/src/egg/parser.yxx"
    {
  EggXfmSAnim *anim_group = new EggXfmSAnim((yyvsp[(2) - (2)]._string));
  egg_stack.push_back(anim_group);
}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 2817 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 2834 "panda/src/egg/parser.yxx"
    {
  EggXfmSAnim *anim_group = DCAST(EggXfmSAnim, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);
  string strval = (yyvsp[(5) - (6)]._string);

  if (cmp_nocase_uh(name, "fps") == 0) {
    anim_group->set_fps(value);
  } else if (cmp_nocase_uh(name, "order") == 0) {
    anim_group->set_order(strval);
  } else {
    eggyywarning("Unsupported Xfm$Anim_S$ scalar: " + name);
  }
}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 2849 "panda/src/egg/parser.yxx"
    {
  DCAST(EggXfmSAnim, egg_stack.back())->add_child(DCAST(EggNode, (yyvsp[(2) - (2)]._egg)));
}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 2864 "panda/src/egg/parser.yxx"
    {
  EggAnimPreload *anim_preload = new EggAnimPreload((yyvsp[(2) - (2)]._string));
  egg_stack.push_back(anim_preload);
}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 2869 "panda/src/egg/parser.yxx"
    {
  (yyval._egg) = egg_stack.back();
  egg_stack.pop_back();
}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 2886 "panda/src/egg/parser.yxx"
    {
  EggAnimPreload *anim_preload = DCAST(EggAnimPreload, egg_stack.back());
  string name = (yyvsp[(3) - (6)]._string);
  double value = (yyvsp[(5) - (6)]._number);

  if (cmp_nocase_uh(name, "fps") == 0) {
    anim_preload->set_fps(value);
  } else if (cmp_nocase_uh(name, "frames") == 0) {
    anim_preload->set_num_frames((int)value);
  } else {
    eggyywarning("Unsupported AnimPreload scalar: " + name);
  }
}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 2910 "panda/src/egg/parser.yxx"
    {
  (yyval._number_list) = PTA_double::empty_array(0);
}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 2914 "panda/src/egg/parser.yxx"
    {
  (yyval._number_list).push_back((double)(yyvsp[(2) - (2)]._number));
}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 2928 "panda/src/egg/parser.yxx"
    {
  (yyval._number_list) = PTA_double::empty_array(0);
}
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 2932 "panda/src/egg/parser.yxx"
    {
  (yyval._number_list).push_back((yyvsp[(2) - (2)]._number));
}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 2946 "panda/src/egg/parser.yxx"
    {
  string name = (yyvsp[(1) - (1)]._string);
  Textures::iterator vpi = textures.find(name);
  if (vpi == textures.end()) {
    eggyyerror("Unknown texture " + name);
    (yyval._egg) = PT(EggObject)();
  } else {
    (yyval._egg) = (*vpi).second;
  }
}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 2967 "panda/src/egg/parser.yxx"
    {
  string name = (yyvsp[(1) - (1)]._string);
  Materials::iterator vpi = materials.find(name);
  if (vpi == materials.end()) {
    eggyyerror("Unknown material " + name);
    (yyval._egg) = PT(EggObject)();
  } else {
    (yyval._egg) = (*vpi).second;
  }
}
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 2988 "panda/src/egg/parser.yxx"
    {
  string name = (yyvsp[(1) - (1)]._string);
  VertexPools::iterator vpi = vertex_pools.find(name);
  if (vpi == vertex_pools.end()) {
    // This will become a forward reference.
    EggVertexPool *pool = new EggVertexPool(name);
    // The egg syntax starts counting at 1 by convention.
    pool->set_highest_index(0);
    vertex_pools[name] = pool;
    (yyval._egg) = pool;
  } else {
    (yyval._egg) = (*vpi).second;
  }
}
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 3013 "panda/src/egg/parser.yxx"
    {
  string name = (yyvsp[(1) - (1)]._string);
  Groups::iterator vpi = groups.find(name);
  if (vpi == groups.end()) {
    eggyyerror("Unknown group " + name);
    (yyval._egg) = PT(EggObject)();
  } else {
    (yyval._egg) = (*vpi).second;
  }
}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 3034 "panda/src/egg/parser.yxx"
    {
  eggyyerror("Name required.");
  (yyval._string) = "";
}
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 3063 "panda/src/egg/parser.yxx"
    {
  eggyyerror("String required.");
  (yyval._string) = "";
}
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 3079 "panda/src/egg/parser.yxx"
    {
  (yyval._string) = "";
}
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 3097 "panda/src/egg/parser.yxx"
    {
  (yyval._string) = (yyvsp[(1) - (1)]._string);
}
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 3101 "panda/src/egg/parser.yxx"
    {
  (yyval._string) = (yyvsp[(1) - (1)]._string);
}
    break;

  case 266:
/* Line 1792 of yacc.c  */
#line 3118 "panda/src/egg/parser.yxx"
    {
  (yyval._string) = "";
}
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 3122 "panda/src/egg/parser.yxx"
    {
  (yyval._string) = (yyvsp[(1) - (1)]._string);
}
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 3138 "panda/src/egg/parser.yxx"
    {
  (yyval._string) = (yyvsp[(1) - (1)]._string);
}
    break;

  case 269:
/* Line 1792 of yacc.c  */
#line 3142 "panda/src/egg/parser.yxx"
    {
  (yyval._string) = (yyvsp[(1) - (2)]._string) + "\n" + (yyvsp[(2) - (2)]._string);
}
    break;

  case 271:
/* Line 1792 of yacc.c  */
#line 3157 "panda/src/egg/parser.yxx"
    {
  (yyval._number) = (yyvsp[(1) - (1)]._ulong);
}
    break;

  case 272:
/* Line 1792 of yacc.c  */
#line 3172 "panda/src/egg/parser.yxx"
    {
  (yyval._number) = (yyvsp[(1) - (1)]._number);
  (yyval._ulong) = (unsigned long)(yyvsp[(1) - (1)]._number);
  (yyval._string) = (yyvsp[(1) - (1)]._string);
}
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 3178 "panda/src/egg/parser.yxx"
    {
  (yyval._number) = (yyvsp[(1) - (1)]._ulong);
  (yyval._ulong) = (yyvsp[(1) - (1)]._ulong);
  (yyval._string) = (yyvsp[(1) - (1)]._string);
}
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 3184 "panda/src/egg/parser.yxx"
    {
  (yyval._number) = 0.0;
  (yyval._ulong) = 0;
  (yyval._string) = (yyvsp[(1) - (1)]._string);
}
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 3201 "panda/src/egg/parser.yxx"
    {
  int i = (int)(yyvsp[(1) - (1)]._number);
  if ((double)i != (yyvsp[(1) - (1)]._number)) {
    eggyywarning("Integer expected.");
    (yyval._number) = (double)i;
  }
}
    break;

  case 276:
/* Line 1792 of yacc.c  */
#line 3209 "panda/src/egg/parser.yxx"
    {
  (yyval._number) = (yyvsp[(1) - (1)]._ulong);
}
    break;


/* Line 1792 of yacc.c  */
#line 5147 "built/tmp/parser.yxx.c"
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


