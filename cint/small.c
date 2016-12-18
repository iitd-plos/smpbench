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
#include "str_op_macros.h"

int a_global[1000];
int *a_global_pointer = NULL;

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


size_t my_strlenw(uint16_t *str/*, char a*/);
size_t my_strlen_scasw(uint16_t *str/*, char a*/);
size_t my_strlen_scasw2(uint16_t *str/*, char a*/);

size_t my_strlenb(char const *str/*, char a*/);
size_t my_strlen_scasb(char *str/*, char a*/);
size_t my_strlen_scasb2(char *str/*, char a*/);

void usage (void);

int
array_cmpw_cmpsl_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPW_CMPSL_NOITER(a, b, n, ret);
  return ret;
}

char *
my_strrchr_noiter(char *haystack, char needle)
{
  char *ptr = haystack;
  MY_STRRCHR_NOITER(haystack, needle, ptr);
  return ptr;
}

char *
my_strrchr(char *haystack, char needle)
{
  char *ptr = haystack;
  int i;

  for (i = 0; i < NUM_ITER; i++) {
    MY_STRRCHR_NOITER(haystack, needle, ptr);
  }
  return ptr;
}

char *
my_strrchr_scasb_noiter(char *haystack, char needle)
{
  char *ret = haystack;
  MY_STRRCHR_SCASB_NOITER(haystack, needle, ret);
  return ret;
}

char *
my_strrchr_scasb(char *haystack, char needle)
{
  char *ret = haystack;
  int i;

  for (i = 0; i < NUM_ITER; i++) {
    MY_STRRCHR_SCASB_NOITER(haystack, needle, ret);
  }
  return ret;
}





size_t
array_rfindb_noiter(char const *str, size_t n, char needle)
{
  size_t ii;
  ARRAY_RFINDB_NOITER(str, n, needle, ii);
  return ii;
}


size_t
array_rfindb(char const *str, size_t n, char needle)
{
  size_t ii;
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_RFINDB_NOITER(str, n, needle, ii);
  }
  return ii;
}

size_t
array_rfindb_scasb_noiter(char *str, size_t n, char needle)
{
  size_t ret = 0;
  ARRAY_RFINDB_SCASB_NOITER(str, n, needle, ret);
  return ret;
}


size_t
array_rfindb_scasb(char *str, size_t n, char needle)
{
  size_t ret = 0, i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_RFINDB_SCASB_NOITER(str, n, needle, ret);
  }
  return ret;
}
/*
size_t
array_rfindb_scasb2(char *str, size_t n, char needle)
{
  size_t ret = -1, i;
  for (i = 0; i < NUM_ITER; i++) {
    ret = ~n;
    __asm volatile ("movl %%ecx,%%edi\n\t"
                  "addl %3,%%edi\n\t"
                  "std\n\t"
                  "notl %%ecx\n\t"
                  "repne scasb\n\t"
                  "notl %%ecx\n\t"
                  "leal -1(%%ecx),%%ecx\n\t"
                  : "=c"(ret)
                  : "c"(ret), "a"(needle), "m"(str));
  }
  return ret;
}
*/

size_t
array_rfindw_noiter(uint16_t *str, size_t n, uint16_t needle)
{
  size_t ii;
  ARRAY_RFINDW_NOITER(str, n, needle, ii);
  return ii;
}

size_t
array_rfindw(uint16_t *str, size_t n, uint16_t needle)
{
  size_t i, ii;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_RFINDW_NOITER(str, n, needle, ii);
  }
  return ii;
}

size_t
array_rfindw_scasw_noiter(uint16_t *str, size_t n, uint16_t needle)
{
  size_t ret = 0;
  ARRAY_RFINDW_SCASW_NOITER(str, n, needle, ret);
  return ret;
}

size_t
array_rfindw_scasw(uint16_t *str, size_t n, uint16_t needle)
{
  size_t ret = 0, i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_RFINDW_SCASW_NOITER(str, n, needle, ret);
  }
  return ret;
}

/*
size_t
array_rfindw_scasw2(uint16_t *str, size_t n, uint16_t needle)
{
  size_t ret = -1, i;
  for (i = 0; i < NUM_ITER; i++) {
    //ret = 0;
    ret = ~n;
    __asm volatile ("std\n\t"
                  "notl %%ecx\n\t"
                  "addl %%ecx,%%edi\n\t"
                  "repne scasw\n\t"
                  "notl %%ecx\n\t"
                  "leal -1(%%ecx),%%ecx\n\t"
                  : "=c"(ret)
                  : "c"(ret), "a"(needle), "D"(str));
  }
  return ret;
}
*/

size_t
array_rfindl_noiter(uint32_t *str, size_t n, uint32_t needle)
{
  size_t ii;
  ARRAY_RFINDL_NOITER(str, n, needle, ii);
  return ii;
}

size_t
array_rfindl(uint32_t *str, size_t n, uint32_t needle)
{
  size_t i, ii;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_RFINDL_NOITER(str, n, needle, ii);
  }
  return ii;
}

size_t
array_rfindl_scasl_noiter(uint32_t *str, size_t n, uint32_t needle)
{
  size_t ret = 0;
  ARRAY_RFINDL_SCASL_NOITER(str, n, needle, ret);
  return ret;
}

size_t
array_rfindl_scasl(uint32_t *str, size_t n, uint32_t needle)
{
  size_t ret = 0, i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_RFINDL_SCASL_NOITER(str, n, needle, ret);
  }
  return ret;
}

/*
size_t
array_rfindl_scasl2(uint32_t *str, size_t n, char needle)
{
  size_t ret = -1, i;
  for (i = 0; i < NUM_ITER; i++) {
    //ret = 0;
    ret = ~n;
    __asm volatile ("std\n\t"
                  "notl %%ecx\n\t"
                  "addl %%ecx,%%edi\n\t"
                  "repne scasl\n\t"
                  "notl %%ecx\n\t"
                  "leal -1(%%ecx),%%ecx\n\t"
                  : "=c"(ret)
                  : "c"(ret), "a"(needle), "D"(str));
  }
  return ret;
}
*/

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



void
my_exit(int ec)
{
  exit(ec);
  /*if (ec) {
    for (;;);
  } else {
    return;
  }*/
}

void
usage (void)
{
  printf ("Usage: combox <prog-name> <arguments>\n");
  printf ("\tprograms: array_cmpb array_cmpw array_cmpl array_setb array_setw array_setl array_findb array_findw array_findl array_rfindb array_rfindw array_rfindl strlen strrchr count_ones\n");
  my_exit (1);
}

int
_sum8_global(int len)
{
  int i;
  int sum = 0;
  for (i = 0; i < len; i++) {
    sum += a_global[i];
  }
  return sum;
}

int
_sum8_global_pointer(int len)
{
  int i;
  int sum = 0;
  for (i = 0; i < len; i++) {
    sum += a_global_pointer[i];
  }
  return sum;
}


int cp_test(int n)
{
  int i;
  int ret = 0;
  for(i = 0; i < n; ++i)
  {
    printf("%d\n", i);
  }

  for(; i >= 0; --i)
  {
    printf("%d\n", i);
    ret++;
  }
  return i;
}

int
_sum8_weird(uint8_t *a, int len) //confuses locals identification
{
  int b[len];
  int i;
  int sum = 0;

  for (i = 0; i < len; i++) {
    b[i] = 2 * a[i];
    sum += a[i];
  }
  return b[a[3]] + sum;

}

int
_sum8(uint8_t *a, int len)
{
  int i;
  int sum = 0;
  for (i = 0; i < len; i++) {
    sum += a[i];
  }
  return sum;
}

