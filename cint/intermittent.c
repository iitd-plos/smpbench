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

#include "checkpoint.h"

int __NV_c1 =0 , __NV_c2 = 0, __NV_total = 0;

int main_exp0()
{
  int a = 5;
  CHECKPOINT;
  ++a;
  return a;
}

int main_exp01()
{
  int a = 5;
  CHECKPOINT;
  ++a;
  return a + __NV_c1;
}

int main_exp02()
{
  int a = 5;
  CHECKPOINT;
  ++a;
  __NV_c1++;
  return a + __NV_c1;
}

int main_exp03()
{
  int a = 5;
  ++a;
  int b = __NV_c1;
  CHECKPOINT;
  ++b;
  __NV_c1 = b;
  return a + __NV_c1;
}

int main_exp1(){
 int s;
 s = rand()%2;
  CHECKPOINT;
 if( s == 0 ){
  CHECKPOINT;
 __NV_c1++;
 }
 else{
  CHECKPOINT;
   __NV_c2++;
 }
 __NV_total++;
  return __NV_total+__NV_c1+__NV_c2+s;
}

int
foo(int a)
{
  return 2*a + 1;
}

int
main(int argc, char **argv)
{
  printf("foo(1) = %d\n", foo(1));
  printf("main_exp0() = %d\n", main_exp0());
  printf("main_exp0() = %d\n", main_exp01());
  printf("main_exp0() = %d\n", main_exp02());
  printf("main_exp0() = %d\n", main_exp03());
  printf("main_exp1() = %d\n", main_exp1());
  return 1;
}
