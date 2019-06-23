#define INT_MAX (1 << 31) - 1

/**
 * memory_copy - copy data from one address to another
 * @param *src source memory address
 * @param *dst destination memory address
 * @param n_bytes number of bytes to copy
 * 
 * Copy n_bytes of bytes from source address to the destination address
 */
void memory_copy(char *src, char *dst, int n_bytes);

/**
 * int_to_ascii - 
 * @param n
 * @param int_str
 * @return 
 */
void int_to_ascii(int n, char *int_str);

/**
 * strlen - get the length of a string
 * @param *str string to get the length from
 * @return the actual string length
 */
int strlen(char *str);

/**
 * strreverse - reverse the string
 * @param *str string to reverse
 */
void strreverse(char *str);