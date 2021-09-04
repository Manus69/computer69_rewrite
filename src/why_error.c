#include "why_error.h"
#include "why_definitions.h"

#include <stdio.h>

byte WHY_ERROR;

const char *error_strings[] = {
"No errorss detected",
"It is totally broken",
"Memory error",
"Index error",
"Parse error",
"Syntax error",
"Math error",
0};

void display_error_message(byte type, const char *message)
{
    char *format;

    format = message ? "%s %s\n" : "%s\n";
    fprintf(stderr, format, error_strings[type], message);
}