#include "frontend_declarations.h"

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