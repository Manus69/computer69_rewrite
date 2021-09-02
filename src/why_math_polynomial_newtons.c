#include "why_lib.h"
#include "why_math_polynomial.h"

#define DELTA 1.0 / (1 << 15)

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
    Complex z0, z1, leading_coefficient;
    real x0;

    p_prime_roots = polynomial_roots(p_prime);
    z0 = *(Complex *)vector_at(p_prime_roots, 0);
    z1 = *(Complex *)vector_at(p_prime_roots, 1);
    leading_coefficient = polynomial_get_leading_coefficient(p);

}

//this is not safe to use
real polynomial_newtons(const Polynomial *p)
{
    Polynomial *p_prime;
    real p_prime_value, root, f, x0, delta;

    p_prime = polynomial_differentiate(p);
    x0 = 0;
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