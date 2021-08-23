#ifndef TEST_H
#define TEST_H

#define SEQUENCE_LENGTH 5

extern const char *valid_basic_strings[];
extern const char *valid_matrix_strings[];
extern const char *valid_id_strings[];
extern const char *valid_ass_strings[];
extern const char *valid_sequence_basic[];
extern const char *valid_sequence[];
extern const char *valid_sequences[][SEQUENCE_LENGTH];

void test_syntax(const char **strings);
void test_computation(const char **strings);
void test_assignment(const char **strings);
void test_sequence(const char **strings);
void test_all_sequences(const char *array[][SEQUENCE_LENGTH]);

#endif