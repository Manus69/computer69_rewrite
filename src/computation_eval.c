#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "operator.h"

#include <assert.h>

static const void *functions[] = {number_add, number_subtract, 
number_mult, number_divide, number_mod, number_power, number_factorial, 0};

Number *computation_eval(const Computation *computation)
{
    Node *node;
    Operator *op;
    Number *(*operation)();
    Number *lhs_value;
    Number *rhs_value;

    if (!computation)
        assert(0);

    node = computation->node;
    if (node->type == NT_NUMBER)
        return node->number;
    
    if (node->type != NT_OPERATOR)
        assert(0);
    
    lhs_value = computation->lhs ? computation_eval(computation->lhs) : NULL;
    rhs_value = computation->rhs ? computation_eval(computation->rhs) : NULL;

    op = node->operator;
    operation = functions[op->type];

    return operation(lhs_value, rhs_value);
}