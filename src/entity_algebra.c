#include "frontend_declarations.h"
#include "entity.h"

#include <assert.h>

Entity *entity_add(Entity *lhs, Entity *rhs)
{
    Number *number;
    MatrixRepr *matrix;
    Computation *computation;

    if (lhs->type != rhs->type)
        return NULL;

    if (lhs->type == ET_NUMBER)
    {
        number = number_add(lhs->number, rhs->number);

        return entity_new_from_number(number, FALSE);
    }
    else if (lhs->type == ET_COMPUTATION)
    {
        computation = computation_add(lhs->computation, rhs->computation);

        return entity_new_from_computation(computation, FALSE);
    }
    else
    {
        matrix = matrix_repr_add(lhs->matrix, rhs->matrix);

        return entity_new_from_matrix(matrix, FALSE);
    }

    return NULL;
}

Entity *entity_increment(Entity *lhs, Entity *rhs)
{
    if (lhs->type != rhs->type)
        return NULL;
    
    if (lhs->type == ET_NUMBER)
    {
        lhs->number = number_increment(lhs->number, rhs->number);

        return lhs;
    }
    else if (lhs->type == ET_COMPUTATION)
    {
        lhs->computation = computation_increment(lhs->computation, rhs->computation);

        return lhs;
    }
    
    assert(0);
}

Entity *entity_mult(Entity *lhs, Entity *rhs)
{
    Number *number;
    MatrixRepr *matrix;
    Computation *_computation;

    if (!lhs || !rhs)
        return NULL;
    if (lhs->type == ET_NUMBER && rhs->type == ET_NUMBER)
    {
        number = number_mult(lhs->number, rhs->number);

        return entity_new_from_number(number, FALSE);
    }
    else if (lhs->type == ET_NUMBER && rhs->type == ET_MATRIX)
    {
        matrix = matrix_repr_scale(rhs->matrix, lhs->number);

        return entity_new_from_matrix(matrix, FALSE);
    }
    else if (lhs->type == ET_MATRIX && rhs->type == ET_MATRIX)
    {
        matrix = matrix_repr_mult(lhs->matrix, rhs->matrix);

        return entity_new_from_matrix(matrix, FALSE);
    }
    else if (lhs->type == ET_COMPUTATION && rhs->type == ET_COMPUTATION)
    {
        _computation = computation_mult(lhs->computation, rhs->computation);

        return entity_new_from_computation(_computation, FALSE);
    }

    return NULL;
}

Entity *entity_subtract(Entity *lhs, Entity *rhs)
{
    Number *number;
    MatrixRepr *matrix;

    if (lhs->type == ET_NUMBER && !rhs)
    {
        number = number_subtract(lhs->number, NULL);

        return entity_new_from_number(number, FALSE);
    }
    else if (lhs->type == ET_COMPUTATION && !rhs)
    {
        return entity_new_from_computation(computation_subtract(lhs->computation, NULL), FALSE);
    }
    else if (lhs->type == ET_COMPUTATION && rhs->type == ET_COMPUTATION)
    {
        return entity_new_from_computation(computation_subtract(lhs->computation, rhs->computation), FALSE);
    }
    else if (lhs->type == ET_NUMBER && rhs->type == ET_NUMBER)
    {
        number = number_subtract(lhs->number, rhs->number);

        return entity_new_from_number(number, FALSE);
    }
    else if (lhs->type == ET_MATRIX && rhs->type == ET_MATRIX)
    {
        matrix = matrix_repr_subtract(lhs->matrix, rhs->matrix);

        return entity_new_from_matrix(matrix, FALSE);
    }

    return NULL;
}

Entity *entity_divide(Entity *lhs, Entity *rhs)
{
    Number *number;

    if (lhs->type == ET_NUMBER && rhs->type == ET_NUMBER)
    {
        number = number_divide(lhs->number, rhs->number);

        return entity_new_from_number(number, FALSE);
    }
    if (lhs->type == ET_COMPUTATION && rhs->type == ET_COMPUTATION)
    {
        return entity_new_from_computation(computation_divide(lhs->computation, rhs->computation), FALSE);
    }

    return NULL;
}

Entity *entity_mod(Entity *lhs, Entity *rhs)
{
    Number *number;

    if (lhs->type == ET_NUMBER && rhs->type == ET_NUMBER)
    {
        number = number_mod(lhs->number, rhs->number);

        return entity_new_from_number(number, FALSE);
    }
    if (lhs->type == ET_COMPUTATION && rhs->type == ET_COMPUTATION)
    {
        return entity_new_from_computation(computation_mod(lhs->computation, rhs->computation), FALSE);
    }

    return NULL;
}

Entity *entity_power(Entity *lhs, Entity *rhs)
{
    Number *number;
    MatrixRepr *matrix;
    Computation *_computation;

    if (lhs->type == ET_NUMBER && rhs->type == ET_NUMBER)
    {
        number = number_power(lhs->number, rhs->number);

        return entity_new_from_number(number, FALSE);
    }
    else if (lhs->type == ET_MATRIX && rhs->type == ET_NUMBER)
    {
        matrix = matrix_repr_power(lhs->matrix, rhs->number);

        return entity_new_from_matrix(matrix, FALSE);
    }
    else if (lhs->type == ET_COMPUTATION && rhs->type == ET_NUMBER)
    {
        ; //why?
    }
    else if (lhs->type == ET_COMPUTATION && rhs->type == ET_COMPUTATION)
    {
        _computation = computation_power(lhs->computation, rhs->computation);

        return entity_new_from_computation(_computation, FALSE);
    }

    return NULL;
}

Entity *entity_factorial(Entity *lhs, Entity *rhs)
{
    Number *number;
    Computation *_computation;

    if (lhs->type == ET_NUMBER && !rhs)
    {
        number = number_factorial(lhs->number, NULL);

        return entity_new_from_number(number, FALSE);
    }
    if (lhs->type == ET_COMPUTATION && !rhs)
    {
        _computation = computation_factorial(lhs->computation, NULL);

        return entity_new_from_computation(_computation, FALSE);
    }

    return NULL;
}
