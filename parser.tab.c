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
#line 11 "parser.y"

#include "symtable.h"
#include "quadruple.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);
extern int line_num;
extern char* yytext;  
extern FILE *yyin;

char* current_function = NULL;


#line 88 "parser.tab.c"

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
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_VOID = 5,                       /* VOID  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_FOR = 9,                        /* FOR  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_REPEAT = 11,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 12,                     /* UNTIL  */
  YYSYMBOL_SWITCH = 13,                    /* SWITCH  */
  YYSYMBOL_CASE = 14,                      /* CASE  */
  YYSYMBOL_DEFAULT = 15,                   /* DEFAULT  */
  YYSYMBOL_CONST = 16,                     /* CONST  */
  YYSYMBOL_IDENTIFIER = 17,                /* IDENTIFIER  */
  YYSYMBOL_INTEGER_NUM = 18,               /* INTEGER_NUM  */
  YYSYMBOL_FLOAT_NUM = 19,                 /* FLOAT_NUM  */
  YYSYMBOL_PLUS = 20,                      /* PLUS  */
  YYSYMBOL_MINUS = 21,                     /* MINUS  */
  YYSYMBOL_MULT = 22,                      /* MULT  */
  YYSYMBOL_DIV = 23,                       /* DIV  */
  YYSYMBOL_ASSIGN = 24,                    /* ASSIGN  */
  YYSYMBOL_EQ = 25,                        /* EQ  */
  YYSYMBOL_NE = 26,                        /* NE  */
  YYSYMBOL_LT = 27,                        /* LT  */
  YYSYMBOL_GT = 28,                        /* GT  */
  YYSYMBOL_LE = 29,                        /* LE  */
  YYSYMBOL_GE = 30,                        /* GE  */
  YYSYMBOL_AND = 31,                       /* AND  */
  YYSYMBOL_OR = 32,                        /* OR  */
  YYSYMBOL_NOT = 33,                       /* NOT  */
  YYSYMBOL_SEMICOLON = 34,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 35,                     /* COMMA  */
  YYSYMBOL_COLON = 36,                     /* COLON  */
  YYSYMBOL_LBRACE = 37,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 38,                    /* RBRACE  */
  YYSYMBOL_LPAREN = 39,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 40,                    /* RPAREN  */
  YYSYMBOL_LEXICAL_ERROR = 41,             /* LEXICAL_ERROR  */
  YYSYMBOL_TRUE = 42,                      /* TRUE  */
  YYSYMBOL_FALSE = 43,                     /* FALSE  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_declaration_list = 46,          /* declaration_list  */
  YYSYMBOL_declaration = 47,               /* declaration  */
  YYSYMBOL_var_type = 48,                  /* var_type  */
  YYSYMBOL_fun_type = 49,                  /* fun_type  */
  YYSYMBOL_var_declaration = 50,           /* var_declaration  */
  YYSYMBOL_fun_declaration = 51,           /* fun_declaration  */
  YYSYMBOL_params = 52,                    /* params  */
  YYSYMBOL_param_list = 53,                /* param_list  */
  YYSYMBOL_param = 54,                     /* param  */
  YYSYMBOL_compound_stmt = 55,             /* compound_stmt  */
  YYSYMBOL_56_1 = 56,                      /* $@1  */
  YYSYMBOL_local_declarations = 57,        /* local_declarations  */
  YYSYMBOL_statement_list = 58,            /* statement_list  */
  YYSYMBOL_statement = 59,                 /* statement  */
  YYSYMBOL_expression_stmt = 60,           /* expression_stmt  */
  YYSYMBOL_selection_stmt = 61,            /* selection_stmt  */
  YYSYMBOL_iteration_stmt = 62,            /* iteration_stmt  */
  YYSYMBOL_return_stmt = 63,               /* return_stmt  */
  YYSYMBOL_switch_stmt = 64,               /* switch_stmt  */
  YYSYMBOL_case_list = 65,                 /* case_list  */
  YYSYMBOL_case_stmt = 66,                 /* case_stmt  */
  YYSYMBOL_default_case = 67,              /* default_case  */
  YYSYMBOL_expression = 68,                /* expression  */
  YYSYMBOL_simple_expr = 69,               /* simple_expr  */
  YYSYMBOL_relop = 70,                     /* relop  */
  YYSYMBOL_additive_expr = 71,             /* additive_expr  */
  YYSYMBOL_term = 72,                      /* term  */
  YYSYMBOL_factor = 73                     /* factor  */
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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   181

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    63,    63,    67,    68,    72,    73,    78,    79,    84,
      88,    93,   107,   123,   132,   144,   145,   146,   150,   154,
     161,   174,   173,   186,   187,   191,   192,   196,   197,   198,
     199,   200,   201,   205,   212,   216,   228,   249,   267,   286,
     303,   307,   315,   326,   340,   341,   345,   354,   363,   394,
     401,   415,   429,   442,   453,   460,   461,   462,   463,   464,
     465,   469,   480,   491,   498,   509,   520,   527,   531,   547,
     562,   569,   576,   583
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "VOID",
  "IF", "ELSE", "WHILE", "FOR", "RETURN", "REPEAT", "UNTIL", "SWITCH",
  "CASE", "DEFAULT", "CONST", "IDENTIFIER", "INTEGER_NUM", "FLOAT_NUM",
  "PLUS", "MINUS", "MULT", "DIV", "ASSIGN", "EQ", "NE", "LT", "GT", "LE",
  "GE", "AND", "OR", "NOT", "SEMICOLON", "COMMA", "COLON", "LBRACE",
  "RBRACE", "LPAREN", "RPAREN", "LEXICAL_ERROR", "TRUE", "FALSE",
  "$accept", "program", "declaration_list", "declaration", "var_type",
  "fun_type", "var_declaration", "fun_declaration", "params", "param_list",
  "param", "compound_stmt", "$@1", "local_declarations", "statement_list",
  "statement", "expression_stmt", "selection_stmt", "iteration_stmt",
  "return_stmt", "switch_stmt", "case_list", "case_stmt", "default_case",
  "expression", "simple_expr", "relop", "additive_expr", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-100)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      63,  -100,  -100,  -100,    61,    25,    63,  -100,    16,    34,
    -100,  -100,    53,  -100,  -100,    -2,    37,    56,    92,  -100,
      55,    55,    92,    -1,  -100,  -100,   109,    92,  -100,  -100,
      70,    43,   129,    66,  -100,  -100,    80,    72,    71,  -100,
      89,    96,    92,    93,    97,    43,    98,  -100,   109,   109,
      30,    30,  -100,  -100,  -100,  -100,  -100,  -100,    30,    30,
      30,  -100,    95,    61,    95,  -100,  -100,  -100,  -100,  -100,
    -100,    66,    66,    75,  -100,  -100,  -100,  -100,  -100,  -100,
    -100,    27,   120,  -100,     2,    22,   100,   101,   102,    74,
      95,   104,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,
    -100,   110,    92,    92,    81,  -100,   111,   134,    92,  -100,
     107,   113,    92,  -100,   121,   122,    44,    44,   127,    92,
     126,   157,  -100,    92,   125,   152,    44,   128,   133,   151,
     -12,  -100,  -100,    44,  -100,   135,   136,  -100,  -100,   132,
    -100,  -100,  -100,  -100,    44,    44
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     7,     8,     9,     0,     0,     2,     4,     0,     0,
       5,     6,     0,     1,     3,     0,     0,     0,     0,    10,
      17,    17,     0,    68,    70,    71,     0,     0,    72,    73,
       0,    49,    54,    63,    66,    16,     0,     0,    15,    19,
       0,     0,     0,     0,    68,    52,     0,    11,     0,     0,
       0,     0,    57,    60,    55,    56,    58,    59,     0,     0,
       0,    20,     0,     0,     0,    12,    48,    69,    67,    50,
      51,    61,    62,    53,    64,    65,    21,    14,    18,    13,
      24,    26,     0,    23,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    22,    28,    25,    27,    29,    30,    31,
      32,     0,     0,     0,     0,    40,     0,     0,     0,    33,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
       0,    35,    37,     0,     0,     0,     0,     0,     0,     0,
       0,    45,    36,     0,    39,     0,     0,    42,    44,     0,
      38,    26,    26,    43,    46,    47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -100,  -100,  -100,   167,     1,  -100,    94,  -100,   153,  -100,
     114,   -48,  -100,  -100,   -39,   -99,    76,  -100,  -100,  -100,
    -100,  -100,    46,  -100,   -18,   -20,  -100,   123,    68,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,    36,     9,    10,    11,    37,    38,
      39,    94,    80,    81,    84,    95,    96,    97,    98,    99,
     100,   130,   131,   139,   101,    31,    58,    32,    33,    34
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      30,     8,   129,   136,    41,    12,    45,     8,    86,    46,
      87,    88,    89,    90,    77,    91,    79,   121,   122,    23,
      24,    25,    18,    42,    66,    13,   137,   132,    69,    70,
       1,     2,    19,    15,   140,    26,    92,    20,    43,    76,
      93,    27,   107,     4,    28,    29,    18,    44,    24,    25,
      86,    16,    87,    88,    89,    90,    19,    91,     1,     2,
      35,    23,    24,    25,     1,     2,     1,     2,     3,    27,
      17,   106,    28,    29,    48,    49,    21,    26,    92,     4,
      22,    76,    82,    27,   110,   111,    28,    29,    59,    60,
     115,    23,    24,    25,   118,    50,    51,    61,    23,    24,
      25,   124,   144,   145,    47,   127,    63,    26,   105,    23,
      24,    25,    62,    27,    26,    92,    28,    29,    71,    72,
      27,    74,    75,    28,    29,    26,    44,    24,    25,    64,
      65,    27,    76,    67,    28,    29,    43,    85,    68,   102,
     103,   104,    26,   108,   109,   113,   114,   116,    27,    50,
      51,    28,    29,   117,    52,    53,    54,    55,    56,    57,
     119,   123,   120,   125,   126,   128,   129,   134,   133,   135,
     143,   141,   142,    14,    40,    83,   138,    78,     0,     0,
     112,    73
};

