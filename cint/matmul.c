#include <string.h>
#include <stdio.h>
//#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

void matmul(long *c, long const *a, long const *b, long len)
{
  int i, j, k;
  for (i = 0; i < len; i++) {
    for (j = 0; j < len; j++) {
      c[i*len + j] = 0;
      for (k = 0; k < len; k++) {
        c[i*len + j] += a[i*len + k] * b[k*len + j];
      }
    }
  }
}


int
main(int argc, char **argv)
{
  long len = 0x300;
  if (argc >= 2) {
    len = atoi(argv[1]);
  }

  long *a = (long *)malloc(len*len*sizeof(long));
  if (!a) {
    printf("%s(): array allocation of size %ld failed.\n", __func__, len*len);
    return 1;
  }
  long *b = (long *)malloc(len*len*sizeof(long));
  if (!b) {
    printf("%s(): array allocation of size %ld failed.\n", __func__, len*len);
    return 1;
  }
  long *c = (long *)malloc(len*len*sizeof(long));
  if (!c) {
    printf("%s(): array allocation of size %ld failed.\n", __func__, len*len);
    return 1;
  }


  srand48(0x12345678);

  for (int i = 0; i < len*len; i++) {
    a[i] = lrand48();
    b[i] = lrand48();
  }

  matmul(c, a, b, len);
  int i = lrand48() % len;
  int j = lrand48() % len;
  printf("c[%d,%d] = %ld\n", i, j, c[i*len + j]);

  for (int i = 0; i < 4; i++) matmul(c, c, a, len);
  printf("c[%d,%d] = %ld\n", i, j, c[i*len + j]);
  return 0;
}
