#include <string.h>
#include <stdio.h>
//#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

void relu(long *a, long len)
{
  int i;
  for (i = 0; i < len; i++) {
    if (a[i] < 0) {
      a[i] = 0;
    }
  }
}

//int
//my_lrand()
//{
//  static int seed = 0x234123;
//  seed = (seed * 2311) % 1235;
//  return seed;
//}

int
main(int argc, char **argv)
{
  long len = 0x90000;
  if (argc >= 2) {
    len = atoi(argv[1]);
  }

  long *a = (long *)malloc(len*sizeof(long));
  if (!a) {
    printf("%s(): array allocation of size %ld failed.\n", __func__, len);
    return 1;
  }

  srand48(0x12345678);

  for (int i = 0; i < len; i++) {
    a[i] = lrand48();
  }

  relu(a, len);
  int i = lrand48() % len;
  printf("a[%d] = %ld\n", i, a[i]);
  for (i = 0; i < 2000; i++) {
    relu(a, len);
  }
  printf("a[%d] = %ld\n", i, a[i]);
  return 0;
}
