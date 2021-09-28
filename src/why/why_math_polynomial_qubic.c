#include "why_lib.h"
#include "why_math_polynomial.h"
#include "why_error.h"

static Polynomial* _scale(const Polynomial* p)
{
    int_signed  n;
    Complex     coefficient;
    Polynomial* p_scaled;
    Polynomial* pointer;

    p_scaled = polynomial_copy(p);
    n = 0;
    while (n <= p->degree)
    {
        coefficient = polynomial_at(p_scaled, n);
        if (complex_is_zero(coefficient))
        {
            n ++;
            continue ;
        }

        if (absolute_value(coefficient.re) < 1)
        {
            pointer = polynomial_scale(p_scaled, complex(1 / coefficient.re, 0));
            polynomial_delete(&p_scaled);
            p_scaled = pointer;
        }

        n ++;
    }

    return p_scaled;
}

static boolean _in_range(const Polynomial* p)
{
    int_signed  n;
    Complex     coefficient;

    n = 0;
    while (n <= p->degree)
    {
        coefficient = polynomial_at(p, n);
        if (absolute_value(coefficient.re) > P_COEFFICIENT_ABS_MAX)
            return FALSE;

        n ++;
    }

    return TRUE;
}

static Vector* _get_roots(Polynomial* p_scaled, Vector* roots, real a_root)
{
    Polynomial* q;
    Polynomial* factor;
    Vector*     quadratic_roots;

    factor = polynomial_new_from_coefficients((real[]){-a_root, 1}, 2);
    q = polynomial_factor(p_scaled, factor);
    quadratic_roots = polynomial_roots(q);
    roots = vector_concatG(roots, quadratic_roots, copy_complex);

    polynomial_delete(&factor);
    vector_delete(&quadratic_roots);
    polynomial_delete(&q);

    return roots;
}

Vector* _solve_qubic(const Polynomial* p)
{
    Vector*     roots;
    Polynomial* p_scaled;
    real        a_root;

    p_scaled = _scale(p);

    if (!_in_range(p_scaled))
    {
        error_set(WHY_ERROR_MATH, "failed to find roots");
        polynomial_delete(&p_scaled);
        return NULL;
    }

    a_root = polynomial_newtons(p_scaled);
    roots = vector_new_with_capacity(copy_shallow, memory_delete, 3);

    vector_push(roots, complex_new(a_root, 0));
    roots = _get_roots(p_scaled, roots, a_root);

    polynomial_delete(&p_scaled);

    return roots;
}