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

    /* FUNCTIONS AND IF CONDITIONS DO NOT WORK PROPERLY BECAUSE THERE IS NOT ENOUGH RESOURCES ABOUT HOW TO HANDLE THEM. */
    /* Some changes are made in cfg because of some reduce-reduce and reduce-shift conflicts. */
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <float.h>
    extern FILE *yyin;
    extern char* yytext;
    int yylex();
    void yyerror(char *s);

    struct symbolTableVariable{ /* Helps for creating symbol table. */
        char * name; /* Name of the variable. */
        int line_number; /* Line number where variable is created. */
        float value; /* Value of the variable. */
    }variableTable[100];

    struct Node{ /* Helps for creating abstract syntax tree. */
        char * terminal; /* Name of the terminal. */
        struct Node * child; /* Child node. */ 
        struct Node * sibling; /* Sibling node. */
    }Node;

    struct Node * createNode(struct Node * sibling, struct Node * child, char * name){ /* Creates a node. */
        struct Node * node = (struct Node * ) malloc(sizeof(struct Node)); 
        node->child = child; /* Sets child of the node as child. */
        node->sibling = sibling; /* Sets sibling of the node as sibling. */
        node->terminal = strdup(name); /* Sets terminal name. */
        return node;
    }

    void printAST(struct Node * node, int intend){ /* Prints the abstract syntax tree in pretty way. */
        if(node->sibling != NULL) /* Prints all siblings. */
            printAST(node->sibling, intend);
        for(int i = 0; i < intend; i++)
            printf("__");
        printf("%s\n", node->terminal); /* Prints current terminal. */
        if(node->child != NULL) /* Prints all children. */
            printAST(node->child, intend + 1);
    }

    int count = 0; /* Counter for symbol table. */

    extern int line_number;

    struct Node * head; /* Head of the abstract syntax tree. */

    float lookupVariable(char * name){ /* Looks up for a variable in symbol table. */
        float value = FLT_MAX; /* Sets the value as max float number. */
        for(int i = 0; i < count; i++){
            if(strcmp(name, variableTable[i].name) == 0){ /* If the variable is found in symbol table, gets its value. */
                value = variableTable[i].value;
            }
        }
        return value;
    }

    void addVariable(char * name, float val){ /* Adds a variable to symbol table. Because there is only one type in our language, a variable can be updated via set or defvar.*/
        int index = count;
        for(int i = 0; i < count; i++){ /* Finds the index of the variable if it exists on symbol table. If the variable does not exist on symbol table, adds it to the at the end of the symbol table. */
            if(strcmp(name, variableTable[i].name) == 0){
                index = i;
            }
        }
        variableTable[index].name = strdup(name);
        variableTable[index].line_number = line_number;
        variableTable[index].value = val;
        if(index == count)
            count++;
    }


    void printSymbolTable(){ /* Prints symbol table in pretty way. */
        printf("-----SYMBOL TABLE-----\n");
        printf("%s\t%s\t%s\n", "NAME", "LINE NO", "VALUE");
        for(int i = 0; i < count; i++){
            printf("%s\t%d\t%f\n", variableTable[i].name, variableTable[i].line_number, variableTable[i].value);
        }
    }



