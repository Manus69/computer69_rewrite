#include "frontend_declarations.h"
#include "computation.h"
#include "number.h"
#include "why_error.h"
#include "node.h"
#include "entity.h"

Computation *computation_reduce(Computation *computation, const VariableTable *v_table, Number *wc_value)
{
    Number *result;    
    Computation *_lhs;
    Computation *_rhs;

    if (!computation)
        return NULL;
    
    if (computation->node->type == NT_MATRIX)
        return computation_matrix_reduce(computation, v_table, wc_value);

    if ((result = computation_eval(computation, v_table, wc_value)))
        return computation_new(node_new(result, NT_NUMBER, FALSE), FALSE);
    else if (WHY_ERROR == WHY_ERROR_MATH)
        return NULL;
    else if (!computation->lhs && !computation->rhs)
        return computation;
    
    error_reset();
    if ((_lhs = computation_reduce(computation->lhs, v_table, wc_value)))
    {
        computation->lhs = _lhs;
        return computation;
    }
    else if (WHY_ERROR == WHY_ERROR_MATH)
        return NULL;
    
    error_reset();
    if ((_rhs = computation_reduce(computation->rhs, v_table, wc_value)))
        computation->rhs = _rhs;
    else if (WHY_ERROR == WHY_ERROR_MATH)
        return NULL;
    
    return computation;
}

Computation *computation_matrix_reduce(Computation *_computation, const VariableTable *v_table, Number *wc_value)
{
    Computation *reduced_item;
    Entity *item;
    int_signed n;
    int_signed size;

    if (!_computation || _computation->node->type != NT_MATRIX)
        return NULL;

    n = 0;
    size = matrix_repr_get_n(_computation->node->matrix);
    while (n < size)
    {
        item = matrix_repr_nth(_computation->node->matrix, n);
        if (item->type == ET_COMPUTATION)
            reduced_item = computation_reduce(item->computation, v_table, wc_value);
        matrix_repr_set_nth(_computation->node->matrix, entity_new_from_computation(reduced_item, FALSE), n);
        n ++;
    }

    return _computation;
}