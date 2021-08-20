#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "operator.h"
#include "terminals.h"

#include <assert.h>

static String *_remove_spaces(String *string)
{
    String *new_string;

    new_string = string_remove_whitespace(string);
    string_delete(&string);

    return new_string;
}

Computation *get_stuff_in_parens(String *string)
{
    int_signed right_index;
    String *substring;
    Computation *computation;

    right_index = find_matching_bracket_str(string);
    if (right_index <= 1)
        return NULL;

    substring = string_get_substring(string, 1, right_index - 1);
    computation = parse(substring);

    _string_shift(string, right_index + 1);
    string_delete(&substring);

    return computation;
}

Computation *get_function(String *string)
{
    int_unsigned length;
    Node *identifier_node;
    Computation *argument;
    Computation *identifier;

    length = id_function_name_str(string);
    if (!length)
        return NULL;

    identifier_node = node_get_identifier(string);
    argument = get_stuff_in_parens(string);
    if (!argument)
        return NULL;

    node_change_type(identifier_node, NT_FUNCTION);
    identifier = computation_new(identifier_node);
    identifier->lhs = argument;

    return identifier;
}

Computation *get_identifier(String *string)
{
    Node *node;

    node = node_get_identifier(string);

    return node ? computation_new(node) : NULL;
}

Computation *get_term(String *string)
{
    Node *node;
    Computation *term;

    if (!string || string_get_length(string) == 0)
        return NULL;
    
    node = node_get_number(string);
    if (node)
        return computation_new(node);
    
    term = get_stuff_in_parens(string);
    if (term)
        return term;
    
    term = get_function(string);
    if (term)
        return term;
    
    term = get_identifier(string);
    if (term)
        return term;
    
    return NULL;
}

Computation *get_operator(String *string)
{
    Node *op_node;

    op_node = node_get_operator(string);

    return computation_new(op_node);
}

static Computation *process_u_minus(String *string)
{
    Computation *root;
    Computation *minus;
    Computation *term;

    minus = get_operator(string);
    term = get_term(string);
    if (!term)
    {
        computation_delete(&minus);
        return NULL;
    }

    minus->lhs = term;

    root = get_operator(string);
    if (!root)
        return minus;
    
    root->lhs = minus;

    return root;
}

static Computation *get_partial_tree(String *string)
{
    Computation *root;
    Computation *lhs;
    Computation *new_root;

    if (string_at(string, 0) == TERMINALS[MINUS])
        return process_u_minus(string);
    
    lhs = get_term(string);
    if (!lhs)
        return NULL;
    
    root = get_operator(string);
    if (!root)
        return lhs;
    
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

static Computation *_parse(String *string)
{
    Computation *root;
    Computation *last_op;
    Computation *next_op;
    Computation *term;

    root = get_partial_tree(string);
    if (root->node->type != NT_OPERATOR)
        return root;

    if (!operator_is_binary(root->node->operator))
            return root;

    last_op = root;
    while (TRUE)
    {
        if (string_get_length(string) == 0)
            return root;
        
        term = get_term(string);
        if (!term)
            assert(0);

        last_op->rhs = term;
        next_op = get_operator(string);

        if (!operator_is_binary(next_op->node->operator))
        {
            computation_insert_root(last_op->rhs, next_op);
            last_op = next_op;
        }
        else if (operator_compare_precedence(last_op->node->operator, next_op->node->operator) > 0)
        {
            computation_swap_root(last_op, next_op);
            last_op = next_op;
        }
        else
        {
            root = computation_insert_root(root, next_op);
            last_op = root;
        }
    }
}

Computation *parse(String *string)
{
    if (!string || !string_get_length(string))
        return NULL;

    string = _remove_spaces(string);

    return _parse(string);
}