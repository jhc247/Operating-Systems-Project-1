/*
 * Generic queue implementation.
 *
 */

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	any_t value;
	struct node* next;
	struct node* prev;
}node;


typedef struct queue
{

	node* head; // the head of the queue
	node* tail; // tail of queue
	int length; //length of queue
}queue;


/*
 * Return an empty queue.
 */
queue_t queue_new() {
	queue_t queue_p = (queue_t)malloc(sizeof(*queue_p));// allocate memory for the pointer to the queue
	
	if(queue_p == NULL){//if not enough memory is allocated 
		printf("malloc has failed to allocate enough memory for the queue");
	}
	
	queue_p->head = queue_p->tail = NULL; //set the head pointer and tail pointer to NULL (initializing them and setting up an empty queue
	queue_p->length = 0;
	return queue_p;

}
/*
 * Prepend an any_t to a queue (both specifed as parameters).  Return
 * 0 (success) or -1 (failure).
 */
int queue_prepend(queue_t queue, any_t item) {
	
	node* node_p = (node*)malloc(sizeof(*node_p)); // give memory to the node

	if(node_p == NULL){ //if not enough memory is allocated
		printf("malloc has failed to allocate enough memory for the PREPEND node");
		return -1;
	}
	node_p->value = item; //add items to pointer
	node_p->next = NULL; //ainitialize next pointer
	node_p->prev = NULL;
	if(queue == NULL){ //if queue is not initialized

		printf("Queue is not initialized (in prepend)");
		free(node_p); //free memory just allocated for the pointer
		return -1;
	}
	else if(queue->head == NULL && queue->tail == NULL){ //if the queue is empty
		queue->head = queue->tail = node_p; //set the head and tail to the only value of the queue
		queue->length += 1;
		return 0;
	}
	
	else if (queue->head == NULL || queue->tail == NULL){

		printf("FUCK THE POLICE");
		return -1;

	}

	else{ //queue is not empty
		node_p->next = queue->head; //not sure, but set the new nodes next to the previous heads 
		node_p->prev = NULL;
		queue->head->prev = node_p; // set node_p to the top of the queue
		queue->head = node_p; //set node_p to the current head node
		queue->length += 1;
	}

	return 0;

}

/*
 * Append an any_t to a queue (both specifed as parameters). Return
 * 0 (success) or -1 (failure). 
 */
int queue_append(queue_t queue, any_t item) {
	node* node_p = (node*)malloc(sizeof(*node_p)); // allocate memory for the node

	if(node_p == NULL){ // if not enough memory
		printf("NOT ENOUGH MEMORY TO APPEND");
		return -1;
	}
	node_p->value = item; //add items to pointer
	node_p->next = NULL; //a initialize next pointer
	node_p->prev = NULL;
	if(queue == NULL) { //if there queue was not initialized
		printf("QUEUE HAS NOT BEEN INITIALIZED IN APPEND");
		free(node_p);
		return -1;
	}
	else if (queue->head == NULL && queue->tail == NULL){ //if queue is empty
		queue->head = queue->tail = node_p; //add to queue
		queue->length += 1;
		return 0;
	}

	else if(queue->head == NULL || queue->tail == NULL){
		printf("WAFFLE FRIES");
		return -1;
	}
	else{ //queue is not empty
		node_p->prev = queue->tail; //not sure, but maybe set the prev value of the new node to the old node
		node_p->next = NULL;
		queue->tail->next = node_p; //set node_p to be the last node
		queue->tail = node_p; //set the tail to be node_p (which is now the last node)
		queue->length += 1;
	}
	return 0;



}

/*
 * Dequeue and return the first any_t from the queue or NULL if queue
 * is empty.  Return 0 (success) or -1 (failure).
 */
