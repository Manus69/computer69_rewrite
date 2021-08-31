#include "why_lib.h"

#include <assert.h>

// #define N_ITERATIONS(x) ((1 + (int_signed)ABS(x)) << 6)
#define N_ITERATIONS (1 << 5)
#define EXP2 (real)7.389056098930650
#define R_THRESHOLD (1 << 2)
#define L_THRESHOLD -(1 << 2)

real math_exp(real x)
{
    real value;
    int_signed n;

    if (x == 0)
        return 1;

    if (x > R_THRESHOLD)
        return math_exp(x / 2) * math_exp(x / 2);

    if (x < L_THRESHOLD)
        return 1 / math_exp(-x);

    value = 0;
    n = N_ITERATIONS;
    while (n > 0)
    {
        value += 1;
        value = (value * x) / n;

        n --;
    }

    value += 1;

    return value;
}
