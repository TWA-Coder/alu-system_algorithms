#include <stdlib.h>
#include "graphs.h"

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
	vertex_t **queue; /* Queue of vertex pointers */
	size_t *depths;   /* Parallel array for depths */
	size_t max_depth = 0;
	size_t read = 0, write = 0;
	vertex_t *v;
	edge_t *edge;

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

	/* Enqueue start node */
	queue[write] = graph->vertices;
	depths[write] = 0;
	visited[graph->vertices->index] = 1;
	write++;

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

	free(visited);
	free(queue);
	free(depths);
	return (max_depth);
}
