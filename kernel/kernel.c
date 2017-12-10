/**
* Kernel code
*/

void main(){
  // Create a pointer to video memory
  char* video_memory = (char*) 0xb8000;
  // Display a X at top-left corner
  *(video_memory+100) = "X";
}
