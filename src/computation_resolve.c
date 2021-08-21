#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"

static Variable *_check_if_variable(Computation *computation, VariableTable *v_table)
{
    Variable *variable;

    if (!computation)
        return NULL;

    if (computation->node->type != NT_IDENTIFIER)
        return NULL;
    
    variable = v_table_search(v_table, computation->node->identifier);
    
    return variable ? variable : NULL;
}

static Computation *_resolve(Computation *computation, const String *wc_identifier, VariableTable *v_table)
{
    Variable *variable;

    if (!computation)
        return NULL;

    variable = _check_if_variable(computation, v_table);
    if (variable)
    {
        computation_delete(&computation);
        computation = variable_get_value(variable);
    }
    else if (computation->node->type == NT_IDENTIFIER)
    {
        if (string_is_identical(wc_identifier, computation->node->identifier))
            node_convert_to_wildcard(computation->node);
    }
    else
    {
        computation_resolve(computation, wc_identifier, v_table);
    }

    return computation;
}

Computation *computation_resolve(Computation *computation, const String *wc_identifier, VariableTable *v_table)
{
    Variable *variable;

    if (!computation)
        return NULL;
    
    computation->lhs = _resolve(computation->lhs, wc_identifier, v_table);
    variable = _check_if_variable(computation, v_table);
    if (variable)
    {
        computation_delete(&computation);
        computation = variable_get_value(variable);
    }
    else if (computation->node->type == NT_IDENTIFIER)
    {
        if (string_is_identical(wc_identifier, computation->node->identifier))
            node_convert_to_wildcard(computation->node);
    }
    computation->rhs = _resolve(computation->rhs, wc_identifier, v_table);

    return computation;
}