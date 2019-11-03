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

int main() {
  return 0;
}
