
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
#define NUM_ITER 10240
//#define NUM_ITER 1
#include "stopwatch.h"
#include "str_op_macros.h"

int
array_cmpl_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPL_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpl(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPL_NOITER(a, b, n, ret);
  }
  return ret;
}

int
main (int argc, char **argv)
{
  char *s, *s2, *s3, *p, *p2, *p3;
  size_t slen, slen2;
  long s_size = 1234567;
  s = (char *)malloc(s_size * sizeof(char));
  assert(s);
  s2 = (char *)malloc(s_size * sizeof(char));
  assert(s2);
  s3 = (char *)malloc(s_size * sizeof(char));
  assert(s3);
  for (p = s, p2 = s2, p3 = s3; (p - s) < s_size; p++, p2++, p3++) {
    *p = ((p - s) % 26) + 'a';
    assert(*p != 0);
    *p2 = ((p2 - s2) % 26) + 'a';
    assert(*p2 != 0);
    *p3 = ((p3 - s3) % 26) + 'a';
    assert(*p3 != 0);
  }
  s[0] = '/'; s2[0] = '/'; s3[0] = '/'; //have a different zero'th elem, so that reverse search traverses the full array
  s[1] = ';'; s2[1] = ';'; s3[1] = ';';
  slen = s_size;//strlen(s);
  //s = argv[2];
  //slen = strlen(s);
  s[slen - 1] = '\0';
  s[slen - 2] = '\0';
  s[slen - 3] = '\0';
  s[slen - 4] = '\0';
  s[slen - 5] = '\0';
  s[slen - 6] = '\0';
  s[slen - 7] = '\0';
  s[slen - 8] = '\0';
  s[slen - 9] = '\0';
  s[slen - 10] = '\0';
  s[slen - 11] = '\0';
  s[slen - 12] = '\0';
  s[slen - 13] = '\0';
  s[slen - 14] = '\0';
  s[slen - 15] = '\0';
  s[slen - 16] = '\0';

  slen2 = s_size;
  s2[slen2 - 1] = '\0';
  s2[slen2 - 2] = '\0';
  s2[slen2 - 3] = '\0';
  s2[slen2 - 4] = '\0';
  s2[slen2 - 5] = '\0';
  s2[slen2 - 6] = '\0';
  s2[slen2 - 7] = '\0';
  s2[slen2 - 8] = '\0';
  s2[slen2 - 9] = '\0';
  s2[slen2 - 10] = '\0';
  s2[slen2 - 11] = '\0';
  s2[slen2 - 12] = '\0';
  s2[slen2 - 13] = '\0';
  s2[slen2 - 14] = '\0';
  s2[slen2 - 15] = '\0';
  s2[slen2 - 16] = '\0';

  struct time array_cmpl_timer;
  stopwatch_reset(&array_cmpl_timer);
  stopwatch_run(&array_cmpl_timer);
  int cmp1l = array_cmpl(s, s2, slen/4);
  stopwatch_stop(&array_cmpl_timer);

  printf("output = %d\n", cmp1l);
  stopwatch_print(&array_cmpl_timer);

  cmp1l = array_cmpl(s, &s2[1], slen);
  printf("unequal comparison: cmp1l = %d\n", cmp1l);
  return 0;
}
