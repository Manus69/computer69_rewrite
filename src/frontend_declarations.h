#ifndef FRONTEND_DECLARATIONS_H
#define FRONTEND_DECLARATIONS_H

#include "why_definitions.h"
#include "frontend_definitions.h"
#include "why_math_complex.h"

Number *number_new_int(int_signed n);
Number *number_new_real(real x);
Number *number_new_complex(Complex z);


#endif