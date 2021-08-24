#include "operator.h"
#include "why_string_interface.h"
#include "why_memory.h"
#include "terminals.h"
#include "why_cstring.h"

#include <assert.h>

boolean operator_is_binary(Operator *operator)
{
    if (operator->type == OT_EXCLAM)
        return FALSE;
    
    return TRUE;
}

int_signed operator_compare_precedence(Operator *lhs, Operator *rhs)
{
    if (lhs->precedence > rhs->precedence)
        return -1;
    return rhs->precedence > lhs->precedence;
}

static byte _get_precedence(OPERATOR_TYPE type)
{
    if (type <= OT_MINUS)
        return 0;
    else if (type <= OT_MOD)
        return 1;
    else if (type == OT_CARET)
        return 2;
    else if (type == OT_EXCLAM)
        return 3;
    
    assert(0);
}

Operator *operator_new_from_type(OPERATOR_TYPE type)
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

    if (string_length(string) == 0)
        return NULL;
    
    characters = string_get_characters(string);
    index = cstr_index_of(TERMINALS, *characters);

    if (index == NOT_FOUND)
        return NULL;
    if (index > EXCLAM)
        return NULL;
    
    _string_shift(string, 1);

    return operator_new_from_type(index);
}

OPERATOR_TYPE operator_get_type(const Operator *operator)
{
    return operator->type;
}

void operator_delete(Operator **operator)
{
    if (!operator || !*operator)
        return ;
    
    free(*operator);
    *operator = NULL;
}

Operator *operator_copy(const Operator *operator)
{
    Operator *copy;

    copy = allocate(sizeof(Operator));
    copy = memory_copy(copy, operator, sizeof(Operator));

    return copy;
}