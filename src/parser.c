#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"
#include "operator.h"
#include "terminals.h"

#include <assert.h>

// static Computation *_parse(String *string);

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

    node_convert_to_bft(identifier_node); //

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

Computation *get_term(String *string, const VariableTable *v_table)
{
    Node *node;
    Computation *term;

    if (!string || string_length(string) == 0)
        return NULL;
    
    node = node_get_number(string);
    if (node)
        return computation_new(node, FALSE);
    
    node = node_get_matrix(string, v_table);
    if (node)
        return computation_new(node, FALSE);

    term = get_stuff_in_parens(string, v_table);
    if (term)
        return term;
    
    term = get_function(string, v_table);
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

    return op_node ? computation_new(op_node, FALSE) : NULL;
}

static Computation *process_u_minus(String *string, const VariableTable *v_table)
{
    Computation *root;
    Computation *minus;
    Computation *term;

    minus = get_operator(string);
    term = get_term(string, v_table);
    if (!term)
    {
        // computation_delete(&minus);
        return NULL;
    }

    minus->lhs = term;

    root = get_operator(string);
    if (!root)
        return minus;
    
    root->lhs = minus;

    return root;
}

static Computation *get_partial_tree(String *string, const VariableTable *v_table)
{
    Computation *root;
    Computation *lhs;
    Computation *new_root;

    if (!string)
        return NULL;

    if (string_at(string, 0) == TERMINALS[MINUS])
        return process_u_minus(string, v_table);
    
    lhs = get_term(string, v_table);
    if (!lhs)
        return NULL;
    
    root = get_operator(string);
    if (!root)
    {
        if (!id_identifier_str(string) || !lhs->node->type == NT_NUMBER)
            return lhs;

        root = computation_new(node_new(operator_new_from_type(OT_STAR), NT_OPERATOR, FALSE), FALSE);
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

static boolean _check_order(const Computation *last_op, const Computation *next_op)
{
    if (!operator_is_binary(next_op->node->operator) ||
    (operator_compare_precedence(last_op->node->operator, next_op->node->operator) > 0))
        return TRUE;
    
    return FALSE;
}

static Computation *_insert_in_order(Computation *last_op, Computation *next_op, Computation *term)
{
    last_op->rhs = next_op;
    next_op->lhs = term;
    last_op = next_op;

    return last_op;
}

Computation *_parse(String *string, const VariableTable *v_table)
{
    Computation *root;
    Computation *last_op;
    Computation *next_op;
    Computation *term;

    root = get_partial_tree(string, v_table);
    if (!root || root->node->type != NT_OPERATOR)
        return root;

    if (!operator_is_binary(root->node->operator))
        return root;

    last_op = root;
    while (TRUE)
    {
        if (string_length(string) == 0)
            return root;

        term = get_term(string, v_table);

        if (!(next_op = get_operator(string)))
        {
            if (!id_identifier_str(string) || !term->node->type == NT_NUMBER)
            {
                last_op->rhs = term;
                return root;
            }
            
            next_op =
            computation_new(node_new(operator_new_from_type(OT_STAR), NT_OPERATOR, FALSE), FALSE);
        }
        
        if (_check_order(last_op, next_op))
        {
            last_op = _insert_in_order(last_op, next_op, term);
        }
        else
        {
            last_op->rhs = term;
            root = computation_insert_root(root, next_op);
            last_op = root;
        }
    }
}

Computation *parse(String *string, const VariableTable *v_table)
{
    if (!string || !string_length(string))
        return NULL;

    string = string_remove_spaces(string);

    return _parse(string, v_table);
}