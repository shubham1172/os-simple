/**
* Screen driver file
*/
#include "screen.h"

/**
* After numerous attempts to solve a bug, I finally noticed that
* vidmem[0] is not working. So char goes in vidmem[1] and attr
* goes in vidmem[2]. Strange! :/
*/

void print_char(char character, int col, int row, char attribute_byte);
int get_screen_offset(int col, int row);
int get_cursor();
void set_cursor(int offset);
int handle_scrolling(int cursor_offset);

// print a character at (col,row) or at cursor position
void print_char(char character, int col, int row, char attribute_byte){
  // pointer to start of memory
  volatile unsigned char *vidmem = (volatile unsigned char *)VIDEO_ADDRESS;
  // default attribute
  if(!attribute_byte){
    attribute_byte = WHITE_ON_BLACK;
  }
  // video memory offset for screen location
  unsigned int offset;
  if(col>=0 && row>=0)
    offset = get_screen_offset(col, row);
  else
    offset = get_cursor();
  // print character
  if(character=='\n'){
    // set offset to last column of this row
    int curr_row = offset/(2*MAX_COLS);
    offset = get_screen_offset(MAX_COLS-1, curr_row);
  }else{
    vidmem[offset] = character;
    vidmem[offset+1] = attribute_byte;
  }
  // update the offset
  offset+=2;
  // handle scroll
  offset = handle_scrolling(offset);
  // update cursor position
  set_cursor(offset);
}

// returns offset for a location
int get_screen_offset(int col, int row){
  return (row*MAX_COLS+col)*2+1;
}

// get the current cursor location as offset
int get_cursor(){
  // reg 14: higher byte of cursor's offset
  // reg 15: lower byte of cursor's offset
  port_byte_out(REG_SCREEN_CONTROL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA)<<8;
  port_byte_out(REG_SCREEN_CONTROL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  // convert characters to offset
  return offset*2;
}

// set the cursor position
void set_cursor(int offset){
  // convert offset to characters
  offset/=2;
  port_byte_out(REG_SCREEN_CONTROL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset>>8));
  port_byte_out(REG_SCREEN_CONTROL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset-(offset>>8)<<8));
}

// print a message at (col, row)
void print_at(char* message, int col, int row){
  // update cursor if col and row are not negative
  if(col>=0 && row>=0)
    set_cursor(get_screen_offset(col, row));
  int i=2;
  char c = message[1];
  print_char(c, col, row, WHITE_ON_BLACK);
  while(1){
    c = message[i];
    if(c==0)
      break;
    print_char(c, -1, -1, WHITE_ON_BLACK);
    i++;
  }
}

// print at cursor location
void print(char* message){
  print_at(message, -1, -1);
}

// clear the screen
void clear_screen(){
  int row, col;
  for(row=0;row=MAX_ROWS;row++)
    for(col=0;col<MAX_COLS;col++)
      print_char(' ', col, row, WHITE_ON_BLACK);

  set_cursor(get_screen_offset(0, 0));
}

// handle_scrolling
int handle_scrolling(int cursor_offset){
  // if cursor is within offset, no changes
  if(cursor_offset<MAX_COLS*MAX_ROWS*2)
    return cursor_offset;

  // shift back rows
  int i;
  for(int i=1;i<MAX_ROWS;i++){
    memory_copy(get_screen_offset(0,i)+VIDEO_ADDRESS,
                get_screen_offset(0,i-1)+VIDEO_ADDRESS,
                MAX_COLS*2
    );
  }
  // clear last line
  char* last_line = get_screen_offset(0, MAX_ROWS-1)+VIDEO_ADDRESS;
  for(i=0;i<MAX_COLS*2;i++){
    last_line[i]=0;
  }

  //move back the cursor
  cursor_offset-=2*MAX_COLS ;

  return cursor_offset;
}
