#ifndef WHY_PRINT_H
#define WHY_PRINT_H

#include "why_definitions.h"
#include "why_vector_interface.h"
#include "why_math_complex.h"
#include "why_string_interface.h"
#include "why_list_interface.h"

#define TOLERANCE (1.0/10000)

void print_int(int_signed n);
void print_int_pointerN(int_signed *n);
void print_real(real x);
void print_complex(Complex z);
void print_cstring(const char *string);
void print_cstringN(const char *string);
void print_string(const String *string);
void print_string_n(const String *string);
void print_polynomial(const Polynomial *p);
void print_polynomial_with_rhs(const Polynomial *p);
void _print_polynomialDBG(const Polynomial *p);
void print_vector(const Vector *vector, void (*print)(), const char *separator);
void print_list(const List *list, void (*function)());

#endif