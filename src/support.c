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

String *string_new_no_space_to_lower(const char *literal)
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
            new_literal[n] = cstr_char_to_lower(*literal);
            n ++;
        }
        literal ++;
    }

    string = string_new_fixed_length(new_literal, n);
    _string_set_allocation(string, TRUE);

    return string;
}

String *string_new_trimmed(const char *characters)
{
    String *string;

    string = string_new_allocated(characters);
    string = string_to_lower(string);
    string = string_trim(string);

    return string;
}

void skip_over_equals(String *string)
{
    string_skip_spaces(string);
    if (string_at(string, 0) == TERMINALS[EQUALS])
        _string_shift(string, 1);
    string_skip_spaces(string);
}

Vector *string_split_and_trim(String *string, char delimiter)
{
    Vector *vector;
    int_signed n;
    String *item;

    if (!(vector = string_split(string, delimiter)))
        return NULL;
    
    n = 0;
    while (n < vector_size(vector))
    {
        item = vector_at(vector, n);
        item = string_trim(item);

        n ++;
    }

    return vector;
}