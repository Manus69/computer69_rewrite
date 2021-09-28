#include "why_math.h"
#include "why_error.h"
#include "why_lib.h"

#define FIB_LIMIT 90

real math_id(real x)
{
    return x;
}

boolean within_delta(real x, real y, real delta)
{
    real diff;

    diff = x - y;
      
    return absolute_value(diff) < delta;
}

int_unsigned factorial(int_unsigned n)
{
    if (n == 0)
        return 1;
    
    return n * factorial(n - 1);
}

//naive
real power(real base, int_unsigned n)
{
    real result;

    if (base == 0 && n == 0)
        return 0;
    
    if (base == 1 || n == 0)
        return 1;
    
    result = 1;
    while (n)
    {
        result *= base;
        n --;
    }

    return result;
}

int_signed power_int(int_signed base, int_unsigned n)
{
    real result;

    result = power(base, n);
    if (result > WHY_INT_MAX)
        return (int_signed)error_set(WHY_ERROR_MATH, "the number is too large");
    
    return result;
}

int_unsigned round_to_int(real x)
{
    if (x > WHY_INT_MAX)
        return (int_unsigned)error_set(WHY_ERROR_CONV, "the number is too large");
    
    return (int_unsigned)x;
}

real absolute_value(real x)
{
    return x < 0 ? -x : x;
}

int_unsigned fib(int_unsigned n)
{
    static int_unsigned values[FIB_LIMIT];
    int_unsigned        value;

    if (n >= FIB_LIMIT)
        return 0;
    
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    if (values[n])
        return values[n];
    else
    {
        value = fib(n - 1) + fib(n - 2);
        values[n] = value;

        return value;
    }
}

static real math_mod_negative(real x, real mod)
{
    while (x < 0)
        x += mod;
    
    return x;
}

//x = k m + r
real math_mod(real x, real mod)
{
    if (mod <= 0)
        return (int_signed)error_set(WHY_ERROR_MATH, "negative mod");
    
    if (x < 0)
        return math_mod_negative(x, mod);

    if (x < mod)
        return x;
    
    while (x >= mod)
        x = x - mod;
    
    return x;
}
