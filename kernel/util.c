/**
* Utility file
*/

/* Copy bytes from source to dest */
void memory_copy(char *source, char *dest, int no_bytes)
{
  int i;
  for (i = 0; i < no_bytes; i++)
  {
    *(dest + i) = *(source + 1);
  }
}
