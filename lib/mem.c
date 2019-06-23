#include "mem.h"

void memcpy(char *src, char *dst, int n_bytes) {
    for (int i = 0; i < n_bytes; i++) {
        dst[i] = src[i];
    }
}