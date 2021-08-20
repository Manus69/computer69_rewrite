#ifndef OPERATOR_H
#define OPERATOR_H

#include "frontend_definitions.h"
#include "why_definitions.h"

enum OPERATOR_TYPE
{
    OT_U_MINUS,
    OT_PLUS, OT_MINUS,
    OT_MULTIPLY, OT_DIVIDE, OT_MOD,
    OT_EXPONENT,
    OT_FACTORIAL,
};

struct Operator
{
    OPERATOR_TYPE type;
    byte precedence;
};

#endif