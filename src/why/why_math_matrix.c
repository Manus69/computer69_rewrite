#include "why_math_matrix.h"
#include "why_memory.h"
#include "why_math_complex.h"

Matrix* matrix_new(int_signed n_rows, int_signed n_cols)
{
    Matrix*     matrix;
    int_signed  size;

    matrix = allocate(sizeof(Matrix));
    size = n_rows * n_cols;
    matrix->array = allocate(sizeof(Complex) * size);
    matrix->n_rows = n_rows;
    matrix->n_cols = n_cols;

    return matrix;
}

void matrix_delete(Matrix** matrix)
{
    if (!matrix || !*matrix)
        return ;
    
    free((*matrix)->array);
    free(*matrix);
    *matrix = NULL;
}

Complex matrix_at(Matrix* A, int_signed j, int_signed k)
{
    return A->array[A->n_cols * j + k];
}

boolean matrix_set(Matrix* A, Complex z, int_signed j, int_signed k)
{
    A->array[A->n_cols * j + k] = z;

    return TRUE;
}

Matrix* matrix_eye(int_signed size);
Matrix* matrix_add(Matrix* A, Matrix* B);
Matrix* matrix_mult(Matrix* A, Matrix* B);