/**
* Kernel code
*/
#include "../drivers/video/video.h"

int main()
{
    clear_screen();
    print_at("WELCOME TO 1172-OS! ", 0, 0);
    print_at("SIMPLE, ELEGANT, BEAUTIFUL.", 1, 0);
    return 0;
}