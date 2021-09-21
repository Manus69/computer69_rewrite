
#ifndef WHY_BUFFER_H
#define WHY_BUFFER_H

#include "why_definitions.h"

#define BUFFER_DEFAULT_SIZE (1 << 1)
#define BUFFER_BRICK -1

struct Buffer
{
    char*   bytes;
    char*   read_pointer;
    char*   search_pointer;
    char*   write_pointer;

    int_signed size;
};

#endif