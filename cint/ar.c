#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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

#define DO_RECOVERY
#define LOW_POWER
#define MODEL_SIZE 100
#define NUM_FEATURES 2
#define ACCEL_WINDOW_SIZE 3

static float stationary[MODEL_SIZE];
static float walking[MODEL_SIZE]; 

unsigned int __NV_walkingCount;
unsigned int __NV_stationaryCount;
unsigned int __NV_totalCount;
#define CP_MAGIC 7524

typedef int accelReading[3];
typedef accelReading accelWindow[ACCEL_WINDOW_SIZE];

static accelWindow aWin;
static int currSamp = 0;

static accelReading mean;
static accelReading stddev;

static int meanmag;
static int stddevmag;

static int initial;

#define MODEL_COMPARISONS 10
#define PROCESSING_TASK 0
#define UPDATE_COUNTS_TASK 1

int check_pt(int magic, int num_NV, int num_V, ...)
{
  printf("Inside Check Point -- Num NV vars = %d Num V vars = %d \n",num_NV, num_V);
}

#define CHECKPOINT check_pt(CP_MAGIC, 0, 0)


int main_ar() 
{
//  __NV_walkingCount = &initial;
//  __NV_stationaryCount = &initial;
//  __NV_totalCount = &initial;
  
  // DINO_RESTORE_CHECK()
  
    // DINO_TASK_BOUNDARY(PROCESSING_TASK,NULL) 
    CHECKPOINT;
     
    __NV_walkingCount = 0;
    __NV_stationaryCount = 0;
    __NV_totalCount = 0;

    int x = 10;
    int y = 10;
    int z = 10;

    aWin[currSamp][0] = x;
    aWin[currSamp][1] = y;
    aWin[currSamp][2] = z;
    currSamp = (currSamp + 1) % ACCEL_WINDOW_SIZE;

    
    mean[0] = mean[1] = mean[2] = 0;
    stddev[0] = stddev[1] = stddev[2] = 0;
    int i;
    for(i = 0; i < ACCEL_WINDOW_SIZE; i++){
      mean[0] = mean[0] + aWin[i][0];//x
      mean[1] = mean[1] + aWin[i][1];//y
      mean[2] = mean[2] + aWin[i][2];//z
    }
    mean[0] = mean[0] / ACCEL_WINDOW_SIZE;
    mean[1] = mean[1] / ACCEL_WINDOW_SIZE;
    mean[2] = mean[2] / ACCEL_WINDOW_SIZE;

    for(i = 0; i < ACCEL_WINDOW_SIZE; i++){
      stddev[0] += aWin[i][0] > mean[0] ? aWin[i][0] - mean[0] : mean[0] - aWin[i][0];//x
      stddev[1] += aWin[i][1] > mean[1] ? aWin[i][1] - mean[1] : mean[1] - aWin[i][1];//x
      stddev[2] += aWin[i][2] > mean[2] ? aWin[i][2] - mean[2] : mean[2] - aWin[i][2];//x
    }
    stddev[0] = stddev[0] / (ACCEL_WINDOW_SIZE-1);
    stddev[1] = stddev[1] / (ACCEL_WINDOW_SIZE-1);
    stddev[2] = stddev[2] / (ACCEL_WINDOW_SIZE-1);
   
    meanmag = mean[0] + mean[1] + mean[2] / 3;
    stddevmag = stddev[0] + stddev[1] + stddev[2] / 3;

    int class; 

    int walk_less_error = 0;
    int stat_less_error = 0;
    int stat_mean_err;
    int stat_sd_err;
    int walk_mean_err;
    int walk_sd_err;
    
    for( i = 0; i < MODEL_COMPARISONS; i+=NUM_FEATURES ){

      stat_mean_err = (stationary[i] > meanmag) ?
                            (stationary[i] - meanmag) :
                            (meanmag - stationary[i]);

      stat_sd_err = (stationary[i+1] > stddevmag) ?
                            (stationary[i+1] - stddevmag) :
                            (stddevmag - stationary[i+1]);
      
      walk_mean_err = (walking[i] > meanmag) ?
                            (walking[i] - meanmag) :
                            (meanmag - walking[i]);

      walk_sd_err =   (walking[i+1] > stddevmag) ?
                            (walking[i+1] - stddevmag) :
                            (stddevmag - walking[i+1]);

      if( walk_mean_err < stat_mean_err ){
        walk_less_error ++;
      }else{
        stat_less_error ++;
      }

      if( walk_sd_err < stat_sd_err ){
        walk_less_error ++;
      }else{
        stat_less_error ++;
      }
      
    }

    if(walk_less_error > stat_less_error ){
      class = 1;
    }else{
      class = 0;
    }
   
  //  DINO_TASK_BOUNDARY(UPDATE_COUNTS_TASK,&DINO_VERSION_totalCount,&DINO_VERSION_statCount,&DINO_VERSION_walkCount) 
    CHECKPOINT;

    /*totalCount, walkingCount, and stationaryCount 
    have an nv-internal consistency requirement.
    This code should be atomic.
    */

    (__NV_totalCount)++;
    printf("Hi\n");
    int q;
    for(q = 0; q < 0xFF; q++);

    if(class){
     (__NV_walkingCount)++;
    }else{
      (__NV_stationaryCount)++;
    }

    return 1;

  
  
}


int main(int argc, char **argv)
{
  printf("main_ar() = %d\n", main_ar());
  return 1;
}