#line 155 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    VALUEF = 259,                  /* VALUEF  */
    OP_PLUS = 260,                 /* OP_PLUS  */
    OP_OP = 261,                   /* OP_OP  */
    OP_CP = 262,                   /* OP_CP  */
    OP_DIV = 263,                  /* OP_DIV  */
    OP_MINUS = 264,                /* OP_MINUS  */
    OP_MULT = 265,                 /* OP_MULT  */
    DEFF = 266,                    /* DEFF  */
    KW_NIL = 267,                  /* KW_NIL  */
    KW_WHILE = 268,                /* KW_WHILE  */
    KW_IF = 269,                   /* KW_IF  */
    KW_LOAD = 270,                 /* KW_LOAD  */
    KW_DISP = 271,                 /* KW_DISP  */
    KW_TRUE = 272,                 /* KW_TRUE  */
    KW_FALSE = 273,                /* KW_FALSE  */
    DEFV = 274,                    /* DEFV  */
    OP_GT = 275,                   /* OP_GT  */
    OP_SET = 276,                  /* OP_SET  */
    OP_AND = 277,                  /* OP_AND  */
    OP_OR = 278,                   /* OP_OR  */
    OP_NOT = 279,                  /* OP_NOT  */
    OP_EQ = 280,                   /* OP_EQ  */
    OP_COMMA = 281                 /* OP_COMMA  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define VALUEF 259
#define OP_PLUS 260
#define OP_OP 261
#define OP_CP 262
#define OP_DIV 263
#define OP_MINUS 264
#define OP_MULT 265
#define DEFF 266
#define KW_NIL 267
#define KW_WHILE 268
#define KW_IF 269
#define KW_LOAD 270
#define KW_DISP 271
#define KW_TRUE 272
#define KW_FALSE 273
#define DEFV 274
#define OP_GT 275
#define OP_SET 276
#define OP_AND 277
#define OP_OR 278
#define OP_NOT 279
#define OP_EQ 280
#define OP_COMMA 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 84 "parser.y"

    struct type{
        struct Node * node;
        float fval;
        char * name;
        int boolean;
    }type;

#line 269 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_VALUEF = 4,                     /* VALUEF  */
  YYSYMBOL_OP_PLUS = 5,                    /* OP_PLUS  */
  YYSYMBOL_OP_OP = 6,                      /* OP_OP  */
  YYSYMBOL_OP_CP = 7,                      /* OP_CP  */
  YYSYMBOL_OP_DIV = 8,                     /* OP_DIV  */
  YYSYMBOL_OP_MINUS = 9,                   /* OP_MINUS  */
  YYSYMBOL_OP_MULT = 10,                   /* OP_MULT  */
  YYSYMBOL_DEFF = 11,                      /* DEFF  */
  YYSYMBOL_KW_NIL = 12,                    /* KW_NIL  */
  YYSYMBOL_KW_WHILE = 13,                  /* KW_WHILE  */
  YYSYMBOL_KW_IF = 14,                     /* KW_IF  */
  YYSYMBOL_KW_LOAD = 15,                   /* KW_LOAD  */
  YYSYMBOL_KW_DISP = 16,                   /* KW_DISP  */
  YYSYMBOL_KW_TRUE = 17,                   /* KW_TRUE  */
  YYSYMBOL_KW_FALSE = 18,                  /* KW_FALSE  */
  YYSYMBOL_DEFV = 19,                      /* DEFV  */
  YYSYMBOL_OP_GT = 20,                     /* OP_GT  */
  YYSYMBOL_OP_SET = 21,                    /* OP_SET  */
  YYSYMBOL_OP_AND = 22,                    /* OP_AND  */
  YYSYMBOL_OP_OR = 23,                     /* OP_OR  */
  YYSYMBOL_OP_NOT = 24,                    /* OP_NOT  */
  YYSYMBOL_OP_EQ = 25,                     /* OP_EQ  */
  YYSYMBOL_OP_COMMA = 26,                  /* OP_COMMA  */
  YYSYMBOL_27_n_ = 27,                     /* '\n'  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_start = 29,                     /* start  */
  YYSYMBOL_input = 30,                     /* input  */
  YYSYMBOL_asg = 31,                       /* asg  */
  YYSYMBOL_exp = 32,                       /* exp  */
  YYSYMBOL_explist = 33,                   /* explist  */
  YYSYMBOL_function = 34,                  /* function  */
  YYSYMBOL_set_of_ids = 35,                /* set_of_ids  */
  YYSYMBOL_fcall = 36,                     /* fcall  */
  YYSYMBOL_set_of_exps = 37,               /* set_of_exps  */
  YYSYMBOL_expb = 38                       /* expb  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   109

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  36
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  89

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


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
      27,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    96,    96,    97,    98,   100,   106,   112,   119,   134,
     146,   158,   170,   182,   196,   213,   224,   231,   235,   240,
     248,   257,   275,   276,   280,   286,   295,   306,   309,   313,
     319,   329,   340,   351,   362,   373,   378
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "VALUEF",
  "OP_PLUS", "OP_OP", "OP_CP", "OP_DIV", "OP_MINUS", "OP_MULT", "DEFF",
  "KW_NIL", "KW_WHILE", "KW_IF", "KW_LOAD", "KW_DISP", "KW_TRUE",
  "KW_FALSE", "DEFV", "OP_GT", "OP_SET", "OP_AND", "OP_OR", "OP_NOT",
  "OP_EQ", "OP_COMMA", "'\\n'", "$accept", "start", "input", "asg", "exp",
  "explist", "function", "set_of_ids", "fcall", "set_of_exps", "expb", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-46)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-5)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      31,   -46,   -46,    55,     4,   -17,   -46,   -46,   -46,   -46,
     -46,    94,    94,    74,    94,    94,    94,     8,     3,    11,
      15,    12,    21,   -46,    -1,    82,    94,    26,    94,    94,
      94,    94,    34,    25,   -46,   -46,    35,    94,    94,   -46,
     -46,   -46,    94,    94,   -46,    39,    45,    46,    47,    54,
      94,     3,     3,     3,    94,   101,    35,    61,    63,   -46,
     -46,   -46,   -46,   -46,    59,    65,    94,     3,     3,    66,
      94,    79,   -46,   -46,    78,    35,    87,    92,    95,   -46,
      99,   -46,   -46,   102,   -46,   -46,   -46,   -46,   -46
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    15,    16,     0,     0,     0,    18,     6,     7,     5,
      17,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     0,    27,     0,     0,     0,
       0,     0,     0,     0,    35,    36,     0,     0,     0,    20,
      19,     3,     0,    28,    26,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       9,    12,    10,    11,    23,     0,     0,     0,     0,     0,
       0,     0,    13,     8,    24,     0,     0,     0,     0,    30,
       0,    14,    25,     0,    33,    32,    31,    34,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -46,    18,   -46,   -46,     1,     0,   -46,   -46,   -46,   -46,
     -45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    21,    22,     9,    65,    10,    27,
      36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       8,     7,     1,     2,    23,     3,    67,    68,    69,    33,
      24,    32,    26,    28,    37,    29,    30,    31,    38,    39,
      34,    35,    77,    78,     8,     7,    -4,    43,    40,    45,
      46,    47,    48,    44,     1,     2,    56,     3,    57,    58,
      49,    55,    41,    26,    59,    50,    60,    51,    52,    53,
      54,    66,    61,    62,    63,    70,    71,    64,    11,     2,
      12,    13,    74,    14,    15,    16,    17,    76,    72,    18,
      73,    80,    75,    79,    19,    83,    20,    11,     2,    12,
      13,    82,    14,    15,    16,    42,    81,    12,    18,     0,
      14,    15,    16,    19,    84,    20,    18,     1,     2,    85,
      25,    19,    86,    20,     1,     2,    87,    13,     0,    88
};

static const yytype_int8 yycheck[] =
{
       0,     0,     3,     4,     0,     6,    51,    52,    53,     6,
      27,     3,    11,    12,     3,    14,    15,    16,     3,     7,
      17,    18,    67,    68,    24,    24,    27,    26,     7,    28,
      29,    30,    31,     7,     3,     4,    36,     6,    37,    38,
       6,     6,    24,    42,    43,    20,     7,    22,    23,    24,
      25,    50,     7,     7,     7,    54,    56,     3,     3,     4,
       5,     6,     3,     8,     9,    10,    11,    66,     7,    14,
       7,    70,     7,     7,    19,    75,    21,     3,     4,     5,
       6,     3,     8,     9,    10,     3,     7,     5,    14,    -1,
       8,     9,    10,    19,     7,    21,    14,     3,     4,     7,
       6,    19,     7,    21,     3,     4,     7,     6,    -1,     7
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     6,    29,    30,    31,    32,    33,    34,
      36,     3,     5,     6,     8,     9,    10,    11,    14,    19,
      21,    32,    33,     0,    27,     6,    32,    37,    32,    32,
      32,    32,     3,     6,    17,    18,    38,     3,     3,     7,
       7,    29,     3,    32,     7,    32,    32,    32,    32,     6,
      20,    22,    23,    24,    25,     6,    33,    32,    32,    32,
       7,     7,     7,     7,     3,    35,    32,    38,    38,    38,
      32,    33,     7,     7,     3,     7,    32,    38,    38,     7,
      32,     7,     3,    33,     7,     7,     7,     7,     7
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    29,    30,    30,    30,    30,    31,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    33,
      33,    34,    35,    35,    35,    35,    36,    37,    37,    37,
      38,    38,    38,    38,    38,    38,    38
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     5,     5,
       5,     5,     5,     5,     6,     1,     1,     1,     1,     3,
       3,     8,     0,     1,     2,     3,     4,     1,     2,     3,
       4,     5,     5,     5,     5,     1,     1
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
  case 2: /* start: input '\n'  */
