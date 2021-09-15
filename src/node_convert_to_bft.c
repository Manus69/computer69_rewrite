#include "frontend_declarations.h"
#include "node.h"

static const void *functions[] = {number_sin, number_cos, number_tan, 
                                number_sqrt, number_log, number_ln, number_exp, number_abs, 0};

void *get_bft_pointer(BULITIN_FUNCTION_TYPE type)
{
    return (void *)functions[type];
}

static int_signed _determine_bft(const char *string)
{
    int_signed type;

    type = 0;
    while (FUNCTION_STRINGS[type])
    {
        if (cstr_compare(string, FUNCTION_STRINGS[type]) == 0)
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
    
    node->type = NT_BUILTIN_FUNCTION;
    node->bf_type = type;

    return node;
}