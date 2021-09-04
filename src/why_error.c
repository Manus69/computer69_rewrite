#include "why_error.h"
#include "why_definitions.h"

#include <stdio.h>

byte WHY_ERROR = WHY_ERROR_DEFAULT;

const char *error_strings[] = {
"No errors detected",
"It is totally broken",
"Memory error",
"Index error",
"Parse error",
"Syntax error",
"Math error",
"Naming error",
"Evaluation error",
0};

void *error_set(byte type)
{
    WHY_ERROR = type;

    return NULL;
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