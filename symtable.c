#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

/* ===== Global Variables ===== */
static Symbol* symbol_table = NULL;
static int current_scope = 0;

/* ===== Helper Functions ===== */
static Symbol* lookup_current_scope_only(const char* name);
static Symbol* lookup_accessible(const char* name);
static const char* type_to_string(DataType type);
static const char* kind_to_string(SymbolKind kind);

/* ===== Initialize Symbol Table ===== */
void init_symbol_table(void) {
    symbol_table = NULL;
    current_scope = 0;
}

/* ===== Cleanup Symbol Table ===== */
void cleanup_symbol_table(void) {
    Symbol* current = symbol_table;
    
    while (current) {
        Symbol* next = current->next;
        
        /* Free function parameters if any */
        if (current->kind == SYMBOL_FUNC) {
            Param* param = current->params;
            while (param) {
                Param* next_param = param->next;
                free(param->name);
                free(param);
                param = next_param;
            }
        }
        
        free(current->name);
        free(current);
        current = next;
    }
    
    symbol_table = NULL;
    current_scope = 0;
}

/* ===== Enter New Scope ===== */
void enter_scope(void) {
    current_scope++;
}

/* ===== Exit Current Scope ===== */
void exit_scope(void) {
    if (current_scope <= 0) {
        fprintf(stderr, "Warning: Cannot exit global scope\n");
        return;
    }
    
    Symbol* current = symbol_table;
    Symbol* previous = NULL;
    
    while (current) {
        if (current->scope_level == current_scope) {
            /* Remove symbol from table */
            if (previous) {
                previous->next = current->next;
            } else {
                symbol_table = current->next;
            }
            
            Symbol* to_free = current;
            current = current->next;
            
            /* Free resources */
            if (to_free->kind == SYMBOL_FUNC) {
                Param* param = to_free->params;
                while (param) {
                    Param* next_param = param->next;
                    free(param->name);
                    free(param);
                    param = next_param;
                }
            }
            
            free(to_free->name);
            free(to_free);
        } else {
            previous = current;
            current = current->next;
        }
    }
    
    current_scope--;
}

