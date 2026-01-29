#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - Adds a vertex to an existing graph
 *
 * @graph: Pointer to the graph to add the vertex to
 * @str: String to store in the new vertex
 *
 * Return: Pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex, *last_vertex;

	if (graph == NULL || str == NULL)
		return (NULL);

	/* Check for duplicate */
	last_vertex = graph->vertices;
	while (last_vertex)
	{
		if (strcmp(last_vertex->content, str) == 0)
			return (NULL);
		if (last_vertex->next == NULL)
			break;
		last_vertex = last_vertex->next;
	}

	new_vertex = malloc(sizeof(vertex_t));
	if (new_vertex == NULL)
		return (NULL);

	new_vertex->content = strdup(str);
	if (new_vertex->content == NULL)
	{
		free(new_vertex);
		return (NULL);
	}

	new_vertex->index = graph->nb_vertices;
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (graph->vertices == NULL)
		graph->vertices = new_vertex;
	else
		last_vertex->next = new_vertex;

	graph->nb_vertices++;

	return (new_vertex);
}
