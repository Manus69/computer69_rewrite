#include "why_math_number_interface.h"
#include "why_memory.h"

int_signed add_int(int_signed n, int_signed m)
{
    return n + m;
}

int_signed mult_int(int_signed n, int_signed m)
{
    return n * m;
}

int_signed subtract_int(int_signed n, int_signed m)
{
    return n - m;
}

int_signed divide_int(int_signed n, int_signed m)
{
    return n / m;
}

int_signed mod_int(int_signed n, int_signed m)
{
    return n % m;
}

real add_real(real x, real y)
{
    return x + y;
}

real mult_real(real x, real y)
{
    return x * y;
}

real subtract_real(real x, real y)
{
    return x - y;
}

real divide_real(real x, real y)
{
    return x / y;
}

boolean real_is_zero(real* x)
{
    return *x == 0;
}

boolean real_is_int(real x)
{
    return x == (int_signed)x;
}

void* real_add(real* x, real* y)
{
    real* result;

    result = allocate(sizeof(real));
    *result = *x + *y;

    return result;
}

void* real_mult(real* x, real* y)
{
    real* result;

    result = allocate(sizeof(real));
    *result = *x * *y;

    return result;
}

boolean complex_is_zero_p(Complex* z)
{
    return complex_is_zero(*z);
}

void* complex_add_p(Complex* z, Complex* w)
{
    Complex* result;

    result = allocate(sizeof(Complex));
    *result = complex_add(*z, *w);

    return result;
}

void* complex_mult_p(Complex* z, Complex* w)
{
    Complex* result;

    result = allocate(sizeof(Complex));
    *result = complex_mult(*z, *w);

    return result;
}