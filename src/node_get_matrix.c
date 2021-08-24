#include "frontend_declarations.h"
#include "node.h"

Node *node_get_matrix(String *string)
{
    MatrixRepr *matrix;
    int_signed n;

    n = find_matching_bracket_str(string);
    if (n == NOT_FOUND)
        return NULL;

    return NULL;
}
