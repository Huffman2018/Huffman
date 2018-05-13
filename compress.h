#define BYTENUMBER_MAX 256

typedef unsigned char u_char;
typedef unsigned int u_int;
typedef struct priorityQueue pQueue;
typedef struct huffmanTree hTree;

void constructFrequencyTable(FILE *file, u_int frequencyTable[]);												//Create frequency byte table
void createByteWay(u_char byteWay[][BYTENUMBER_MAX]);															//Create byte way based in frequency byte table
void constructByteWay(u_char byteWay[][BYTENUMBER_MAX], u_char byteWayPass[], hTree *tree, int deep);			//Construct byte way based in input file
void writeHeader(FILE *file, hTree *tree);																		//Write header of compressed file
void writeCompressedFile(FILE *inputFile, FILE *outputFile, u_char byteWay[][BYTENUMBER_MAX], int treeSize);	//Write the compressed file in binary mode
void compressFile();																							//Compress file to .huff using input file and huffman tree
