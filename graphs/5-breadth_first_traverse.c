#include <stdlib.h>
#include "graphs.h"

/**
 * process_bfs - Helper function to process the BFS queue
 *
 * @queue: Queue of vertices
 * @depths: Array of depths
 * @visited: Array of visited flags
 * @action: Action to perform on each vertex
 * @write: Current write index in the queue
 *
 * Return: The maximum depth reached
 */
static size_t process_bfs(vertex_t **queue, size_t *depths, int *visited,
			  void (*action)(const vertex_t *v, size_t depth),
			  size_t write)
{
	size_t read = 0, max_depth = 0;
	vertex_t *v;
	edge_t *edge;

	while (read < write)
	{
		v = queue[read];
		if (depths[read] > max_depth)
			max_depth = depths[read];

		action(v, depths[read]);

		edge = v->edges;
		while (edge)
		{
			if (!visited[edge->dest->index])
			{
				visited[edge->dest->index] = 1;
				queue[write] = edge->dest;
				depths[write] = depths[read] + 1;
				write++;
			}
			edge = edge->next;
		}
		read++;
	}
	return (max_depth);
}

/**
 * breadth_first_traverse - Goes through a graph using the breadth-first algo
 *
 * @graph: Pointer to the graph to traverse
 * @action: Pointer to the function to be called for each visited vertex
 *
 * Return: The biggest vertex depth, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	vertex_t **queue;
	size_t *depths;
	size_t max_depth = 0;

	if (!graph || !graph->vertices || !action)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(int));
	queue = malloc(graph->nb_vertices * sizeof(vertex_t *));
	depths = malloc(graph->nb_vertices * sizeof(size_t));

	if (!visited || !queue || !depths)
	{
		free(visited);
		free(queue);
		free(depths);
		return (0);
	}

	queue[0] = graph->vertices;
	depths[0] = 0;
	visited[graph->vertices->index] = 1;

	max_depth = process_bfs(queue, depths, visited, action, 1);

	free(visited);
	free(queue);
	free(depths);
	return (max_depth);
}
