#ifndef WHY_LIB_H
#define WHY_LIB_H

#include "why_definitions.h"
#include "why_macros.h"
#include "why_memory.h"
#include "why_math.h"
#include "why_string_interface.h"
#include "why_vector_interface.h"
#include "why_list_interface.h"
#include "why_math_number_interface.h"
#include "why_tree_interface.h"
#include "why_conversion.h"
#include "why_copy.h"
#include "why_print.h"
#include "why_cstring.h"

#define OVERFLOW_CHECK TRUE

Vector* string_split(String* string, char delimiter);
Vector* cstr_split(char* string, char delimiter);
String* get_line(int file_descriptor);
String* get_all_lines(int file_descriptor);

#endif