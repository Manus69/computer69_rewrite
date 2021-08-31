#include "why_lib.h"

#include <assert.h>

#define N_ITERATIONS(x) ((1 + (int_signed)ABS(x)) << 4)

real math_exp(real x)
{
    real value;
    int_signed n;

    if (x == 0)
        return 1;

    value = 0;
    n = N_ITERATIONS(x);
    while (n > 0)
    {
        value += 1;
        value = (value * x) / n;

        n --;
    }

    value += 1;

    return value;
}
