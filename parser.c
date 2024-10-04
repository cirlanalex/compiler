/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

  
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "messages.h"
  #include "usage.h"
  #include "symtable.h"
  #include "gencode.h"

  void yyerror(char *msg);    /* forward declaration */
  /* exported by the lexer (made with flex) */
  extern int yylex(void);
  extern char *yytext;
  extern void showErrorLine();
  extern void initLexer(FILE *f);
  extern void finalizeLexer();
  extern int warnings;
  FILE *input;
  FILE *output;


#line 94 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_CONST = 4,                      /* CONST  */
  YYSYMBOL_VAR = 5,                        /* VAR  */
  YYSYMBOL_ARRAY = 6,                      /* ARRAY  */
  YYSYMBOL_RANGE = 7,                      /* RANGE  */
  YYSYMBOL_OF = 8,                         /* OF  */
  YYSYMBOL_FUNCTION = 9,                   /* FUNCTION  */
  YYSYMBOL_PROCEDURE = 10,                 /* PROCEDURE  */
  YYSYMBOL_BEGINTOK = 11,                  /* BEGINTOK  */
  YYSYMBOL_ENDTOK = 12,                    /* ENDTOK  */
  YYSYMBOL_ASSIGN = 13,                    /* ASSIGN  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_DO = 18,                        /* DO  */
  YYSYMBOL_RELOPLT = 19,                   /* RELOPLT  */
  YYSYMBOL_RELOPLEQ = 20,                  /* RELOPLEQ  */
  YYSYMBOL_RELOPEQ = 21,                   /* RELOPEQ  */
  YYSYMBOL_RELOPNEQ = 22,                  /* RELOPNEQ  */
  YYSYMBOL_RELOPGEQ = 23,                  /* RELOPGEQ  */
  YYSYMBOL_RELOPGT = 24,                   /* RELOPGT  */
  YYSYMBOL_INTEGER = 25,                   /* INTEGER  */
  YYSYMBOL_REAL = 26,                      /* REAL  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_NOT = 29,                       /* NOT  */
  YYSYMBOL_DIV = 30,                       /* DIV  */
  YYSYMBOL_MOD = 31,                       /* MOD  */
  YYSYMBOL_SKIP = 32,                      /* SKIP  */
  YYSYMBOL_READLN = 33,                    /* READLN  */
  YYSYMBOL_WRITELN = 34,                   /* WRITELN  */
  YYSYMBOL_INTNUMBER = 35,                 /* INTNUMBER  */
  YYSYMBOL_REALNUMBER = 36,                /* REALNUMBER  */
  YYSYMBOL_IDENTIFIER = 37,                /* IDENTIFIER  */
  YYSYMBOL_38_ = 38,                       /* '+'  */
  YYSYMBOL_39_ = 39,                       /* '-'  */
  YYSYMBOL_40_ = 40,                       /* '*'  */
  YYSYMBOL_41_ = 41,                       /* '/'  */
  YYSYMBOL_42_ = 42,                       /* ';'  */
  YYSYMBOL_43_ = 43,                       /* '.'  */
  YYSYMBOL_44_ = 44,                       /* ':'  */
  YYSYMBOL_45_ = 45,                       /* ','  */
  YYSYMBOL_46_ = 46,                       /* '['  */
  YYSYMBOL_47_ = 47,                       /* ']'  */
  YYSYMBOL_48_ = 48,                       /* '('  */
  YYSYMBOL_49_ = 49,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_program = 51,                   /* program  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_53_2 = 53,                      /* $@2  */
  YYSYMBOL_54_3 = 54,                      /* $@3  */
  YYSYMBOL_55_4 = 55,                      /* $@4  */
  YYSYMBOL_56_5 = 56,                      /* $@5  */
  YYSYMBOL_ConstDecl = 57,                 /* ConstDecl  */
  YYSYMBOL_NumericValue = 58,              /* NumericValue  */
  YYSYMBOL_VarDecl = 59,                   /* VarDecl  */
  YYSYMBOL_IdentifierList = 60,            /* IdentifierList  */
  YYSYMBOL_TypeSpec = 61,                  /* TypeSpec  */
  YYSYMBOL_BasicType = 62,                 /* BasicType  */
  YYSYMBOL_FuncProcDecl = 63,              /* FuncProcDecl  */
  YYSYMBOL_SubProgDecl = 64,               /* SubProgDecl  */
  YYSYMBOL_SubProgHeading = 65,            /* SubProgHeading  */
  YYSYMBOL_66_6 = 66,                      /* $@6  */
  YYSYMBOL_67_7 = 67,                      /* $@7  */
  YYSYMBOL_PossibleParameters = 68,        /* PossibleParameters  */
  YYSYMBOL_Parameters = 69,                /* Parameters  */
  YYSYMBOL_ParameterList = 70,             /* ParameterList  */
  YYSYMBOL_ParamList = 71,                 /* ParamList  */
  YYSYMBOL_CompoundStatement = 72,         /* CompoundStatement  */
  YYSYMBOL_OptionalStatements = 73,        /* OptionalStatements  */
  YYSYMBOL_StatementList = 74,             /* StatementList  */
  YYSYMBOL_Statement = 75,                 /* Statement  */
  YYSYMBOL_76_8 = 76,                      /* @8  */
  YYSYMBOL_77_9 = 77,                      /* @9  */
  YYSYMBOL_78_10 = 78,                     /* @10  */
  YYSYMBOL_79_11 = 79,                     /* $@11  */
  YYSYMBOL_LhsList = 80,                   /* LhsList  */
  YYSYMBOL_Lhs = 81,                       /* Lhs  */
  YYSYMBOL_ProcedureCall = 82,             /* ProcedureCall  */
  YYSYMBOL_Guard = 83,                     /* Guard  */
  YYSYMBOL_BoolAtom = 84,                  /* BoolAtom  */
  YYSYMBOL_Relop = 85,                     /* Relop  */
  YYSYMBOL_ArithExprList = 86,             /* ArithExprList  */
  YYSYMBOL_ArithExpr = 87                  /* ArithExpr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   203

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      48,    49,    40,    38,    45,    39,    43,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    42,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    75,    75,    76,    77,    78,    79,    75,    83,    84,
      87,    88,    91,    92,    95,    96,    99,   100,   103,   104,
     107,   108,   111,   114,   114,   115,   115,   118,   119,   122,
     125,   126,   129,   130,   133,   136,   137,   140,   141,   144,
     145,   146,   147,   148,   148,   148,   149,   149,   149,   152,
     153,   155,   156,   159,   160,   161,   162,   165,   166,   167,
     168,   169,   172,   175,   176,   177,   178,   179,   180,   183,
     184,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "CONST",
  "VAR", "ARRAY", "RANGE", "OF", "FUNCTION", "PROCEDURE", "BEGINTOK",
  "ENDTOK", "ASSIGN", "IF", "THEN", "ELSE", "WHILE", "DO", "RELOPLT",
  "RELOPLEQ", "RELOPEQ", "RELOPNEQ", "RELOPGEQ", "RELOPGT", "INTEGER",
  "REAL", "AND", "OR", "NOT", "DIV", "MOD", "SKIP", "READLN", "WRITELN",
  "INTNUMBER", "REALNUMBER", "IDENTIFIER", "'+'", "'-'", "'*'", "'/'",
  "';'", "'.'", "':'", "','", "'['", "']'", "'('", "')'", "$accept",
  "program", "$@1", "$@2", "$@3", "$@4", "$@5", "ConstDecl",
  "NumericValue", "VarDecl", "IdentifierList", "TypeSpec", "BasicType",
  "FuncProcDecl", "SubProgDecl", "SubProgHeading", "$@6", "$@7",
  "PossibleParameters", "Parameters", "ParameterList", "ParamList",
  "CompoundStatement", "OptionalStatements", "StatementList", "Statement",
  "@8", "@9", "@10", "$@11", "LhsList", "Lhs", "ProcedureCall", "Guard",
  "BoolAtom", "Relop", "ArithExprList", "ArithExpr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-119)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,    -8,    36,    11,  -119,  -119,  -119,    57,    33,  -119,
      75,    93,   120,   100,  -119,  -119,  -119,    68,  -119,   117,
     156,  -119,    26,   110,   114,   130,   161,   135,  -119,   132,
    -119,  -119,   137,  -119,  -119,  -119,  -119,    80,  -119,  -119,
      66,   147,  -119,   133,   133,   -18,  -119,  -119,   136,   138,
      -1,  -119,   168,   141,  -119,   172,  -119,   144,  -119,   181,
       9,   148,   149,  -119,   -18,  -119,  -119,    41,    28,   -18,
     106,  -119,    85,   -18,   152,    28,    28,    28,  -119,    80,
      28,  -119,   155,   100,   124,   -14,  -119,   145,  -119,  -119,
      28,    28,    28,   123,   -12,    62,  -119,   -18,   -18,  -119,
    -119,  -119,  -119,  -119,  -119,    28,    28,    28,    28,    28,
      28,    28,   146,   150,    23,  -119,    24,   119,   101,    50,
    -119,   119,   151,   131,    26,     9,  -119,   153,    19,    73,
      89,  -119,  -119,    80,  -119,   166,  -119,  -119,   123,   123,
    -119,  -119,   119,   176,   152,  -119,    28,  -119,  -119,  -119,
     189,    26,  -119,  -119,  -119,    28,  -119,  -119,  -119,    80,
    -119,   119,   145,  -119,   105,   183,  -119,  -119,  -119,    80,
    -119
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     9,     3,     0,    13,
       0,     4,     0,     0,    21,    10,    11,     0,    14,     0,
       5,     8,     0,     0,     0,     0,     0,     0,    13,     0,
      18,    19,     0,    16,    15,    23,    25,    36,     6,    20,
       0,     0,    12,     0,    28,     0,    46,    40,     0,     0,
      53,    42,     0,    35,    37,     0,    41,     0,    22,     0,
       0,     0,     0,    27,     0,    75,    76,    71,     0,     0,
       0,    57,     0,     0,     0,     0,     0,     0,    34,     0,
       0,     7,     0,     0,     0,     0,    30,     0,    26,    58,
       0,     0,     0,    83,     0,     0,    43,     0,     0,    63,
      64,    65,    66,    67,    68,     0,     0,     0,     0,     0,
       0,     0,    47,    51,     0,    49,     0,    69,     0,     0,
      38,    39,     0,     0,     0,     0,    29,     0,     0,     0,
       0,    61,    84,     0,    60,    59,    81,    82,    77,    78,
      79,    80,    62,     0,     0,    55,     0,    56,    52,    54,
       0,     0,    33,    31,    24,     0,    72,    74,    44,     0,
      50,    70,     0,    32,     0,     0,    48,    17,    73,     0,
      45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,   173,
      -9,  -118,   -84,  -119,  -119,  -119,  -119,  -119,  -119,   158,
    -119,    78,    -6,  -119,  -119,   -79,  -119,  -119,  -119,  -119,
    -119,   -69,  -119,   -42,  -119,  -119,   -29,   -67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,     9,    14,    26,    57,     7,    17,    11,
      84,    32,    33,    20,    27,    28,    43,    44,    62,    61,
      85,    86,    51,    52,    53,    54,   133,   165,    73,   143,
     114,    55,    56,    70,    71,   111,   116,    72
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     120,    93,    95,   127,    19,   115,   152,     1,   117,   118,
     117,    64,   -51,   121,    83,    97,    98,    65,    66,    67,
      38,    68,    89,   128,   117,   130,   155,    94,   125,     3,
      69,   112,    29,   163,    58,   126,     4,   131,   136,   137,
     138,   139,   140,   141,   142,    76,    18,    77,   119,   105,
     106,    30,    31,     5,   158,   134,   135,   107,   108,   109,
     110,     8,   129,    65,    66,    67,   156,    68,   144,   146,
      10,    13,   145,   147,   123,   160,    92,    37,   167,   161,
     166,    99,   100,   101,   102,   103,   104,    90,   164,    91,
     170,    37,   105,   106,    45,   146,    12,    46,    13,   149,
     107,   108,   109,   110,    99,   100,   101,   102,   103,   104,
      21,   132,    47,    48,    49,   105,   106,    50,   146,   105,
     106,    96,   157,   107,   108,   109,   110,   107,   108,   109,
     110,   105,   106,    97,    98,   105,   106,    18,   132,   107,
     108,   109,   110,   107,   108,   109,   110,    34,   148,   105,
     106,    35,   168,   105,   106,    15,    16,   107,   108,   109,
     110,    22,    23,   109,   110,    24,    25,    36,   124,    23,
      30,    31,    37,    97,    98,   151,    23,    39,    41,    42,
      78,    60,    59,    79,    74,    80,    75,    81,    82,   113,
     122,    88,    87,    97,   159,   154,    76,   162,   150,   169,
       0,    40,    63,   153
};

static const yytype_int16 yycheck[] =
{
      79,    68,    69,    87,    13,    74,   124,     3,    75,    76,
      77,    29,    13,    80,     5,    27,    28,    35,    36,    37,
      26,    39,    64,    90,    91,    92,     7,    69,    42,    37,
      48,    73,     6,   151,    40,    49,     0,    49,   105,   106,
     107,   108,   109,   110,   111,    46,    37,    48,    77,    30,
      31,    25,    26,    42,   133,    97,    98,    38,    39,    40,
      41,     4,    91,    35,    36,    37,    47,    39,    45,    45,
      37,     5,    49,    49,    83,   144,    48,    11,   162,   146,
     159,    19,    20,    21,    22,    23,    24,    46,   155,    48,
     169,    11,    30,    31,    14,    45,    21,    17,     5,    49,
      38,    39,    40,    41,    19,    20,    21,    22,    23,    24,
      42,    49,    32,    33,    34,    30,    31,    37,    45,    30,
      31,    15,    49,    38,    39,    40,    41,    38,    39,    40,
      41,    30,    31,    27,    28,    30,    31,    37,    49,    38,
      39,    40,    41,    38,    39,    40,    41,    37,    47,    30,
      31,    37,    47,    30,    31,    35,    36,    38,    39,    40,
      41,    44,    45,    40,    41,     9,    10,    37,    44,    45,
      25,    26,    11,    27,    28,    44,    45,    42,    46,    42,
      12,    48,    35,    42,    48,    13,    48,    43,     7,    37,
      35,    42,    44,    27,    18,    42,    46,     8,    47,    16,
      -1,    28,    44,   125
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    51,    37,     0,    42,    52,    57,     4,    53,
      37,    59,    21,     5,    54,    35,    36,    58,    37,    60,
      63,    42,    44,    45,     9,    10,    55,    64,    65,     6,
      25,    26,    61,    62,    37,    37,    37,    11,    72,    42,
      59,    46,    42,    66,    67,    14,    17,    32,    33,    34,
      37,    72,    73,    74,    75,    81,    82,    56,    72,    35,
      48,    69,    68,    69,    29,    35,    36,    37,    39,    48,
      83,    84,    87,    78,    48,    48,    46,    48,    12,    42,
      13,    43,     7,     5,    60,    70,    71,    44,    42,    83,
      46,    48,    48,    87,    83,    87,    15,    27,    28,    19,
      20,    21,    22,    23,    24,    30,    31,    38,    39,    40,
      41,    85,    83,    37,    80,    81,    86,    87,    87,    86,
      75,    87,    35,    60,    44,    42,    49,    62,    87,    86,
      87,    49,    49,    76,    83,    83,    87,    87,    87,    87,
      87,    87,    87,    79,    45,    49,    45,    49,    47,    49,
      47,    44,    61,    71,    42,     7,    47,    49,    75,    18,
      81,    87,     8,    61,    87,    77,    75,    62,    47,    16,
      75
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    52,    53,    54,    55,    56,    51,    57,    57,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    66,    65,    67,    65,    68,    68,    69,
      70,    70,    71,    71,    72,    73,    73,    74,    74,    75,
      75,    75,    75,    76,    77,    75,    78,    79,    75,    80,
      80,    81,    81,    82,    82,    82,    82,    83,    83,    83,
      83,    83,    84,    85,    85,    85,    85,    85,    85,    86,
      86,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,     0,     0,     0,    13,     6,     0,
       1,     1,     6,     0,     1,     3,     1,     8,     1,     1,
       3,     0,     3,     0,     7,     0,     5,     1,     0,     3,
       1,     3,     4,     3,     3,     1,     0,     1,     3,     3,
       1,     1,     1,     0,     0,     8,     0,     0,     6,     1,
       3,     1,     4,     1,     4,     4,     4,     1,     2,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     4,     6,     4,     1,     1,     3,     3,     3,
       3,     3,     3,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 75 "parser.y"
                                            { generateHeader(); free((yyvsp[-1].sval)); }
#line 1291 "parser.tab.c"
    break;

  case 3: /* $@2: %empty  */
