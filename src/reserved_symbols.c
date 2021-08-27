#include "why_memory.h"
#include "why_cstring.h"

const char *RESERVED_SYMBOLS[] =
{
    "abs", "i", "pi", "e", "sin", "cos", "tan", "log", "abs", "sqrt", 0,
};

const char *FUNCTION_STRINGS[] = {"sin", "cos", "tan", "log", "abs", 0};

char *check_reserved_symbols(const char *string)
{
    int_signed n;

    n = 0;
    while (RESERVED_SYMBOLS[n])
    {
        if (cstr_compare(string, RESERVED_SYMBOLS[n]) == 0)
            return (char *)RESERVED_SYMBOLS[n];

        n ++;
    }

    return NULL;
}