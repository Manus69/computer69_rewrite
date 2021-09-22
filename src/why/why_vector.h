#ifndef WHY_VECTOR_H
#define WHY_VECTOR_H

#include "why_definitions.h"

struct Vector
{
    void*       (*copy)();
    void        (*delete)();
    int_signed  (*compare)();

    void**      items;
    int_signed  current_index;
    int_signed  capacity;
};

#endif