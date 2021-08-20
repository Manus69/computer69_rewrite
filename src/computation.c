#include "computation.h"
#include "frontend_declarations.h"

Computation *computation_new(Node *node)
{
    Computation *cmp;

    cmp = allocate(sizeof(Computation));
    cmp->node = node;
    cmp->lhs = NULL;
    cmp->rhs = NULL;

    return cmp;
}

void computation_delete(Computation **computation)
{
    Computation *cmp;

    if (!computation || !*computation)
        return ;

    cmp = *computation;
    node_delete(&cmp->node);
    computation_delete(&cmp->lhs);
    computation_delete(&cmp->rhs);
    
    free(cmp);
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

Computation *computation_swap_root(Computation *root, Computation *new_root)
{
    Computation *lhs;
    Computation *rhs;

    lhs = root->lhs;
    rhs = root->rhs;
    root->lhs = new_root;
    root->rhs = NULL;
    new_root->lhs = lhs;
    new_root->rhs = rhs;
    SWAP(root->node,new_root->node, Node *);

    return root;
}