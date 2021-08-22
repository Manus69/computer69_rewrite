#ifndef TEST_H
#define TEST_H

extern const char *valid_basic_strings[];
extern const char *valid_matrix_strings[];
extern const char *valid_id_strings[];

void test_syntax(const char **strings);
void computation_test_basic(const char **strings);

#endif