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

char* current_function = NULL;

/* Simplified Attribute struct */
typedef struct {
    char* place;    /* temporary variable or label */
    DataType type;  /* data type - using DataType enum */
    int is_label;   /* 1 if place is a label, 0 if temp/variable */
} Attribute;

%}

%union {
    Attribute attr;
    char* str;
    int num;
}

%token INT FLOAT VOID 
%token IF ELSE WHILE FOR RETURN REPEAT UNTIL SWITCH CASE DEFAULT CONST
%token <str> IDENTIFIER
%token <str> INTEGER_NUM FLOAT_NUM
%token PLUS MINUS MULT DIV ASSIGN
%token EQ NE LT GT LE GE
%token AND OR NOT
%token SEMICOLON COMMA COLON LBRACE RBRACE LPAREN RPAREN
%token LEXICAL_ERROR
%token TRUE FALSE

%type <attr> expression simple_expr additive_expr term factor
%type <attr> var_type fun_type
%type <num> params param_list
%type <str> relop

/* Tell Bison to expect 1 shift/reduce conflict (dangling else) */
%expect 1

/* Standard precedence */
%right NOT
%left AND OR
%left EQ NE LT GT LE GE
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

/* FIXED: Simplified to avoid conflicts */
var_type
    : INT   { $$.type = TYPE_INT; $$.place = NULL; $$.is_label = 0; }
    | FLOAT { $$.type = TYPE_FLOAT; $$.place = NULL; $$.is_label = 0; }
    ;

/* FIXED: Simplified - only VOID for functions */
fun_type
    : VOID  { $$.type = TYPE_VOID; $$.place = NULL; $$.is_label = 0; }
    ;

var_declaration:
    var_type IDENTIFIER SEMICOLON
    {
        if (!insert_symbol($2, $1.type))
            yyerror("Redeclaration of variable");
    }
    | var_type IDENTIFIER ASSIGN expression SEMICOLON
    {
        if (!insert_symbol($2, $1.type))
            yyerror("Redeclaration of variable");

        if ($1.type != $4.type && !($1.type == TYPE_FLOAT && $4.type == TYPE_INT))
            yyerror("Type mismatch in initialization");

        mark_initialized($2);
        gen_assign($4.place, $2);
        
        free_temp_label($4.place);
    }
    | CONST var_type IDENTIFIER ASSIGN expression SEMICOLON
    {
        if (!insert_const($3, $2.type))
            yyerror("Redeclaration of constant");

        if ($2.type != $5.type && !($2.type == TYPE_FLOAT && $5.type == TYPE_INT))
            yyerror("Type mismatch in constant initialization");

        gen_assign($5.place, $3);
        free_temp_label($5.place);
    }
    ;

/* FIXED: Allow functions to return int/float/void */
fun_declaration:
    fun_type IDENTIFIER LPAREN params RPAREN compound_stmt
    {
        if (!insert_function($2, $1.type))
            yyerror("Redeclaration of function");

        current_function = strdup($2);
        free(current_function);
        current_function = NULL;
    }
    | var_type IDENTIFIER LPAREN params RPAREN compound_stmt  /* int/float functions */
    {
        if (!insert_function($2, $1.type))
            yyerror("Redeclaration of function");

        current_function = strdup($2);
        free(current_function);
        current_function = NULL;
    }
    ;

params:
    param_list
    | VOID { $$ = 0; }
    | { $$ = 0; }
    ;

param_list:
    param_list COMMA param
    {
        $$ = $1 + 1;
    }
    | param
    {
        $$ = 1;
    }
    ;

