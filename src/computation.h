#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "frontend_definitions.h"

struct Computation
{
    Node*           node;
    Computation*    lhs;
    Computation*    rhs;
};

#endif