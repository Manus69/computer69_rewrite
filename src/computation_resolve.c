#include "frontend_declarations.h"
#include "computation.h"
#include "node.h"

void computation_resolve(Computation *computation, const String *wc_identifier, VariableTable *v_table)
{
    Node *node;
    Variable *variable;

    if (!computation)
        return ;
    
    computation_resolve(computation->lhs, wc_identifier, v_table);

    node = computation_get_node(computation);
    if (node->type == NT_IDENTIFIER)
    {
        if (string_is_identical(node->identifier, wc_identifier))
            node_convert_to_wildcard(node);
        else if ((variable = v_table_search(v_table, node->identifier)))
        {
            
        }
    }

    computation_resolve(computation->rhs, wc_identifier, v_table);
}