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

//fix op priorities
//dont forget the author file
//only letters in variable names?
//user defined names must be case insensitive
//remove all asserts
//format all headers
//order all reserved symbols (reserved symols, function names, etc) and make a binary lookup
//be careful around things of the form f(x) = ... ; g(x) = f with no arg; this must be checked
//max size for matrices?
//some print functions print retarded stuff like -0 etc.
//unfuck enums, reserved strings and function names
//-999999999999999999999999999999999999999999999999999999x = x^2?
//"f(x) = sin(sqrt(4)*pi)" does not resolve to value "f(x) = ln(e)", etc
//"-13.2593 + 6.48091X - 8.58475X^2 + 0.0000267855X^3 = 0?" makes valgrind shit the bed
//be careful around small coefficients
//make a structure with strings, f_pointers, etc indexed by an enum
//2 / (2 %2 )
//x^3 - 3x^2 - x + 1 = 0? LOOPS OUT
// print polynomial has "x" hardcoded

int main()
{
    clock_t start;
    clock_t end;

    start = clock();
    data = data_init();
    
    // run_tests();
    // test_statement("2 + 3 ^ 4 * 2");
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