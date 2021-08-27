#ifndef MATRIX_REPR_H
#define MATRIX_REPR_H

#include "why_vector_interface.h"

#define COPY_FUNCTION computation_copy_wrapper

struct MatrixRepr
{
    Vector *items;
    int_signed n_cols;
    int_signed n_rows;
};

#endif