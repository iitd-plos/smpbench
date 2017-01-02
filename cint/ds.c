#include <stdlib.h>
#include <limits.h>

#include "checkpoint.h"

//#include <msp430.h>
//#include "dino.h"
//#include "data_bins.h"
//#include "data_thresholds.h"

volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh0;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh1;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh2;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh3;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh4;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh5;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh6;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh7;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh8;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh9;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataThresh10;
unsigned __histo_read__NV_dataThresh(unsigned i){
  if( i == 0 ){
    return __NV_dataThresh0;
  }else if( i == 1 ){
    return __NV_dataThresh1;
  }else if( i == 2 ){
    return __NV_dataThresh2;
  }else if( i == 3 ){
    return __NV_dataThresh3;
  }else if( i == 4 ){
    return __NV_dataThresh4;
  }else if( i == 5 ){
    return __NV_dataThresh5;
  }else if( i == 6 ){
    return __NV_dataThresh6;
  }else if( i == 7 ){
    return __NV_dataThresh7;
  }else if( i == 8 ){
    return __NV_dataThresh8;
  }else if( i == 9 ){
    return __NV_dataThresh9;
  }else if( i == 10 ){
    return __NV_dataThresh10;
  }else { /*should never get here!*/ return 0; }
}
void __histo_write__NV_dataThresh(unsigned i,unsigned v){
  if( i == 0 ){
    __NV_dataThresh0 = v;
  }else if( i == 1 ){
    __NV_dataThresh1 = v;
  }else if( i == 2 ){
    __NV_dataThresh2 = v;
  }else if( i == 3 ){
    __NV_dataThresh3 = v;
  }else if( i == 4 ){
    __NV_dataThresh4 = v;
  }else if( i == 5 ){
    __NV_dataThresh5 = v;
  }else if( i == 6 ){
    __NV_dataThresh6 = v;
  }else if( i == 7 ){
    __NV_dataThresh7 = v;
  }else if( i == 8 ){
    __NV_dataThresh8 = v;
  }else if( i == 9 ){
    __NV_dataThresh9 = v;
  }else if( i == 10 ){
    __NV_dataThresh10 = v;
  }else { /*should never get here!*/ return; }
}

volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin0;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin1;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin2;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin3;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin4;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin5;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin6;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin7;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin8;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin9;
volatile __attribute__((section("FRAMVARS"))) unsigned int __NV_dataBin10;
unsigned __histo_read__NV_dataBin(unsigned i){
  if( i == 0 ){
    return __NV_dataBin0;
  }else if( i == 1 ){
    return __NV_dataBin1;
  }else if( i == 2 ){
    return __NV_dataBin2;
  }else if( i == 3 ){
    return __NV_dataBin3;
  }else if( i == 4 ){
    return __NV_dataBin4;
  }else if( i == 5 ){
    return __NV_dataBin5;
  }else if( i == 6 ){
    return __NV_dataBin6;
  }else if( i == 7 ){
    return __NV_dataBin7;
  }else if( i == 8 ){
    return __NV_dataBin8;
  }else if( i == 9 ){
    return __NV_dataBin9;
  }else if( i == 10 ){
    return __NV_dataBin10;
  }else { /*should never get here!*/ return 0; }
}
void __histo_write__NV_dataBin(unsigned i,unsigned v){
  if( i == 0 ){
    __NV_dataBin0 = v;
  }else if( i == 1 ){
    __NV_dataBin1 = v;
  }else if( i == 2 ){
    __NV_dataBin2 = v;
  }else if( i == 3 ){
    __NV_dataBin3 = v;
  }else if( i == 4 ){
    __NV_dataBin4 = v;
  }else if( i == 5 ){
    __NV_dataBin5 = v;
  }else if( i == 6 ){
    __NV_dataBin6 = v;
  }else if( i == 7 ){
    __NV_dataBin7 = v;
  }else if( i == 8 ){
    __NV_dataBin8 = v;
  }else if( i == 9 ){
    __NV_dataBin9 = v;
  }else if( i == 10 ){
    __NV_dataBin10 = v;
  }else { /*should never get here!*/ return; }
}











#define NUM_ITERS 100
#define SAMPLES_PER_ITER 20
#define NUM_BINS 10 /*total number of bins*/
#define SAMPLE_MAX 100 /*max expected value of a sample*/
#undef USE_LEDS
#undef FLASH_ON_BOOT

