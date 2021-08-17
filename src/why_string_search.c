#include "why_string.h"
#include "why_string_interface.h"

static inline boolean _id_char(char lhs, char rhs)
{
    return lhs == rhs;
}

static inline boolean _not_id_char(char lhs, char rhs)
{
    return !_id_char(lhs, rhs);
}

int_signed string_index_of_predicate(const String *string, int_signed start, char c, boolean (*predicate)(char, char))
{
    int_signed n;

    if (start >= string->length)
        return NOT_FOUND;

    n = start;
    while (n < string->length)
    {
        if (predicate(string->characters[n], c))
            return n;
        n ++;
    }

    return NOT_FOUND;
}

int_signed string_index_of_from(const String *string, int_signed start, char c)
{
    return string_index_of_predicate(string, start, c, _id_char);
}

int_signed string_index_of(const String *string, char c)
{
    return string_index_of_from(string, 0, c);
}

int_signed string_index_of_compliment_from(const String *string, int_signed start, char c)
{
    return string_index_of_predicate(string, start, c, _not_id_char);
}

static int_signed _string_find_from(const String *haystack, const String *needle, int_signed start)
{
    int_signed next_index;
    int_signed n;

    if (haystack->length < needle->length + start)
        return NOT_FOUND;

    if (haystack->characters[start + needle->length - 1] != needle->characters[needle->length - 1])
        return _string_find_from(haystack, needle, start + 1);

    n = 0;
    next_index = NOT_FOUND;
    while (haystack->characters[start + n] == needle->characters[n])
    {
        if (!needle->characters[n])
            return start;
        if (haystack->characters[start + n] == needle->characters[0])
            next_index = start + n; //is this wrong?
        n ++;
    }
    if (!needle->characters[n])
        return start;
    if (next_index == NOT_FOUND || next_index == start)
        next_index = string_index_of_from(haystack, start + n, needle->characters[0]);

    return _string_find_from(haystack, needle, next_index);
}

int_signed string_find(const String *haystack, const String *needle)
{
    if (!needle)
        return NOT_FOUND;
    
    if (needle->length > haystack->length)
        return NOT_FOUND;

    if (needle->length == 0)
        return 0;

    return _string_find_from(haystack, needle, 0);
}

int_signed string_find_literal(const String *haystack, const char *needle)
{
    String *string;
    int_signed n;

    string = string_new(needle);

    n = string_find(haystack, string);
    string_delete(&string);

    return n;
}