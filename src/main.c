#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "test.h"
#include "data_interface.h"

#include <stdio.h>
#include <time.h>
#include <math.h>

Data *data;

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

void matrix_test()
{
    MatrixRepr *A;
    MatrixRepr *B;
    MatrixRepr *result;
    int_signed size;
    NUMBER_TYPE type;

    size = 100;
    type = NT_REAL;
    A = generate_random_matrix(size, size, type);
    B = generate_random_matrix(size, size, type);
    result = matrix_repr_mult(A, B);

    print_matrix_repr(result);

    matrix_repr_delete(&A);
    matrix_repr_delete(&B);
    matrix_repr_delete(&result);
}

void polynomial_test()
{
    Polynomial *p;
    Computation *cmp;
    String *str;

    str = string_new_no_space("2 - 1");
    cmp = _parse(str, NULL);
    cmp = computation_resolve(cmp, "x", NULL);
    p = computation_to_polynomial(cmp);

    print_polynomial(p);

    polynomial_delete(&p);
    string_delete(&str);
}

void sqrt_test(real initial_value, real step, real terminal_value)
{
    real x, _x;

    while (initial_value < terminal_value)
    {
        printf("a = %Lf\n", initial_value);
        x = math_sqrt(initial_value);
        printf("my sqrt:    %.10Lf\n", x);

        _x = sqrt(initial_value);
        printf("stock sqrt: %.10Lf\n\n", _x);

        initial_value += step;
    }
}

void log_test(real initial_value, real step, real terminal_value)
{
    real x, _x;

    while (initial_value < terminal_value)
    {
        printf("a = %Lf\n", initial_value);
        x = math_ln(initial_value);
        printf("my log:    %.10Lf\n", x);

        _x = log(initial_value);
        printf("stock log: %.10Lf\n\n", _x);

        initial_value += step;
    }
}

void exp_test(real initial_value, real step, real terminal_value)
{
    real x, _x;

    while (initial_value < terminal_value)
    {
        x = math_exp(initial_value);
        _x = exp(initial_value);
        printf("a = %Lf\n", initial_value);
        printf("my exp:     %.10Lf\n", x);
        printf("stock exp:  %.10Lf\n\n", _x);

        initial_value += step;
    }
}

void math_test()
{
    real initial_value;
    real terminal_value;
    real step;

    initial_value = 0.1;
    terminal_value = __INT_MAX__;
    step = 10000;

    // sqrt_test(initial_value, step, terminal_value);
    log_test(initial_value, step, terminal_value);
}

void run_tests()
{
    // test_all_sequences(valid_sequences);
    // test_all_sequences(valid_matrix_sequences);
    // test_all_sequences(valid_polynomial_sequences);
}

//user defined names must be case insensitive
//NT enums have the same prefix
//format all headers
//order all reserved symbols (reserved symols, function names, etc) and make a binary lookup
//be careful around things of the form f(x) = ... ; g(x) = f with no arg; this must be checked
//max size for matrices?
//upper limit for all numbers?
//some increment functions allocate, others do not
//no () after matrix function assignment
//some print functions print retarded stuff like -0 etc.
//destructive polynomial operations?
//insert implicit stars before parsing?
//unfuck enums, reserved strings and function names
//"f(x) = sin(sqrt(4)*pi)" does not resolve to value "f(x) = ln(e)", etc
//make a structure with strings, f_pointers, etc indexed by an enum
//polynomials cant have symbols other than x 

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    // data_vector = get_data_vector();

    data = data_init();

    test_sequence(valid_sequence);
    run_tests();
    // matrix_test();
    // math_test();
    // polynomial_test();

    // printf("%.15Lf\n", math_exp(2));

    printf("\nMEMORY USAGE: %Ld\n", data_get_bytes(data));

    data_delete(&data);
    end = clock();

    printf("TIME ELAPSED: %f S\n", (end - start)/(double)CLOCKS_PER_SEC);

    return 0;
}