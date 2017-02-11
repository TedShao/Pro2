#include <stdint.h>
#include <stdlib.h>
#include "queue.h"
#include <stdio.h>
#include <unistd.h>
//we are using a linked list to construct our queue
//each are connected with a Node

//Source: https://gist.github.com/mycodeschool/7510222
struct node {
	void* ndata;
	struct node* next; 
};

struct queue {
	/* TODO Phase 1 */
	
	//int data;
    //struct node* next = NULL;
	struct node* start;
	struct node* end;
	//queue_t first = NULL, last = NULL;
};


queue_t queue_create(void)
{
	/* TODO Phase 1 */
	/*
	 * queue_create - Allocate an empty queue
	 *
	 * Return: Pointer to empty queue, or NULL in case of failure
	 */

	//struct queue* myqueue = (struct queue*)malloc(sizeof(struct queue));
	queue_t myqueue = malloc(sizeof(struct queue));

	// Resource: https://github.com/twcamper/c-programming/blob/master/lib/bounded-queue.c

    //myqueue->data = 0;
    //myqueue->first = this;

    //*****hahahahahhahahahahaahahahahahaahahahaha******//
 	// myqueue.start = (struct Node*)malloc(sizeof(struct Node));
	// myqueue.end = (struct Node*)malloc(sizeof(struct Node));

	return myqueue;
}

int queue_length(queue_t queue);

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
	/*
	 * queue_destroy - Deallocate a queue
	 * @queue: Queue to deallocate
	 *
	 * Return: 0 if @queue was successfully destroyed, or -1 in case of failure
	 */
	if(queue == NULL)
		return -1;
	free(queue);

	if(queue_length(queue)==0)
		return 0;
	else
		return -1;
}

int queue_enqueue(queue_t queue, void *data)
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

	//Source: https://gist.github.com/mycodeschool/7510222
	/*struct *Node new_element = (struct Node*)malloc(sizeof(struct Node));
	queue.last = new_element;
	queue.last = new_element;*/
	
	if(queue == NULL || data == NULL)
		return -1;

	struct node* newEle = (struct node*)malloc(sizeof(struct node));
	newEle->ndata = data;
	newEle->next = NULL;
	if (queue->start == NULL) {
		queue->start = newEle;
		queue->end = newEle;
		return 0;
	}
	else {
		queue->end->next = newEle;
		queue->end = newEle;
		return 0;
	}
}

int queue_dequeue(queue_t queue, void **data)
{
	
/*
 * queue_dequeue - Dequeue data
 * @queue: Queue in which to dequeue data
 * @data: Address of data pointer where data is received
 *
 * Return: 0 if @data was set with oldest item in @queue, or -1 in case of
 * failure
 */
	/*hardik's code
	queue->next = NULL;
    return queue->data;
    */

    if (queue->start == NULL) { //the queue is empty
    	printf("Error: Empty queue!\n");
    	return -1;
    }
    else { //the queue has >= 1 element
    	*data = queue->start->ndata; //ndata holds address of thread

    	queue->start = queue->start->next;
    	return 0;

    } //Jonathan's
/*
    struct node* rip = queue->start;
    if (rip == NULL) { //the queue is empty
    	printf("Error: Empty queue!\n");
    	return -1;
    }
    else { //the queue has >= 1 element
    	queue->start = rip->next;
    	typeof(rip->ndata) *temp = rip->ndata;
		*data = *temp;
    	//free(rip);
		printf("\ndata : %d\n", *data);
		//printf("\ntemp : %d\n", temp);
    	return 0;
    }*/
}

int queue_delete(queue_t queue, void *data)
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

	struct node* rip = queue->start;
	int returnVal = -1;

	if(rip == NULL){ // Empty queue
		printf("Error: Empty queue!\n");
		return -1;
	}

	else{

		while(rip->next != NULL) {
			if (rip->next->ndata == data) {
				rip->next = rip->next->next;
				free(rip->next->ndata);
				free(rip->next);
				returnVal = 0;
				break;
			}
		}
		return returnVal;
	}	

}

//typedef void (*queue_func_t)(void *data);
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
	struct node* temp = queue->start;
	while (temp != NULL) {
		//apply func to each data

		//func(temp->data);

		//Source: http://msl.cs.uiuc.edu/~lavalle/cs326a/projects/bgoc/code/queue.C [http://msl.cs.uiuc.edu/~lavalle/cs326a/projects/bgoc/code/queue.c_green] 
		(*func)(temp->ndata);
		temp = temp->next;
	}

	// void
	// Queue::Apply(void (*func)(PGNode *)) const
	// { 
	//     QueueElement *ptr;

	//     for (ptr = first; ptr != NULL; ptr = ptr->next) {
	//         (*func)(ptr->item);
	//     }
	// }

	return 0;
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
	int queue_len = 0;
	struct node* temp = queue->start;
	while (temp!=NULL) {
		temp = temp->next;
		queue_len++;
	}
	return queue_len;
}