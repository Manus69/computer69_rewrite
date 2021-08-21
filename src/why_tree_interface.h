#ifndef WHY_TREE_INTERFACE_H
#define WHY_TREE_INTERFACE_H

#include "why_definitions.h"

typedef struct Tree Tree;

Tree    *tree_new(const void *node, int_signed (*compare)());
Tree    *tree_get_left(Tree *tree);
Tree    *tree_get_right(Tree *tree);
void    tree_delete(Tree **tree, void (*delete_)());
void    *tree_get_node(Tree *tree);
void    tree_map_flr(Tree *tree, void (*function)());
void    tree_map_lfr(Tree *tree, void (*function)());
void    *tree_search(const Tree *tree, const void *item);
void    *tree_search_function(const Tree *tree, const void *item, int_signed (*function)());
boolean tree_insert(Tree *tree, void *item);

#endif