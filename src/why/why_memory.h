#ifndef WHY_MEMORY_H
#define WHY_MEMORY_H

#include <stdlib.h>

#include "why_definitions.h"

void *allocate(int_unsigned size);
void *memory_copy(void *restrict destination, const void *restrict source, int_unsigned size);
void *memory_set(void *object, byte value, int_unsigned size);
void *reallocate(const void *item, int_unsigned current_size, int_unsigned extra_size);
void *memory_zero(int_unsigned size);
void memory_delete(void **item);

#endif