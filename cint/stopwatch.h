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


/*
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
*/

static long long
gettimeofday_usecs(void)
{
  struct timeval tv;
  long long ret;

  gettimeofday(&tv, NULL);
  return (long long)tv.tv_sec * 1e+6 + (long long)tv.tv_usec;
}

static long long
curtime_usecs(void)
{
  //return clock_monotonic_curtime_usecs();
  return gettimeofday_usecs();
}

static int
stopwatch_run (struct time *timer)
{
  //printf("%s(): entry\n", __func__);
  //int flags = timer->flags ;

  ASSERT(timer->running == FALSE) ;

  //if (flags & SW_WALLCLOCK)
    //{
      timer->wallClock_start = curtime_usecs();

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

static void
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

static int
stopwatch_tell (struct time *timer)
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
      timer->wallClock_elapsed += curtime_usecs() - timer->wallClock_start ;
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

static void
stopwatch_stop(struct time *timer)
{
  //printf("%s(): entry\n", __func__);
  ASSERT(timer->running == TRUE);
  stopwatch_tell (timer);
  timer->running = FALSE;
}

static void
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
