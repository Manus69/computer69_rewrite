#include "print.h"

#include <stdio.h>
#include <assert.h>

void print_int(int_signed n)
{
    printf("%lld", n);
}

void print_real(real x)
{
    if (x < 0)
    {
        printf("-");
        print_real(-x);

        return ;
    }

    if (x - round_to_int(x) < TOLERANCE)
        printf("%.0Lf", x);
    else
        printf("%Lf", x);
}

void print_complex(Complex z)
{
    if (z.im == 0)
    {
        print_real(z.re);
        return ;
    }
    print_real(z.re);
    printf(" + ");

    if (z.im != 1)
        print_real(z.im);

    printf("i");
}

void print_number(const Number *number)
{
    if (number->type == NT_INT)
        print_int(number->n);
    else if (number->type == NT_REAL)
        print_real(number->x);
    else if (number->type == NT_COMPLEX)
        print_complex(number->z);
    else assert(0);
}

void print_string(const char *string)
{
    printf("%s\n", string);
}

void print_vector(const Vector *vector, void (*print)())
{
    int_signed n;
    int_signed size;
    void *item;

    size = vector_size(vector);
    n = 0;
    while (n < size)
    {
        item = vector_at(vector, n);
        print(item);
        n ++;
    }
}