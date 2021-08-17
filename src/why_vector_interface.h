#ifndef WHY_VECTOR_INTERFACE_H
#define WHY_VECTOR_INTERFACE_H

#include "why_definitions.h"

#define V_CAPACITY_DEFAULT (1 << 1)

typedef struct Vector Vector;

Vector *vector_new(void *(*copy)(), void (*delete_)());
void vector_delete(Vector **vector);

void *vector_at(const Vector *vector, int_signed index);
void *vector_set(Vector *vector, void *item, int_signed index);
int_signed vector_size(const Vector *vector);
boolean vector_push(Vector *vector, void *item);
void *vector_pop(Vector *vector);
void vector_map(Vector *vector, void (*function)());
void vector_swap(Vector *vector, int_signed m, int_signed n);

#endif