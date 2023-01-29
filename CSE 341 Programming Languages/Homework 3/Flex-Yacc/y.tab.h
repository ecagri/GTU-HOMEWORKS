/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 128 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
