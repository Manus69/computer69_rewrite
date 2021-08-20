#include "node.h"
#include "why_memory.h"
#include "frontend_declarations.h"

Node *node_new(void *data, NODE_TYPE type)
{
    Node *node;

    node = allocate(sizeof(Node));
    
    // if (type == NT_NUMBER)
    //     node->number = data;
    // else if (type == NT_MATRIX)
    //     node->matrix = data;
    // else if (type == NT_IDENTIFIER)
    //     node->identifier = data;
    
    node->identifier = data;
    node->type = type;

    return node;
}

Node *node_change_type(Node *node, NODE_TYPE type)
{
    node->type = type;

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
        return string_delete;
    else if (type == NT_OPERATOR)
        return operator_delete;
    
    return NULL;
}

//this is spooky
void node_delete(Node **node)
{
    void (*destructor)();

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

    number = number_new(string);
    
    return number ? node_new(number, NT_NUMBER) : NULL;   
}

Node *node_get_operator(String *string)
{
    Operator *operator;

    operator = operator_new(string);

    return operator ? node_new(operator, NT_OPERATOR) : NULL;
}

Node *node_get_identifier(String *string)
{
    int_unsigned length;
    String *substring;

    length = id_identifier(string_get_characters(string));
    if (!length)
        return NULL;
    
    substring = string_get_substring(string, 0, length);
    _string_shift(string, length);

    return node_new(substring, NT_IDENTIFIER);
}