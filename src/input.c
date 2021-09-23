#include "frontend_declarations.h"
#include "terminals.h"
#include "computation.h"
#include "node.h"
#include "why_error.h"

#define DBG 1
#if DBG
    #include "print.h" //
    #include <assert.h>
#endif

static VariableTable* _insert_into_table(Variable* variable, VariableTable* v_table)
{
    Variable* v;

    if (!v_table)
        v_table = v_table_new(variable);
    else if ((v = v_table_search(v_table, variable_get_name(variable))))
    {
        v = variable_assign(v, variable_get_value(variable), TRUE);
        variable_delete(&variable);
    }
    else if (!v_table_insert_report(v_table, variable))
        variable_delete(&variable);

    return v_table;
}

static VariableTable* _process_assignment(String* line, VariableTable* v_table)
{
    Variable* _variable;

    _variable = variable_create_from_string(line, v_table);
    if (!_variable)
        return v_table;

    print_variableNI(_variable);
    
    if (variable_get_name(_variable))
        v_table = _insert_into_table(_variable, v_table);

    return v_table;
}

static VariableTable* _process_eval(String* line, VariableTable* v_table)
{
    Vector* substrings;
    String* lhs;
    VariableTable* result;

    substrings = string_split_and_trim(line, TERMINALS[EQUALS]);
    lhs = vector_at(substrings, 0);

    result = _process_assignment(lhs, v_table);
    vector_delete(&substrings);

    return result;
}

static void _process_polynomial(Computation* lhs, Computation* rhs)
{    
    Polynomial* p;
    Polynomial* _lhs;
    Polynomial* _rhs;
    Vector*     roots;

    _lhs = computation_to_polynomial(lhs);
    _rhs = computation_to_polynomial(rhs);

    p = polynomial_subtract(_lhs, _rhs);
    print_polynomial_with_rhs(p);
    roots = polynomial_roots(p);

    if (polynomial_is_zero(p))
        print_root_messageAR();
    else if (!roots && !WHY_ERROR)
        print_root_messageNR();
    else
    {
        print_roots(roots);
        printf("\n");
    }

    polynomial_delete(&p);
    polynomial_delete(&_lhs);
    polynomial_delete(&_rhs);
    vector_delete(&roots);
}

static char* _get_first_identifier(const Computation* _computation)
{
    char* _lhs;

    if (!_computation)
        return NULL;
    
    if (_computation->node->type == NT_IDENTIFIER)
    {
        if (!check_reserved_symbols(_computation->node->identifier))
            return _computation->node->identifier;
    }

    _lhs = _get_first_identifier(_computation->lhs);
    if (_lhs)
        return _lhs;
    
    return _get_first_identifier(_computation->rhs);
}

static void _handle_errors(Vector* strings)
{
    vector_delete(&strings);
}

static void _process_find_roots(String* line, VariableTable* v_table)
{
    Vector*         strings;
    Computation*    lhs;
    Computation*    rhs;
    char*           id;

    strings = string_split_and_trim(line, TERMINALS[EQUALS]);
    if (vector_size(strings) != 2)
    {
        vector_delete(&strings);
        error_set(WHY_ERROR_SYNTAX, string_get_characters(line));

        return ;
    }
    
    lhs = parse(vector_at(strings, 0), v_table);
    rhs = parse(vector_at(strings, 1), v_table);

    if (WHY_ERROR)
        return _handle_errors(strings);

    if (!(id = _get_first_identifier(lhs)))
        id = _get_first_identifier(rhs);
    
    lhs = computation_resolve(lhs, id, v_table);
    rhs = computation_resolve(rhs, id, v_table);

    _process_polynomial(lhs, rhs);
    vector_delete(&strings);
}

VariableTable* process_input_line(String* line, VariableTable* v_table)
{
    String*         substring;
    VariableTable*  result;
    Variable*       _variable;
    
    result = v_table;
    if ((_variable = v_table_search(v_table, string_get_characters(line))))
    {
        print_variableN(_variable);
        return v_table;
    }

    if (id_assignment(line))
        result = _process_assignment(line, v_table);
    else if (id_evaluation(line))
        result = _process_eval(line, v_table);
    else if (id_find_roots(line))
    {
        substring = string_substring(line, 0, string_length(line) - 1);
        _process_find_roots(substring, v_table);
        string_delete(&substring);
    }
    else if (id_statement(line))
        result = _process_assignment(line, v_table);

    if (WHY_ERROR)
        error_display();

    return result;
}