#ifndef WHY_MACROS_H
#define WHY_MACROS_H

#define ABS(x) ((((x) < 0)) ? -(x) : (x))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define SWAP(a , b, type) {type swap = a; a = b; b = swap;}

#endif