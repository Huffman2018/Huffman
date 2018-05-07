#include "huffmanTree.h"

//Priority Queue
typedef struct priorityQueue {
	hTree *head;
	int size;
} pQueue;

pQueue* createPQueue();										//Create Priority Queue
hTree* createNode(char byte, int frequency);				//Create a new node
void enqueueNode(pQueue *queue, char byte, int frequency);	//Create and add a new node in ascending order
void enqueueParentNode(pQueue *queue, hTree *node);			//Add a node in ascending order
hTree* dequeueNode(pQueue *queue);							//Dequeue the head of priority queue
int pQueueEmpty(pQueue *queue);								//Verify if priority queue has empty
