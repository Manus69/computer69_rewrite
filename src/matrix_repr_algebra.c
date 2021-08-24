#include "frontend_declarations.h"
#include "matrix_repr.h"

static Computation *_add_jk(const MatrixRepr *lhs, const MatrixRepr *rhs, int_signed j, int_signed k)
{
    Computation *result;
    Computation *_lhs;
    Computation *_rhs;

    _lhs = matrix_repr_at(lhs, j, k);
    _rhs = matrix_repr_at(rhs, j, k);
    result = computation_add(_lhs, _rhs);

    return result;
}

static Computation *_subtract_jk(const MatrixRepr *lhs, const MatrixRepr *rhs, int_signed j, int_signed k)
{
    Computation *result;
    Computation *_lhs;
    Computation *_rhs;

    _lhs = matrix_repr_at(lhs, j, k);
    _rhs = matrix_repr_at(rhs, j, k);
    result = computation_subtract(_lhs, _rhs);

    return result;
}

static Computation *_multiply_jk(const MatrixRepr *lhs, const MatrixRepr *rhs, int_signed j, int_signed k)
{
    Computation *result;
    Computation *product;
    Computation *_lhs;
    Computation *_rhs;
    int_signed w;

    if (!lhs->n_cols)
        return NULL;
    
    _lhs = matrix_repr_at(lhs, j, 0);
    _rhs = matrix_repr_at(rhs, 0, k);
    product = computation_mult(_lhs, _rhs);
    result = product;
    w = 1;

    while (w < lhs->n_cols)
    {
        _lhs = matrix_repr_at(lhs, j, w);
        _rhs = matrix_repr_at(rhs, w, k);
        product = computation_mult(_lhs, _rhs);        
        result = computation_increment(result, product);
        w ++;
    }

    return result;
}

static MatrixRepr *_matrix_operation(MatrixRepr *matrix, MatrixRepr *lhs, MatrixRepr *rhs, Computation *(*combine_jk)())
{
    int_signed j;
    int_signed k;
    int_signed n_rows;
    Computation *value;

    j = 0;
    n_rows = matrix_repr_n_rows(matrix);
    while (j < n_rows)
    {
        k = 0;
        while (k < matrix->n_cols)
        {
            value = combine_jk(lhs, rhs, j, k);
            matrix_repr_set(matrix, value, j, k);

            k ++;
        }

        j ++;
    }

    return matrix;
}

MatrixRepr *matrix_repr_add(MatrixRepr *lhs, MatrixRepr *rhs)
{
    MatrixRepr *matrix;

    if (!matrix_repr_equal_size(lhs, rhs))
        return NULL;
    
    matrix = matrix_repr_new_fixed_size(matrix_repr_n_rows(lhs), lhs->n_cols);
    matrix = _matrix_operation(matrix, lhs, rhs, _add_jk);

    return matrix;
}

MatrixRepr *matrix_repr_mult(MatrixRepr *lhs, MatrixRepr *rhs)
{
    MatrixRepr *matrix;

    if (matrix_repr_n_cols(lhs) != matrix_repr_n_rows(rhs))
        return NULL;
    
    matrix = matrix_repr_new_fixed_size(matrix_repr_n_rows(lhs), lhs->n_cols);
    matrix = _matrix_operation(matrix, lhs, rhs, _multiply_jk);

    return matrix;
}

MatrixRepr *matrix_repr_scale(MatrixRepr *matrix, Number *number)
{
    Computation *value;
    int_signed j;
    int_signed k;
    int_signed n_rows;

    n_rows = matrix_repr_n_rows(matrix);
    j = 0;
    while (j < n_rows)
    {
        k = 0;
        while (k < matrix->n_cols)
        {
            value = matrix_repr_at(matrix, j, k);
            value = computation_scale(value, number);
            matrix_repr_set(matrix, value, j, k);

            k ++;
        }

        j ++;
    }

    return matrix;
}

MatrixRepr *matrix_repr_subtract(MatrixRepr *lhs, MatrixRepr *rhs);
MatrixRepr *matrix_repr_divide(MatrixRepr *lhs, MatrixRepr *rhs);
MatrixRepr *matrix_repr_mod(MatrixRepr *lhs, MatrixRepr *rhs);
MatrixRepr *matrix_repr_power(MatrixRepr *lhs, MatrixRepr *rhs);
MatrixRepr *matrix_repr_factorial(MatrixRepr *lhs, MatrixRepr *rhs);