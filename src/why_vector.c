#include "why_vector.h"
#include "why_vector_interface.h"
#include "why_memory.h"
#include "why_macros.h"

static void **_get_array(int_signed size)
{
    void **array;

    array = allocate(sizeof(void *) * size);
    size --;
    while (size >= 0)
    {
        array[size] = NULL;
        size --;
    }

    return array;
}

Vector *vector_new(void *(*copy)(), void (*delete)())
{
    Vector *vector;

    vector = allocate(sizeof(Vector));
    vector->items = _get_array(V_CAPACITY_DEFAULT);
    vector->copy = copy;
    vector->delete = delete;
    vector->current_index = 0;
    vector->capacity = V_CAPACITY_DEFAULT;
    vector->compare = NULL;

    return vector;
}

void vector_map(Vector *vector, void (*function)())
{
    int_signed n;

    n = 0;
    while (n < vector->current_index)
    {
        function(vector->items[n]);
        n ++;
    }
}

static void _delete_items(Vector *vector)
{
    int_signed n;

    if (!vector)
        return ;
    
    n = 0;
    while (n < vector->current_index)
    {
        vector->delete(&vector->items[n]);
        n ++;
    }
}

void vector_delete(Vector **vector)
{
    if (!vector || !*vector)
        return ;
    
    _delete_items(*vector);
    free((*vector)->items);
    free(*vector);
    *vector = NULL;
}

void *vector_at(const Vector *vector, int_signed index)
{
    if (!vector || index >= vector->current_index)
        return NULL;
    
    return vector->items[index];
}

int_signed vector_size(const Vector *vector)
{
    return vector->current_index;
}

void *vector_set(Vector *vector, void *item, int_signed index)
{
    void *return_value;

    if (index >= vector->current_index)
        return NULL;

    return_value = vector_at(vector, index);
    vector->items[index] = item;

    return return_value;
}

static boolean _reallocate_array(Vector *vector)
{
    int_signed new_capacity;
    void **new_array;

    new_capacity = vector->capacity * 2;
    new_array = _get_array(new_capacity);
    new_array = memory_copy(new_array, vector->items, vector->current_index * sizeof(void *));

    free(vector->items);
    vector->items = new_array;
    vector->capacity = new_capacity;

    return TRUE;
}

boolean vector_push(Vector *vector, void *item)
{
    if (vector->current_index == vector->capacity)
        _reallocate_array(vector);
    
    vector->items[vector->current_index] = vector->copy(item);
    vector->current_index ++;

    return TRUE;
}


void *vector_pop(Vector *vector)
{
    void *item;

    if (vector->current_index == 0)
        return NULL;
    
    item = vector_at(vector, vector->current_index - 1);
    vector->current_index --;

    return item;
}

void vector_swap(Vector *vector, int_signed m, int_signed n)
{
    SWAP(vector->items[m], vector->items[n], void *);
}

Vector *vector_copy(const Vector *vector)
{
    Vector *copy;
    void *item;
    int_signed n;
    int_signed length;

    if (!vector)
        return NULL;
    
    copy = vector_new(vector->copy, vector->delete);
    n = 0;
    length = vector->current_index;
    while (n < length)
    {
        item = copy->copy(vector->items[n]);
        vector_push(copy, item);

        n ++;
    }

    return copy;
}
