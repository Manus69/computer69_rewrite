#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>

#include "frontend_definitions.h"
#include "why_print.h"

#define WC_SYMBOL "_"

void print_number(const Number *number);
void print_computation(const Computation *computation);
void print_variable(const Variable *variable);
void print_v_table(const VariableTable *v_table);
void print_matrix_row(const MatrixRepr *matrix, int_signed j);
void print_matrix_repr(const MatrixRepr *matrix);
void print_entity(const Entity *entity);

#endif