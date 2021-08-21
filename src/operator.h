#ifndef OPERATOR_H
#define OPERATOR_H

#include "frontend_definitions.h"
#include "why_definitions.h"

struct Operator
{
    OPERATOR_TYPE type;
    byte precedence;
};

#endif