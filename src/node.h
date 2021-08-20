#ifndef NODE_H
#define NODE_H

#include "frontend_definitions.h"
#include "why_string_interface.h"

enum NODE_TYPE
{
    NT_NUMBER, NT_MATRIX, NT_WILDCARD,
    NT_OPERATOR,
    NT_FUNCTION, NT_IDENTIFIER,
};

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