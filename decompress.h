#define BYTENUMBER_MAX 256

typedef unsigned char u_char;
typedef unsigned int u_int;
typedef struct priorityQueue pQueue;
typedef struct huffmanTree hTree;

int fileIsHuff(char *filename);																	//Verify if file is .huff type
void writeDecompressedFile(FILE *inputFile, FILE *outputFile, hTree *tree, int trashSize);		//Write decompressed file in binary mode
void decompressFile();																			//Decompress file using compressed file