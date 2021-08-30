#include "why_math.h"
#include "why_math_polynomial.h"
#include "why_memory.h"


Complex polynomial_evaluate(Polynomial *p, Complex value)
{
    Complex result;
    int_signed n;

    result = complex_zero();
    n = polynomial_get_degree(p);

    while (n >= 0)
    {
        result = complex_mult(result, value);
        result = complex_add(result, polynomial_at(p, n));
        n --;
    }

    return result;
}

Polynomial *polynomial_differentiate(Polynomial *p)
{
    Polynomial *derivative;
    Complex value;
    int_signed n;

    derivative = _new(p->degree + 1, p->variable);
    n = 1;
    while (n <= derivative->degree)
    {
        value = complex_scale(polynomial_at(p, n), n);
        polynomial_set(derivative, value, n - 1);
        n ++;
    }

    derivative->degree = _get_degree(derivative, 0);

    return derivative;
}

Polynomial *polynomial_factor(Polynomial *p, Polynomial *q);
