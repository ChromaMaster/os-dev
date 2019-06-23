#include "util.h"

void memory_copy(char *src, char *dst, int n_bytes) {
    for (int i = 0; i < n_bytes; i++) {
        dst[i] = src[i];
        // *(dst + i) = *(src + 1);
        // dst[i] = '#';
    }
}

void int_to_ascii(int n, char *int_str) {
    int i = 0;
    int is_negative = 0;

    if (n == 0) {
        int_str[i++] = '0';
        int_str[i] = '\0';
        return int_str;
    }

    if (n < 0) {
        is_negative = 1;
        n = -n;
    }

    while (n != 0) {
        int rem = n % 10;
        int_str[i++] = '0' + rem;
        n /= 10;
    }

    if (is_negative) {
        int_str[i++] = '-';
    }

    int_str[i] = '\0';

    // reverse the string
    strreverse(int_str);
}

int strlen(char *str) {
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

void strreverse(char *str) {
    char tmp_c;
    int start = 0;
    int end = strlen(str) - 1;
    while (start < end) {
        char tmp_c = str[start];
        str[start] = str[end];
        str[end] = tmp_c;

        start++;
        end--;
    }
}