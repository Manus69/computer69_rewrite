#include "variable.h"
#include "frontend_declarations.h"

Variable *variable_new(String *name, Computation *value, VARIABLE_TYPE type)
{
    Variable *variable;

    variable = allocate(sizeof(Variable));
    variable->name = name;
    variable->value = value;
    variable->type = type;

    return variable;
}

void variable_delete(Variable **variable)
{
    if (!variable || !*variable)
        return ;
    
    string_delete(&(*variable)->name);
    computation_delete(&(*variable)->value);

    free(*variable);
    *variable = NULL;
}

int_signed variable_compare(const Variable *lhs, const Variable *rhs)
{
    return string_compare(lhs->name, rhs->name);
}

String *variable_get_name(const Variable *variable)
{
    return variable->name;
}

Computation *variable_get_value(const Variable *variable)
{
    return variable->value;
}

Variable *variable_copy(const Variable *variable)
{
    Variable *copy;

    copy = allocate(sizeof(Variable));
    copy->name = string_copy_deep(variable->name);
    copy->value = computation_copy(variable->value);
    copy->type = variable->type;

    return copy;
}

Variable *variable_assign(Variable *variable, const Computation *value)
{
    computation_delete(&variable->value);
    variable->value = computation_copy(value);

    return variable;
}