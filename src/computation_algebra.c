#include "frontend_declarations.h"
#include "computation.h"

static Node *_get_op_node(OPERATOR_TYPE type)
{
    Node *node;
    Operator *operator;

    operator = operator_new_from_type(type);
    node = node_new(operator, NT_OPERATOR);

    return node;
}

static Computation *_computation_combine(Computation *lhs, Computation *rhs, OPERATOR_TYPE type)
{
    Computation *result;
    Node *root_node;

    root_node = _get_op_node(type);
    result = computation_new(root_node);
    result->lhs = computation_copy(lhs);
    result->rhs = computation_copy(rhs);

    return result;
}

Computation *computation_increment(Computation *lhs, Computation *rhs)
{
    Computation *root;

    root = computation_new(_get_op_node(OT_PLUS));
    root->lhs = lhs;
    root->rhs = rhs;

    return root;
}

Computation *computation_add(Computation *lhs, Computation *rhs)
{
    return _computation_combine(lhs, rhs, OT_PLUS);
}

Computation *computation_mult(Computation *lhs, Computation *rhs)
{
    return _computation_combine(lhs, rhs, OT_STAR);
}

Computation *computation_subtract(Computation *lhs, Computation *rhs)
{
    return _computation_combine(lhs, rhs, OT_MINUS);
}

Computation *computation_divide(Computation *lhs, Computation *rhs)
{
    return _computation_combine(lhs, rhs, OT_SLASH);
}

Computation *computation_mod(Computation *lhs, Computation *rhs)
{
    return _computation_combine(lhs, rhs, OT_MOD);
}

Computation *computation_power(Computation *lhs, Computation *rhs)
{
    return _computation_combine(lhs, rhs, OT_CARET);
}

Computation *computation_factorial(Computation *lhs, Computation *rhs)
{
    return _computation_combine(lhs, rhs, OT_EXCLAM);
}

Computation *computation_scale(Computation *computation, Number *number)
{
    Computation *factor;

    factor = computation_new(node_new(number_copy(number), NT_NUMBER));

    return computation_mult(computation, factor);
}