#define SAMPLE_TASK 0
#define BIN_TASK 1
#define SORT_TASK 2
#define CHECK_TASK 3
#define START_TASK 4
/*Need to calibrate to get real values for this*/
const unsigned thresholds[NUM_BINS] = {
  10, 20, 30, 40, 50, 60, 70, 80, 90, 0xffff /*last bin is for everything else*/
};

/* These "pinned" variables are fixed at these addresses. */

/*currTemp is a pointer to the current entry in the data log*/
volatile __attribute__((section("FRAMVARS"))) unsigned int inErrorState;
volatile __attribute__((section("FRAMVARS"))) unsigned int initialized;
volatile __attribute__((section("FRAMVARS"))) unsigned int finished;
volatile __attribute__((section("FRAMVARS"))) unsigned int reboots;
volatile __attribute__((section("FRAMVARS"))) unsigned int numSamples;
volatile __attribute__((section("FRAMVARS"))) unsigned int numSwaps;



/*dataLog is a buffer of TEMP_WINDOW NV data entries*/
/*defined in data_array.h, generated by dinoArrayGen.pl... ugh*/
unsigned getOneSample(){

  unsigned ret = rand() % SAMPLE_MAX;
  return ret;
   
}

void abortWithError(){
  
  inErrorState = 0xBEEE;  

//#if defined(WISP5)
//  P4OUT |= BIT0;
//#elif defined(BREADBOARD)
//  P1OUT |= BIT0;
//#endif //BREADBOARD
//
//  while(1){ }

}
 
/*We will use __NV_dataBin[] as a list of bins, each of which corresponds
  to a dataerature range.

  We will use __NV_dataThresh[] as a list of thresholds, each of which 
  is the upper bound of the data value in the corresponding dataBin bin

  NUM_BINS = 3
  thresholds [ 10 | 20 | 30 ]
  datathresh [  0 |  1 |  2 ] 
  databins   [  0 |  0 |  0 ]
 
  addToBin(15)
  
  thresholds [ 10 | 20 | 30 ]
  datathresh [  0 |  1 |  2 ] 
  databins   [  0 |  1 |  0 ]

  swapBins(0,1)
  
  thresholds [ 10 | 20 | 30 ]
  datathresh [  1 |  0 |  2 ] <--entry 0 contains "1", a pointer to "20"
  databins   [  1 |  0 |  0 ] <--entry 0 contains "1", the count for "20"


  and so on.


  Invariant: datas that contribute to the value in __NV_dataBin[i]
             were less than __NV_dataBin[i] when they were recorded.
  
             each entry in thresholds occurs in exactly one location in
             __NV_dataThresh[].

*/
void addToBin(unsigned data){

  /*Fill this out so we pass a value in and get a bin back*/
  unsigned i;
  unsigned thresh = 0xffff;
  for( i = 0; i < NUM_BINS; i++){

    /*Look through the sorted list of histogram thresholds...*/
    if( data < thresholds[i] ){

      /*thresholds[i] is the threshold for this measurment*/
      thresh = thresholds[i];
      break;

    }

  } 

  unsigned j; 
  /*Find this threshold in the unsorted list of histogram keys*/
  for( j = 0; j < NUM_BINS; j++ ){

    unsigned tInd = __histo_read__NV_dataThresh(j);//the index for this key 
    unsigned t = thresholds[tInd];//the key itself

    /*This key (t) matches the threshold 
      for this measurement (thresholds[i]).*/
    if( t == thresh ){

      /*Increment the found key's bin's value*/
      unsigned binVal = __histo_read__NV_dataBin(j);
      __histo_write__NV_dataBin(j, binVal+1);

      return;

    }

  }

  /*If we get here, the measurement has no bin in
    the histogram, which is an error*/
  abortWithError();

}

void swapBins(int binI, int binJ){

  if(binI >= NUM_BINS ||
     binJ >= NUM_BINS ){
    return;
  }
  numSwaps++;
  unsigned tmpBinVal = __histo_read__NV_dataBin(binI);
  unsigned tmpThrVal = __histo_read__NV_dataThresh(binI);
  
  __histo_write__NV_dataThresh(binI, __histo_read__NV_dataThresh(binJ)); 
  __histo_write__NV_dataBin(binI, __histo_read__NV_dataBin(binJ)); 
  /*A failure here leaves the data structure corrupted!*/
  __histo_write__NV_dataBin(binJ, tmpBinVal); 
  __histo_write__NV_dataThresh(binJ, tmpThrVal); 
   
}

