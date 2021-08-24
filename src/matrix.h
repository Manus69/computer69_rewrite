#ifndef MATRIX_H
#define MATRIX_H

#include "why_vector_interface.h"

struct MatrixRepr
{
    Vector *rows;
    int_signed n_cols;
};

#endif