#include "node.h"
#include "why_memory.h"
#include "frontend_declarations.h"

#include <assert.h>

Node *node_new(void *data, NODE_TYPE type, boolean copy)
{
    Node *node;

    node = allocate(sizeof(Node));
    
    if (type == NT_NUMBER)
        node->number = copy ? number_copy(data) : data;
    else if (type == NT_OPERATOR)
        node->operator = copy ? operator_copy(data) : data;
    else if (type == NT_WILDCARD || type == NT_FUNCTION || type == NT_IDENTIFIER)
        node->identifier = copy ? cstr_copy(data) : data;
    else if (type == NT_MATRIX)
        node->matrix = copy ? matrix_repr_copy(data) : data;
    
    node->type = type;

    return node;
}

Node *node_change_type(Node *node, NODE_TYPE type)
{
    node->type = type;

    return node;
}

Node *node_convert_to_wildcard(Node *node)
{
    if (node->type != NT_IDENTIFIER)
        return NULL;
    
    // string_delete(&node->identifier);
    cstr_delete(&node->identifier);
    node->type = NT_WILDCARD;

    return node;
}

NODE_TYPE node_get_type(const Node *node)
{
    return node->type;
}

static void *_fetch_destructor(NODE_TYPE type)
{
    if (type == NT_NUMBER)
        return number_delete;
    else if (type == NT_MATRIX)
        return matrix_repr_delete;
    else if (type == NT_IDENTIFIER)
        return cstr_delete;
    else if (type == NT_OPERATOR)
        return operator_delete;
    else if (type == NT_FUNCTION)
        return cstr_delete;
    
    return NULL;
}

void node_delete(Node **node)
{
    void (*destructor)();

    #if NO_DELETE
    return ;
    #endif

    if (!node || !*node)
        return ;

    destructor = _fetch_destructor((*node)->type);
    if (destructor)
        destructor(&(*node)->identifier); //
    
    free(*node);
    *node = NULL;
}

Node *node_get_number(String *string)
{
    Number *number;

    number = number_from_string(string);
    
    return number ? node_new(number, NT_NUMBER, FALSE) : NULL;   
}

Node *node_get_operator(String *string)
{
    Operator *operator;

    operator = operator_new(string);

    return operator ? node_new(operator, NT_OPERATOR, FALSE) : NULL;
}

Node *node_get_identifier(String *string)
{
    int_unsigned length;
    char *substring;

    length = id_identifier(string_get_characters(string));
    if (!length)
        return NULL;
    
    substring = string_slice(string, length);
    _string_shift(string, length);

    return node_new(substring, NT_IDENTIFIER, FALSE);
}

Node *node_get_matrix(String *string, const VariableTable *v_table)
{
    MatrixRepr *matrix;
    Node *node;

    matrix = matrix_repr_from_string(string, v_table);
    node = matrix ? node_new(matrix, NT_MATRIX, FALSE) : NULL;    

    return node;
}

Node *node_copy(const Node *node)
{
    Node *new_node;

    new_node = allocate(sizeof(Node));
    new_node->type = node->type;

    if (node->type == NT_OPERATOR)
        new_node->operator = node->operator;
    else if (node->type == NT_NUMBER)
        new_node->number = number_copy(node->number);
    else if (node->type == NT_IDENTIFIER || node->type == NT_FUNCTION)
        new_node->identifier = cstr_copy(node->identifier);
    else if (node->type == NT_MATRIX)
        new_node->matrix = matrix_repr_copy(node->matrix);
    else if (node->type == NT_BUILTIN_FUNCTION)
        new_node->bf_type = node->bf_type;
    // else assert(0);

    return new_node;
}