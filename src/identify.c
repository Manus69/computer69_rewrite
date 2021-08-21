#include "frontend_declarations.h"
#include "terminals.h"

int_unsigned id_identifier(const char *string)
{
    char *pointer;

    if (!*string)
        return 0;

    if (!id_alpha(string))
        return 0;
    
    pointer = (char *)string;
    while (*pointer)
    {
        if (!id_alphanum(pointer) && *pointer != '_')
            break ;
        
        pointer ++;
    }

    return pointer - string;
}

int_unsigned id_function_name(const char *string)
{
    int_unsigned length;

    length = id_identifier(string);
    if (!length)
        return 0;
    
    if (string[length] == TERMINALS[O_PAREN])
        return length;
    
    return 0;
}

int_unsigned id_identifier_str(const String *string)
{
    return id_identifier(string_get_characters(string));
}

int_unsigned id_function_name_str(const String *string)
{
    return id_function_name(string_get_characters(string));
}