#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "compress.h"
#include "decompress.h"

void initScreen() {
	int choice = -1;
	endScreenCtrl();
	while(1) {
		printf("----- Huffman project -----\n");
		printf("1) Compress file\n");
		printf("2) Decompress file\n");
		printf("0) Exit\n");
		printf("\n");
		printf("Option: ");
		scanf("%d", &choice);
		endScreenCtrl();
		if(choice == 1) {
			//compressFile();		//in development
			break;
		} else if(choice == 2) {
			//decompressFile();		//in development
			break;
		} else if(choice == 0) {
			exitScreen();
			break;
		}
	}
}

void exitScreen() {
	printf("----- Bye! -----\n");
}

void continueScreen() {
	char choice;
	while(1) {
		printf("----- Huffman project -----\n");
		printf("Do you want to continue? (Y/N)\n");
		printf("\n");
		printf("Option: ");
		choice = getchar();
		endScreenCtrl();
		choice = toupper(choice);
		if(choice == 'Y') {
			initScreen();
			break;
		} else if(choice == 'N') {
			exitScreen();
			break;
		}
	}
}

void endScreenCtrl() {
	system("cls");
	fflush(stdin);
}
