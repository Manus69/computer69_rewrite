#ifndef TEST_H
#define TEST_H

#include <math.h>

#define SEQUENCE_LENGTH 10

extern const char *invalid_strings[];
extern const char *context_dependent_strings[];
extern const char *valid_basic_strings[];
extern const char *valid_matrix_strings[];
extern const char *valid_id_strings[];
extern const char *valid_ass_strings[];
extern const char *valid_sequence_basic[];
extern const char *valid_sequence[];
extern const char *valid_sequences[][SEQUENCE_LENGTH];
extern const char *valid_matrix_sequences[][SEQUENCE_LENGTH];
extern const char *valid_polynomial_sequences[][SEQUENCE_LENGTH];

void test_statement(const char *characters);
void test_sequence(const char **strings);
void test_all_sequences(const char *array[][SEQUENCE_LENGTH]);
void test_all_statements(const char **strings);
void sqrt_test(real initial_value, real step, real terminal_value);
void log_test(real initial_value, real step, real terminal_value);
void exp_test(real initial_value, real step, real terminal_value);
void math_test();

MatrixRepr *generate_random_matrix(int_signed n_rows, int_signed n_cols, NUMBER_TYPE type);

#endif