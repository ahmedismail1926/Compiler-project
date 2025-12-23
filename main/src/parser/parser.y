%code requires {
    #include "symtable.h"

    typedef struct {
        char* place;
        DataType type;
        int is_label;
    } Attribute;
}

%{
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
static int current_function_has_return = 0;

%}
%union {
    Attribute attr;
    char* str;
    int num;
}


%token INT FLOAT CHAR BOOL VOID 
%token IF ELSE WHILE DO FOR RETURN BREAK CONTINUE REPEAT UNTIL SWITCH CASE DEFAULT CONST
%token <str> IDENTIFIER
%token <str> INTEGER_NUM FLOAT_NUM CHAR_LITERAL
%token PLUS MINUS MULT DIV MOD ASSIGN
%token INC DEC PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token BIT_AND BIT_OR BIT_XOR BIT_NOT
%token EQ NE LT GT LE GE
%token AND OR NOT
%token SEMICOLON COMMA COLON LBRACE RBRACE LPAREN RPAREN
%token LEXICAL_ERROR
%token TRUE FALSE

%type <attr> expression simple_expr additive_expr term factor
%type <attr> var_type fun_type arg
%type <num> params param_list arg_list
%type <str> relop

/* Tell Bison to expect 1 shift/reduce conflict (dangling else) */
%expect 1

/* Standard precedence - lowest to highest */
%right ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%left OR
%left AND
%left BIT_OR
%left BIT_XOR
%left BIT_AND
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV MOD
%right NOT BIT_NOT
%right INC DEC

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
    | CHAR  { $$.type = TYPE_CHAR; $$.place = NULL; $$.is_label = 0; }
    | BOOL  { $$.type = TYPE_BOOL; $$.place = NULL; $$.is_label = 0; }
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

        if ($1.type != $4.type && 
            !($1.type == TYPE_FLOAT && $4.type == TYPE_INT) &&
            !($1.type == TYPE_BOOL && $4.type == TYPE_INT) &&
            !($1.type == TYPE_INT && $4.type == TYPE_BOOL))
            yyerror("Type mismatch in initialization");

        mark_initialized($2);
        mark_used($2);
        gen_assign($4.place, $2);
        
        free_temp_label($4.place);
    }
    | CONST var_type IDENTIFIER ASSIGN expression SEMICOLON
    {
        if (!insert_const($3, $2.type))
            yyerror("Redeclaration of constant");

        if ($2.type != $5.type && 
            !($2.type == TYPE_FLOAT && $5.type == TYPE_INT) &&
            !($2.type == TYPE_BOOL && $5.type == TYPE_INT) &&
            !($2.type == TYPE_INT && $5.type == TYPE_BOOL))
            yyerror("Type mismatch in constant initialization");

        gen_assign($5.place, $3);
        mark_used($3);
        free_temp_label($5.place);
    }
    ;


