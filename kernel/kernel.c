#include "../drivers/screen.h"

void main() {
    clear_screen();
    kprintln("Medium size string");
    kprint("Large size string that it will be printed to the screen");
    kprintln("String with end line");
    kprint("Another stirng");
    kprint_at("Printed at [25,60]", 23, 79);
}