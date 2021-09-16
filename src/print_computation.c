#include "print.h"
#include "frontend_declarations.h"
#include "node.h"
#include "computation.h"
#include "operator.h"

#include <assert.h>

void print_computationL(const Computation *computation, const char *wc_symbol);

static void _pp_print(const Computation *computation, const char *wc_symbol)
{
    printf("(");
    fflush(NULL);
    print_computation(computation, wc_symbol);
    printf(")");
}

static void _check_branch_and_print(const Computation *root, const Computation *branch, const char *wc_symbol, boolean left)
{
    Node *root_node;
    Node *branch_node;

    root_node = root->node;
    branch_node = branch ? branch->node : NULL;

    if (!branch_node)
        return ;

    if (root_node->type == NT_FUNCTION)
        return _pp_print(branch, wc_symbol);

    if (branch_node->type != NT_OPERATOR)
        return print_computation(branch, wc_symbol);

    if (root_node->type == NT_OPERATOR && branch_node->type == NT_OPERATOR)
    {
        if (left && operator_compare_precedence(branch_node->operator, root_node->operator) > 0)
            return _pp_print(branch, wc_symbol);
        else if (!left && operator_compare_precedence(branch_node->operator, root_node->operator) >= 0)
            return _pp_print(branch, wc_symbol);
        else
            return print_computation(branch, wc_symbol);
    }

    print_computationL(branch, wc_symbol);
}

static void _check_left_branch_and_print(const Computation *root, const Computation *branch, const char *wc_symbol)
{
    return _check_branch_and_print(root, branch, wc_symbol, TRUE);
}

static void _check_right_branch_and_print(const Computation *root, const Computation *branch, const char *wc_symbol)
{
    return _check_branch_and_print(root, branch, wc_symbol, FALSE);
}

static void _print_function(const Computation *computation, const char *wc_symbol)
{
    print_node(computation->node, wc_symbol);
    _pp_print(computation->lhs, wc_symbol);
}

static void _print_u_minus(const Computation *computation, const char *wc_symbol)
{
    print_node(computation->node, wc_symbol);
    print_computation(computation->lhs, wc_symbol);
}

static byte _check_u_minus(const Computation *computation)
{
    Node *node;

    node = computation->node;

    if (node->type == NT_OPERATOR && node->operator->type == OT_MINUS && !computation->rhs)
        return TRUE;

    return FALSE;
}

static void _print_computation(const Computation *computation, const char *wc_symbol, void (*m_print)())
{
    Node *root_node;

    if (!computation)
        return ;
    
    root_node = computation->node;

    if (root_node->type == NT_FUNCTION || root_node->type == NT_BUILTIN_FUNCTION)
        return _print_function(computation, wc_symbol);

    if (_check_u_minus(computation))
        return _print_u_minus(computation, wc_symbol);

    if (root_node->type == NT_MATRIX)
        return m_print(root_node->matrix, wc_symbol);

    _check_left_branch_and_print(computation, computation->lhs, wc_symbol);
    print_node(root_node, wc_symbol);
    _check_right_branch_and_print(computation, computation->rhs, wc_symbol);
}

void print_computation(const Computation *computation, const char *wc_symbol)
{
    return _print_computation(computation, wc_symbol, print_matrix_reprL); //
}

void print_computationL(const Computation *computation, const char *wc_symbol)
{
    return _print_computation(computation, wc_symbol, print_matrix_reprL);
}

void print_computationDBG(const Computation *computation, const char *wc_symbol)
{
    print_computation(computation, wc_symbol);
    printf("\n");
}
