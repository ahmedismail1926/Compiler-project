#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

/* ===== PHASE 2: Global symbol table ===== */
static Symbol* symbol_table = NULL;
static int current_scope = 0;

/* ===== PHASE 2: Initialize symbol table ===== */
void init_symbol_table() {
    symbol_table = NULL;
    current_scope = 0;
}

/*  Enter new scope */
void enter_scope() {
    current_scope++;
}

/*  Exit scope */
void exit_scope() {
    Symbol* curr = symbol_table;
    Symbol* prev = NULL;

    while (curr) {
        if (curr->scope_level == current_scope) {
            if (prev)
                prev->next = curr->next;
            else
                symbol_table = curr->next;

            Symbol* temp = curr;
            curr = curr->next;
            free(temp->name);
            free(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    current_scope--;
}

/* detect multiple declarations in the same scope */
static Symbol* lookup_current_scope(const char* name) {
    Symbol* curr = symbol_table;
    while (curr) {
        if (strcmp(curr->name, name) == 0 &&
            curr->scope_level == current_scope)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

/*  Lookup any scope */
static Symbol* lookup(const char* name) {
    Symbol* curr = symbol_table;
    while (curr) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

/*  Insert variable */
int insert_symbol(const char* name, int type) {
    if (lookup_current_scope(name))
        return 0;

    Symbol* sym = malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->type = type;
    sym->kind = SYMBOL_VAR;
    sym->scope_level = current_scope;
    sym->initialized = 0;
    sym->used = 0;
    sym->next = symbol_table;
    symbol_table = sym;

    return 1;
}

/*  Insert constant */
int insert_const(const char* name, int type) {
    if (lookup_current_scope(name))
        return 0;

    Symbol* sym = malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->type = type;
    sym->kind = SYMBOL_CONST;
    sym->scope_level = current_scope;
    sym->initialized = 1;
    sym->used = 0;
    sym->next = symbol_table;
    symbol_table = sym;

    return 1;
}

/*  Insert function  */
int insert_function(const char* name, int type) {
    if (lookup_current_scope(name))
        return 0;

    Symbol* sym = malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->type = type;
    sym->kind = SYMBOL_FUNC;
    sym->scope_level = current_scope;
    sym->initialized = 1;
    sym->used = 0;
    sym->next = symbol_table;
    symbol_table = sym;

    return 1;
}

/* Declaration check */
int is_declared(const char* name) {
    return lookup(name) != NULL;
}

/*  Get type */
int get_type(const char* name) {
    Symbol* sym = lookup(name);
    return sym ? sym->type : -1;
}

/* Initialization tracking */
void mark_initialized(const char* name) {
    Symbol* sym = lookup(name);
    if (sym)
        sym->initialized = 1;
}

int is_initialized(const char* name) {
    Symbol* sym = lookup(name);
    return sym ? sym->initialized : 0;
}

/*  Usage tracking */
void mark_used(const char* name) {
    Symbol* sym = lookup(name);
    if (sym)
        sym->used = 1;
}

/*  Unused variable detection*/
void check_unused_variables() {
    Symbol* curr = symbol_table;
    while (curr) {
        if (curr->kind == SYMBOL_VAR &&
            curr->scope_level == current_scope &&
            !curr->used) {
            printf("Semantic Warning: Variable '%s' declared but not used\n",
                curr->name);
        }
        curr = curr->next;
    }
}

/*  Semantic error*/
void semantic_error(const char* msg, const char* name) {
    fprintf(stderr, "Semantic Error: %s (%s)\n", msg, name);
}

/*  Print symbol table */
void print_symbol_table() {
    Symbol* curr = symbol_table;

    printf("\n===== SYMBOL TABLE =====\n");
    printf("%-12s %-6s %-8s %-6s %-6s %-6s\n",
        "Name", "Type", "Kind", "Scope", "Init", "Used");

    while (curr) {
        printf("%-12s %-6d %-8d %-6d %-6d %-6d\n",
            curr->name,
            curr->type,
            curr->kind,
            curr->scope_level,
            curr->initialized,
            curr->used);
        curr = curr->next;
    }
}
