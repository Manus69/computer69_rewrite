#include "frontend_declarations.h"
#include "node.h"

static int_signed _determine_bft(const String *string)
{
    int_signed type;

    type = 0;
    while (FUNCTION_STRINGS[type])
    {
        if (string_is_identical_to(string, FUNCTION_STRINGS[type]))
            return type;
        
        type ++;
    }
    
    return NOT_FOUND;
}

Node *node_convert_to_bft(Node *node)
{
    int_signed type;

    if (node->type != NT_FUNCTION)
        return NULL;

    type = _determine_bft(node->identifier);
    if (type == NOT_FOUND)
        return NULL;
    
    string_delete(&node->identifier);
    node->type = NT_BUILTIN_FUNCTION;
    node->bf_type = type;

    return node;
}