#line 76 "parser.y"
                               { generateNewLine(); }
#line 1297 "parser.tab.c"
    break;

  case 4: /* $@3: %empty  */
#line 77 "parser.y"
                             { generateNewLine(); }
#line 1303 "parser.tab.c"
    break;

  case 5: /* $@4: %empty  */
#line 78 "parser.y"
                                  { generateMain(); }
#line 1309 "parser.tab.c"
    break;

  case 6: /* $@5: %empty  */
#line 79 "parser.y"
                                       { generateFunctionEnd(NULL); }
#line 1315 "parser.tab.c"
    break;

  case 8: /* ConstDecl: ConstDecl CONST IDENTIFIER RELOPEQ NumericValue ';'  */
#line 83 "parser.y"
                                                                          { constDeclarationCheck((yyvsp[-3].sval), (yyvsp[-1].number).returnType, (yyvsp[-1].number).ival, (yyvsp[-1].number).dval); }
#line 1321 "parser.tab.c"
    break;

  case 10: /* NumericValue: INTNUMBER  */
#line 87 "parser.y"
                                { (yyval.number).returnType = RETURN_TYPE_INTEGER; (yyval.number).ival = (yyvsp[0].ival); }
#line 1327 "parser.tab.c"
    break;

  case 11: /* NumericValue: REALNUMBER  */
