#include "why_print.h"

#include <stdio.h>
#include <assert.h>
#include <unistd.h>

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
    if (z.re)
    {
        print_real(z.re);
        printf(" + ");
    }

    if (z.im != 1)
        print_real(z.im);

    printf("i");
}

void print_cstring(const char *string)
{
    printf("%s", string);
}

//this is ugly and dangerous
void print_string(const String *string)
{
    char *cstring;
    int_signed length;

    if (!string)
        return ;

    cstring = string_get_characters(string);
    length = string_length(string);
    printf("%.*s", (int)length, cstring);
}

void print_string_n(const String *string)
{
    print_string(string);
    printf("\n");
}

void print_vector(const Vector *vector, void (*print)(), const char *separator)
{
    int_signed n;
    int_signed size;
    void *item;

    if (!vector)
        return ;

    size = vector_size(vector);
    item = vector_at(vector, 0);
    print(item);

    n = 1;
    while (n < size)
    {
        if (separator)
            printf("%s", separator);
        
        item = vector_at(vector, n);
        print(item);

        n ++;
    }
}

static void _print_initial(const Polynomial *p, int_signed degree)
{
    Complex coefficient;

    coefficient = polynomial_at(p, 0);
    print_complex(coefficient);

    if (degree < 1)
        return ;
    
    coefficient = polynomial_at(p, 1);
    printf(" + ");
    if (coefficient.re != 1 && coefficient.im == 0)
        print_complex(coefficient);
    printf("x");
}

void print_polynomial(const Polynomial *p)
{
    int_signed n;
    int_signed degree;
    Complex coefficient;

    if (!p)
        return ;
    
    if (polynomial_get_degree(p) < 0)
    {
        printf("zero polynomial\n");

        return ;
    }

    degree = polynomial_get_degree(p);
    _print_initial(p, degree);

    n = 2;
    while (n <= degree)
    {
        coefficient = polynomial_at(p, n);
        printf(" + ");
        if (coefficient.re != 1 && coefficient.im == 0)
            print_complex(coefficient);

        printf("x^%Ld", n);

        n ++;
    }
}

void _print_polynomialDBG(const Polynomial *p)
{
    int_signed n;
    int_signed degree;
    Complex z;

    n = 0;
    degree = polynomial_get_degree(p);
    while (n <= degree)
    {
        z = polynomial_at(p, n);
        printf("%lld %Lf %Lf\n", n, z.re, z.im);
        n ++;
    }
    printf("\n");
}