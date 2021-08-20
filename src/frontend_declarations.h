#ifndef FRONTEND_DECLARATIONS_H
#define FRONTEND_DECLARATIONS_H

#include "frontend_definitions.h"
#include "why_lib.h"

Number *number_new(String *string);
void number_delete(Number **number);

Operator *operator_new(String *string);
void operator_delete(Operator **operator);
boolean operator_is_binary(Operator *operator);
int_signed operator_compare_precedence(Operator *lhs, Operator *rhs);
OPERATOR_TYPE operator_get_type(const Operator *operator);

MatrixRepr *matrix_repr_new(String *string);
void matrix_repr_delete(MatrixRepr **matrix);

Node *node_get_number(String *string);
Node *node_get_operator(String *string);
Node *node_get_identifier(String *string);
Node *node_change_type(Node *node, NODE_TYPE type);
NODE_TYPE node_get_type(const Node *node);
void node_delete(Node **node);

Computation *computation_new(Node *node);
Computation *computation_insert_root(Computation *root, Computation *new_root);
Computation *computation_swap_root(Computation *root, Computation *new_root);
Computation *computation_get_lhs(const Computation *computation);
Computation *computation_get_rhs(const Computation *computation);
Node *computation_get_node(const Computation *computation);
void computation_delete(Computation **computation);

int_unsigned id_identifier(const char *string);
int_unsigned id_function_name(const char *string);
int_unsigned id_identifier_str(const String *string);
int_unsigned id_function_name_str(const String *string);
int_signed find_matching_bracket(const char *string);
int_signed find_matching_bracket_str(const String *string);
String *string_new_no_space(const char *characters);

Computation *parse(String *string);

#endif