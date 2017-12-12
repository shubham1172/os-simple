/**
* Screen driver header file
*/
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// default color scheme
#define WHITE_ON_BLACK 0x0f
// screen device I/O ports
#define REG_SCREEN_CONTROL 0x3D4
#define REG_SCREEN_DATA 0x3D5

// function declarations
void print_at(char* message, int col, int row);
void print(char* message);
void clear_screen();
