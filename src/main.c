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
//be careful around things of the form f(x) = ... ; g(x) = f with no arg; this must be checked
//max size for matrices?
//limit for factorials and powers?
//find an input to break "insert root"
//put more complicated expressions into readme
// f(x) = ? should be equivalent to "f" ?
//test functions with veird values: log(-1), etc

int main()
{
    clock_t start;
    clock_t end;

    atexit(_at_exit);

    start = clock();
    data = data_init();
    
    // run_tests();
    // test_statement("-999999999999999999999999999999999999999999999999999999x = x^2?");
    // test_sequence(valid_sequence);
    main_loop();

    printf("\nMEMORY USAGE: %Ld\n", data_get_bytes(data));

    data_delete(&data);
    end = clock();

    printf("TIME ELAPSED: %f S\n", (end - start)/(double)CLOCKS_PER_SEC);

    return 0;
}