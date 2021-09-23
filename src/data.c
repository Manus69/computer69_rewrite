#include "frontend_declarations.h"
#include "data.h"
#include "why_error.h"

Data* data;

Vector* get_data_vector()
{
    return vector_new_with_capacity(copy_shallow, memory_delete, DEFAULT_DATA_CAPACITY);
}

Vector* get_vector_vector()
{
    return vector_new_with_capacity(copy_shallow, vector_delete_no_content, DEFAULT_DATA_CAPACITY);
}

Data* data_init()
{
    Data* data;

    data = allocate(sizeof(Data));
    data->data_vector = get_data_vector();
    data->vector_vector = get_vector_vector();
    data->bytes_allocated = 0;

    return data;
}

void data_delete(Data** data)
{
    if (!data || !*data)
        return ;

    vector_delete(&(*data)->data_vector);
    vector_delete(&(*data)->vector_vector);

    free(*data);
    *data = NULL;
}

void data_add_pointer(Data* data, void* pointer, int_signed size)
{
    vector_push(data->data_vector, pointer);
    data->bytes_allocated += size;

    #if CHECK_MEMORY
    if (data->bytes_allocated > DATA_SIZE_THRESHOLD)
        error_set(WHY_ERROR_MEMORY, "memory limit has been reached");
    #endif
}

void data_add_vector_pointer(Data* data, void* pointer)
{
    vector_push(data->vector_vector, pointer);
    data->bytes_allocated += 2 * sizeof(void *);
    data->bytes_allocated += V_CAPACITY_DEFAULT * sizeof(void *);

    #if CHECK_MEMORY
    if (data->bytes_allocated > DATA_SIZE_THRESHOLD)
        error_set(WHY_ERROR_MEMORY, "memory limit has been reached");
    #endif
}

void data_increment_bytes(Data* data, int_signed n_bytes)
{
    data->bytes_allocated += n_bytes;
}

int_signed data_get_bytes(const Data* data)
{
    return data->bytes_allocated;
}