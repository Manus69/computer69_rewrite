#include "why_heap_interface.h"
#include "why_vector_interface.h"
#include "why_vector.h"
#include "why_memory.h"
#include "why_macros.h"

//not tested

Heap* heap_new(void* (*copy)(), void (*delete)(), int_signed (*compare)())
{
    Heap* heap;

    heap = vector_new(copy, delete);
    heap->compare = compare;

    return heap;
}

void heap_delete(Heap** heap)
{
    return vector_delete(heap);
}

void heap_map(Heap* heap, void (*function)())
{
    return vector_map(heap, function);
}

void heap_swap(Heap* heap, int_signed m, int_signed n)
{
    return vector_swap(heap, m, n);
}

static int_signed _index_of_parent(int_signed index)
{
    return (index - 1) / 2;
}

static int_signed _index_of_left_child(int_signed index)
{
    return 2*  index + 1;
}

static int_signed _index_of_right_child(int_signed index)
{
    return 2*  index + 2;
}

static void* _get_parent(Heap* heap, int_signed index)
{
    return heap->items[_index_of_parent(index)];
}

void* _get_left_child(Heap* heap, int_signed index)
{
    int_signed child_index;

    child_index = _index_of_left_child(index);
    if (child_index >= heap->current_index)
        return NULL;

    return heap->items[child_index];
}

void* _get_right_child(Heap* heap, int_signed index)
{
    int_signed child_index;

    child_index = _index_of_right_child(index);
    if (child_index >= heap->current_index)
        return NULL;

    return heap->items[child_index];
}

static void _restore_heap_property(Heap* heap, int_signed index)
{
    int_signed  parent_index;
    void*       parent;

    while (index)
    {
        parent_index = _index_of_parent(index);
        parent = _get_parent(heap, parent_index);

        if (heap->compare(parent, heap->items[index]) < 0)
            return ;

        heap_swap(heap, parent_index, index);
        index = parent_index;
    }
}

boolean heap_push(Heap* heap, void* item)
{
    if (vector_push(heap, item))
    {
        _restore_heap_property(heap, heap->current_index - 1);

        return TRUE;
    }
    
    return FALSE;
}
