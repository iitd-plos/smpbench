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

size_t __attribute__ ((noinline)) strlen(const char* str) {
  const char* char_ptr = str;
  while(*char_ptr != '\0') {
    char_ptr++;
  }

  return (size_t)(char_ptr-str);
}


int main() {
  return 0;
}
