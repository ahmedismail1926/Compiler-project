
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     VOID = 260,
     IF = 261,
     ELSE = 262,
     WHILE = 263,
     FOR = 264,
     RETURN = 265,
     REPEAT = 266,
     UNTIL = 267,
     SWITCH = 268,
     CASE = 269,
     DEFAULT = 270,
     CONST = 271,
     IDENTIFIER = 272,
     INTEGER_NUM = 273,
     FLOAT_NUM = 274,
     PLUS = 275,
     MINUS = 276,
     MULT = 277,
     DIV = 278,
     ASSIGN = 279,
     EQ = 280,
     NE = 281,
     LT = 282,
     GT = 283,
     LE = 284,
     GE = 285,
     AND = 286,
     OR = 287,
     SEMICOLON = 288,
     COMMA = 289,
     COLON = 290,
     LBRACE = 291,
     RBRACE = 292,
     LPAREN = 293,
     RPAREN = 294,
     LEXICAL_ERROR = 295
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


