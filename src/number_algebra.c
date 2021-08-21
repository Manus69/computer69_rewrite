#include "frontend_declarations.h"
#include "number.h"

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

    type = _promote(lhs, rhs);

    if (type == NT_INT)
        return number_new_int(add_int(lhs->n, rhs->n));
    else if (type == NT_REAL)
        return number_new_real(add_real(lhs->x, rhs->x));
    else
        return number_new_complex(complex_add(lhs->z, rhs->z));
}

Number *number_mult(Number *lhs, Number *rhs)
{
    NUMBER_TYPE type;

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

    if (number_is_zero(rhs))
        assert(0);
    
    type = _promote(lhs, rhs);
    if (type == NT_INT)
        return number_new_int(divide_int(lhs->n, rhs->n));
    else if (type == NT_REAL)
        return number_new_real(divide_real(lhs->x, rhs->x));
    else if (type == NT_COMPLEX)
        return number_new_complex(complex_div(lhs->z, rhs->z));
    
    assert(0);
}

Number *number_mod(Number *lhs, Number *rhs)
{
    if (lhs->type != NT_INT || rhs->type != NT_INT)
        assert(0);
    
    if (number_is_zero(rhs))
        assert(0);

    return number_new_int(mod_int(lhs->n, rhs->n));
}

Number *number_power(Number *lhs, Number *rhs)
{
    if (rhs->type != NT_INT)
        assert(0);

    if (rhs->n < 0)
        assert(0);
    
    if (lhs->type == NT_INT)
        return number_new_int(power_int(lhs->n, rhs->n));
    else if (lhs->type == NT_REAL)
        return number_new_real(power(lhs->x, rhs->n));
    else
        return number_new_complex(complex_power(lhs->z, rhs->n));
}

Number *number_factorial(Number *lhs, const Number *rhs)
{
    if (rhs)
        assert(0);

    if (lhs->type != NT_INT)
        assert(0);
    
    return number_new_int(factorial(lhs->n));
}