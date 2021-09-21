#include "frontend_declarations.h"
#include "number.h"
#include "why_error.h"

#include <assert.h>

static NUMBER_TYPE _promote(Number *lhs, Number *rhs)
{
    NUMBER_TYPE type;

    type = MAX(lhs->type, rhs->type);
    number_promote(lhs, type);
    number_promote(rhs, type);

    return type;
}

//this might change the arguments
Number *number_add(Number *lhs, Number *rhs)
{
    NUMBER_TYPE type;

    if (!lhs || !rhs)
        return error_set(WHY_ERROR_MATH, NULL);

    type = _promote(lhs, rhs);

    if (type == NT_INT)
        return number_new_int(add_int(lhs->n, rhs->n));
    else if (type == NT_REAL)
        return number_new_real(add_real(lhs->x, rhs->x));
    else
        return number_new_complex(complex_add(lhs->z, rhs->z));

}

Number *number_increment(Number *lhs, Number *rhs)
{
    NUMBER_TYPE type;

    if (!lhs || !rhs)
        return error_set(WHY_ERROR_MATH, NULL);

    type = _promote(lhs, rhs);

    if (type == NT_INT)
        lhs->n += rhs->n;
    else if (type == NT_REAL)
        lhs->x += rhs->x;
    else
        lhs->z = complex_add(lhs->z, rhs->z);

    return lhs;
}

Number *number_mult(Number *lhs, Number *rhs)
{
    NUMBER_TYPE type;

    if (!lhs || !rhs)
        return error_set(WHY_ERROR_MATH, NULL);

    type = _promote(lhs, rhs);

    if (type == NT_INT)
        return number_new_int(mult_int(lhs->n, rhs->n));
    else if (type == NT_REAL)
        return number_new_real(mult_real(lhs->x, rhs->x));
    else if (type == NT_COMPLEX)
        return number_new_complex(complex_mult(lhs->z, rhs->z));
    
    assert(0);
}

Number *number_subtract(Number *lhs, Number *rhs)
{
    NUMBER_TYPE type;

    if (!lhs)
        return error_set(WHY_ERROR_MATH, NULL);
    
    if (!rhs)
        return number_scale(lhs, -1);

    type = _promote(lhs, rhs);

    if (type == NT_INT)
        return number_new_int(subtract_int(lhs->n, rhs->n));
    else if (type == NT_REAL)
        return number_new_real(subtract_real(lhs->x, rhs->x));
    else if (type == NT_COMPLEX)
        return number_new_complex(complex_subtract(lhs->z, rhs->z));
    
    assert(0);
}

Number *number_divide(Number *lhs, Number *rhs)
{
    NUMBER_TYPE type;

    if (!lhs || !rhs)
        return error_set(WHY_ERROR_MATH, NULL);

    if (number_is_zero(rhs))
        return error_set(WHY_ERROR_MATH, " divison by zero");
    
    type = _promote(lhs, rhs);
    if (type == NT_INT)
        // return number_new_int(divide_int(lhs->n, rhs->n));
        return number_new_real(divide_real(lhs->n, rhs->n));
    else if (type == NT_REAL)
        return number_new_real(divide_real(lhs->x, rhs->x));
    else if (type == NT_COMPLEX)
        return number_new_complex(complex_div(lhs->z, rhs->z));
    
    assert(0);
}

Number *number_mod(Number *lhs, Number *rhs)
{
    if (!lhs || !rhs)
        return error_set(WHY_ERROR_MATH, NULL);
    
    if (lhs->type != NT_INT || rhs->type != NT_INT)
        return error_set(WHY_ERROR_MATH, " mod of non-integer types if undefined");
    
    if (number_is_zero(rhs))
        return error_set(WHY_ERROR_MATH, " divison by zero");

    return number_new_int(mod_int(lhs->n, rhs->n));
}

Number *number_power(Number *lhs, Number *rhs)
{
    if (!lhs || !rhs)
        return error_set(WHY_ERROR_MATH, NULL);
    
    if (rhs->type != NT_INT)
        return error_set(WHY_ERROR_MATH, " non-integer powers are not supported");

    if (rhs->n < 0)
        return error_set(WHY_ERROR_MATH, " negative powers are not supported");

    if (lhs->type == NT_INT)
        return number_new_int(power_int(lhs->n, rhs->n));
    else if (lhs->type == NT_REAL)
        return number_new_real(power(lhs->x, rhs->n));
    else
        return number_new_complex(complex_power(lhs->z, rhs->n));
}

Number *number_factorial(Number *lhs, const Number *rhs)
{
    if (!lhs || rhs)
        return error_set(WHY_ERROR_MATH, NULL);
    
    if (lhs->type != NT_INT)
        return error_set(WHY_ERROR_MATH, NULL);

    if (lhs->n < 0)
        return error_set(WHY_ERROR_MATH, "! is defined for non-negative integers");
    
    return number_new_int(factorial(lhs->n));
}

Number *number_scale(Number *number, real factor)
{
    if (!number)
        return error_set(WHY_ERROR_MATH, NULL);
    
    if (number->type == NT_INT)
        return number_new_int(number->n * factor);
    else if (number->type == NT_REAL)
        return number_new_real(number->x * factor);
    else
        return number_new_complex(complex_scale(number->z, factor));
}

Number *number_function(const Number *number, real (*function)(real))
{
    real arg;

    if (!number)
        return error_set(WHY_ERROR_MATH, NULL);
    
    if (number->type == NT_COMPLEX)
        return error_set(WHY_ERROR_MATH, "complex numbers are not supported for this function");
    
    arg = number->type == NT_REAL ? number->x : number->n;

    return number_new_real(function(arg));
}

Number *number_sin(const Number *number)
{
    return number_function(number, math_sin);
}

Number *number_cos(const Number *number)
{
    return number_function(number, math_cos);
}

Number *number_tan(const Number *number)
{
    return number_function(number, math_tan);
}

Number *number_sqrt(const Number *number)
{
    return number_function(number, math_sqrt);
}

Number *number_log(const Number *number)
{
    return number_function(number, math_log2);
}

Number *number_ln(const Number *number)
{
    return number_function(number, math_ln);
}

Number *number_exp(const Number *number)
{
    return number_function(number, math_exp);
}

Number *number_abs(Number *number)
{
    if (!number)
        return error_set(WHY_ERROR_MATH, NULL);
    
    if (number->type == NT_INT)
        number->n = ABS(number->n);
    else if (number->type == NT_REAL)
        number->x = ABS(number->x);
    else
        return error_set(WHY_ERROR_MATH, " complex numbers are not supported for this function");
    
    return number;
}