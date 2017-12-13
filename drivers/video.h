/**
* Screen driver header file
*/
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// default color scheme
#define WHITE_ON_BLACK 0x0f
#define BLACK_ON_WHITE 0xf0
#define WHITE_ON_BLUE 0x1f
// screen device I/O ports
#define REG_SCREEN_CONTROL 0x3D4
#define REG_SCREEN_DATA 0x3D5

// function declarations
void print_at(const char* msg, int x, int y);
void clear_screen();
