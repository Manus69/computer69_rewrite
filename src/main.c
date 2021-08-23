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

    string = string_new_no_space("sin(x) = x");
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
    String *string1;

    // string = string_new_no_space("x = pi");
    // string1 = string_new_no_space("x2 = x");

    string = string_new_no_space("var = pi");
    string1 = string_new_no_space("v = var");

    v_table = NULL;
    
    if (id_assignment(string))
    {
        variable = variable_create_from_string(string, v_table);
        print_variable(variable);
        v_table = v_table_insert(v_table, variable);

        variable = variable_create_from_string(string1, v_table);
        print_variable(variable);
        v_table_insert(v_table, variable);
    }
    else if (id_evaluation(string))
    {
        ;
    }

    v_table_delete(&v_table);
    string_delete(&string);
    string_delete(&string1);
}

//user defined names must be case insensitive
//NT enums have the same prefix
//format all headers

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    // String *lhs, *rhs;
    // lhs = string_new("a1");
    // rhs = string_new("a");

    // printf("%lld\n", string_compare(lhs, rhs));

    // test_syntax(valid_basic_strings);
    // test_computation(valid_basic_strings);
    // test_computation(valid_id_strings);
    // test_assignment(valid_ass_strings);
    // test_sequence(valid_sequence);
    test_all_sequences(valid_sequences);
    // test();


    end = clock();

    printf("\nTIME ELAPSED: %f S\n", (end - start)/(double)CLOCKS_PER_SEC);

    return 0;
}