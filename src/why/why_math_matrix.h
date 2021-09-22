#ifndef WHY_MATH_MATRIX_H
#define WHY_MATH_MATRIX_H

#include "why_definitions.h"
#include "why_math.h"

struct Matrix
{
    Complex*    array;
    int_signed  n_rows;
    int_signed  n_cols;
};

#endif