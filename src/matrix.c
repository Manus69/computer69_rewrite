#include "matrix.h"
#include "frontend_declarations.h"
#include "frontend_declarations.h"

MatrixRepr *matrix_repr_new(String *string)
{
    return string ? NULL : NULL;
}

void matrix_repr_delete(MatrixRepr **matrix)
{
    if (matrix)
        return ;
}

MatrixRepr *matrix_repr_copy(const MatrixRepr *matrix)
{
    return (MatrixRepr *)matrix;
}