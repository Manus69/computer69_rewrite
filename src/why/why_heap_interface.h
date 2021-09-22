#ifndef WHY_HEAP_INTERFACE_H
#define WHY_HEAP_INTERFACE_H

#include "why_definitions.h"

#define H_CAPACITY_DEFAULT (1 << 1)

typedef struct Vector Heap;

Heap*   heap_new(void* (*copy)(), void (*delete)(), int_signed (*compare)());
void    heap_delete(Heap** heap);

boolean heap_push(Heap* heap, void* item);
void*   heap_pop_root(Heap* heap);
void    heap_map(Heap* heap, void (*function)());

#endif