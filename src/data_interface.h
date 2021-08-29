#ifndef DATA_INTERFACE_H
#define DATA_INTERFACE_H

#include "frontend_definitions.h"

// Vector *data_vector;
Vector *get_data_vector();

Data *data_init();
void data_delete(Data **data);
void data_add_pointer(Data *data, void *pointer, int_signed size);
void data_add_vector_pointer(Data *data, void *pointer);
int_signed data_get_bytes(const Data *data);
void data_increment_bytes(Data *data, int_signed n_bytes);

#endif