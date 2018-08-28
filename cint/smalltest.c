#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdbool.h>

//const char interp_section[] __attribute__((section(".interp"))) = "/path/to/dynamic/linker";

int sum_positive_g[144];
int sum_positive_sum = 0;
int sum_positive_const = 123;

void sum_positive_globals(int n) {
  int *ptr = sum_positive_g;
  int i;
  for (i = 0; i < n; i++, ptr++) {
    if (*ptr > 0) {
      sum_positive_sum = sum_positive_sum + sum_positive_const * (*ptr);
    }
  }
}
int main()
{
  printf("start tests\n");
  sum_positive_globals(100);
  printf("finished\n");
  return 0;
}
