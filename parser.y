%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symtable.h"
#include "quadruple.h"

int yylex();
void yyerror(const char *s);
extern int line_num;
extern FILE *yyin;


typedef struct {
    char* place;
    int type;
} Attribute;


static int temp_counter = 0;
char* new_temp() {
    char buf[20];
    sprintf(buf, "t%d", temp_counter++);
    return strdup(buf);
}
%}


%union {
    Attribute attr;
    char* str;
}


%token INT FLOAT VOID
%token IF ELSE WHILE FOR RETURN REPEAT UNTIL SWITCH CASE DEFAULT CONST
%token <str> IDENTIFIER
%token <str> INTEGER_NUM FLOAT_NUM
%token PLUS MINUS MULT DIV ASSIGN
%token EQ NE LT GT LE GE
%token AND OR
%token SEMICOLON COMMA COLON LBRACE RBRACE LPAREN RPAREN
%token LEXICAL_ERROR


%type <attr> expression simple_expression additive_expression term factor
%type <attr> type_specifier


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
    {
        if (!insert_symbol($2, $1.type))
            semantic_error("Redeclaration of variable", $2);
    }
    | type_specifier IDENTIFIER ASSIGN expression SEMICOLON
    {
        if (!insert_symbol($2, $1.type))
            semantic_error("Redeclaration of variable", $2);

        if ($1.type != $4.type)
            semantic_error("Type mismatch in initialization", $2);

        mark_initialized($2);
        gen_quad("=", $4.place, "", $2);
    }
    | CONST type_specifier IDENTIFIER ASSIGN expression SEMICOLON
    {
        if (!insert_const($3, $2.type))
            semantic_error("Redeclaration of constant", $3);

        gen_quad("=", $5.place, "", $3);
    }
    ;

type_specifier:
    INT   { $$ = (Attribute){ .type = INT }; }
    | FLOAT { $$ = (Attribute){ .type = FLOAT }; }
    | VOID  { $$ = (Attribute){ .type = VOID }; }
    ;



fun_declaration:
    type_specifier IDENTIFIER LPAREN params RPAREN compound_stmt
    {
        if (!insert_function($2, $1.type))
            semantic_error("Redeclaration of function", $2);
    }
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
    {
        insert_symbol($2, $1.type);
        mark_initialized($2);
    }
    ;



compound_stmt:
    LBRACE
    {
        enter_scope();
    }
    local_declarations statement_list
    RBRACE
    {
        check_unused_variables();
        exit_scope();
    }
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

/* ================= EXPRESSIONS ================= */

expression:
    IDENTIFIER ASSIGN expression
    {
        if (!is_declared($1))
            semantic_error("Assignment to undeclared variable", $1);

        if (is_const($1))
            semantic_error("Cannot assign to constant", $1);

        gen_quad("=", $3.place, "", $1);
        mark_initialized($1);
        $$ = $3;
    }
    | simple_expression
    {
        $$ = $1;
    }
    ;

simple_expression:
    additive_expression
    | additive_expression LT additive_expression
    {
        $$ = (Attribute){ .place = new_temp(), .type = INT };
        gen_quad("<", $1.place, $3.place, $$.place);
    }
    | additive_expression GT additive_expression
    {
        $$ = (Attribute){ .place = new_temp(), .type = INT };
        gen_quad(">", $1.place, $3.place, $$.place);
    }
    | additive_expression EQ additive_expression
    {
        $$ = (Attribute){ .place = new_temp(), .type = INT };
        gen_quad("==", $1.place, $3.place, $$.place);
    }
    | additive_expression LE additive_expression
    {
        $$ = (Attribute){ .place = new_temp(), .type = INT };
        gen_quad("<=", $1.place, $3.place, $$.place);
    }
    | additive_expression GE additive_expression
    {
        $$ = (Attribute){ .place = new_temp(), .type = INT };
        gen_quad(">=", $1.place, $3.place, $$.place);
    }
    | additive_expression NE additive_expression
    {
        $$ = (Attribute){ .place = new_temp(), .type = INT };
        gen_quad("!=", $1.place, $3.place, $$.place);
    }
    ;

additive_expression:
    additive_expression PLUS term
    {
        $$ = (Attribute){ .place = new_temp(), .type = $1.type };
        gen_quad("+", $1.place, $3.place, $$.place);
    }
    | additive_expression MINUS term
    {
        $$ = (Attribute){ .place = new_temp(), .type = $1.type };
        gen_quad("-", $1.place, $3.place, $$.place);
    }
    | term
    {
        $$ = $1;
    }
    ;

term:
    term MULT factor
    {
        $$ = (Attribute){ .place = new_temp(), .type = $1.type };
        gen_quad("*", $1.place, $3.place, $$.place);
    }
    | term DIV factor
    {
        $$ = (Attribute){ .place = new_temp(), .type = $1.type };
        gen_quad("/", $1.place, $3.place, $$.place);
    }
    | factor
    {
        $$ = $1;
    }
    ;

factor:
    LPAREN expression RPAREN
    {
        $$ = $2;
    }
    | IDENTIFIER
    {
        if (!is_declared($1))
            semantic_error("Variable used before declaration", $1);

        if (!is_initialized($1))
            semantic_error("Variable used before initialization", $1);

        mark_used($1);
        $$ = (Attribute){ .place = strdup($1), .type = get_type($1) };
    }
    | INTEGER_NUM
    {
        $$ = (Attribute){ .place = new_temp(), .type = INT };
        gen_quad("=", $1, "", $$.place);
    }
    | FLOAT_NUM
    {
        $$ = (Attribute){ .place = new_temp(), .type = FLOAT };
        gen_quad("=", $1, "", $$.place);
    }
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
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        return 1;
    }

    init_symbol_table();
    init_quadruples();

    if (yyparse() == 0) {
        printf("\nParsing completed successfully\n");
        print_symbol_table();
        print_quadruples();
    }

    fclose(yyin);
    return 0;
}
