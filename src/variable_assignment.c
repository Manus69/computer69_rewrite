#include "variable.h"
#include "frontend_declarations.h"
#include "terminals.h"
#include "computation.h"
#include "node.h"

#include "print.h"//

#include <assert.h>
#include <stdio.h> //

static char *_get_arg_name(String *string)
{
    int_signed n;
    char *arg_name;

    n = find_matching_bracket_str(string, TERMINALS[O_PAREN], TERMINALS[C_PAREN]);
    arg_name = string_slice_index(string, 1, n - 1);

    return arg_name;
}

Variable *variable_create_with_name(String *string, const VariableTable *v_table, char *name)
{
    Computation *argument;
    Variable *variable;
    Entity *value;

    argument = _parse(string, v_table);
    argument = computation_resolve(argument, NULL, v_table);

    // print_computation(argument);
    // fflush(NULL);

    value = computation_evalG(argument, v_table, NULL);
    computation_delete(&argument);

    if (entity_get_type(value) == ET_COMPUTATION)
        assert(0);

    variable = variable_new(name, value, FALSE);

    if (string_length(string))
        assert(0);

    return variable;
}

static Variable *_create_constant(String *string, const VariableTable *v_table, int_signed name_length)
{
    char *name;

    name = string_slice(string, name_length);
    _string_shift(string, name_length + 1);

    return variable_create_with_name(string, v_table, name);
}

static Variable *_create_parametrized(String *string, const VariableTable *v_table, int_signed name_length)
{
    char *name;
    char *arg_name;
    Computation *argument;
    Variable *variable;
    Entity *value;
    
    name = string_slice(string, name_length);
    if (check_reserved_symbols(name))
        assert(0);

    _string_shift(string, name_length);
    arg_name = _get_arg_name(string);
    if (v_table_search(v_table, arg_name))
        assert(0);
    
    _string_shift(string, cstr_length(arg_name) + 3);

    argument = _parse(string, v_table);

    #if DBG
    print_computation(argument);
    printf("\n");
    #endif

    argument = computation_resolve(argument, arg_name, v_table);

    #if DBG
    print_computation(argument);
    printf("\n");
    #endif

    cstr_delete(&arg_name);
    // value = entity_new_from_computation(argument, TRUE);

    if (argument->node->type == NT_NUMBER)
    {
        value = entity_new_from_number(argument->node->number, TRUE);
        computation_delete(&argument);
    }
    else if (argument->node->type == NT_MATRIX)
    {
        value = entity_new_from_matrix(argument->node->matrix, TRUE);
        // computation_delete(&argument);
    }
    else
    {
        value = entity_new_from_computation(argument, FALSE);
        // value = entity_new_from_computation(argument, TRUE);

    }

    // computation_delete(&argument);
    variable = variable_new(name, value, FALSE);

    if (string_length(string))
        assert(0);
    
    return variable;
}

Variable *variable_create_from_string(String *string, const VariableTable *v_table)
{
    int_signed length;
    int_signed index;

    index = string_index_of(string, '=');
    length = id_function_name_str(string);
    if (length && index != NOT_FOUND)
        return _create_parametrized(string, v_table, length);

    length = id_identifier(string_get_characters(string));
    if (length && index != NOT_FOUND)
        return _create_constant(string, v_table, length);

    return variable_create_with_name(string, v_table, NULL); 
}
