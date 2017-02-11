
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include <assert.h>
struct queuetest {
	int value;
};

int main(void){
	struct queuetest* queue_element = malloc(sizeof(struct queuetest));
	queue_element->value = 1;
	struct queuetest* queue_element2 = malloc(sizeof(struct queuetest));
	queue_element2->value = 2;
	struct queuetest* queue_element3 = malloc(sizeof(struct queuetest));
	queue_element3->value = 3;
	struct queuetest* queue_element4 = malloc(sizeof(struct queuetest));
	queue_element4->value = 4;
	struct queuetest* queue_element5 = malloc(sizeof(struct queuetest));
	queue_element5->value = 5;
	queue_t queue_elementQueue = queue_create();
	queue_enqueue(queue_elementQueue,(void*)queue_element);
	queue_enqueue(queue_elementQueue,(void*)queue_element2);
	queue_enqueue(queue_elementQueue,(void*)queue_element3);
	queue_enqueue(queue_elementQueue,(void*)queue_element4);
	queue_enqueue(queue_elementQueue,(void*)queue_element5);
	struct queuetest* kqueue_element = malloc(sizeof(struct queuetest));
	
	queue_dequeue(queue_elementQueue,(void*)kqueue_element);
	
	int queue_elementVal = 99;
	queue_elementVal = kqueue_element->value;
	
	
	queue_t hiQueue = queue_create();
	queue_enqueue(hiQueue,(void*)1);
	queue_enqueue(hiQueue,(void*)2);
	queue_enqueue(hiQueue,(void*)3);
	queue_enqueue(hiQueue,(void*)4);
	queue_enqueue(hiQueue,(void*)5);
	queue_enqueue(hiQueue,(void*)6);
	queue_enqueue(hiQueue,(void*)7);
	queue_enqueue(hiQueue,(void*)8);
	queue_enqueue(hiQueue,(void*)9);
	//queue_dequeue(hiQueue,(void*)2);
	
	assert(queue_enqueue(NULL, NULL) == -1);
	assert(queue_destroy(NULL) == -1);
	
	void *k = NULL;
	int l = queue_dequeue(hiQueue, &k);

	queue_enqueue(hiQueue, (void*)10);

	return 0;
}
