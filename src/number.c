#include "number.h"
#include "why_memory.h"

Number *number_new_int(int_signed n)
{
    Number *number;

    number = allocate(sizeof(Number));
    number->n = n;
    number->type = NT_INT;

    return number;
}

Number *number_new_real(real x)
{
    Number *number;

    number = allocate(sizeof(Number));
    number->x = x;
    number->type = NT_REAL;

    return number;
}

Number *number_new_complex(Complex z)
{
    Number *number;

    number = allocate(sizeof(Number));
    number->z = z;
    number->type = NT_COMPLEX;

    return number;
}