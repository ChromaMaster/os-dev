#include "std.h"
#include "string.h"

void int_to_ascii(int n, char *int_str) {
    int i = 0;
    int is_negative = 0;

    if (n == 0) {
        int_str[i++] = '0';
        int_str[i] = '\0';
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