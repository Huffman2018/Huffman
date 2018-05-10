# Huffman

Compress and decompress files using Huffman algorithm.

### Who to compile (Terminal):

	gcc -c compress.c -o compress.o
	gcc -c decompress.c -o decompress.o
	gcc -c huffmanTree.c -o huffmanTree.o
	gcc -c interface.c -o interface.o
	gcc -c main.c -o main.o
	gcc -c priorityQueue.c -o priorityQueue.o
	gcc -c utilities.c -o utilities.o
	gcc compress.o decompress.o huffmanTree.o interface.o main.o priorityQueue.o utilities.o -o executable

or:

	compilator.sh

### Who to execute (Terminal):

	executable.exe

Enjoy