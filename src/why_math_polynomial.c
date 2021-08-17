#include "why_math.h"
#include "why_math_polynomial.h"
#include "why_memory.h"
#include "why_cstring.h"

#include <assert.h>

static void _array_init(Complex *array, int_signed n, int_signed size)
{
    while (n < size)
    {
        array[n] = complex_zero();
        n ++;
    }
}

static Polynomial *_new(int_signed size, char *variable)
{
    Polynomial *p;

    p = allocate(sizeof(Polynomial));
    p->coefficients = allocate(sizeof(Complex) * size);
    _array_init(p->coefficients, 0, size);
    p->degree = -1;
    p->capacity = size;
    p->variable = variable;

    return p;
}

Polynomial *polynomial_new(char *variable)
{
    return _new(P_DEFAULT_SIZE, variable);    
}

Polynomial *polynomial_new_from_complex(Complex z)
{
    Polynomial *p;

    p = polynomial_new(NULL);
    polynomial_set(p, z, 0);

    return p;
}

Polynomial *polynomial_copy(const Polynomial *p)
{
    Polynomial *new;

    if (p->degree == -1)
        return polynomial_new(cstr_copy(p->variable));
    
    new = polynomial_new(cstr_copy(p->variable));
    new->degree = p->degree;
    new->capacity = new->degree + 1;
    new->coefficients = memory_copy(new->coefficients, p->coefficients, (p->degree + 1) * sizeof(Complex));

    return new;
}

void polynomial_delete(Polynomial **p)
{
    free((*p)->coefficients);
    free((*p)->variable);
    free(*p);
    *p = NULL;
}

int_signed polynomial_get_degree(const Polynomial *p)
{
    return p->degree;
}

char *polynomial_get_variable(const Polynomial *p)
{
    return p->variable;
}

static int_signed _get_degree(Polynomial *p, int_signed start)
{
    int_signed n;

    n = start;
    while (n >= 0)
    {
        if (!complex_is_zero(p->coefficients[n]))
            return n;

        n --;
    }

    return -1;
}

Complex polynomial_at(const Polynomial *p, int_signed degree)
{
    if (degree >= p->capacity)
        return complex_zero();
    
    return p->coefficients[degree];
}

static Polynomial *_extend_array(Polynomial *p, int_signed new_size)
{
    Complex *new_array;
    int_unsigned current_size;

    current_size = p->capacity * sizeof(Complex);
    new_array = reallocate(p->coefficients, current_size, new_size);
    free(p->coefficients);
    p->coefficients = new_array;
    p->capacity = new_size;

    return p;
}

boolean polynomial_set(Polynomial *p, Complex value, int_signed degree)
{
    if (degree >= p->capacity)
        _extend_array(p, degree + 1);
    
    p->coefficients[degree] = value;

    if (!complex_is_zero(value))
    {
        if (degree > p->degree)
            p->degree = degree;
    }
    else if (degree == p->degree)
    {
        p->degree = _get_degree(p, degree);
    }

    return TRUE;
}

Polynomial *polynomial_increment(Polynomial *p, Polynomial *q)
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

Polynomial *polynomial_add(Polynomial *p, Polynomial *q)
{
    int_signed n;
    Complex value;
    Polynomial *new_polynomial;

    new_polynomial = polynomial_new(cstr_copy(p->variable));
    n = q->degree;
    while (n >= 0)
    {
        if (!complex_is_zero(q->coefficients[n]))
        {
            value = complex_add(p->coefficients[n], q->coefficients[n]);
            polynomial_set(new_polynomial, value, n);
        }

        n --;
    }

    return new_polynomial;
}

Polynomial *polynomial_scale(Polynomial *p, Complex factor)
{
    Complex value;
    int_signed n;

    n = 0;
    while (n <= p->degree)
    {
        value = complex_mult(polynomial_at(p, n), factor);
        polynomial_set(p, value, n);

        n ++;
    }

    return p;
}

Polynomial *polynomial_multiply(Polynomial *p, Polynomial *q)
{
    int_signed degree;
    int_signed k;
    Complex value;
    Complex sum;
    Polynomial *r;

    degree = p->degree + q->degree;

    r = polynomial_new(p->variable);
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

Polynomial *polynomial_exponentiate(Polynomial *p, int_signed power)
{
    Polynomial *result;
    Polynomial *pointer;

    if (!p)
        return NULL;
    
    if (power == 0)
        return polynomial_new_from_complex(complex(1, 0));
    
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

