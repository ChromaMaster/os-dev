/**
 * port_byte_in - read a byte from a specific port
 * @param port port to read from
 * 
 * @return byte read from the port
 */
unsigned char port_byte_in(unsigned short port);

/**
 * port_byte_out - write a byte to a specific port
 * @param port port to write to
 * @param data byte to wite to the port 
 */
void port_byte_out(unsigned short port, unsigned char data);

/**
 * port_word_in - read a word from a specific port
 * @param port port to read from
 * 
 * @return word read from the port
 */
unsigned short port_word_in(unsigned short port);

/**
 * port_word_out - write a word to a specific port
 * @param port port to write to
 * @param data word to write to the port 
 */
void port_word_out(unsigned short port, unsigned short data);