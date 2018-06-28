#include <stdio.h>
#include <stdlib.h>
#include "huffmanTree.h"
#include "priorityQueue.h"
#include "utilities.h"

hTree* createHTree() {
	return NULL;
}
hTree* constructHTree(pQueue *queue) {
	hTree *parentNode = createHTree();
	hTree *node1 = createHTree();
	hTree *node2 = createHTree();
	while(queue->head->next != NULL) {
		node1 = dequeueNode(queue);
		node2 = dequeueNode(queue);
		parentNode = mergeNodes(node1, node2);
		enqueueParentNode(queue, parentNode);
	}
	return queue->head;
}
hTree* reconstructHTree(FILE *file, hTree *tree) {
	u_char byte;
	fread(&byte, sizeof(u_char), 1, file);
	if(byte == '*') {
		tree = createNode(byte, 0);
		tree->left = reconstructHTree(file, tree->left);
		tree->right = reconstructHTree(file, tree->right);
	} else {
		if(byte == '\\') {
			fread(&byte, sizeof(u_char), 1, file);
			tree = createNode(byte, 0);
		} else {
			tree = createNode(byte, 0);
		}
	}
}
hTree* mergeNodes(hTree *left, hTree *right) {
	u_int frequency = left->frequency + right->frequency;
	hTree *parentNode = createNode('\*', frequency);
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
void writeHTree(FILE *file, hTree *tree) {
	if(isLeaf(tree)) {
		if(tree->byte == '\\' || tree->byte == '*') {
			u_char byte = '\\';
			fwrite(&byte, sizeof(u_char), 1, file);
		}
		fwrite(&tree->byte, sizeof(u_char), 1, file);
		return;
	}
	fwrite(&tree->byte, sizeof(u_char), 1, file);
	if(tree->left != NULL) {
		writeHTree(file, tree->left);
	}
	if(tree->right != NULL) {
		writeHTree(file, tree->right);
	}
}
