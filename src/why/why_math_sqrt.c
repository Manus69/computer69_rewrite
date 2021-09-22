#include "why_lib.h"

#include <assert.h>
#include <limits.h>

#define DBG 0
#if DBG
#include <stdio.h>
#endif

#define SQRT_EPSILON    1.0 / (1 << 20)
#define SN_CUTOFF       100
#define FACTOR          (1 << 4)

real math_sqrt(real a)
{
    real x, x0, f, f_prime;

    if (a < 0)
        assert(0);
    
    if (a == 0)
        return 0;

    if (a == 1)
        return 1;
    
    if (a < SN_CUTOFF)
        return math_sqrt(a * FACTOR * FACTOR) / FACTOR;

    if (a > __INT_MAX__)
        return 2 * math_sqrt(a / 4);

    x0 = a > 1 ? a / 2 : 1;
    f = x0 * x0 - a;

    while (!within_delta(f, 0, SQRT_EPSILON))
    {
        f_prime = 2 * x0;
        x = x0 - f / f_prime;
        f = x * x - a;
        x0 = x;
    }

    return x;
}