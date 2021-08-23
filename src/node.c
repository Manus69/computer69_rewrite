#include "node.h"
#include "why_memory.h"
#include "frontend_declarations.h"

Node *node_new(void *data, NODE_TYPE type)
{
    Node *node;

    node = allocate(sizeof(Node));
    
    node->identifier = data;
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
    
    string_delete(&node->identifier);
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
        return string_delete;
    else if (type == NT_OPERATOR)
        return operator_delete;
    else if (type == NT_FUNCTION)
        return string_delete;
    
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

    number = number_from_string(string);
    
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
    
    substring = string_substring(string, 0, length);
    _string_shift(string, length);

    return node_new(substring, NT_IDENTIFIER);
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
    else if (node->type == NT_IDENTIFIER)
        new_node->identifier = string_copy_semideep(node->identifier);
    else if (node->type == NT_MATRIX)
        new_node->matrix = matrix_repr_copy(node->matrix);

    return new_node;
}