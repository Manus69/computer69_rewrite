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

Entity *entity_new_from_computation(const Computation *computation)
{
    return entity_new(computation, ET_COMPUTATION);
}

ENTITY_TYPE entity_get_type(const Entity *entity)
{
    return entity->type;
}

Entity *entity_copy(const Entity *entity)
{
    Number *number;
    MatrixRepr *matrix;
    Computation *computation;

    if (entity->type == ET_NUMBER)
    {
        number = number_copy(entity->number);

        return entity_new_from_number(number);
    }
    else if (entity->type == ET_MATRIX)
    {
        matrix = matrix_repr_copy(entity->matrix);

        return entity_new_from_matrix(matrix);
    }
    else if (entity->type == ET_COMPUTATION)
    {
        computation = computation_copy(entity->computation);

        return entity_new_from_computation(computation);
    }

    return NULL;
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


Computation *computation_from_entity(Entity *entity)
{
    ENTITY_TYPE type;
    Node *node;
    MatrixRepr *matrix;
    Number *number;

    type = entity_get_type(entity);
    if (type == ET_COMPUTATION)
        return computation_copy(entity->computation);
    else if (type == ET_NUMBER)
    {
        number = number_copy(entity->number);
        node = node_new(number, NT_NUMBER);

        return computation_new(node);
    }
    else if (type == ET_MATRIX)
    {
        matrix = matrix_repr_copy(entity->matrix);
        node = node_new(matrix, NT_MATRIX);

        return computation_new(node);
    }

    return NULL;
}
