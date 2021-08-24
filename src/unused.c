#include "frontend_declarations.h"

//no reason to use this
void *get_function_by_name(String *name)
{
    void *result;

    if (!name)
        return NULL;

    result = NULL;

    if (string_is_identical_to(name, "sin"))
        result = number_sin;
    else if (string_is_identical_to(name, "cos"))
        result = number_cos;
    else if (string_is_identical_to(name, "tan"))
        result = number_tan;
    else if (string_is_identical_to(name, "log"))
        result = number_log;
    else if (string_is_identical_to(name, "abs"))
        result = number_abs;
    
    if (result)
        _string_shift(name, 3); //careful here

    return result;
}