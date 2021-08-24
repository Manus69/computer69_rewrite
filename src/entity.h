#ifndef ENTITY_H
#define ENTITY_H

#include "frontend_definitions.h"

struct Entity
{
    union
    {
        Number *number;
        MatrixRepr *matrix;
    };

    ENTITY_TYPE type;
};

#endif