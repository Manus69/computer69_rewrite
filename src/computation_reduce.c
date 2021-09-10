#include "frontend_declarations.h"
#include "computation.h"
#include "number.h"
#include "why_error.h"

Computation *computation_reduce(Computation *computation, const VariableTable *v_table, Number *wc_value)
{
    Number *lhs;
    Number *rhs;
    Number *result;

    if (!computation)
        return NULL;
    
    result = computation_eval(computation, v_table, wc_value);
    if (result)
        return computation_new(node_new(result, NT_NUMBER, FALSE), FALSE);
    
    lhs = computation_eval(computation->lhs, v_table, wc_value);
    if (lhs)
    {
        computation->lhs = computation_new(node_new(lhs, NT_NUMBER, FALSE), FALSE);
        return computation;
    }
    
    rhs = computation_eval(computation->rhs, v_table, wc_value);
    if (rhs)
    {
        computation->rhs = computation_new(node_new(rhs, NT_NUMBER, FALSE), FALSE);
    }

    return computation;
}