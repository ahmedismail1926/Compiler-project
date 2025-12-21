#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadruple.h"


static Quadruple quad_table[MAX_QUADS];
static int quad_index = 0;
static int temp_counter = 0;
static int label_counter = 0;


static const char* safe_str(const char* str) {
    return (str && str[0] != '\0') ? str : "-";
}


void init_quadruples(void) {
    quad_index = 0;
    temp_counter = 0;
    label_counter = 0;
    
    //memset(quad_table, 0, sizeof(quad_table)); //clear the table(optional)
}


void gen_quad(const char* op, const char* arg1, const char* arg2, const char* result) {
    
    if (!op) {
        fprintf(stderr, "Error: NULL operation in gen_quad\n");
        return;
    }
    
    if (quad_index >= MAX_QUADS) {
        fprintf(stderr, "FATAL ERROR: Quadruple table overflow (max %d)\n", MAX_QUADS);
        fprintf(stderr, "  Operation: %s, Args: %s, %s, Result: %s\n",
                op, safe_str(arg1), safe_str(arg2), safe_str(result));
        exit(EXIT_FAILURE);
    }
    
    strncpy(quad_table[quad_index].op, op, sizeof(quad_table[quad_index].op) - 1);
    quad_table[quad_index].op[sizeof(quad_table[quad_index].op) - 1] = '\0';
    
    if (arg1 && arg1[0]) {
        strncpy(quad_table[quad_index].arg1, arg1, sizeof(quad_table[quad_index].arg1) - 1);
        quad_table[quad_index].arg1[sizeof(quad_table[quad_index].arg1) - 1] = '\0';
    } else {
        quad_table[quad_index].arg1[0] = '\0';
    }
    
    if (arg2 && arg2[0]) {
        strncpy(quad_table[quad_index].arg2, arg2, sizeof(quad_table[quad_index].arg2) - 1);
        quad_table[quad_index].arg2[sizeof(quad_table[quad_index].arg2) - 1] = '\0';
    } else {
        quad_table[quad_index].arg2[0] = '\0';
    }
    
    if (result && result[0]) {
        strncpy(quad_table[quad_index].result, result, sizeof(quad_table[quad_index].result) - 1);
        quad_table[quad_index].result[sizeof(quad_table[quad_index].result) - 1] = '\0';
    } else {
        quad_table[quad_index].result[0] = '\0';
    }
    
    quad_index++;
}

void backpatch(int q_index, const char* label) {
    if (q_index >= 0 && q_index < quad_index && label && label[0]) {
        strncpy(quad_table[q_index].result, label, sizeof(quad_table[q_index].result) - 1);
        quad_table[q_index].result[sizeof(quad_table[q_index].result) - 1] = '\0';
    } else {
        fprintf(stderr, "Warning: Invalid backpatch attempt at index %d\n", q_index);
    }
}


char* new_temp(void) {
    char* buf = malloc(20);
    if (!buf) {
        fprintf(stderr, "Memory allocation error for temp variable\n");
        return strdup("t0"); 
    }
    snprintf(buf, 20, "t%d", temp_counter++);
    return buf;
}

char* new_label(void) {
    char* buf = malloc(20);
    if (!buf) {
        fprintf(stderr, "Memory allocation error for label\n");
        return strdup("L0"); 
    }
    snprintf(buf, 20, "L%d", label_counter++);
    return buf;
}


void free_temp_label(char* s) {
    if (!s) return;

    if (s[0] == 't' || s[0] == 'L') {
        free(s);
    }
}


void gen_label(const char* label_name) {
    if (!label_name || label_name[0] == '\0') {
        fprintf(stderr, "Warning: Empty label name\n");
        return;
    }
    gen_quad("LABEL", "", "", label_name);
}


int nextquad(void) {
    return quad_index;
}

int get_quad_count(void) {
    return quad_index;
}


int get_temp_count(void) {
    return temp_counter;
}


int get_label_count(void) {
    return label_counter;
}


void cleanup_quadruples(void) {
    quad_index = 0;
    temp_counter = 0;
    label_counter = 0;
}


const Quadruple* get_quad(int index) {
    if (index >= 0 && index < quad_index) {
        return &quad_table[index];
    }
    return NULL;
}

void gen_jump(const char* label) {
    gen_quad("JMP", "", "", label);
}

void gen_jump_false(const char* condition, const char* label) {
    gen_quad("JF", condition, "", label);
}


void gen_call(const char* func_name, const char* result) {
    gen_quad("CALL", func_name, "", result ? result : "");
}

void gen_return(const char* value) {
    gen_quad("RETURN", value ? value : "", "", "");
}


void gen_add(const char* arg1, const char* arg2, const char* result) {
    gen_quad("ADD", arg1, arg2, result);
}

void gen_sub(const char* arg1, const char* arg2, const char* result) {
    gen_quad("SUB", arg1, arg2, result);
}

void gen_mult(const char* arg1, const char* arg2, const char* result) {
    gen_quad("MULT", arg1, arg2, result);
}

void gen_div(const char* arg1, const char* arg2, const char* result) {
    gen_quad("DIV", arg1, arg2, result);
}

void gen_assign(const char* src, const char* dest) {
    gen_quad("ASSIGN", src, "", dest);
}


void print_quadruples(void) {
    printf("\n========== QUADRUPLES (%d generated) ==========\n", quad_index);
    printf("%-5s %-10s %-12s %-12s %-12s\n", 
        "#", "OP", "ARG1", "ARG2", "RESULT");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < quad_index; i++) {
        printf("%-5d %-10s %-12s %-12s %-12s\n",
            i,
            quad_table[i].op,
            quad_table[i].arg1[0] ? quad_table[i].arg1 : "-",
            quad_table[i].arg2[0] ? quad_table[i].arg2 : "-",
            quad_table[i].result[0] ? quad_table[i].result : "-");
    }
    printf("============================================================\n");
}

/* ===== PRINT QUADRUPLES TO FILE ===== */
void print_quadruples_to_file(FILE* file) {
    if (!file) return;
    
    fprintf(file, "\n========== QUADRUPLES (%d generated) ==========\n", quad_index);
    fprintf(file, "%-5s %-10s %-12s %-12s %-12s\n", 
            "#", "OP", "ARG1", "ARG2", "RESULT");
    fprintf(file, "------------------------------------------------------------\n");
    
    for (int i = 0; i < quad_index; i++) {
        fprintf(file, "%-5d %-10s %-12s %-12s %-12s\n",
                i,
                quad_table[i].op,
                quad_table[i].arg1[0] ? quad_table[i].arg1 : "-",
                quad_table[i].arg2[0] ? quad_table[i].arg2 : "-",
                quad_table[i].result[0] ? quad_table[i].result : "-");
    }
    fprintf(file, "============================================================\n");
}

/* ===== SAVE QUADRUPLES TO FILE ===== */
void save_quadruples(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s' for writing quadruples\n", filename);
        return;
    }
    
    print_quadruples_to_file(file);
    fclose(file);
    printf("Quadruples saved to '%s'\n", filename);
}