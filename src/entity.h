#ifndef ENTITY_H
#define ENTITY_H

#include "frontend_definitions.h"

struct Entity
{
    union
    {
        Number*         number;
        MatrixRepr*     matrix;
        Computation*    computation;
    };

    ENTITY_TYPE type;
};

#endif