#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define _UTHREAD_PRIVATE
#include "context.h"
#include "preempt.h"
#include "queue.h"
#include "uthread.h"
#include <string.h>

#define Thread_Waiting 0
#define Thread_Running 1
#define Thread_Blocked 2
#define Thread_Zombie 3

queue_t running; //only 'one' running thread
queue_t waiting; //can be several running thrd
queue_t blocked; // ..
queue_t zombie; // ..
queue_t threads_queue;

int loop = 0;
int uthread_create(uthread_func_t func, void *arg);
struct uthread_tcb *uthread_current(void);
struct uthread_tcb* idleThread;
uthread_ctx_t* temp;


struct uthread_tcb {
	/* TODO Phase 2 */
	/*
	 * uthread_tcb - Internal representation of threads called TCB (Thread Control Block)
	 */

	/*
    a state (running, ready, blocked, etc.)
    a backup of the CPU registersaving the thread upon descheduling and restoring it later)
    a stack
    */
    int state;
    uthread_ctx_t* context;
	void* tstack;//= uthread_ctx_alloc_stack();
};


void uthread_yield(void)
{
	/* TODO Phase 2 */
	/*
	 * uthread_yield - Yield execution
	 *
	 * This function is to be called from the currently active and running thread in
	 * order to yield for other threads to execute.
	 */

	int queue_int = 1;
	if (queue_length(running)>0) {
		struct uthread_tcb* nextThread; //create a temporary variable to hold thread
		nextThread = malloc(sizeof(struct uthread_tcb));
		nextThread->tstack = uthread_ctx_alloc_stack();
		nextThread->context = uthread_ctx_alloc_stack();
		//queue_int = queue_dequeue(waiting,(void**) &nextThread); //remove the thread from waiting queue
	}
	if (queue_length(waiting)>0) {
		struct uthread_tcb* nextThread; //create a temporary variable to hold thread
		nextThread = malloc(sizeof(struct uthread_tcb));
		nextThread->tstack = uthread_ctx_alloc_stack();
		nextThread->context = uthread_ctx_alloc_stack();
		queue_int = queue_dequeue(waiting,(void**) &nextThread); //remove the thread from waiting queue
		if(!queue_int){
			if(loop == 0){
				nextThread->state = Thread_Running; //set the status to running
				queue_enqueue(running,(void*)nextThread); //add into running queue
				
				//run the thread?
				queue_int = 1;
				
				loop = 1;
				//queue_enqueue(waiting,(void**) &temp);
				uthread_ctx_switch(temp,nextThread->context);
			}
			else{
				struct uthread_tcb* currentThread; //create a temporary variable to hold thread
				currentThread = malloc(sizeof(struct uthread_tcb));
				currentThread->tstack = uthread_ctx_alloc_stack();
				currentThread->context = uthread_ctx_alloc_stack();
				queue_int = queue_dequeue(running,(void**) &currentThread);
				queue_enqueue(zombie,(void**) &currentThread);
				
				nextThread->state = Thread_Running; //set the status to running
				queue_enqueue(running,(void*)nextThread); //add into running queue
				
				
				//run the thread?
				queue_int = 1;
			
				uthread_ctx_switch(currentThread->context,nextThread->context);
	
			}
		}
	}
	
	
	/*
	else if(queue_length(zombie) > 0){
		
		// We try to run the parents one by one but here is where the code fails. 
		
		
		
		
		struct uthread_tcb* nextThread; //create a temporary variable to hold thread
		nextThread = malloc(sizeof(struct uthread_tcb));
		nextThread->tstack = uthread_ctx_alloc_stack();
		nextThread->context = uthread_ctx_alloc_stack();
		queue_int = queue_dequeue(zombie,(void**) &nextThread);
		
		struct uthread_tcb* currentThread; //create a temporary variable to hold thread
		currentThread = malloc(sizeof(struct uthread_tcb));
		currentThread->tstack = uthread_ctx_alloc_stack();
		currentThread->context = uthread_ctx_alloc_stack();
		queue_int = queue_dequeue(running,(void**) &currentThread);
		queue_enqueue(running,(void*)nextThread);
		uthread_ctx_switch(currentThread->context,nextThread->context);
		
		
	}
	
	*/
}


