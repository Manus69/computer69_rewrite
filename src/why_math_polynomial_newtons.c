#include "why_lib.h"
#include "why_math_polynomial.h"

#define DELTA 1.0 / (1 << 17)

static real _get_delta(const Polynomial *p, real x0)
{
    real p0;
    real leading_coefficient;

    p0 = polynomial_evaluate(p, complex(x0, 0)).re;
    leading_coefficient = polynomial_get_leading_coefficient(p).re;

    if (p0 > 0 && leading_coefficient > 0)
        return -DELTA;
    
    if (p0 > 0 && leading_coefficient < 0)
        return DELTA;
    
    if (p0 < 0 && leading_coefficient > 0)
        return DELTA;

    if (p0 < 0 && leading_coefficient < 0)
        return -DELTA;
    
    return DELTA;
}

static real _get_x0(const Polynomial *p, const Polynomial *p_prime)
{
    Vector *p_prime_roots;
    Complex z0, z1, p0, p1, leading_coefficient;
    real x0;

    p_prime_roots = polynomial_roots(p_prime);
    if (vector_size(p_prime_roots) == 1)
    {
        vector_delete(&p_prime_roots);
        return 0;
    }
    
    z0 = *(Complex *)vector_at(p_prime_roots, 0);
    z1 = *(Complex *)vector_at(p_prime_roots, 1);
    p0 = polynomial_evaluate(p, z0);
    p1 = polynomial_evaluate(p, z1);

    leading_coefficient = polynomial_get_leading_coefficient(p);
    if (leading_coefficient.re > 0)
    {
        if (p0.re < 0 && p1.re < 0)
            x0 = MAX(z0.re, z1.re);
        else
            x0 = MIN(z0.re, z1.re);
    }
    else if (leading_coefficient.re < 0)
    {
        if (p0.re > 0 && p1.re > 0)
            x0 = MAX(z0.re, z1.re);
        else
            x0 = MIN(z0.re, z1.re);
    }
    else
        x0 = 0;

    vector_delete(&p_prime_roots);

    return x0;
}

//this is not safe to use
real polynomial_newtons(const Polynomial *p)
{
    Polynomial *p_prime;
    real p_prime_value, root, f, x0, delta;

    p_prime = polynomial_differentiate(p);
    x0 = _get_x0(p, p_prime);
    root = x0;
    f = polynomial_evaluate(p, complex(x0, 0)).re;
    p_prime_value = polynomial_evaluate(p_prime, complex(x0, 0)).re;
    delta = _get_delta(p, x0);

    while (!within_delta(f, 0, DELTA))
    {
        while (p_prime_value == 0)
        {
            x0 += delta;
            p_prime_value = polynomial_evaluate(p_prime, complex(x0, 0)).re;
        }

        p_prime_value = polynomial_evaluate(p_prime, complex(x0, 0)).re;
        root = x0 - f / p_prime_value;
        f = polynomial_evaluate(p, complex(root, 0)).re;
        x0 = root;
    }

    polynomial_delete(&p_prime);

    return root;
}