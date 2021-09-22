#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "test/test.h"
#include "data_interface.h"
#include "why_error.h"

#include <stdio.h>
#include <time.h>
#include <limits.h>

void run_tests()
{
    test_all_statements(valid_basic_strings);
    test_all_sequences(valid_polynomial_sequences);
    test_all_sequences(valid_matrix_sequences);
    test_all_sequences(valid_sequences);
}

static void _at_exit()
{
    get_line(-1);
}

//dont forget the author file
//only letters in variable names?
//remove all asserts
//format all headers
//order all reserved symbols (reserved symols, function names, etc) and make a binary lookup
//be careful around things of the form f(x) = ... ; g(x) = f with no arg; this must be checked
//max size for matrices?
//limit for factorials and powers?
//-999999999999999999999999999999999999999999999999999999x = x^2?
//"-13.2593 + 6.48091X - 8.58475X^2 + 0.0000267855X^3 = 0?" makes valgrind shit the bed
//be careful around small coefficients
//find an input to break "insert root"
//put more complicated expressions into readme
//put a qubic equation into a readme
// f(x) = ? should be equivalent to "f" ?

int main()
{
    clock_t start;
    clock_t end;

    atexit(_at_exit);

    start = clock();
    data = data_init();
    
    // run_tests();
    test_statement("-13.2593 + 6.48091X - 8.58475X^2 + 0.0000267855X^3 = 0?");
    // test_sequence(valid_sequence);
    // main_loop();

    printf("\nMEMORY USAGE: %Ld\n", data_get_bytes(data));

    data_delete(&data);
    end = clock();

    printf("TIME ELAPSED: %f S\n", (end - start)/(double)CLOCKS_PER_SEC);

    return 0;
}