#include "frontend_declarations.h"
#include "terminals.h"

#include "print.h" //
#include <assert.h>

static VariableTable *_insert_into_table(Variable *variable, VariableTable *v_table)
{
    Variable *v;

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

static VariableTable *_process_assignment(String *line, VariableTable *v_table)
{
    Variable *_variable;

    _variable = variable_create_from_string(line, v_table);

    //
    print_variable(_variable);
    printf("\n");
    
    if (variable_get_name(_variable))
        v_table = _insert_into_table(_variable, v_table);

    return v_table;
}

static void _process_polynomial(Computation *lhs, Computation *rhs)
{    
    Polynomial *p;
    Polynomial *_lhs;
    Polynomial *_rhs;
    Vector *roots;

    _lhs = computation_to_polynomial(lhs);
    _rhs = computation_to_polynomial(rhs);
    p = polynomial_subtract(_lhs, _rhs);

    print_polynomial(p);

    roots = polynomial_roots(p);
    printf("\n");
    print_roots(roots);
    printf("\n");

    polynomial_delete(&p);
    polynomial_delete(&_lhs);
    polynomial_delete(&_rhs);
    vector_delete(&roots);
}

static void _process_find_roots(String *line, VariableTable *v_table)
{
    Vector *strings;
    Computation *lhs;
    Computation *rhs;

    strings = string_split(line, TERMINALS[EQUALS]);
    if (vector_size(strings) != 2)
        assert(0);
    
    lhs = _parse(vector_at(strings, 0), v_table);
    rhs = _parse(vector_at(strings, 1), v_table);
    lhs = computation_resolve(lhs, "x", v_table);
    rhs = computation_resolve(rhs, "x", v_table);

    _process_polynomial(lhs, rhs);
    vector_delete(&strings);
}

VariableTable *process_input_line(String *line, VariableTable *v_table)
{
    String *substring;
    
    if (id_assignment(line))
        return _process_assignment(line, v_table);
    else if (id_evaluation(line))
        return _process_assignment(line, v_table);
    else if (id_find_roots(line))
    {
        substring = string_substring(line, 0, string_length(line) - 1);
        _process_find_roots(substring, v_table);
        string_delete(&substring);
    }
    else if (id_statement(line))
        return _process_assignment(line, v_table);

    return v_table;
}