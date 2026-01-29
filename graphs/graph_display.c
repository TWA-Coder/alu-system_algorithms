#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

/**
 * graph_display - Prints the content of a graph (vertices only for now)
 *
 * @graph: Pointer to the graph to display
 */
void graph_display(const graph_t *graph)
{
	vertex_t *v;

	edge_t *e;

	if (!graph)
		return;

	printf("Number of vertices: %lu\n", graph->nb_vertices);
	v = graph->vertices;
	while (v)
	{
		printf("[%lu] %s", v->index, v->content);
		e = v->edges;
		while (e)
		{
			printf(" ->%lu", e->dest->index);
			e = e->next;
		}
		printf("\n");
		v = v->next;
	}
}
