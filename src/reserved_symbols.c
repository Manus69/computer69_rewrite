#include "why_string_interface.h"
#include "why_memory.h"

const char *RESERVED_SYMBOLS[] =
{
    "abs", "i", "pi", "e", "sin", "cos", "tan", "log", "abs", "sqrt", 0,
};

const char *FUNCTION_STRINGS[] = {"sin", "cos", "tan", "log", "abs", 0};

char *check_reserved_symbols(const String *string)
{
    int_signed n;

    n = 0;
    while (RESERVED_SYMBOLS[n])
    {
        if (string_is_identical_to(string, RESERVED_SYMBOLS[n]))
            return (char *)RESERVED_SYMBOLS[n];

        n ++;
    }

    return NULL;
}