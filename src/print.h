#ifndef PRINT_H
#define PRINT_H

#include "number.h"
#include "why_vector_interface.h"

#define TOLERANCE (1.0/10000)

void print_int(int_signed n);
void print_real(real x);
void print_complex(Complex z);
void print_number(const Number *number);
void print_string(const char *string);
void print_vector(const Vector *vector, void (*print)());

#endif