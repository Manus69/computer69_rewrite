#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "entity.h"
#include "variable.h"
#include "why_error.h"

#include <assert.h>

static Variable *_check_if_variable(Computation *computation, const VariableTable *v_table)
{
    Variable *variable;

    if (!computation)
        return NULL;

    if (computation->node->type != NT_IDENTIFIER && computation->node->type != NT_FUNCTION)
        return NULL;
    
    variable = v_table_search(v_table, computation->node->identifier);
    
    return variable;
}

static void _resolve_matrix(MatrixRepr *matrix, const char *wc_identifier, const VariableTable *v_table)
{
    Entity *item;
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
            item = matrix_repr_at(matrix, j, k);
            if (item->type == ET_COMPUTATION)
                item->computation = computation_resolve(item->computation, wc_identifier, v_table);
            
            matrix_repr_set(matrix, item, j, k);

            k ++;
        }

        j ++;
    }
}

static Computation *_resolve_node(Computation *computation, const char *wc_identifier, const VariableTable *v_table)
{
    Variable *variable;
    Entity *value;
    Computation *copy;
    MatrixRepr *matrix;

    variable = _check_if_variable(computation, v_table);
    if (variable)
    {
        if (variable_get_type(variable) == VT_CONSTANT)
        {
            value = variable_get_value(variable);
            computation = computation_from_entity(value, TRUE);
        }
        else if (variable_get_type(variable) == VT_COMPUTATION)
        {
            copy = computation_copy(variable->entity->computation);
            if (computation->lhs) ///
                copy = computation_replace_wc(copy, computation->lhs);
            computation = copy;
        }
        else if (variable_get_type(variable) == VT_MATRIX)
        {
            matrix = matrix_repr_copy(variable->entity->matrix);
            if (computation->lhs) ////
                matrix = matrix_repr_replace_wc(matrix, computation->lhs);
            computation = computation_from_entity(entity_new_from_matrix(matrix, FALSE), FALSE);            
        }
    }
    else if (computation->node->type == NT_IDENTIFIER)
    {
        if (cstr_compare(wc_identifier, computation->node->identifier) == 0)
            node_convert_to_wildcard(computation->node);
        else if (!check_reserved_symbols(computation->node->identifier))
            error_set(WHY_ERROR_SYMBOL, computation->node->identifier);
    }
    else if (computation->node->type == NT_MATRIX)
        _resolve_matrix(computation->node->matrix, wc_identifier, v_table);

    return computation;
}

Computation *computation_resolve(Computation *computation, const char *wc_identifier, const VariableTable *v_table)
{
    if (!computation)
        return NULL;

    computation->lhs = computation_resolve(computation->lhs, wc_identifier, v_table);

    if(!(computation = _resolve_node(computation, wc_identifier, v_table)))
        return error_set(WHY_ERROR_GENERIC, " could not resolve symbols");

    computation->rhs = computation_resolve(computation->rhs, wc_identifier, v_table);    

    return WHY_ERROR == WHY_ERROR_DEFAULT ? computation : NULL;
}