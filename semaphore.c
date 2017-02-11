#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define _UTHREAD_PRIVATE
#include "preempt.h"
#include "queue.h"
#include "semaphore.h"
#include "uthread.h"

//Source: http://stackoverflow.com/questions/1152246/mutual-exclusion-using-testandset-instruction
//Source: 

struct semaphore {
	/* TODO Phase 3 */
	int value;
	int lock;
	queue_t waiting;
};

sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
	/*
	 * sem_create - Allocate and initialize a semaphore
	 * @count: Semaphore count
	 *
	 * Return: Pointer to initialized semaphore, or NULL in case of failure
 	*/

 	struct semaphore* new_sema = malloc(sizeof(struct semaphore));

 	/*return NULL if we can't create the semaphore*/
 	if (new_sema == NULL) { 
 		return NULL;
 	}
 	else {
 		/*Initialize the variables in semaphore*/ 
	 	new_sema->value = count;
	 	new_sema->lock = 0;
	 	waiting = queue_create();
	 	return new_sema;
	}
 	
}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */
	/*
	 * sem_destroy - Deallocate a semaphore
	 * @sem: Semaphore to deallocate
	 *
	 * Return: 0 is @sem was successfully destroyed, or -1 in case of failure
	 */

	free(sem->waiting);
	free(sem);

	return 0;
}

int sem_down(sem_t sem)
{
	/* TODO Phase 3 */
	/*
	 * sem_down - Take a semaphore
	 * @sem: Semaphore to take
	 *
	 * Return: 0 in case of success, or -1 in case of failure
	 *
	 * Note that taking a unavailable semaphore will cause the caller thread to be
	 * blocked until the semaphore becomes available.
	 */

	while (test_and_set(&sem->lock) == 1); //wait until the lock is released

	/*if the thread can't get the semaphore, add to waiting queue*/
	if(sem->value < 1) { 
		struct uthread_t* nextThread = malloc(typeof(struct uthread_t));
		nextThread = uthread_current();
		queue_enqueue(sem->waiting,nextThread);
		uthread_block() //FIXME: Implement this function in uthread.c
		//queue_enqueue(waiting)
	}
	else { 
		/*we can use the semaphore*/
		sem->value--; //decrease count of available slots
		//how do we let the thread use the semaphore?
	}
	sem->lock = 1; //lock the lock again

	return 0;
}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */
	/*
	 * sem_up - Release a semaphore
	 * @sem: Semaphore to release
	 *
	 * Return: 0 in case of success, or -1 in case of failure
	 */

	while (test_and_set(&sem->lock) == 1); //wait until the lock is released

	sem->lock = 1;
	sem->value++; //increase count of available slots
	if (sem->value > 0) { //if semaphore is available
		if (queue_length(sem->waiting)>0) { //if there are any thread waiting to use semaphore
			/*Let the next waiting thread use semaphore*/
			struct uthread_t* nextThread = malloc(typeof(struct uthread_t));
			queue_dequeue(sem->waiting, nextThread);
			uthread_unblock(); //FIXME: Implement this function in uthread.c
			//how do I run the next thread?
			//uthread_ctx_switch()?
		}
		
	}
	sem->lock = 0; //lock the lock again
}

