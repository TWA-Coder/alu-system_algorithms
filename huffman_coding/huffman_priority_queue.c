#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * struct_cmp - Custom comparator for huffman coding
 *
 * @p1: First pointer (binary_tree_node_t *)
 * @p2: Second pointer (binary_tree_node_t *)
 *
 * Return: Difference between the frequencies
 */
int struct_cmp(void *p1, void *p2)
{
	binary_tree_node_t *n1, *n2;
	symbol_t *s1, *s2;

	n1 = (binary_tree_node_t *)p1;
	n2 = (binary_tree_node_t *)p2;

	s1 = (symbol_t *)n1->data;
	s2 = (symbol_t *)n2->data;

	return (s1->freq - s2->freq);
}

/**
 * huffman_priority_queue - Creates a priority queue for the Huffman coding
 *
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of the arrays
 *
 * Return: Pointer to the created min heap, or NULL if it fails
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *symbol;
	binary_tree_node_t *node, *inserted;
	size_t i;

	if (data == NULL || freq == NULL || size == 0)
		return (NULL);

	heap = heap_create(struct_cmp);
	if (heap == NULL)
		return (NULL);

	for (i = 0; i < size; ++i)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (symbol == NULL)
		{
			heap_delete(heap, NULL); /* Need proper cleanup ideally */
			return (NULL);
		}

		node = binary_tree_node(NULL, symbol);
		if (node == NULL)
		{
			free(symbol);
			heap_delete(heap, NULL);
			return (NULL);
		}

		inserted = heap_insert(heap, node);
		if (inserted == NULL)
		{
			free(symbol);
			free(node);
			heap_delete(heap, NULL);
			return (NULL);
		}
	}

	return (heap);
}
