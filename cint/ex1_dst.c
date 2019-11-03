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
  unsigned i=0;
  while((len-i)%4 != 0) {
    array[i]^= 0xFFFFFFFF;
    i++;
  }
  while(i < len)
  {
    array[i]  ^= 0xFFFFFFFF;
    array[i+1]^= 0xFFFFFFFF;
    array[i+2]^= 0xFFFFFFFF;
    array[i+3]^= 0xFFFFFFFF;
    i += 4;
  }
}

int main() {
  return 0;
}
