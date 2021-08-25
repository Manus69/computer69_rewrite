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

static void _resolve_matrix(MatrixRepr *matrix, const String *wc_identifier, const VariableTable *v_table)
{
    Computation *computation;
    int_signed j;
    int_signed k;
    int_signed n_rows;
    int_signed n_cols;

    j = 0;
    n_rows = matrix_repr_n_rows(matrix);
    n_cols = matrix_repr_n_cols(matrix);
    while (j < n_rows)
    {
        k = 0;
        while (k < n_cols)
        {
            computation = matrix_repr_at(matrix, j, k);
            computation = computation_resolve(computation, wc_identifier, v_table);
            matrix_repr_set(matrix, computation, j, k);

            k ++;
        }

        j ++;
    }
}

static Computation *_resolve_node(Computation *computation, const String *wc_identifier, const VariableTable *v_table)
{
    Variable *variable;
    Entity *value;

    variable = _check_if_variable(computation, v_table);
    if (variable)
    {
        computation_delete(&computation);
        // computation = computation_copy(variable_get_value(variable));
        value = variable_get_value(variable);
        computation = computation_from_entity(value);
    }
    else if (computation->node->type == NT_IDENTIFIER)
    {
        if (string_is_identical(wc_identifier, computation->node->identifier))
            node_convert_to_wildcard(computation->node);
    }
    else if (computation->node->type == NT_MATRIX)
    {
        _resolve_matrix(computation->node->matrix, wc_identifier, v_table);
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