#line 88 "parser.y"
                                { (yyval.number).returnType = RETURN_TYPE_REAL; (yyval.number).dval = (yyvsp[0].dval); }
#line 1333 "parser.tab.c"
    break;

  case 12: /* VarDecl: VarDecl VAR IdentifierList ':' TypeSpec ';'  */
#line 91 "parser.y"
                                                                  { addIdentifiersToSymTable((yyvsp[-3].identifiers), transformTypeToVar((yyvsp[-1].typeSpec).type), (yyvsp[-1].typeSpec).type, (yyvsp[-1].typeSpec).returnType, (yyvsp[-1].typeSpec).lowerBound, (yyvsp[-1].typeSpec).upperBound); }
#line 1339 "parser.tab.c"
    break;

  case 14: /* IdentifierList: IDENTIFIER  */
#line 95 "parser.y"
                                                    { (yyval.identifiers) = createIdentifiersStruct((yyvsp[0].sval)); }
#line 1345 "parser.tab.c"
    break;

  case 15: /* IdentifierList: IdentifierList ',' IDENTIFIER  */
#line 96 "parser.y"
                                                    { (yyval.identifiers) = (yyvsp[-2].identifiers); addIdentifier((yyval.identifiers), (yyvsp[0].sval)); }
#line 1351 "parser.tab.c"
    break;

  case 16: /* TypeSpec: BasicType  */
