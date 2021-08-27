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

    cmp = parse(string, NULL);

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

void matrix_test()
{
    String *string;

    // string = string_new_no_space("[1, 1, pi]");
    string = string_new_no_space("[[x];[pi]]");
    MatrixRepr *matrix = matrix_repr_from_string(string, NULL);

    string_delete(&string);

    print_matrix_repr(matrix);

    matrix_repr_delete(&matrix);
}

void test()
{
    Vector *v;
    String *str;

    str = string_new("this is a test");
    v = string_split(str, ' ');
    string_delete(&str);

    print_vector(v, print_string, "-----");
    printf("\n");

    str = vector_at(v, 3);
    print_string_n(str);
    _string_shift(str, 2);
    print_string_n(str);

    print_vector(v, print_string, "-----");
    printf("\n");

    vector_delete(&v);
}

#include <limits.h>

void fib_test()
{
    int_signed n;
    int_unsigned _fib;

    n = 0;
    while (n < 150)
    {
        _fib = fib(n);
        if (_fib > ULLONG_MAX / 2)
            printf("n = %Ld -----------------", n);
        
        printf("n = %Ld, %Lu\n", n, _fib);
        
        n ++;
    }
}

//user defined names must be case insensitive
//NT enums have the same prefix
//format all headers
//add sqrt()
//order all reserved symbols (reserved symols, function names, etc) and make a binary lookup
//unfuck memory managment
//be careful around things of the form f(x) = ... ; g(x) = f with no arg; this must be checked

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    // test_sequence(valid_sequence_basic);
    test_sequence(valid_sequence);
    // test_all_sequences(valid_sequences);
    // test_all_sequences(valid_matrix_sequences);
    // test();

    // printf("%Lu\n", fib(89));

    end = clock();

    printf("\nTIME ELAPSED: %f S\n", (end - start)/(double)CLOCKS_PER_SEC);

    return 0;
}