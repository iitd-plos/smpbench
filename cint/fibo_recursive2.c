#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

static unsigned long compute_fibo_rec2(unsigned int n);
static unsigned long
compute_fibo_rec2_helper(unsigned int n)
{
  if (n < 3) {
    return 1;
  }
  return (compute_fibo_rec2(n - 1) + compute_fibo_rec2(n - 2));
}

static unsigned long
compute_fibo_rec2(unsigned int n)
{
  if (n < 3) {
    return 1;
  }
  return (compute_fibo_rec2_helper(n - 1) + compute_fibo_rec2_helper(n - 2));
}

int
main(int argc, char **argv)
{
  unsigned int n = 45;
  if (argc >= 2) {
    n = atoi(argv[1]);
  }
  unsigned long ret = compute_fibo_rec2(n);
  printf("%lu\n", ret);
  return 0;
}
