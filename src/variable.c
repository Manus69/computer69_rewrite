#include "variable.h"
#include "frontend_declarations.h"

Variable *variable_new(String *name, Entity *entity)
{
    Variable *variable;

    variable = allocate(sizeof(Variable));
    variable->name = name;
    variable->entity = entity;

    return variable;
}

void variable_delete(Variable **variable)
{
    if (!variable || !*variable)
        return ;
    
    string_delete(&(*variable)->name);
    entity_delete(&(*variable)->entity);

    free(*variable);
    *variable = NULL;
}

Variable *variable_new_from_computation(String *name, Computation *computation)
{
    Entity *value;

    value = entity_new_from_computation(computation);

    return variable_new(name, value);
}

int_signed variable_compare(const Variable *lhs, const Variable *rhs)
{
    return string_compare(lhs->name, rhs->name);
}

String *variable_get_name(const Variable *variable)
{
    return variable->name;
}

Entity *variable_get_value(const Variable *variable)
{
    return variable->entity;
}

VARIABLE_TYPE variable_get_type(const Variable *variable)
{
    return (VARIABLE_TYPE)entity_get_type(variable->entity);
}

Variable *variable_copy(const Variable *variable)
{
    Variable *copy;

    copy = allocate(sizeof(Variable));
    copy->name = string_copy_deep(variable->name);
    copy->entity = entity_copy(variable->entity);

    return copy;
}

Variable *variable_assign_computation(Variable *variable, const Computation *value)
{
    entity_delete(&variable->entity);
    variable->entity = entity_new_from_computation(computation_copy(value));

    return variable;
}

Variable *variable_assign(Variable *variable, Entity *value)
{
    entity_delete(&variable->entity);
    variable->entity = entity_copy(value);

    return variable;
}