/* FIXED: Parameters can be int/float */
param:
    var_type IDENTIFIER
    {
        insert_symbol($2, $1.type);
        mark_initialized($2);

        if (current_function) {
            add_function_param(current_function, $2, $1.type);
        }
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
    {
        /* Free temporary if expression created one */
        if ($1.place && strncmp($1.place, "t", 1) == 0) {
            free_temp_label($1.place);
        }
    }
    | SEMICOLON
    ;

selection_stmt:
    IF LPAREN expression RPAREN statement
    {
        if ($3.type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* end_label = new_label();
        gen_jump_false($3.place, end_label);
        
        gen_label(end_label);
        free_temp_label(end_label);
        free_temp_label($3.place);
    }
    | IF LPAREN expression RPAREN statement ELSE statement
    {
        if ($3.type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* else_label = new_label();
        char* end_label = new_label();
        
        gen_jump_false($3.place, else_label);
        
        gen_jump(end_label);
        gen_label(else_label);
        
        gen_label(end_label);
        free_temp_label(else_label);
        free_temp_label(end_label);
        free_temp_label($3.place);
    }
    ;

iteration_stmt:
    WHILE LPAREN expression RPAREN statement
    {
        if ($3.type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* start_label = new_label();
        char* end_label = new_label();
        
        gen_label(start_label);
        gen_jump_false($3.place, end_label);
        
        gen_jump(start_label);
        gen_label(end_label);
        
        free_temp_label(start_label);
        free_temp_label(end_label);
        free_temp_label($3.place);
    }
    | FOR LPAREN expression_stmt expression SEMICOLON expression RPAREN statement
    {
        if ($4.type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* start_label = new_label();
        char* end_label = new_label();
        
        gen_label(start_label);
        gen_jump_false($4.place, end_label);
        
        gen_jump(start_label);
        gen_label(end_label);
        
        free_temp_label(start_label);
        free_temp_label(end_label);
        free_temp_label($4.place);
        free_temp_label($6.place);
    }
    | REPEAT compound_stmt UNTIL LPAREN expression RPAREN SEMICOLON
    {
        if ($5.type != TYPE_INT)
            yyerror("Condition must be boolean/int");
        
        char* start_label = new_label();
        
        gen_label(start_label);
        
        gen_jump_false($5.place, start_label);
        
        free_temp_label(start_label);
        free_temp_label($5.place);
    }
    ;

return_stmt:
    RETURN SEMICOLON
    {
        gen_return("");
    }
    | RETURN expression SEMICOLON
    {
        gen_return($2.place);
        free_temp_label($2.place);
    }
    ;

switch_stmt:
    SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE
    {
        if ($3.type != TYPE_INT)
            yyerror("Switch expression must be integer");
        
        char* end_label = new_label();
        gen_label(end_label);
        
        free_temp_label(end_label);
        free_temp_label($3.place);
    }
    | SWITCH LPAREN expression RPAREN LBRACE case_list default_case RBRACE
    {
        if ($3.type != TYPE_INT)
            yyerror("Switch expression must be integer");
        
        char* end_label = new_label();
        gen_label(end_label);
        
        free_temp_label(end_label);
        free_temp_label($3.place);
    }
    ;

case_list:
    case_list case_stmt
    | case_stmt
    ;

case_stmt:
    CASE INTEGER_NUM COLON statement_list
    {
        char* case_label = new_label();
        gen_label(case_label);
        free_temp_label(case_label);
    }
    ;

default_case:
    DEFAULT COLON statement_list
    {
        char* default_label = new_label();
        gen_label(default_label);
        free_temp_label(default_label);
    }
    ;

expression:
    IDENTIFIER ASSIGN expression
    {
        if (!is_declared($1)){
            yyerror("Assignment to undeclared variable");
        }else if(!is_accessible($1)){
            yyerror("Variable not accessible in current scope");
        }
        if (is_const($1))
            yyerror("Cannot assign to constant");
        
        if (get_type($1) != $3.type && 
            !(get_type($1) == TYPE_FLOAT && $3.type == TYPE_INT))
            yyerror("Type mismatch in assignment");
        
        gen_assign($3.place, $1);
        mark_initialized($1);
        
        $$.place = strdup($1);
        $$.type = get_type($1);
        $$.is_label = 0;
        
        free_temp_label($3.place);
    }
    | simple_expr
    {
        $$ = $1;
    }
    ;

simple_expr:
    simple_expr AND simple_expr
    {
        if ($1.type != TYPE_INT || $3.type != TYPE_INT)
            yyerror("Logical AND requires boolean/int operands");
        
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        
        gen_quad("AND", $1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | simple_expr OR simple_expr
    {
        if ($1.type != TYPE_INT || $3.type != TYPE_INT)
            yyerror("Logical OR requires boolean/int operands");
        
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        
        gen_quad("OR", $1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | NOT simple_expr
    {
        if ($2.type != TYPE_INT)
            yyerror("Logical NOT requires boolean/int operand");
        
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        
        gen_quad("NOT", $2.place, "", $$.place);
        
        free_temp_label($2.place);
    }
    | additive_expr relop additive_expr
    {
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        
        gen_quad($2, $1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | additive_expr
    {
        $$ = $1;
    }
    ;

relop:
    LT { $$ = "<"; }
    | GT { $$ = ">"; }
    | EQ { $$ = "=="; }
    | LE { $$ = "<="; }
    | GE { $$ = ">="; }
    | NE { $$ = "!="; }
    ;

additive_expr:
    additive_expr PLUS term
    {
        $$.place = new_temp();
        $$.type = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        $$.is_label = 0;
        
        gen_add($1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | additive_expr MINUS term
    {
        $$.place = new_temp();
        $$.type = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        $$.is_label = 0;
        
        gen_sub($1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | term
    {
        $$ = $1;
    }
    ;

term:
    term MULT factor
    {
        $$.place = new_temp();
        $$.type = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        $$.is_label = 0;
        
        gen_mult($1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | term DIV factor
    {
        $$.place = new_temp();
        $$.type = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        $$.is_label = 0;
        
        gen_div($1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
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
        if (!is_declared($1)){
            yyerror("Variable used before declaration");
        }else if(!is_accessible($1)){
            yyerror("Variable not accessible in current scope");
        }

        if (!is_initialized($1))
            yyerror("Variable used before initialization");

        mark_used($1);
        $$.place = strdup($1);
        $$.type = get_type($1);
        $$.is_label = 0;
    }
    | IDENTIFIER LPAREN RPAREN
    {
        if (!is_function($1))
            yyerror("Call to undeclared function");
        
        int expected_count = get_function_param_count($1);
        if (expected_count != 0)
            yyerror("Wrong number of arguments in function call");
        
        $$.place = new_temp();
        $$.type = get_function_type($1);
        $$.is_label = 0;
        
        gen_call($1, $$.place);
    }
    | INTEGER_NUM
    {
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        gen_assign($1, $$.place);
    }
    | FLOAT_NUM
    {
        $$.place = new_temp();
        $$.type = TYPE_FLOAT;
        $$.is_label = 0;
        gen_assign($1, $$.place);
    }
    | TRUE
    {
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        gen_assign("1", $$.place);
    }
    | FALSE
    {
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        gen_assign("0", $$.place);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", line_num);
    fprintf(stderr, "Error: %s\n", s);
    if (yytext && strlen(yytext) > 0) {
        fprintf(stderr, "Current token: '%s'\n", yytext);
    }
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