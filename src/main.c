#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "test.h"

#include <stdio.h>

void parse_test()
{
    Computation *cmp;
    String *string;

    // string = string_new("3!^2+1");
    string = string_new("i");

    cmp = parse(string);

    print_computation(cmp);

    string_delete(&string);
    computation_delete(&cmp);
}

void variable_test()
{
    Variable *v;
    VariableTable *v_table;
    String *string;

    string = string_new("v(x) = sin(x)");
    v_table = v_table_new(NULL);
    v = variable_create_from_string(string, v_table);

    print_variable(v);

    v_table = v_table_new(v);
    // v_table_insert(v_table, v);

    // variable_delete(&v);
    v_table_delete(&v_table);
    string_delete(&string);
}

void test()
{
    Variable *variable;
    VariableTable *v_table;
    String *string;
    char *input;

    string = string_new_no_space("x=1");
}

//user defined names must be case insensitive
//NT enums have the same prefix
//double exclam in a row?
//variables with no parameters

int main()
{
    // parse_test();
    test_syntax(valid_strings);
    // variable_test();

    return 0;
}