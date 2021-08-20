#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "why_print.h"
#include "terminals.h"
#include "node.h"
#include "operator.h"

#include <stdio.h>
#include <assert.h>

void print_number(const Number *number)
{
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

    index = operator_get_type(operator);

    printf("%c", TERMINALS[index]);
}

void print_node(const Node *node)
{
    NODE_TYPE type;

    type = node_get_type(node);
    if (type == NT_NUMBER)
        print_number(node->number);
    else if (type == NT_OPERATOR)
        print_operator(node->operator);
    else if (type == NT_IDENTIFIER)
        print_string(node->identifier);
    else if (type == NT_WILDCARD)
        print_string(node->identifier);
}

void print_computation(const Computation *computation)
{
    if (!computation)
        return ;
    
    print_computation(computation_get_lhs(computation));
    print_node(computation_get_node(computation));
    print_computation(computation_get_rhs(computation));
}
