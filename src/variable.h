#ifndef VARIABLE_H
#define VARIABLE_H

#include "frontend_definitions.h"
#include "why_string_interface.h"

struct Variable
{
    String *name;
    Computation *value;
    VARIABLE_TYPE type;
};

#endif