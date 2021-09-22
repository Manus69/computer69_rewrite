#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "operator.h"
#include "terminals.h"
#include "why_error.h"
#include "parser.h"

#include "why_string.h" //
// #include <assert.h>

static boolean _check_if_implicit_star(String* string, Computation* lhs)
{
    if (id_identifier_str(string))
    {
        if (lhs->node->type == NT_NUMBER)
            return TRUE;
        if (lhs->node->type == NT_OPERATOR && lhs->node->operator->type == OT_MINUS)
        {
            if (lhs->lhs && lhs->lhs->node->type == NT_NUMBER)
                return TRUE;
        }
    }

    return FALSE;
}

static Computation* get_partial_tree(String* string, const VariableTable* v_table)
{
    Computation* root;
    Computation* lhs;
    Computation* new_root;

    if (!string)
        return NULL;
    
    if (!(lhs = get_term(string, v_table)))
        return error_set(WHY_ERROR_PARSE, string_get_characters(string));
    
    if (!(root = get_operator(string)))
    {
        if (_check_if_implicit_star(string, lhs))
            root = computation_new(node_new(operator_new_from_type(OT_STAR), NT_OPERATOR, FALSE), FALSE);
        else if (!string_length(string))
            return lhs;
        else
            return error_set(WHY_ERROR_PARSE, string_get_characters(string));
    }
    
    root->lhs = lhs;
    while (!operator_is_binary(root->node->operator))
    {
        new_root = get_operator(string);
        if (!new_root)
            break ;
        
        root = computation_insert_root(root, new_root);
    }

    return root;    
}

static Computation* _insert_below(Computation* last_op, Computation* next_op, Computation* term)
{
    last_op->rhs = next_op;
    next_op->lhs = term;
    last_op = next_op;

    return last_op;
}

static Computation* _insert_above(Computation** root, Computation* last_op, Computation* next_op, Computation* term)
{
    Computation* parent;

    parent = computation_find_parentR(*root, last_op);
    last_op->rhs = term;
    next_op->lhs = last_op;

    if (parent)
        parent->rhs = next_op;
    else
        *root = next_op;

    return next_op;
}

//this is bad
static void _check_precedence_and_insert(Computation** last_op, 
                                        Computation** next_op, Computation** term, Computation** root)
{
    int_signed comparison;

    comparison = operator_compare_precedence((*last_op)->node->operator, (*next_op)->node->operator);

    if (comparison > 0)
        *last_op = _insert_below(*last_op,* next_op,* term);
    else if (comparison < 0 && operator_compare_precedence((*root)->node->operator, (*next_op)->node->operator) <= 0)
    {
        (*last_op)->rhs =* term;
        *root = computation_insert_root(*root,* next_op);
        *last_op =* root;
    }
    else
        *last_op = _insert_above(root,* last_op,* next_op,* term);
}

Computation* parse(String* string, const VariableTable* v_table)
{
    Computation* root;
    Computation* last_op;
    Computation* next_op;
    Computation* term;

    if (!(root = get_partial_tree(string, v_table)))
        return NULL;
    
    if (root->node->type != NT_OPERATOR)
        return root;

    if (!operator_is_binary(root->node->operator))
        return root;

    last_op = root;
    while (string_length(string))
    {
        if(!(term = get_term(string, v_table)) && operator_is_binary(last_op->node->operator))
            return error_set(WHY_ERROR_SYNTAX, string_get_characters(string));

        if (!(next_op = get_operator(string)))
        {         
            if (!string_length(string))
            {
                last_op->rhs = term;
                return root;
            }

            if (id_identifier_str(string) && term->node->type == NT_NUMBER)
                next_op =
                computation_new(node_new(operator_new_from_type(OT_STAR), NT_OPERATOR, FALSE), FALSE);
            else
                return error_set(WHY_ERROR_SYNTAX, string_get_characters(string));
        }
        
        _check_precedence_and_insert(&last_op, &next_op, &term, &root);
    }

    return root;
}
