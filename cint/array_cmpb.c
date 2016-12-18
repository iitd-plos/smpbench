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

struct time {
  long long num_starts;
  int		running ;
//  int		flags ;
  
  long long	wallClock_start ;
//  long long	processor_start ;
//  long long	clockticks_start ;	/* CLOCK TICKS, not USECS */
//  long long	user_start ;
//  long long	system_start ;
  
  long long	wallClock_elapsed ;
//  long long	processor_elapsed ;
//  long long	clockticks_elapsed ;	/* CLOCK TICKS, not USECS */
//  long long	user_elapsed ;
//  long long	system_elapsed ;
};

void stopwatch_reset(struct time *timer);
int stopwatch_run(struct time *timer);
void stopwatch_stop(struct time *timer);
void stopwatch_print(struct time *timer);

#include "str_op_macros.h"

int
array_cmpb_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPB_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpb(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPB_NOITER(a, b, n, ret);
  }
  return ret;
}

static long long
clock_monotonic_curtime_usecs(void)
{
  struct timespec tp;
  int rc;

  rc = clock_gettime(CLOCK_MONOTONIC, &tp);
  ASSERT(rc == 0);
  
  long long ret = 0;
  //printf("ret = %lld\n", ret);
  ret = (long)tp.tv_sec * 1e+6 + (long)tp.tv_nsec/1e+3;
  //printf("ret = %lld\n", ret);
  //printf("tp.tv_sec = %ld, tp.tv_nsec = %ld, ret = %lld\n", (long)tp.tv_sec, (long)tp.tv_nsec, ret);
  return ret;
}

int
stopwatch_run (struct time *timer)
{
  //printf("%s(): entry\n", __func__);
  //int flags = timer->flags ;

  ASSERT(timer->running == FALSE) ;

  //if (flags & SW_WALLCLOCK)
    //{
      timer->wallClock_start = clock_monotonic_curtime_usecs();

      /*struct timeval tv ;
      if (gettimeofday (&tv, NULL) < 0)
	{
	  timer->flags = -1 ;
	  return -1 ;
	}
      timer->wallClock_start = tv.tv_usec + tv.tv_sec*1e6;*/

/*
      DBG (STOPWATCH, ("%s() %d: after call to gettimeofday,"
		       " timer->wallClock_start = %" PRId64 "\n", __func__, __LINE__,
		       timer->wallClock_start)) ;
*/
//    }
//  else
//    {
//      timer->wallClock_start = -1 ;
//    }
//
//  if (flags & SW_PROCESSOR)
//    {
//      clock_t clockticks = clock() ;
//      timer->processor_start = ceil ((double)clockticks*1e6/CLOCKS_PER_SEC) ;
//    }
//  else
//    {
//      timer->processor_start = -1 ;
//    }
//
//  if (flags & SW_CLOCKTICKS || flags & SW_USER || flags & SW_SYSTEM)
//    {
//      struct tms tms ;
//      clock_t clockticks = times (&tms) ;
//      if (clockticks==(clock_t)-1)
//	{
//	  timer->flags = -1 ;
//	  return -1 ;
//	}
//      if (flags & SW_CLOCKTICKS)
//	{
//	  timer->clockticks_start = clockticks ;
//	}
//      else
//	{
//	  timer->clockticks_start = -1 ;
//	}
//
//      if (flags & SW_USER)
//	{
//	  timer->user_start = tms.tms_utime;
//	}
//      else
//	{
//	  timer->user_start = -1 ;
//	}
//
//      if (flags & SW_SYSTEM)
//	{
//	  timer->system_start = tms.tms_stime;
//	}
//      else
//	{
//	  timer->system_start = -1 ;
//	}
//    }
  timer->running = TRUE;
  timer->num_starts++;
  return 0 ;
}

void
stopwatch_reset(struct time *timer)
{
  timer->num_starts = 0;
  timer->running = FALSE ;

  timer->wallClock_elapsed = 0;
//  timer->processor_elapsed = 0;
//  timer->clockticks_elapsed = 0;
//  timer->user_elapsed = 0;
//  timer->system_elapsed = 0;
}