/* ===== Lookup symbol in CURRENT scope only ===== */
static Symbol* lookup_current_scope_only(const char* name) {
    Symbol* current = symbol_table;
    while (current) {
        if (strcmp(current->name, name) == 0 && 
            current->scope_level == current_scope) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* ===== Lookup symbol in ANY accessible scope (current or outer) ===== */
static Symbol* lookup_accessible(const char* name) {
    Symbol* current = symbol_table;
    Symbol* found = NULL;
    int nearest_scope = -1;
    
    /* Find the nearest declaration in accessible scope */
    while (current) {
        if (strcmp(current->name, name) == 0) {
            /* Symbol found - check if it's in accessible scope */
            if (current->scope_level <= current_scope) {
                /* Choose the nearest (highest scope level) declaration */
                if (found == NULL || current->scope_level > nearest_scope) {
                    found = current;
                    nearest_scope = current->scope_level;
                }
            }
        }
        current = current->next;
    }
    
    return found;
}

/* ===== Insert Variable Symbol ===== */
int insert_symbol(const char* name, DataType type) {
    /* Check if already declared in CURRENT scope only */
    if (lookup_current_scope_only(name)) {
        return 0;  /* Already declared in this scope */
    }
    
    Symbol* new_symbol = malloc(sizeof(Symbol));
    if (!new_symbol) return 0;
    
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->kind = SYMBOL_VAR;
    new_symbol->scope_level = current_scope;
    new_symbol->initialized = 0;
    new_symbol->used = 0;
    new_symbol->param_count = 0;
    new_symbol->params = NULL;
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
    
    return 1;
}

/* ===== Insert Constant Symbol ===== */
int insert_const(const char* name, DataType type) {
    /* Check if already declared in CURRENT scope only */
    if (lookup_current_scope_only(name)) {
        return 0;  /* Already declared in this scope */
    }
    
    Symbol* new_symbol = malloc(sizeof(Symbol));
    if (!new_symbol) return 0;
    
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->kind = SYMBOL_CONST;
    new_symbol->scope_level = current_scope;
    new_symbol->initialized = 1;  /* Constants are always initialized */
    new_symbol->used = 0;
    new_symbol->param_count = 0;
    new_symbol->params = NULL;
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
    
    return 1;
}

/* ===== Insert Function Symbol ===== */
int insert_function(const char* name, DataType type) {
    /* Check if already declared in CURRENT scope only */
    if (lookup_current_scope_only(name)) {
        return 0;  /* Already declared in this scope */
    }
    
    Symbol* new_symbol = malloc(sizeof(Symbol));
    if (!new_symbol) return 0;
    
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->kind = SYMBOL_FUNC;
    new_symbol->scope_level = current_scope;
    new_symbol->initialized = 1;  /* Functions are always "initialized" */
    new_symbol->used = 0;
    new_symbol->param_count = 0;
    new_symbol->params = NULL;
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
    
    return 1;
}

/* ===== Add Parameter to Function ===== */
void add_function_param(const char* func_name, const char* param_name, DataType param_type) {
    Symbol* func = lookup_accessible(func_name);
    if (!func || func->kind != SYMBOL_FUNC) {
        return;
    }
    
    Param* new_param = malloc(sizeof(Param));
    if (!new_param) return;
    
    new_param->name = strdup(param_name);
    new_param->type = param_type;
    new_param->next = NULL;
    
    /* Add to end of parameter list */
    if (func->params == NULL) {
        func->params = new_param;
    } else {
        Param* last = func->params;
        while (last->next) {
            last = last->next;
        }
        last->next = new_param;
    }
    
    func->param_count++;
}

/* ===== Get Function Parameter Count ===== */
int get_function_param_count(const char* func_name) {
    Symbol* func = lookup_accessible(func_name);
    if (!func || func->kind != SYMBOL_FUNC) {
        return -1;
    }
    return func->param_count;
}

/* ===== Get Function Parameter Type ===== */
DataType get_function_param_type(const char* func_name, int param_index) {
    Symbol* func = lookup_accessible(func_name);
    if (!func || func->kind != SYMBOL_FUNC) {
        return TYPE_VOID;  /* Error value */
    }
    
    if (param_index < 0 || param_index >= func->param_count) {
        return TYPE_VOID;  /* Error value */
    }
    
    Param* param = func->params;
    for (int i = 0; i < param_index && param; i++) {
        param = param->next;
    }
    
    return param ? param->type : TYPE_VOID;
}

/* ===== Get Function Return Type ===== */
DataType get_function_type(const char* func_name) {
    Symbol* func = lookup_accessible(func_name);
    if (func && func->kind == SYMBOL_FUNC) {
        return func->type;
    }
    return TYPE_VOID;  /* Error value */
}

/* ===== Check if Symbol is Declared and Accessible ===== */
int is_declared(const char* name) {
    Symbol* sym = lookup_accessible(name);
    return sym != NULL;
}

/* ===== Get Symbol Type (only if accessible) ===== */
DataType get_type(const char* name) {
    Symbol* sym = lookup_accessible(name);
    return sym ? sym->type : TYPE_VOID;
}

/* ===== Check if Symbol is Constant (only if accessible) ===== */
int is_const(const char* name) {
    Symbol* sym = lookup_accessible(name);
    return (sym && sym->kind == SYMBOL_CONST);
}

/* ===== Check if Symbol is Function (only if accessible) ===== */
int is_function(const char* name) {
    Symbol* sym = lookup_accessible(name);
    return (sym && sym->kind == SYMBOL_FUNC);
}

/* ===== Check if Symbol is Accessible in Current Scope ===== */
int is_accessible(const char* name) {
    Symbol* sym = lookup_accessible(name);
    return sym != NULL;
}

/* ===== Mark Symbol as Initialized ===== */
void mark_initialized(const char* name) {
    Symbol* sym = lookup_accessible(name);
    if (sym) {
        sym->initialized = 1;
    }
}

/* ===== Check if Symbol is Initialized ===== */
int is_initialized(const char* name) {
    Symbol* sym = lookup_accessible(name);
    return sym ? sym->initialized : 0;
}

/* ===== Mark Symbol as Used ===== */
void mark_used(const char* name) {
    Symbol* sym = lookup_accessible(name);
    if (sym) {
        sym->used = 1;
    }
}

/* ===== Check for Unused Variables in Current Scope ===== */
void check_unused_variables(void) {
    Symbol* current = symbol_table;
    
    while (current != NULL) {
        if (current->kind == SYMBOL_VAR &&
            current->scope_level == current_scope &&
            !current->used) {
            fprintf(stderr, "Warning: Variable '%s' declared but not used in scope %d\n",
                current->name, current_scope);
        }
        current = current->next;
    }
}

/* ===== Helper: Convert Type to String ===== */
static const char* type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT:   return "INT";
        case TYPE_FLOAT: return "FLOAT";
        case TYPE_VOID:  return "VOID";
        default:         return "UNKNOWN";
    }
}

/* ===== Helper: Convert Kind to String ===== */
static const char* kind_to_string(SymbolKind kind) {
    switch (kind) {
        case SYMBOL_VAR:   return "VARIABLE";
        case SYMBOL_CONST: return "CONSTANT";
        case SYMBOL_FUNC:  return "FUNCTION";
        default:           return "UNKNOWN";
    }
}

/* ===== Print Symbol Table ===== */
void print_symbol_table(void) {
    Symbol* current = symbol_table;
    
    printf("\n========== SYMBOL TABLE (Current Scope: %d) ==========\n", current_scope);
    printf("%-20s %-10s %-12s %-8s %-6s %-10s %-10s\n",
        "Name", "Type", "Kind", "Scope", "Params", "Init", "Used");
    printf("-------------------------------------------------------------------------------\n");
    
    while (current) {
        /* Build parameter string */
        char param_str[50] = "";
        if (current->kind == SYMBOL_FUNC && current->param_count > 0) {
            strcat(param_str, "(");
            Param* param = current->params;
            while (param) {
                strcat(param_str, type_to_string(param->type));
                param = param->next;
                if (param) strcat(param_str, ",");
            }
            strcat(param_str, ")");
        }
        
        printf("%-20s %-10s %-12s %-8d %-6s %-10s %-10s\n",
            current->name,
            type_to_string(current->type),
            kind_to_string(current->kind),
            current->scope_level,
            param_str,
            current->initialized ? "YES" : "NO",
            current->used ? "YES" : "NO");
        
        current = current->next;
    }
    printf("===============================================================================\n");
}