int
sum8(int argc, char **argv)
{
  if (argc < 2) {
    printf("Usage: sum8 <array-size>\n");
    my_exit(1);
  }

  int len = atoi(argv[1]);
  uint8_t *a = (uint8_t *)malloc(len * sizeof(uint8_t));
  a_global_pointer = (int *)malloc(len * sizeof(uint8_t));

  if (!a || !a_global_pointer) {
    printf ("%s(): array allocation of size %d failed.\n", __func__, len);
    my_exit(1);
  }

  int i, j;

  srand48 (0x12345678);

  for (i = 0; i < len; i++) {
    a[i] = rand() & 0xff;
    a_global_pointer[i] = rand() & 0xff;
  }

  for (i = 0; i < sizeof a_global/sizeof a_global[0]; i++) {
    a_global[i] = rand() & 0xff;
  }

  if (len <= 10) {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++) {
      printf ("a[%d] = %d\n", i, a[i]);
    }
  }

  int sum = _sum8(a, len);
  int sum2 = _sum8_global(sizeof a_global/sizeof a_global[0]);
  int sum3 = _sum8_global_pointer(len);

  printf ("sum = %d, sum2 = %d, sum3 = %d.\n", sum, sum2, sum3);
  return len;
}

struct node {
  int val;
  struct node *next;
};

void
remove_list_entry_bad_taste(struct node const *entry, struct node *head) //from Linus Torvald's interview https://www.youtube.com/watch?v=o8NPllzkFhE
{
  struct node *prev = NULL;
  struct node *walk = head;

  while (walk != entry) {
    prev = walk;
    walk = walk->next;
  }
  if (!prev) {
    head = entry->next;
  } else {
    prev->next = entry->next;
  }
}

void
remove_list_entry_good_taste(struct node const *entry, struct node *head) //from Linus Torvald's interview https://www.youtube.com/watch?v=o8NPllzkFhE
{
  struct node **indirect = &head;

  while ((*indirect) != entry) {
    indirect = &(*indirect)->next;
  }
  *indirect = entry->next;
}


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


int
array_cmpb2_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPB2_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpb2(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPB2_NOITER(a, b, n, ret);
  }
  return ret;
}

int
array_cmpb4_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPB4_NOITER(a, b, n, ret);
  return ret;
}



int
array_cmpb4(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPB4_NOITER(a, b, n, ret);
  }
  return ret;
}

int
array_cmpb_cmpsb_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPB_CMPSB_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpb_cmpsb(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPB_CMPSB_NOITER(a, b, n, ret);
  }
  return ret;
}

int
array_cmpb_cmpsw_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPB_CMPSW_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpb_cmpsw(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPB_CMPSW_NOITER(a, b, n, ret);
  }
  return ret;
}

int
array_cmpb_cmpsl_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPB_CMPSL_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpb_cmpsl(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPB_CMPSL_NOITER(a, b, n, ret);
  }
  return ret;
}

int
array_cmpw_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPW_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpw(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPW_NOITER(a, b, n, ret);
  }
  return ret;
}

int
array_cmpw2_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPW2_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpw2(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPW2_NOITER(a, b, n, ret);
  }
  return ret;
}

int
array_cmpw_cmpsw_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPW_CMPSW_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpw_cmpsw(const void *a, const void *b, size_t n)
{
  int i, ret = 1;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_CMPW_CMPSW_NOITER(a, b, n, ret);
  }
  return ret;
}

int
array_cmpw_cmpsl(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPW_CMPSL_NOITER(a, b, n, ret);
  }
  return ret;
}

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
array_cmpl_cmpsl_noiter(const void *a, const void *b, size_t n)
{
  int ret = 1;
  ARRAY_CMPL_CMPSL_NOITER(a, b, n, ret);
  return ret;
}

int
array_cmpl_cmpsl(const void *a, const void *b, size_t n)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 1;
    ARRAY_CMPL_CMPSL_NOITER(a, b, n, ret);
  }
  return ret;
}

