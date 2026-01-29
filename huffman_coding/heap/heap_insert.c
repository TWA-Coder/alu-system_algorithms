#include <stdlib.h>
#include "heap.h"

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 *
 * @heap: Pointer to the heap in which the node has to be inserted
 * @data: Pointer containing the data to store in the new node
 *
 * Return: Pointer to the created node, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
    size_t temp_size, mask;
    binary_tree_node_t *parent, *new_node;
    void *temp_data;

    if (heap == NULL || data == NULL)
        return (NULL);
    if (heap->root == NULL)
    {
        new_node = binary_tree_node(NULL, data);
        if (new_node == NULL)
            return (NULL);
        heap->root = new_node;
        heap->size++;
        return (new_node);
    }
    temp_size = (heap->size + 1) >> 1;
    mask = (size_t)1 << ((sizeof(size_t) * 8) - 1);
    while (!(temp_size & mask))
        mask >>= 1;
    mask >>= 1;
    parent = heap->root;
    while (mask > 0)
    {
        if (temp_size & mask)
            parent = parent->right;
        else
            parent = parent->left;
        mask >>= 1;
    }
    new_node = binary_tree_node(parent, data);
    if (new_node == NULL)
        return (NULL);
    if ((heap->size + 1) & 1)
        parent->right = new_node;
    else
        parent->left = new_node;
    heap->size++;
    while (new_node->parent && heap->data_cmp(new_node->data, new_node->parent->data) < 0)
    {
        temp_data = new_node->data;
        new_node->data = new_node->parent->data;
        new_node->parent->data = temp_data;
        new_node = new_node->parent;
    }
    return (new_node);
}
