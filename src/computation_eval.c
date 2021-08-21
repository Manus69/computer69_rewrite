#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "operator.h"

#include <assert.h>

static const void *functions[] = {number_add, number_subtract, 
number_mult, number_divide, number_mod, number_power, number_factorial, 0};

Number *computation_eval(const Computation *computation)
{
    Operator *op;
    Number *(*operation)();
    Number *lhs_value;
    Number *rhs_value;
    Number *result;

    if (!computation)
        assert(0);

    if (computation->node->type == NT_NUMBER)
        return number_copy(computation->node->number);
    
    if (computation->node->type != NT_OPERATOR)
        assert(0);
    
    lhs_value = computation->lhs ? computation_eval(computation->lhs) : NULL;
    rhs_value = computation->rhs ? computation_eval(computation->rhs) : NULL;

    op = computation->node->operator;
    operation = functions[op->type];
    result = operation(lhs_value, rhs_value);

    number_delete(&lhs_value);
    number_delete(&rhs_value);

    return result;
}