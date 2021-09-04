#include "why_conversion.h"
#include "why_cstring.h"
#include "why_error.h"

#include <assert.h>

static real _convert_decimal_part(const char *string, int_signed length)
{
    real result;
    char c;

    result = 0;
    while (length)
    {
        c = string[length - 1];
        result = result / 10 + (c - '0') / 10.0;
        length --;
    }

    return result;
}

static real _convert_int_part(const char *string, int_signed length)
{
    real result;    

    result = 0;
    while (length)
    {
        result = result * 10 + *string - '0';
        length --;
        string ++;
    }

    return result;
}

int_signed convert_to_int(const char *string)
{
    int_signed result;

    if (*string == '-')
        return -convert_to_int(++ string);
    
    result = 0;
    while (*string && id_digit(string))
    {
        result = result * 10 + *string - '0';
        string ++;
    }

    return result;
}

real convert_to_real(const char *string)
{
    real result;
    int_unsigned int_part;
    int_unsigned decimal_part;

    if (*string == '-')
        return -convert_to_real(++ string);
    
    int_part = id_unsigned(string);
    if (!int_part)
    {
        error_set(WHY_ERROR_CONV, string);
        return 0;
    }

    result = _convert_int_part(string, int_part);
    string += int_part;

    if (*string != '.')
        return result;

    string ++;
    decimal_part = id_digit_string(string);
    if (!decimal_part)
    {
        error_set(WHY_ERROR_CONV, string);
        return 0;
    }
    
    result += _convert_decimal_part(string, decimal_part);

    return result;
}

Complex convert_to_complex(const char *string)
{
    int_unsigned length;
    int_signed sign;
    real re;
    real im;
    
    if (*string == 'i')
        return complex(0, 1);
    
    length = id_int_or_float(string);
    if (!length)
    {
        error_set(WHY_ERROR_CONV, string);
        return complex(0, 0);
    }
    
    re = convert_to_real(string);
    string += length;
    if (*string == 'i')
        return (Complex){0, re};
    
    while (*string && id_whitespace(string))
        string ++;
    
    if (*string == '+')
        sign = 1;
    else if (*string == '-')
        sign = -1;
    else
        return (Complex){re, 0};
    
    while (*string && id_whitespace(string))
        string ++;

    length = id_imaginary(string);
    if (!length)
        return (Complex){re, 0};

    im = convert_to_real(string) * sign;

    return (Complex){re, im};
}