int queue_dequeue(queue_t queue, any_t* item) {

	node* a = NULL;
	node* b = NULL;

	if( queue == NULL){//check if queue is null
		printf("no queue");
		return -1;
	}
	else if (queue->head == NULL && queue->tail == NULL){//check if queue is empty
		printf("queue is empty");
		return -1;
	}

	else if(item == NULL){
		printf("are you my mommy?");
		return -1;

	}

	a = queue->head; // a is the head
	b = a->next;// bis the next
	*item = a->value;
	printf("the address of the first any_t is %d", *item); //print the item
	free (a);// free a
	queue->head = b; //set the new head to b
	queue->length -= 1;
	if(queue->head = NULL){//queue is empty
		queue->tail = queue->head;
	}
	return 0;
}

/*
 * Iterate the function parameter over each element in the queue.  The
 * additional any_t argument is passed to the function as its first
 * argument and the queue element is the second.  Return 0 (success)
 * or -1 (failure).
 */
int queue_iterate(queue_t queue, PFany f, any_t item) {
	node* a = NULL;
	a = queue->head;

	/*if(queue == NULL){
		printf("what queue?");
		return -1;
	}*/
	
	if( item == NULL){
		printf("there is no item");
		return -1;

	}
	while (a){
		
		int x = f(item, a);
		printf("the first value is : %d", x);
		a = a->next;
	}
   

	return 0;
}

/*
 * Free the queue and return 0 (success) or -1 (failure).
 */
int queue_free (queue_t queue) {
      
	node* a = NULL;
	node* b = NULL;
	
	  if( queue == NULL){
		free(queue);
		return 0;
	  }
	  else {//if(queue->head == NULL && queue->tail == NULL){
		  free(queue);
		  return 0;

	  }
	  /*
	  else{
		  while(queue->head){ //while queue has a head
			  a = queue->head; //set a to queue head
			  b = a->next; //set b to next node of a
			  free(a);
			  queue->head = b;
			  if(queue->head == NULL){ //finish clearing queue and free queue
				  queue->head = queue->tail;
				  free(queue);
			  }
				  return 0;
			  
		  }*/

		  }

/*
 * Return the number of items in the queue.
 */
int queue_length(queue_t queue) {

	printf("there are %d items in the queue", queue->length);
	return queue->length;
}


/* 
 * Delete the specified item from the given queue. 
 * Return -1 on error.
 */
int queue_delete(queue_t queue, any_t* item) {
	
	node* finder = NULL;
	
	if(queue == NULL || item == NULL){ // arguments not allocated
		printf("allocation error in queue_delete");
		return -1;
	}

	else if(queue->head == NULL && queue->tail == NULL){//queue is empty
		printf("queue is empty");
		return -1;
	}

	else{
		finder = queue->head; //finder start at head of queue
		while( finder){ //while finder is not NULL
			if(finder->value == *item){ //if value of the node finder is pointing to is the same as the item looked for
				if(finder != queue->head){ //if the value is found and finder is not the head, set the previous nodes next to finders next
				finder->prev->next = finder->next;
				}
				if(finder != queue->tail){//if the value is found and finder is not the tail, set the previous node next to the finders previous
				finder->next->prev = finder->prev;
				}
				if(finder == queue->head){ //if the finder is the head
					queue->head = queue->head->next; // set the head value to the next value in the queue
				}
				if(finder == queue->tail){//if the finder is the tail
					queue->tail = queue->tail->prev; //set the tail value to the previous last value in the queue
				}

				finder->next = NULL; //if finder is the found value set all value of the nodes to null and free it.
				finder->prev = NULL; 
				finder->value = NULL;
				free(finder);
				queue->length -= 1;
				return 0;
			}
			if(finder == queue->tail && finder->value != *item){ //if entire queue is search and item is not found, set finder to null and free it.
				printf("the item is not on the list");
				finder = NULL;
				free(finder);
				return 0;
			}
			else{//if item is not found in current node, and queue is not at an end, go to next node
			finder = finder->next;
			}
		}

		}

	return 0;
}