#line 96 "parser.y"
               {}
#line 1334 "y.tab.c"
    break;

  case 3: /* start: input '\n' start  */
#line 97 "parser.y"
                     {}
#line 1340 "y.tab.c"
    break;

  case 5: /* input: function  */
#line 100 "parser.y"
             { /* input can be a function. */
        (yyval.type).node = createNode(NULL, (yyvsp[0].type).node, strdup("FUNCTION")); /* Creates a node with no siblings and function is child of it. */
        head = createNode(NULL, (yyval.type).node, strdup("INPUT"));
        printAST(head, 0); /* Prints the abstract syntax tree. */
        printSymbolTable(); /* Prints the symbol table. */
    }
#line 1351 "y.tab.c"
    break;

  case 6: /* input: exp  */
#line 106 "parser.y"
        {
        (yyval.type).node = createNode(NULL, (yyvsp[0].type).node, strdup("EXPRESSION")); /* Creates a node with no siblings and exp is child of it. */
        head = createNode(NULL, (yyval.type).node, strdup("INPUT"));
        printAST(head, 0); /* Prints the abstract syntax tree. */
        printSymbolTable(); /* Prints the symbol table. */
    }
#line 1362 "y.tab.c"
    break;

  case 7: /* input: explist  */
#line 112 "parser.y"
            {
        (yyval.type).node = createNode(NULL, (yyvsp[0].type).node, strdup("EXPLIST")); /* Creates a node with no siblings and explist is child of it. */
        head = createNode(NULL, (yyval.type).node, strdup("INPUT"));
        printAST(head, 0); /* Prints the abstract syntax tree. */
        printSymbolTable(); /* Prints the symbol table. */
    }
