#include "matrix_repr.h"
#include "frontend_declarations.h"
#include "frontend_declarations.h"
#include "terminals.h"

#include <assert.h>

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

boolean matrix_repr_set(MatrixRepr *matrix, Computation *value, int_signed j, int_signed k)
{
    Vector *row;
    Computation *old_value;

    row = matrix_repr_get_row(matrix, j);
    old_value = vector_at(row, k);
    computation_delete(&old_value);
    vector_set(row, value, k);

    return TRUE;
}

static Vector *_process_elements(const Vector *elements, const VariableTable *v_table)
{
    Vector *row;
    // Variable *variable;
    String *element;
    int_signed n;
    int_signed length;
    Computation *computation;

    row = matrix_row_new();
    n = 0;
    length = vector_size(elements);
    while (n < length)
    {
        element = vector_at(elements, n);
        // variable = variable_create_with_name(element, v_table, NULL);
        // vector_push(row, variable);
        computation = _parse(element, v_table);
        vector_push(row, computation);
        n ++;
    }

    return row;
}

Vector *matrix_row_from_string(String *string, const VariableTable *v_table)
{
    int_signed n;
    String *substring;
    Vector *elements;
    Vector *row;

    n = find_matching_bracket_str(string, TERMINALS[O_BRACKET], TERMINALS[C_BRACKET]);
    if (n == NOT_FOUND || n < 2)
        return NULL;

    substring = string_substring(string, 1, n - 1);
    elements = string_split(substring, TERMINALS[COMMA]);

    row = _process_elements(elements, v_table);
    if (row)
    {
        _string_shift(string, n);
    }
    else assert(0);

    string_delete(&substring);
    vector_delete(&elements);

    return row;
}

MatrixRepr *matrix_repr_add_row(MatrixRepr *matrix, Vector *row)
{
    if (matrix->n_cols == -1)
    {
        vector_push(matrix->rows, row);
        matrix->n_cols = vector_size(row);
    }
    else if (matrix->n_cols == vector_size(row))
        vector_push(matrix->rows, row);
    else
        assert(0);

    return matrix;
}

static MatrixRepr *_get_matrix(String *string, const VariableTable *v_table)
{
    MatrixRepr *matrix;
    Vector *rows;
    Vector *row;
    int_signed n;
    int_signed length;

    matrix = matrix_repr_new();
    rows = string_split(string, TERMINALS[SEMICOLON]);
    length = vector_size(rows);
    n = 0;

    while (n < length)
    {
        row = matrix_row_from_string(vector_at(rows, n), v_table);
        matrix_repr_add_row(matrix, row);
        n ++;
    }

    vector_delete(&rows);

    return matrix;
}

MatrixRepr *matrix_repr_from_string(String *string, const VariableTable *v_table)
{
    MatrixRepr *matrix;
    int_signed index;
    String *substring;

    index = find_matching_bracket_str(string, TERMINALS[O_BRACKET], TERMINALS[C_BRACKET]);
    if (index == NOT_FOUND || index < 4)
        return NULL;
    
    substring = string_substring(string, 1, index - 1);
    _string_shift(string, index + 1);
    
    matrix = _get_matrix(substring, v_table);
    string_delete(&substring);

    return matrix;
}

void matrix_repr_delete(MatrixRepr **matrix)
{
    if (!matrix || !*matrix)
        return ;

    vector_delete(&(*matrix)->rows);
    free(*matrix);
    *matrix = NULL;
}

MatrixRepr *matrix_repr_copy(const MatrixRepr *matrix)
{
    return (MatrixRepr *)matrix;
}