#line 99 "parser.y"
                                                                          { (yyval.typeSpec).type = TYPE_VALUE; (yyval.typeSpec).returnType = (yyvsp[0].returntype); (yyval.typeSpec).lowerBound = 0; (yyval.typeSpec).upperBound = 0; }
#line 1357 "parser.tab.c"
    break;

  case 17: /* TypeSpec: ARRAY '[' INTNUMBER RANGE INTNUMBER ']' OF BasicType  */
#line 100 "parser.y"
                                                                          { arrayTypeCheck((yyvsp[-5].ival), (yyvsp[-3].ival)); (yyval.typeSpec).type = TYPE_ARRAY; (yyval.typeSpec).returnType = (yyvsp[0].returntype); (yyval.typeSpec).lowerBound = (yyvsp[-5].ival); (yyval.typeSpec).upperBound = (yyvsp[-3].ival); }
#line 1363 "parser.tab.c"
    break;

  case 18: /* BasicType: INTEGER  */
#line 103 "parser.y"
                              { (yyval.returntype) = RETURN_TYPE_INTEGER; }
#line 1369 "parser.tab.c"
    break;

  case 19: /* BasicType: REAL  */
#line 104 "parser.y"
                              { (yyval.returntype) = RETURN_TYPE_REAL; }
#line 1375 "parser.tab.c"
    break;

  case 20: /* FuncProcDecl: FuncProcDecl SubProgDecl ';'  */
