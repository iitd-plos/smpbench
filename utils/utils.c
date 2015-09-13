#include "utils.h"
#include "config.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <assert.h>
#include "mysyscalls.h"
#define PROCESSOR_FREQ 2.27e+9

static char const *cur_profile = NULL;
static unsigned long long start_tsc = 0;
int is_native = 0;
static double freq = 0;

void
profile_init(void)
{
	freq = 2.53e+9;
}

void
profile_start(char const *bmark)
{
  char const *p;
  cur_profile = bmark;
  start_tsc = rdtsc();

  /* Tell VMM to start profiling */
  for (p = cur_profile; *p; p++) {
    outl(*p, 0);
  }
  outl('\0', 0);
  outl(1, 0);
}

void
profile_stop(int error)
{
  unsigned long long cur_tsc = rdtsc();
  char output[1024];
  FILE *fp;
  snprintf(output, sizeof output, "BMARK -> %s: %llx : %lf\n", cur_profile, cur_tsc - start_tsc,
    (cur_tsc - start_tsc)/freq);
  fp = fopen(BUILD_DIR "/profile.results", "a");
  ASSERT(fp);
  fprintf(fp, "%s", output);
  printf("%s", output);
  fclose(fp);

  /* Tell VMM to stop profiling */
  if (error) {
    outl(3, 0);
  } else {
    outl(2, 0);
  }

  cur_profile = NULL;
}

void
profile_flush(void)
{
  static long long volatile i;
  printf("%s(): start\n", __func__);
  for (i = 0; i < 40000000ULL; i++);
  printf("%s(): done\n", __func__);
}

uint32_t
str2int(char const *str)
{
  int i;
  uint32_t ret_int;
  int end_reached = 0;
  char *ret = (char *)&ret_int;

  for (i = 0; i < 4; i++) {
    if (!end_reached) {
      ret[i] = str[i];
      if (str[i] == '\0') {
        end_reached = 1;
      }
    } else {
      ret[i] = 0;
    }
  }
  return ret_int;
}

static uint64_t loops_per_usecond = 0;
static void
do_loops(uint64_t loops)
{
  while (loops-- > 0) {
    barrier();
  }
}

void
timer_calibrate(void) 
{
  uint64_t start;
  uint64_t loops = 10000000ULL;
  start = rdtsc();
  do_loops(loops);
  loops_per_usecond = loops/((rdtsc() - start) / (PROCESSOR_FREQ/1e+6));
  /*
  printf("%s(): %lld loops per usecond.\n", __func__,
      (unsigned long long)loops_per_usecond);
      */
}

/* Busy-wait for approximately NUM/DENOM seconds. */
void
busy_wait(size_t useconds)
{
  int64_t loops = loops_per_usecond*useconds;
  assert(loops_per_usecond);
  do_loops(loops);
}

pid_t
xfork(char const *path, char *const args[])
{
  pid_t pid;
  int fd;

  pid = fork();

  if (pid) {
    /* parent */
    return pid;
  }
  /* child */
  execv(path, args);
  printf("execv(%s, %s) failed: %s()\n", path, args[0], strerror(errno));
  exit(1);
}
