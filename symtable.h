#ifndef SYMTABLE_H
#define SYMTABLE_H

/*  Symbol kind */
typedef enum {
    SYMBOL_VAR,
    SYMBOL_CONST,
    SYMBOL_FUNC
} SymbolKind;

/* Symbol table entry */
typedef struct Symbol {
    char* name;
    int type;               // INT, FLOAT, VOID
    SymbolKind kind;
    int scope_level;
    int initialized;
    int used;
    struct Symbol* next;
} Symbol;

/*  Symbol table initialization */
void init_symbol_table();

/* Scope handling */
void enter_scope();
void exit_scope();

/* Insertions */
int insert_symbol(const char* name, int type);
int insert_const(const char* name, int type);
int insert_function(const char* name, int type);

/* Lookups */
int is_declared(const char* name);
int get_type(const char* name);

/* Semantic checks */
void mark_initialized(const char* name);
int is_initialized(const char* name);
void mark_used(const char* name);
void check_unused_variables();

/* Error reporting */
void semantic_error(const char* msg, const char* name);

/* Debug output */
void print_symbol_table();

#endif