#line 107 "parser.y"
                                                  { generateNewLine(); }
#line 1381 "parser.tab.c"
    break;

  case 22: /* SubProgDecl: SubProgHeading VarDecl CompoundStatement  */
#line 111 "parser.y"
                                                              { returnMissingCheck(); exitScope(); }
#line 1387 "parser.tab.c"
    break;

  case 23: /* $@6: %empty  */
#line 114 "parser.y"
                                         { enterScope(); }
#line 1393 "parser.tab.c"
    break;

  case 24: /* SubProgHeading: FUNCTION IDENTIFIER $@6 Parameters ':' BasicType ';'  */
#line 114 "parser.y"
                                                                                        { functionDeclarationCheck((yyvsp[-5].sval), (yyvsp[-3].parameters), (yyvsp[-1].returntype)); }
#line 1399 "parser.tab.c"
    break;

  case 25: /* $@7: %empty  */
#line 115 "parser.y"
                                          { enterScope(); }
#line 1405 "parser.tab.c"
    break;

  case 26: /* SubProgHeading: PROCEDURE IDENTIFIER $@7 PossibleParameters ';'  */
#line 115 "parser.y"
                                                                                        { procedureDeclarationCheck((yyvsp[-3].sval), (yyvsp[-1].parameters)); }
#line 1411 "parser.tab.c"
    break;

  case 27: /* PossibleParameters: Parameters  */
#line 118 "parser.y"
                                            { (yyval.parameters) = (yyvsp[0].parameters); }
#line 1417 "parser.tab.c"
    break;

  case 28: /* PossibleParameters: %empty  */
#line 119 "parser.y"
                                            { (yyval.parameters) = NULL; }
#line 1423 "parser.tab.c"
    break;

  case 29: /* Parameters: '(' ParameterList ')'  */
#line 122 "parser.y"
                                            { (yyval.parameters) = (yyvsp[-1].parameters); }
#line 1429 "parser.tab.c"
    break;

  case 30: /* ParameterList: ParamList  */
#line 125 "parser.y"
                                                  { (yyval.parameters) = (yyvsp[0].parameters); }
#line 1435 "parser.tab.c"
    break;

  case 31: /* ParameterList: ParameterList ';' ParamList  */
#line 126 "parser.y"
                                                  { (yyval.parameters) = (yyvsp[-2].parameters); addParameterList((yyval.parameters), (yyvsp[0].parameters)); }
#line 1441 "parser.tab.c"
    break;

  case 32: /* ParamList: VAR IdentifierList ':' TypeSpec  */
#line 129 "parser.y"
                                                      { (yyval.parameters) = createParametersStruct((yyvsp[-2].identifiers), transformTypeToVar((yyvsp[0].typeSpec).type), (yyvsp[0].typeSpec).returnType, (yyvsp[0].typeSpec).lowerBound, (yyvsp[0].typeSpec).upperBound); }
#line 1447 "parser.tab.c"
    break;

  case 33: /* ParamList: IdentifierList ':' TypeSpec  */
#line 130 "parser.y"
                                                      { (yyval.parameters) = createParametersStruct((yyvsp[-2].identifiers), (yyvsp[0].typeSpec).type, (yyvsp[0].typeSpec).returnType, (yyvsp[0].typeSpec).lowerBound, (yyvsp[0].typeSpec).upperBound); }
#line 1453 "parser.tab.c"
    break;

  case 39: /* Statement: Lhs ASSIGN ArithExpr  */
#line 144 "parser.y"
                                                            { statementCheck((yyvsp[-2].lhs), (yyvsp[0].arithStruct)); }
#line 1459 "parser.tab.c"
    break;

  case 43: /* @8: %empty  */
#line 148 "parser.y"
                                   { (yyval.ival) = generateIfLabel((yyvsp[-1].sval)); }
#line 1465 "parser.tab.c"
    break;

  case 44: /* @9: %empty  */
#line 148 "parser.y"
                                                                                 { (yyval.ival) = generateElseLabel((yyvsp[-1].ival)); }
#line 1471 "parser.tab.c"
    break;

  case 45: /* Statement: IF Guard THEN @8 Statement @9 ELSE Statement  */
