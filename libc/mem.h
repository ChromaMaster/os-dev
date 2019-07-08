#ifndef MEM_H
#define MEM_H

#include "types.h"

/**
 * memcpy - copy data from one address to another
 * @param *src source memory address
 * @param *dst destination memory address
 * @param n_bytes number of bytes to copy
 * 
 * Copy n_bytes of bytes from source address to the destination address
 */
void memcpy(u8int *src, u8int *dst, int n_bytes);

#endif  // !MEM_H