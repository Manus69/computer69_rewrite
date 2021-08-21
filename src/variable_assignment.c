#include "variable.h"
#include "frontend_declarations.h"

static String *_get_arg_name(String *string)
{
    int_signed n;
    String *arg_name;

    n = find_matching_bracket_str(string);
    arg_name = string_get_substring(string, 1, n - 1);

    return arg_name;
}

Variable *variable_create_from_string(String *string, VariableTable *v_table)
{
    int_signed length;
    String *name;
    String *arg_name;
    Computation *argument;

    string = string_remove_spaces(string);
    length = id_function_name_str(string);
    if (!length)
        return NULL;

    name = string_get_substring(string, 0, length);
    _string_shift(string, length);
    arg_name = _get_arg_name(string);
    _string_shift(string, string_get_length(arg_name) + 3);
    argument = _parse(string);
}