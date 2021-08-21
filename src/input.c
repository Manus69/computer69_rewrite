#include "frontend_declarations.h"
#include "terminals.h"

boolean id_assignment(const String *string)
{
    int_signed length;
    int_signed index;

    length = string_get_length(string);
    if (length < 3)
        return FALSE;
    
    if (string_at(string, length - 1) == TERMINALS[QUESTION])
        return FALSE;

    index = string_index_of(string, TERMINALS[EQUALS]);
    if (index == NOT_FOUND)
        return FALSE;
    
    return TRUE;
}

boolean id_evaluation(const String *string)
{
    int_signed length;

    length = string_get_length(string);
    if (length <= 2)
        return FALSE;
    
    if (string_at(string, length - 1) != TERMINALS[QUESTION])
        return FALSE;
    
    if (string_at(string, length - 2) != TERMINALS[EQUALS])
        return FALSE;
    
    return TRUE;    
}

boolean id_find_roots(const String *string)
{
    return string ? FALSE : FALSE;
}