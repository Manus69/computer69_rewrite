#include "why_tree.h"
#include "why_tree_interface.h"
#include "why_memory.h"

Tree *tree_new(void *node, int_signed (*compare)())
{
    Tree *tree;

    tree = allocate(sizeof(Tree));
    tree->node = node;
    tree->compare = compare;
    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

void tree_delete(Tree **tree, void (*delete_)())
{
    Tree *left;
    Tree *right;

    if (!tree || !*tree)
        return ;

    left = (*tree)->left;
    right = (*tree)->right;
    delete_(&(*tree)->node);
    free(*tree);
    *tree = NULL;

    tree_delete(&left, delete_);
    tree_delete(&right, delete_);
}

void *tree_get_node(Tree *tree)
{
    if (!tree)
        return NULL;
    
    return tree->node;
}

void tree_map_flr(Tree *tree, void (*function)())
{
    if (!tree)
        return ;
    
    function(tree->node);
    tree_map_flr(tree->left, function);
    tree_map_flr(tree->right, function);
}

void tree_map_lfr(Tree *tree, void (*function)())
{
    if (!tree)
        return ;
    
    tree_map_lfr(tree->left, function);
    function(tree->node);
    tree_map_lfr(tree->right, function);
}

void *tree_search(Tree *tree, void *item)
{
    if (!tree)
        return NULL;
    
    return tree_search_function(tree, item, tree->compare);
}

void *tree_search_function(Tree *tree, void *item, int_signed (*function)())
{
    int_signed result;

    if (!tree)
        return NULL;

    result = function(tree->node, item);
    if (result == 0)
        return tree->node;
    else if (result > 0)
        return tree_search(tree->right, item);
    else
        return tree_search(tree->left, item);
}

boolean tree_insert(Tree *tree, void *item)
{
    int_signed result;

    if (!tree)
        return FALSE;

    result = tree->compare(tree->node, item);
    if (result == 0)
        return FALSE;
    else if (result > 0)
    {
        if (tree->right)
            return tree_insert(tree->right, item);
        
        tree->right = tree_new(item, tree->compare);
    }
    else
    {
        if (tree->left)
            return tree_insert(tree, item);
        
        tree->left = tree_new(item, tree->compare);
    }

    return FALSE;
}

Tree *tree_get_left(Tree *tree)
{
    return tree->left;
}

Tree *tree_get_right(Tree *tree)
{
    return tree->right;
}