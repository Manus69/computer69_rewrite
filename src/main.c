#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "test.h"
#include "data_interface.h"

#include <stdio.h>
#include <time.h>

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

#include <math.h>
void math_test()
{
    real x;
    real _x;
    real angle;

    angle = 0;
    while (angle <= 100 * PI)
    {
        x = math_sin(angle);
        _x = sin(angle);

        printf("angle = %Lf\n", angle);
        printf("my sin: %Lf\nstock sin: %Lf\n\n", x, _x);

        x = math_cos(angle);
        _x = cos(angle);

        printf("angle = %Lf\n", angle);
        printf("my cos: %Lf\nstock cos: %Lf\n\n", x, _x);

        angle += PI / 4;
    }

}

//user defined names must be case insensitive
//NT enums have the same prefix
//format all headers
//add sqrt()
//order all reserved symbols (reserved symols, function names, etc) and make a binary lookup
//be careful around things of the form f(x) = ... ; g(x) = f with no arg; this must be checked
//max size for matrices?
//upper limit for all numbers?
//some increment functions allocate, others do not
//no () after matrix function assignment
//some print functions print retarded stuff like -0 etc.
//destructive polynomial operations?
//insert implicit stars before parsing?

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    // data_vector = get_data_vector();

    data = data_init();

    // test_sequence(valid_sequence);
    // test_all_sequences(valid_sequences);
    // test_all_sequences(valid_matrix_sequences);
    test_all_sequences(valid_polynomial_sequences);
    // test();
    // matrix_test();
    // math_test();
    // polynomial_test();

    printf("\nMEMORY USAGE: %Ld\n", data_get_bytes(data));

    data_delete(&data);
    end = clock();

    printf("TIME ELAPSED: %f S\n", (end - start)/(double)CLOCKS_PER_SEC);

    return 0;
}