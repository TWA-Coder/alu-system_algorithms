#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_tree - Builds the Huffman tree
 *
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of the arrays
 *
 * Return: Pointer to the root node of the Huffman tree, or NULL if it fails
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
    heap_t *priority_queue;
    binary_tree_node_t *root;

    if (data == NULL || freq == NULL || size == 0)
        return (NULL);

    priority_queue = huffman_priority_queue(data, freq, size);
    if (priority_queue == NULL)
        return (NULL);

    while (priority_queue->size > 1)
    {
        if (huffman_extract_and_insert(priority_queue) == 0)
        {
            /* This might leak partial trees if delete doesn't handle nested deeply */
             heap_delete(priority_queue, NULL);
             return (NULL);
        }
    }

    root = (binary_tree_node_t *)heap_extract(priority_queue);
    heap_delete(priority_queue, NULL);
    return (root);
}