#line 148 "parser.y"
                                                                                                                                            { generateLabel((yyvsp[-2].ival)); }
#line 1477 "parser.tab.c"
    break;

  case 46: /* @10: %empty  */
#line 149 "parser.y"
                           { (yyval.ival) = generateWhileLabel(); }
#line 1483 "parser.tab.c"
    break;

  case 47: /* $@11: %empty  */
#line 149 "parser.y"
                                                                      { generateWhileLabelCheck((yyvsp[0].sval), (yyvsp[-1].ival) + 1); }
#line 1489 "parser.tab.c"
    break;

  case 48: /* Statement: WHILE @10 Guard $@11 DO Statement  */
#line 149 "parser.y"
                                                                                                                                  { generateWhileLabelFinal((yyvsp[-4].ival)); }
#line 1495 "parser.tab.c"
    break;

  case 49: /* LhsList: Lhs  */
#line 152 "parser.y"
                                                  { (yyval.lhsList) = createLhsListStruct((yyvsp[0].lhs)); }
#line 1501 "parser.tab.c"
    break;

  case 50: /* LhsList: LhsList ',' Lhs  */
#line 153 "parser.y"
                                                  { (yyval.lhsList) = (yyvsp[-2].lhsList); addLhs((yyval.lhsList), (yyvsp[0].lhs)); }
#line 1507 "parser.tab.c"
    break;

  case 51: /* Lhs: IDENTIFIER  */
#line 155 "parser.y"
                                                  { lhsCheck((yyvsp[0].sval)); (yyval.lhs).identifier = (yyvsp[0].sval); (yyval.lhs).temp = NULL; }
#line 1513 "parser.tab.c"
    break;

  case 52: /* Lhs: IDENTIFIER '[' ArithExpr ']'  */
#line 156 "parser.y"
                                                  { lhsArrayCheck((yyvsp[-3].sval), (yyvsp[-1].arithStruct)); (yyval.lhs).identifier = (yyvsp[-3].sval); (yyval.lhs).temp = (yyvsp[-1].arithStruct).temp; }
#line 1519 "parser.tab.c"
    break;

  case 53: /* ProcedureCall: IDENTIFIER  */
#line 159 "parser.y"
                                                      { procedureCallCheck((yyvsp[0].sval)); }
#line 1525 "parser.tab.c"
    break;

  case 54: /* ProcedureCall: IDENTIFIER '(' ArithExprList ')'  */
#line 160 "parser.y"
                                                      { procedureCallWithParametersCheck((yyvsp[-3].sval), (yyvsp[-1].arithExprs)); }
#line 1531 "parser.tab.c"
    break;

  case 55: /* ProcedureCall: READLN '(' LhsList ')'  */
#line 161 "parser.y"
                                                      { readlnCheck((yyvsp[-1].lhsList)); }
#line 1537 "parser.tab.c"
    break;

  case 56: /* ProcedureCall: WRITELN '(' ArithExprList ')'  */
#line 162 "parser.y"
                                                      { writelnCheck((yyvsp[-1].arithExprs)); }
#line 1543 "parser.tab.c"
    break;

  case 57: /* Guard: BoolAtom  */
#line 165 "parser.y"
                                            { (yyval.sval) = (yyvsp[0].sval); }
#line 1549 "parser.tab.c"
    break;

  case 58: /* Guard: NOT Guard  */
#line 166 "parser.y"
                                            { (yyval.sval) = generateNot((yyvsp[0].sval)); }
#line 1555 "parser.tab.c"
    break;

  case 59: /* Guard: Guard OR Guard  */
#line 167 "parser.y"
                                            { (yyval.sval) = generateOr((yyvsp[-2].sval), (yyvsp[0].sval)); }
#line 1561 "parser.tab.c"
    break;

  case 60: /* Guard: Guard AND Guard  */
#line 168 "parser.y"
                                            { (yyval.sval) = generateAnd((yyvsp[-2].sval), (yyvsp[0].sval)); }
#line 1567 "parser.tab.c"
    break;

  case 61: /* Guard: '(' Guard ')'  */
#line 169 "parser.y"
                                            { (yyval.sval) = (yyvsp[-1].sval); }
#line 1573 "parser.tab.c"
    break;

  case 62: /* BoolAtom: ArithExpr Relop ArithExpr  */
#line 172 "parser.y"
                                                                  { (yyval.sval) = boolCheck((yyvsp[-2].arithStruct), (yyvsp[-1].sval), (yyvsp[0].arithStruct)); }
#line 1579 "parser.tab.c"
    break;

  case 63: /* Relop: RELOPLT  */
#line 175 "parser.y"
                              { char *operator = malloc(sizeof(char) * 2); strcpy(operator, "<"); (yyval.sval) = operator; }
#line 1585 "parser.tab.c"
    break;

  case 64: /* Relop: RELOPLEQ  */
#line 176 "parser.y"
                              { char *operator = malloc(sizeof(char) * 3); strcpy(operator, "<="); (yyval.sval) = operator; }
#line 1591 "parser.tab.c"
    break;

  case 65: /* Relop: RELOPEQ  */
