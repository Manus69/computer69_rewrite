#include "variable.h"
#include "frontend_declarations.h"
#include "data_interface.h"

Variable *variable_new(char *name, Entity *entity, boolean parametrized, boolean copy)
{
    Variable *variable;

    variable = allocate(sizeof(Variable));
    variable->name = name;
    variable->entity = copy? entity_copy(entity) : entity;
    variable->parametrized = parametrized;

    data_add_pointer(data, variable, sizeof(Variable));
    data_add_pointer(data, variable->name, sizeof(void *));

    return variable;
}

void variable_delete(Variable **variable)
{
    #if NO_DELETE
    return ;
    #endif

    if (!variable || !*variable)
        return ;
    
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

boolean variable_is_parametrized(const Variable *variable)
{
    return variable->parametrized;
}

Variable *variable_copy(const Variable *variable)
{
    Variable *copy;

    copy = allocate(sizeof(Variable));
    copy->name = cstr_copy(variable->name);
    copy->entity = entity_copy(variable->entity);

    data_add_pointer(data, copy, sizeof(variable));
    data_add_pointer(data, copy->name, sizeof(void *));

    return copy;
}

Variable *variable_assign(Variable *variable, Entity *value, boolean copy)
{
    variable->entity = copy ? entity_copy(value) : value;

    return variable;
}
