#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "queues.h"
#include "../graphs/graphs.h"
#include <limits.h>

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target);
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target);

#endif /* PATHFINDING_H */
