#include <stdlib.h>
#include "heap.h"

/**
 * binary_tree_node - Creates a generic Binary Tree node
 *
 * @parent: Pointer to the parent node of the node to be created
 * @data: Data to be stored in the node
 *
 * Return: Pointer to the created node or NULL if it fails
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
    binary_tree_node_t *node;

    node = malloc(sizeof(binary_tree_node_t));
    if (node == NULL)
        return (NULL);

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;

    return (node);
}
