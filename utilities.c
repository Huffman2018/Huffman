#include "utilities.h"

u_char set_bit (u_char byte, int bitPos) {

    return (byte | (1 << (7 - bitPos)));
}

int is_bit_set (u_char byte, short int a) {

    return (byte & (1 << a));
}