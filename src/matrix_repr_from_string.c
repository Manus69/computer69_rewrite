#include "frontend_declarations.h"
#include "terminals.h"
#include "matrix_repr.h"
#include "why_error.h"

#if DBG
    #include "print.h"
    #include <stdio.h>
#endif

static MatrixRepr* _process_row(MatrixRepr* matrix, String* row_string, const VariableTable* v_table)
{
    Vector*     items;
    Entity*     item;
    String*     item_string;
    int_signed  n;

    items = string_split(row_string, TERMINALS[COMMA]);
    n = 0;

    if (!matrix->n_cols)
        matrix->n_cols = vector_size(items);
    if (matrix->n_cols == 0 || matrix->n_cols != vector_size(items))
    {
        vector_delete(&items);
        return NULL;
    }
    if (matrix->n_cols > MATRIX_MAX_SIZE)
    {
        vector_delete(&items);
        return error_set(WHY_ERROR_GENERIC, "the matrix is too large");
    }

    while (n < vector_size(items))
    {
        item_string = vector_at(items, n);
        item = entity_new_from_computation(parse(item_string, v_table), FALSE);
        matrix_repr_push(matrix, item);

        n ++;
    }

    vector_delete(&items);

    return matrix;
}

static MatrixRepr* _process_rows(Vector* rows, const VariableTable* v_table)
{
    MatrixRepr* matrix;
    String*     row_string;
    String*     substring;
    int_signed  n;
    int_signed  length;

    matrix = matrix_repr_new(COPY_FUNCTION);
    n = 0;
    
    matrix->n_rows = vector_size(rows);

    if (matrix->n_rows > MATRIX_MAX_SIZE)
        return error_set(WHY_ERROR_GENERIC, "the matrix is too large");
    
    while (n < vector_size(rows))
    {
        row_string = vector_at(rows, n);
        row_string = string_skip_spaces(row_string);
        length = id_row(row_string);
        if (!length || length != string_length(row_string))
            return NULL;

        substring = string_substring(row_string, 1, length - 2);
        if (!_process_row(matrix, substring, v_table))
        {
            string_delete(&substring);
            return NULL;
        }
        
        string_delete(&substring);
        n ++;
    }

    return matrix;
}

MatrixRepr* matrix_repr_from_string(String* string, const VariableTable* v_table)
{
    MatrixRepr*     matrix;
    String*         substring;
    Vector*         rows;
    int_unsigned    length;

    length = id_matrix(string);
    if (!length)
        return NULL;

    substring = string_substring(string, 1, length - 2);
    rows = string_split(substring, TERMINALS[SEMICOLON]);

    matrix = _process_rows(rows, v_table);

    _string_shift(string, length);
    
    string_delete(&substring);
    vector_delete(&rows);

    return matrix;
}