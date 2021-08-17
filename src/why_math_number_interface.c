#include "why_math_number_interface.h"
#include "why_memory.h"

boolean real_is_zero(real *x)
{
    return *x == 0;
}

void *real_add(real *x, real *y)
{
    real *result;

    result = allocate(sizeof(real));
    *result = *x + *y;

    return result;
}

void *real_mult(real *x, real *y)
{
    real *result;

    result = allocate(sizeof(real));
    *result = *x * *y;

    return result;
}

boolean complex_is_zero_p(Complex *z)
{
    return complex_is_zero(*z);
}

void *complex_add_p(Complex *z, Complex *w)
{
    Complex *result;

    result = allocate(sizeof(Complex));
    *result = complex_add(*z, *w);

    return result;
}

void *complex_mult_p(Complex *z, Complex *w)
{
    Complex *result;

    result = allocate(sizeof(Complex));
    *result = complex_mult(*z, *w);

    return result;
}