#include "screen.h"
#include "io_ports.h"

void kprint(char *message) {
    kprint_at(message, -1, -1);
}

void kprintln(char *message) {
    kprint_at(message, -1, -1);
    print_char('\n', -1, -1, 0);
}

void kprint_at(char *message, int row, int col) {
    // Get current row and col of cursor if there are negative
    int offset;
    if (row < 0 || col < 0) {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    // Loop through each char of the message and print it.
    int i = 0;
    while (message[i] != 0) {
        print_char(message[i++], row, col, 0);
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Private driver functions
////////////////////////////////////////////////////////////////////////////////

void print_char(char character, int row, int col, char attr) {
    // Create a byte (char) pointer to the start of video memory
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;

    // Error control: print a red 'E' if the coords aren't right */
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
        vidmem[2 * (MAX_COLS) * (MAX_ROWS)-1] = RED_ON_WHITE;
        return;
    }
    // // Returns 0 coords are out of the screen
    // if (row > MAX_ROWS || col > MAX_COLS) {
    //     return -1;
    // }

    // If attribute byte is zero, assume the default style.
    if (attr == 0) {
        attr = WHITE_ON_BLACK;
    }

    // Get the video memory offset for the screen location
    int offset;

    // If col and row are non - negative, use them for offset.
    if (row >= 0 && col >= 0) {
        offset = get_offset(row, col);
    } else {
        // Otherwise, use the current cursor position.
        offset = get_cursor_offset();
    }

    // If we see a newline character, set offset to the end of
    // current row, so it will be advanced to the first col
    // of the next row.
    if (character == '\n') {
        int rows = get_offset_row(offset);
        offset = get_offset(rows + 1, 0);
    } else {
        // Otherwise, write the character and its attribute byte to
        // video memory at our calculated offset.
        vidmem[offset] = character;
        vidmem[offset + 1] = attr;

        // Update the offset to the next character cell, which is
        // two bytes ahead of the current cell.
        offset += 2;
    }

    // Make scrolling adjustment, for when we reach the bottom
    // of the screen.
    // offset = handle_scrolling(offset);

    // Update the cursor position on the screen device.
    set_cursor_offset(offset);
}

int get_offset(int row, int col) {
    // (row * ROW_WIDTH (MAX_COLS) + col) * 2(bytes per character)
    return (row * MAX_COLS + col) * 2;
}

int get_offset_row(int offset) {
    return offset / (2 * MAX_COLS);
}
int get_offset_col(int offset) {
    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}

int get_cursor_offset() {
    // DOC: http://www.osdever.net/FreeVGA/vga/textcur.htm#position
    // The device uses its control register as an index
    // to select its internal registers, of which we are
    // interested in :
    // reg 14: which is the high byte of the cursor’s offset
    // reg 15: which is the low byte of the cursor’s offset

    // Once the internal register has been selected , we may read or
    // write a byte on the data register.
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    // Since the cursor offset reported by the VGA hardware is the
    // number of characters , we multiply by two to convert it to
    // a character cell offset.
    return offset * 2;
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
    /* Loop through video memory and write blank characters . */
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            print_char(' ', row, col, WHITE_ON_BLACK);
        }
    }

    // Move the cursor back to the top left .
    set_cursor_offset(get_offset(0, 0));
}
