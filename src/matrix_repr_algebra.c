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
    
    matrix = matrix_repr_new_fixed_size(lhs->n_rows, lhs->n_cols);
    matrix = _matrix_operation(matrix, lhs, rhs, _add_jk);

    return matrix;
}

MatrixRepr *matrix_repr_subtract(MatrixRepr *lhs, MatrixRepr *rhs)
{
    MatrixRepr *matrix;

    if (!matrix_repr_equal_size(lhs, rhs))
        return NULL;
    
    matrix = matrix_repr_new_fixed_size(lhs->n_rows, lhs->n_cols);
    matrix = _matrix_operation(matrix, lhs, rhs, _subtract_jk);

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

//this is a placeholder
MatrixRepr *matrix_repr_power(MatrixRepr *lhs, Number *number)
{
    MatrixRepr *matrix;
    MatrixRepr *pointer;
    int_signed m;
    int_signed n;

    if (number_get_type(number) != NT_INT)
        return NULL;

    n = number_get_int(number);

    if (!matrix_repr_is_square(lhs))
        return NULL;
    if (n < 0)
        return NULL;
    if (n == 0)
        return matrix_repr_I(lhs->n_cols);
    if (n == 1)
        return matrix_repr_copy(lhs);

    m = 0;
    matrix = matrix_repr_copy(lhs);
    pointer = matrix;
    while (m < n)
    {
        matrix = matrix_repr_mult(matrix, lhs);
        matrix_repr_delete(&pointer);
        pointer = matrix;

        m ++;
    }

    return matrix;
}

MatrixRepr *matrix_repr_I(int_signed size)
{
    MatrixRepr *matrix;
    Computation *item;
    int_signed j;
    int_signed k;
    Node *node;

    matrix = matrix_repr_new_fixed_size(size, size);
    j = 0;
    while (j < size)
    {
        k = 0;
        while (k < size)
        {
            node = node_new(number_new_int(k == j), NT_NUMBER, FALSE);
            item = computation_new(node, FALSE);

            matrix_repr_set(matrix, item, j, k);

            k ++;
        }

        j ++;
    }

    return matrix;
}