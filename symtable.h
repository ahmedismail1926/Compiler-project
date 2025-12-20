#ifndef SYMTABLE_H
#define SYMTABLE_H


typedef enum {
    TYPE_INT = 1,
    TYPE_FLOAT = 2,
    TYPE_VOID = 3
} DataType;


typedef enum {
    SYMBOL_VAR,
    SYMBOL_CONST,
    SYMBOL_FUNC
} SymbolKind;

/* ===== Parameter Structure ===== */
typedef struct Param {
    char* name;
    DataType type;
    struct Param* next;
} Param;

/* ===== Symbol Structure ===== */
typedef struct Symbol {
    char* name;
    DataType type;               
    SymbolKind kind;
    int scope_level;
    int initialized;
    int used;
    int param_count;
    Param* params; 
    struct Symbol* next;
} Symbol;


void init_symbol_table(void);
void cleanup_symbol_table(void);


void enter_scope(void);
void exit_scope(void);


int insert_symbol(const char* name, DataType type);
int insert_const(const char* name, DataType type);
int insert_function(const char* name, DataType type);


void add_function_param(const char* func_name, const char* param_name, DataType param_type);
int get_function_param_count(const char* func_name);
DataType get_function_param_type(const char* func_name, int param_index);
DataType get_function_type(const char* func_name);


int is_declared(const char* name);
int is_accessible(const char* name);  
DataType get_type(const char* name);
int is_const(const char* name);
int is_function(const char* name);

void mark_initialized(const char* name);
int is_initialized(const char* name);
void mark_used(const char* name);
void check_unused_variables(void);


void print_symbol_table(void);

#endif