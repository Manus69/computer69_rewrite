#include "number.h"
#include "why_memory.h"
#include "why_string_interface.h"
#include "why_conversion.h"
#include "why_cstring.h"
#include "data_interface.h"

Number* number_new_int(int_signed n)
{
    Number* number;

    number = allocate(sizeof(Number));
    number->n = n;
    number->type = NT_INT;

    data_add_pointer(data, number, sizeof(Number));

    return number;
}

Number* number_new_int_str(const char* string)
{
    int_signed n;

    n = convert_to_int(string);

    return number_new_int(n);
}

Number* number_new_real(real x)
{
    Number* number;

    number = allocate(sizeof(Number));
    number->x = x;
    number->type = NT_REAL;

    data_add_pointer(data, number, sizeof(Number));

    return number;
}

Number* number_new_real_str(const char* string)
{
    real x;

    x = convert_to_real(string);

    return number_new_real(x);
}

Number* number_new_complex(Complex z)
{
    Number* number;

    number = allocate(sizeof(Number));
    number->z = z;
    number->type = NT_COMPLEX;

    data_add_pointer(data, number, sizeof(Number));

    return number;
}

Number* number_new_complex_str(const char* string)
{
    Complex z;

    z = convert_to_complex(string);

    return number_new_complex(z);
}

Number* number_promote(Number* number, NUMBER_TYPE type)
{
    Complex z;

    if (!number)
        return NULL;

    if (type <= number->type)
        return number;
    else if (type == NT_REAL)
    {
        number->x = number->n;
    }
    else if (type == NT_COMPLEX)
    {
        z = number->type == NT_INT ? complex(number->n, 0) : complex(number->x, 0);
        number->z = z;
    }
    number->type = type;

    return number;
}

Number* number_demote_if_possible(Number* number)
{
    if (!number)
        return NULL;

    if (number->type == NT_INT)
        return number;

    if (number->type == NT_REAL)
    {
        if (number->x == (int_signed)number->x)
        {
            number->n = number->x;
            number->type = NT_INT;
        }
    }
    else if (number->type == NT_COMPLEX)
    {
        if (complex_is_real(number->z))
        {
            number->x = number->z.re;
            number->type = NT_REAL;

            return number_demote_if_possible(number);
        }
    }

    return number;
}

boolean number_is_zero(const Number* number)
{
    if (!number)
        return FALSE;
    
    if (number->type == NT_INT)
        return number->n == 0;
    else if (number->type == NT_REAL)
        return number->x == 0;
    else
        return complex_is_zero(number->z);
}

NUMBER_TYPE number_get_type(const Number* number)
{
    return number->type;
}

int_signed number_get_int(const Number* number)
{
    return number->n;
}

Number* number_from_string(String* string)
{
    char*       literal;
    int_signed  length;

    if (string_length(string) == 0)
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

Number* number_copy(const Number* number)
{
    Number* copy;

    copy = allocate(sizeof(Number));
    copy = memory_copy(copy, number, sizeof(Number));

    data_add_pointer(data, copy, sizeof(Number));

    return copy;
}

Complex number_to_complex(const Number* number)
{
    if (number->type == NT_COMPLEX)
        return number->z;
    
    if (number->type == NT_REAL)
        return complex(number->x, 0);
    
    return complex(number->n, 0);
}

void number_delete(Number** number)
{
    #if NO_DELETE
        return ;
    #endif

    if (!number || !*number)
        return ;

    free(*number);
    *number = NULL;
}