#line 177 "parser.y"
                              { char *operator = malloc(sizeof(char) * 3); strcpy(operator, "=="); (yyval.sval) = operator; }
#line 1597 "parser.tab.c"
    break;

  case 66: /* Relop: RELOPNEQ  */
#line 178 "parser.y"
                              { char *operator = malloc(sizeof(char) * 3); strcpy(operator, "!="); (yyval.sval) = operator; }
#line 1603 "parser.tab.c"
    break;

  case 67: /* Relop: RELOPGEQ  */
#line 179 "parser.y"
                              { char *operator = malloc(sizeof(char) * 3); strcpy(operator, ">="); (yyval.sval) = operator; }
#line 1609 "parser.tab.c"
    break;

  case 68: /* Relop: RELOPGT  */
#line 180 "parser.y"
                              { char *operator = malloc(sizeof(char) * 2); strcpy(operator, ">"); (yyval.sval) = operator; }
#line 1615 "parser.tab.c"
    break;

  case 69: /* ArithExprList: ArithExpr  */
#line 183 "parser.y"
                                                                  { (yyval.arithExprs) = createArithExprsStruct((yyvsp[0].arithStruct).type, (yyvsp[0].arithStruct).returnType, (yyvsp[0].arithStruct).temp, (yyvsp[0].arithStruct).lowerBound, (yyvsp[0].arithStruct).upperBound, (yyvsp[0].arithStruct).arrayElement); }
#line 1621 "parser.tab.c"
    break;

  case 70: /* ArithExprList: ArithExprList ',' ArithExpr  */
#line 184 "parser.y"
                                                                  { (yyval.arithExprs) = (yyvsp[-2].arithExprs); addArithExpr((yyval.arithExprs), (yyvsp[0].arithStruct).type, (yyvsp[0].arithStruct).returnType, (yyvsp[0].arithStruct).temp, (yyvsp[0].arithStruct).lowerBound, (yyvsp[0].arithStruct).upperBound, (yyvsp[0].arithStruct).arrayElement); }
#line 1627 "parser.tab.c"
    break;

  case 71: /* ArithExpr: IDENTIFIER  */
#line 187 "parser.y"
                                                                  { (yyval.arithStruct) = arithIdentifierCheck((yyvsp[0].sval)); }
#line 1633 "parser.tab.c"
    break;

  case 72: /* ArithExpr: IDENTIFIER '[' ArithExpr ']'  */
#line 188 "parser.y"
                                                                  { (yyval.arithStruct) = arithArrayElementCheck((yyvsp[-3].sval), (yyvsp[-1].arithStruct)); }
#line 1639 "parser.tab.c"
    break;

  case 73: /* ArithExpr: IDENTIFIER '[' ArithExpr RANGE ArithExpr ']'  */
#line 189 "parser.y"
                                                                  { (yyval.arithStruct) = arithArrayTrimCheck((yyvsp[-5].sval), (yyvsp[-3].arithStruct), (yyvsp[-1].arithStruct)); }
#line 1645 "parser.tab.c"
    break;

  case 74: /* ArithExpr: IDENTIFIER '(' ArithExprList ')'  */
#line 190 "parser.y"
                                                                  { (yyval.arithStruct) = arithFunctionCheck((yyvsp[-3].sval), (yyvsp[-1].arithExprs)); }
#line 1651 "parser.tab.c"
    break;

  case 75: /* ArithExpr: INTNUMBER  */
#line 191 "parser.y"
                                                                  { (yyval.arithStruct).returnType = RETURN_TYPE_INTEGER; (yyval.arithStruct).type = TYPE_CONST; (yyval.arithStruct).ival = (yyvsp[0].ival); (yyval.arithStruct).temp = generateInteger((yyvsp[0].ival)); }
#line 1657 "parser.tab.c"
    break;

  case 76: /* ArithExpr: REALNUMBER  */
#line 192 "parser.y"
                                                                  { (yyval.arithStruct).returnType = RETURN_TYPE_REAL; (yyval.arithStruct).type = TYPE_CONST; (yyval.arithStruct).dval = (yyvsp[0].dval); (yyval.arithStruct).temp = generateReal((yyvsp[0].dval)); }
#line 1663 "parser.tab.c"
    break;

  case 77: /* ArithExpr: ArithExpr '+' ArithExpr  */
#line 193 "parser.y"
                                                                  { (yyval.arithStruct) = arithOperatorCheck((yyvsp[-2].arithStruct), (yyvsp[0].arithStruct), '+'); }
#line 1669 "parser.tab.c"
    break;

  case 78: /* ArithExpr: ArithExpr '-' ArithExpr  */
#line 194 "parser.y"
                                                                  { (yyval.arithStruct) = arithOperatorCheck((yyvsp[-2].arithStruct), (yyvsp[0].arithStruct), '-'); }
#line 1675 "parser.tab.c"
    break;

  case 79: /* ArithExpr: ArithExpr '*' ArithExpr  */
