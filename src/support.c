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
            return string - initial;
        
        string ++;
    }
    
    return NOT_FOUND;
}

int_signed find_matching_bracket_str(const String *string)
{
    char *characters;

    characters = string_get_characters(string);

    return find_matching_bracket(characters);
}

String *string_new_no_space(const char *literal)
{
    String *string;
    char *new_literal;
    int_signed length;
    int_signed n;

    length = cstr_length(literal);
    new_literal = memory_zero(length + 1);
    n = 0;
    while (*literal)
    {
        if (!id_whitespace(literal))
        {
            new_literal[n] = *literal;
            n ++;
        }
        literal ++;
    }

    string = string_new_fixed_length(new_literal, n);
    _string_set_allocation(string, TRUE);

    return string;
}
