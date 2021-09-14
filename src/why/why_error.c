#include "why_error.h"
#include "why_definitions.h"
#include "why_cstring.h"

#include <stdio.h>

int_unsigned WHY_ERROR = WHY_ERROR_DEFAULT;
char *error_string = NULL;

const char *error_strings[] = {
"No errors detected",
"Error",
"It is totally broken",
"Memory error",
"Index error",
"Parse error",
"Syntax error",
"Math error",
"Name error",
"Unknown symbol error",
"Evaluation error",
"Conversion error",
0};

void *error_set(int_unsigned type, const char *_error_string)
{
    if (WHY_ERROR != WHY_ERROR_DEFAULT)
        return NULL;
    
    WHY_ERROR = type;
    if (error_string)
    {
        free(error_string);
    }
    
    error_string = cstr_copy(_error_string);

    return NULL;
}

void error_reset()
{
    cstr_delete(&error_string);
    WHY_ERROR = WHY_ERROR_DEFAULT;
}

void error_display()
{
    char *format;

    format = error_string ? "%s %s\n" : "%s\n";
    fprintf(stderr, format, error_strings[WHY_ERROR], error_string);

    error_reset();
}

void error_display_message(const char *message)
{
    char *format;

    format = message ? "%s at %s\n" : "%s\n";
    fprintf(stderr, format, error_strings[WHY_ERROR], message);
}

void *error_display_message_return(const char *message)
{
    error_display_message(message);

    return NULL;
}

void error_display_custom(const char *message)
{
    fprintf(stderr, "%s", message);
}

void *error_display_custom_return(const char *message)
{
    error_display_custom(message);

    return NULL;
}