void sortBinsByFrequency(void){

  unsigned i = 0;
  for( i = 1; i < NUM_BINS; i++ ){
   
    unsigned j = i;
    while( j > 0 && __histo_read__NV_dataBin(j - 1) > 
                    __histo_read__NV_dataBin(j) ) {

        swapBins(j,j-1);
        j--;

    }

  }

}  


void checkInvariants(void){

  unsigned i;
  unsigned numKeysFound = 0;
  unsigned keysFound[NUM_BINS];
  for( i = 0; i < NUM_BINS; i++ ){
    keysFound[i] = 0;
  }
  for( i = 0; i < NUM_BINS; i++ ){

    unsigned key = __histo_read__NV_dataThresh(i);

    if( keysFound[key] == 0 ){

      keysFound[key] = 1;
      numKeysFound++;
          
    }else{
      abortWithError();
    }

  }


  if( numKeysFound < NUM_BINS ){
      abortWithError();
  }

}


//void initializeHardware(){
//  
//#ifdef WISP5
//  setupDflt_IO();
//
//  PRXEOUT |= PIN_RX_EN; /** TODO: enable PIN_RX_EN only when needed in the future */
//
//
//  /*Before anything else, do the device hardware configuration*/
//  P4DIR |= BIT0;
//  PJDIR |= BIT6;
//#if defined(USE_LEDS) && defined(FLASH_ON_BOOT)
//  P4OUT |= BIT0;
//  PJOUT |= BIT6;
//  int i;
//  for (i = 0; i < 0xffff; i++)
//    ;
//  P4OUT &= ~BIT0;  // Toggle P4.4 using exclusive-OR
//  PJOUT &= ~BIT6;  // Toggle P4.5 using exclusive-OR
//#endif /*USE LEDS*/
//#endif /*WISP5*/
//
//#ifdef BREADBOARD
//  P1DIR |= BIT0;
//  P4DIR |= BIT4;// Set P4.4/5 to output direction
//  P1OUT &= ~BIT0;  
//  P4OUT &= ~BIT4;  
//#if defined(USE_LEDS) && defined(FLASH_ON_BOOT)
//  P1OUT |= BIT0;
//  P4OUT |= BIT4;
//  int i;
//  for (i = 0; i < 0xffff; i++)
//    ;
//  P1OUT &= ~BIT0;  
//  P4OUT &= ~BIT4;  
//#endif //USE LEDS
//
//#endif /*BREADBOARD*/
//
//}



void initializeNVData() {
  if(initialized != 0xBEEE){
    for(int i = 0; i < NUM_BINS; i++){
      __histo_write__NV_dataBin(i,0x0);
      /*The bin corresponding to the ith 
        threshold is in the ith position to start*/
      __histo_write__NV_dataThresh(i,i);
      
    }
    reboots = 0;
    numSamples = 0;
    numSwaps = 0;
    initialized = 0xBEEE;
  }
}

__attribute__((section(".init9"), aligned(2)))
int main(void){

//  WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
//  PM5CTL0 &= ~LOCKLPM5;
//  initializeHardware();
  reboots++;
  //DINO_RESTORE_CHECK();

  //DINO_TASK_BOUNDARY(START_TASK,NULL);
  CHECKPOINT;
//  if( finished == 0xBEEE ){
//#if defined(WISP5)
//    PJOUT |= BIT6;
//#elif defined(BREADBOARD)
//    P4OUT |= BIT4;
//#endif
//    while( 1 ){ }
//  }

  if( inErrorState == 0xBEEE ){

    abortWithError();

  }

  initializeNVData();
  

  while( numSamples < (NUM_ITERS * SAMPLES_PER_ITER) ){

    int r;
    for(r = 0; r < SAMPLES_PER_ITER; r++){

      //DINO_TASK_BOUNDARY(SAMPLE_TASK,NULL);
      CHECKPOINT;
      unsigned samp = getOneSample();
      //DINO_TASK_BOUNDARY(BIN_TASK,NULL);
      CHECKPOINT;
      addToBin(samp);
      numSamples++;

    }

    //DINO_TASK_BOUNDARY(SORT_TASK,NULL);
    CHECKPOINT;
    sortBinsByFrequency();

    //DINO_TASK_BOUNDARY(CHECK_TASK,NULL);
    CHECKPOINT;
    checkInvariants();

  }

  finished = 0xBEEE;
//#if defined(WISP5)
//  PJOUT |= BIT6;
//#elif defined(BREADBOARD)
//  P4OUT |= BIT4;
//#endif
//  while( 1 ){ }

}
