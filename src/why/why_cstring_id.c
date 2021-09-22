#include "why_cstring.h"

static inline int_unsigned _is_between(char value, char left, char right)
{
    return value >= left && value <= right;
}

int_unsigned id_digit(const char* string)
{
    return _is_between(*string, '0', '9');
}

int_unsigned id_lower(const char* string)
{
    return _is_between(*string, 'a', 'z');
}

int_unsigned id_upper(const char* string)
{
    return _is_between(*string, 'A', 'Z');
}

int_unsigned id_alpha(const char* string)
{
    return id_lower(string) || id_upper(string);
}

int_unsigned id_alphanum(const char* string)
{
    return id_digit(string) || id_alpha(string);
}

int_unsigned id_whitespace(const char* string)
{
    return* string == ' ' ||* string == '\t';
}

int_unsigned id_digit_string(const char* string)
{
    char* pointer;

    pointer = (char* )string;
    while (*pointer && id_digit(pointer))
        pointer ++;

    return pointer - string;
}

int_unsigned id_unsigned(const char* string)
{
    char* pointer;

    if (!string || !*string)
        return 0;

    if (*string == '0' && !id_digit(string + 1))
        return 1;
    else if (*string == '0')
        return 0;
    
    pointer = (char* )string;
    while (*pointer && id_digit(pointer))
        pointer ++;
    
    return pointer - string;
}

int_unsigned id_int(const char* string)
{
    char* pointer;

    if (!string || !*string)
        return 0;

    pointer = (char* )string + 1;
    if (*string == '-' && id_digit(pointer))
        return 1 + id_unsigned(pointer);
    
    return id_unsigned(string);
}

int_unsigned id_float(const char* string)
{
    char* pointer;
    int_signed length;

    if (!string || !*string)
        return 0;

    pointer = (char* )string;
    pointer += id_int(string);

    if (pointer == string)
        return 0;
    
    if (*pointer == '.')
    {
        if (_is_between(*(pointer + 1), '0', '9'))
        {
            length = id_digit_string(pointer + 1);
            return (pointer - string) +  length + 1;
        }
        return 0;
    }
    else
        return 0;

    return pointer - string;
}

int_unsigned id_int_or_float(const char* string)
{
    int_unsigned length;

    length = id_float(string);
    if (length)
        return length;
    
    return id_int(string);
}

int_unsigned id_imaginary(const char* string)
{
    char* pointer;

    if (!string || !*string)
        return 0;

    pointer = (char* )string + id_int_or_float(string);
    if (*pointer == 'i')
        pointer ++;
    else
        return 0;
    
    return pointer - string;
}