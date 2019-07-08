#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Attribute byte for our default colour scheme.

// All supported colors with black background color
#define BLUE_ON_BLACK 0x01
#define GREEN_ON_BLACK 0x02
#define CYAN_ON_BLACK 0x03
#define RED_ON_BLACK 0x04
#define MAGENTA_ON_BLACK 0x05
#define BROWN_ON_BLACK 0x06
#define LIGHT_GREY_ON_BLACK 0x07
#define DARK_GREY_ON_BLACK 0x08
#define LIGHT_BLUE_ON_BLACK 0x09
#define LIGHT_GREEN_ON_BLACK 0x0a
#define LIGHT_CYAN_ON_BLACK 0x0b
#define LIGHT_RED_ON_BLACK 0x0c
#define LIGHT_MAGENTA_ON_BLACK 0x0d
#define LIGHT_BROWN_ON_BLACK 0x0e
#define WHITE_ON_BLACK 0x0f

#define RED_ON_WHITE 0xf4

// Screen device I / O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

/**
 * kprint - print message to the screen
 * @param message message to be printed
 * 
 * Print message to the screen at current cursor position
 */
void kprint(char* message);

/**
 * kprintln - print message to the screen
 * @param message message to be printed
 * 
 * Print message to the screen at current cursor position and add newline
 */
void kprintln(char* message);

/**
 * print_at - print message to the screen
 * @param message message to be printed
 * @param row row where string starts. max value is 24
 * @param col col where string starts. max value is 79
 * @param attr attribute for the character (background & foreground colors)
 * 
 * Print message to the screen at [row, col] position
 */
void kprint_at(char* message, int row, int col, int attr);

/**
 * clear_screen - clear the screen
 */
void clear_screen();

////////////////////////////////////////////////////////////////////////////////
// Private driver functions
////////////////////////////////////////////////////////////////////////////////

// Print a char on the screen at row, col, or at cursor position.
void print_char(char character, int row, int col, char attr);

// Returns the offset of a the position [row, col]
int get_offset(int row, int col);

// Get the row of a offset given
int get_offset_row(int offset);

// Get the col of a offset given
int get_offset_col(int offset);

// Get the current cursor offset
int get_cursor_offset();

// Move the cursor to offset
void set_cursor_offset(int offset);

// Scrolls the screen if the cursor get out of the screen
int scroll_screen(int offset);