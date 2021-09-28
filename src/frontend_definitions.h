#ifndef FRONTEND_DEFINITIONS_H
#define FRONTEND_DEFINITIONS_H

#include "why_tree_interface.h"
#include "why_vector_interface.h"

#define NO_DELETE       1
#define CHECK_MEMORY    1
#define MATRIX_MAX_SIZE 4
#define FACTORIAL_MAX_N 20
#define WHITE_SPACE     " \t\n\r"

typedef struct Number Number;
typedef struct MatrixRepr MatrixRepr;
typedef struct Operator Operator;
typedef struct Node Node;
typedef struct Computation Computation;
typedef struct Variable Variable;
typedef struct Entity Entity;
typedef struct Data Data;

typedef Tree VariableTable;

typedef enum NUMBER_TYPE NUMBER_TYPE;
typedef enum T_CHARS T_CHARS;
typedef enum OPERATOR_TYPE OPERATOR_TYPE;
typedef enum NODE_TYPE NODE_TYPE;
typedef enum VARIABLE_TYPE VARIABLE_TYPE;
typedef enum BULITIN_FUNCTION_TYPE BULITIN_FUNCTION_TYPE;
typedef enum ENTITY_TYPE ENTITY_TYPE;

extern Vector*  data_vector;
extern Data*    data;

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
    OT_STAR, OT_SLASH, OT_MOD,
    OT_CARET,
    OT_EXCLAM,
};

enum BULITIN_FUNCTION_TYPE
{
    BFT_SIN, BFT_COS, BFT_TAN, BTF_SQRT, BFT_LOG, BTF_LN, BTF_EXP, BFT_ABS,
};

enum VARIABLE_TYPE
{
    VT_CONSTANT,
    VT_MATRIX,
    VT_COMPUTATION,
};

enum ENTITY_TYPE
{
    ET_NUMBER,
    ET_MATRIX,
    ET_COMPUTATION,
};

#endif