#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

//#define MAX_LEN 0x800000

//static uint8_t a[MAX_LEN];

int
main(int argc, char **argv)
{
  long len = 0x9000;
  if (argc >= 2) {
    len = atoi(argv[1]);
  }

  long *a = (long *)malloc(len*sizeof(long));
  if (!a) {
    printf("%s(): array allocation of size %ld failed.\n", __func__, len);
    return 1;
  }

  int i, j;
  srand48 (0x12345678);

  for (i = 0; i < len; i++) {
    a[i] = lrand48();
  }

  if (len <= 10) {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++)
      printf ("a[%d] = %ld\n", i, a[i]);
  }

  for (i = 0; i < len; i++) {
    for (j = 0; j < len - i - 1; j++) {
      if (a[j] > a[j+1]) {
        long tmp = a[j+1];
        a[j+1] = a[j];
        a[j] = tmp;
      }
    }
  }

  if (len <= 10) {
    printf ("Printing Sorted array:\n");
    for (i = 0; i < len; i++)
      printf ("a[%d] = %ld\n", i, a[i]);
  }
  printf("max element = %ld\n", a[len - 1]);

  return 0;
}
