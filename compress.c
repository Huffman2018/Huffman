#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "huffmanTree.h"
#include "interface.h"
#include "priorityQueue.h"
#include "utilities.h"

void constructFrequencyTable(FILE *file, u_int frequencyTable[]) {
	u_char byte;
	while(fread(&byte, sizeof(u_char), 1, file) == 1) {
		frequencyTable[byte]++;
	}
}
void createByteWay(u_char byteWay[][BYTENUMBER_MAX]) {
	int a;
	for(a = 0; a < BYTENUMBER_MAX; a++) {
		byteWay[a][0] = '\0';
	}
}
void constructByteWay(u_char byteWay[][BYTENUMBER_MAX], u_char byteWayPass[], hTree *tree, int deep) {
	int deepPass = deep;
	if(isLeaf(tree)) {
		int a;
		for(a = 0; a < deep; a++) {
			byteWay[tree->byte][a] = byteWayPass[a];
		}
		byteWay[tree->byte][a] = '\0';
		return;
	}
	if(tree->left != NULL) {
		deepPass = deep + 1;
		byteWayPass[deep] = '0';
		constructByteWay(byteWay, byteWayPass, tree->left, deepPass);
		deepPass = deep;
	}
	if(tree->right != NULL) {
		deepPass = deep + 1;
		byteWayPass[deep] = '1';
		constructByteWay(byteWay, byteWayPass, tree->right, deep+1);
		deepPass = deep;
	}
}
void writeHeader(FILE *file, hTree *tree) {
	u_char byte = 0;
	fwrite(&byte, sizeof(u_char), 2, file);
	writeHTree(file, tree);
}
void writeCompressedFile(FILE *inputFile, FILE *outputFile, u_char byteWay[][BYTENUMBER_MAX], int treeSize) {
	u_char trashSize = 0;
	u_char byte = 0;
	u_char bytePass;
	u_char treeSizePass = treeSize;
	int bitSize = 0;
	int bitWayPos = 0;
	rewind(inputFile);
	while(fread(&bytePass, sizeof(u_char), 1, inputFile) == 1) {
		bitWayPos = 0;
		while(byteWay[bytePass][bitWayPos] != '\0') {
			if(bitSize == 8) {
				fwrite(&byte, sizeof(u_char), 1, outputFile);
				byte = 0;
				bitSize = 0;
			}
			if(byteWay[bytePass][bitWayPos] == '1') {
				byte = setBit(byte, bitSize);
			}
			bitSize++;
			bitWayPos++;
		}
	}
	fwrite(&byte, sizeof(u_char), 1, outputFile);
	trashSize = (8 - bitSize) << 5;
	rewind(outputFile);
	fwrite(&trashSize, sizeof(u_char), 1, outputFile);
	fwrite(&treeSizePass, sizeof(u_char), 1, outputFile);
}
void compressFile() {
	pQueue *queue = createPQueue();
	hTree *tree = createHTree();
	FILE *inputFile = NULL;
	FILE *outputFile = NULL;
	char inputFilename[FILENAME_MAX];
	char outputFilename[FILENAME_MAX];
	u_char byteWay[BYTENUMBER_MAX][BYTENUMBER_MAX];
	u_char byteWayPass[BYTENUMBER_MAX];
	u_int frequencyTable[BYTENUMBER_MAX];
	int *treeSize = (int*)malloc(sizeof(int));
	treeSize = &queue->size;
	while(!fileIsOpen(inputFile)) {
		printf("----- Huffman compress and decompress -----\n");
		printf("Write file name to compress, including extension: ");
		scanf("%[^\n]s", inputFilename);
		getchar();
		strcpy(outputFilename, inputFilename);
		strcat(outputFilename, ".huff");
		inputFile = fopen(inputFilename, "r+");
		if(!fileIsOpen(inputFile)) {
			endScreenCtrl();
		}
	}
	printf("Compressing file...");
	constructFrequencyTable(inputFile, frequencyTable);					printf(".");
	constructPQueue(queue, frequencyTable);								printf(".");
	tree = constructHTree(queue);										printf(".");
	createByteWay(byteWay);												printf(".");
	constructByteWay(byteWay, byteWayPass, tree, 0); 					printf(".");
	outputFile = fopen(outputFilename, "w+");							printf(".");
	writeHeader(outputFile, tree);										printf(".");
	writeCompressedFile(inputFile, outputFile, byteWay, *treeSize);		printf(".");
	fclose(inputFile);													printf(".");
	fclose(outputFile);													printf(".\n");
	printf("Compress complete!\n\n");
	continueScreen();
}