int
array_setb_noiter(void *dest, unsigned char fill_value, size_t count)
{
  ARRAY_SETB_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setb(void *dest, unsigned char fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETB_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setb2_noiter(void *dest, unsigned char fill_value, size_t count)
{
  ARRAY_SETB2_NOITER(dest, fill_value, count);
  return 0;
}


int
array_setb2(void *dest, unsigned char fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETB2_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setb4_noiter(void *dest, unsigned char fill_value, size_t count)
{
  ARRAY_SETB4_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setb4(void *dest, unsigned char fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETB4_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setb_stosb_noiter(void *dest, unsigned char fill_value, size_t count)
{
  ARRAY_SETB_STOSB_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setb_stosb(void *dest, unsigned char fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETB_STOSB_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setb_stosw_noiter(void *dest, unsigned char fill_value, size_t count)
{
  ARRAY_SETB_STOSW_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setb_stosw(void *dest, unsigned char fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETB_STOSW_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setb_stosl_noiter(void *dest, unsigned char fill_value, size_t count)
{
  ARRAY_SETB_STOSL_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setb_stosl(void *dest, unsigned char fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETB_STOSL_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setw_noiter(void *dest, uint16_t fill_value, size_t count)
{
  ARRAY_SETW_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setw(void *dest, uint16_t fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETW_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setw2_noiter(void *dest, uint16_t fill_value, size_t count)
{
  ARRAY_SETW2_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setw2(void *dest, uint16_t fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETW2_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setw_stosw_noiter(void *dest, uint16_t fill_value, size_t count)
{
  ARRAY_SETW_STOSW_NOITER(dest, fill_value, count);
  return 0;
}


int
array_setw_stosw(void *dest, uint16_t fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETW_STOSW_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setw_stosl_noiter(void *dest, uint16_t fill_value, size_t count)
{
  ARRAY_SETW_STOSL_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setw_stosl(void *dest, uint16_t fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETW_STOSL_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setl_noiter(void *dest, uint32_t fill_value, size_t count)
{
  ARRAY_SETL_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setl(void *dest, uint32_t fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETL_NOITER(dest, fill_value, count);
  }
  return 0;
}

int
array_setl_stosl_noiter(void *dest, uint32_t fill_value, size_t count)
{
  ARRAY_SETL_STOSL_NOITER(dest, fill_value, count);
  return 0;
}

int
array_setl_stosl(void *dest, uint32_t fill_value, size_t count)
{
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_SETL_STOSL_NOITER(dest, fill_value, count);
  }
  return 0;
}

size_t
array_findb_noiter(char const *str, size_t n, char needle)
{
  char const *ptr = str;
  size_t ret;
  ARRAY_FINDB_NOITER(str, n, needle, ptr, ret);
  return ret;
}

size_t
array_findb(char const *str, size_t n, char needle)
{
  char const *ptr = str;
  size_t ret;
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_FINDB_NOITER(str, n, needle, ptr, ret);
  }
  return ret;
}

size_t
array_findb_scasb_noiter(char *str, size_t n, char needle)
{
  size_t ret = 0;
  ARRAY_FINDB_SCASB_NOITER(str, n, needle, ret);
  return ret;
}



size_t
array_findb_scasb(char *str, size_t n, char needle)
{
  size_t ret = 0;
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_FINDB_SCASB_NOITER(str, n, needle, ret);
  }
  return ret;
}

/*
size_t
array_findb_scasb2(char *str, size_t n, char needle)
{
  size_t ret = -1, i;
  __asm volatile ("cld\n\t");
  for (i = 0; i < NUM_ITER; i++) {
    __asm volatile ("movl %%esi,%%ecx\n\t"
                  "movl %%edx, %%edi\n\t"
                  "repne scasb\n\t"
                  "notl %%ecx\n\t"
                  "leal -1(%%ecx),%%ecx\n\t"
                  : "=c"(ret)
                  : "S"(n), "a"(needle), "D"(str));
  }
  return ret;
}
*/

size_t
array_findw_noiter(uint16_t *str, size_t n, uint16_t needle)
{
  size_t ii;
  ARRAY_FINDW_NOITER(str, n, needle, ii);
  return ii;
}

size_t
array_findw(uint16_t *str, size_t n, uint16_t needle)
{
  size_t i, ii;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_FINDW_NOITER(str, n, needle, ii);
  }
  return ii;
}

size_t
array_findw_scasw_noiter(uint16_t *str, size_t n, uint16_t needle)
{
  size_t ret = 0;
  ARRAY_FINDW_SCASW_NOITER(str, n, needle, ret);
  return ret;
}

size_t
array_findw_scasw(uint16_t *str, size_t n, uint16_t needle)
{
  size_t ret = 0, i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_FINDW_SCASW_NOITER(str, n, needle, ret);
  }
  return ret;
}

/*
size_t
array_findw_scasw2(uint16_t *str, size_t n, uint16_t needle)
{
  size_t ret = -1, i;
  for (i = 0; i < NUM_ITER; i++) {
    //ret = 0;
    ret = ~n;
    __asm volatile ("cld\n\t"
                  "notl %%ecx\n\t"
                  "repne scasw\n\t"
                  "notl %%ecx\n\t"
                  "leal -1(%%ecx),%%ecx\n\t"
                  : "=c"(ret)
                  : "c"(ret), "a"(needle), "D"(str));
  }
  return ret;
}
*/

size_t
array_findl_noiter(uint32_t *str, size_t n, uint32_t needle)
{
  size_t ii;
  ARRAY_FINDL_NOITER(str, n, needle, ii);
  return ii;
}

size_t
array_findl(uint32_t *str, size_t n, uint32_t needle)
{
  size_t i, ii;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_FINDL_NOITER(str, n, needle, ii);
  }
  return ii;
}

size_t
array_findl_scasl_noiter(uint32_t *str, size_t n, uint32_t needle)
{
  size_t ret = 0;
  ARRAY_FINDL_SCASL_NOITER(str, n, needle, ret);
  return ret;
}



size_t
array_findl_scasl(uint32_t *str, size_t n, uint32_t needle)
{
  size_t ret = 0, i;
  for (i = 0; i < NUM_ITER; i++) {
    ARRAY_FINDL_SCASL_NOITER(str, n, needle, ret);
  }
  return ret;
}

/*
size_t
array_findl_scasl2(uint32_t *str, size_t n, char needle)
{
  size_t ret = -1, i;
  for (i = 0; i < NUM_ITER; i++) {
    //ret = 0;
    ret = ~n;
    __asm volatile ("cld\n\t"
                  "notl %%ecx\n\t"
                  "repne scasl\n\t"
                  "notl %%ecx\n\t"
                  "leal -1(%%ecx),%%ecx\n\t"
                  : "=c"(ret)
                  : "c"(ret), "a"(needle), "D"(str));
  }
  return ret;
}
*/

size_t
my_strlen_noiter(char const *str)
{
  char const *ptr = str;
  size_t ret;
  MY_STRLEN_NOITER(str, ptr, ret);
  return ret;
}

size_t
my_strlen(char const *str)
{
  char const *ptr = str;
  size_t ret;
  int i;
  for (i = 0; i < NUM_ITER; i++) {
    MY_STRLEN_NOITER(str, ptr, ret);
  }
  return ret;
}

size_t
my_strlen_scasb_noiter(char *str)
{
  size_t ret = 0;
  MY_STRLEN_SCASB_NOITER(str, ret);
  return ret;
}

size_t
my_strlen_scasb(char *str)
{
  size_t ret = 0, i;
  for (i = 0; i < NUM_ITER; i++) {
    MY_STRLEN_SCASB_NOITER(str, ret);
  }
  return ret;
}

/*
size_t
my_strlen_scasb2(char *str)
{
  size_t ret = -1, i;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 0;
    __asm volatile ("movl %%ecx,%%edi\n\t"
                  "addl %3,%%edi\n\t"
                  "std\n\t"
                  "notl %%ecx\n\t"
                  "repne scasb\n\t"
                  "notl %%ecx\n\t"
                  "leal -1(%%ecx),%%ecx\n\t"
                  : "=c"(ret)
                  : "c"(ret), "a"(0), "m"(str));
  }
  return ret;
}
*/

int
my_strcmp(char const *a, char const *b)
{
  int i, ret = 0;
  for (i = 0; i < NUM_ITER; i++) {
    MY_STRCMP(a, b, ret);
  }
  return ret;
}

int
my_strcmp_cmpsb(char const *a, char const *b)
{
  printf("%s(): this is not possible\n", __func__);
  int i, ret = 0;
  for (i = 0; i < NUM_ITER; i++) {
    MY_STRCMP_CMPSB(a, b, ret);
  }
  return ret;
}


/*
#define array_search_macro(haystack, n, needle) ({ \
  long __array_search_i, __array_search_ret = -1; \
  for (__array_search_i = 0; __array_search_i < (n); __array_search_i++) { \
    if ((haystack)[__array_search_i] == (needle)) {  \
      __array_search_ret = __array_search_i; \
    } \
  } \
  __array_search_ret; \
})

int
array_search_regular(int const *haystack, size_t n, int needle)
{
  return array_search_macro(haystack, n, needle);
}

int
array_search_scasl(int const *haystack, size_t n, int needle)
{
  size_t ret = -1, i;
  for (i = 0; i < NUM_ITER; i++) {
    ret = -1;
    __asm volatile ("cld\n\t"
                  "repne scasl\n\t"
                  "neg %%ecx\n\t"
                  "sub $2,%%ecx\n\t"
                  : "=c"(ret)
                  : "c"(n), "a"(needle), "D"(haystack));
  }
  return ret;
}
*/

int
count_ones32_noiter(uint32_t *a, size_t size)
{
  unsigned ret = 0;
  COUNT_ONES32_NOITER(a, size, ret);
  return ret;
}

int
count_ones32(uint32_t *a, size_t size)
{
  unsigned i, ret = 0;
  for (i = 0; i < NUM_ITER; i++) {
    COUNT_ONES32_NOITER(a, size, ret);
  }
  return ret;
}

int
count_ones_popcnt32_noiter(uint32_t *a, size_t size)
{
  unsigned ret = 0;
  COUNT_ONES_POPCNT32_NOITER(a, size, ret);
  return ret;
}



int
count_ones_popcnt32(uint32_t *a, size_t size)
{
  unsigned i, ret = 0;
  for (i = 0; i < NUM_ITER; i++) {
    COUNT_ONES_POPCNT32_NOITER(a, size, ret);
  }
  return ret;
}

/*
int
count_ones_regular64(uint64_t a)
{
  int i, n, ret = 0;
  for (i = 0; i < NUM_ITER; i++) {
    ret = 0;
    for (n = 0; n < 64; i++) {
      if (a & (1 << n)) {
        ret++;
      }
    }
  }
  return ret;
}

int
count_ones_popcnt64(uint64_t a)
{
  int i, ret;
  for (i = 0; i < NUM_ITER; i++) {
    __asm volatile("popcntl %1, %0\n\t"
                 "leal 4(%1), %%ecx\n\t"
                 "popcntl %%ecx, %%ecx\n\t"
                 "addl %%ecx, %0\n\t"
                 : "=b"(ret)
                 : "r"(a)
                 : "%ecx");
  }
  return ret;
}
*/

void stopwatch_reset(struct time *timer);
int stopwatch_run(struct time *timer);
void stopwatch_stop(struct time *timer);
void stopwatch_print(struct time *timer);

size_t my_strlen(char const *str/*, char a*/);
size_t my_strlen_scasb(char *str/*, char a*/);
size_t my_strlen_scasb2(char *str/*, char a*/);

char *my_strrchr(char *haystack, char needle);
char *my_strrchr_scasb(char *haystack, char needle);

void usage (void);

int
main (int argc, char **argv)
{
  if (argc < 2)
      usage();

  char *s, *s2, *s3, *p, *p2, *p3;
  size_t slen, slen2;
  //char *s = argv[2];
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

  //some of these functions are implemented as optimized routines in libraries; but they have fixed implementations (e.g., only for char but not for uint16_t)
  if (!strcmp(argv[1], "array_cmpb")) { //show results for uint16_t. Discuss that while wmemcmp exists, very few people use it due to portability issues; different compilers have different representations of wide-character (Windows: 16-bit, Linux 32-bit) [source: http://stackoverflow.com/questions/11287213/what-is-a-wide-character-string-in-c-language]
    struct time array_cmpb_timer;
    struct time array_cmpb2_timer;
    struct time array_cmpb4_timer;
    struct time array_cmpb_cmpsb_timer;
    struct time array_cmpb_cmpsw_timer;
    struct time array_cmpb_cmpsl_timer;

    stopwatch_reset(&array_cmpb_timer);
    stopwatch_reset(&array_cmpb2_timer);
    stopwatch_reset(&array_cmpb4_timer);
    stopwatch_reset(&array_cmpb_cmpsb_timer);
    stopwatch_reset(&array_cmpb_cmpsw_timer);
    stopwatch_reset(&array_cmpb_cmpsl_timer);

    stopwatch_run(&array_cmpb_timer);
    int cmp1b = array_cmpb(s, s2, slen);
    stopwatch_stop(&array_cmpb_timer);

    stopwatch_run(&array_cmpb2_timer);
    int cmp1b2 = array_cmpb2(s, s2, slen);
    stopwatch_stop(&array_cmpb2_timer);

    stopwatch_run(&array_cmpb4_timer);
    int cmp1b4 = array_cmpb4(s, s2, slen);
    stopwatch_stop(&array_cmpb4_timer);

    stopwatch_run(&array_cmpb_cmpsb_timer);
    int cmp2b = array_cmpb_cmpsb(s, s2, slen);
    stopwatch_stop(&array_cmpb_cmpsb_timer);

    stopwatch_run(&array_cmpb_cmpsw_timer);
    int cmp3b = array_cmpb_cmpsw(s, s2, slen);
    stopwatch_stop(&array_cmpb_cmpsw_timer);

    stopwatch_run(&array_cmpb_cmpsl_timer);
    int cmp4b = array_cmpb_cmpsl(s, s2, slen);
    stopwatch_stop(&array_cmpb_cmpsl_timer);

    printf("cmp1b = %d, cmp1b2 = %d, cmp1b4 = %d, cmp2b = %d, cmp3b = %d, cmp4b = %d\n", cmp1b, cmp1b2, cmp1b4, cmp2b, cmp3b, cmp4b);
    stopwatch_print(&array_cmpb_timer);
    stopwatch_print(&array_cmpb2_timer);
    stopwatch_print(&array_cmpb4_timer);
    stopwatch_print(&array_cmpb_cmpsb_timer);
    stopwatch_print(&array_cmpb_cmpsw_timer);
    stopwatch_print(&array_cmpb_cmpsl_timer);

    cmp1b = array_cmpb(s, s2, 0);
    cmp1b2 = array_cmpb2(s, s2, 0);
    cmp1b4 = array_cmpb4(s, s2, 0);
    cmp2b = array_cmpb_cmpsb(s, s2, 0);
    cmp3b = array_cmpb_cmpsw(s, s2, 0);
    cmp4b = array_cmpb_cmpsl(s, s2, 0);
    printf("zero len comparison: cmp1b = %d, cmp1b2 = %d, cmp1b4 = %d, cmp2b = %d, cmp3b = %d, cmp4b = %d\n", cmp1b, cmp1b2, cmp1b4, cmp2b, cmp3b, cmp4b);

    cmp1b = array_cmpb(s, &s2[1], slen);
    cmp1b2 = array_cmpb2(s, &s2[1], slen);
    cmp1b4 = array_cmpb4(s, &s2[1], slen);
    cmp2b = array_cmpb_cmpsb(s, &s2[1], slen);
    cmp3b = array_cmpb_cmpsw(s, &s2[1], slen);
    cmp4b = array_cmpb_cmpsl(s, &s2[1], slen);
    printf("unequal comparison: cmp1b = %d, cmp1b2 = %d, cmp1b4 = %d, cmp2b = %d, cmp3b = %d, cmp4b = %d\n", cmp1b, cmp1b2, cmp1b4, cmp2b, cmp3b, cmp4b);
  } else if (!strcmp(argv[1], "array_cmpw")) {
    struct time array_cmpw_timer;
    struct time array_cmpw2_timer;
    struct time array_cmpw_cmpsw_timer;
    struct time array_cmpw_cmpsl_timer;

    stopwatch_reset(&array_cmpw_timer);
    stopwatch_reset(&array_cmpw2_timer);
    stopwatch_reset(&array_cmpw_cmpsw_timer);
    stopwatch_reset(&array_cmpw_cmpsl_timer);

    stopwatch_run(&array_cmpw_timer);
    int cmp1w = array_cmpw(s, s2, slen/2);
    stopwatch_stop(&array_cmpw_timer);

    stopwatch_run(&array_cmpw2_timer);
    int cmp1w2 = array_cmpw2(s, s2, slen/2);
    stopwatch_stop(&array_cmpw2_timer);

    stopwatch_run(&array_cmpw_cmpsw_timer);
    int cmp2w = array_cmpw_cmpsw(s, s2, slen/2);
    stopwatch_stop(&array_cmpw_cmpsw_timer);

    stopwatch_run(&array_cmpw_cmpsl_timer);
    int cmp3w = array_cmpw_cmpsl(s, s2, slen/2);
    stopwatch_stop(&array_cmpw_cmpsl_timer);

    printf("cmp1w = %d, cmp1w2 = %d, cmp2w = %d, cmp3w = %d\n", cmp1w, cmp1w2, cmp2w, cmp3w);
    stopwatch_print(&array_cmpw_timer);
    stopwatch_print(&array_cmpw2_timer);
    stopwatch_print(&array_cmpw_cmpsw_timer);
    stopwatch_print(&array_cmpw_cmpsl_timer);

    cmp1w = array_cmpw(s, s2, 0);
    cmp1w2 = array_cmpw2(s, s2, 0);
    cmp2w = array_cmpw_cmpsw(s, s2, 0);
    cmp3w = array_cmpw_cmpsl(s, s2, 0);
    printf("zero len comparison: cmp1w = %d, cmp1w2 = %d, cmp2w = %d, cmp3w = %d\n", cmp1w, cmp1w2, cmp2w, cmp3w);

    cmp1w = array_cmpw(s, &s2[1], slen);
    cmp1w2 = array_cmpw2(s, &s2[1], slen);
    cmp2w = array_cmpw_cmpsw(s, &s2[1], slen);
    cmp3w = array_cmpw_cmpsl(s, &s2[1], slen);
    printf("unequal comparison: cmp1w = %d, cmp1w2 = %d, cmp2w = %d, cmp3w = %d\n", cmp1w, cmp1w2, cmp2w, cmp3w);

  } else if (!strcmp(argv[1], "array_cmpl")) {
    struct time array_cmpl_timer;
    struct time array_cmpl_cmpsl_timer;

    stopwatch_reset(&array_cmpl_timer);
    stopwatch_reset(&array_cmpl_cmpsl_timer);

    stopwatch_run(&array_cmpl_timer);
    int cmp1d = array_cmpl(s, s2, slen/4);
    stopwatch_stop(&array_cmpl_timer);

    stopwatch_run(&array_cmpl_cmpsl_timer);
    int cmp2d = array_cmpl_cmpsl(s, s2, slen/4);
    stopwatch_stop(&array_cmpl_cmpsl_timer);

    printf("cmp1d = %d, cmp2d = %d\n", cmp1d, cmp2d);
    stopwatch_print(&array_cmpl_timer);
    stopwatch_print(&array_cmpl_cmpsl_timer);

    cmp1d = array_cmpl(s, s2, 0);
    cmp2d = array_cmpl_cmpsl(s, s2, 0);
    printf("zero len comparison: cmp1l = %d, cmp2l = %d\n", cmp1d, cmp2d);

    cmp1d = array_cmpl(s, &s2[1], slen);
    cmp2d = array_cmpl_cmpsl(s, &s2[1], slen);
    printf("unequal comparison: cmp1l = %d, cmp2l = %d\n", cmp1d, cmp2d);
  } else if (!strcmp(argv[1], "array_setb")) {
    struct time array_setb_timer;
    struct time array_setb2_timer;
    struct time array_setb4_timer;
    struct time array_setb_stosb_timer;
    struct time array_setb_stosw_timer;
    struct time array_setb_stosl_timer;

    stopwatch_reset(&array_setb_timer);
    stopwatch_reset(&array_setb2_timer);
    stopwatch_reset(&array_setb4_timer);
    stopwatch_reset(&array_setb_stosb_timer);
    stopwatch_reset(&array_setb_stosw_timer);
    stopwatch_reset(&array_setb_stosl_timer);

    stopwatch_run(&array_setb_timer);
    int set1b = array_setb(s, s2[0], slen);
    stopwatch_stop(&array_setb_timer);

    stopwatch_run(&array_setb2_timer);
    int set1b2 = array_setb2(s, s2[0], slen);
    stopwatch_stop(&array_setb2_timer);

    stopwatch_run(&array_setb4_timer);
    int set1b4 = array_setb4(s, s2[0], slen);
    stopwatch_stop(&array_setb4_timer);

    stopwatch_run(&array_setb_stosb_timer);
    int set2b = array_setb_stosb(s, s2[0], slen);
    stopwatch_stop(&array_setb_stosb_timer);

    stopwatch_run(&array_setb_stosw_timer);
    int set3b = array_setb_stosw(s, s2[0], slen);
    stopwatch_stop(&array_setb_stosw_timer);

    stopwatch_run(&array_setb_stosl_timer);
    int set4b = array_setb_stosl(s, s2[0], slen);
    stopwatch_stop(&array_setb_stosl_timer);

    printf("set1b = %d, set1b2 = %d, set1b4 = %d, set2b = %d, set3b = %d, set4b = %d\n", set1b, set1b2, set1b4, set2b, set3b, set4b);
    stopwatch_print(&array_setb_timer);
    stopwatch_print(&array_setb2_timer);
    stopwatch_print(&array_setb4_timer);
    stopwatch_print(&array_setb_stosb_timer);
    stopwatch_print(&array_setb_stosw_timer);
    stopwatch_print(&array_setb_stosl_timer);
  } else if (!strcmp(argv[1], "array_setw")) {
    struct time array_setw_timer;
    struct time array_setw2_timer;
    struct time array_setw_stosw_timer;
    struct time array_setw_stosl_timer;

    stopwatch_reset(&array_setw_timer);
    stopwatch_reset(&array_setw2_timer);
    stopwatch_reset(&array_setw_stosw_timer);
    stopwatch_reset(&array_setw_stosl_timer);

    stopwatch_run(&array_setw_timer);
    int set1w = array_setw(s, s2[0], slen/2);
    stopwatch_stop(&array_setw_timer);

    stopwatch_run(&array_setw2_timer);
    int set1w2 = array_setw2(s, s2[0], slen/2);
    stopwatch_stop(&array_setw2_timer);

    stopwatch_run(&array_setw_stosw_timer);
    int set2w = array_setw_stosw(s, s2[0], slen/2);
    stopwatch_stop(&array_setw_stosw_timer);

    stopwatch_run(&array_setw_stosl_timer);
    int set3w = array_setw_stosl(s, s2[0], slen/2);
    stopwatch_stop(&array_setw_stosl_timer);

    printf("set1w = %d, set1w2 = %d, set2w = %d, set3w = %d\n", set1w, set1w2, set2w, set3w);
    stopwatch_print(&array_setw_timer);
    stopwatch_print(&array_setw2_timer);
    stopwatch_print(&array_setw_stosw_timer);
    stopwatch_print(&array_setw_stosl_timer);
  } else if (!strcmp(argv[1], "array_setl")) {
    struct time array_setl_timer;
    struct time array_setl_stosl_timer;

    stopwatch_reset(&array_setl_timer);
    stopwatch_reset(&array_setl_stosl_timer);

    stopwatch_run(&array_setl_timer);
    int set1l = array_setl(s, s2[0], slen/4);
    stopwatch_stop(&array_setl_timer);

    stopwatch_run(&array_setl_stosl_timer);
    int set2l = array_setl_stosl(s, s2[0], slen/4);
    stopwatch_stop(&array_setl_stosl_timer);

    printf("set1l = %d, set2l = %d\n", set1l, set2l);
    stopwatch_print(&array_setl_timer);
    stopwatch_print(&array_setl_stosl_timer);
  } else if (!strcmp(argv[1], "array_findb")) {
    struct time array_findb_timer;
    struct time array_findb_scasb_timer;
    struct time array_findbn_timer;
    struct time array_findbn_scasb_timer;

    stopwatch_reset(&array_findb_timer);
    stopwatch_reset(&array_findb_scasb_timer);
    stopwatch_reset(&array_findbn_timer);
    stopwatch_reset(&array_findbn_scasb_timer);

    stopwatch_run(&array_findb_timer);
    int find1b = array_findb(s, slen, s[slen - 1]);
    stopwatch_stop(&array_findb_timer);

    stopwatch_run(&array_findb_scasb_timer);
    int find2b = array_findb_scasb(s, slen, s[slen - 1]);
    stopwatch_stop(&array_findb_scasb_timer);

    stopwatch_run(&array_findbn_timer);
    int find1bn = array_findb(s, slen, ')');
    stopwatch_stop(&array_findbn_timer);

    stopwatch_run(&array_findbn_scasb_timer);
    int find2bn = array_findb_scasb(s, slen, ')');
    stopwatch_stop(&array_findbn_scasb_timer);

    printf("find1b = %d, find2b = %d, find1bn = %d, find2bn = %d\n", find1b, find2b, find1bn, find2bn);
    stopwatch_print(&array_findb_timer);
    stopwatch_print(&array_findb_scasb_timer);
    stopwatch_print(&array_findbn_timer);
    stopwatch_print(&array_findbn_scasb_timer);

    find1b = array_findb(s, 1, s[0]);
    find2b = array_findb_scasb(s, 1, s[0]);
    find1bn = array_findb(s, 1, ')');
    find2bn = array_findb_scasb(s, 1, ')');
    printf("len1: find1b = %d, find2b = %d, find1bn = %d, find2bn = %d\n", find1b, find2b, find1bn, find2bn);

    find1b = array_findb(s, 0, s[0]);
    find2b = array_findb_scasb(s, 0, s[0]);
    find1bn = array_findb(s, 0, ')');
    find2bn = array_findb_scasb(s, 0, ')');
    printf("len0: find1b = %d, find2b = %d, find1bn = %d, find2bn = %d\n", find1b, find2b, find1bn, find2bn);
  } else if (!strcmp(argv[1], "array_findw")) {
    struct time array_findw_timer;
    struct time array_findw_scasw_timer;
    struct time array_findwn_timer;
    struct time array_findwn_scasw_timer;

    stopwatch_reset(&array_findw_timer);
    stopwatch_reset(&array_findw_scasw_timer);
    stopwatch_reset(&array_findwn_timer);
    stopwatch_reset(&array_findwn_scasw_timer);

    stopwatch_run(&array_findw_timer);
    int find1w = array_findw((uint16_t *)s, slen/2, *((uint16_t *)&s[slen - 2]));
    stopwatch_stop(&array_findw_timer);

    stopwatch_run(&array_findw_scasw_timer);
    int find2w = array_findw_scasw((uint16_t *)s, slen/2, *((uint16_t *)&s[slen - 2]));
    stopwatch_stop(&array_findw_scasw_timer);

    stopwatch_run(&array_findwn_timer);
    int find1wn = array_findw((uint16_t *)s, slen/2, ')');
    stopwatch_stop(&array_findwn_timer);

    stopwatch_run(&array_findwn_scasw_timer);
    int find2wn = array_findw_scasw((uint16_t *)s, slen/2, ')');
    stopwatch_stop(&array_findwn_scasw_timer);

    printf("find1w = %d, find2w = %d, find1wn = %d, find2wn = %d\n", find1w, find2w, find1wn, find2wn);
    stopwatch_print(&array_findw_timer);
    stopwatch_print(&array_findw_scasw_timer);
    stopwatch_print(&array_findwn_timer);
    stopwatch_print(&array_findwn_scasw_timer);

    find1w = array_findw((uint16_t *)s, 1, s[0]);
    find2w = array_findw_scasw((uint16_t *)s, 1, s[0]);
    find1wn = array_findw((uint16_t *)s, 1, ')');
    find2wn = array_findw_scasw((uint16_t *)s, 1, ')');
    printf("len1: find1w = %d, find2w = %d, find1wn = %d, find2wn = %d\n", find1w, find2w, find1wn, find2wn);

    find1w = array_findw((uint16_t *)s, 0, *((uint16_t *)&s[0]));
    find2w = array_findw_scasw((uint16_t *)s, 0, *((uint16_t *)&s[0]));
    find1wn = array_findw((uint16_t *)s, 0, ')');
    find2wn = array_findw_scasw((uint16_t *)s, 0, ')');
    printf("len0: find1w = %d, find2w = %d, find1wn = %d, find2wn = %d\n", find1w, find2w, find1wn, find2wn);
  } else if (!strcmp(argv[1], "array_findl")) {
    struct time array_findl_timer;
    struct time array_findl_scasl_timer;
    struct time array_findln_timer;
    struct time array_findln_scasl_timer;

    stopwatch_reset(&array_findl_timer);
    stopwatch_reset(&array_findl_scasl_timer);
    stopwatch_reset(&array_findln_timer);
    stopwatch_reset(&array_findln_scasl_timer);

    stopwatch_run(&array_findl_timer);
    int find1l = array_findl((uint32_t *)s, slen/4, *((uint32_t *)&s[slen - 4]));
    stopwatch_stop(&array_findl_timer);

    stopwatch_run(&array_findl_scasl_timer);
    int find2l = array_findl_scasl((uint32_t *)s, slen/4, *((uint32_t *)&s[slen - 4]));
    stopwatch_stop(&array_findl_scasl_timer);

    stopwatch_run(&array_findln_timer);
    int find1ln = array_findl((uint32_t *)s, slen/4, '(');
    stopwatch_stop(&array_findln_timer);

    stopwatch_run(&array_findln_scasl_timer);
    int find2ln = array_findl_scasl((uint32_t *)s, slen/4, '(');
    stopwatch_stop(&array_findln_scasl_timer);

    printf("find1l = %d, find2l = %d, find1ln = %d, find2ln = %d\n", find1l, find2l, find1ln, find2ln);
    stopwatch_print(&array_findl_timer);
    stopwatch_print(&array_findl_scasl_timer);
    stopwatch_print(&array_findln_timer);
    stopwatch_print(&array_findln_scasl_timer);

    find1l = array_findl((uint32_t *)s, 1, *((uint32_t *)&s[0]));
    find2l = array_findl_scasl((uint32_t *)s, 1, *((uint32_t *)&s[0]));
    find1ln = array_findl((uint32_t *)s, 1, ')');
    find2ln = array_findl_scasl((uint32_t *)s, 1, ')');
    printf("len1: find1l = %d, find2l = %d, find1ln = %d, find2ln = %d\n", find1l, find2l, find1ln, find2ln);

    find1l = array_findl((uint32_t *)s, 0, s[0]);
    find2l = array_findl_scasl((uint32_t *)s, 0, s[0]);
    find1ln = array_findl((uint32_t *)s, 0, ')');
    find2ln = array_findl_scasl((uint32_t *)s, 0, ')');
    printf("len0: find1l = %d, find2l = %d, find1ln = %d, find2ln = %d\n", find1l, find2l, find1ln, find2ln);
  } else if (!strcmp(argv[1], "array_rfindb")) {
    struct time array_rfindb_timer;
    struct time array_rfindb_scasb_timer;
    struct time array_rfindbn_timer;
    struct time array_rfindbn_scasb_timer;

    stopwatch_reset(&array_rfindb_timer);
    stopwatch_reset(&array_rfindb_scasb_timer);
    stopwatch_reset(&array_rfindbn_timer);
    stopwatch_reset(&array_rfindbn_scasb_timer);

    stopwatch_run(&array_rfindb_timer);
    int rfind1b = array_rfindb(s, slen, s[0]);
    stopwatch_stop(&array_rfindb_timer);

    stopwatch_run(&array_rfindb_scasb_timer);
    int rfind2b = array_rfindb_scasb(s, slen, s[0]);
    stopwatch_stop(&array_rfindb_scasb_timer);

    stopwatch_run(&array_rfindbn_timer);
    int rfind1bn = array_rfindb(s, slen, ')');
    stopwatch_stop(&array_rfindbn_timer);

    stopwatch_run(&array_rfindbn_scasb_timer);
    int rfind2bn = array_rfindb_scasb(s, slen, ')');
    stopwatch_stop(&array_rfindbn_scasb_timer);

    printf("rfind1b = %d, rfind2b = %d, rfind1bn = %d, rfind2bn = %d\n", rfind1b, rfind2b, rfind1bn, rfind2bn);
    stopwatch_print(&array_rfindb_timer);
    stopwatch_print(&array_rfindb_scasb_timer);
    stopwatch_print(&array_rfindbn_timer);
    stopwatch_print(&array_rfindbn_scasb_timer);

    rfind1b = array_rfindb(s, 1, s[0]);
    rfind2b = array_rfindb_scasb(s, 1, s[0]);
    rfind1bn = array_rfindb(s, 1, ')');
    rfind2bn = array_rfindb_scasb(s, 1, ')');
    printf("len1: rfind1b = %d, rfind2b = %d, rfind1bn = %d, rfind2bn = %d\n", rfind1b, rfind2b, rfind1bn, rfind2bn);

    rfind1b = array_rfindb(s, 0, s[0]);
    rfind2b = array_rfindb_scasb(s, 0, s[0]);
    rfind1bn = array_rfindb(s, 0, ')');
    rfind2bn = array_rfindb_scasb(s, 0, ')');
    printf("len0: rfind1b = %d, rfind2b = %d, rfind1bn = %d, rfind2bn = %d\n", rfind1b, rfind2b, rfind1bn, rfind2bn);
  } else if (!strcmp(argv[1], "array_rfindw")) {
    struct time array_rfindw_timer;
    struct time array_rfindw_scasw_timer;
    struct time array_rfindwn_timer;
    struct time array_rfindwn_scasw_timer;

    stopwatch_reset(&array_rfindw_timer);
    stopwatch_reset(&array_rfindw_scasw_timer);
    stopwatch_reset(&array_rfindwn_timer);
    stopwatch_reset(&array_rfindwn_scasw_timer);

    stopwatch_run(&array_rfindw_timer);
    int rfind1w = array_rfindw((uint16_t *)s, slen/2, *((uint16_t *)&s[0]));
    stopwatch_stop(&array_rfindw_timer);

    stopwatch_run(&array_rfindw_scasw_timer);
    int rfind2w = array_rfindw_scasw((uint16_t *)s, slen/2, *((uint16_t *)&s[0]));
    stopwatch_stop(&array_rfindw_scasw_timer);

    stopwatch_run(&array_rfindwn_timer);
    int rfind1wn = array_rfindw((uint16_t *)s, slen/2, '(');
    stopwatch_stop(&array_rfindwn_timer);

    stopwatch_run(&array_rfindwn_scasw_timer);
    int rfind2wn = array_rfindw_scasw((uint16_t *)s, slen/2, '(');
    stopwatch_stop(&array_rfindwn_scasw_timer);

    printf("rfind1w = %d, rfind2w = %d, rfind1wn = %d, rfind2wn = %d\n", rfind1w, rfind2w, rfind1wn, rfind2wn);
    stopwatch_print(&array_rfindw_timer);
    stopwatch_print(&array_rfindw_scasw_timer);
    stopwatch_print(&array_rfindwn_timer);
    stopwatch_print(&array_rfindwn_scasw_timer);

    rfind1w = array_rfindw((uint16_t *)s, 1, s[0]);
    rfind2w = array_rfindw_scasw((uint16_t *)s, 1, s[0]);
    rfind1wn = array_rfindw((uint16_t *)s, 1, ')');
    rfind2wn = array_rfindw_scasw((uint16_t *)s, 1, ')');
    printf("len1: rfind1w = %d, rfind2w = %d, rfind1wn = %d, rfind2wn = %d\n", rfind1w, rfind2w, rfind1wn, rfind2wn);

    rfind1w = array_rfindw((uint16_t *)s, 0, s[0]);
    rfind2w = array_rfindw_scasw((uint16_t *)s, 0, s[0]);
    rfind1wn = array_rfindw((uint16_t *)s, 0, ')');
    rfind2wn = array_rfindw_scasw((uint16_t *)s, 0, ')');
    printf("len0: rfind1w = %d, rfind2w = %d, rfind1wn = %d, rfind2wn = %d\n", rfind1w, rfind2w, rfind1wn, rfind2wn);
  } else if (!strcmp(argv[1], "array_rfindl")) {
    struct time array_rfindl_timer;
    struct time array_rfindl_scasl_timer;
    struct time array_rfindln_timer;
    struct time array_rfindln_scasl_timer;

    stopwatch_reset(&array_rfindl_timer);
    stopwatch_reset(&array_rfindl_scasl_timer);
    stopwatch_reset(&array_rfindln_timer);
    stopwatch_reset(&array_rfindln_scasl_timer);

    stopwatch_run(&array_rfindl_timer);
    int rfind1l = array_rfindl((uint32_t *)s, slen/4, *((uint32_t *)&s[0]));
    stopwatch_stop(&array_rfindl_timer);

    stopwatch_run(&array_rfindl_scasl_timer);
    int rfind2l = array_rfindl_scasl((uint32_t *)s, slen/4, *((uint32_t *)&s[0]));
    stopwatch_stop(&array_rfindl_scasl_timer);

    stopwatch_run(&array_rfindln_timer);
    int rfind1ln = array_rfindl((uint32_t *)s, slen/4, ')');
    stopwatch_stop(&array_rfindln_timer);

    stopwatch_run(&array_rfindln_scasl_timer);
    int rfind2ln = array_rfindl_scasl((uint32_t *)s, slen/4, ')');
    stopwatch_stop(&array_rfindln_scasl_timer);

    printf("rfind1l = %d, rfind2l = %d, rfind1ln = %d, rfind2ln = %d\n", rfind1l, rfind2l, rfind1ln, rfind2ln);
    stopwatch_print(&array_rfindl_timer);
    stopwatch_print(&array_rfindl_scasl_timer);
    stopwatch_print(&array_rfindln_timer);
    stopwatch_print(&array_rfindln_scasl_timer);

    rfind1l = array_rfindl((uint32_t *)s, 1, s[0]);
    rfind2l = array_rfindl_scasl((uint32_t *)s, 1, s[0]);
    rfind1ln = array_rfindl((uint32_t *)s, 1, ')');
    rfind2ln = array_rfindl_scasl((uint32_t *)s, 1, ')');
    printf("len1: rfind1l = %d, rfind2l = %d, rfind1ln = %d, rfind2ln = %d\n", rfind1l, rfind2l, rfind1ln, rfind2ln);

    rfind1l = array_rfindl((uint32_t *)s, 0, s[0]);
    rfind2l = array_rfindl_scasl((uint32_t *)s, 0, s[0]);
    rfind1ln = array_rfindl((uint32_t *)s, 0, ')');
    rfind2ln = array_rfindl_scasl((uint32_t *)s, 0, ')');
    printf("len0: rfind1l = %d, rfind2l = %d, rfind1ln = %d, rfind2ln = %d\n", rfind1l, rfind2l, rfind1ln, rfind2ln);

  } else if (!strcmp(argv[1], "strlen")) { //call it array_find and show results for uint16_t
    struct time my_strlen_timer;
    struct time my_strlen_scasb_timer;
    //struct time my_strlen_scasb2_timer;

    stopwatch_reset(&my_strlen_timer);
    stopwatch_reset(&my_strlen_scasb_timer);
    //stopwatch_reset(&my_strlen_scasb2_timer);
    size_t len1 = 0, len2 = 0, len3 = 0;
    
    stopwatch_run(&my_strlen_timer);
    len1 = my_strlen(s);
    stopwatch_stop(&my_strlen_timer);

    stopwatch_run(&my_strlen_scasb_timer);
    len2 = my_strlen_scasb(s);
    stopwatch_stop(&my_strlen_scasb_timer);

    //stopwatch_run(&my_strlen_scasb2_timer);
    //len3 = my_strlen_scasb2(s);
    //stopwatch_stop(&my_strlen_scasb2_timer);


    printf("len1 = %zd, len2 = %zd\n", len1, len2);
    stopwatch_print(&my_strlen_timer);
    stopwatch_print(&my_strlen_scasb_timer);
    //stopwatch_print(&my_strlen_scasb2_timer);

/*
    struct time my_strlenw_timer;
    struct time my_strlen_scasw_timer;
    struct time my_strlen_scasw2_timer;

    stopwatch_reset(&my_strlenw_timer);
    stopwatch_reset(&my_strlen_scasw_timer);
    stopwatch_reset(&my_strlen_scasw2_timer);
    
    stopwatch_run(&my_strlenw_timer);
    size_t len1w = my_strlenw((uint16_t *)s);
    stopwatch_stop(&my_strlenw_timer);

    stopwatch_run(&my_strlen_scasw_timer);
    size_t len2w = my_strlen_scasw((uint16_t *)s);
    stopwatch_stop(&my_strlen_scasw_timer);

    stopwatch_run(&my_strlen_scasw2_timer);
    size_t len3w = my_strlen_scasw2((uint16_t *)s);
    stopwatch_stop(&my_strlen_scasw2_timer);

    printf("len1w = %zd, len2w = %zd, len3w = %zd\n", len1w, len2w, len3w);
    stopwatch_print(&my_strlenw_timer);
    stopwatch_print(&my_strlen_scasw_timer);
    stopwatch_print(&my_strlen_scasw2_timer);


    struct time my_strlend_timer;
    struct time my_strlen_scasd_timer;
    struct time my_strlen_scasd2_timer;

    stopwatch_reset(&my_strlend_timer);
    stopwatch_reset(&my_strlen_scasd_timer);
    stopwatch_reset(&my_strlen_scasd2_timer);
    
    stopwatch_run(&my_strlend_timer);
    size_t len1d = my_strlend((uint32_t *)s);
    stopwatch_stop(&my_strlend_timer);
    size_t len2d = 0, len3d = 0;
    stopwatch_run(&my_strlen_scasd_timer);
    len2d = my_strlen_scasd((uint32_t *)s);
    stopwatch_stop(&my_strlen_scasd_timer);

    stopwatch_run(&my_strlen_scasd2_timer);
    len3d = my_strlen_scasd2((uint32_t *)s);
    stopwatch_stop(&my_strlen_scasd2_timer);

    printf("len1d = %zd, len2d = %zd, len3d = %zd\n", len1d, len2d, len3d);
    stopwatch_print(&my_strlend_timer);
    stopwatch_print(&my_strlen_scasd_timer);
    stopwatch_print(&my_strlen_scasd2_timer);*/

    exit(0);
  } else if (!strcmp(argv[1], "strrchr")) {
    struct time my_strrchr_timer;
    struct time my_strrchr_scasb_timer;
    struct time my_strrchr1_timer;
    struct time my_strrchr1_scasb_timer;
    struct time my_strrchrn_timer;
    struct time my_strrchrn_scasb_timer;

    stopwatch_reset(&my_strrchr_timer);
    stopwatch_reset(&my_strrchr_scasb_timer);
    stopwatch_reset(&my_strrchr1_timer);
    stopwatch_reset(&my_strrchr1_scasb_timer);
    stopwatch_reset(&my_strrchrn_timer);
    stopwatch_reset(&my_strrchrn_scasb_timer);
    
    stopwatch_run(&my_strrchr_timer);
    char *strrchr_out = my_strrchr(s, s[0]);
    stopwatch_stop(&my_strrchr_timer);

    stopwatch_run(&my_strrchr_scasb_timer);
    char *strrchr_scasb_out = my_strrchr_scasb(s, s[0]);
    stopwatch_stop(&my_strrchr_scasb_timer);

    stopwatch_run(&my_strrchr1_timer);
    char *strrchr1_out = my_strrchr(s, s[1]);
    stopwatch_stop(&my_strrchr1_timer);

    stopwatch_run(&my_strrchr1_scasb_timer);
    char *strrchr1_scasb_out = my_strrchr_scasb(s, s[1]);
    stopwatch_stop(&my_strrchr1_scasb_timer);

    stopwatch_run(&my_strrchrn_timer);
    char *strrchrn_out = my_strrchr(s, '(');
    stopwatch_stop(&my_strrchrn_timer);

    stopwatch_run(&my_strrchrn_scasb_timer);
    char *strrchrn_scasb_out = my_strrchr_scasb(s, '(');
    stopwatch_stop(&my_strrchrn_scasb_timer);

    printf("s = %p, strrchr_out = %p, strrchr_scasb_out = %p, strrchr1_out = %p, strrchr1_scasb_out = %p, strrchrn_out = %p, strrchrn_scasb_out = %p\n", s, strrchr_out, strrchr_scasb_out, strrchr1_out, strrchr1_scasb_out, strrchrn_out, strrchrn_scasb_out);
    stopwatch_print(&my_strrchr_timer);
    stopwatch_print(&my_strrchr_scasb_timer);
    stopwatch_print(&my_strrchr1_timer);
    stopwatch_print(&my_strrchr1_scasb_timer);
    stopwatch_print(&my_strrchrn_timer);
    stopwatch_print(&my_strrchrn_scasb_timer);

    exit(0);
  } else if (!strcmp(argv[1], "strcmp")) {
    struct time my_strcmp_timer;
    struct time my_strcmp_cmpsb_timer;
    struct time my_strcmpn_timer;
    struct time my_strcmpn_cmpsb_timer;

    stopwatch_reset(&my_strcmp_timer);
    stopwatch_reset(&my_strcmp_cmpsb_timer);
    stopwatch_reset(&my_strcmpn_timer);
    stopwatch_reset(&my_strcmpn_cmpsb_timer);
    
    stopwatch_run(&my_strcmp_timer);
    int strcmp_out = my_strcmp(s, s2);
    stopwatch_stop(&my_strcmp_timer);

    stopwatch_run(&my_strcmp_cmpsb_timer);
    int strcmp_cmpsb_out = my_strcmp_cmpsb(s, s2);
    stopwatch_stop(&my_strcmp_cmpsb_timer);

    stopwatch_run(&my_strcmpn_timer);
    int strcmpn_out = my_strcmp(s, s3);
    stopwatch_stop(&my_strcmpn_timer);

    stopwatch_run(&my_strcmpn_cmpsb_timer);
    int strcmpn_cmpsb_out = my_strcmp_cmpsb(s, s3);
    stopwatch_stop(&my_strcmpn_cmpsb_timer);

    printf("strcmp_out = %d, strcmp_cmpsb_out = %d, strcmpn_out = %d, strcmpn_cmpsb_out = %d\n", strcmp_out, strcmp_cmpsb_out, strcmpn_out, strcmpn_cmpsb_out);
    stopwatch_print(&my_strcmp_timer);
    stopwatch_print(&my_strcmp_cmpsb_timer);
    stopwatch_print(&my_strcmpn_timer);
    stopwatch_print(&my_strcmpn_cmpsb_timer);
    exit(0);
  } else if (!strcmp(argv[1], "count_ones")) {
    struct time count_ones_timer;
    struct time count_ones_popcnt_timer;

    stopwatch_reset(&count_ones_timer);
    stopwatch_reset(&count_ones_popcnt_timer);
    
    stopwatch_run(&count_ones_timer);
    int count_ones_out = count_ones32((uint32_t *)s, slen/4);
    stopwatch_stop(&count_ones_timer);

    stopwatch_run(&count_ones_popcnt_timer);
    int count_ones_popcnt_out = count_ones_popcnt32((uint32_t *)s, slen/4);
    stopwatch_stop(&count_ones_popcnt_timer);

    printf("count_ones_out = %d, count_ones_popcnt_out = %d\n", count_ones_out, count_ones_popcnt_out);
    stopwatch_print(&count_ones_timer);
    stopwatch_print(&count_ones_popcnt_timer);
    exit(0);
  } else if (!strcmp(argv[1], "sum8")) {
    int ret;
    ret = sum8(argc - 1, argv + 1);
    ret += cp_test(argc - 1);
    printf("Summed an array of 8-bit elements of size %d.\n", ret);
    return 0;
  }
  return 0;
}
