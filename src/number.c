#include "number.h"
#include "why_memory.h"
#include "why_string_interface.h"
#include "why_conversion.h"
#include "why_cstring.h"

Number *number_new_int(int_signed n)
{
    Number *number;

    number = allocate(sizeof(Number));
    number->n = n;
    number->type = NT_INT;

    return number;
}

Number *number_new_int_str(const char *string)
{
    int_signed n;

    n = convert_to_int(string);

    return number_new_int(n);
}

Number *number_new_real(real x)
{
    Number *number;

    number = allocate(sizeof(Number));
    number->x = x;
    number->type = NT_REAL;

    return number;
}

Number *number_new_real_str(const char *string)
{
    real x;

    x = convert_to_real(string);

    return number_new_real(x);
}

Number *number_new_complex(Complex z)
{
    Number *number;

    number = allocate(sizeof(Number));
    number->z = z;
    number->type = NT_COMPLEX;

    return number;
}

Number *number_new_complex_str(const char *string)
{
    Complex z;

    z = convert_to_complex(string);

    return number_new_complex(z);
}

Number *number_new(String *string)
{
    int_signed length;
    char *literal;

    if (string_get_length(string) == 0)
        return NULL;

    literal = string_get_characters(string);
    length = id_imaginary(literal);
    if (length)
    {
        _string_shift(string, length);

        return number_new_complex_str(literal);
    }

    length = id_float(literal);
    if (length)
    {
        _string_shift(string, length);

        return number_new_real_str(literal);
    }

    length = id_int(literal);
    if (length)
    {
        _string_shift(string, length);

        return number_new_int_str(literal);
    }

    return NULL;
}

void number_delete(Number **number)
{
    if (!number || !*number)
        return ;

    free(*number);
    *number = NULL;
}