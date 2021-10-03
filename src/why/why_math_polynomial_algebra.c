#include "why_lib.h"
#include "why_math_polynomial.h"
#include "why_memory.h"
#include "why_cstring.h"

#if WHY_DBG
    #include "why_print.h"
#endif

Polynomial* polynomial_increment(Polynomial* p, Polynomial* q)
{
    int_signed n;
    Complex value;

    n = q->degree;
    while (n >= 0)
    {
        if (!complex_is_zero(q->coefficients[n]))
        {
            value = complex_add(p->coefficients[n], q->coefficients[n]);
            polynomial_set(p, value, n);
        }

        n --;
    }

    return p;
}

Polynomial* polynomial_add(Polynomial* p, Polynomial* q)
{
    Polynomial* new_polynomial;
    Polynomial* larger_p;
    Complex     value;
    int_signed  n;

    if (!p || !q)
        return NULL;

    larger_p = p->degree > q->degree ? p : q; 
    new_polynomial = polynomial_copy(larger_p);
    n = p->degree < q->degree ? p->degree : q->degree;

    while (n >= 0)
    {
        if (!complex_is_zero(polynomial_at(q, n)) || !complex_is_zero(polynomial_at(p, n)))
        {
            value = complex_add(polynomial_at(p, n), polynomial_at(q, n));
            polynomial_set(new_polynomial, value, n);
        }

        n --;
    }

    return new_polynomial;
}

Polynomial* polynomial_addLD(Polynomial* p, Polynomial* q)
{
    return polynomial_increment(p, q);
}

Polynomial* polynomial_scale(Polynomial* p, Complex factor)
{
    Complex     value;
    int_signed  n;
    Polynomial* copy;

    if (!p)
        return NULL;

    copy = polynomial_copy(p);
    n = 0;
    while (n <= p->degree)
    {
        value = complex_mult(polynomial_at(p, n), factor);
        polynomial_set(copy, value, n);

        n ++;
    }

    return copy;
}

Polynomial* polynomial_subtract(Polynomial* p, Polynomial* q)
{
    Polynomial* copy;
    Polynomial* result;

    copy = polynomial_scale(q, complex(-1, 0));

    result = polynomial_add(p, copy);
    polynomial_delete(&copy);

    return result;
}

Polynomial* polynomial_subtractLD(Polynomial* p, Polynomial* q)
{
    Polynomial* result;

    result = polynomial_subtract(p, q);
    polynomial_delete(&p);

    return result;
}

Polynomial* polynomial_multiply(Polynomial* p, Polynomial* q)
{
    int_signed  degree;
    int_signed  k;
    Complex     value;
    Complex     sum;
    Polynomial* r;

    degree = p->degree + q->degree;
    r = _new(degree + 1, NULL);

    while (degree >= 0)
    {
        k = 0;
        sum = complex_zero();
        while (k <= degree)
        {
            value = complex_mult(polynomial_at(p, k), polynomial_at(q, degree - k));
            sum = complex_add(sum, value);
            k ++;
        }
        polynomial_set(r, sum, degree);
        degree --;
    }

    return r;
}

Polynomial* polynomial_multiplyLD(Polynomial* p, Polynomial* q)
{
    Polynomial* result;

    result = polynomial_multiply(p, q);
    polynomial_delete(&p);

    return result;
}

//careful
static int_signed _is_monomial(const Polynomial* p)
{
    int_signed n;

    n = 0;
    while (n < p->degree)
    {
        if (!complex_is_zero(p->coefficients[n]))
            return NOT_FOUND;
        
        n ++;
    }

    return p->degree;
}

Polynomial* polynomial_exponentiate(Polynomial* p, int_signed power)
{
    Polynomial* result;
    Polynomial* pointer;

    if (!p)
        return NULL;
    
    if (power == 0)
        return polynomial_new_from_complex(complex(1, 0));
    
    if (_is_monomial(p))
        return polynomial_new_from_complexG(p->coefficients[p->degree], power*  p->degree, p->variable);

    pointer = polynomial_copy(p);
    result = pointer;
    power --;

    while (power)
    {
        result = polynomial_multiply(pointer, p);
        polynomial_delete(&pointer);
        pointer = result;

        power --;
    }

    return result;
}

Polynomial* polynomial_exponentiateG(Polynomial* p, Polynomial* q)
{
    if (!p || !q)
        return NULL;

    if (q->degree != 0)
        return NULL;
    
    if (complex_is_real(q->coefficients[0]) == FALSE)
        return NULL;

    if (real_is_int(q->coefficients[0].re) == FALSE)
        return NULL;

    return polynomial_exponentiate(p, (int_signed)q->coefficients[0].re);
}