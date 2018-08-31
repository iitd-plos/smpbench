#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MERGE(l,r,u) do { \
  int ii,jj,kk; \
  ii=l; jj=r; kk=l; \
  while (ii<r && jj<u) { \
    if (a[ii-1]<=a[jj-1]) {b[kk-1]=a[ii-1]; ii++;}  \
    else {b[kk-1]=a[jj-1]; jj++;} \
    kk++; \
  } \
  while (ii<r) {  \
    b[kk-1]=a[ii-1]; ii++; kk++; \
  } \
  while (jj<u) {  \
    b[kk-1]=a[jj-1]; jj++; kk++; \
  } \
  for (kk=l; kk<u; kk++) {  \
    a[kk-1]=b[kk-1];  \
  } \
} while (0)

int
main(int argc, char **argv)
{
  int len = 0xc00000;
  if (argc >= 2) {
    len = atoi(argv[1]);
  }

  long *a = (long *) malloc (len*sizeof(long));
  long *b = (long *) malloc (len*sizeof(long));
  if (!a || !b) {
    printf("%s(): array allocation of size %d failed.\n", __func__, len);
    return 1;
  }

  int i;

  srand48 (0x12345678);

  for (i = 0; i < len; i++) {
    a[i] = lrand48();
  }

  if (len <= 10) {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++)
      printf ("a[%d] = %ld\n", i, a[i]);
  }

  int k,u;
  k=1;
  while (k<len) {
    i=1;
    while (i+k<=len) {
      u=i+k*2;
      if (u>len) u=len+1;
      int t = i + k;
      MERGE(i,t,u);
      i=i+k*2;
    }
    k=k*2;
  }

  if (len <= 10) {
    printf ("Printing Sorted array:\n");
    for (i = 0; i < len; i++) {
      printf("b[%d] = %ld\n", i, b[i]);
    }
  }
  printf("min element = %ld.\n", b[0]);
  printf("median element = %ld.\n", b[len / 2]);
  printf("max element = %ld.\n", b[len - 1]);

  return 0;
}
