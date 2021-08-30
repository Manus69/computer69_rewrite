#ifndef WHY_MATH_H
#define WHY_MATH_H

#include "why_definitions.h"
#include "why_vector_interface.h"

#define EPSILON (((real)1) / (1 << 12))
#define PI (real)3.1415926535
#define E (real)2.7182818284

typedef struct Complex Complex;
typedef struct Polynomial Polynomial;
typedef struct Matrix Matrix;

boolean         within_delta(real x, real y, real delta);
boolean         real_is_int(real x);
real            math_mod(real x, real mod);
real            power(real base, int_unsigned n);
real            absolute_value(real x);
int_signed      power_int(int_signed base, int_unsigned n);
int_unsigned    factorial(int_unsigned n);
int_unsigned    round_to_int(real x);
int_unsigned    fib(int_unsigned n);

//
real            math_sqrt(real a);
real            math_id(real x);
real            math_sin(real x);
real            math_cos(real x);
real            math_tan(real x);
real            math_log(real x, int_unsigned base);
real            math_log2();

Complex complex_id(Complex z);
Complex complex_sin(Complex z);
Complex complex_cos(Complex z);
Complex complex_tan(Complex z);
Complex complex_log(Complex z);

//
Complex complex(real re, real im);
Complex *complex_new(real re, real im);
Complex *complex_copy(Complex *z);
Complex complex_zero();
Complex complex_add(Complex lhs, Complex rhs);
Complex complex_mult(Complex lhs, Complex rhs);
Complex complex_div(Complex lhs, Complex rhs);
Complex complex_subtract(Complex lhs, Complex rhs);
Complex complex_inv(Complex z);
boolean complex_is_real(Complex z);
boolean complex_is_zero(Complex z);
Complex complex_scale(Complex z, real a);
Complex complex_conjugate(Complex z);
Complex complex_power(Complex z, int_unsigned n);
real complex_mod_squared(Complex z);

//
Polynomial *polynomial_new(char *variable);
Polynomial *polynomial_new_from_complex(Complex z);
Polynomial *polynomial_new_from_complexG(Complex z, int_signed degree, char *variable);
Polynomial *polynomial_new_from_coefficients(real coefficients[], int_signed size);
Polynomial *polynomial_copy(const Polynomial *p);
void polynomial_delete(Polynomial **p);
int_signed polynomial_get_degree(const Polynomial *p);
char *polynomial_get_variable(const Polynomial *p);
Complex polynomial_at(const Polynomial *p, int_signed degree);
boolean polynomial_set(Polynomial *p, Complex value, int_signed degree);
Polynomial *polynomial_increment(Polynomial *p, Polynomial *q);
Polynomial *polynomial_add(Polynomial *p, Polynomial *q);
Polynomial *polynomial_subtract(Polynomial *p, Polynomial *q);
Polynomial *polynomial_multiply(Polynomial *p, Polynomial *q);
Polynomial *polynomial_scale(Polynomial *p, Complex factor);
Polynomial *polynomial_exponentiate(Polynomial *p, int_signed power);
Polynomial *polynomial_factor(Polynomial *p, Polynomial *q);
Polynomial *polynomial_differentiate(Polynomial *p);
Complex polynomial_evaluate(Polynomial *p, Complex value);
boolean polynomial_is_constant(const Polynomial *p);
Complex polynomial_get_constant_coefficient(const Polynomial *p);
boolean polynomial_is_real(const Polynomial *p);
Vector *polynomial_roots(const Polynomial *p);

//
Matrix *matrix_new(int_signed n_rows, int_signed n_cols);
void matrix_delete(Matrix **matrix);
Complex matrix_at(Matrix *A, int_signed j, int_signed k);
boolean matrix_set(Matrix *A, Complex z, int_signed j, int_signed k);
Matrix *matrix_eye(int_signed size);
Matrix *matrix_add(Matrix *A, Matrix *B);
Matrix *matrix_mult(Matrix *A, Matrix *B);

#endif