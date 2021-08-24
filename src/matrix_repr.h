#ifndef MATRIX_REPR_H
#define MATRIX_REPR_H

#include "why_vector_interface.h"

struct MatrixRepr
{
    Vector *rows;
    int_signed n_cols;
};

#endif