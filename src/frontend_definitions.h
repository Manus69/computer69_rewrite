#ifndef FRONTEND_DEFINITIONS_H
#define FRONTEND_DEFINITIONS_H

#include "why_tree_interface.h"

typedef struct Number Number;
typedef struct MatrixRepr MatrixRepr;
typedef struct Operator Operator;
typedef struct Node Node;
typedef struct Computation Computation;
typedef struct Variable Variable;

typedef Tree VariableTable;

typedef enum NUMBER_TYPE NUMBER_TYPE;
typedef enum T_CHARS T_CHARS;
typedef enum OPERATOR_TYPE OPERATOR_TYPE;
typedef enum NODE_TYPE NODE_TYPE;

enum NODE_TYPE
{
    NT_NUMBER, NT_MATRIX, NT_WILDCARD,
    NT_OPERATOR,
    NT_FUNCTION, NT_IDENTIFIER,
};

enum OPERATOR_TYPE
{
    OT_PLUS, OT_MINUS,
    OT_MULTIPLY, OT_DIVIDE, OT_MOD,
    OT_EXPONENT,
    OT_FACTORIAL,
};

#endif