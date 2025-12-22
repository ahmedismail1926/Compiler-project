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
INTEGER     -?{DIGIT}+
FLOATNUM    -?{DIGIT}+"."{DIGIT}+
WHITESPACE  [ \t\r]+

%%

"int"       { return INT; }
"float"     { return FLOAT; }
"char"      { return CHAR; }
"bool"      { return BOOL; }
"void"      { return VOID; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"do"        { return DO; }
"for"       { return FOR; }
"return"    { return RETURN; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"repeat"    { return REPEAT; }
"until"     { return UNTIL; }
"switch"    { return SWITCH; }
"case"      { return CASE; }
"default"   { return DEFAULT; }
"const"     { return CONST; }



"true"      { return TRUE; }
"false"     { return FALSE; }

'\\n'       { yylval.str = strdup("10"); return CHAR_LITERAL; }
'\\t'       { yylval.str = strdup("9"); return CHAR_LITERAL; }
'\\r'       { yylval.str = strdup("13"); return CHAR_LITERAL; }
'\\0'       { yylval.str = strdup("0"); return CHAR_LITERAL; }
'\\''       { yylval.str = strdup("39"); return CHAR_LITERAL; }
'\\\\'      { yylval.str = strdup("92"); return CHAR_LITERAL; }
'[^'\\]'    { 
                char buf[8];
                snprintf(buf, sizeof(buf), "%d", yytext[1]);
                yylval.str = strdup(buf);
                return CHAR_LITERAL; 
            }

{ID} {
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}


{FLOATNUM} {
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
"!"         { return NOT; } 

"++"        { return INC; }
"--"        { return DEC; }
"+="        { return PLUS_ASSIGN; }
"-="        { return MINUS_ASSIGN; }
"*="        { return MULT_ASSIGN; }
"/="        { return DIV_ASSIGN; }
"%="        { return MOD_ASSIGN; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULT; }
"/"         { return DIV; }
"%"         { return MOD; }
"="         { return ASSIGN; }
"<"         { return LT; }
">"         { return GT; }

"&"         { return BIT_AND; }
"|"         { return BIT_OR; }
"^"         { return BIT_XOR; }
"~"         { return BIT_NOT; }


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
