#include "variable.h"
#include "frontend_declarations.h"

Variable *variable_new(char *name, Entity *entity, boolean copy)
{
    Variable *variable;

    variable = allocate(sizeof(Variable));
    variable->name = name;
    variable->entity = copy? entity_copy(entity) : entity;

    return variable;
}

void variable_delete(Variable **variable)
{
    if (!variable || !*variable)
        return ;
    
    // string_delete(&(*variable)->name);
    cstr_delete(&(*variable)->name);
    entity_delete(&(*variable)->entity);

    free(*variable);
    *variable = NULL;
}

int_signed variable_compare(const Variable *lhs, const Variable *rhs)
{
    return cstr_compare(lhs->name, rhs->name);
}

char *variable_get_name(const Variable *variable)
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
    copy->name = cstr_copy(variable->name);
    copy->entity = entity_copy(variable->entity);

    return copy;
}

// Variable *variable_assign_computation(Variable *variable, const Computation *value)
// {
//     entity_delete(&variable->entity);
//     variable->entity = entity_new_from_computation(computation_copy(value));

//     return variable;
// }

Variable *variable_assign(Variable *variable, Entity *value, boolean copy)
{
    entity_delete(&variable->entity);
    variable->entity = copy ? entity_copy(value) : value;

    return variable;
}
