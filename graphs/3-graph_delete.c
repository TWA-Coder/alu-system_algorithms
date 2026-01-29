#include <stdlib.h>
#include "graphs.h"

/**
 * graph_delete - Deletes a graph completely
 *
 * @graph: Pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
	vertex_t *v, *v_next;
	edge_t *e, *e_next;

	if (graph == NULL)
		return;

	v = graph->vertices;
	while (v)
	{
		v_next = v->next;

		/* Free edges */
		e = v->edges;
		while (e)
		{
			e_next = e->next;
			free(e);
			e = e_next;
		}

		/* Free vertex content */
		free(v->content);

		/* Free vertex */
		free(v);

		v = v_next;
	}

	free(graph);
}
