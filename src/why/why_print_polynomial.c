#include "why_math_polynomial.h"
#include "why_print.h"

#include <stdio.h>

#define DEFAULT_SYMBOL "x"

//this is all fucked up

static void _print_p_coefficient(Complex coefficient, boolean _signed, int_signed degree)
{
    if (complex_is_zero(coefficient))
        return ;

    if (complex_is_real(coefficient))
    {
        if (coefficient.re == 1 && degree)
            return ;
        if (coefficient.re == -1 && degree)
        {
            printf("-");
            return ;
        }
        
        _signed ? print_real(coefficient.re) : print_real(absolute_value(coefficient.re));
    }
    else if (complex_is_imaginary(coefficient))
    {
        if (coefficient.im == 1)
        {
            printf("i");
            return ;
        }

        _signed ? print_real(coefficient.im) : print_real(absolute_value(coefficient.im));
    }
    else
    {
        printf("( ");
        print_complex(coefficient);
        printf(" )");
    }
}

static int _determine_sign(Complex coefficient)
{
    if (complex_is_zero(coefficient))
        return 0;
    
    if (complex_is_real(coefficient))
        return coefficient.re > 0 ? 1 : -1;

    if (complex_is_imaginary(coefficient))
        return coefficient.im > 0 ? 1 : -1;
    
    return 1;
}

static void _print_coefficient(const Polynomial* p, int_signed degree, boolean leading)
{
    Complex coefficient;
    int sign;

    coefficient = polynomial_at(p, degree);
    if (leading)
    {
        _print_p_coefficient(coefficient, TRUE, degree);
        return ;
    }
    
    coefficient = polynomial_at(p, degree);
    sign = _determine_sign(coefficient);
    
    sign > 0 ? printf(" + ") : printf(" - ");
    _print_p_coefficient(coefficient, FALSE, degree);
}

//this is fucking ugly
void print_polynomial(const Polynomial* p)
{
    int_signed  n;
    int_signed  degree;
    Complex     coefficient;
    boolean     leading;

    if (!p)
        return ;
    
    if (polynomial_get_degree(p) < 0)
    {
        printf("zero polynomial");
        return ;
    }

    leading = TRUE;
    degree = polynomial_get_degree(p);
    n = 0;
    while (n <= degree)
    {
        coefficient = polynomial_at(p, n);
        if (complex_is_zero(coefficient))
        {
            n ++;
            continue ;
        }

        _print_coefficient(p, n, leading);
        leading = FALSE;

        if (n > 1)
            printf("%s^%Ld", p->variable ? p->variable : DEFAULT_SYMBOL, n);
        else if (n == 1)
            printf("%s", p->variable ? p->variable : DEFAULT_SYMBOL);

        n ++;
    }
}

void print_polynomial_with_rhs(const Polynomial* p)
{
    if (!p)
        return ;
    
    if (polynomial_get_degree(p) >= 0)
    {
        print_polynomial(p);
        printf(" = 0");
    }
    else
    {
        print_polynomial(p);
    }

    printf("\n");
}

void _print_polynomialDBG(const Polynomial* p)
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