#line 1373 "y.tab.c"
    break;

  case 8: /* asg: OP_OP OP_SET ID exp OP_CP  */
#line 119 "parser.y"
                              { /* Assignment continues with "(" "set" ID exp ")". */
        struct Node * temp8 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[-2].type).name); /* Creates a node for OP_ID with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_SET with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp8, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp8 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, temp7, strdup("ID")); /* Creates a node for ID with temp3 is sibling of it and temp7 is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_SET")); /* Creates a node for OP_SET with temp2 is sibling of it and temp6 is child of it. */  
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        (yyval.type).fval = (yyvsp[-1].type).fval; /* Returns the value of last expression. */
        printf("%s = %f\n", (yyvsp[-2].type).name, (yyvsp[-1].type).fval);
        addVariable((yyvsp[-2].type).name, (yyvsp[-1].type).fval); /* Adds the variable to the symbol table. */
    }
#line 1392 "y.tab.c"
    break;

  case 9: /* exp: OP_OP OP_PLUS exp exp OP_CP  */
#line 134 "parser.y"
                                {
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_PLUS with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-2].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_PLUS")); /* Creates a node for OP_PLUS with temp2 is sibling of it and temp6 is child of it. */
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        (yyval.type).fval = (yyvsp[-1].type).fval; /* Returns the value of last expression. */
        printf("%f\n", (yyvsp[-2].type).fval + (yyvsp[-1].type).fval);
    }
#line 1409 "y.tab.c"
    break;

  case 10: /* exp: OP_OP OP_MINUS exp exp OP_CP  */
#line 146 "parser.y"
                                 {
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_MINUS with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-2].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_MINUS")); /* Creates a node for OP_MINUS with temp2 is sibling of it and temp6 is child of it. */ 
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        (yyval.type).fval = (yyvsp[-1].type).fval;  /* Returns the value of last expression. */
        printf("%f\n", (yyvsp[-2].type).fval - (yyvsp[-1].type).fval);
    }
#line 1426 "y.tab.c"
    break;

  case 11: /* exp: OP_OP OP_MULT exp exp OP_CP  */
