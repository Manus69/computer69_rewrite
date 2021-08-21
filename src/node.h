#ifndef NODE_H
#define NODE_H

#include "frontend_definitions.h"
#include "why_string_interface.h"

struct Node
{
    union
    {
        Number *number;
        Operator *operator;
        MatrixRepr *matrix;
        String *identifier;
    };
    
    NODE_TYPE type;
};

#endif