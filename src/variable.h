#ifndef VARIABLE_H
#define VARIABLE_H

#include "frontend_definitions.h"
#include "why_string_interface.h"

struct Variable
{
    Entity*         entity;
    char*           name;
    char*           initial_parameter;
    boolean         parametrized;
};

#endif