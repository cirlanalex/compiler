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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    PROGRAM = 258,                 /* PROGRAM  */
    CONST = 259,                   /* CONST  */
    VAR = 260,                     /* VAR  */
    ARRAY = 261,                   /* ARRAY  */
    RANGE = 262,                   /* RANGE  */
    OF = 263,                      /* OF  */
    FUNCTION = 264,                /* FUNCTION  */
    PROCEDURE = 265,               /* PROCEDURE  */
    BEGINTOK = 266,                /* BEGINTOK  */
    ENDTOK = 267,                  /* ENDTOK  */
    ASSIGN = 268,                  /* ASSIGN  */
    IF = 269,                      /* IF  */
    THEN = 270,                    /* THEN  */
    ELSE = 271,                    /* ELSE  */
    WHILE = 272,                   /* WHILE  */
    DO = 273,                      /* DO  */
    RELOPLT = 274,                 /* RELOPLT  */
    RELOPLEQ = 275,                /* RELOPLEQ  */
    RELOPEQ = 276,                 /* RELOPEQ  */
    RELOPNEQ = 277,                /* RELOPNEQ  */
    RELOPGEQ = 278,                /* RELOPGEQ  */
    RELOPGT = 279,                 /* RELOPGT  */
    INTEGER = 280,                 /* INTEGER  */
    REAL = 281,                    /* REAL  */
    AND = 282,                     /* AND  */
    OR = 283,                      /* OR  */
    NOT = 284,                     /* NOT  */
    DIV = 285,                     /* DIV  */
    MOD = 286,                     /* MOD  */
    SKIP = 287,                    /* SKIP  */
    READLN = 288,                  /* READLN  */
    WRITELN = 289,                 /* WRITELN  */
    INTNUMBER = 290,               /* INTNUMBER  */
    REALNUMBER = 291,              /* REALNUMBER  */
    IDENTIFIER = 292               /* IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 55 "parser.y"

  int ival;     /* used for passing int values from lexer to parser */
  double dval;  /* used for passing double values from lexer to parser */
  char *sval;   /* used for passing string values from lexer to parser */
  ReturnType returntype;
  TypeSpecStruct typeSpec;
  ArithStruct arithStruct;
  NumberStruct number;
  IdentifiersStruct *identifiers;
  ParametersStruct *parameters;
  ArithExprsStruct *arithExprs;
  LhsStruct lhs;
  LhsListStruct *lhsList;
  /* add here anything you may need */
  /*....*/  

#line 118 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
