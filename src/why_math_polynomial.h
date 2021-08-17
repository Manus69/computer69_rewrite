#ifndef WHY_MATH_POLYNOMIAL_H
#define WHY_MATH_POLYNOMIAL_H

#include "why_math.h"
#include "why_definitions.h"
#include "why_vector_interface.h"
#include "why_math_complex.h"

// #define P_MAX_DEGREE (1 << 4)

#define P_DEFAULT_SIZE (1 << 1)

struct Polynomial
{
    // Complex coefficients[P_MAX_DEGREE + 1];
    Complex *coefficients;
    char *variable;
    int_signed degree;
    int_signed capacity;
};

#endif