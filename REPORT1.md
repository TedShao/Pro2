# Pro2

#### Part1: Queue  API

We were able to complete a full implementation of queue. 
For the queue implementation, we had a structure for queue and structure for node. The queue has pointers that point to the front and end of queue and node has a ointer to point to whatever data we require to use and a pointer to the next node. 
To create, the queue, we simply allocate enough memeory to it.
To destroy, the queue, we check if it has elements in it, and the free up that memeory. 
To enqueue, we rerout the pointers of the queue and set the end of the queue to the new element. 
To dequeue, we rerout the pointer to the next element and assign the queue element data to the data passed as argument. 
To delete, we look for the appropriate data, and reassign the respective pointers and free up that memeory.
To iterate, we simply apply the function passed in the paramenter, to all the elements in the queue. 
To find the length of the queue, we walk through the queue, counting elements and returning the total. 

To test the queue, we tried to enqueue and dequeue various types of objects, such as, ints, chars and structs. We tried all the functions and made sure that the ouput was expected. We tried subjecting the queue to 'wrong' elements, to make sure it does not crash or lose objects. 

#### Part2: Thread API

We started the uthread library in the start function. We created global queues for running, waiting, blocked and zombie threads. We realized that we may not need the running queue, since we will only have one running thread at a time, however, it made sense in our implementation of uthread_current.

For uthread_start, we were very comfused as how to use contexts and the stack and how do to the various functions in the context.h files work. We started by putting most of the yield function in the start function. When we started to understand how the program would work, we started with an initial thread, that hold the context for the current context and after calling the create function using the arguments we let the yield function handle the rest. 
For the create function, we simply set the values for the context using the passes func and arg arguments. We the enqueue it to the waiting queue.
In the exit function, we update some queues and states an call teh yield function. 
The bulk of the work is done in the yield function, where its main job is to get elelments from the waiting queue and switch their contexts. 

We were able to pass test1.c however, we ran into trouble in the test2.c file.

#### Part3: Semaphore API
We started implementing semaphore but weren't able to complete semaphore because we were trying to debug threadAPI not passing test2.c

For the smaphore implementation, in the struct, we created variables:
  - value : stores the count of how many threads can be entering the semaphore
  - lock : a simple lock feature with the atomic test_and_set() to ensure no other thread can enter the critical section
  - waiting: a queue that stores all the threads waiting to enter the semaphore

In sem_create(), we allocate space for the semaphore struct, immidiately return NULL if we fail to do so. Once we successfully created it, we initialize the value with the passed in parameter, set the lock to 0, and create a queue for waiting.

In sem_destroy(), we free the queue in the semaphore, and then the semaphore itself.

In sem_down(), we enter a while loop with condition (test_and_set(&sem->lock) == 1) to make sure that the thread doesn't enter the critical section while another thread is running. When it's finally the thread's turn, it first acquires the lock and set the variable to 1 so that no other thread can interrupt it, then it checks if the semaphore is full. If it's full, then the thread gets added to the waiting queue and now releases the lock. Otherwise, it can enter the semaphore and increases the count by 1. AFter it's donw, it releases the lock so the next thread can access the semaphore.

In sem_up(), same as sem_down(), we enter a while loop with condition (test_and_set(&sem->lock) == 1) to make sure that the thread doesn't enter the critical section while another thread is running. When it's finally the thread's turn, it first acquires the lock, then it releases a spot in the semaphore by decrementing the count value. Next, it checks if by decrementing the count value, another thread can enter. If that's true, then we dequeue the first thread from the waiting queue, calling unblock() to let scheduler know that it can schedule the thread now

#### Part4: Preemption

We didn't get to this phase.

### Resources
- https://gist.github.com/mycodeschool/7510222 (our queue structure was heavily based on this)
- https://github.com/twcamper/c-programming/blob/master/lib/bounded-queue.c (another source for examples of queue functions)
- http://stackoverflow.com/questions/1152246/mutual-exclusion-using-testandset-instruction (provided example on dealing with critical section)
- https://github.com/pb376/cs4411-p5/blob/master/PortOSWin/synch.c (provided an example on how to do semaphore)
