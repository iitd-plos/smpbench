#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <assert.h>
#define ASSERT assert
#define TRUE	1
#define FALSE	0
#define NOT_IMPLEMENTED() assert(0)


int
foo(int a)
{
  return 2*a + 1;
}

int
main(int argc, char **argv)
{
  printf("foo(1) = %d\n", foo(1));
  return 1;
}
