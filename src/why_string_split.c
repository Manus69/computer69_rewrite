#include "why_vector_interface.h"
#include "why_string_interface.h"
#include "why_copy.h"

Vector *string_split(String *string, char delimiter)
{
    Vector      *vector;
    String      *element;
    int_signed  index;
    int_signed  length;

    vector = vector_new(copy_shallow, string_delete);

    while ((length = string_length(string)))
    {
        index = string_index_of(string, delimiter);
        if (index > 0)
        {
            element = string_substring(string, 0, index);
            _string_shift(string, index + 1);
        }
        else if (index == NOT_FOUND)
        {
            element = string_substring_from(string, 0);
            _string_shift(string, length);
        }
        else
        {
            element = string_new("");
            _string_shift(string, 1);
        }
        vector_push(vector, element);
    }

    _string_rewind(string);
    return vector;
}

Vector *string_split_cstar(char *c_string, char delimiter)
{
    String *string;
    Vector *vector;

    string = string_new(c_string);
    vector = string_split(string, delimiter);
    string_delete(&string);

    return vector;
}