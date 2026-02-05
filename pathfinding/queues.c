#include <stdlib.h>
#include "queues.h"

/**
 * queue_create - Creates a new queue
 *
 * Return: Pointer to the new queue, or NULL on failure
 */
queue_t *queue_create(void)
{
	queue_t *queue = malloc(sizeof(queue_t));

	if (queue)
	{
		queue->front = NULL;
		queue->back = NULL;
	}
	return (queue);
}

/**
 * queue_push - Pushes an element to the back of the queue
 * @queue: The queue
 * @content: The element content
 *
 * Return: 1 on success, 0 on failure
 */
int queue_push(queue_t *queue, void *content)
{
	queue_node_t *node;

	if (!queue)
		return (0);

	node = malloc(sizeof(queue_node_t));
	if (!node)
		return (0);

	node->content = content;
	node->next = NULL;

	if (queue->back)
		queue->back->next = node;
	queue->back = node;

	if (!queue->front)
		queue->front = node;

	return (1);
}

/**
 * dequeue - Removes and returns the front element of the queue
 * @queue: The queue
 *
 * Return: Pointer to the content, or NULL if empty/failure
 */
void *dequeue(queue_t *queue)
{
	queue_node_t *node;
	void *content;

	if (!queue || !queue->front)
		return (NULL);

	node = queue->front;
	content = node->content;

	queue->front = node->next;
	if (!queue->front)
		queue->back = NULL;

	free(node);
	return (content);
}

/**
 * queue_delete - Deletes the queue
 * @queue: The queue
 */
void queue_delete(queue_t *queue)
{
	queue_node_t *node, *next;

	if (!queue)
		return;

	node = queue->front;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	free(queue);
}
