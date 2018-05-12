typedef unsigned char u_char;
typedef unsigned int u_int;
typedef struct priorityQueue pQueue;
typedef struct huffmanTree hTree;					//Huffman Tree struct
struct huffmanTree {
	u_char byte;
	u_int frequency;
	hTree *next;
	hTree *left;
	hTree *right;
};

hTree* createHTree();								//Create Huffman Tree
hTree* constructHTree(pQueue *queue);				//Construct Huffman Tree using the priority queue
hTree* mergeNodes(hTree *left, hTree *right);		//Create a father to last 2 nodes of  priority queue
int isLeaf(hTree *tree);							//Verify if a node has a leaf
int hTreeEmpty(hTree *tree);						//Verify if huffman tree has empty
void writeHTree(FILE *file, hTree *tree);			//Write Huffman Tree (pre-order) in file
