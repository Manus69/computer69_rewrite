#ifndef FRONTEND_DECLARATIONS_H
#define FRONTEND_DECLARATIONS_H

#include "frontend_definitions.h"
#include "why_lib.h"

Number *number_new(String *string);
void number_delete(Number **number);

Operator *operator_new(String *string);
void operator_delete(Operator **operator);

MatrixRepr *matrix_repr_new(String *string);
void matrix_repr_delete(MatrixRepr **matrix);

Node *node_get_number(String *string);
Node *node_get_operator(String *string);
Node *node_get_undetermined(String *string);

int_unsigned id_identifier(const char *string);
int_signed find_matching_bracket(const char *string);

#endif