#include "parser.h"
#include "why_error.h"
#include "terminals.h"
#include "computation.h"

static Computation* _get_term(String* string, const VariableTable* v_table);

Computation* get_stuff_in_parens(String* string, const VariableTable* v_table)
{
    int_signed right_index;
    String* substring;
    Computation* computation;

    right_index = find_matching_bracket_str(string, TERMINALS[O_PAREN], TERMINALS[C_PAREN]);
    if (right_index <= 1)
        return NULL;

    substring = string_substring(string, 1, right_index - 1);
    computation = parse(substring, v_table);

    _string_shift(string, right_index + 1);
    string_delete(&substring);

    return computation;
}

Computation* get_function(String* string, const VariableTable* v_table)
{
    int_unsigned length;
    Node* identifier_node;
    Computation* argument;
    Computation* identifier;

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

Computation* get_identifier(String* string)
{
    Node* node;

    node = node_get_identifier(string);

    return node ? computation_new(node, FALSE) : NULL;
}

static Computation* _process_u_minus(String* string, const VariableTable* v_table)
{
    Computation* minus;
    Computation* term;

    minus = get_operator(string);
    if (string_at(string, 0) == TERMINALS[MINUS])
        return error_set(WHY_ERROR_PARSE, string_get_characters(string));

    if (!(term = _get_term(string, v_table)))
        return error_set(WHY_ERROR_PARSE, string_get_characters(string));

    minus->lhs = term;

    return minus;
}

static Computation* _get_term(String* string, const VariableTable* v_table)
{
    Node*           node;
    Computation*    term;

    if ((term = get_function(string, v_table)))
        return term;
    
    if ((term = get_identifier(string)))
        return term;
    
    if ((node = node_get_number(string)))
        return computation_new(node, FALSE);
    
    if ((node = node_get_matrix(string, v_table)))
        return computation_new(node, FALSE);

    if ((term = get_stuff_in_parens(string, v_table)))
        return term;
    
    return NULL;
}

Computation* get_term(String* string, const VariableTable* v_table)
{    
    if (!string || string_length(string) == 0)
        return NULL;
    
    string_skip_spaces(string);

    if (string_at(string, 0) == TERMINALS[MINUS])
        return _process_u_minus(string, v_table);
    
    return _get_term(string, v_table);
}

Computation* get_operator(String* string)
{
    Node* op_node;

    string_skip_spaces(string);

    op_node = node_get_operator(string);

    return op_node ? computation_new(op_node, FALSE) : NULL;
}