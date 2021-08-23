#include "variable.h"
#include "frontend_declarations.h"

#include <assert.h>

static String *_get_arg_name(String *string)
{
    int_signed n;
    String *arg_name;

    n = find_matching_bracket_str(string);
    arg_name = string_substring(string, 1, n - 1);

    return arg_name;
}

static Variable *_create_constant(String *string, VariableTable *v_table, int_signed name_length)
{
    String *name;
    Computation *argument;
    Variable *variable;
    Number *value;

    name = string_substring_allocated(string, 0, name_length);
    _string_shift(string, name_length + 1);

    argument = _parse(string);
    argument = computation_resolve(argument, NULL, v_table);
    value = computation_eval(argument, v_table, NULL);
    computation_delete(&argument);

    argument = computation_new(node_new(value, NT_NUMBER));
    variable = variable_new(name, argument, VT_CONSTANT);

    return variable;
}

static Variable *_create_parametrized(String *string, VariableTable *v_table, int_signed name_length)
{
    String *name;
    String *arg_name;
    Computation *argument;
    Variable *variable;
    
    name = string_substring_allocated(string, 0, name_length);
    if (check_reserved_symbols(name))
        assert(0);
    
    _string_shift(string, name_length);
    arg_name = _get_arg_name(string);    
    _string_shift(string, string_length(arg_name) + 3);

    argument = _parse(string);
    argument = computation_resolve(argument, arg_name, v_table);
    variable = variable_new(name, argument, VT_COMPUTATION);
    string_delete(&arg_name);

    return variable;
}

Variable *variable_create_from_string(String *string, VariableTable *v_table)
{
    int_signed length;

    length = id_function_name_str(string);
    if (length)
        return _create_parametrized(string, v_table, length);

    length = id_identifier(string_get_characters(string));
    if (length)
        return _create_constant(string, v_table, length);

    assert(0);    
}
