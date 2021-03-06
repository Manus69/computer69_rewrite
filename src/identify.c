#include "frontend_declarations.h"
#include "terminals.h"

boolean contains_i(const char* string)
{
    if (!string || !*string)
        return FALSE;

    if (*string != 'i')
        return FALSE;
    
    if (*(string + 1) == 0)
        return TRUE;
    
    if (id_whitespace(string + 1))
        return TRUE;
    
    if (id_alphanum(string + 1))
        return FALSE;
    
    return TRUE;
}

int_unsigned id_identifier(const char* string)
{
    char* pointer;

    if (!*string)
        return 0;

    if (!id_alpha(string))
        return 0;
    
    pointer = (char* )string;
    while (*pointer)
    {
        if (!id_alphanum(pointer) &&* pointer != '_')
            break ;
        
        pointer ++;
    }

    return pointer - string;
}

int_unsigned id_function_name(const char* string)
{
    int_unsigned length;

    length = id_identifier(string);
    if (!length)
        return 0;
    
    if (string[length] == TERMINALS[O_PAREN])
        return length;
    
    return 0;
}

int_unsigned id_identifier_str(const String* string)
{
    return id_identifier(string_get_characters(string));
}

int_unsigned id_function_name_str(const String* string)
{
    return id_function_name(string_get_characters(string));
}

int_unsigned id_matrix(const String* string)
{
    int_signed index;

    index = find_matching_bracket_str(string, TERMINALS[O_BRACKET], TERMINALS[C_BRACKET]);
    if (index == NOT_FOUND || index < 4)
        return 0;

    return index + 1;
}

int_unsigned id_row(const String* string)
{
    int_signed index;

    index = find_matching_bracket_str(string, TERMINALS[O_BRACKET], TERMINALS[C_BRACKET]);
    if (index == NOT_FOUND || index < 2)
        return 0;
    
    return index + 1;
}