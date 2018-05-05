typedef struct huffmanTree {
	char byte;
	int frequency;
	hTree *next;
	hTree *left;
	hTree *right;
} hTree;
