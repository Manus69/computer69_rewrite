#include "frontend_declarations.h"
#include "terminals.h"

boolean id_assignment(const String *string)
{
    int_signed length;
    int_signed index;

    length = string_length(string);
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
    int_signed n;
    char c;

    length = string_length(string);
    if (length <= 2)
        return FALSE;
    
    if (string_at(string, length - 1) != TERMINALS[QUESTION])
        return FALSE;
    
    n = length - 2;
    while (n)
    {
        c = string_at(string, n);
        if (!id_whitespace(&c))
            break ;
        
        n --;
    }

    if (string_at(string, n) != TERMINALS[EQUALS])
        return FALSE;
    
    return TRUE;    
}

boolean id_find_roots(const String *string)
{
    int_signed length;

    length = string_length(string);
    if (length < 4)
        return FALSE;
    
    if (string_at(string, length - 1) != TERMINALS[QUESTION])
        return FALSE;
    
    if (string_index_of(string, TERMINALS[EQUALS]) == NOT_FOUND)
        return FALSE;
    
    return TRUE;
}

boolean id_display(const String *string, const VariableTable *v_table)
{
    Variable *_variable;

    _variable = v_table_search(v_table, string_get_characters(string));
    
    return _variable ? TRUE : FALSE;
}

boolean id_statement(const String *string)
{
    return string_length(string) > 0;
}