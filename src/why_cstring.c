#include "why_cstring.h"

int_signed cstr_length(const char *string)
{
    char *iterator;

    if (!string)
        return 0;

    iterator = (char *)string;
    while (*iterator)
        iterator ++;
    
    return iterator - string;    
}

char *cstr_substring(const char *string, int_unsigned length)
{
    char *substring;

    substring = allocate(length + 1);
    substring = memory_copy(substring, string, length);
    substring[length] = '\0';

    return substring;
}

char *cstr_copy(const char *string)
{
    if (!string)
        return NULL;
    
    return cstr_substring(string, cstr_length(string));
}

void cstr_delete(char **string)
{
    free(*string);
    *string = NULL;
}

int_signed cstr_compare_length(const char *lhs, const char *rhs, int_signed length)
{
    int_signed n;

    if (!lhs && !rhs)
        return 0;
    
    if (!rhs)
        return *lhs;
    if (!lhs)
        return *rhs;

    n = 0;
    while (n < length)
    {
        if (lhs[n] != rhs[n])
            return rhs[n] - lhs[n];
        
        n ++;
    }

    return 0;
}

int_signed cstr_compare(const char *lhs, const char *rhs)
{
    if (!lhs && !rhs)
        return 0;
    
    if (!rhs)
        return *lhs;
    if (!lhs)
        return *rhs;
    
    while (*lhs == *rhs && *lhs)
    {
        lhs ++;
        rhs ++;
    }

    return *rhs - *lhs;
}

char *cstr_concat_length(const char *lhs, int_signed lhs_len, const char *rhs, int_signed rhs_len)
{
    int_signed total_len;
    char *new_str;

    total_len = rhs_len + lhs_len;

    new_str = allocate(total_len + 1);
    
    memory_copy(new_str, lhs, lhs_len);
    memory_copy(new_str + lhs_len, rhs, rhs_len);
    new_str[total_len] = 0;

    return new_str;
}

char *cstr_concat(const char *lhs, const char *rhs)
{
    int_signed lhs_len;
    int_signed rhs_len;

    lhs_len = cstr_length(lhs);
    rhs_len = cstr_length(rhs);

    return cstr_concat_length(lhs, lhs_len, rhs, rhs_len);
}

int_signed cstr_index_of(const char *string, char c)
{
    int_signed n;

    n = 0;
    while (string[n])
    {
        if (string[n] == c)
            return n;
        n ++;
    }

    return NOT_FOUND;
}
