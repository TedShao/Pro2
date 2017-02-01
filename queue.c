#include <stdint.h>
#include <stdlib.h>

#include "queue.h"

struct node{
	
}
struct queue {
	/* TODO Phase 1 */
	/*
	 * queue_create - Allocate an empty queue
	 *
	 * Return: Pointer to empty queue, or NULL in case of failure
	 */
	int data;
	int* next = NULL;
};

queue_t queue_create(void)
{
	/* TODO Phase 1 */
	/*
	 * queue_destroy - Deallocate a queue
	 * @queue: Queue to deallocate
	 *
	 * Return: 0 if @queue was successfully destroyed, or -1 in case of failure
	 */
	queue newqueue;
	newqueue.data = 0;
	*newqueue.next = NULL;
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
	/*
	 * queue_enqueue - Enqueue data
	 * @queue: Queue in which to enqueue data
	 * @data: Data to enqueue
	 *
	 * Return: 0 if @data was successfully enqueued in @queue, or -1 in case of
	 * failure
	 */
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	/*
	 * queue_dequeue - Dequeue data
	 * @queue: Queue in which to dequeue data
	 * @data: Address of data pointer where data is received
	 *
	 * Return: 0 if @data was set with oldest item in @queue, or -1 in case of
	 * failure
	 */
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
	/*
	 * queue_delete - Delete data
	 * @queue: Queue in which to delete data
	 * @data: Data to delete
	 *
	 * Return: 0 if @data was found and deleted from @queue, or -1 in case of
	 * failure
	 */
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	/*
	 * queue_func_t - Queue callback function type
	 * @data: Data item
	 */
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
	/*
	 * queue_iterate - Iterate on all items of a queue
	 * @queue: Queue to iterate on
	 * @func: Function to call on each queue item
	 *
	 * Return: 0 if @queue was iterated successfully, or -1 in case of failure
	 *
	 * Note that this function should be resistant to data items being deleted
	 * as part of the iteration (ie in @func).
	 */
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	/*
	 * queue_length - Queue length
	 * @queue: Queue to get the length of
	 *
	 * Return: Length of @queue, or -1 in case of failure
	 */
}

