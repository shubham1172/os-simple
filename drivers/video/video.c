/**
* Display device driver
*/
#include "video.h"
#include "../io/port_controller.h"

int get_offset(int row, int col);
int get_cursor();
void update_cursor(int offset);

/** print msg at (x,y) or cursor */
void print_at(const char *msg, int x, int y)
{
    unsigned char *video = (unsigned char *)VIDEO_ADDRESS;
    unsigned int offset = 0, i = 0;
    // decide offset value
    if (x >= 0 || y >= 0)
    {
        // get offset from coordinates
        offset = get_offset(x, y);
    }
    else
    {
        // get cursor
        offset = get_cursor();
    }
    while (1)
    {
        char c = msg[i];
        if (c == 0)
            break;
        video[offset] = c;
        video[offset + 1] = WHITE_ON_BLUE;
        offset += 2;
        i++;
    }
    update_cursor(offset);
}

/** print msg at cursor position */
void print(const char *msg)
{
    print_at(msg, -1, -1);
}

/** wipe everything */
void clear_screen()
{
    unsigned char *video = (unsigned char *)VIDEO_ADDRESS;
    int i, j;
    for (i = 0; i < MAX_ROWS; i++)
    {
        for (j = 0; j < MAX_COLS; j++)
        {
            unsigned int off = get_offset(i, j);
            video[off] = ' ';
            video[off + 1] = WHITE_ON_BLUE;
        }
    }
}

/** get offset */
int get_offset(int row, int col)
{
    return (row * MAX_COLS + col) * 2;
}

/** CURSOR FUNCTIONS */

/** disable cursor */
void disable_cursor()
{
    port_byte_out(REG_SCREEN_CONTROL, 0x0A);
    port_byte_out(REG_SCREEN_DATA, 0x20);
}

/** enable cursor with scanlines (need to check on them) */
void enable_cursor(int cursor_start, int cursor_end)
{
    port_byte_out(REG_SCREEN_DATA, 0x0A);
    port_byte_out(REG_SCREEN_CONTROL, (port_byte_in(0x3DF) & 0xC0) | cursor_start);

    port_byte_out(REG_SCREEN_DATA, 0x0B);
    port_byte_out(REG_SCREEN_CONTROL, (port_byte_in(0x3E0) & 0xE0) | cursor_end);
}

/** wraparound for enable_cursor */
void enable_cursor_simple()
{
    enable_cursor(0, 0);
}

/** update the postion of cursor */
void update_cursor(int offset)
{
    // get position
    int pos = offset / 2;
    // update registers 14,15
    port_byte_out(REG_SCREEN_CONTROL, 15);
    port_byte_out(REG_SCREEN_DATA, (pos & 0xFF));
    port_byte_out(REG_SCREEN_CONTROL, 14);
    port_byte_out(REG_SCREEN_DATA, (pos >> 8) & 0xFF);
}

/** get current cursor value as offset */
int get_cursor()
{
    int pos = 0;
    // read from the registers
    port_byte_out(REG_SCREEN_CONTROL, 15);
    pos += port_byte_in(REG_SCREEN_DATA);
    port_byte_out(REG_SCREEN_CONTROL, 14);
    pos += (port_byte_in(REG_SCREEN_DATA) << 8);
    return pos * 2;
}
