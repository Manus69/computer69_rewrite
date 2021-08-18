#ifndef NUMBER_H
#define NUMBER_H

#include "why_definitions.h"
#include "frontend_definitions.h"
#include "why_math_complex.h"

enum NUMBER_TYPE
{
    NT_INT, NT_REAL, NT_COMPLEX,
};

struct Number
{
    union
    {
        int_signed n;
        real x;
        Complex z;
    };

    NUMBER_TYPE type;
};

#endif