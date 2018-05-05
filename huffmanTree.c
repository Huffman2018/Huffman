#include <stdio.h>
#include <stdlib.h>
#include "huffmanTree.h"
#include "priorityQueue.h"

hTree* createHuffmanTree() {
	return NULL;
}
hTree* mergeNodes(hTree *left, hTree *right) {
	hTree *parentNode = createNode('\*', (left->frequency + right->frequency));
	parentNode->left = left;
	parentNode->right = right;
	return parentNode;
}
hTree* constructHuffmanTree(pQueue *queue) {
	hTree *parentNode = createHuffmanTree();
	while(queue->head->next != NULL) {
		parentNode = mergeNodes(dequeueNode(queue), dequeueNode(queue));
		enqueueParentNode(queue, parentNode);
	}
	return queue->head;
}
int isLeaf(hTree *tree) {
	return ((tree->left == NULL) && (tree->right == NULL));
}
int hTreeEmpty(hTree *tree) {
	return (tree == NULL);
}
