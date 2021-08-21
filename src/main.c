#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "test.h"

#include <stdio.h>
#include <time.h>

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

    string = string_new_no_space("x = 1+1-(1+1)");
    v_table = NULL;
    
    if (id_assignment(string))
    {
        variable = variable_create_from_string(string, v_table);
        print_variable(variable);

        v_table = v_table_insert(v_table, variable);
    }
    else if (id_evaluation(string))
    {
        ;
    }

    v_table_delete(&v_table);
    string_delete(&string);    
}

void number_test()
{
    Number *n0, *n1, *result;
    String *str0, *str1;

    str0 = string_new("-1");
    str1 = string_new("i");

    n0 = number_new(str0);
    n1 = number_new(str1);
    result = number_add(n0, n1);

    print_number(result);

    number_delete(&n0);
    number_delete(&n1);
    number_delete(&result);
    string_delete(&str0);
    string_delete(&str1);
}

//user defined names must be case insensitive
//NT enums have the same prefix
//double exclam in a row?
//format all headers

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    // number_test();
    // parse_test();
    // test_syntax(valid_strings);
    // variable_test();
    test();

    end = clock();

    printf("\nTIME ELAPSED: %f S\n", (end - start)/(double)CLOCKS_PER_SEC);

    return 0;
}