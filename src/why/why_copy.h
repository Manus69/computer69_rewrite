#ifndef WHY_COPY_H
#define WHY_COPY_H

#include "why_definitions.h"
#include "why_math_complex.h"

void* copy_shallow(const void* item);
void* copy_int_signed(int_signed* n);
void* copy_real(real* x);
void* copy_complex(Complex* z);
void* copy_cstring(const char* string);

#endif