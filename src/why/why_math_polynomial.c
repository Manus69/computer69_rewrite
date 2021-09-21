#include "why_math.h"
#include "why_math_polynomial.h"
#include "why_memory.h"
#include "why_cstring.h"
#include "why_lib.h"

#include <assert.h>

#if WHY_DBG
#include "why_print.h"
#endif

static void _array_init(Complex *array, int_signed n, int_signed size)
{
    while (n < size)
    {
        array[n] = complex_zero();
        n ++;
    }
}

Polynomial *_new(int_signed size, char *variable)
{
    Polynomial *p;

    if (size <= 0)
        return polynomial_new(variable);
    
    p = allocate(sizeof(Polynomial));
    p->coefficients = allocate(sizeof(Complex) * size);
    _array_init(p->coefficients, 0, size);
    p->degree = -1;
    p->capacity = size;
    p->variable = cstr_copy(variable);

    return p;
}

Polynomial *polynomial_new(char *variable)
{
    return _new(P_DEFAULT_SIZE, variable);    
}

Polynomial *polynomial_new_from_complexG(Complex z, int_signed degree, char *variable)
{
    Polynomial *p;

    p = _new(degree + 1, variable);
    polynomial_set(p, z, degree);

    return p;
}

Polynomial *polynomial_new_from_complex(Complex z)
{
    Polynomial *p;

    p = polynomial_new(NULL);
    polynomial_set(p, z, 0);

    #if WHY_DBG
    _print_polynomialDBG(p);
    #endif

    return p;
}

Polynomial *polynomial_new_from_coefficients(real coefficients[], int_signed size)
{
    Polynomial *p;
    Complex _coefficient;
    int_signed n;

    if (!size)
        return NULL;

    p = _new(size, NULL);
    p->degree = size - 1;
    n = 0;
    while (n < size)
    {
        _coefficient = complex(coefficients[n], 0);
        p->coefficients[n] = _coefficient;

        n ++;
    }

    return p;
}

Polynomial *polynomial_copy(const Polynomial *p)
{
    Polynomial *new;

    if (!p)
        return NULL;

    if (p->degree == -1)
        return polynomial_new(cstr_copy(p->variable));
    
    new = _new(p->degree + 1, p->variable);
    new->degree = p->degree;
    new->capacity = new->degree + 1;
    new->coefficients = memory_copy(new->coefficients, p->coefficients, (p->degree + 1) * sizeof(Complex));

    return new;
}

void polynomial_delete(Polynomial **p)
{
    if (!p || !*p)
        return ;
    
    free((*p)->coefficients);
    free((*p)->variable);
    free(*p);
    *p = NULL;
}

int_signed polynomial_get_degree(const Polynomial *p)
{
    if (!p)
        return -1;
    
    return p->degree;
}

char *polynomial_get_variable(const Polynomial *p)
{
    return p->variable;
}

int_signed _get_degree(Polynomial *p, int_signed start)
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
    int_signed current_size;
    int_signed extra_size;


    new_size *= sizeof(Complex);
    current_size = p->capacity * sizeof(Complex);

    if (new_size <= current_size)
        return p;
    
    extra_size = new_size - current_size;
    new_array = reallocate(p->coefficients, current_size, extra_size);
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

boolean polynomial_is_constant(const Polynomial *p)
{
    return p->degree == 0;
}

Complex polynomial_get_constant_coefficient(const Polynomial *p)
{
    return p->coefficients[0];
}

boolean polynomial_is_real(const Polynomial *p)
{
    int_signed n;

    n = 0;
    while (n <= p->degree)
    {
        if (!complex_is_real(p->coefficients[n]))
            return FALSE;
        
        n ++;
    }

    return TRUE;
}

boolean polynomial_is_zero(const Polynomial *p)
{
    if (!p)
        return FALSE;
    
    if (p->degree < 0)
        return TRUE;
    
    if (p->degree > 0)
        return FALSE;

    return complex_is_zero(p->coefficients[0]);
}

Complex polynomial_get_leading_coefficient(const Polynomial *p)
{
    if (p && p->degree >= 0)
        return p->coefficients[p->degree];

    assert(0);
}