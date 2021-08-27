#include "why_math.h"

#include <limits.h>
#include <assert.h>

#define LIMIT 90

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
    return (int_signed)power(base, n);
}

int_unsigned round_to_int(real x)
{
    if (x > ULLONG_MAX)
        assert(0);
    
    return (int_unsigned)x;
}

real absolute_value(real x)
{
    return x < 0 ? -x : x;
}

int_unsigned fib(int_unsigned n)
{
    static int_unsigned values[LIMIT];
    int_unsigned value;

    if (n >= LIMIT)
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
