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
    char *format;

    if (!operator)
        return ;

    index = operator_get_type(operator);
    if (index == OT_CARET || index == OT_EXCLAM)
        format = "%c";
    else
        format = " %c ";

    printf(format, TERMINALS[index]);
}

void print_node(const Node *node, const char *wc_symbol)
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
        print_cstring(wc_symbol ? wc_symbol : WC_SYMBOL);
    else if (type == NT_FUNCTION)
        print_cstring(node->identifier);
    else if (type == NT_BUILTIN_FUNCTION)
        print_cstring(FUNCTION_STRINGS[node->bf_type]);
    else if (type == NT_MATRIX)
        print_matrix_repr(node->matrix, wc_symbol);
    else assert(0);
}

void print_variable(const Variable *variable)
{
    Entity *value;

    if (!variable)
        return ;
    
    value = variable_get_value(variable);
    print_entity(value, NULL);
}

void print_variableN(const Variable *variable)
{
    print_variable(variable);
    printf("\n");
}

void print_variableNI(const Variable *variable)
{
    Entity *value;

    if (!variable)
        return ;
    
    value = variable_get_value(variable);
    print_entity(value, variable->initial_parameter);
    printf("\n");
}

void print_variable_verbose(const Variable *variable, const char *wc_symbol)
{
    Entity *value;

    if (!variable)
        return ;
    
    value = variable_get_value(variable);
    if (!variable->name)
    {
        print_entity(value, wc_symbol); //

        return ;
    }

    print_cstring(variable->name);
    if (variable_is_parametrized(variable))
        printf("(%s)", WC_SYMBOL);

    printf(" = ");
    print_entity(value, wc_symbol);
}

void print_v_table(const VariableTable *v_table)
{
    if (!v_table)
        return ;

    print_v_table(v_table->left);
    print_variable_verbose(v_table->node, NULL);
    printf("\n");
    print_v_table(v_table->right);
}

void print_matrix_row(const MatrixRepr *matrix, int_signed j, const char *wc_symbol)
{
    int_signed k;
    Entity *item;

    if (!matrix)
        return ;

    printf("[ ");
    item = matrix_repr_at(matrix, j, 0);
    print_entity(item, wc_symbol);
    k = 1;

    while (k < matrix_repr_n_cols(matrix))
    {
        printf("%s", " , ");
        item = matrix_repr_at(matrix, j, k);
        print_entity(item, wc_symbol);

        k ++;
    }
    printf(" ]");
}

void print_matrix_repr(const MatrixRepr *matrix, const char *wc_symbol)
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
    print_matrix_row(matrix, 0, wc_symbol);

    n = 1;
    while (n < n_rows)
    {
        printf("\n");
        print_matrix_row(matrix, n, wc_symbol);
        n ++;
    }
    // printf("]");
}

static void *functions[] = {print_number, print_matrix_repr, print_computation, 0};

void print_entity(const Entity *entity, const char *wc_symbol)
{
    void (*print_function)();

    if (!entity)
        return ;
    
    print_function = functions[entity_get_type(entity)];
    print_function(entity->number, wc_symbol);
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