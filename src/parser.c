#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "operator.h"
#include "terminals.h"
#include "why_error.h"

#include <assert.h>

Computation *get_term(String *string, const VariableTable *v_table);
Computation *get_operator(String *string);

Computation *get_stuff_in_parens(String *string, const VariableTable *v_table)
{
    int_signed right_index;
    String *substring;
    Computation *computation;

    right_index = find_matching_bracket_str(string, TERMINALS[O_PAREN], TERMINALS[C_PAREN]);
    if (right_index <= 1)
        return NULL;

    substring = string_substring(string, 1, right_index - 1);
    computation = _parse(substring, v_table);

    _string_shift(string, right_index + 1);
    string_delete(&substring);

    return computation;
}

Computation *get_function(String *string, const VariableTable *v_table)
{
    int_unsigned length;
    Node *identifier_node;
    Computation *argument;
    Computation *identifier;

    length = id_function_name_str(string);
    if (!length)
        return NULL;

    identifier_node = node_get_identifier(string);
    argument = get_stuff_in_parens(string, v_table);
    if (!argument)
        return NULL;

    node_change_type(identifier_node, NT_FUNCTION);
    node_convert_to_bft(identifier_node);

    identifier = computation_new(identifier_node, FALSE);
    identifier->lhs = argument;

    return identifier;
}

Computation *get_identifier(String *string)
{
    Node *node;

    node = node_get_identifier(string);

    return node ? computation_new(node, FALSE) : NULL;
}

static Computation *_process_u_minus(String *string, const VariableTable *v_table)
{
    Computation *minus;
    Computation *term;

    minus = get_operator(string);
    if (!(term = get_term(string, v_table)))
        return error_set(WHY_ERROR_PARSE, string_get_characters(string));

    minus->lhs = term;

    return minus;
}

Computation *get_term(String *string, const VariableTable *v_table)
{
    Node *node;
    Computation *term;

    if (!string || string_length(string) == 0)
        return NULL;
    
    string_skip_spaces(string);

    if ((node = node_get_number(string)))
        return computation_new(node, FALSE);
    
    if ((node = node_get_matrix(string, v_table)))
        return computation_new(node, FALSE);

    if ((term = get_stuff_in_parens(string, v_table)))
        return term;
    
    if ((term = get_function(string, v_table)))
        return term;
    
    if ((term = get_identifier(string)))
        return term;

    if (string_at(string, 0) == TERMINALS[MINUS])
        return _process_u_minus(string, v_table);
    
    return NULL;
}

Computation *get_operator(String *string)
{
    Node *op_node;

    string_skip_spaces(string);

    op_node = node_get_operator(string);

    return op_node ? computation_new(op_node, FALSE) : NULL;
}

static Computation *get_partial_tree(String *string, const VariableTable *v_table)
{
    Computation *root;
    Computation *lhs;
    Computation *new_root;

    if (!string)
        return NULL;
    
    if (!(lhs = get_term(string, v_table)))
        return error_set(WHY_ERROR_PARSE, string_get_characters(string));
    
    if (!(root = get_operator(string)))
    {
        if (id_identifier_str(string) && lhs->node->type == NT_NUMBER)
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

static Computation *_insert_below(Computation *last_op, Computation *next_op, Computation *term)
{
    last_op->rhs = next_op;
    next_op->lhs = term;
    last_op = next_op;

    return last_op;
}

static Computation *_insert_above(Computation **root, Computation *last_op, Computation *next_op, Computation *term)
{
    Computation *parent;

    parent = computation_find_parentR(*root, last_op);
    last_op->rhs = term;
    next_op->lhs = last_op;

    if (parent)
        parent->rhs = next_op;
    else
        *root = next_op;

    return next_op;
}

static void _check_precedence_and_insert(Computation **last_op, Computation **next_op, Computation **term, Computation **root)
{
    int_signed comparison;

    comparison = operator_compare_precedence((*last_op)->node->operator, (*next_op)->node->operator);

    if (comparison > 0)
        *last_op = _insert_below(*last_op, *next_op, *term);
    else if (comparison < 0 && operator_compare_precedence((*root)->node->operator, (*next_op)->node->operator) <= 0)
    {
        (*last_op)->rhs = *term;
        *root = computation_insert_root(*root, *next_op);
        *last_op = *root;
    }
    else
    {
        *last_op = _insert_above(root, *last_op, *next_op, *term);
    }
}

Computation *_parse(String *string, const VariableTable *v_table)
{
    Computation *root;
    Computation *last_op;
    Computation *next_op;
    Computation *term;

    if (!(root = get_partial_tree(string, v_table)))
        return NULL;
    
    if (root->node->type != NT_OPERATOR)
        return root;

    if (!operator_is_binary(root->node->operator))
        return root;

    last_op = root;
    while (string_length(string))
    {
        if(!(term = get_term(string, v_table)))
            return error_set(WHY_ERROR_SYNTAX, string_get_characters(string));

        if (!(next_op = get_operator(string)))
        {         
            if (!string_length(string))
            {
                last_op->rhs = term;
                return root;
            }

            if (id_identifier_str(string) && term->node->type == NT_NUMBER)
            {
                next_op =
                computation_new(node_new(operator_new_from_type(OT_STAR), NT_OPERATOR, FALSE), FALSE);
            }
            else
                return error_set(WHY_ERROR_SYNTAX, string_get_characters(string));
        }
        
        _check_precedence_and_insert(&last_op, &next_op, &term, &root);
    }

    return root;
}
