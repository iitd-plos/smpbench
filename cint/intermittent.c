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


int __NV_c1 =0 , __NV_c2 = 0, __NV_total = 0;

int check_pt(int num_NV, int num_V, ...)
{
    printf("Inside Check Point -- Num NV vars = %d Num V vars = %d \n",num_NV, num_V);

}

int main_exp1(){
 int s,c;
 s = rand()%2;
 check_pt(0,2,&s,sizeof(s),&c,sizeof(c));
 if( s == 0 ){
 check_pt(0,2,&s,sizeof(s),&c,sizeof(c));
 __NV_c1++;
 }
 else{
 check_pt(0,2,&s,sizeof(s),&c,sizeof(c));
   __NV_c2++;
 }
 __NV_total++;
 assert(__NV_total==__NV_c1+__NV_c2);
return 0;
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
  printf("main_exp1() = %d\n", main_exp1());
  return 1;
}
