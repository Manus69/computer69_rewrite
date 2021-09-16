#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>

#include "frontend_definitions.h"
#include "why_print.h"

#define WC_SYMBOL "_"

void print_number(const Number *number);
void print_operator(const Operator *operator);
void print_node(const Node *node, const char *wc_symbol);
void print_computation(const Computation *computation, const char *wc_symbol);
void print_computationDBG(const Computation *computation, const char *wc_symbol);
void print_variable_verbose(const Variable *variable, const char *wc_symbol);
void print_variable(const Variable *variable);
void print_variableN(const Variable *variable);
void print_variableNI(const Variable *variable);
void print_v_table(const VariableTable *v_table);
void print_matrix_row(const MatrixRepr *matrix, int_signed j, const char *wc_symbol);
void print_matrix_repr(const MatrixRepr *matrix, const char *wc_symbol);
void print_matrix_reprL(const MatrixRepr *matrix, const char *wc_symbol);
void print_entity(const Entity *entity, const char *wc_symbol);
void print_roots(const Vector *roots);
void print_root_messageAR();
void print_root_messageNR();

#endif