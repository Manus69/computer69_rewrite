#include "why_lib.h"

#include <assert.h>

#define N_TERMS     (1 << 6)
#define LN2         (real)0.693147180559945309
#define R_THRESHOLD (1 << 3)
#define L_THRESHOLD 1

//ln x = 2[(x - 1)/(x + 1) + 1/3((x - 1)/(x + 1))^3 + 1/5((x - 1)/(x + 1))^5 + ...]
real math_ln(real x)
{
    int_signed n;
    real value;
    real w;

    if (x <= 0)
        assert(0);
    
    if (x > R_THRESHOLD)
        return LN2 + math_ln(x / 2);

    if (x < L_THRESHOLD)
        return math_ln(2 * x) - LN2;

    n = N_TERMS;
    value = 0;
    w = (x - 1) / (x + 1);

    while (n > 0)
    {
        if (n % 2)
            value += 1.0 / n;
        value = value * w;

        n --;
    }

    return 2 * value;
}

real math_log2(real x)
{
    return math_ln(x) / LN2;
}

real math_log(real x, real base)
{
    if (base <= 1)
        assert(0);
    
    return math_ln(x) / math_ln(base);
}

//ln x = (x - 1)/x + 1/2((x - 1)/x)^2 + 1/3((x - 1)/x)^3 + ...
//x >= 1/2 
real math_ln3(real x)
{
    real value, w;
    int_signed n;

    n = N_TERMS;
    w = (x - 1) / x;
    value = 0;

    while (n > 0)
    {
        value += 1.0 / n;
        value = value * w;
        
        n --;
    }

    return value;
}

//ln x = (x - 1) - 1/2(x - 1)^2 + 1/3(x - 1)^3 - 1/4(x - 1)^4 + ...
//somehow this only works for 0 < x <= 2 but why?
//this is bullshit
real math_ln2(real x)
{
    int_signed n;
    real value;
    real coefficient;
    real w;

    if (x <= 0)
        assert(0);

    n = N_TERMS;
    value = 0;
    w = x - 1;

    while (n > 0)
    {
        coefficient = 1.0 / n;
        coefficient = (n % 2 == 0) ? -coefficient : coefficient;
        value += coefficient;
        value = (value * w);

        n --;
    }

    return value;
}