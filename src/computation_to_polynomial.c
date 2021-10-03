#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "entity.h"
#include "why_error.h"

static void* _handle_errors(Polynomial *lhs, Polynomial *rhs)
{
    polynomial_delete(&lhs);
    polynomial_delete(&rhs);

    return error_set(WHY_ERROR_MATH, NULL);
}

static Polynomial* _combine_polynomials(Polynomial* lhs, Operator* op, Polynomial* rhs)
{
    Polynomial*     result;
    OPERATOR_TYPE   op_type;
    Complex         z;

    result = NULL;
    op_type = operator_get_type(op);

    if ((!lhs || !rhs) && (op_type != OT_MINUS))
        return _handle_errors(lhs, rhs);
    
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
        if (polynomial_is_constant(rhs))
        {
            z = polynomial_get_constant_coefficient(rhs);
            if (complex_is_real(z) && real_is_int(z.re) && z.re >= 0)
                result = polynomial_exponentiate(lhs, z.re);
        }
        else if (polynomial_is_zero(rhs))
            result = polynomial_new_from_complex(complex(1, 0));
    }

    polynomial_delete(&lhs);
    polynomial_delete(&rhs);

    return result;
}

Polynomial* computation_to_polynomial(const Computation* _computation)
{
    Polynomial* lhs;
    Polynomial* rhs;
    Complex     z;

    if (!_computation)
        return NULL;
    
    if (_computation->node->type == NT_NUMBER)
    {
        z = number_to_complex(_computation->node->number);
        return polynomial_new_from_complex(z);
    }

    if (_computation->node->type == NT_WILDCARD)
        return polynomial_new_from_complexG(complex(1, 0), 1, _computation->node->identifier);

    if (_computation->node->type == NT_IDENTIFIER)
    {
        if (is_pi(_computation->node->identifier))
            return polynomial_new_from_complex(complex(PI, 0));
        if (is_e(_computation->node->identifier))
            return polynomial_new_from_complex(complex(E, 0));
        
        return NULL;
    }

    if (_computation->node->type != NT_OPERATOR)
        return NULL;
    
    lhs = computation_to_polynomial(_computation->lhs);
    rhs = computation_to_polynomial(_computation->rhs);

    return _combine_polynomials(lhs, _computation->node->operator, rhs);
}