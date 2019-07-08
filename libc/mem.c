#include "mem.h"

void memcpy(u8int *src, u8int *dst, int n_bytes) {
    for (int i = 0; i < n_bytes; i++) {
        dst[i] = src[i];
    }
}