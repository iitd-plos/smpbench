#include "stdio.h"

#define CP_MAGIC 7524

int check_pt(int magic, int num_NV, int num_V, ...)
{
  printf("Inside Check Point -- Num NV vars = %d Num V vars = %d \n",num_NV, num_V);
}


#define CHECKPOINT check_pt(CP_MAGIC, 0, 0)

