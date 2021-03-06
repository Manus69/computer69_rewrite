#include "frontend_declarations.h"
#include "entity.h"
#include "data_interface.h"

Entity* entity_new(const void* stuff, ENTITY_TYPE type)
{
    Entity* entity;

    entity = allocate(sizeof(Entity));
    entity->number = (void *)stuff;
    entity->type = type;

    data_add_pointer(data, entity, sizeof(Entity));    

    return entity;
}

Entity* entity_new_from_number(const Number* number, boolean copy)
{
    return entity_new(copy ? number_copy(number) : number, ET_NUMBER);
}

Entity* entity_new_from_matrix(const MatrixRepr* matrix, boolean copy)
{
    return entity_new(copy ? matrix_repr_copy(matrix) : matrix, ET_MATRIX);
}

Entity* entity_new_from_computation(const Computation* computation, boolean copy)
{
    return entity_new(copy ? computation_copy(computation) : computation, ET_COMPUTATION);
}

ENTITY_TYPE entity_get_type(const Entity* entity)
{
    return entity->type;
}

static void* _functions[] = {entity_new_from_number, entity_new_from_matrix, entity_new_from_computation, 0};

Entity* entity_copy(const Entity* entity)
{
    void* (*function)();

    if (!entity)
        return NULL;
    
    function =_functions[entity->type];
    
    return function(entity->number, TRUE);
}

void* entity_copy_wrapper(const Entity* entity)
{
    return entity_copy(entity);
}

static void* destructors[] = {number_delete, matrix_repr_delete, computation_delete, 0};

void entity_delete(Entity** entity)
{
    void (*destructor)();

    #if NO_DELETE
        return ;
    #endif

    if (!entity || !*entity)
        return ;
    
    destructor = destructors[(*entity)->type];
    destructor(&(*entity)->number);

    free(*entity);
    *entity = NULL;
}

Computation* computation_from_entity(Entity* entity, boolean copy)
{
    Node*       node;
    ENTITY_TYPE type;

    type = entity_get_type(entity);
    if (type == ET_COMPUTATION)
        return copy ? computation_copy(entity->computation) : entity->computation;
    else if (type == ET_NUMBER)
    {
        node = node_new(entity->number, NT_NUMBER, copy);
        return computation_new(node, FALSE);
    }
    else if (type == ET_MATRIX)
    {
        node = node_new(entity->matrix, NT_MATRIX, copy);
        return computation_new(node, FALSE);
    }

    return NULL;
}
