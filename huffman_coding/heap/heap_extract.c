#include <stdlib.h>
#include "heap.h"

/**
 * tree_height - logical height of the heap for navigation
 * @size: number of nodes
 * Return: height
 */
static size_t tree_height(size_t size)
{
    size_t height = 0;
    size_t temp = size;

    while (temp > 0)
    {
        temp >>= 1;
        height++;
    }
    return (height);
}

/**
 * get_last_node - finds the last node in the heap
 * @heap: pointer to the heap
 * Return: pointer to the last node
 */
static binary_tree_node_t *get_last_node(heap_t *heap)
{
    size_t height, mask;
    binary_tree_node_t *node;

    if (!heap || !heap->root || heap->size == 0)
        return (NULL);

    if (heap->size == 1)
        return (heap->root);

    height = tree_height(heap->size);
    /* mask for the bit after the MSB of size */
    mask = 1 << (height - 2); 
    
    node = heap->root;
    while (mask > 0)
    {
        if (heap->size & mask)
            node = node->right;
        else
            node = node->left;
        mask >>= 1;
    }
    return (node);
}

/**
 * heapify_down - restores min heap property from root
 * @heap: pointer to the heap
 */
static void heapify_down(heap_t *heap)
{
    binary_tree_node_t *node, *child;
    void *temp;

    node = heap->root;
    while (node->left)
    {
        child = node->left;
        if (node->right && heap->data_cmp(node->right->data, child->data) < 0)
            child = node->right;
        
        if (heap->data_cmp(node->data, child->data) <= 0)
            break;
            
        temp = node->data;
        node->data = child->data;
        child->data = temp;
        
        node = child;
    }
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 *
 * @heap: Pointer to the heap from which to extract the value
 *
 * Return: Pointer to the data that was stored in the root node
 */
void *heap_extract(heap_t *heap)
{
    void *data;
    binary_tree_node_t *last, *root_node;

    if (!heap || !heap->root)
        return (NULL);

    root_node = heap->root;
    data = root_node->data;
    
    if (heap->size == 1)
    {
        free(root_node);
        heap->root = NULL;
        heap->size = 0;
        return (data);
    }

    last = get_last_node(heap);
    
    /* Detach last node */
    if (last->parent->left == last)
        last->parent->left = NULL;
    else
        last->parent->right = NULL;

    /* Replace root with last */
    heap->root = last;
    last->parent = NULL;
    last->left = root_node->left;
    last->right = root_node->right;
    
    if (last->left)
        last->left->parent = last;
    if (last->right)
        last->right->parent = last;

    free(root_node);
    heap->size--;
    
    heapify_down(heap);
    
    return (data);
}
