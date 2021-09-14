#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "why_error.h"
#include "terminals.h"

#include <assert.h>

static char *_get_arg_name(String *string)
{
    int_signed n;
    char *arg_name;

    n = find_matching_bracket_str(string, TERMINALS[O_PAREN], TERMINALS[C_PAREN]);
    if (n < 0)
        return error_set(WHY_ERROR_SYNTAX, string_get_characters(string));
    
    arg_name = string_slice_index(string, 1, n - 1);

    if (cstr_index_of_any(arg_name, WHITE_SPACE) != NOT_FOUND)
    {
        cstr_delete(&arg_name);
        error_set(WHY_ERROR_NAME, " Invalid name");
    }

    return arg_name;
}

static Variable *_build_variable(const Computation *argument, String *string, char *name, char *arg_name)
{
    Entity *value;
    Variable *variable;

    if (argument->node->type == NT_NUMBER)
        value = entity_new_from_number(argument->node->number, TRUE);
    else if (argument->node->type == NT_MATRIX)
        value = entity_new_from_matrix(argument->node->matrix, TRUE);
    else
    {
        value = entity_new_from_computation(argument, FALSE);
    }

    variable = variable_new(name, arg_name, value, FALSE);

    if (string_length(string))
        assert(0);

    return variable;
}

static void *_handle_name_errors(char *name)
{
    error_set(WHY_ERROR_NAME, name);
    cstr_delete(&name);

    return NULL;
}

static void *_handle_reserved_name(char *name, char *arg_name)
{
    error_set(WHY_ERROR_NAME, arg_name);
    cstr_delete(&name);
    cstr_delete(&arg_name);

    return NULL;
}

Variable *_create_parametrized(String *string, const VariableTable *v_table, int_signed name_length)
{
    char *name;
    char *arg_name;
    Computation *argument;
    
    name = string_slice(string, name_length);
    if (check_reserved_symbols(name))
        return _handle_name_errors(name);

    _string_shift(string, name_length);
    if (!(arg_name = _get_arg_name(string)))
        return _handle_name_errors(name);

    if (v_table_search(v_table, arg_name))
        return _handle_reserved_name(name, arg_name);
    
    _string_shift(string, cstr_length(arg_name) + 2);
    skip_over_equals(string);

    argument = parse(string, v_table);
    argument = computation_resolve(argument, arg_name, v_table);

    //
    // if (argument->node->type != NT_MATRIX)
    argument = computation_reduce(argument, v_table, NULL);    
    //

    if (!argument)
    {
        cstr_delete(&name);
        return NULL;
    }
    error_reset();
    
    return _build_variable(argument, string, name, arg_name);
}