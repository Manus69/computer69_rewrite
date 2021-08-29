#ifndef DATA_H
#define DATA_H

#include "why_vector_interface.h"

#define DEFAULT_DATA_CAPACITY (1 << 11)
#define DATA_SIZE_THRESHOLD (1 << 20)

struct Data
{
    Vector *data_vector;
    Vector *vector_vector;
    int_signed bytes_allocated;
};

#endif