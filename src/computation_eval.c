#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "operator.h"
#include "entity.h"

#include "print.h" //

#include <assert.h>

static const void *op_functions[] = {number_add, number_subtract, 
number_mult, number_divide, number_mod, number_power, number_factorial, 0};

static const void *op_functionsG[] = {entity_add, entity_subtract, 
entity_mult, entity_divide, entity_mod, entity_power, entity_factorial, 0};

static Number *_get_value(const char *id)
{
    if (!id)
        return NULL;

    if (cstr_compare(id, "pi") == 0)
        return number_new_real(PI);
    else if (cstr_compare(id, "e") == 0)
        return number_new_real(E);
    
    assert(0);
}

static Number *_process_btf(const Computation *computation, const VariableTable *v_table, Number *wc_value)
{
    Number *(*function)();
    Number *lhs_value;
    Number *result;

    lhs_value = computation_eval(computation->lhs, v_table, wc_value);
    function = get_bft_pointer(computation->node->bf_type);
    if (function)
    {
        result = function(lhs_value);
        result = number_demote_if_possible(result);
        number_delete(&lhs_value);

        return result;
    }

    assert(0);
}

static Entity *_eval_btfG(const Computation *computation, const VariableTable *v_table, Entity *wc_value)
{
    Number *result;
    // Entity *lhs_value;
    
    if (!wc_value)
        result = _process_btf(computation, v_table, NULL);
    else if (wc_value->type == ET_NUMBER)
        result = _process_btf(computation, v_table, wc_value->number);
    else assert(0);

    return entity_new_from_number(result, FALSE);
}

static Number *_process_function(const Computation *computation, const VariableTable *v_table, Number *wc_value)
{
    Number *lhs_value;
    Number *result;
    Variable *variable;
    Entity *value;

    variable = v_table_search(v_table, computation->node->identifier);
    if (variable)
    {
        lhs_value = computation_eval(computation->lhs, v_table, wc_value);
        value = variable_get_value(variable);

        if (entity_get_type(value) != ET_COMPUTATION)
            assert(0);
        
        result = computation_eval(value->computation, v_table, lhs_value);
        result = number_demote_if_possible(result);
        number_delete(&lhs_value);

        return result;
    }

    assert(0);
}

static Entity *_eval_matrix(MatrixRepr *matrix, const VariableTable *v_table, Entity *wc_value)
{
    int_signed n;
    // MatrixRepr *matrix;
    Computation *value;
    Number *number;

    if (wc_value && wc_value->type != ET_NUMBER)
        assert(0);
    
    // matrix = computation->node->matrix;
    n = 0;
    while ((value = matrix_repr_nth(matrix, n)))
    {
        number = computation_eval(value, v_table, wc_value ? wc_value->number : NULL);
        value = computation_new(node_new(number, NT_NUMBER, FALSE), FALSE);
        matrix_repr_set_nth(matrix, value, n);

        n ++;
    }

    return entity_new_from_matrix(matrix, TRUE);
}

static Entity *_eval_functionG(const Computation *computation, const VariableTable *v_table, Entity *wc_value)
{
    Entity *lhs_value;
    Entity *result;
    Entity *argument; //
    Variable *variable;

    variable = v_table_search(v_table, computation->node->identifier);
    if (variable)
    {
        lhs_value = computation_evalG(computation->lhs, v_table, wc_value);
        argument = variable_get_value(variable);

        // if (entity_get_type(argument) != ET_COMPUTATION)
        //     assert(0);
        if (argument->type == ET_COMPUTATION)
            result = computation_evalG(argument->computation, v_table, lhs_value);
        else if (argument->type == ET_MATRIX)
            result = _eval_matrix(argument->matrix, v_table, lhs_value);
        else assert(0);

        if (result->type == ET_NUMBER)
            result->number = number_demote_if_possible(result->number);
        entity_delete(&lhs_value);

        return result;
    }

    assert(0);
}

static Number *_process_id(const Computation *computation)
{
    Number *value;

    value = _get_value(computation->node->identifier);

    return value;
}

static Entity *_eval_idG(const Computation *computation)
{
    return entity_new_from_number(_process_id(computation), FALSE);
}

Number *computation_eval(const Computation *computation, const VariableTable *v_table, Number *wc_value)
{
    Number *(*function)();
    Number *lhs_value;
    Number *rhs_value;
    Number *result;

    if (!computation)
        assert(0);

    if (computation->node->type == NT_NUMBER)
        return number_copy(computation->node->number);
    if (computation->node->type == NT_BUILTIN_FUNCTION)
        return _process_btf(computation, v_table, wc_value);
    if (computation->node->type == NT_FUNCTION)
        return _process_function(computation, v_table, wc_value);
    if (computation->node->type == NT_IDENTIFIER)
        return _process_id(computation);
    if (computation->node->type == NT_WILDCARD && wc_value)
        return number_copy(wc_value);
    if (computation->node->type != NT_OPERATOR)
        assert(0);
    
    lhs_value = computation->lhs ? computation_eval(computation->lhs, v_table, wc_value) : NULL;
    rhs_value = computation->rhs ? computation_eval(computation->rhs, v_table, wc_value) : NULL;

    function = op_functions[computation->node->operator->type];
    result = function(lhs_value, rhs_value);
    result = number_demote_if_possible(result);

    number_delete(&lhs_value);
    number_delete(&rhs_value);

    return result;
}

Entity *computation_evalG(const Computation *computation, const VariableTable *v_table, Entity *wc_value)
{
    Entity *(*function)();
    Entity *lhs_value;
    Entity *rhs_value;
    Entity *result;

    if (!computation)
        assert(0);

    if (computation->node->type == NT_NUMBER)
        return entity_new_from_number(computation->node->number, TRUE);
    if (computation->node->type == NT_MATRIX)
        return _eval_matrix(computation->node->matrix, v_table, wc_value);
    if (computation->node->type == NT_BUILTIN_FUNCTION)
        return _eval_btfG(computation, v_table, wc_value);
    if (computation->node->type == NT_FUNCTION)
        return _eval_functionG(computation, v_table, wc_value);
    if (computation->node->type == NT_IDENTIFIER)
        return _eval_idG(computation);
    if (computation->node->type == NT_WILDCARD && wc_value && wc_value->type == ET_NUMBER)
        return entity_new_from_number(wc_value->number, TRUE);
    if (computation->node->type != NT_OPERATOR)
        assert(0);
    
    lhs_value = computation->lhs ? computation_evalG(computation->lhs, v_table, wc_value) : NULL;
    rhs_value = computation->rhs ? computation_evalG(computation->rhs, v_table, wc_value) : NULL;

    function = op_functionsG[computation->node->operator->type];
    result = function(lhs_value, rhs_value);

    if (result && result->type == ET_NUMBER)
        result->number = number_demote_if_possible(result->number);

    entity_delete(&lhs_value);
    entity_delete(&rhs_value);

    return result;
}