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

};

void display_error_message(byte type, const char *message);

#endif