#include <stdio.h>
#include <stdlib.h>
#include "huffmanTree.h"
#include "priorityQueue.h"
#include "utilities.h"

pQueue* createPQueue() {
	pQueue *newQueue = (pQueue*)malloc(sizeof(pQueue));
	newQueue->head = NULL;
	newQueue->size = 0;
	return newQueue;
}
void constructPQueue(pQueue *queue, u_int frequencyTable[]) {
	u_int a;
	for(a = 0; a < BYTENUMBER_MAX; a++) {
		if(frequencyTable[a] != 0) {
			enqueueNode(queue, a, frequencyTable[a]);
		}
	}
}
hTree* createNode(u_char byte, u_int frequency) {
	hTree *newNode = (hTree*)malloc(sizeof(hTree));
	newNode->byte = byte;
	newNode->frequency = frequency;
	newNode->next = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}
void enqueueNode(pQueue *queue, u_char byte, u_int frequency) {
	hTree *newNode = createNode(byte, frequency);
	if(pQueueEmpty(queue) || queue->head->frequency >= frequency) {
		newNode->next = queue->head;
		queue->head = newNode;
	} else {
		hTree *pass = queue->head;
		while(pass->next != NULL && pass->next->frequency < frequency) {
			pass = pass->next;
		}
		newNode->next = pass->next;
		pass->next = newNode;
	}
	queue->size++;
}
void enqueueParentNode(pQueue *queue, hTree *node) {
	if(pQueueEmpty(queue) || queue->head->frequency >= node->frequency) {
		node->next = queue->head;
		queue->head = node;
	} else {
		hTree *pass = queue->head;
		while(pass->next != NULL && pass->next->frequency < node->frequency) {
			pass = pass->next;
		}
		node->next = pass->next;
		pass->next = node;
	}
	queue->size++;
}
hTree* dequeueNode(pQueue *queue) {
	if(!pQueueEmpty(queue)){
		hTree *node = queue->head;
		queue->head = queue->head->next;
		node->next = NULL;
		return node;
	}
	return NULL;
}
int pQueueEmpty(pQueue *queue) {
	return (queue->head == NULL);
}