#line 158 "parser.y"
                                {
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_MULT with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-2].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_MULT")); /* Creates a node for OP_MULT with temp2 is sibling of it and temp6 is child of it. */   
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        (yyval.type).fval = (yyvsp[-1].type).fval;  /* Returns the value of last expression. */
        printf("%f\n", (yyvsp[-2].type).fval * (yyvsp[-1].type).fval);
    }
#line 1443 "y.tab.c"
    break;

  case 12: /* exp: OP_OP OP_DIV exp exp OP_CP  */
#line 170 "parser.y"
                               {
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_DIV with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-2].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_DIV")); /* Creates a node for OP_DIV with temp2 is sibling of it and temp6 is child of it. */   
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        (yyval.type).fval = (yyvsp[-1].type).fval;  /* Returns the value of last expression. */
        printf("%f\n", (yyvsp[-2].type).fval / (yyvsp[-1].type).fval);
    }
#line 1460 "y.tab.c"
    break;

  case 13: /* exp: OP_OP DEFV ID exp OP_CP  */
#line 182 "parser.y"
                            {
        struct Node * temp8 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[-2].type).name); /* Creates a node for ID with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for DEFV with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp8, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp8 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp5 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, temp7, strdup("ID")); /* Creates a node for ID with temp3 is sibling of it and temp7 is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("DEFV")); /* Creates a node for DEFV with temp2 is sibling of it and temp6 is child of it. */ 
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        (yyval.type).fval = (yyvsp[-1].type).fval;  /* Returns the value of last expression. */
        printf("%s = %f\n", (yyvsp[-2].type).name, (yyvsp[-1].type).fval);
        addVariable((yyvsp[-2].type).name, (yyvsp[-1].type).fval);
    }
#line 1479 "y.tab.c"
    break;

  case 14: /* exp: OP_OP KW_IF expb explist explist OP_CP  */
#line 196 "parser.y"
                                           {
        struct Node * next; /* To decide next expression according to expb value. */
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for KW_IF with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-5].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        if((yyvsp[-3].type).boolean == 0){ /* Creates the next node according to expb value. */
            next = createNode(temp4, (yyvsp[-1].type).node, "EXPLIST");
        }
        else{
            next = createNode(temp4, (yyvsp[-2].type).node, "EXPLIST");
        }
        struct Node * temp2 = createNode(next, (yyvsp[-3].type).node, strdup("EXPB")); /* Creates a node for expb with next is sibling of it and result of the expb is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("KW_IF")); /* Creates a node for KW_IF with temp2 is sibling of it and temp6 is child of it. */   
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        (yyval.type).fval = (yyvsp[-1].type).fval;  /* Returns the value of last expression. */
    }
#line 1501 "y.tab.c"
    break;

  case 15: /* exp: ID  */
#line 213 "parser.y"
       {
        struct Node * temp = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for ID with only its name. */
        (yyval.type).node = createNode(NULL, temp, strdup("ID")); /* Creates a node for ID with no sibling and temp is child of it. */
        float value = lookupVariable((yyvsp[0].type).name); /* Gets value of the variable. */
        if(value == FLT_MAX){ /* If the variable is not declared before, prints an error. */
            char message[100];
            printf("The variable \"%s\" is not recognized!\n", (yyvsp[0].type).name);
            YYABORT;
        }
        (yyval.type).fval = value;  /* Returns the value of last expression. */
    }
#line 1517 "y.tab.c"
    break;

  case 16: /* exp: VALUEF  */
#line 224 "parser.y"
           {
        char * valuef = (char *)malloc(100*sizeof(char)); 
        sprintf(valuef, "%f", (yyvsp[0].type).fval); /* Convert the float value to string. */
        struct Node * temp = createNode(NULL, NULL, valuef); /* Creates a node for VALUEF with only its name. */
        (yyval.type).node = createNode(NULL, temp, strdup("VALUEF")); /* Creates a node for VALUEF with no sibling and temp is child of it. */
        (yyval.type).fval = (yyvsp[0].type).fval;  /* Returns the value of last expression. */
    }
#line 1529 "y.tab.c"
    break;

  case 17: /* exp: fcall  */
#line 231 "parser.y"
          {
        (yyval.type).node = createNode(NULL, (yyvsp[0].type).node, strdup("FCALL")); /* Creates a node for fcall with no sibling and result of the fcall is child of it. */
        (yyval.type).fval = (yyvsp[0].type).fval;  /* Returns the value of last expression. */
    }
