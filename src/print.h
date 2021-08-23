#ifndef PRINT_H
#define PRINT_H

#include "frontend_definitions.h"

#define WC_SYMBOL "_"

void print_number(const Number *number);
void print_computation(const Computation *computation);
void print_variable(const Variable *variable);

#endif