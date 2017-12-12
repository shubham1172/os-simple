/**
* Kernel code
*/
#include "../drivers/screen.h"

int main(){

  /**unsigned char *video = (unsigned char *)0xb8000;
  const char* msg = "This is a message";
  const char color = 0x1f;
  unsigned int off=0; unsigned int i=1;
  while(1){
        char c = msg[i];
        if(c==0)
          break;
        video[off+1] = c;
        video[off+2] = color;
        off+=2;i++;
  }*/
  char msg = 'A';
  char attr = 0xf0;
  print_char(msg, 0, 0, attr);
  return 0;
}
