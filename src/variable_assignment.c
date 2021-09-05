#include "variable.h"
#include "frontend_declarations.h"
#include "terminals.h"
#include "computation.h"
#include "node.h"
#include "why_error.h"

#include "print.h"//

#include <assert.h>

Variable *_create_parametrized(String *string, const VariableTable *v_table, int_signed name_length);

static void *_handle_parse_errors(const String *string, char *name)
{
    cstr_delete(&name);
    if (string_length(string))
    {
        error_set(WHY_ERROR_PARSE, string_get_characters(string));
    }
    
    return NULL;
}

static void *_handle_eval_errors(char *name)
{
    cstr_delete(&name);
    
    return error_set(WHY_ERROR_EVAL, NULL);
}

Variable *variable_create_named(String *string, const VariableTable *v_table, char *name)
{
    Computation *argument;
    Variable *variable;
    Entity *value;

    argument = _parse(string, v_table);
    if (!argument || string_length(string))
        return _handle_parse_errors(string, name);

    argument = computation_resolve(argument, NULL, v_table);
    value = computation_evalG(argument, v_table, NULL);
    
    if (!value || entity_get_type(value) == ET_COMPUTATION)
        return _handle_eval_errors(name);

    variable = variable_new(name, value, FALSE, FALSE);

    if (string_length(string))
        assert(0);

    return variable;
}

static Variable *_create_constant(String *string, const VariableTable *v_table, int_signed name_length)
{
    char *name;

    name = string_slice(string, name_length);
    _string_shift(string, name_length);
    skip_over_equals(string);

    return variable_create_named(string, v_table, name);
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

    return variable_create_named(string, v_table, NULL); 
}
