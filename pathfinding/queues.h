#ifndef QUEUES_H
#define QUEUES_H

/**
 * struct queue_s - Queue structure
 * @front: Front node
 * @back: Back node
 */
typedef struct queue_s
{
	struct queue_node_s *front;
	struct queue_node_s *back;
} queue_t;

/**
 * struct queue_node_s - Queue node structure
 * @content: Node content
 * @next: Next node
 */
typedef struct queue_node_s
{
	void *content;
	struct queue_node_s *next;
} queue_node_t;

queue_t *queue_create(void);
int queue_push(queue_t *queue, void *content);
void *dequeue(queue_t *queue);
void queue_delete(queue_t *queue);

#endif /* QUEUES_H */
