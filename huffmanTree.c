#include <stdio.h>
#include <stdlib.h>
#include "huffmanTree.h"
#include "priorityQueue.h"

hTree* createHTree() {
	return NULL;
}
hTree* constructHTree(pQueue *queue) {
	hTree *parentNode = createHTree();
	while(queue->head->next != NULL) {
		parentNode = mergeNodes(dequeueNode(queue), dequeueNode(queue));
		enqueueParentNode(queue, parentNode);
	}
	return queue->head;
}
hTree* mergeNodes(hTree *left, hTree *right) {
	hTree *parentNode = createNode('\*', (left->frequency + right->frequency));
	parentNode->left = left;
	parentNode->right = right;
	return parentNode;
}
int isLeaf(hTree *tree) {
	return ((tree->left == NULL) && (tree->right == NULL));
}
int hTreeEmpty(hTree *tree) {
	return (tree == NULL);
}
void writeHTree(FILE *file, hTree *tree, int *treeSize) {
	if(isLeaf(tree)) {
		if(tree->byte == '\\' || tree->byte == '*') {
			char byte = '\\';
			(*treeSize)++;
			fwrite(&byte, sizeof(char), 1, file);
		}
		(*treeSize)++;
		fwrite(&tree->byte, sizeof(char), 1, file);
		return;
	}
	if(tree->left != NULL) {
		writeHTree(file, tree->left, treeSize);
	}
	if(tree->right != NULL) {
		writeHTree(file, tree->right, treeSize);
	}
}
