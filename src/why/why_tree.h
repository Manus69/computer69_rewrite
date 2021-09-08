#ifndef WHY_TREE_H
#define WHY_TREE_H

#include "why_tree_interface.h"

struct Tree
{
    void *node;
    int_signed (*compare)();

    Tree *left;
    Tree *right;
};


#endif