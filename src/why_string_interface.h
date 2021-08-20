#ifndef WHY_STRING_INTERFACE_H
#define WHY_STRING_INTERFACE_H

#include "why_definitions.h"

typedef struct String String;

void        _string_init(String *string, const char *literal, int_signed length, unsigned char allocated);
void        _string_init_copy(String *lhs, const String *rhs);
char        string_at(const String *string, int_signed n);
char        *string_get_characters(const String *string);
int_signed  _string_shift(String *string, int_signed shift);
int_signed  string_get_length(const String *string);
int_signed  string_compare(const String *lhs, const String *rhs);
boolean     string_is_identical(const String *lhs, const String *rhs);
String      *string_new_fixed_length(const char *literal, int_signed length);
String      *string_new(const char *literal);
String      *string_new_allocated_fl(const char *literal, int_signed length);
String      *string_new_allocated(const char *literal);
String      *string_append_literal(String *string, const char *rhs);
String      *string_append_string(String *string, const String *rhs);
String      *string_copy_shallow(const String *string);
String      *string_copy_semideep(const String *string);
String      *string_copy_deep(const String *string);
String      *string_get_substring(const String *string, int_signed left_index, int_signed length);
String      *string_get_substring_from(const String *string, int_signed length);
String      *string_remove_spaces(String *string);
String      *string_substitute_chars(String *string, const char *set, char replacement);
void        string_delete(String **string);

//search
int_signed string_index_of_predicate(const String *string, int_signed start, char c, boolean (*predicate)(char, char));
int_signed string_index_of_from(const String *string, int_signed start, char c);
int_signed string_index_of(const String *string, char c);
int_signed string_index_of_compliment_from(const String *string, int_signed start, char c);
int_signed string_index_of_any(const String *string, char *characters);
int_signed string_find(const String *haystack, const String *needle);
int_signed string_find_literal(const String *haystack, const char *needle);

#endif