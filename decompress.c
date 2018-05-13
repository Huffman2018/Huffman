#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decompress.h"
#include "huffmanTree.h"
#include "interface.h"
#include "priorityQueue.h"
#include "utilities.h"

int fileIsHuff(char *filename) {
	char huffExtension[] = ".huff";
	int a;
	int b = 0;
	for(a = (strlen(filename) - 5); a < strlen(filename); a++, b++) {
		if(filename[a] != huffExtension[b]) {
			return 0;
		}
	}
	return 1;
}
void writeDecompressedFile(FILE *inputFile, FILE *outputFile, hTree *tree, int trashSize) {
	hTree *treePass;
	u_char byte;
	u_char bytePrevious;
	int bitPos;
	treePass = tree;
	fread(&byte, sizeof(u_char), 1, inputFile);
	bytePrevious = byte;
	while(fread(&byte, sizeof(u_char), 1, inputFile) == 1) {
		for(bitPos = 7; bitPos >= 0; bitPos--) {
			if(isLeaf(treePass)) {
				fwrite(&treePass->byte, sizeof(u_char), 1, outputFile);
				treePass = tree;
			}
			if(!isBitSet(bytePrevious, bitPos)) {
				treePass = treePass->left;
			} else {
				treePass = treePass->right;
			}
		}
		bytePrevious = byte;
	}
	for(bitPos = 7; bitPos >= trashSize - 1; bitPos--) {
		if(isLeaf(treePass)) {
			fwrite(&treePass->byte, sizeof(u_char), 1, outputFile);
			treePass = tree;
		}
		if(!isBitSet(bytePrevious, bitPos)) {
			treePass = treePass->left;
		} else {
			treePass = treePass->right;
		}
	}
}
void decompressFile() {
	hTree *tree = createHTree();
	FILE *inputFile = NULL;
	FILE *outputFile = NULL;
	char inputFilename[FILENAME_MAX];
	char outputFilename[FILENAME_MAX];
	u_char trashSize;
	u_char treeSize;
	int trashSizePass;
	while(!fileIsOpen(inputFile) || !fileIsHuff(inputFilename)) {
		printf("----- Huffman compress and decompress -----\n");
		printf("Write file name to decompress, including extension: ");
		scanf("%[^\n]s", inputFilename);
		getchar();
		inputFile = fopen(inputFilename, "rb");
		if(!fileIsOpen(inputFile) || !fileIsHuff(inputFilename)) {
			endScreenCtrl();
		}
	}
	fflush(stdin);
	printf("Write file name after decompress, including extension: ");
	scanf("%[^\n]s", outputFilename);
	getchar();
	printf("Decompressing file...");
	fread(&trashSize, sizeof(u_char), 1, inputFile);					printf(".");
	trashSize = (trashSize >> 5);										printf(".");
	trashSizePass = trashSize;											printf(".");
	fread(&treeSize, sizeof(u_char), 1, inputFile);						printf(".");
	tree = reconstructHTree(inputFile, tree);							printf(".");
	outputFile = fopen(outputFilename, "wb");							printf(".");
	writeDecompressedFile(inputFile, outputFile, tree, trashSizePass);	printf(".");
	fclose(inputFile);													printf(".");
	fclose(outputFile);													printf(".\n");
	printf("Decompress complete!\n\n");
	continueScreen();
}