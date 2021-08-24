#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"

static Variable *_check_if_variable(Computation *computation, const VariableTable *v_table)
{
    Variable *variable;

    if (!computation)
        return NULL;

    if (computation->node->type != NT_IDENTIFIER)
        return NULL;
    
    variable = v_table_search(v_table, computation->node->identifier);
    
    return variable ? variable : NULL;
}

static Computation *_resolve_node(Computation *computation, const String *wc_identifier, const VariableTable *v_table)
{
    Variable *variable;

    variable = _check_if_variable(computation, v_table);
    if (variable)
    {
        computation_delete(&computation);
        computation = computation_copy(variable_get_value(variable));
    }
    else if (computation->node->type == NT_IDENTIFIER)
    {
        if (string_is_identical(wc_identifier, computation->node->identifier))
            node_convert_to_wildcard(computation->node);
    }
    else if (computation->node->type == NT_FUNCTION)
    {
        ;
    }

    return computation;
}

Computation *computation_resolve(Computation *computation, const String *wc_identifier, const VariableTable *v_table)
{
    if (!computation)
        return NULL;

    computation->lhs = computation_resolve(computation->lhs, wc_identifier, v_table);

    computation = _resolve_node(computation, wc_identifier, v_table);

    computation->rhs = computation_resolve(computation->rhs, wc_identifier, v_table);    

    return computation;
}