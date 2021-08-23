#include "frontend_declarations.h"

static const void *functions[] = {number_sin, number_cos, number_tan, number_log, number_abs, 0};

void *get_bft_pointer(BULITIN_FUNCTION_TYPE type)
{
    return (void *)functions[type];
}