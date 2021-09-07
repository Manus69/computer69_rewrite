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
Number          *number_sqrt(const Number *number);
Number          *number_cos(const Number *number);
Number          *number_tan(const Number *number);
Number          *number_log(const Number *number);
Number          *number_ln(const Number *number);
Number          *number_exp(const Number *number);
Number          *number_abs(Number *number);
Number          *number_increment(Number *lhs, Number *rhs);
boolean         number_is_zero(const Number *number);
NUMBER_TYPE     number_get_type(const Number *number);
int_signed      number_get_int(const Number *number);
void            number_delete(Number **number);
Complex         number_to_complex(const Number *number);

//operator
Operator        *operator_new(String *string);
Operator        *operator_new_from_type(OPERATOR_TYPE type);
void            operator_delete(Operator **operator);
boolean         operator_is_binary(Operator *operator);
int_signed      operator_compare_precedence(Operator *lhs, Operator *rhs);
OPERATOR_TYPE   operator_get_type(const Operator *operator);
Operator        *operator_copy(const Operator *operator);

//matrix representation
MatrixRepr      *matrix_repr_new(void *(*copy)());
Vector          *matrix_row_new();
MatrixRepr      *matrix_repr_replace_wc(MatrixRepr *matrix, Computation *value);
Vector          *matrix_repr_get_row(const MatrixRepr *matrix, int_signed n);
boolean         matrix_repr_push(MatrixRepr *matrix, Entity *value);
int_signed      matrix_repr_n_cols(const MatrixRepr *matrix);
int_signed      matrix_repr_n_rows(const MatrixRepr *matrix);
void            matrix_repr_delete(MatrixRepr **matrix);
MatrixRepr      *matrix_repr_copy(const MatrixRepr *matrix);
Vector          *matrix_row_from_string(String *string, const VariableTable *v_table);
MatrixRepr      *matrix_repr_from_string(String *string, const VariableTable *v_table);
boolean         matrix_repr_equal_size(const MatrixRepr *lhs, const MatrixRepr *rhs);
Entity          *matrix_repr_at(const MatrixRepr *matrix, int_signed j, int_signed k);
Entity          *matrix_repr_nth(const MatrixRepr *matrix, int_signed n);
Entity          *matrix_repr_set_nth(MatrixRepr *matrix, Entity *value, int_signed n);
Entity          *matrix_repr_set(MatrixRepr *matrix, Entity *value, int_signed j, int_signed k);
boolean         matrix_repr_is_square(const MatrixRepr *matrix);
MatrixRepr      *matrix_repr_power(MatrixRepr *lhs, Number *number);
MatrixRepr      *matrix_repr_I(int_signed size);
MatrixRepr      *matrix_repr_new_fixed_size(int_signed n_rows, int_signed n_cols);
MatrixRepr      *matrix_repr_add(MatrixRepr *lhs, MatrixRepr *rhs);
MatrixRepr      *matrix_repr_subtract(MatrixRepr *lhs, MatrixRepr *rhs);
MatrixRepr      *matrix_repr_mult(MatrixRepr *lhs, MatrixRepr *rhs);
MatrixRepr      *matrix_repr_add_row(MatrixRepr *matrix, Vector *row);
MatrixRepr      *matrix_repr_scale(MatrixRepr *matrix, Number *number);

//node
Node            *node_new(void *data, NODE_TYPE type, boolean copy);
Node            *node_get_number(String *string);
Node            *node_get_operator(String *string);
Node            *node_get_identifier(String *string);
Node            *node_get_matrix(String *string, const VariableTable *v_table);
Node            *node_change_type(Node *node, NODE_TYPE type);
Node            *node_convert_to_wildcard(Node *node);
Node            *node_convert_to_bft(Node *node);
Node            *node_copy(const Node *node);
NODE_TYPE       node_get_type(const Node *node);
void            node_delete(Node **node);

