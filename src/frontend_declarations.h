#ifndef FRONTEND_DECLARATIONS_H
#define FRONTEND_DECLARATIONS_H

#include "frontend_definitions.h"
#include "why_lib.h"

//number
Number          *number_new_int(int_signed n);
Number          *number_new_real(real x);
Number          *number_new_complex(Complex z);
Number          *number_new(String *string);
Number          *number_copy(const Number *number);
Number          *number_promote(Number *number, NUMBER_TYPE type);
Number          *number_add(Number *lhs, Number *rhs);
Number          *number_mult(Number *lhs, Number *rhs);
Number          *number_subtract(Number *lhs, Number *rhs);
Number          *number_divide(Number *lhs, Number *rhs);
Number          *number_mod(Number *lhs, Number *rhs);
Number          *number_power(Number *lhs, Number *rhs);
Number          *number_factorial(Number *lhs, const Number *rhs);
Number          *number_scale(Number *number, real factor);
Number          *number_add_in_situ(Number *lhs, Number *rhs);
boolean         number_is_zero(const Number *number);
void            number_delete(Number **number);

//operator
Operator        *operator_new(String *string);
void            operator_delete(Operator **operator);
boolean         operator_is_binary(Operator *operator);
int_signed      operator_compare_precedence(Operator *lhs, Operator *rhs);
OPERATOR_TYPE   operator_get_type(const Operator *operator);

//matrix representation
MatrixRepr      *matrix_repr_new(String *string);
void            matrix_repr_delete(MatrixRepr **matrix);

//node
Node            *node_new(void *data, NODE_TYPE type);
Node            *node_get_number(String *string);
Node            *node_get_operator(String *string);
Node            *node_get_identifier(String *string);
Node            *node_change_type(Node *node, NODE_TYPE type);
Node            *node_convert_to_wildcard(Node *node);
NODE_TYPE       node_get_type(const Node *node);
void            node_delete(Node **node);

//computation
Computation     *computation_new(Node *node);
Computation     *computation_insert_root(Computation *root, Computation *new_root);
Computation     *computation_swap_root(Computation *root, Computation *new_root);
Computation     *computation_get_lhs(const Computation *computation);
Computation     *computation_get_rhs(const Computation *computation);
Computation     *computation_resolve(Computation *computation, const String *wc_identifier, VariableTable *v_table);
void            computation_traverse(Computation *computation, void (*function)());
Node            *computation_get_node(const Computation *computation);
void            computation_delete(Computation **computation);
Number          *computation_eval(const Computation *computation);

//variable
Variable        *variable_new(String *name, Computation *value, VARIABLE_TYPE type);
int_signed      variable_compare(const Variable *lhs, const Variable *rhs);
Computation     *variable_get_value(const Variable *variable);
void            variable_delete(Variable **variable);
Variable        *variable_create_from_string(String *string, VariableTable *v_table);

//variable table
VariableTable   *v_table_new(const Variable *variable);
void            v_table_delete(VariableTable **v_table);
int_signed      match_variable(const Variable *variable, const String *name);
Variable        *v_table_search(const VariableTable *v_table, const String *name);
VariableTable   *v_table_insert(VariableTable *v_table, Variable *variable);

//parser
Computation     *parse(String *string);
Computation     *_parse(String *string); // get rid of one of these later

//support
int_unsigned    id_identifier(const char *string);
int_unsigned    id_function_name(const char *string);
int_unsigned    id_identifier_str(const String *string);
int_unsigned    id_function_name_str(const String *string);
int_signed      find_matching_bracket(const char *string);
int_signed      find_matching_bracket_str(const String *string);
String          *string_new_no_space(const char *characters);

boolean id_assignment(const String *string);
boolean id_evaluation(const String *string);
boolean id_find_roots(const String *string);


#endif