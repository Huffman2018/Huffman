#include <stdio.h>
#include <stdlib.h>
#include "huffmanTree.h"
#include "priorityQueue.h"

pQueue* createPQueue() {
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
	return newNode;
}
void enqueueNode(pQueue *queue, char byte, int frequency) {
	hTree *newNode = createNode(byte, frequency);
	if(pQueueEmpty(queue) || queue->head->frequency >= frequency) {
		newNode->next = queue->head;
		queue->head = newNode;
	} else {
		hTree *temp = queue->head;
		while(temp->next != NULL || temp->next->frequency < frequency) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}
	queue->size++;
}
void enqueueParentNode(pQueue *queue, hTree *node) {
	if(pQueueEmpty(queue) || queue->head->frequency >= node->frequency) {
		node->next = queue->head;
		queue->head = node;
	} else {
		hTree *temp = queue->head;
		while(temp->next != NULL || temp->next->frequency >= node->frequency) {
			temp = temp->next;
		}
		node->next = queue->head;
		queue->head = node;
	}
	queue->size++;
}
hTree* dequeueNode(pQueue *queue) {
	if(!pQueueEmpty(queue)){
		hTree *node = queue->head;
		node->next = NULL;
		queue->head = queue->head->next;
		return node;
	}
	return NULL;
}
int pQueueEmpty(pQueue *queue) {
	return (queue->head == NULL);
}
