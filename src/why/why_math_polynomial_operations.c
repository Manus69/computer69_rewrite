#include "why_math.h"
#include "why_math_polynomial.h"
#include "why_memory.h"


Complex polynomial_evaluate(const Polynomial* p, Complex value)
{
    Complex     result;
    int_signed  n;

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

Polynomial* polynomial_differentiate(const Polynomial* p)
{
    Polynomial* derivative;
    Complex     value;
    int_signed  n;

    derivative = _new(p->degree + 1, p->variable);
    n = 1;
    while (n <= p->degree)
    {
        value = complex_scale(polynomial_at(p, n), n);
        polynomial_set(derivative, value, n - 1);
        n ++;
    }

    derivative->degree = _get_degree(derivative, derivative->degree);

    return derivative;
}

static Polynomial* _get_multiplier(const Polynomial* p, const Polynomial* d)
{
    Complex     leading_p;
    Complex     leading_d;
    Polynomial* multiplier;

    leading_p = polynomial_get_leading_coefficient(p);
    leading_d = polynomial_get_leading_coefficient(d);

    multiplier = polynomial_new_from_complexG(complex_div(leading_p, leading_d), p->degree - d->degree, NULL);

    return multiplier;
}

//p(x) = q(x)d(x) + r(x)
Polynomial* polynomial_factor(const Polynomial* p, const Polynomial* d)
{
    Polynomial* q;
    Polynomial* remainder;
    Polynomial* multiplier;
    Polynomial* result;

    if (!p || !d)
        return NULL;
    
    if (p->degree < 2 || p->degree <= d->degree)
        return NULL;
    
    if (!polynomial_is_real(p) || !polynomial_is_real(d))
        return NULL;

    result = polynomial_new(NULL);
    remainder = polynomial_copy(p);
    while (remainder->degree > 0)
    {
        multiplier = _get_multiplier(remainder, d);
        polynomial_set(result, polynomial_get_leading_coefficient(multiplier), multiplier->degree);

        q = polynomial_multiplyLD(multiplier, (Polynomial* )d);
        remainder = polynomial_subtractLD(remainder, q);

        polynomial_delete(&q);
    }

    polynomial_delete(&remainder);

    return result;
}
