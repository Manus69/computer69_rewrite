#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "test.h"
#include "data_interface.h"
#include "why_error.h"

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>

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

void run_tests()
{
    test_all_sequences(valid_sequences);
    test_all_sequences(valid_matrix_sequences);
    test_all_sequences(valid_polynomial_sequences);
}

//user defined names must be case insensitive
//NT enums have the same prefix
//format all headers
//order all reserved symbols (reserved symols, function names, etc) and make a binary lookup
//be careful around things of the form f(x) = ... ; g(x) = f with no arg; this must be checked
//max size for matrices?
//upper limit for all numbers?
//some increment functions allocate, others do not
//some print functions print retarded stuff like -0 etc.
//unfuck enums, reserved strings and function names
//"f(x) = sin(sqrt(4)*pi)" does not resolve to value "f(x) = ln(e)", etc
//column times row?
//x^3 = 99999999999999999999999999999?
//"-13.2593 + 6.48091X - 8.58475X^2 + 0.0000267855X^3 = 0?" makes valgrind shit the bed
//be careful around small coefficients
//make a structure with strings, f_pointers, etc indexed by an enum
//f(x = 2 does something weird
//f(x) = ... ; f does not print the value
//numeric variable and function with the same name w = ... ; w(x) = ...
//r(x) =[[cos(x), -sin(x)];[sin(x), cos(x)]] , v = [[1];[0]] , r * v
//w(x) = (f+g)(x)
//x = 2; (1+1)x
//matrix times vector is broken

int main()
{
    clock_t start;
    clock_t end;

    start = clock();
    data = data_init();
    
    // test_statement("r(x) = [[cos(x), -sin(x)]; [sin(x), cos(x)]]");
    // test_statement("[[0] ; [1]]");
    // run_tests();
    // test_all_statements(invalid_strings);
    // test_all_statements(context_dependent_strings);
    // matrix_test();
    // math_test(); 
    // test_sequence(valid_sequence);
    main_loop();

    printf("\nMEMORY USAGE: %Ld\n", data_get_bytes(data));

    data_delete(&data);
    end = clock();

    printf("TIME ELAPSED: %f S\n", (end - start)/(double)CLOCKS_PER_SEC);

    return 0;
}