void uthread_exit(void)
{
	//printf("Start of exit() \n");
	/* TODO Phase 2 */
	/*
	 * uthread_exit - Exit from currently running thread
	 *
	 * This function is to be called from the currently active and running thread in
	 * order to finish its execution.
	 */
	struct uthread_tcb* current_thread ;
	
	//printf("running queue length %d\n", queue_length(running));
	int queue_int = 1;
	queue_int = queue_dequeue(running, (void**) &current_thread);
	
	
	//if(!queue_int){
		current_thread->state = Thread_Zombie;
		queue_enqueue(zombie, (void*)current_thread);
		uthread_yield();
	//}
	
	
	
	/*
	queue_dequeue(running,(void*)current_thread);
	current_thread->state = Thread_Zombie;
	queue_enqueue(zombie,(void*)current_thread);*/

	/*add the oldest waiting thread to running */
	/*int queue_int = 1;
	if (queue_length(waiting) != 0) { //if there's a thread waiting,
		struct uthread_tcb* nextThread; //create a temporary variable to hold thread
		queue_int = queue_dequeue(waiting,(void*)nextThread); //remove the thread from waiting queue
		if(!queue_int){
			nextThread->state = Thread_Running; //set the status to running
			queue_enqueue(running,(void*)nextThread); //add into running queue
			//run the thread?
			uthread_ctx_switch(current_thread->context,nextThread->context);
			queue_int = 1;
		}
	}*/

	/*switch context from previously running queue to the next waiting thread*/
	
}

void uthread_block(void)
{
	/* TODO Phase 2 */
	/*
	 * uthread_block - Block currently running thread
	 */

}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 2 */
	/*
	 * uthread_unblock - Unblock thread
	 * @uthread: TCB of thread to unblock
	 */
}

struct uthread_tcb *uthread_current(void)
{
	/*
	 * uthread_current - Get currently running thread
	 *
	 * Return: Pointer to current thread's TCB
	 */
	struct uthread_tcb* cur_thread;
	queue_dequeue(running,(void*)cur_thread);
	queue_enqueue(running,(void*)cur_thread);
	return cur_thread;
}


void uthread_start(uthread_func_t start, void *arg)
{
	/* TODO Phase 2 */
	/*
	 * uthread_start - Start the thread system
	 * @start: Function of the first thread to start
	 * @arg: Argument to be passed to the first thread
	 *
	 * This function should only be called by the main() function of the application
	 * and never returns.
	 *
	 * This function starts the thread system and becomes the "idle" thread. It
	 * exits from the application when all the threads have finished and the thread
	 * system is done running.
	 */

	/* We do the following 3 things:
    1.It registers the so-far single execution flow of the application as the idle thread that the library can schedule
    2.It creates a new thread, the initial thread, as specified by the arguments of the function
    3.The function finally execute an infinite loop which
        a.When there are no more threads which are ready to run in the system, stops the idle loop and exits the program.
        b.Or simply yields to next available thread
	*/
	
	//create 4 queues for different states
	waiting = queue_create();
	running = queue_create();
	blocked = queue_create();
	zombie = queue_create();
	int queue_int = 1, create_status = 1;// To see if the dequeue was successful
	//create idle thread
	

	struct uthread_tcb* idleThread;
	idleThread = malloc(sizeof(struct uthread_tcb));
	idleThread->tstack = uthread_ctx_alloc_stack();
	idleThread->context = uthread_ctx_alloc_stack();
	if (!idleThread->context)
        write(1,"We Lose at context", 7);
	temp = uthread_ctx_alloc_stack();
	temp = idleThread->context;
	create_status = uthread_create(start,arg);
	//queue_enqueue(waiting,firstThread); 
	if(!create_status) {
		;//printf("We are great at creating thread!!!!!!!!!!!\n");
	}

	//uthread_ctx_switch(idleThread->context, firstThread->context);
	/*Keep looping until all jos are done*/

	while(1){
		if(queue_length(waiting) == 0 && queue_length(running) == 0 && 
			queue_length(blocked) == 0)  { //all threads have been executed, everything is done! :D
			//uthread_ctx_switch(,idlethread->context);
			
			printf("All threads have been exeuted, you may now exit this process.\n");
			uthread_ctx_switch(temp,idleThread->context);
			break;
		}
		else{
			//printf("Entering yield()\n");
			uthread_yield();
			
		}
	}
}

//int uthread_ctx_init(uthread_ctx_t *uctx, void *top_of_stack, uthread_func_t func, void *arg)

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	/*
	 * uthread_create - Create a new thread
	 * @func: Function to be executed by the thread
	 * @arg: Argument to be passed to the thread
	 *
	 * Return: 0 in case of success, or -1 in case of failure
	 */
	struct uthread_tcb* new_thread;
	new_thread = malloc(sizeof(struct uthread_tcb));
	new_thread->tstack = uthread_ctx_alloc_stack();
	//new_thread->context = new_thread->tstack;
	new_thread->context = uthread_ctx_alloc_stack();
	if(!uthread_ctx_init(new_thread->context, new_thread->tstack, func, arg)){ 
		new_thread->state = Thread_Waiting; //the newly created thread goes into waiting state
		queue_enqueue(waiting,(void*)new_thread); //let new_thread be ready 
		return 0;
	}
	return -1;
}


	