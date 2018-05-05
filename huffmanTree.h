typedef struct huffmanTree {
	char byte;
	int frequency;
	hTree *next;
	hTree *left;
	hTree *right;
} hTree;

hTree* createHuffmanTree();
hTree* mergeNodes(hTree *left, hTree *right);
hTree* constructHuffmanTree(pQueue *queue);
int isLeaf(hTree *tree);
int hTreeEmpty(hTree *tree);
