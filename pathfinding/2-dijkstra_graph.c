#include "pathfinding.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/**
 * get_min_vertex - Finds the unvisited vertex with the smallest distance
 * @dists: Array of distances
 * @visited: Array of visited status
 * @nb_vertices: Number of vertices
 *
 * Return: Index of the vertex, or -1 if none found
 */
static int get_min_vertex(int *dists, int *visited, size_t nb_vertices)
{
	int min_dist = INT_MAX;
	int min_idx = -1;
	size_t i;

	for (i = 0; i < nb_vertices; i++)
	{
		if (!visited[i] && dists[i] < min_dist)
		{
			min_dist = dists[i];
			min_idx = i;
		}
	}
	return (min_idx);
}

/**
 * dijkstra_graph - Finds the shortest path from start to target in a graph
 * @graph: The graph
 * @start: Starting vertex
 * @target: Target vertex
 *
 * Return: Queue containing the path (strings), or NULL on failure
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
	int *dists;
	int *visited;
	vertex_t **parents;
	size_t i;
	int u_idx;
	vertex_t *u, *curr;
	edge_t *edge;
	queue_t *path = NULL;
	char *city_name;
	void *temp_stack[2048];
	int stack_idx = 0;

	if (!graph || !start || !target)
		return (NULL);

	dists = malloc(graph->nb_vertices * sizeof(int));
	visited = calloc(graph->nb_vertices, sizeof(int));
	parents = calloc(graph->nb_vertices, sizeof(vertex_t *));

	if (!dists || !visited || !parents)
	{
		free(dists);
		free(visited);
		free(parents);
		return (NULL);
	}

	for (i = 0; i < graph->nb_vertices; i++)
		dists[i] = INT_MAX;

	dists[start->index] = 0;

	while ((u_idx = get_min_vertex(dists, visited, graph->nb_vertices)) != -1)
	{
		visited[u_idx] = 1;
		
		/* Find the vertex pointer for u_idx (not efficient but structure forces it unless we map) */
		/* Actually graphs usually store vertices in a list, not indexed array directly accessibly?
		   Wait, graph_t has `vertex_t *vertices` which is a linked list.
		   We need to traverse to find the vertex ptr? Or assume `nb_vertices` is consistent.
		   The `vertex_t` struct has `index`.
		   We can only access u if we traverse.
		   Wait, for printing and edges we need `vertex_t *u`.
		   Optimization: Can we map index -> vertex_t*?
		   Since we cannot modify structs, we might need a temporary map array.
		 */
		u = graph->vertices;
		while (u && u->index != (size_t)u_idx)
			u = u->next;

		if (!u) break; /* Should not happen */

		printf("Checking %s, distance from %s is %d\n",
		       u->content, start->content, dists[u_idx]);

		if (u == target)
			break; /* Found target */

		for (edge = u->edges; edge; edge = edge->next)
		{
			int v_idx = edge->dest->index;
			int weight = edge->weight;

			if (!visited[v_idx] && dists[u_idx] != INT_MAX &&
			    dists[u_idx] + weight < dists[v_idx])
			{
				dists[v_idx] = dists[u_idx] + weight;
				parents[v_idx] = u;
			}
		}
	}

	/* Reconstruct path if target reachable */
	if (dists[target->index] != INT_MAX)
	{
		path = queue_create();
		if (path)
		{
			curr = (vertex_t *)target;
			while (curr)
			{
				city_name = strdup(curr->content);
				temp_stack[stack_idx++] = city_name;
				curr = parents[curr->index];
			}

			/* Push to queue in correct order (Start -> ... -> Target) */
			while (stack_idx > 0)
			{
				queue_push(path, temp_stack[--stack_idx]);
			}
		}
	}

	free(dists);
	free(visited);
	free(parents);

	return (path);
}
