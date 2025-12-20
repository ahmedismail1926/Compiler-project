#ifndef QUADRUPLE_H
#define QUADRUPLE_H

#include <stdio.h>

#define MAX_QUADS 2000  


typedef struct {
    char op[10];      /* operation: JMP, JF, JT, CALL, RET, LABEL, ADD, SUB, etc. */
    char arg1[20];    /* first operand */
    char arg2[20];    /* second operand */
    char result[20];  /* result or label */
} Quadruple;


void init_quadruples(void);
void gen_quad(const char* op, const char* arg1, const char* arg2, const char* result);
void backpatch(int q_index, const char* label);
int nextquad(void);
int get_quad_count(void);
void cleanup_quadruples(void);


char* new_temp(void);
char* new_label(void);
void gen_label(const char* label_name);
void free_temp_label(char* temp_or_label);  


void gen_jump(const char* label);                    /* JMP label */
void gen_jump_false(const char* condition, const char* label); /* JF condition, label */


void gen_call(const char* func_name, const char* result);  
void gen_return(const char* value);                   

void gen_add(const char* arg1, const char* arg2, const char* result);    
void gen_sub(const char* arg1, const char* arg2, const char* result);    
void gen_mult(const char* arg1, const char* arg2, const char* result);   
void gen_div(const char* arg1, const char* arg2, const char* result);    
void gen_assign(const char* src, const char* dest);                      


void print_quadruples(void);
void print_quadruples_to_file(FILE* file);
void save_quadruples(const char* filename);


const Quadruple* get_quad(int index);
int get_temp_count(void);
int get_label_count(void);

#endif 