//computation
Computation     *computation_new(Node *node, boolean copy);
Computation     *computation_copy(const Computation *computation);
void            *computation_copy_wrapper(Computation *computation);
Computation     *computation_insert_root(Computation *root, Computation *new_root);
Computation     *computation_swap_root(Computation *root, Computation *new_root);
Computation     *computation_get_lhs(const Computation *computation);
Computation     *computation_get_rhs(const Computation *computation);
Computation     *computation_replace_wc(Computation *_computation, Computation *value);
Computation     *computation_resolve(Computation *computation, const char *wc_identifier, const VariableTable *v_table);
void            computation_traverse(Computation *computation, void (*function)());
Node            *computation_get_node(const Computation *computation);
void            computation_delete(Computation **computation);
Number          *computation_eval(const Computation *computation, const VariableTable *v_table, Number *wc_value);
Entity          *computation_evalG(const Computation *computation, const VariableTable *v_table, Entity *wc_value);
Computation     *computation_add(Computation *lhs, Computation *rhs);
Computation     *computation_mult(Computation *lhs, Computation *rhs);
Computation     *computation_subtract(Computation *lhs, Computation *rhs);
Computation     *computation_divide(Computation *lhs, Computation *rhs);
Computation     *computation_mod(Computation *lhs, Computation *rhs);
Computation     *computation_power(Computation *lhs, Computation *rhs);
Computation     *computation_factorial(Computation *lhs, Computation *rhs);
Computation     *computation_increment(Computation *lhs, Computation *rhs);
Computation     *computation_scale(Computation *computation, Number *number);
Polynomial      *computation_to_polynomial(const Computation *_computation);

//entity
Entity          *entity_new(const void *stuff, ENTITY_TYPE type);
void            entity_delete(Entity **entity);
ENTITY_TYPE     entity_get_type(const Entity *entity);
void            *entity_copy_wrapper(const Entity *entity);
Entity          *entity_copy(const Entity *entity);
Entity          *entity_new_from_computation(const Computation *computation, boolean copy);
Entity          *entity_new_from_number(const Number *number, boolean copy);
Entity          *entity_new_from_matrix(const MatrixRepr *matrix, boolean copy);
Entity          *entity_add(Entity *lhs, Entity *rhs);
Entity          *entity_mult(Entity *lhs, Entity *rhs);
Entity          *entity_subtract(Entity *lhs, Entity *rhs);
Entity          *entity_divide(Entity *lhs, Entity *rhs);
Entity          *entity_mod(Entity *lhs, Entity *rhs);
Entity          *entity_power(Entity *lhs, Entity *rhs);
Entity          *entity_increment(Entity *lhs, Entity *rhs);
Entity          *entity_factorial(Entity *lhs, Entity *rhs);
Computation     *computation_from_entity(Entity *entity, boolean copy);

//variable
Variable        *variable_new(char *name, Entity *entity, boolean parametrized, boolean copy);
VARIABLE_TYPE   variable_get_type(const Variable *variable);
int_signed      variable_compare(const Variable *lhs, const Variable *rhs);
Entity          *variable_get_value(const Variable *variable);
char            *variable_get_name(const Variable *variable);
void            variable_delete(Variable **variable);
Variable        *variable_create_from_string(String *string, const VariableTable *v_table);
Variable        *variable_copy(const Variable *variable);
Variable        *variable_assign(Variable *variable, Entity *value, boolean copy);
Variable        *variable_create_named(String *string, const VariableTable *v_table, char *name);
boolean         variable_is_parametrized(const Variable *variable);


//variable table
VariableTable   *v_table_new(const Variable *variable);
void            v_table_delete(VariableTable **v_table);
int_signed      match_variable(const Variable *variable, const char *name);
Variable        *v_table_search(const VariableTable *v_table, const char *name);
VariableTable   *v_table_insert(VariableTable *v_table, const Variable *variable);
VariableTable   *v_table_insert_report(VariableTable *v_table, const Variable *variable);

//parser
Computation     *parse(String *string, const VariableTable *v_table);
Computation     *_parse(String *string, const VariableTable *v_table); // get rid of one of these later

//input
VariableTable   *process_input_line(String *line, VariableTable *v_table);
boolean         id_assignment(const String *string);
boolean         id_evaluation(const String *string);
boolean         id_find_roots(const String *string);
boolean         id_statement(const String *string);
boolean         id_display(const String *string, const VariableTable *v_table);

//support
int_unsigned    id_identifier(const char *string);
int_unsigned    id_function_name(const char *string);
int_unsigned    id_identifier_str(const String *string);
int_unsigned    id_function_name_str(const String *string);
int_unsigned    id_row(const String *string);
int_unsigned    id_matrix(const String *string);
int_signed      find_matching_bracket(const char *string, char o_symbol, char c_symbol);
int_signed      find_matching_bracket_str(const String *string, char o_symbol, char c_symbol);
String          *string_new_no_space_to_lower(const char *characters);
String          *string_new_trimmed(const char *characters);
Vector          *string_split_and_trim(String *string, char delimiter);
boolean         is_pi(const char *string);
boolean         is_e(const char *string);
char            *check_reserved_symbols(const char *string);
void            *get_bft_pointer(BULITIN_FUNCTION_TYPE type);
void            skip_over_equals(String *string);

void            main_loop();

#endif