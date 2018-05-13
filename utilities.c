#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

u_char setBit(u_char byte, int bitPos) {
    return (byte | (1 << (7 - bitPos)));
}
int isBitSet(u_char byte, int a) {
    return (byte & (1 << a));
}
int fileIsOpen(FILE *file) {
	return (file != NULL);
}
