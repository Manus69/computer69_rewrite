#ifndef WHY_STRING_H
#define WHY_STRING_H

#include "why_definitions.h"

struct String
{
    char        *characters;
    int_signed  length;
    boolean     allocated;
};

#endif