#include "frontend_declarations.h"
#include "terminals.h"

int_signed find_matching_bracket(const char *string, char o_symbol, char c_symbol)
{
    char *initial;
    int_signed count;

    if (!string || *string != o_symbol)
        return NOT_FOUND;

    initial = (char *)string;
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

int_signed find_matching_bracket_str(const String *string, char o_symbol, char c_symbol)
{
    char *characters;

    characters = string_get_characters(string);

    return find_matching_bracket(characters, o_symbol, c_symbol);
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
