#ifndef WHY_ERROR_H
#define WHY_ERROR_H

#include "why_definitions.h"

extern byte WHY_ERROR;

typedef enum WHY_ERROR_TYPE WHY_ERROR_TYPE;

enum WHY_ERROR_TYPE
{
    WHY_ERROR_DEFAULT,
    WHY_ERROR_TOTAL_BRICK,
    WHY_ERROR_MEMORY,
    WHY_ERROR_INDEX,
    WHY_ERROR_PARSE,
    WHY_ERROR_SYNTAX,
    WHY_ERROR_MATH,
    WHY_ERROR_NAME,
    WHY_ERROR_EVAL,
};

void *error_set(byte type);
void error_display_message(const char *message);
void *error_display_message_return(const char *message);

#endif