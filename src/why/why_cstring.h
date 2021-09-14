#ifndef WHY_CSTRING_H
#define WHY_CSTRING_H

#include "why_memory.h"

int_signed      cstr_length(const char *string);
int_signed      cstr_compare(const char *lhs, const char *rhs);
int_signed      cstr_compare_length(const char *lhs, const char *rhs, int_signed length);
int_signed      cstr_index_of(const char *string, char c);
int_signed      cstr_index_of_any(const char *string, const char *set);
char            *cstr_substring(const char *string, int_unsigned length);
char            *cstr_copy(const char *string);
char            *cstr_concat_length(const char *lhs, int_signed lhs_len, const char *rhs, int_signed rhs_len);
char            *cstr_concat(const char *lhs, const char *rhs);
void            cstr_delete(char **string);
void            cstr_to_lower(char *string);
char            cstr_char_to_lower(char c);
char            *cstr_trim(const char *string);
boolean         cstr_starts_with(const char * restrict string, const char * restrict start);

int_unsigned    id_digit(const char *string);
int_unsigned    id_lower(const char *string);
int_unsigned    id_upper(const char *string);
int_unsigned    id_alpha(const char *string);
int_unsigned    id_alphanum(const char *string);
int_unsigned    id_unsigned(const char *string);
int_unsigned    id_whitespace(const char *string);
int_unsigned    id_digit_string(const char *string);
int_unsigned    id_int(const char *string);
int_unsigned    id_float(const char *string);
int_unsigned    id_imaginary(const char *string);
int_unsigned    id_int_or_float(const char *string);

#endif