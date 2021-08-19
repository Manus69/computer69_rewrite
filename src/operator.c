#include "operator.h"
#include "why_string_interface.h"
#include "why_memory.h"
#include "terminals.h"
#include "why_cstring.h"

#include <assert.h>

static byte _get_precedence(OPERATOR_TYPE type)
{
    if (type <= OT_MINUS)
        return 0;
    else if (type <= OT_MOD)
        return 1;
    else if (type == OT_EXPONENT)
        return 2;
    else if (type == OT_FACTORIAL)
        return 3;
    
    assert(0);
}

static Operator *_new(OPERATOR_TYPE type)
{
    Operator *op;

    op = allocate(sizeof(Operator));
    op->type = type;
    op->precedence = _get_precedence(type);

    return op;
}

Operator *operator_new(String *string)
{
    char *characters;
    int_signed index;

    if (string_get_length(string) == 0)
        return NULL;
    
    characters = string_get_characters(string);
    index = cstr_index_of(TERMINALS, *characters);

    if (index == NOT_FOUND)
        return NULL;
    if (index > EXCLAM)
        return NULL;
    
    return _new(index);
}

void operator_delete(Operator **operator)
{
    if (!operator || !*operator)
        return ;
    
    free(*operator);
    *operator = NULL;
}