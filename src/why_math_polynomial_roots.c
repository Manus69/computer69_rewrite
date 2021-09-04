#include "why_lib.h"
#include "why_math_polynomial.h"

#include <assert.h>

#if WHY_DBG
#include <stdio.h>
#endif

static Vector *_solve_constant(const Polynomial *p)
{
    Vector *root;

    if (!complex_is_zero(p->coefficients[0]))
        return NULL;

    root = vector_new_with_capacity(copy_shallow, memory_delete, 1);
    vector_push(root, complex_copy(&p->coefficients[0]));

    return root;
}

//a0 + a1x = 0
static Vector *_solve_linear(const Polynomial *p)
{
    Vector *roots;
    real x;
    
    roots = vector_new_with_capacity(copy_shallow, memory_delete, 2);

    x = -p->coefficients[0].re / p->coefficients[1].re;
    vector_push(roots, complex_new(x, 0));

    return roots;
}

//c + bx + ax^2 = 0
static Vector *_solve_quadratic(const Polynomial *p)
{
    Vector *roots;
    real a, b, c, x, D;

    #if WHY_DBG
    _print_polynomialDBG(p);
    #endif

    roots = vector_new_with_capacity(copy_shallow, memory_delete, 2);
    
    a = p->coefficients[2].re;
    b = p->coefficients[1].re;
    c = p->coefficients[0].re;

    D = b * b - 4 * a *c;
    if (D == 0)
    {
        vector_push(roots, complex_new(-b, 0));
    }
    else if (D > 0)
    {
        x = (-b + math_sqrt(D)) / (2 * a);
        vector_push(roots, complex_new(x, 0));
        x = (-b - math_sqrt(D)) / (2 * a);
        vector_push(roots, complex_new(x, 0));
    } 
    else
    {
        x = math_sqrt(-D) / (2 * a);
        vector_push(roots, complex_new(-b / (2 * a), x));
        vector_push(roots, complex_new(-b / (2 * a), -x));
    }

    return roots;
}

static Vector *_solve_qubic(const Polynomial *p)
{
    Vector *roots;
    Vector *quadratic_roots;
    Polynomial *q;
    Polynomial *factor;
    real a_root;

    a_root = polynomial_newtons(p);
    roots = vector_new_with_capacity(copy_shallow, memory_delete, 3);

    vector_push(roots, complex_new(a_root, 0));

    factor = polynomial_new_from_coefficients((real[]){-a_root, 1}, 2);
    q = polynomial_factor(p, factor);
    quadratic_roots = polynomial_roots(q);
    roots = vector_concatG(roots, quadratic_roots, copy_complex);

    polynomial_delete(&factor);
    vector_delete(&quadratic_roots);
    polynomial_delete(&q);

    return roots;
}

Vector *polynomial_roots(const Polynomial *p)
{
    if (!p)
        return NULL;

    if (p->degree < 0)
        return NULL;

    if (!polynomial_is_real(p))
        return NULL;

    if (p->degree == 0)
        return _solve_constant(p);
    
    if (p->degree == 1)
        return _solve_linear(p);

    if (p->degree == 2)
        return _solve_quadratic(p);

    if (p->degree == 3)
        return _solve_qubic(p);

    assert(0);
}