#include "frontend_declarations.h"
#include "entity.h"

Entity *entity_new(const void *stuff, ENTITY_TYPE type)
{
    Entity *entity;

    entity = allocate(sizeof(Entity));
    entity->number = (void *)stuff;
    entity->type = type;

    return entity;
}

Entity *entity_new_from_number(const Number *number)
{
    return entity_new(number, ET_NUMBER);
}

Entity *entity_new_from_matrix(const MatrixRepr *matrix)
{
    return entity_new(matrix, ET_MATRIX);
}

void entity_delete(Entity **entity)
{
    if (!entity || !*entity)
        return ;
    
    if ((*entity)->type == ET_NUMBER)
        number_delete(&(*entity)->number);
    else
        matrix_repr_delete(&(*entity)->matrix);

    free(*entity);
    *entity = NULL;
}

Entity *entity_add(Entity *lhs, Entity *rhs)
{
    Number *number;
    MatrixRepr *matrix;

    if (lhs->type != rhs->type)
        return NULL;

    if (lhs->type == ET_NUMBER)
    {
        number = number_add(lhs->number, rhs->number);

        return entity_new_from_number(number);
    }
    else
    {
        matrix = matrix_repr_add(lhs->matrix, rhs->matrix);

        return entity_new_from_matrix(matrix);
    }
}

Entity *entity_mult(Entity *lhs, Entity *rhs)
{
    Number *number;
    MatrixRepr *matrix;

    if (lhs->type == ET_NUMBER && rhs->type == ET_NUMBER)
    {
        number = number_mult(lhs, rhs);

        return entity_new_from_number(number);
    }
    else if (lhs->type == ET_NUMBER && rhs->type == ET_MATRIX)
    {
        matrix = matrix_repr_scale(rhs->matrix, lhs->number);

        return entity_new_from_matrix(matrix);
    }
    else if (lhs->type == ET_MATRIX && rhs->type == ET_MATRIX)
    {
        matrix = matrix_repr_mult(lhs, rhs);

        return matrix;
    }

    return NULL;
}

Entity *entity_subtract(Entity *lhs, Entity *rhs)
{
    ;
}

Entity *entity_divide(Entity *lhs, Entity *rhs)
{
    ;
}

Entity *entity_mod(Entity *lhs, Entity *rhs)
{
    ;
}

Entity *entity_power(Entity *lhs, Entity *rhs)
{
    ;
}

Entity *entity_factorial(Entity *lhs, Entity *rhs)
{
    ;
}