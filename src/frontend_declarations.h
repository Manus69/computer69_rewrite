#ifndef FRONTEND_DECLARATIONS_H
#define FRONTEND_DECLARATIONS_H

#include "frontend_definitions.h"
#include "why_lib.h"

extern const char *FUNCTION_STRINGS[];

//number
Number          *number_new_int(int_signed n);
Number          *number_new_real(real x);
Number          *number_new_complex(Complex z);
Number          *number_from_string(String *string);
Number          *number_copy(const Number *number);
Number          *number_promote(Number *number, NUMBER_TYPE type);
Number          *number_demote_if_possible(Number *number);
Number          *number_add(Number *lhs, Number *rhs);
Number          *number_mult(Number *lhs, Number *rhs);
Number          *number_subtract(Number *lhs, Number *rhs);
Number          *number_divide(Number *lhs, Number *rhs);
Number          *number_mod(Number *lhs, Number *rhs);
Number          *number_power(Number *lhs, Number *rhs);
Number          *number_factorial(Number *lhs, const Number *rhs);
Number          *number_scale(Number *number, real factor);
Number          *number_sin(const Number *number);
Number          *number_cos(const Number *number);
Number          *number_tan(const Number *number);
Number          *number_log(const Number *number);
Number          *number_abs(Number *number);
boolean         number_is_zero(const Number *number);
void            number_delete(Number **number);

//operator
Operator        *operator_new(String *string);
void            operator_delete(Operator **operator);
boolean         operator_is_binary(Operator *operator);
int_signed      operator_compare_precedence(Operator *lhs, Operator *rhs);
OPERATOR_TYPE   operator_get_type(const Operator *operator);
Operator        *operator_copy(const Operator *operator);

//matrix representation
MatrixRepr      *matrix_repr_new();
Vector          *matrix_repr_get_row(const MatrixRepr *matrix, int_signed n);
int_signed      matrix_repr_size(const MatrixRepr *matrix);
void            matrix_repr_delete(MatrixRepr **matrix);
MatrixRepr      *matrix_repr_copy(const MatrixRepr *matrix);
Vector          *matrix_row_from_string(String *string, const VariableTable *v_table);
MatrixRepr      *matrix_repr_from_string(String *string, const VariableTable *v_table);

//node
Node            *node_new(void *data, NODE_TYPE type);
Node            *node_get_number(String *string);
Node            *node_get_operator(String *string);
Node            *node_get_identifier(String *string);
Node *node_get_matrix(String *string, const VariableTable *v_table);
Node            *node_change_type(Node *node, NODE_TYPE type);
Node            *node_convert_to_wildcard(Node *node);
Node            *node_convert_to_bft(Node *node);
Node            *node_copy(const Node *node);
NODE_TYPE       node_get_type(const Node *node);
void            node_delete(Node **node);

//computation
Computation     *computation_new(Node *node);
Computation     *computation_copy(const Computation *computation);
Computation     *computation_insert_root(Computation *root, Computation *new_root);
Computation     *computation_swap_root(Computation *root, Computation *new_root);
Computation     *computation_get_lhs(const Computation *computation);
Computation     *computation_get_rhs(const Computation *computation);
Computation     *computation_resolve(Computation *computation, const String *wc_identifier, const VariableTable *v_table);
void            computation_traverse(Computation *computation, void (*function)());
Node            *computation_get_node(const Computation *computation);
void            computation_delete(Computation **computation);
Number          *computation_eval(const Computation *computation, const VariableTable *v_table, Number *wc_value);

//variable
Variable        *variable_new(String *name, Computation *value, VARIABLE_TYPE type);
int_signed      variable_compare(const Variable *lhs, const Variable *rhs);
Computation     *variable_get_value(const Variable *variable);
String          *variable_get_name(const Variable *variable);
void            variable_delete(Variable **variable);
Variable        *variable_create_from_string(String *string, const VariableTable *v_table);
Variable        *variable_copy(const Variable *variable);
Variable        *variable_assign(Variable *variable, const Computation *value);
Variable        *variable_create_with_name(String *string, const VariableTable *v_table, String *name);

//variable table
VariableTable   *v_table_new(const Variable *variable);
void            v_table_delete(VariableTable **v_table);
int_signed      match_variable(const Variable *variable, const String *name);
Variable        *v_table_search(const VariableTable *v_table, const String *name);
VariableTable   *v_table_insert(VariableTable *v_table, const Variable *variable);
boolean         v_table_insert_report(VariableTable *v_table, const Variable *variable);

//parser
Computation     *parse(String *string, const VariableTable *v_table);
Computation     *_parse(String *string, const VariableTable *v_table); // get rid of one of these later

//support
int_unsigned    id_identifier(const char *string);
int_unsigned    id_function_name(const char *string);
int_unsigned    id_identifier_str(const String *string);
int_unsigned    id_function_name_str(const String *string);
int_signed      find_matching_bracket(const char *string, char o_symbol, char c_symbol);
int_signed      find_matching_bracket_str(const String *string, char o_symbol, char c_symbol);
String          *string_new_no_space(const char *characters);

boolean         id_assignment(const String *string);
boolean         id_evaluation(const String *string);
boolean         id_find_roots(const String *string);

char *check_reserved_symbols(const String *string);
void *get_bft_pointer(BULITIN_FUNCTION_TYPE type);


#endif