#line 195 "parser.y"
                                                                  { (yyval.arithStruct) = arithOperatorCheck((yyvsp[-2].arithStruct), (yyvsp[0].arithStruct), '*'); }
#line 1681 "parser.tab.c"
    break;

  case 80: /* ArithExpr: ArithExpr '/' ArithExpr  */
#line 196 "parser.y"
                                                                  { (yyval.arithStruct) = arithOperatorCheck((yyvsp[-2].arithStruct), (yyvsp[0].arithStruct), '/'); }
#line 1687 "parser.tab.c"
    break;

  case 81: /* ArithExpr: ArithExpr DIV ArithExpr  */
#line 197 "parser.y"
                                                                  { (yyval.arithStruct) = arithOperatorDivModCheck((yyvsp[-2].arithStruct), (yyvsp[0].arithStruct), ':'); }
#line 1693 "parser.tab.c"
    break;

  case 82: /* ArithExpr: ArithExpr MOD ArithExpr  */
#line 198 "parser.y"
                                                                  { (yyval.arithStruct) = arithOperatorDivModCheck((yyvsp[-2].arithStruct), (yyvsp[0].arithStruct), '%'); }
#line 1699 "parser.tab.c"
    break;

  case 83: /* ArithExpr: '-' ArithExpr  */
#line 199 "parser.y"
                                                                  { (yyval.arithStruct) = arithNegationCheck((yyvsp[0].arithStruct)); }
#line 1705 "parser.tab.c"
    break;

  case 84: /* ArithExpr: '(' ArithExpr ')'  */
#line 200 "parser.y"
                                                                  { (yyval.arithStruct) = (yyvsp[-1].arithStruct); }
#line 1711 "parser.tab.c"
    break;


#line 1715 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 203 "parser.y"


void printToken(int token, FILE *f) {
  /* single character tokens */
  if (token < 256) {
    if (token < 33) {
      /* non-printable character */
      fprintf(f, "chr(%d)", token);
    } else {
      fprintf(f, "'%c'", token);
    }
    return;
  }
  /* standard tokens (>255) */
  switch (token) {
    case PROGRAM   : fprintf(f, "PROGRAM"); break;
    case CONST     : fprintf(f, "CONST"); break;
    case IDENTIFIER: fprintf(f, "identifier<%s>", yytext); break;
    case VAR       : fprintf(f, "VAR"); break;
    case ARRAY     : fprintf(f, "ARRAY"); break;
    case RANGE     : fprintf(f, ".."); break;
    case INTNUMBER : fprintf(f, "Integer<%d>", yylval.ival); break;
    case REALNUMBER: fprintf(f, "Real<%lf>", yylval.dval); break;
    case OF        : fprintf(f, "OF"); break;
    case INTEGER   : fprintf(f, "INTEGER"); break;
    case REAL      : fprintf(f, "REAL"); break;
    case FUNCTION  : fprintf(f, "FUNCTION"); break;
    case PROCEDURE : fprintf(f, "PROCEDURE"); break;
    case BEGINTOK  : fprintf(f, "BEGIN"); break;
    case ENDTOK    : fprintf(f, "END"); break;
    case ASSIGN    : fprintf(f, ":="); break;
    case IF        : fprintf(f, "IF"); break;
    case THEN      : fprintf(f, "THEN"); break;
    case ELSE      : fprintf(f, "ELSE"); break;
    case WHILE     : fprintf(f, "WHILE"); break;
    case DO        : fprintf(f, "DO"); break;
    case SKIP      : fprintf(f, "SKIP"); break;
    case READLN    : fprintf(f, "READLN"); break;
    case WRITELN   : fprintf(f, "WRITELN"); break;
  }
}

void freeLexerAndParser() {
  finalizeLexer();
  fclose(input);
  fclose(output);
  // printSymbolTable();
  freeLastFunctionName();
  freeSymbolTable();
}

void error() {
  printf("ERRORS: 1\nWARNINGS: %d\nREJECTED\n", warnings);

  freeLexerAndParser();

  exit(EXIT_SUCCESS);  /* EXIT_SUCCESS because we use Themis */
}

void yyerror (char *msg) {
  showErrorLine();
  fprintf(stderr, "%s (detected at token=", msg);
  printToken(yychar, stderr);
  fprintf(stderr, ").\n");

  error();
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s [pasfile] [outputfile]\n", argv[0]);
    return EXIT_FAILURE;
  }
  
  input = (strcmp(argv[1], "-") == 0) ? stdin : fopen(argv[1], "r");
  if(input == NULL) {
    fprintf(stderr, "Failed to open input file!\n");
    exit(EXIT_FAILURE);
  }

  output = (strcmp(argv[2], "-") == 0) ? stdout : fopen(argv[2], "w");
  if (output == NULL) {
    fprintf(stderr, "Failed to open output file!\n");
    exit(EXIT_FAILURE);
  }

  initLexer(input);
  int result = yyparse();

  // printf("ERRORS: %d\n", 0);
  // printf("WARNINGS: %d\n", warnings);
  // puts(result == 0 ? "ACCEPTED" : "REJECTED");

  freeLexerAndParser();

  return EXIT_SUCCESS;
}