static const yytype_int16 yycheck[] =
{
      18,     0,    14,    15,    22,     4,    26,     6,     6,    27,
       8,     9,    10,    11,    62,    13,    64,   116,   117,    17,
      18,    19,    24,    24,    42,     0,    38,   126,    48,    49,
       3,     4,    34,    17,   133,    33,    34,    39,    39,    37,
      38,    39,    90,    16,    42,    43,    24,    17,    18,    19,
       6,    17,     8,     9,    10,    11,    34,    13,     3,     4,
       5,    17,    18,    19,     3,     4,     3,     4,     5,    39,
      17,    89,    42,    43,    31,    32,    39,    33,    34,    16,
      24,    37,    81,    39,   102,   103,    42,    43,    22,    23,
     108,    17,    18,    19,   112,    20,    21,    17,    17,    18,
      19,   119,   141,   142,    34,   123,    35,    33,    34,    17,
      18,    19,    40,    39,    33,    34,    42,    43,    50,    51,
      39,    59,    60,    42,    43,    33,    17,    18,    19,    40,
      34,    39,    37,    40,    42,    43,    39,    17,    40,    39,
      39,    39,    33,    39,    34,    34,    12,    40,    39,    20,
      21,    42,    43,    40,    25,    26,    27,    28,    29,    30,
      39,    34,    40,    37,     7,    40,    14,    34,    40,    18,
      38,    36,    36,     6,    21,    81,   130,    63,    -1,    -1,
     104,    58
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    16,    45,    46,    47,    48,    49,
      50,    51,    48,     0,    47,    17,    17,    17,    24,    34,
      39,    39,    24,    17,    18,    19,    33,    39,    42,    43,
      68,    69,    71,    72,    73,     5,    48,    52,    53,    54,
      52,    68,    24,    39,    17,    69,    68,    34,    31,    32,
      20,    21,    25,    26,    27,    28,    29,    30,    70,    22,
      23,    17,    40,    35,    40,    34,    68,    40,    40,    69,
      69,    72,    72,    71,    73,    73,    37,    55,    54,    55,
      56,    57,    48,    50,    58,    17,     6,     8,     9,    10,
      11,    13,    34,    38,    55,    59,    60,    61,    62,    63,
      64,    68,    39,    39,    39,    34,    68,    55,    39,    34,
      68,    68,    60,    34,    12,    68,    40,    40,    68,    39,
      40,    59,    59,    34,    68,    37,     7,    68,    40,    14,
      65,    66,    59,    40,    34,    18,    15,    38,    66,    67,
      59,    36,    36,    38,    58,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    48,    48,    49,
      50,    50,    50,    51,    51,    52,    52,    52,    53,    53,
      54,    56,    55,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    59,    60,    60,    61,    61,    62,    62,    62,
      63,    63,    64,    64,    65,    65,    66,    67,    68,    68,
      69,    69,    69,    69,    69,    70,    70,    70,    70,    70,
      70,    71,    71,    71,    72,    72,    72,    73,    73,    73,
      73,    73,    73,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       3,     5,     6,     6,     6,     1,     1,     0,     3,     1,
       2,     0,     5,     2,     0,     2,     0,     1,     1,     1,
       1,     1,     1,     2,     1,     5,     7,     5,     8,     7,
       2,     3,     7,     8,     2,     1,     4,     3,     3,     1,
       3,     3,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     1,     1,     1
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
  case 7: /* var_type: INT  */
#line 78 "parser.y"
            { (yyval.attr).type = TYPE_INT; (yyval.attr).place = NULL; (yyval.attr).is_label = 0; }
#line 1251 "parser.tab.c"
    break;

  case 8: /* var_type: FLOAT  */
#line 79 "parser.y"
            { (yyval.attr).type = TYPE_FLOAT; (yyval.attr).place = NULL; (yyval.attr).is_label = 0; }
#line 1257 "parser.tab.c"
    break;

  case 9: /* fun_type: VOID  */
#line 84 "parser.y"
            { (yyval.attr).type = TYPE_VOID; (yyval.attr).place = NULL; (yyval.attr).is_label = 0; }
#line 1263 "parser.tab.c"
    break;

  case 10: /* var_declaration: var_type IDENTIFIER SEMICOLON  */
#line 89 "parser.y"
    {
        if (!insert_symbol((yyvsp[-1].str), (yyvsp[-2].attr).type))
            yyerror("Redeclaration of variable");
    }
#line 1272 "parser.tab.c"
    break;

  case 11: /* var_declaration: var_type IDENTIFIER ASSIGN expression SEMICOLON  */
#line 94 "parser.y"
    {
        if (!insert_symbol((yyvsp[-3].str), (yyvsp[-4].attr).type))
            yyerror("Redeclaration of variable");

        if ((yyvsp[-4].attr).type != (yyvsp[-1].attr).type && !((yyvsp[-4].attr).type == TYPE_FLOAT && (yyvsp[-1].attr).type == TYPE_INT))
            yyerror("Type mismatch in initialization");

        mark_initialized((yyvsp[-3].str));
        mark_used((yyvsp[-3].str));
        gen_assign((yyvsp[-1].attr).place, (yyvsp[-3].str));
        
        free_temp_label((yyvsp[-1].attr).place);
    }
#line 1290 "parser.tab.c"
    break;

  case 12: /* var_declaration: CONST var_type IDENTIFIER ASSIGN expression SEMICOLON  */
#line 108 "parser.y"
    {
        if (!insert_const((yyvsp[-3].str), (yyvsp[-4].attr).type))
            yyerror("Redeclaration of constant");

        if ((yyvsp[-4].attr).type != (yyvsp[-1].attr).type && !((yyvsp[-4].attr).type == TYPE_FLOAT && (yyvsp[-1].attr).type == TYPE_INT))
            yyerror("Type mismatch in constant initialization");

        gen_assign((yyvsp[-1].attr).place, (yyvsp[-3].str));
        mark_used((yyvsp[-3].str));
        free_temp_label((yyvsp[-1].attr).place);
    }
#line 1306 "parser.tab.c"
    break;

  case 13: /* fun_declaration: fun_type IDENTIFIER LPAREN params RPAREN compound_stmt  */
#line 124 "parser.y"
    {
        if (!insert_function((yyvsp[-4].str), (yyvsp[-5].attr).type))
            yyerror("Redeclaration of function");

        current_function = strdup((yyvsp[-4].str));
        free(current_function);
        current_function = NULL;
    }
#line 1319 "parser.tab.c"
    break;

  case 14: /* fun_declaration: var_type IDENTIFIER LPAREN params RPAREN compound_stmt  */
#line 133 "parser.y"
    {
        if (!insert_function((yyvsp[-4].str), (yyvsp[-5].attr).type))
            yyerror("Redeclaration of function");

        current_function = strdup((yyvsp[-4].str));
        free(current_function);
        current_function = NULL;
    }
#line 1332 "parser.tab.c"
    break;

  case 16: /* params: VOID  */
#line 145 "parser.y"
           { (yyval.num) = 0; }
#line 1338 "parser.tab.c"
    break;

  case 17: /* params: %empty  */
#line 146 "parser.y"
      { (yyval.num) = 0; }
#line 1344 "parser.tab.c"
    break;

  case 18: /* param_list: param_list COMMA param  */
#line 151 "parser.y"
    {
        (yyval.num) = (yyvsp[-2].num) + 1;
    }
#line 1352 "parser.tab.c"
    break;

  case 19: /* param_list: param  */
#line 155 "parser.y"
    {
        (yyval.num) = 1;
    }
#line 1360 "parser.tab.c"
    break;

  case 20: /* param: var_type IDENTIFIER  */
#line 162 "parser.y"
    {
        insert_symbol((yyvsp[0].str), (yyvsp[-1].attr).type);
        mark_initialized((yyvsp[0].str));

        if (current_function) {
            add_function_param(current_function, (yyvsp[0].str), (yyvsp[-1].attr).type);
        }
    }
#line 1373 "parser.tab.c"
    break;

  case 21: /* $@1: %empty  */
#line 174 "parser.y"
    {
        enter_scope();
    }
#line 1381 "parser.tab.c"
    break;

  case 22: /* compound_stmt: LBRACE $@1 local_declarations statement_list RBRACE  */
#line 179 "parser.y"
    {
        check_unused_variables();
        exit_scope();
    }
#line 1390 "parser.tab.c"
    break;

  case 33: /* expression_stmt: expression SEMICOLON  */
#line 206 "parser.y"
    {
        /* Free temporary if expression created one */
        if ((yyvsp[-1].attr).place && strncmp((yyvsp[-1].attr).place, "t", 1) == 0) {
            free_temp_label((yyvsp[-1].attr).place);
        }
    }
#line 1401 "parser.tab.c"
    break;

  case 35: /* selection_stmt: IF LPAREN expression RPAREN statement  */
#line 217 "parser.y"
    {
        if ((yyvsp[-2].attr).type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* end_label = new_label();
        gen_jump_false((yyvsp[-2].attr).place, end_label);
        
        gen_label(end_label);
        free_temp_label(end_label);
        free_temp_label((yyvsp[-2].attr).place);
    }
#line 1417 "parser.tab.c"
    break;

  case 36: /* selection_stmt: IF LPAREN expression RPAREN statement ELSE statement  */
#line 229 "parser.y"
    {
        if ((yyvsp[-4].attr).type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* else_label = new_label();
        char* end_label = new_label();
        
        gen_jump_false((yyvsp[-4].attr).place, else_label);
        
        gen_jump(end_label);
        gen_label(else_label);
        
        gen_label(end_label);
        free_temp_label(else_label);
        free_temp_label(end_label);
        free_temp_label((yyvsp[-4].attr).place);
    }
#line 1439 "parser.tab.c"
    break;

  case 37: /* iteration_stmt: WHILE LPAREN expression RPAREN statement  */
#line 250 "parser.y"
    {
        if ((yyvsp[-2].attr).type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* start_label = new_label();
        char* end_label = new_label();
        
        gen_label(start_label);
        gen_jump_false((yyvsp[-2].attr).place, end_label);
        
        gen_jump(start_label);
        gen_label(end_label);
        
        free_temp_label(start_label);
        free_temp_label(end_label);
        free_temp_label((yyvsp[-2].attr).place);
    }
#line 1461 "parser.tab.c"
    break;

  case 38: /* iteration_stmt: FOR LPAREN expression_stmt expression SEMICOLON expression RPAREN statement  */
#line 268 "parser.y"
    {
        if ((yyvsp[-4].attr).type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* start_label = new_label();
        char* end_label = new_label();
        
        gen_label(start_label);
        gen_jump_false((yyvsp[-4].attr).place, end_label);
        
        gen_jump(start_label);
        gen_label(end_label);
        
        free_temp_label(start_label);
        free_temp_label(end_label);
        free_temp_label((yyvsp[-4].attr).place);
        free_temp_label((yyvsp[-2].attr).place);
    }
#line 1484 "parser.tab.c"
    break;

  case 39: /* iteration_stmt: REPEAT compound_stmt UNTIL LPAREN expression RPAREN SEMICOLON  */
#line 287 "parser.y"
    {
        if ((yyvsp[-2].attr).type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* start_label = new_label();
        
        gen_label(start_label);
        
        gen_jump_false((yyvsp[-2].attr).place, start_label);
        
        free_temp_label(start_label);
        free_temp_label((yyvsp[-2].attr).place);
    }
#line 1502 "parser.tab.c"
    break;

  case 40: /* return_stmt: RETURN SEMICOLON  */
#line 304 "parser.y"
    {
        gen_return("");
    }
#line 1510 "parser.tab.c"
    break;

  case 41: /* return_stmt: RETURN expression SEMICOLON  */
#line 308 "parser.y"
    {
        gen_return((yyvsp[-1].attr).place);
        free_temp_label((yyvsp[-1].attr).place);
    }
#line 1519 "parser.tab.c"
    break;

  case 42: /* switch_stmt: SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE  */
#line 316 "parser.y"
    {
        if ((yyvsp[-4].attr).type != TYPE_INT)
            yyerror("Switch expression must be integer");
        
        char* end_label = new_label();
        gen_label(end_label);
        
        free_temp_label(end_label);
        free_temp_label((yyvsp[-4].attr).place);
    }
#line 1534 "parser.tab.c"
    break;

  case 43: /* switch_stmt: SWITCH LPAREN expression RPAREN LBRACE case_list default_case RBRACE  */
#line 327 "parser.y"
    {
        if ((yyvsp[-5].attr).type != TYPE_INT)
            yyerror("Switch expression must be integer");
        
        char* end_label = new_label();
        gen_label(end_label);
        
        free_temp_label(end_label);
        free_temp_label((yyvsp[-5].attr).place);
    }
#line 1549 "parser.tab.c"
    break;

  case 46: /* case_stmt: CASE INTEGER_NUM COLON statement_list  */
#line 346 "parser.y"
    {
        char* case_label = new_label();
        gen_label(case_label);
        free_temp_label(case_label);
    }
#line 1559 "parser.tab.c"
    break;

  case 47: /* default_case: DEFAULT COLON statement_list  */
#line 355 "parser.y"
    {
        char* default_label = new_label();
        gen_label(default_label);
        free_temp_label(default_label);
    }
#line 1569 "parser.tab.c"
    break;

  case 48: /* expression: IDENTIFIER ASSIGN expression  */
#line 364 "parser.y"
    {
        if (!is_declared((yyvsp[-2].str))){
            yyerror("Assignment to undeclared variable");
            YYERROR;
        }else if(!is_accessible((yyvsp[-2].str))){
            yyerror("Variable not accessible in current scope");
            YYERROR;
        }
        if (is_const((yyvsp[-2].str))){
            yyerror("Cannot assign to constant");
            YYERROR;
        }
        
        if (get_type((yyvsp[-2].str)) != (yyvsp[0].attr).type && 
            !(get_type((yyvsp[-2].str)) == TYPE_FLOAT && (yyvsp[0].attr).type == TYPE_INT)){
                yyerror("Type mismatch in assignment");
                YYERROR;
            }
            
        
        gen_assign((yyvsp[0].attr).place, (yyvsp[-2].str));
        mark_initialized((yyvsp[-2].str));
        mark_used((yyvsp[-2].str)); 
        
        (yyval.attr).place = strdup((yyvsp[-2].str));
        (yyval.attr).type = get_type((yyvsp[-2].str));
        (yyval.attr).is_label = 0;
        
        free_temp_label((yyvsp[0].attr).place);
    }
#line 1604 "parser.tab.c"
    break;

  case 49: /* expression: simple_expr  */
#line 395 "parser.y"
    {
        (yyval.attr) = (yyvsp[0].attr);
    }
#line 1612 "parser.tab.c"
    break;

  case 50: /* simple_expr: simple_expr AND simple_expr  */
#line 402 "parser.y"
    {
        if ((yyvsp[-2].attr).type != TYPE_INT || (yyvsp[0].attr).type != TYPE_INT)
            yyerror("Logical AND requires boolean/int operands");
        
        (yyval.attr).place = new_temp();
        (yyval.attr).type = TYPE_INT;
        (yyval.attr).is_label = 0;
        
        gen_quad("AND", (yyvsp[-2].attr).place, (yyvsp[0].attr).place, (yyval.attr).place);
        
        free_temp_label((yyvsp[-2].attr).place);
        free_temp_label((yyvsp[0].attr).place);
    }
#line 1630 "parser.tab.c"
    break;

  case 51: /* simple_expr: simple_expr OR simple_expr  */
#line 416 "parser.y"
    {
        if ((yyvsp[-2].attr).type != TYPE_INT || (yyvsp[0].attr).type != TYPE_INT)
            yyerror("Logical OR requires boolean/int operands");
        
        (yyval.attr).place = new_temp();
        (yyval.attr).type = TYPE_INT;
        (yyval.attr).is_label = 0;
        
        gen_quad("OR", (yyvsp[-2].attr).place, (yyvsp[0].attr).place, (yyval.attr).place);
        
        free_temp_label((yyvsp[-2].attr).place);
        free_temp_label((yyvsp[0].attr).place);
    }
#line 1648 "parser.tab.c"
    break;

  case 52: /* simple_expr: NOT simple_expr  */
#line 430 "parser.y"
    {
        if ((yyvsp[0].attr).type != TYPE_INT)
            yyerror("Logical NOT requires boolean/int operand");
        
        (yyval.attr).place = new_temp();
        (yyval.attr).type = TYPE_INT;
        (yyval.attr).is_label = 0;
        
        gen_quad("NOT", (yyvsp[0].attr).place, "", (yyval.attr).place);
        
        free_temp_label((yyvsp[0].attr).place);
    }
#line 1665 "parser.tab.c"
    break;

  case 53: /* simple_expr: additive_expr relop additive_expr  */
#line 443 "parser.y"
    {
        (yyval.attr).place = new_temp();
        (yyval.attr).type = TYPE_INT;
        (yyval.attr).is_label = 0;
        
        gen_quad((yyvsp[-1].str), (yyvsp[-2].attr).place, (yyvsp[0].attr).place, (yyval.attr).place);
        
        free_temp_label((yyvsp[-2].attr).place);
        free_temp_label((yyvsp[0].attr).place);
    }
#line 1680 "parser.tab.c"
    break;

  case 54: /* simple_expr: additive_expr  */
#line 454 "parser.y"
    {
        (yyval.attr) = (yyvsp[0].attr);
    }
#line 1688 "parser.tab.c"
    break;

  case 55: /* relop: LT  */
#line 460 "parser.y"
       { (yyval.str) = "<"; }
#line 1694 "parser.tab.c"
    break;

  case 56: /* relop: GT  */
#line 461 "parser.y"
         { (yyval.str) = ">"; }
#line 1700 "parser.tab.c"
    break;

  case 57: /* relop: EQ  */
#line 462 "parser.y"
         { (yyval.str) = "=="; }
#line 1706 "parser.tab.c"
    break;

  case 58: /* relop: LE  */
#line 463 "parser.y"
         { (yyval.str) = "<="; }
#line 1712 "parser.tab.c"
    break;

  case 59: /* relop: GE  */
#line 464 "parser.y"
         { (yyval.str) = ">="; }
#line 1718 "parser.tab.c"
    break;

  case 60: /* relop: NE  */
#line 465 "parser.y"
         { (yyval.str) = "!="; }
#line 1724 "parser.tab.c"
    break;

  case 61: /* additive_expr: additive_expr PLUS term  */
#line 470 "parser.y"
    {
        (yyval.attr).place = new_temp();
        (yyval.attr).type = ((yyvsp[-2].attr).type == TYPE_FLOAT || (yyvsp[0].attr).type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        (yyval.attr).is_label = 0;
        
        gen_add((yyvsp[-2].attr).place, (yyvsp[0].attr).place, (yyval.attr).place);
        
        free_temp_label((yyvsp[-2].attr).place);
        free_temp_label((yyvsp[0].attr).place);
    }
#line 1739 "parser.tab.c"
    break;

  case 62: /* additive_expr: additive_expr MINUS term  */
#line 481 "parser.y"
    {
        (yyval.attr).place = new_temp();
        (yyval.attr).type = ((yyvsp[-2].attr).type == TYPE_FLOAT || (yyvsp[0].attr).type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        (yyval.attr).is_label = 0;
        
        gen_sub((yyvsp[-2].attr).place, (yyvsp[0].attr).place, (yyval.attr).place);
        
        free_temp_label((yyvsp[-2].attr).place);
        free_temp_label((yyvsp[0].attr).place);
    }
#line 1754 "parser.tab.c"
    break;

  case 63: /* additive_expr: term  */
#line 492 "parser.y"
    {
        (yyval.attr) = (yyvsp[0].attr);
    }
#line 1762 "parser.tab.c"
    break;

  case 64: /* term: term MULT factor  */
#line 499 "parser.y"
    {
        (yyval.attr).place = new_temp();
        (yyval.attr).type = ((yyvsp[-2].attr).type == TYPE_FLOAT || (yyvsp[0].attr).type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        (yyval.attr).is_label = 0;
        
        gen_mult((yyvsp[-2].attr).place, (yyvsp[0].attr).place, (yyval.attr).place);
        
        free_temp_label((yyvsp[-2].attr).place);
        free_temp_label((yyvsp[0].attr).place);
    }
#line 1777 "parser.tab.c"
    break;

  case 65: /* term: term DIV factor  */
#line 510 "parser.y"
    {
        (yyval.attr).place = new_temp();
        (yyval.attr).type = ((yyvsp[-2].attr).type == TYPE_FLOAT || (yyvsp[0].attr).type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        (yyval.attr).is_label = 0;
        
        gen_div((yyvsp[-2].attr).place, (yyvsp[0].attr).place, (yyval.attr).place);
        
        free_temp_label((yyvsp[-2].attr).place);
        free_temp_label((yyvsp[0].attr).place);
    }
#line 1792 "parser.tab.c"
    break;

  case 66: /* term: factor  */
#line 521 "parser.y"
    {
        (yyval.attr) = (yyvsp[0].attr);
    }
#line 1800 "parser.tab.c"
    break;

  case 67: /* factor: LPAREN expression RPAREN  */
#line 528 "parser.y"
    {
        (yyval.attr) = (yyvsp[-1].attr);
    }
#line 1808 "parser.tab.c"
    break;

  case 68: /* factor: IDENTIFIER  */
#line 532 "parser.y"
    {
        if (!is_declared((yyvsp[0].str))){
            yyerror("Variable used before declaration");
        }else if(!is_accessible((yyvsp[0].str))){
            yyerror("Variable not accessible in current scope");
        }

        if (!is_initialized((yyvsp[0].str)))
            yyerror("Variable used before initialization");

        mark_used((yyvsp[0].str));
        (yyval.attr).place = strdup((yyvsp[0].str));
        (yyval.attr).type = get_type((yyvsp[0].str));
        (yyval.attr).is_label = 0;
    }
#line 1828 "parser.tab.c"
    break;

  case 69: /* factor: IDENTIFIER LPAREN RPAREN  */
#line 548 "parser.y"
    {
        if (!is_function((yyvsp[-2].str)))
            yyerror("Call to undeclared function");
        
        int expected_count = get_function_param_count((yyvsp[-2].str));
        if (expected_count != 0)
            yyerror("Wrong number of arguments in function call");
        
        (yyval.attr).place = new_temp();
        (yyval.attr).type = get_function_type((yyvsp[-2].str));
        (yyval.attr).is_label = 0;
        
        gen_call((yyvsp[-2].str), (yyval.attr).place);
    }
#line 1847 "parser.tab.c"
    break;

  case 70: /* factor: INTEGER_NUM  */
#line 563 "parser.y"
    {
        (yyval.attr).place = new_temp();
        (yyval.attr).type = TYPE_INT;
        (yyval.attr).is_label = 0;
        gen_assign((yyvsp[0].str), (yyval.attr).place);
    }
#line 1858 "parser.tab.c"
    break;

  case 71: /* factor: FLOAT_NUM  */
#line 570 "parser.y"
    {
        (yyval.attr).place = new_temp();
        (yyval.attr).type = TYPE_FLOAT;
        (yyval.attr).is_label = 0;
        gen_assign((yyvsp[0].str), (yyval.attr).place);
    }
#line 1869 "parser.tab.c"
    break;

  case 72: /* factor: TRUE  */
#line 577 "parser.y"
    {
        (yyval.attr).place = new_temp();
        (yyval.attr).type = TYPE_INT;
        (yyval.attr).is_label = 0;
        gen_assign("1", (yyval.attr).place);
    }
#line 1880 "parser.tab.c"
    break;

  case 73: /* factor: FALSE  */
#line 584 "parser.y"
    {
        (yyval.attr).place = new_temp();
        (yyval.attr).type = TYPE_INT;
        (yyval.attr).is_label = 0;
        gen_assign("0", (yyval.attr).place);
    }
#line 1891 "parser.tab.c"
    break;


#line 1895 "parser.tab.c"

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

#line 592 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", line_num, s);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        return 1;
    }

    init_symbol_table();
    init_quadruples();

    if (yyparse() == 0) {
        printf("\nParsing completed successfully\n");
        print_symbol_table();
        print_quadruples();
        
        /* Save to file */
        save_quadruples("output.quads");
    }

    fclose(yyin);
    cleanup_symbol_table();
    cleanup_quadruples();
    
    return 0;
}
