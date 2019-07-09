#include "mem.h"

void memcpy(u8 *src, u8 *dst, int n_bytes) {
    for (int i = 0; i < n_bytes; i++) {
        dst[i] = src[i];
    }
}