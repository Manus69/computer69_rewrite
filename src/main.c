#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "test/test.h"
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
    test_all_statements(valid_basic_strings);
    test_all_sequences(valid_polynomial_sequences);
    test_all_sequences(valid_matrix_sequences);
    test_all_sequences(valid_sequences);
}

//dont forget the author file
//only letters in variable names?
//remove all asserts
//format all headers
//order all reserved symbols (reserved symols, function names, etc) and make a binary lookup
//be careful around things of the form f(x) = ... ; g(x) = f with no arg; this must be checked
//max size for matrices?
//unfuck enums, reserved strings and function names
//-999999999999999999999999999999999999999999999999999999x = x^2?
//"-13.2593 + 6.48091X - 8.58475X^2 + 0.0000267855X^3 = 0?" makes valgrind shit the bed
//be careful around small coefficients
//make a structure with strings, f_pointers, etc indexed by an enum
//find an input to break "insert root"
// f(x) = ? should be equivalent to "f" ?
//use computation_to_polynomial to avoid lazy evaluation?
//put more complicated expressions into readme

int main()
{
    clock_t start;
    clock_t end;

    start = clock();
    data = data_init();
    
    // run_tests();
    // test_statement("E(x) = 0");
    // test_all_statements(invalid_strings);
    // test_all_statements(context_dependent_strings);
    // matrix_test();
    // math_test(); 
    test_sequence(valid_sequence);
    // main_loop();

    printf("\nMEMORY USAGE: %Ld\n", data_get_bytes(data));

    data_delete(&data);
    end = clock();

    printf("TIME ELAPSED: %f S\n", (end - start)/(double)CLOCKS_PER_SEC);

    return 0;
}