#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "why_print.h"
#include "terminals.h"
#include "node.h"
#include "operator.h"
#include "computation.h"
#include "variable.h"
#include "number.h"
#include "variable_table.h"
#include "why_tree.h"

#include <stdio.h>
#include <unistd.h>
#include <assert.h>

void print_number(const Number *number)
{
    if (!number)
        return ;
    
    if (number->type == NT_INT)
        print_int(number->n);
    else if (number->type == NT_REAL)
        print_real(number->x);
    else if (number->type == NT_COMPLEX)
        print_complex(number->z);
    else assert(0);
}

void print_operator(const Operator *operator)
{
    int_signed index;

    if (!operator)
        return ;

    index = operator_get_type(operator);

    printf("%c", TERMINALS[index]);
}

void print_node(const Node *node)
{
    NODE_TYPE type;

    if (!node)
        return ;

    type = node_get_type(node);
    if (type == NT_NUMBER)
        print_number(node->number);
    else if (type == NT_OPERATOR)
        print_operator(node->operator);
    else if (type == NT_IDENTIFIER)
        print_string(node->identifier);
    else if (type == NT_WILDCARD)
        print_cstring(WC_SYMBOL);
    else if (type == NT_FUNCTION)
        print_string(node->identifier);
    else if (type == NT_BUILTIN_FUNCTION)
        print_cstring(FUNCTION_STRINGS[node->bf_type]);
}

void _default_print(const Computation *computation)
{
    if (!computation)
        return ;
    
    print_computation(computation_get_lhs(computation));
    print_node(computation_get_node(computation));
    print_computation(computation_get_rhs(computation));
}

static void _pp_print(const Computation *computation)
{
    printf("(");
    fflush(NULL);
    print_computation(computation);
    printf(")");
}

static void _check_branch_and_print(const Computation *root, const Computation *branch)
{
    Node *root_node;
    Node *branch_node;

    root_node = root->node;
    branch_node = branch ? branch->node : NULL;

    if (!branch_node)
        return ;

    if (root_node->type == NT_FUNCTION)
        return _pp_print(branch);

    if (branch_node->type != NT_OPERATOR)
        return print_computation(branch);

    if (root_node->type == NT_OPERATOR && branch_node->type == NT_OPERATOR)
    {
        if (operator_compare_precedence(branch_node->operator, root_node->operator) > 0)
        {
            return _pp_print(branch);
        }
        else
        {
            return print_computation(branch);
        }
    }

    print_computation(branch);
}

static void _print_function(const Computation *computation)
{
    print_node(computation->node);
    _pp_print(computation->lhs);
}

static void _print_u_minus(const Computation *computation)
{
    print_node(computation->node);
    print_computation(computation->lhs);
}

static byte _check_u_minus(const Computation *computation)
{
    Node *node;

    node = computation->node;

    if (node->type == NT_OPERATOR && node->operator->type == OT_MINUS && !computation->rhs)
        return TRUE;

    return FALSE;
}

void print_computation(const Computation *computation)
{
    Node *root_node;

    if (!computation)
        return ;
    
    root_node = computation->node;

    if (root_node->type == NT_FUNCTION || root_node->type == NT_BUILTIN_FUNCTION)
        return _print_function(computation);

    if (_check_u_minus(computation))
        return _print_u_minus(computation);

    _check_branch_and_print(computation, computation->lhs);
    print_node(root_node);
    _check_branch_and_print(computation, computation->rhs);
}

void print_variable(const Variable *variable)
{
    if (!variable)
        return ;
    
    if (!variable->name)
    {
        print_computation(variable->value);

        return ;
    }

    print_string(variable->name);
    if (variable->type == VT_COMPUTATION)
        printf("(%s)", WC_SYMBOL);

    printf(" = ");
    print_computation(variable->value);
}

void print_v_table(const VariableTable *v_table)
{
    if (!v_table)
        return ;

    print_v_table(v_table->left);
    print_variable(v_table->node);
    printf("\n");
    print_v_table(v_table->right);
}