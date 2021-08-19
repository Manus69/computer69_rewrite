#ifndef NODE_H
#define NODE_H

#include "frontend_definitions.h"
#include "why_string_interface.h"

enum NODE_TYPE
{
    NT_NUMBER, NT_MATRIX, NT_WILDCARD,
    NT_OPERATOR,
    NT_FUNCTION, NT_UNDETERMINED,
};

struct Node
{
    union
    {
        Number *number;
        MatrixRepr *matrix;
        String *identifier;
    };
    NODE_TYPE type;
};

#endif