#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "entity.h"

Computation *computation_replace_wc(Computation *_computation, Computation *value)
{
    if (!_computation)
        return NULL;
    
    if (_computation->node->type == NT_WILDCARD)
    {
        // computation_delete(&_computation);

        return value;
    }

    if (_computation->node->type == NT_MATRIX)
    {
        _computation->node->matrix = matrix_repr_replace_wc(_computation->node->matrix, value);

        return _computation;
    }

    _computation->lhs = computation_replace_wc(_computation->lhs, value);
    _computation->rhs = computation_replace_wc(_computation->rhs, value);

    return _computation;
}

MatrixRepr *matrix_repr_replace_wc(MatrixRepr *matrix, Computation *value)
{
    int_signed n;
    Entity *element;

    n = 0;
    while ((element = matrix_repr_nth(matrix, n)))
    {
        if (element->type == ET_COMPUTATION)
        {
            element->computation = computation_replace_wc(element->computation, value);
        }

        n ++;
    }

    return matrix;
}