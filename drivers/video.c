#include "video.h"

/** print msg at (x,y) */
void print_at(const char* msg, int x, int y){
  unsigned char *video = (unsigned char *)VIDEO_ADDRESS;
  unsigned int off=get_offset(x,y);
  unsigned int i=1;
  while(1){
        char c = msg[i];
        if(c==0)
          break;
        video[off] = c;
        video[off+1] = WHITE_ON_BLUE;
        off+=2;i++;
  }
}

/** wipe everything */
void clear_screen(){
  unsigned char *video = (unsigned char *)VIDEO_ADDRESS;
  int i,j;
  for(i=0;i<MAX_ROWS;i++){
    for(j=0;j<MAX_COLS;j++){
      unsigned int off = get_offset(i,j);
      video[off] = ' ';
      video[off+1] = WHITE_ON_BLUE;
    }
  }
}

/** get offset */
int get_offset(int row, int col){
  return (row*MAX_COLS+col)*2+1;
}
