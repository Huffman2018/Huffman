#include <stdlib.h>

typedef struct priorityQueue {
	hTree *head;
	int size;
} pQueue;
typedef struct huffmanTree {
	char byte;
	int frequency;
	hTree *next;
	hTree *left;
	hTree *right;
} hTree;

pQueue* createPQueue {
	pQueue *newQueue = (pQueue*) malloc(sizeof(pQueue));
	newQueue->head = NULL;
	newQueue->size = 0;
	return newQueue;
}
hTree* createNode(char byte, int frequency) {
	hTree *newNode = (hTree*) malloc(sizeof(hTree));
	newNode->byte = byte;
	newNode->frequency = frequency;
	newNode->next = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	return NewNode;
}
void addNodeQueue(pQueue queue, char byte, int frequency) {
	hTree newNode = createNode(byte, frequency);
	if(pQueueEmpty(queue) || queue->head->frequency >= frequency) {
		newNode->next = queue->head;
		queue->head = newNode;
	} else {
		hTree* temp = queue->head;
		while(temp->next != NULL || temp->next->frequency < frequency) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}
	queue->size++;
}
int pQueueEmpty(pQueue queue) {
	return (queue->head == NULL);
}

