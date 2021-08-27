#include "matrix_repr.h"
#include "frontend_declarations.h"
#include "frontend_declarations.h"
#include "terminals.h"

#include <assert.h>
#include "print.h"

MatrixRepr *matrix_repr_new(void *(*copy)())
{
    MatrixRepr *matrix;

    matrix = allocate(sizeof(MatrixRepr));
    matrix->items = vector_new(copy, computation_delete);
    matrix->n_rows = 1;
    matrix->n_cols = 0;

    return matrix;
}

MatrixRepr *matrix_repr_new_fixed_size(int_signed n_rows, int_signed n_cols)
{
    MatrixRepr *matrix;
    int_signed n;
    int_signed size;

    size = n_rows * n_cols;
    n = 0;
    matrix = matrix_repr_new(COPY_FUNCTION);

    while (n < size)
    {
        vector_push(matrix->items, NULL);
        n ++;
    }
    
    matrix->n_rows = n_rows;
    matrix->n_cols = n_cols;

    return matrix;
}

int_signed matrix_repr_n_cols(const MatrixRepr *matrix)
{
    return matrix->n_cols;
}

int_signed matrix_repr_n_rows(const MatrixRepr *matrix)
{
    return matrix->n_rows;
}

boolean matrix_repr_is_square(const MatrixRepr *matrix)
{
    if (matrix->n_cols == matrix->n_rows)
        return TRUE;
    
    return FALSE;
}

boolean matrix_repr_equal_size(const MatrixRepr *lhs, const MatrixRepr *rhs)
{
    if (lhs->n_cols != rhs->n_cols)
        return FALSE;
    
    return lhs->n_rows== rhs->n_rows;
}

Computation *matrix_repr_at(const MatrixRepr *matrix, int_signed j, int_signed k)
{
    Computation *value;
    int_signed n;

    n = j * matrix->n_cols + k;
    value = vector_at(matrix->items, n);

    return value;
}

Computation *matrix_repr_nth(const MatrixRepr *matrix, int_signed n)
{
    return vector_at(matrix->items, n);
}

boolean matrix_repr_push(MatrixRepr *matrix, Computation *value)
{
    return vector_push(matrix->items, value);
}

Computation *matrix_repr_set(MatrixRepr *matrix, Computation *value, int_signed j, int_signed k)
{
    Computation *old_value;
    int_signed n;

    n = j * matrix->n_cols + k;
    old_value = vector_set(matrix->items, value, n);

    return old_value;
}

Computation *matrix_repr_set_nth(MatrixRepr *matrix, Computation *value, int_signed n)
{
    return vector_set(matrix->items, value, n);
}

void matrix_repr_delete(MatrixRepr **matrix)
{
    if (!matrix || !*matrix)
        return ;

    vector_delete(&(*matrix)->items);
    free(*matrix);
    *matrix = NULL;
}

MatrixRepr *matrix_repr_copy(const MatrixRepr *matrix)
{
    MatrixRepr *copy;
    
    copy = matrix_repr_new(COPY_FUNCTION);
    copy->items = vector_copy(matrix->items);
    copy->n_cols = matrix->n_cols;
    copy->n_rows = matrix->n_rows;

    return copy;
}
