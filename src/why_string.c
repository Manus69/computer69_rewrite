#include "why_string.h"
#include "why_string_interface.h"
#include "why_memory.h"
#include "why_cstring.h"

void _string_init(String *string, const char *literal, int_signed length, unsigned char allocated)
{
    string->characters = (char *)literal;
    string->pointer = string->characters;
    string->length = length;
    string->allocated = allocated;
}

void _string_init_copy(String *lhs, const String *rhs)
{
    lhs->characters = (char *)rhs->characters;
    lhs->pointer = lhs->characters;
    lhs->length = rhs->length;
    lhs->allocated = FALSE;
}

int_signed _string_shift(String *string, int_signed shift)
{
    if (string->length < shift)
        shift = string->length;
    
    string->characters += shift;
    string->length -= shift;

    return shift;
}

String *string_new_fixed_length(const char *literal, int_signed length)
{
    String *string;

    string = allocate(sizeof(String));
    
    _string_init(string, literal, length, FALSE);

    return string;
}

String *string_new(const char *literal)
{
    int_signed length;

    length = cstr_length(literal);

    if (length < 0)
        return NULL;

    return string_new_fixed_length(literal, length);
}

String *string_new_allocated_fl(const char *literal, int_signed length)
{
    String *string;
    char *characters;

    string = allocate(sizeof(String));

    characters = allocate(length + 1);

    characters = memory_copy(characters, literal, length);
    characters[length] = 0;

    _string_init(string, characters, length, TRUE);

    return string;
}

String *string_new_allocated(const char *literal)
{
    int_signed length;

    length = cstr_length(literal);

    return string_new_allocated_fl(literal, length);
}

char string_at(const String *string, int_signed n)
{
    return string->characters[n];
}

char *string_get_characters(const String *string)
{
    return string->characters;
}

int_signed string_get_length(const String *string)
{
    return string->length;
}

void string_delete(String **string)
{
    if (!string || !*string)
        return ;
    if ((*string)->allocated)
        free((*string)->pointer);

    free(*string);
    *string = NULL;
}

static String *_append_literal(String *string, const char *rhs, int_signed length)
{
    char *new_characters;

    new_characters = cstr_concat_length(string->characters, string->length, rhs, length);
    if (!new_characters)
        return string;
    
    if (string->allocated)
        free(string->characters);
    
    _string_init(string, new_characters, string->length + length, TRUE);

    return string;
}

String *string_append_literal(String *string, const char *rhs)
{
    int_signed length;

    length = cstr_length(rhs);
    if (!length)
        return string;

    return _append_literal(string, rhs, length);
}

String *string_append_string(String *string, const String *rhs)
{
    if (!rhs)
        return string;
    
    return _append_literal(string, rhs->characters, rhs->length);
}

String *string_copy_shallow(const String *string)
{
    return (String *)string;
}

String *string_copy_semideep(const String *string)
{
    if (!string)
        return NULL;

    return string_new_fixed_length(string->characters, string->length);
}

String *string_copy_deep(const String *string)
{
    String *string_copy;
    char *copy;

    if (!string)
        return NULL;

    copy = cstr_copy(string->characters);
    if (!copy)
        return NULL;

    string_copy = string_new_fixed_length(copy, string->length);
    string_copy->allocated = TRUE;

    return string_copy;
}

int_signed string_compare(const String *lhs, const String *rhs)
{
    return cstr_compare(lhs->characters, rhs->characters);
}

boolean string_is_identical(const String *lhs, const String *rhs)
{
    if (lhs->length != rhs->length)
        return FALSE;

    return (string_compare(lhs, rhs) == 0) ? TRUE : FALSE;
}

String *string_get_substring(const String *string, int_signed left_index, int_signed length)
{
    char *pointer;

    pointer = string->characters + left_index;

    return string_new_fixed_length(pointer, length);
}

String *string_get_substring_from(const String *string, int_signed left_index)
{
    if (string->length <= left_index)
        return NULL;

    return string_get_substring(string, left_index, string->length - left_index);
}

static inline void _insert(char *string, int_signed n, char c)
{
    if (c)
        string[n] = c;
}

String *string_substitute_chars(String *string, const char *set, char replacement)
{
    char *new_characters;
    char *characters;
    int_signed n;
    int_signed index;

    new_characters = memory_zero(string->length + 1);
    characters = string_get_characters(string);
    n = 0;
    while (*characters)
    {
        index = cstr_index_of(set, *characters);
        if (index != NOT_FOUND)
        {
            new_characters[n] = replacement;
            if (replacement)
                n ++;
        }
        else
        {
            new_characters[n] = *characters;
            n ++;
        }
        characters ++;
    }

    _string_init(string, new_characters, n, TRUE);
    
    return string;
}

String *string_remove_spaces(String *string)
{
    return string_substitute_chars(string, " \t", 0);
}