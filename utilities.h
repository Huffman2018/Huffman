#define BYTENUMBER_MAX 256

typedef unsigned char u_char;
typedef unsigned int u_int;

u_char setBit(u_char byte, int bitPos);		//Set bit to bit position
int isBitSet(u_char byte, short int a);		//Verify if bit has set in 'a' position
