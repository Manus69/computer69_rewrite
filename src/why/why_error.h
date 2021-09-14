#ifndef WHY_ERROR_H
#define WHY_ERROR_H

#include "why_definitions.h"

extern int_unsigned WHY_ERROR;
extern char *error_string;

typedef enum WHY_ERROR_TYPE WHY_ERROR_TYPE;

enum WHY_ERROR_TYPE
{
    WHY_ERROR_DEFAULT,
    WHY_ERROR_GENERIC,
    WHY_ERROR_TOTAL_BRICK,
    WHY_ERROR_MEMORY,
    WHY_ERROR_INDEX,
    WHY_ERROR_PARSE,
    WHY_ERROR_SYNTAX,
    WHY_ERROR_MATH,
    WHY_ERROR_NAME,
    WHY_ERROR_SYMBOL,
    WHY_ERROR_EVAL,
    WHY_ERROR_CONV,
};

void *error_set(int_unsigned type, const char *_error_message);
void error_display();
void error_reset();
void error_display_message(const char *message);
void *error_display_message_return(const char *message);
void error_display_custom(const char *message);
void *error_display_custom_return(const char *message);

#endif