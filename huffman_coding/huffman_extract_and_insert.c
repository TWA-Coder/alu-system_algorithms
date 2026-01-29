#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts the two nodes of the priority queue
 * and insert a new one
 *
 * @priority_queue: Pointer to the priority queue to extract from
 *
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
    binary_tree_node_t *node1, *node2, *new_node;
    symbol_t *new_symbol, *s1, *s2;
    size_t sum_freq;

    if (!priority_queue || priority_queue->size < 2)
        return (0);

    node1 = (binary_tree_node_t *)heap_extract(priority_queue);
    if (!node1)
        return (0);

    node2 = (binary_tree_node_t *)heap_extract(priority_queue);
    if (!node2)
        return (0);

    s1 = (symbol_t *)node1->data;
    s2 = (symbol_t *)node2->data;
    sum_freq = s1->freq + s2->freq;

    new_symbol = symbol_create(-1, sum_freq);
    if (!new_symbol)
        return (0);

    new_node = binary_tree_node(NULL, new_symbol);
    if (!new_node)
    {
        free(new_symbol);
        return (0);
    }

    new_node->left = node1;
    new_node->right = node2;
    node1->parent = new_node;
    node2->parent = new_node;

    if (!heap_insert(priority_queue, new_node))
    {
        free(new_symbol);
        free(new_node);
        return (0);
    }

    return (1);
}
