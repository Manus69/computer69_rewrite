#include "frontend_declarations.h"
#include "terminals.h"
#include "matrix_repr.h"

#include "print.h"
#include <stdio.h>
#include <assert.h>

static MatrixRepr *_process_row(MatrixRepr *matrix, String *row_string, const VariableTable *v_table)
{
    Vector *items;
    Entity *item;
    String *item_string;
    int_signed n;

    items = string_split(row_string, TERMINALS[COMMA]);
    n = 0;

    if (!matrix->n_cols)
        matrix->n_cols = vector_size(items);
    if (matrix->n_cols == 0 || matrix->n_cols != vector_size(items))
        assert(0);

    while (n < vector_size(items))
    {
        item_string = vector_at(items, n);
        item = entity_new_from_computation(_parse(item_string, v_table), FALSE);
        matrix_repr_push(matrix, item);

        // entity_delete(&item);
        n ++;
    }

    vector_delete(&items);

    return matrix;
}

static MatrixRepr *_process_rows(Vector *rows, const VariableTable *v_table)
{
    MatrixRepr *matrix;
    String *row_string;
    String *substring;
    int_signed n;
    int_signed length;

    matrix = matrix_repr_new(COPY_FUNCTION);
    n = 0;
    
    matrix->n_rows = vector_size(rows);

    while (n < vector_size(rows))
    {
        row_string = vector_at(rows, n);
        length = id_row(row_string);
        if (!length)
            assert(0);

        substring = string_substring(row_string, 1, length - 2);

        #if DBG
        print_string_n(substring);
        #endif

        _process_row(matrix, substring, v_table);
        
        string_delete(&substring);
        n ++;
    }

    return matrix;
}

MatrixRepr *matrix_repr_from_string(String *string, const VariableTable *v_table)
{
    MatrixRepr *matrix;
    int_unsigned length;
    String *substring;
    Vector *rows;

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