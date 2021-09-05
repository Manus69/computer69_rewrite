#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "terminals.h"
#include "node.h"
#include "operator.h"
#include "computation.h"
#include "variable.h"
#include "number.h"
#include "variable_table.h"
#include "why_tree.h"
#include "entity.h"

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
        print_cstring(node->identifier);
    else if (type == NT_WILDCARD)
        print_cstring(WC_SYMBOL);
    else if (type == NT_FUNCTION)
        print_cstring(node->identifier);
    else if (type == NT_BUILTIN_FUNCTION)
        print_cstring(FUNCTION_STRINGS[node->bf_type]);
    else if (type == NT_MATRIX)
        print_matrix_repr(node->matrix);
    else assert(0);
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

    if (root_node->type == NT_MATRIX)
        return print_matrix_repr(root_node->matrix);

    _check_branch_and_print(computation, computation->lhs);
    print_node(root_node);
    _check_branch_and_print(computation, computation->rhs);
}

void print_computationDBG(const Computation *computation)
{
    print_computation(computation);
    printf("\n");
}

void print_variable(const Variable *variable)
{
    Entity *value;

    if (!variable)
        return ;
    
    value = variable_get_value(variable);
    print_entity(value);
}

void print_variable_verbose(const Variable *variable)
{
    Entity *value;

    if (!variable)
        return ;
    
    value = variable_get_value(variable);
    if (!variable->name)
    {
        print_entity(value); //

        return ;
    }

    print_cstring(variable->name);
    if (variable_is_parametrized(variable))
        printf("(%s)", WC_SYMBOL);

    printf(" = ");
    print_entity(value);
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

void print_matrix_row(const MatrixRepr *matrix, int_signed j)
{
    int_signed k;
    Entity *item;

    if (!matrix)
        return ;

    printf("[");
    item = matrix_repr_at(matrix, j, 0);
    print_entity(item);
    k = 1;

    while (k < matrix_repr_n_cols(matrix))
    {
        printf("%s", ",");
        item = matrix_repr_at(matrix, j, k);
        print_entity(item);

        k ++;
    }
    printf("]");
}

void print_matrix_repr(const MatrixRepr *matrix)
{
    int_signed n;
    int_signed n_rows;
    int_signed n_cols;

    if (!matrix)
        return ;

    n_rows = matrix_repr_n_rows(matrix);
    n_cols = matrix_repr_n_cols(matrix);
    if (!n_rows || !n_cols)
        return ;
    
    // printf("[");
    print_matrix_row(matrix, 0);

    n = 1;
    while (n < n_rows)
    {
        printf("\n");
        print_matrix_row(matrix, n);
        n ++;
    }
    // printf("]");
}

static void *functions[] = {print_number, print_matrix_repr, print_computation, 0};

void print_entity(const Entity *entity)
{
    void (*print_function)();

    if (!entity)
        return ;
    
    print_function = functions[entity_get_type(entity)];
    print_function(entity->number);
}

void print_roots(const Vector *roots)
{
    int_signed n;
    Complex *z;

    if (!roots)
        return ;
    
    printf("[");
    z = vector_at(roots, 0);
    print_complex(*z);

    n = 1;
    while (n < vector_size(roots))
    {
        printf(", ");
        z = vector_at(roots, n);
        print_complex(*z);

        n ++;
    }
    printf("]");
}

void print_root_messageAR()
{
    printf("[%s]\n", "Any number is a root");
}

void print_root_messageNR()
{
    printf("[%s]\n", "No roots");
}