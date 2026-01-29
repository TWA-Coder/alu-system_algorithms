#include <stdlib.h>
#include "heap.h"

/**
 * free_node - recursive helper to free binary tree nodes
 * @node: pointer to the node to free
 * @free_data: pointer to the function to free content of the node
 */
static void free_node(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (node)
	{
		free_node(node->left, free_data);
		free_node(node->right, free_data);
		if (free_data)
			free_data(node->data);
		free(node);
	}
}

/**
 * heap_delete - Deallocates a heap
 *
 * @heap: Pointer to the heap to delete
 * @free_data: Pointer to a function that will be used to free the content
 * of a node
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap)
	{
		free_node(heap->root, free_data);
		free(heap);
	}
}
