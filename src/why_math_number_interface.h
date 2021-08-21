#ifndef WHY_MATH_NUMBER_INTERFACE_H
#define WHY_MATH_NUMBER_INTERFACE_H

#include "why_definitions.h"
#include "why_math_complex.h"

int_signed add_int(int_signed n, int_signed m);
int_signed mult_int(int_signed n, int_signed m);
int_signed subtract_int(int_signed n, int_signed m);
int_signed divide_int(int_signed n, int_signed m);
int_signed mod_int(int_signed n, int_signed m);
real add_real(real x, real y);
real mult_real(real x, real y);
real subtract_real(real x, real y);
real divide_real(real x, real y);

boolean real_is_zero(real *x);
void *real_add(real *x, real *y);
void *real_mult(real *x, real *y);

boolean complex_is_zero_p(Complex *z);
void *complex_add_p(Complex *z, Complex *w);
void *complex_mult_p(Complex *z, Complex *w);

#endif