#line 1538 "y.tab.c"
    break;

  case 18: /* exp: asg  */
#line 235 "parser.y"
        {
        (yyval.type).node = createNode(NULL, (yyvsp[0].type).node, strdup("ASSIGNMENT")); /* Creates a node for assignment with no sibling and result of the assignment is child of it. */
        (yyval.type).fval = (yyvsp[0].type).fval;  /* Returns the value of last expression. */
    }
#line 1547 "y.tab.c"
    break;

  case 19: /* explist: OP_OP explist OP_CP  */
#line 240 "parser.y"
                        {
        struct Node * temp4 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp3 = createNode(NULL, NULL, (yyvsp[-2].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp2 = createNode(NULL, temp4, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling of and temp4 is child of it. */
        struct Node * temp1 = createNode(temp2, (yyvsp[-1].type).node, strdup("EXPLIST")); /* Creates a node for explist with temp2 is sibling of it and result of the explist is child of it. */
        (yyval.type).node = createNode(temp1, temp3, strdup("OP_OP"));  /* Creates a node for OP_OP with temp1 is sibling of it and temp3 is child of it. */
        (yyval.type).fval = (yyvsp[-1].type).fval;
    }
#line 1560 "y.tab.c"
    break;

  case 20: /* explist: OP_OP exp OP_CP  */
#line 248 "parser.y"
                    {
        struct Node * temp4 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp3 = createNode(NULL, NULL, (yyvsp[-2].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp2 = createNode(NULL, temp4, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling of and temp4 is child of it. */
        struct Node * temp1 = createNode(temp2, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp2 is sibling of it and result of the expression is child of it. */
        (yyval.type).node = createNode(temp1, temp3, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp3 is child of it. */
        (yyval.type).fval = (yyvsp[-1].type).fval;
    }
#line 1573 "y.tab.c"
    break;

  case 21: /* function: OP_OP DEFF ID OP_OP set_of_ids OP_CP explist OP_CP  */
#line 257 "parser.y"
                                                       {
        struct Node * temp13 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp12 = createNode(NULL, NULL, (yyvsp[-2].type).name); /* Creates a node for OP_CP with only its name. */ 
        struct Node * temp11 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp10 = createNode(NULL, NULL, (yyvsp[-5].type).name); /* Creates a node for ID with only its name. */
        struct Node * temp9 = createNode(NULL, NULL, (yyvsp[-6].type).name); /* Creates a node for DEFF with only its name. */
        struct Node * temp8 = createNode(NULL, NULL, (yyvsp[-7].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp7 = createNode(NULL, temp13, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling of and temp13 is child of it. */
        struct Node * temp6 = createNode(temp7, (yyvsp[-1].type).node, strdup("EXPLIST")); /* Creates a node for explist with temp7 is sibling of it and result of the explist is child of it. */
        struct Node * temp5 = createNode(temp6, temp12, strdup("OP_CP")); /* Creates a node for OP_CP with temp6 is sibling of it and temp12 is child of it. */
        struct Node * temp4 = createNode(temp5, (yyvsp[-3].type).node, strdup("SETOFIDS")); /* Creates a node for set_of_ids with temp5 is sibling of it and result of the set_of_ids is child of it. */
        struct Node * temp3 = createNode(temp4, temp11, strdup("OP_OP")); /* Creates a node for OP_OP with temp4 is sibling of it and temp11 is child of it. */
        struct Node * temp2 = createNode(temp3, temp10, strdup("ID")); /* Creates a node for ID with temp3 is sibling of it and temp10 is child of it. */
        struct Node * temp1 = createNode(temp2, temp9, strdup("DEFF")); /* Creates a node for DEFF with temp2 is sibling of it and temp9 is child of it. */
        (yyval.type).node = createNode(temp1, temp8, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp8 is child of it. */
        (yyval.type).fval = 0.0;
    }
#line 1595 "y.tab.c"
    break;

  case 22: /* set_of_ids: %empty  */
#line 275 "parser.y"
    {}
#line 1601 "y.tab.c"
    break;

  case 23: /* set_of_ids: ID  */
#line 276 "parser.y"
       {
        struct Node * temp = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for ID with only its name. */
        (yyval.type).node = createNode(NULL, temp, strdup("ID")); /* Creates a node for ID with no sibling of and temp is child of it. */
    }
#line 1610 "y.tab.c"
    break;

  case 24: /* set_of_ids: ID ID  */
#line 280 "parser.y"
          {
        struct Node * temp2 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for ID with only its name. */
        struct Node * temp1 = createNode(NULL, temp2, "ID"); /* Creates a node for ID with no sibling of and temp2 is child of it. */
        struct Node * temp = createNode(NULL, NULL, (yyvsp[-1].type).name); /* Creates a node for ID with only its name. */
        (yyval.type).node = createNode(temp1, temp, strdup("ID")); /* Creates a node for ID with temp1 is sibling of it and temp is child of it. */
    }
#line 1621 "y.tab.c"
    break;

  case 25: /* set_of_ids: ID ID ID  */
#line 286 "parser.y"
             {
        struct Node * temp4 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for ID with only its name. */
        struct Node * temp3 = createNode(NULL, temp4, "ID"); /* Creates a node for ID with no sibling of and temp4 is child of it. */
        struct Node * temp2 = createNode(NULL, NULL, (yyvsp[-1].type).name); /* Creates a node for ID with only its name. */
        struct Node * temp1 = createNode(temp3, temp2, "ID"); /* Creates a node for ID with temp3 is sibling of it and temp2 is child of it. */
        struct Node * temp = createNode(NULL, NULL, (yyvsp[-2].type).name); /* Creates a node for ID with only its name. */
        (yyval.type).node = createNode(temp1, temp, strdup("ID")); /* Creates a node for ID with temp1 is sibling of it and temp is child of it. */
    }
#line 1634 "y.tab.c"
    break;

  case 26: /* fcall: OP_OP ID set_of_exps OP_CP  */
#line 295 "parser.y"
                               {
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-2].type).name); /* Creates a node for ID with only its name. */ 
        struct Node * temp4 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp3 = createNode(NULL, temp6, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling of and temp6 is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-1].type).node, strdup("SETOFEXPRESSIONS")); /* Creates a node for set_of_expression with temp3 is sibling of it and result of the set_of_expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp5, strdup("ID")); /* Creates a node for ID with temp2 is sibling of it and temp5 is child of it. */   
        (yyval.type).node = createNode(temp1, temp4, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp4 is child of it. */
        (yyval.type).fval = 0.0;
    }
#line 1649 "y.tab.c"
    break;

  case 27: /* set_of_exps: exp  */
#line 306 "parser.y"
        {
        (yyval.type).node = createNode(NULL, (yyvsp[0].type).node, strdup("EXPRESSION")); /* Creates a node for exp with no sibling and result of the expression is child of it. */
    }
#line 1657 "y.tab.c"
    break;

  case 28: /* set_of_exps: exp exp  */
#line 309 "parser.y"
            {
        struct Node * temp = createNode(NULL, (yyvsp[0].type).node, strdup("EXPRESSION")); /* Creates a node for exp with no sibling and result of the expression is child of it. */
        (yyval.type).node = createNode(temp, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp is sibling of it and result of the expression is child of it. */
    }
#line 1666 "y.tab.c"
    break;

  case 29: /* set_of_exps: exp exp exp  */
#line 313 "parser.y"
                {
        struct Node * temp1 = createNode(NULL, (yyvsp[0].type).node, strdup("EXPRESSION")); /* Creates a node for exp with no sibling and result of the expression is child of it. */
        struct Node * temp = createNode(temp1, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp1 is sibling of it and result of the expression is child of it. */
        (yyval.type).node = createNode(temp, (yyvsp[-2].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp1 is sibling of it and result of the expression is child of it. */
    }
#line 1676 "y.tab.c"
    break;

  case 30: /* expb: OP_OP OP_NOT expb OP_CP  */
#line 319 "parser.y"
                            {
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-2].type).name); /* Creates a node for OP_NOT with only its name. */
        struct Node * temp4 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp3 = createNode(NULL, temp6, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp6 is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-1].type).node, strdup("EXPB")); /* Creates a node for expb with temp3 is sibling of it and result of the expb is child of it. */
        struct Node * temp1 = createNode(temp2, temp5, strdup("OP_NOT")); /* Creates a node for OP_NOT with no sibling and temp5 is child of it. */    
        (yyval.type).node = createNode(temp1, temp4, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp4 is child of it. */
        (yyval.type).boolean = ((yyvsp[-1].type).boolean == 1) ? 0: 1; /* If expb is 0 returns 1, otherwise returns 0. */
    }
#line 1691 "y.tab.c"
    break;

  case 31: /* expb: OP_OP OP_OR expb expb OP_CP  */
#line 329 "parser.y"
                                {
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_OR with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPB")); /* Creates a node for expb with temp4 is sibling of it and result of the expb is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-2].type).node, strdup("EXPB")); /* Creates a node for expb with temp3 is sibling of it and result of the expb is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_OR")); /* Creates a node for OP_OR with no sibling and temp6 is child of it. */     
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp5 is child of it. */
        (yyval.type).boolean = ((yyvsp[-2].type).boolean + (yyvsp[-1].type).boolean < 1) ? 0: 1; /* If one of the expb1 and expb2 is 1 returns 1, otherwise returns 0. */
    }
#line 1707 "y.tab.c"
    break;

  case 32: /* expb: OP_OP OP_AND expb expb OP_CP  */
#line 340 "parser.y"
                                 {
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_AND with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPB")); /* Creates a node for expb with temp4 is sibling of it and result of the expb is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-2].type).node, strdup("EXPB")); /* Creates a node for expb with temp3 is sibling of it and result of the expb is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_AND")); /* Creates a node for OP_AND with no sibling and temp6 is child of it. */     
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp5 is child of it. */
        (yyval.type).boolean = ((yyvsp[-2].type).boolean + (yyvsp[-1].type).boolean == 2) ? 1: 0; /* If both expb1 and expb2 is 1 returns 1, otherwise returns 0. */
    }
#line 1723 "y.tab.c"
    break;

  case 33: /* expb: OP_OP OP_GT exp exp OP_CP  */
#line 351 "parser.y"
                              {
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_GT with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-2].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_GT")); /* Creates a node for OP_GT with no sibling and temp6 is child of it. */     
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp5 is child of it. */
        (yyval.type).boolean = ((yyvsp[-2].type).fval > (yyvsp[-1].type).fval) ? 1: 0; /* Compares exp1 and exp2, and returns 1 if exp1 is greater than exp2, otherwise returns 0. */
    }
#line 1739 "y.tab.c"
    break;

  case 34: /* expb: OP_OP OP_EQ exp exp OP_CP  */
#line 362 "parser.y"
                              {
        struct Node * temp7 = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, (yyvsp[-3].type).name); /* Creates a node for OP_EQ with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, (yyvsp[-4].type).name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, (yyvsp[-1].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, (yyvsp[-2].type).node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_EQ")); /* Creates a node for OP_EQ with no sibling and temp6 is child of it. */   
        (yyval.type).node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp5 is child of it. */
        (yyval.type).boolean = ((yyvsp[-2].type).fval == (yyvsp[-1].type).fval) ? 1: 0; /* Compares exp1 and exp2, and returns 1 if they are equal, otherwise returns 0. */
    }
#line 1755 "y.tab.c"
    break;

  case 35: /* expb: KW_TRUE  */
#line 373 "parser.y"
            {
        struct Node * temp = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for KW_TRUE with only its name. */
        (yyval.type).node = createNode(NULL, temp, strdup("KW_TRUE")); /* Creates a node for KW_TRUE with no sibling and temp is child of it. */
        (yyval.type).boolean = 1; /* Returns 1. */
    }
#line 1765 "y.tab.c"
    break;

  case 36: /* expb: KW_FALSE  */
#line 378 "parser.y"
             {
        struct Node * temp = createNode(NULL, NULL, (yyvsp[0].type).name); /* Creates a node for KW_FALSE with only its name. */
        (yyval.type).node = createNode(NULL, temp, strdup("KW_FALSE")); /* Creates a node for KW_FALSE with no sibling and temp is child of it. */
        (yyval.type).boolean = 0; /* Returns 0. */
    }
#line 1775 "y.tab.c"
    break;


#line 1779 "y.tab.c"

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

#line 383 "parser.y"


int main(int argc, char **argv){
    //yyin = fopen(argv[1], "r");
    yyparse();
}

void yyerror(char * message){
    printf("Syntax Error!\n");
}



