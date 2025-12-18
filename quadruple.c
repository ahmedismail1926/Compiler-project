#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadruple.h"

/* ===== PHASE 2: Quadruple Table ===== */
#define MAX_QUADS 1000

static Quadruple quad_table[MAX_QUADS];
static int quad_index = 0;

/*  Initialize quadruple table */
void init_quadruples() {
    quad_index = 0;
}

/*  Generate a new quadruple*/
void gen_quad(const char* op, const char* arg1,
            const char* arg2, const char* result) {

    if (quad_index >= MAX_QUADS) {
        fprintf(stderr, "Semantic Error: Quadruple table overflow\n");
        return;
    }

    /* Safe string copy */
    snprintf(quad_table[quad_index].op,
            sizeof(quad_table[quad_index].op),
            "%s", op);

    snprintf(quad_table[quad_index].arg1,
            sizeof(quad_table[quad_index].arg1),
            "%s", arg1);

    snprintf(quad_table[quad_index].arg2,
            sizeof(quad_table[quad_index].arg2),
            "%s", arg2);

    snprintf(quad_table[quad_index].result,
            sizeof(quad_table[quad_index].result),
            "%s", result);

    quad_index++;
}

/*  Print quadruples  */
void print_quadruples() {
    int i;

    printf("\n===== QUADRUPLES =====\n");
    printf("%-5s %-10s %-10s %-10s %-10s\n",
        "#", "OP", "ARG1", "ARG2", "RESULT");

    for (i = 0; i < quad_index; i++) {
        printf("%-5d %-10s %-10s %-10s %-10s\n",
            i,
            quad_table[i].op,
            quad_table[i].arg1,
            quad_table[i].arg2,
            quad_table[i].result);
    }
}
