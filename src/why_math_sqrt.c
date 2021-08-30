#include "why_lib.h"

#include <assert.h>

#define SQRT_EPSILON 1.0 / (1 << 12)
#define SN_CUTOFF 3
#define FACTOR (1 << 3)

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

    x0 = 1;
    f = 1;

    while (!within_delta(f, 0, SQRT_EPSILON))
    {
        f_prime = 2 * x0;
        x = x0 - f / f_prime;
        f = x * x - a;
        x0 = x;
    }

    return x;
}