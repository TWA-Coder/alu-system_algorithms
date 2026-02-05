#include "pathfinding.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * backtracking_g_recursive - Recursive helper for backtracking on graph
 * @cur: Current vertex
 * @target: Target vertex
 * @queue: Queue to store the path
 * @visited: Visited array (by index)
 *
 * Return: 1 on success, 0 on failure
 */
int backtracking_g_recursive(vertex_t const *cur, vertex_t const *target,
			     queue_t *queue, int *visited)
{
	edge_t *edge;
	char *city_copy;

	if (!cur || !target || visited[cur->index])
		return (0);

	visited[cur->index] = 1;
	printf("Checking %s\n", cur->content);

	if (cur->index == target->index)
	{
		city_copy = strdup(cur->content);
		if (!city_copy)
			return (0); /* Allocation error */
		queue_push(queue, city_copy);
		return (1);
	}

	for (edge = cur->edges; edge; edge = edge->next)
	{
		if (visited[edge->dest->index])
			continue;

		if (backtracking_g_recursive(edge->dest, target, queue, visited))
		{
			city_copy = strdup(cur->content);
			if (!city_copy)
				return (0);
			queue_push(queue, city_copy);
			return (1);
		}
	}

	return (0);
}

/**
 * backtracking_graph - Finds the first path from start to target in a graph
 * @graph: The graph
 * @start: Starting vertex
 * @target: Target vertex
 *
 * Return: Queue containing the path (strings), or NULL on failure
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target)
{
	queue_t *path = NULL;
	queue_t *reversed_path = NULL;
	int *visited;
	char *city;
	void *temp_storage[2048]; /* Should be enough for typical graphs */
	int count = 0;

	if (!graph || !start || !target)
		return (NULL);

	visited = calloc(graph->nb_vertices, sizeof(int));
	if (!visited)
		return (NULL);

	path = queue_create();
	if (!path)
	{
		free(visited);
		return (NULL);
	}

	if (backtracking_g_recursive(start, target, path, visited))
	{
		/* Reverse the queue similar to array backtracking */
		reversed_path = queue_create();
		if (reversed_path)
		{
			while ((city = dequeue(path)))
			{
				temp_storage[count++] = city;
			}
			while (count > 0)
			{
				queue_push(reversed_path, temp_storage[--count]);
			}
			queue_delete(path);
			path = reversed_path;
		}
	}
	else
	{
		queue_delete(path);
		path = NULL;
	}

	free(visited);
	return (path);
}
