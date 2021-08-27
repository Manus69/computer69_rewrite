#include "computation.h"
#include "frontend_declarations.h"
#include "node.h"

Computation *computation_new(Node *node, boolean copy)
{
    Computation *computation;

    computation = allocate(sizeof(Computation));
    computation->node = copy ? node_copy(node) : node;
    computation->lhs = NULL;
    computation->rhs = NULL;

    return computation;
}

void computation_delete(Computation **computation)
{
    Computation *cmp;

    if (!computation || !*computation)
        return ;

    cmp = *computation;
    computation_delete(&cmp->lhs);
    computation_delete(&cmp->rhs);
    node_delete(&cmp->node);
    
    free(*computation);
    *computation = NULL;
}

Computation *computation_get_lhs(const Computation *computation)
{
    return computation->lhs;
}

Computation *computation_get_rhs(const Computation *computation)
{
    return computation->rhs;
}

Node *computation_get_node(const Computation *computation)
{
    return computation->node;
}

Computation *computation_insert_root(Computation *root, Computation *new_root)
{
    new_root->lhs = root;

    return new_root;
}

void computation_traverse(Computation *computation, void (*function)())
{
    if (!computation)
        return ;
    
    computation_traverse(computation->lhs, function);
    function(computation->node);
    computation_traverse(computation->rhs, function);
}

Computation *computation_copy(const Computation *computation)
{
    Computation *copy;

    if (!computation)
        return NULL;

    copy = computation_new(computation->node, TRUE);
    copy->lhs = computation_copy(computation->lhs);
    copy->rhs = computation_copy(computation->rhs);

    return copy;
}

void *computation_copy_wrapper(Computation *computation)
{
    return computation_copy(computation);
}