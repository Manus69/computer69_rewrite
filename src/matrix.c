#include "matrix.h"
#include "frontend_declarations.h"
#include "frontend_declarations.h"
#include "terminals.h"

#include <assert.h>

Vector *matrix_row_new()
{
    return vector_new(copy_shallow, variable_delete);
}

MatrixRepr *matrix_repr_new()
{
    MatrixRepr *matrix;

    matrix = allocate(sizeof(MatrixRepr));
    matrix->rows = vector_new(copy_shallow, vector_delete);
    matrix->n_cols = -1;

    return matrix;
}

Vector *matrix_repr_get_row(const MatrixRepr *matrix, int_signed n)
{
    return vector_at(matrix->rows, n);
}

int_signed matrix_repr_size(const MatrixRepr *matrix)
{
    return vector_size(matrix->rows);
}

static Vector *_process_elements(const Vector *elements, const VariableTable *v_table)
{
    Vector *row;
    Variable *variable;
    String *element;
    int_signed n;
    int_signed length;

    row = matrix_row_new();
    n = 0;
    length = vector_size(elements);
    while (n < length)
    {
        element = vector_at(elements, n);
        variable = variable_create_with_name(element, v_table, NULL);
        vector_push(row, variable);
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

    n = find_matching_bracket_str(string);
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
    int_signed length;
    String *substring;

    index = find_matching_bracket_str(string);
    length = string_length(string);
    if (index == NOT_FOUND || length < 5)
        return NULL;
    
    substring = string_substring(string, 1, length - 2);
    _string_shift(string, string_length(substring) + 2);
    
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