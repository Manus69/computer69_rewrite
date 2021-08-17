#include "why_vector_interface.h"
#include "why_string_interface.h"
#include "why_copy.h"

Vector *string_split(String *string, char delimiter)
{
    Vector *vector;
    String *substring;
    int_signed left_index;
    int_signed right_index;

    vector = vector_new(copy_shallow, string_delete);
    left_index = string_index_of_compliment_from(string, 0, delimiter);
    if (left_index == NOT_FOUND)
        return vector;

    right_index = string_index_of_from(string, left_index + 1, delimiter);

    while (right_index != NOT_FOUND && left_index != NOT_FOUND)
    {
        substring = string_get_substring(string, left_index, right_index);
        vector_push(vector, substring);

        left_index = string_index_of_compliment_from(string, right_index + 1, delimiter);
        right_index = string_index_of_from(string, right_index + 1, delimiter);
    }

    if (left_index != NOT_FOUND)
    {
        substring = string_get_substring_from(string, left_index);
        vector_push(vector, substring);
    }

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