int stopwatch_tell (struct time *timer)
{
  //printf("%s(): entry\n", __func__);

  if (timer->running == FALSE)
    return 0 ;

  //printf("%s() %d:\n", __func__, __LINE__);
//  int flags = timer->flags;
//
//  if (flags == (clock_t)-1)
//    {
//      return -1 ;
//    }
 
//  if (flags & SW_WALLCLOCK)
//    {
      timer->wallClock_elapsed += clock_monotonic_curtime_usecs() - timer->wallClock_start ;
      //struct timeval tv ;
  //printf("%s() %d: wallClock_elapsed = %lld\n", __func__, __LINE__, (long long)timer->wallClock_elapsed);

/*
      if (STOPWATCH)
	{
	  tv.tv_sec = tv.tv_usec = 0 ;
	}
*/

      /*if (gettimeofday (&tv, NULL) < 0)
	{
	  ASSERT(0) ;
	  return -1 ;
	}

      timer->wallClock_elapsed += (tv.tv_usec + tv.tv_sec*1e6)
						 - timer->wallClock_start ;*/
//    }
//
//  if (flags & SW_PROCESSOR)
//    {
//      clock_t clockticks = clock() ;
//
//      timer->processor_elapsed += ceil ((double)clockticks*1e6/CLOCKS_PER_SEC)
//					  	 - timer->processor_start ;
//
//      /* assuming clock_t is unsigned and we are running on a 32 bit
//	 machine */
//      if (timer->processor_elapsed < 0)
//	timer->processor_elapsed += (unsigned int)0xffffffff ;  
//    }
//
//  if (flags & SW_CLOCKTICKS || flags & SW_USER || flags & SW_SYSTEM)
//    {
//      struct tms tms ;
//      clock_t clockticks = times (&tms) ;
//      if (clockticks==(clock_t)-1)
//	{
//	  assert (0) ;
//	  return -1 ;
//	}
//
//      if (flags & SW_CLOCKTICKS)
//	{
//	  timer->clockticks_elapsed += clockticks - timer->clockticks_start ;
//
//	  /* assumes clock_t is unsigned and we are running on a 32 bit
//	     machine */
//	  if (timer->clockticks_elapsed < 0)
//	    timer->clockticks_elapsed += (unsigned int)0xffffffff ;  
//	}
//
//      if (flags & SW_USER)
//	{
//	  timer->user_elapsed += tms.tms_utime - timer->user_start ;
//
//	  /* assuming clock_t is unsigned and we are running on a 32 bit
//	     machine */
//	  if (timer->user_elapsed < 0)
//	    timer->user_elapsed += (unsigned int)0xffffffff ;  
//	}
//
//      if (flags & SW_SYSTEM)
//	{
//	  timer->system_elapsed += tms.tms_stime - timer->system_start ;
//
//	  /* assumes clock_t is unsigned and we are running on a 32 bit
//	     machine */
//	  if (timer->user_elapsed < 0)
//	    timer->user_elapsed += (unsigned int)0xffffffff ;  
//	}
//    }
  return 0 ;
}

void
stopwatch_stop (struct time *timer)
{
  //printf("%s(): entry\n", __func__);
  ASSERT(timer->running == TRUE);
  stopwatch_tell (timer);
  timer->running = FALSE;
}

void
stopwatch_print (struct time *timer)
{
  stopwatch_tell (timer);

  double secs;
  secs = (double)timer->wallClock_elapsed/1e6 ;
  printf ("Wall-clock [%lld entries]: %d:%d:%d.%f\n", timer->num_starts,
      (int)(secs/3.6e3),
      ((int)((secs/60))) % 60,
      ((int)secs)%60, (double)timer->wallClock_elapsed - ((int)secs * 1e6));
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

  struct time array_cmpb_timer;
  stopwatch_reset(&array_cmpb_timer);
  stopwatch_run(&array_cmpb_timer);
  int cmp1b = array_cmpb(s, s2, slen);
  stopwatch_stop(&array_cmpb_timer);

  printf("output = %d\n", cmp1b);
  stopwatch_print(&array_cmpb_timer);

  cmp1b = array_cmpb(s, &s2[1], slen);
  printf("unequal comparisono output: cmp1b = %d\n", cmp1b);

  return 0;
}
