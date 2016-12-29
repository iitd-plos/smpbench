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

#define CP_MAGIC 7524

int __NV_c1 =0 , __NV_c2 = 0, __NV_total = 0;

int check_pt(int magic, int num_NV, int num_V, ...)
{
    printf("Inside Check Point -- Num NV vars = %d Num V vars = %d \n",num_NV, num_V);

}

int check_pt1(int magic, int num_NV, int num_V, void* v, unsigned s)
{
  printf("Inside Check Point -- Num NV vars = %d Num V vars = %d \n",num_NV, num_V);
}

int check_pt2(int magic, int num_NV, int num_V, void* v1, unsigned s1, void* v2, unsigned s2)
{
  printf("Inside Check Point -- Num NV vars = %d Num V vars = %d \n",num_NV, num_V);
}

int check_pt21(int magic, int num_NV, int num_V, void* v1, unsigned s1, void* v2, unsigned s2, void* v3, unsigned s3)
{
  printf("Inside Check Point -- Num NV vars = %d Num V vars = %d \n",num_NV, num_V);
}

int check_pt31(int magic, int num_NV, int num_V, void* v1, unsigned s1, void* v2, unsigned s2, void* v3, unsigned sv3, void* v4, unsigned sv4)
{
  printf("Inside Check Point -- Num NV vars = %d Num V vars = %d \n",num_NV, num_V);
}

int main_exp0()
{
  int a = 5;
  check_pt1(CP_MAGIC, 0, 1, &a, sizeof(a));
  ++a;
  return a;
}

int main_exp01()
{
  int a = 5;
  check_pt2(CP_MAGIC, 1, 1, &__NV_c1, sizeof(__NV_c1), &a, sizeof(a));
  ++a;
  __NV_c1++;
  return a + __NV_c1;
}

int main_exp1(){
 int s;
 s = rand()%2;
 check_pt31(CP_MAGIC, 3, 1, &__NV_total, sizeof(__NV_total), &__NV_c1, sizeof(__NV_c1), &__NV_c2, sizeof(__NV_c2), &s, sizeof(s));
 if( s == 0 ){
 check_pt31(CP_MAGIC, 3, 1, &__NV_total, sizeof(__NV_total), &__NV_c1, sizeof(__NV_c1), &__NV_c2, sizeof(__NV_c2), &s, sizeof(s));
 __NV_c1++;
 }
 else{
 check_pt31(CP_MAGIC, 3, 1, &__NV_total, sizeof(__NV_total), &__NV_c1, sizeof(__NV_c1), &__NV_c2, sizeof(__NV_c2), &s, sizeof(s));
   __NV_c2++;
 }
 __NV_total++;
 //assert(__NV_total==__NV_c1+__NV_c2);
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
  printf("main_exp1() = %d\n", main_exp1());
  return 1;
}
