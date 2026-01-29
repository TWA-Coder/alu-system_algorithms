#include <stdlib.h>
#include "graphs.h"

/**
 * dfs_recursive - Helper function for Depth First Traversal
 *
 * @v: Current vertex being visited
 * @visited: Array of visited statuses
 * @action: Pointer to the function to be called for each visited vertex
 * @depth: Current depth
 * @max_depth: Pointer to the max depth variable
 */
static void dfs_recursive(const vertex_t *v, int *visited,
			  void (*action)(const vertex_t *v, size_t depth),
			  size_t depth, size_t *max_depth)
{
	edge_t *edge;

	visited[v->index] = 1;
	action(v, depth);

	if (depth > *max_depth)
		*max_depth = depth;

	edge = v->edges;
	while (edge)
	{
		if (!visited[edge->dest->index])
		{
			dfs_recursive(edge->dest, visited, action,
				      depth + 1, max_depth);
		}
		edge = edge->next;
	}
}

/**
 * depth_first_traverse - Goes through a graph using the depth-first algorithm
 *
 * @graph: Pointer to the graph to traverse
 * @action: Pointer to the function to be called for each visited vertex
 *
 * Return: The biggest vertex depth, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t max_depth = 0;

	if (!graph || !graph->vertices || !action)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(int));
	if (!visited)
		return (0);

	dfs_recursive(graph->vertices, visited, action, 0, &max_depth);

	free(visited);
	return (max_depth);
}
