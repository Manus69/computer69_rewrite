
#include "why_cstring.h"
#include "why_vector_interface.h"
#include "why_copy.h"

Vector* cstr_split(char* string, char delimiter)
{
    Vector*     vector;
    int_signed  index;
    int_signed  length;
    char*       substring;

    vector = vector_new(copy_shallow, memory_delete);

    while (*string)
    {
        index = cstr_index_of(string, delimiter);
        if (index > 0)
        {
            substring = cstr_substring(string, index);
            string += index + 1;
        }
        else if (index == 0)
        {
            substring = cstr_copy("");
            string ++;
        }
        else
        {
            length = cstr_length(string);
            substring = cstr_substring(string, length);
            string += length;
        }

        vector_push(vector, substring);
    }

    return vector;
}