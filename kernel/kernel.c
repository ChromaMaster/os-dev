#include "../drivers/screen.h"

void main() {
    clear_screen();
    kprintln("Medium size string");
    kprintln("SecondMedium size string");
    kprint_at("Printed at [25,60]", 23, 70);
    kprint_at("SCROLL_____", 24, 70);
    kprint_at("SecondSsSSCROLL_____", 24, 79);
}