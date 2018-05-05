#include "huffmanTree.h"

typedef struct priorityQueue {
	hTree *head;
	int size;
} pQueue;

pQueue* createPQueue();
hTree* createNode(char byte, int frequency);
void enqueueNode(pQueue queue, char byte, int frequency);
hTree* dequeueNode(pQueue queue);
int pQueueEmpty(pQueue queue);
