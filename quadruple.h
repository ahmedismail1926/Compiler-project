#ifndef QUADRUPLE_H
#define QUADRUPLE_H


typedef struct {
    char op[10];      // operation
    char arg1[20];    // first operand
    char arg2[20];    // second operand
    char result[20];  // result
} Quadruple;


void init_quadruples();
void gen_quad(const char* op, const char* arg1,
            const char* arg2, const char* result);
void print_quadruples();

#endif

