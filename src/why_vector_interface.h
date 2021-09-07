#ifndef WHY_VECTOR_INTERFACE_H
#define WHY_VECTOR_INTERFACE_H

#include "why_definitions.h"

#define V_CAPACITY_DEFAULT (1 << 3)

typedef struct Vector Vector;

Vector      *vector_new(void *(*copy)(), void (*delete_)());
Vector      *vector_new_with_capacity(void *(copy)(), void (*delete)(), int_signed capacity);
Vector      *vector_copy(const Vector *vector);
Vector      *vector_copy_with(const Vector *vector, void *(*copy_function)());
Vector      *vector_concat(Vector *lhs, const Vector *rhs);
Vector      *vector_concatG(Vector *lhs, const Vector *rhs, void *(copy)());
boolean     vector_push(Vector *vector, void *item);
boolean     vector_pushG(Vector *vector, void *item, void *(*copy)());
int_signed  vector_size(const Vector *vector);
void        *vector_at(const Vector *vector, int_signed index);
void        *vector_set(Vector *vector, void *item, int_signed index);
void        *vector_pop(Vector *vector);
void        vector_map(Vector *vector, void (*function)());
void        vector_swap(Vector *vector, int_signed m, int_signed n);
void        vector_delete(Vector **vector);
void        vector_delete_no_content(Vector **vector);

#endif