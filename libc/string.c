#include "string.h"

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