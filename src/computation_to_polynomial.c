#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "entity.h"

#include <assert.h>

static Polynomial *_combine_polynomials(Polynomial *lhs, Operator *op, Polynomial *rhs)
{
    OPERATOR_TYPE op_type;
    Polynomial *result;
    Complex z;

    #if DBG
    _print_polynomialDBG(lhs);
    _print_polynomialDBG(rhs);
    #endif

    result = NULL;
    op_type = operator_get_type(op);

    if ((!lhs || !rhs) && (op_type != OT_MINUS))
        return NULL;
    
    if (op_type == OT_PLUS)
        result = polynomial_add(lhs, rhs);
    else if (op_type == OT_MINUS)
    {
        if (lhs && rhs)
            result = polynomial_subtract(lhs, rhs);
        else if (!rhs)
            result = polynomial_scale(lhs, complex(-1, 0));
    }
    else if (op_type == OT_STAR)
        result = polynomial_multiply(lhs, rhs);
    else if (op_type == OT_CARET)
    {
        if (!polynomial_is_constant(rhs))
            return NULL;

        z = polynomial_get_constant_coefficient(rhs);
        if (complex_is_real(z) && real_is_int(z.re) && z.re >= 0)
            result = polynomial_exponentiate(lhs, z.re);
    }

    polynomial_delete(&lhs);
    polynomial_delete(&rhs);

    return result;
}

Polynomial *computation_to_polynomial(const Computation *_computation)
{
    Polynomial *lhs;
    Polynomial *rhs;
    Complex z;

    if (!_computation)
        return NULL;
    
    if (_computation->node->type == NT_NUMBER)
    {
        z = number_to_complex(_computation->node->number);

        return polynomial_new_from_complex(z);
    }

    if (_computation->node->type == NT_WILDCARD)
    {
        return polynomial_new_from_complexG(complex(1, 0), 1, NULL);
    }

    if (_computation->node->type != NT_OPERATOR)
        assert(0);
    
    lhs = computation_to_polynomial(_computation->lhs);
    rhs = computation_to_polynomial(_computation->rhs);

    return _combine_polynomials(lhs, _computation->node->operator, rhs);
}