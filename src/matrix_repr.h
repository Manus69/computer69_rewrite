#ifndef MATRIX_REPR_H
#define MATRIX_REPR_H

#include "why_vector_interface.h"

#define COPY_FUNCTION entity_copy_wrapper
// #define COPY_FUNCTION copy_shallow

struct MatrixRepr
{
    Vector *items;
    int_signed n_cols;
    int_signed n_rows;
};

#endif