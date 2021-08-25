#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "operator.h"
#include "entity.h"

#include <assert.h>

static const void *op_functions[] = {number_add, number_subtract, 
number_mult, number_divide, number_mod, number_power, number_factorial, 0};

static const void *op_functionsG[] = {entity_add, entity_subtract, 
entity_mult, entity_divide, entity_mod, entity_power, entity_factorial, 0};

static Number *_get_value(const String *id)
{
    if (!id)
        return NULL;

    if (string_is_identical_to(id, "pi"))
        return number_new_real(PI);
    else if (string_is_identical_to(id, "e"))
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

static Entity *_process_btfG(const Computation *computation, const VariableTable *v_table, Entity *wc_value)
{
    Entity *lhs_value;
    Number *result;

    lhs_value = computation_evalG(computation, v_table, wc_value);
    if (lhs_value->type == ET_MATRIX)
        assert(0);
    
    result = _process_btf(computation, v_table, wc_value->number);

    return entity_new_from_number(result);
}

static Number *_process_function(const Computation *computation, const VariableTable *v_table, Number *wc_value)
{
    Number *lhs_value;
    Number *result;
    Variable *variable;

    variable = v_table_search(v_table, computation->node->identifier);
    if (variable)
    {
        lhs_value = computation_eval(computation->lhs, v_table, wc_value);
        result = computation_eval(variable_get_value(variable), v_table, lhs_value);
        result = number_demote_if_possible(result);
        number_delete(&lhs_value);

        return result;
    }

    assert(0);
}

static Entity *_process_functionG(const Computation *computation, const VariableTable *v_table, Entity *wc_value)
{
    Entity *lhs_value;
    Entity *result;
    Entity *value; //
    Variable *variable;

    variable = v_table_search(v_table, computation->node->identifier);
    if (variable)
    {
        lhs_value = computation_evalG(computation->lhs, v_table, wc_value);
        result = computation_evalG(variable_get_value(variable), v_table, lhs_value);
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

static Entity *_process_idG(const Computation *computation)
{
    return entity_new_from_number(_process_id(computation));
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

static Entity *_process_matrix(const Computation *computation, const VariableTable *v_table, Number *wc_value)
{
    ;
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
        return entity_new_from_number(number_copy(computation->node->number));
    if (computation->node->type == NT_MATRIX)
        assert(0);
    if (computation->node->type == NT_BUILTIN_FUNCTION)
        return _process_btfG(computation, v_table, wc_value);
    if (computation->node->type == NT_FUNCTION)
        return _process_functionG(computation, v_table, wc_value);
    if (computation->node->type == NT_IDENTIFIER)
        return _process_idG(computation);
    if (computation->node->type == NT_WILDCARD && wc_value && wc_value->type == ET_NUMBER)
        return entity_new_from_number(number_copy(wc_value->number));
    if (computation->node->type != NT_OPERATOR)
        assert(0);
    
    lhs_value = computation->lhs ? computation_evalG(computation->lhs, v_table, wc_value) : NULL;
    rhs_value = computation->rhs ? computation_evalG(computation->rhs, v_table, wc_value) : NULL;

    function = op_functionsG[computation->node->operator->type];
    result = function(lhs_value, rhs_value);

    if (result->type == ET_NUMBER)
        result->number = number_demote_if_possible(result->number);

    entity_delete(&lhs_value);
    entity_delete(&rhs_value);

    return result;
}