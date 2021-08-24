#ifndef FRONTEND_DEFINITIONS_H
#define FRONTEND_DEFINITIONS_H

#include "why_tree_interface.h"

typedef struct Number Number;
typedef struct MatrixRepr MatrixRepr;
typedef struct Operator Operator;
typedef struct Node Node;
typedef struct Computation Computation;
typedef struct Variable Variable;
typedef struct Entity Entity;

typedef Tree VariableTable;

typedef enum NUMBER_TYPE NUMBER_TYPE;
typedef enum T_CHARS T_CHARS;
typedef enum OPERATOR_TYPE OPERATOR_TYPE;
typedef enum NODE_TYPE NODE_TYPE;
typedef enum VARIABLE_TYPE VARIABLE_TYPE;
typedef enum BULITIN_FUNCTION_TYPE BULITIN_FUNCTION_TYPE;
typedef enum ENTITY_TYPE ENTITY_TYPE;

enum NUMBER_TYPE
{
    NT_INT, NT_REAL, NT_COMPLEX,
};

enum NODE_TYPE
{
    NT_NUMBER, NT_MATRIX, NT_WILDCARD,
    NT_OPERATOR,
    NT_FUNCTION, NT_IDENTIFIER,
    NT_BUILTIN_FUNCTION,
};

enum OPERATOR_TYPE
{
    OT_PLUS, OT_MINUS,
    OT_MULTIPLY, OT_DIVIDE, OT_MOD,
    OT_EXPONENT,
    OT_FACTORIAL,
};

enum BULITIN_FUNCTION_TYPE
{
    BFT_SIN, BFT_COS, BFT_TAN, BFT_LOG, BFT_ABS,
};

enum VARIABLE_TYPE
{
    VT_CONSTANT,
    VT_COMPUTATION,
    VT_MATRIX,
};

enum ENTITY_TYPE
{
    ET_NUMBER,
    ET_MATRIX,
};

#endif