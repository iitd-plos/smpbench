#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#ifdef TIMING_OUTPUT
#include <time.h>
#include <sys/time.h>
#endif
#include <string.h>
#include "cint/ctests_helper.h"

void __attribute__ ((noinline)) bitflip (int *array, unsigned int len) {
  for(unsigned int i = 0; i < len; ++i) {
    array[i] ^= 0xffffffff;
  }
}

size_t __attribute__ ((noinline)) strlen(const char* str) {
  const char* char_ptr = str;
  while(*char_ptr != '\0') {
    char_ptr++;
  }

  return (size_t)(char_ptr-str);
}

char *
strchrnul(const char *s, unsigned char c)
{
  char * ptr = s;
  for (; *ptr != c; ++ptr)
    if (*ptr == '\0')
      return (void *) ptr;
  return (char *) ptr;
}

int main() {
  return 0;
}
