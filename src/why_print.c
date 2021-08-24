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