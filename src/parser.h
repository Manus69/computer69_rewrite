#ifndef PARSER_H
#define PARSER_H

#include "frontend_declarations.h"

Computation* get_operator(String* string);
Computation* get_term(String* string, const VariableTable* v_table);
Computation* get_stuff_in_parens(String* string, const VariableTable* v_table);
Computation* get_function(String* string, const VariableTable* v_table);
Computation* get_identifier(String* string);
Computation* get_operator(String* string);

#endif