fun_declaration:
    fun_type IDENTIFIER
    {
        if (!insert_function($2, $1.type))
            yyerror("Redeclaration of function");
        current_function = strdup($2);
        current_function_has_return = 0;
    }
    LPAREN params RPAREN compound_stmt
    {
        /* If function is non-void, ensure at least one return was seen */
        if (current_function != NULL) {
            DataType ftype = get_function_type(current_function);
            if (ftype != TYPE_VOID && !current_function_has_return) {
                yyerror("Non-void function missing return");
                YYERROR;
            }
        }
        free(current_function);
        current_function = NULL;
    }
    | var_type IDENTIFIER
    {
        if (!insert_function($2, $1.type))
            yyerror("Redeclaration of function");
        current_function = strdup($2);
        current_function_has_return = 0;
    }
    LPAREN params RPAREN compound_stmt  /* int/float functions */
    {
        /* If function is non-void, ensure at least one return was seen */
        if (current_function != NULL) {
            DataType ftype = get_function_type(current_function);
            if (ftype != TYPE_VOID && !current_function_has_return) {
                yyerror("Non-void function missing return");
                YYERROR;
            }
        }
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

arg_list:
    arg_list COMMA arg
    {
        $$ = $1 + 1;
    }
    | arg
    {
        $$ = 1;
    }
    ;

arg:
    expression
    {
        /* Generate PARAM quadruple for each argument */
        gen_quad("PARAM", $1.place, "", "");
        $$ = $1;
        free_temp_label($1.place);
    }
    ;

compound_stmt:
    LBRACE
    {
        enter_scope();
    }
    block_item_list
    RBRACE
    {
        check_unused_variables();
        exit_scope();
    }
    ;

block_item_list:
    /* empty */
    | block_item_list block_item
    ;

block_item:
    statement
    | var_declaration
    ;

statement:
    expression_stmt
    | compound_stmt
    | selection_stmt
    | iteration_stmt
    | return_stmt
    | switch_stmt
    | jump_stmt
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
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON
    {
        if ($5.type != TYPE_INT && $5.type != TYPE_BOOL)
            yyerror("Condition must be boolean/int");
        
        char* start_label = new_label();
        char* end_label = new_label();
        
        gen_label(start_label);
        /* statement body already executed */
        gen_jump_false($5.place, end_label);
        gen_jump(start_label);
        gen_label(end_label);
        
        free_temp_label(start_label);
        free_temp_label(end_label);
        free_temp_label($5.place);
    }
    ;

return_stmt:
    RETURN SEMICOLON
    {
        DataType ftype = get_function_type(current_function);
        if (ftype != TYPE_VOID) {
            yyerror("Missing return value in non-void function");
            YYERROR;
        }
            /* mark that this function has a return */
            current_function_has_return = 1;
        gen_return("");
    }
    | RETURN expression SEMICOLON
    {
        DataType ftype = get_function_type(current_function);
        if (ftype == TYPE_VOID) {
            yyerror("Return with value in void function");
            YYERROR;
        }

        if (ftype != $2.type &&
            !(ftype == TYPE_FLOAT && $2.type == TYPE_INT) &&
            !(ftype == TYPE_BOOL && $2.type == TYPE_INT) &&
            !(ftype == TYPE_INT && $2.type == TYPE_BOOL)) {
            yyerror("Return type mismatch");
            YYERROR;
        }

        gen_return($2.place);
            /* mark that this function has a return */
            current_function_has_return = 1;
        free_temp_label($2.place);
    }
    ;

jump_stmt:
    BREAK SEMICOLON
    {
        gen_quad("BREAK", "", "", "");
    }
    | CONTINUE SEMICOLON
    {
        gen_quad("CONTINUE", "", "", "");
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
    CASE INTEGER_NUM COLON case_body
    {
        char* case_label = new_label();
        gen_label(case_label);
        free_temp_label(case_label);
    }
    ;

default_case:
    DEFAULT COLON case_body
    {
        char* default_label = new_label();
        gen_label(default_label);
        free_temp_label(default_label);
    }
    ;

/* Case body only allows statements (not declarations) - use { } for declarations */
case_body:
    /* empty */
    | case_body statement
    ;

expression:
    IDENTIFIER ASSIGN expression
    {
        if (!is_declared($1)){
            yyerror("Assignment to undeclared variable");
            YYERROR;
        }else if(!is_accessible($1)){
            yyerror("Variable not accessible in current scope");
            YYERROR;
        }
        if (is_const($1)){
            yyerror("Cannot assign to constant");
            YYERROR;
        }
        
        if (get_type($1) != $3.type && 
            !(get_type($1) == TYPE_FLOAT && $3.type == TYPE_INT) &&
            !(get_type($1) == TYPE_BOOL && $3.type == TYPE_INT) &&
            !(get_type($1) == TYPE_INT && $3.type == TYPE_BOOL)){
                yyerror("Type mismatch in assignment");
                YYERROR;
            }
            
        
        gen_assign($3.place, $1);
        mark_initialized($1);
        mark_used($1); 
        
        $$.place = strdup($1);
        $$.type = get_type($1);
        $$.is_label = 0;
        
        free_temp_label($3.place);
    }
    | IDENTIFIER PLUS_ASSIGN expression
    {
        if (!is_declared($1)) { yyerror("Assignment to undeclared variable"); YYERROR; }
        if (is_const($1)) { yyerror("Cannot assign to constant"); YYERROR; }
        
        char* temp = new_temp();
        gen_add($1, $3.place, temp);
        gen_assign(temp, $1);
        mark_initialized($1);
        mark_used($1);
        
        $$.place = strdup($1);
        $$.type = get_type($1);
        $$.is_label = 0;
        
        free_temp_label(temp);
        free_temp_label($3.place);
    }
    | IDENTIFIER MINUS_ASSIGN expression
    {
        if (!is_declared($1)) { yyerror("Assignment to undeclared variable"); YYERROR; }
        if (is_const($1)) { yyerror("Cannot assign to constant"); YYERROR; }
        
        char* temp = new_temp();
        gen_sub($1, $3.place, temp);
        gen_assign(temp, $1);
        mark_initialized($1);
        mark_used($1);
        
        $$.place = strdup($1);
        $$.type = get_type($1);
        $$.is_label = 0;
        
        free_temp_label(temp);
        free_temp_label($3.place);
    }
    | IDENTIFIER MULT_ASSIGN expression
    {
        if (!is_declared($1)) { yyerror("Assignment to undeclared variable"); YYERROR; }
        if (is_const($1)) { yyerror("Cannot assign to constant"); YYERROR; }
        
        char* temp = new_temp();
        gen_mult($1, $3.place, temp);
        gen_assign(temp, $1);
        mark_initialized($1);
        mark_used($1);
        
        $$.place = strdup($1);
        $$.type = get_type($1);
        $$.is_label = 0;
        
        free_temp_label(temp);
        free_temp_label($3.place);
    }
    | IDENTIFIER DIV_ASSIGN expression
    {
        if (!is_declared($1)) { yyerror("Assignment to undeclared variable"); YYERROR; }
        if (is_const($1)) { yyerror("Cannot assign to constant"); YYERROR; }
        
        char* temp = new_temp();
        gen_div($1, $3.place, temp);
        gen_assign(temp, $1);
        mark_initialized($1);
        mark_used($1);
        
        $$.place = strdup($1);
        $$.type = get_type($1);
        $$.is_label = 0;
        
        free_temp_label(temp);
        free_temp_label($3.place);
    }
    | IDENTIFIER MOD_ASSIGN expression
    {
        if (!is_declared($1)) { yyerror("Assignment to undeclared variable"); YYERROR; }
        if (is_const($1)) { yyerror("Cannot assign to constant"); YYERROR; }
        
        char* temp = new_temp();
        gen_quad("MOD", $1, $3.place, temp);
        gen_assign(temp, $1);
        mark_initialized($1);
        mark_used($1);
        
        $$.place = strdup($1);
        $$.type = get_type($1);
        $$.is_label = 0;
        
        free_temp_label(temp);
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
        if ($1.type != TYPE_INT && $1.type != TYPE_BOOL)
            yyerror("Logical AND requires boolean/int operands");
        if ($3.type != TYPE_INT && $3.type != TYPE_BOOL)
            yyerror("Logical AND requires boolean/int operands");
        
        $$.place = new_temp();
        $$.type = TYPE_BOOL;
        $$.is_label = 0;
        
        gen_quad("AND", $1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | simple_expr OR simple_expr
    {
        if ($1.type != TYPE_INT && $1.type != TYPE_BOOL)
            yyerror("Logical OR requires boolean/int operands");
        if ($3.type != TYPE_INT && $3.type != TYPE_BOOL)
            yyerror("Logical OR requires boolean/int operands");
        
        $$.place = new_temp();
        $$.type = TYPE_BOOL;
        $$.is_label = 0;
        
        gen_quad("OR", $1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | NOT simple_expr
    {
        if ($2.type != TYPE_INT && $2.type != TYPE_BOOL)
            yyerror("Logical NOT requires boolean/int operand");
        
        $$.place = new_temp();
        $$.type = TYPE_BOOL;
        $$.is_label = 0;
        
        gen_quad("NOT", $2.place, "", $$.place);
        
        free_temp_label($2.place);
    }
    | simple_expr BIT_AND simple_expr
    {
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        
        gen_quad("BIT_AND", $1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | simple_expr BIT_OR simple_expr
    {
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        
        gen_quad("BIT_OR", $1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
    }
    | simple_expr BIT_XOR simple_expr
    {
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        
        gen_quad("BIT_XOR", $1.place, $3.place, $$.place);
        
        free_temp_label($1.place);
        free_temp_label($3.place);
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
    | term MOD factor
    {
        $$.place = new_temp();
        $$.type = TYPE_INT;  /* Modulo only for integers */
        $$.is_label = 0;
        
        gen_quad("MOD", $1.place, $3.place, $$.place);
        
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
    | IDENTIFIER LPAREN arg_list RPAREN
    {
        if (!is_function($1))
            yyerror("Call to undeclared function");
        
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
        $$.type = TYPE_BOOL;
        $$.is_label = 0;
        gen_assign("1", $$.place);
    }
    | FALSE
    {
        $$.place = new_temp();
        $$.type = TYPE_BOOL;
        $$.is_label = 0;
        gen_assign("0", $$.place);
    }
    | CHAR_LITERAL
    {
        $$.place = new_temp();
        $$.type = TYPE_CHAR;
        $$.is_label = 0;
        gen_assign($1, $$.place);
    }
    | INC IDENTIFIER
    {
        /* Pre-increment: ++x */
        if (!is_declared($2)) { yyerror("Variable used before declaration"); }
        if (is_const($2)) { yyerror("Cannot modify constant"); }
        
        char* temp = new_temp();
        gen_add($2, "1", temp);
        gen_assign(temp, $2);
        mark_used($2);
        mark_initialized($2);
        
        $$.place = strdup($2);
        $$.type = get_type($2);
        $$.is_label = 0;
        free_temp_label(temp);
    }
    | DEC IDENTIFIER
    {
        /* Pre-decrement: --x */
        if (!is_declared($2)) { yyerror("Variable used before declaration"); }
        if (is_const($2)) { yyerror("Cannot modify constant"); }
        
        char* temp = new_temp();
        gen_sub($2, "1", temp);
        gen_assign(temp, $2);
        mark_used($2);
        mark_initialized($2);
        
        $$.place = strdup($2);
        $$.type = get_type($2);
        $$.is_label = 0;
        free_temp_label(temp);
    }
    | IDENTIFIER INC
    {
        /* Post-increment: x++ */
        if (!is_declared($1)) { yyerror("Variable used before declaration"); }
        if (is_const($1)) { yyerror("Cannot modify constant"); }
        
        $$.place = new_temp();
        gen_assign($1, $$.place);  /* Save original value */
        
        char* temp = new_temp();
        gen_add($1, "1", temp);
        gen_assign(temp, $1);
        mark_used($1);
        mark_initialized($1);
        
        $$.type = get_type($1);
        $$.is_label = 0;
        free_temp_label(temp);
    }
    | IDENTIFIER DEC
    {
        /* Post-decrement: x-- */
        if (!is_declared($1)) { yyerror("Variable used before declaration"); }
        if (is_const($1)) { yyerror("Cannot modify constant"); }
        
        $$.place = new_temp();
        gen_assign($1, $$.place);  /* Save original value */
        
        char* temp = new_temp();
        gen_sub($1, "1", temp);
        gen_assign(temp, $1);
        mark_used($1);
        mark_initialized($1);
        
        $$.type = get_type($1);
        $$.is_label = 0;
        free_temp_label(temp);
    }
    | BIT_NOT factor
    {
        /* Bitwise NOT: ~x */
        $$.place = new_temp();
        $$.type = TYPE_INT;
        $$.is_label = 0;
        gen_quad("BIT_NOT", $2.place, "", $$.place);
        free_temp_label($2.place);
    }
    ;

%%

static FILE* error_file = NULL;
static int error_count = 0;

void yyerror(const char *s) {
    fprintf(stderr, "Line [%d] --> Syntax Error: %s\n", line_num, s);
    if (error_file) {
        fprintf(error_file, "Line [%d] --> Syntax Error: %s\n", line_num, s);
    }
    error_count++;
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

    /* Open error file */
    error_file = fopen("error.txt", "w");
    
    init_symbol_table();
    init_quadruples();

    int parse_result = yyparse();
    
    if (parse_result == 0 && error_count == 0) {
        printf("\nParsing completed successfully\n");
        print_symbol_table();
        print_quadruples();
        
        /* Save to files */
        save_quadruples("quadruples.txt");
        save_symbol_table("output.txt");
        
        if (error_file) {
            fprintf(error_file, "No errors found.\n");
        }
    } else {
        printf("\nCompilation failed with %d error(s)\n", error_count);
    }

    if (error_file) {
        fclose(error_file);
    }
    
    fclose(yyin);
    cleanup_symbol_table();
    cleanup_quadruples();
    
    return (error_count > 0) ? 1 : 0;
}