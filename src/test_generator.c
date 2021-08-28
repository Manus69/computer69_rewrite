#include "frontend_declarations.h"

#define FACTOR (real) 100 / RAND_MAX;
#define MOD 1000

static Entity *_get_random_int()
{
    int_signed value;

    value = rand() % MOD;
    value = (rand() % 2) ? value : -value; 

    return entity_new_from_number(number_new_int(value), FALSE);
}

static Entity *_get_random_real()
{
    real value;

    value = rand() * FACTOR;
    value = (rand() % 2) ? value : -value;

    return entity_new_from_number(number_new_real(value), FALSE);
}

static Entity *_get_random_complex()
{
    Complex value;

    value.re = rand() * FACTOR;
    value.re = (rand() % 2) ? value.re : -value.re; 

    value.im = rand() * FACTOR;
    value.im = (rand() % 2) ? value.im : -value.im;

    return entity_new_from_number(number_new_complex(value), FALSE);
}

static void *getters[] = {_get_random_int, _get_random_real, _get_random_complex, 0};

MatrixRepr *generate_random_matrix(int_signed n_rows, int_signed n_cols, NUMBER_TYPE type)
{
    Entity *value;
    int_signed n;
    int_signed size;
    MatrixRepr *matrix;
    Entity *(*get)();

    get = getters[type];

    srand(0);
    matrix = matrix_repr_new_fixed_size(n_rows, n_cols);
    size = n_rows * n_cols;
    n = 0;

    while (n < size)
    {
        value = get();
        matrix_repr_set_nth(matrix, value, n);

        n ++;
    }

    return matrix;
}
