# Pro2

## Functions

## To-Do List

#### Part1: Queue  API
- [X] create()
- [X] destroy()
- [X] enqueue()
- [X] dequeue()
- [X] delete()
- [ ] iterate() //How the Fuck do I use the function????????? alksdalksjdlsakdj
- [X] length()


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
- [ ] tcb
- [ ] yield()
- [ ] create()
- [ ] exit()
- [ ] block()
- [ ] unblock()
- [ ] current()
- [ ] start()

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

In sem_destroy(), we free the queue in the semaphore, and then the semaphore itself

In sem_down(),

In sem_up(),

#### Part4: Preemption
### Resources
- https://gist.github.com/mycodeschool/7510222 (our queue structure was heavily based on this)
- https://github.com/twcamper/c-programming/blob/master/lib/bounded-queue.c (another source for examples of queue functions)
