#include <stdio.h>
#include "utilities.h"

u_char setBit(u_char byte, int bitPos) {
    return (byte | (1 << (7 - bitPos)));
}
int isBitSet(u_char byte, short int a) {
    return (byte & (1 << a));
}