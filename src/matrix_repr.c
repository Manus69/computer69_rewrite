#include "matrix_repr.h"
#include "frontend_declarations.h"
#include "frontend_declarations.h"
#include "terminals.h"

#include <assert.h>
#include "print.h"

Vector *matrix_row_new()
{
    // return vector_new(copy_shallow, variable_delete);
    return vector_new(copy_shallow, computation_delete);
}

MatrixRepr *matrix_repr_new()
{
    MatrixRepr *matrix;

    matrix = allocate(sizeof(MatrixRepr));
    matrix->rows = vector_new(copy_shallow, vector_delete);
    matrix->n_cols = -1;

    return matrix;
}

static Vector *_row_of_zeroes(int_signed size)
{
    int_signed n;
    Vector *row;

    n = 0;
    row = matrix_row_new();
    while (n < size)
    {
        vector_push(row, NULL);
        n ++;
    }

    return row;
}

MatrixRepr *matrix_repr_new_fixed_size(int_signed n_rows, int_signed n_cols)
{
    Vector *row;
    MatrixRepr *matrix;
    int_signed j;

    matrix = matrix_repr_new();
    j = 0;
    while (j < n_rows)
    {
        row = _row_of_zeroes(n_cols);
        matrix_repr_add_row(matrix, row);

        j ++;
    }
    
    return matrix;
}

Vector *matrix_repr_get_row(const MatrixRepr *matrix, int_signed n)
{
    return vector_at(matrix->rows, n);
}

int_signed matrix_repr_n_cols(const MatrixRepr *matrix)
{
    return matrix->n_cols;
}

int_signed matrix_repr_n_rows(const MatrixRepr *matrix)
{
    return vector_size(matrix->rows);
}

boolean matrix_repr_is_square(const MatrixRepr *matrix)
{
    if (matrix_repr_n_rows(matrix) == matrix_repr_n_cols(matrix))
        return TRUE;
    
    return FALSE;
}

boolean matrix_repr_equal_size(const MatrixRepr *lhs, const MatrixRepr *rhs)
{
    if (lhs->n_cols != rhs->n_cols)
        return FALSE;
    
    return matrix_repr_n_rows(lhs) == matrix_repr_n_rows(rhs);
}

Computation *matrix_repr_at(const MatrixRepr *matrix, int_signed j, int_signed k)
{
    Vector *row;
    Computation *value;

    row = matrix_repr_get_row(matrix, j);
    value = vector_at(row, k);

    return value;
}

Computation *matrix_repr_nth(const MatrixRepr *matrix, int_signed n)
{
    int_signed j;
    int_signed k;
    int_signed n_cols;

    n_cols = matrix_repr_n_cols(matrix);

    j = n / n_cols;
    k = n % n_cols;

    return matrix_repr_at(matrix, j, k);
}

boolean matrix_repr_set_nth(MatrixRepr *matrix, Computation *value, int_signed n)
{
    int_signed j;
    int_signed k;
    int_signed n_cols;

    n_cols = matrix_repr_n_cols(matrix);

    j = n / n_cols;
    k = n % n_cols;

    matrix_repr_set(matrix, value, j, k);

    return TRUE;
}

boolean matrix_repr_set(MatrixRepr *matrix, Computation *value, int_signed j, int_signed k)
{
    Vector *row;
    Computation *old_value;
    Computation *new_value;

    row = matrix_repr_get_row(matrix, j);
    old_value = vector_at(row, k);
    new_value = computation_copy(value);
    vector_set(row, new_value, k);
    
    // computation_delete(&old_value);

    return TRUE;
}

void matrix_repr_delete(MatrixRepr **matrix)
{
    if (!matrix || !*matrix)
        return ;

    vector_delete(&(*matrix)->rows);
    free(*matrix);
    *matrix = NULL;
}

static void _copy_iterate(MatrixRepr *copy, const MatrixRepr *matrix, int_signed n_rows, int_signed n_cols)
{
    int_signed j;
    int_signed k;
    Computation *value;

    j = 0;
    while (j < n_rows)
    {
        k = 0;
        while (k < n_cols)
        {
            value = matrix_repr_at(matrix, j, k);
            value = computation_copy(value);
            matrix_repr_set(copy, value, j, k);

            k ++;
        }

        j ++;
    }
}

MatrixRepr *matrix_repr_copy(const MatrixRepr *matrix)
{
    MatrixRepr *copy;
    int_signed n_rows;
    int_signed n_cols;

    n_rows = matrix_repr_n_rows(matrix);
    n_cols = matrix_repr_n_cols(matrix);
    copy = matrix_repr_new_fixed_size(n_rows, n_cols);

    _copy_iterate(copy, matrix, n_rows, n_cols);

    return copy;
}
