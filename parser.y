%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
extern int line_num;
extern FILE *yyin;
%}

%token INT FLOAT VOID
%token IF ELSE WHILE FOR RETURN REPEAT UNTIL SWITCH CASE DEFAULT CONST
%token IDENTIFIER INTEGER_NUM FLOAT_NUM
%token PLUS MINUS MULT DIV ASSIGN
%token EQ NE LT GT LE GE
%token AND OR
%token SEMICOLON COMMA COLON LBRACE RBRACE LPAREN RPAREN
%token LEXICAL_ERROR

%left OR
%left AND
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV

%%

program:
    declaration_list
    ;

declaration_list:
    declaration_list declaration
    | declaration
    ;

declaration:
    var_declaration
    | fun_declaration
    ;

var_declaration:
    type_specifier IDENTIFIER SEMICOLON
    | type_specifier IDENTIFIER ASSIGN expression SEMICOLON
    | CONST type_specifier IDENTIFIER ASSIGN expression SEMICOLON
    ;

type_specifier:
    INT
    | FLOAT
    | VOID
    ;

fun_declaration:
    type_specifier IDENTIFIER LPAREN params RPAREN compound_stmt
    ;

params:
    param_list
    | VOID
    |
    ;

param_list:
    param_list COMMA param
    | param
    ;

param:
    type_specifier IDENTIFIER
    ;

compound_stmt:
    LBRACE local_declarations statement_list RBRACE
    ;

local_declarations:
    local_declarations var_declaration
    |
    ;

statement_list:
    statement_list statement
    |
    ;

statement:
    expression_stmt
    | compound_stmt
    | selection_stmt
    | iteration_stmt
    | return_stmt
    | switch_stmt
    ;

expression_stmt:
    expression SEMICOLON
    | SEMICOLON
    ;

selection_stmt:
    IF LPAREN expression RPAREN statement
    | IF LPAREN expression RPAREN statement ELSE statement
    ;

iteration_stmt:
    WHILE LPAREN expression RPAREN statement
    | FOR LPAREN expression_stmt expression_stmt expression RPAREN statement
    | FOR LPAREN expression_stmt expression_stmt RPAREN statement
    | REPEAT compound_stmt UNTIL LPAREN expression RPAREN SEMICOLON
    ;

return_stmt:
    RETURN SEMICOLON
    | RETURN expression SEMICOLON
    ;

switch_stmt:
    SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE
    | SWITCH LPAREN expression RPAREN LBRACE case_list default_case RBRACE
    ;

case_list:
    case_list case_stmt
    | case_stmt
    ;

case_stmt:
    CASE INTEGER_NUM COLON statement_list
    ;

default_case:
    DEFAULT COLON statement_list
    ;

expression:
    IDENTIFIER ASSIGN expression
    | simple_expression
    ;

simple_expression:
    additive_expression relop additive_expression
    | additive_expression
    ;

relop:
    LE
    | LT
    | GT
    | GE
    | EQ
    | NE
    ;

additive_expression:
    additive_expression addop term
    | term
    ;

addop:
    PLUS
    | MINUS
    ;

term:
    term mulop factor
    | factor
    ;

mulop:
    MULT
    | DIV
    ;

factor:
    LPAREN expression RPAREN
    | IDENTIFIER
    | call
    | INTEGER_NUM
    | FLOAT_NUM
    ;

call:
    IDENTIFIER LPAREN args RPAREN
    ;

args:
    arg_list
    |
    ;

arg_list:
    arg_list COMMA expression
    | expression
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d\n", line_num);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    if (yyparse() == 0) {
        printf("Success\n");
    }

    fclose(yyin);
    return 0;
}
