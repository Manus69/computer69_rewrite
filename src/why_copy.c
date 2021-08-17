#include "why_copy.h"
#include "why_memory.h"

void *copy_shallow(const void *item)
{
    return (void *)item;
}

void *copy_real(real *x)
{
    real *number;

    number = allocate(sizeof(real));
    *number = *x;

    return number;
}

void *copy_complex(Complex *z)
{
    Complex *w;

    w = allocate(sizeof(Complex));
    w->re = z->re;
    w->im = z->im;

    return w;
}