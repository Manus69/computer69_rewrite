#include "frontend_declarations.h"
#include "terminals.h"

int_signed find_matching_bracket(const char *string)
{
    char *initial;
    char c_symbol;
    int_signed count;

    if (!string)
        return NOT_FOUND;

    initial = (char *)string;
    if (*initial == TERMINALS[O_PAREN])
        c_symbol = TERMINALS[C_PAREN];
    else if (*initial == TERMINALS[O_BRACKET])
        c_symbol = TERMINALS[C_BRACKET];
    else
        return NOT_FOUND;

    string ++;
    count = 1;
    while (*string)
    {
        if (*string == c_symbol)
            count --;
        else if (*string == *initial)
            count ++;
        
        if (count == 0)
            return string - initial - 1;
        
        string ++;
    }
    
    return NOT_FOUND;
}