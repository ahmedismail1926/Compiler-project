%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

int line_num = 1;
%}

%option noyywrap

DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT}|_)*
INTEGER     {DIGIT}+
FLOAT       {DIGIT}+"."{DIGIT}+
WHITESPACE  [ \t\r]+

%%

"int"       { return INT; }
"float"     { return FLOAT; }
"void"      { return VOID; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR; }
"return"    { return RETURN; }
"repeat"    { return REPEAT; }
"until"     { return UNTIL; }
"switch"    { return SWITCH; }
"case"      { return CASE; }
"default"   { return DEFAULT; }
"const"     { return CONST; }


{ID} {
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}


{FLOAT} {
    yylval.str = strdup(yytext);
    return FLOAT_NUM;
}

{INTEGER} {
    yylval.str = strdup(yytext);
    return INTEGER_NUM;
}


"=="        { return EQ; }
"!="        { return NE; }
"<="        { return LE; }
">="        { return GE; }

"&&"        { return AND; }
"||"        { return OR; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULT; }
"/"         { return DIV; }
"="         { return ASSIGN; }
"<"         { return LT; }
">"         { return GT; }


";"         { return SEMICOLON; }
","         { return COMMA; }
":"         { return COLON; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
"("         { return LPAREN; }
")"         { return RPAREN; }


{WHITESPACE}    { }


"\n"        { line_num++; }


"//".*      { }

/* Multi-line comments */
"/*"        {
                int c;
                while ((c = input()) != 0) {
                    if (c == '\n') line_num++;
                    else if (c == '*') {
                        if ((c = input()) == '/') break;
                        else unput(c);
                    }
                }
            }


. {
    fprintf(stderr,
        "Lexical error: Unrecognized character '%s' at line %d\n",
        yytext, line_num);
    return LEXICAL_ERROR;
}

%%
