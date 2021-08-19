#include "print.h"
#include "why_print.h"

#include <stdio.h>
#include <assert.h>

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
