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

}

Entity *entity_mult(Entity *lhs, Entity *rhs);
Entity *entity_subtract(Entity *lhs, Entity *rhs);
Entity *entity_divide(Entity *lhs, Entity *rhs);
Entity *entity_mod(Entity *lhs, Entity *rhs);
Entity *entity_power(Entity *lhs, Entity *rhs);
Entity *entity_factorial(Entity *lhs, const Entity *rhs);
Entity *entity_scale(Entity *entity, real factor);