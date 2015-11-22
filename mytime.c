#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "utils.h"

static void
usage(void)
{
  printf("Usage: mytime <benchmark-name> <command> <args> . . .\n");
  exit(1);
}

int
main(int argc, char **argv)
{
  struct profile_struct *ps;
  int child_exit_status;
  struct rusage rusage;

  if (argc <= 2) {
    usage();
  }
  char const *bname = argv[1];
  int i;

  profile_init();

  ps = profile_start(bname);

  pid_t child = xfork(argv[2], &argv[2]);
  wait4(child, &child_exit_status, 0, &rusage);

  profile_stop(ps, child_exit_status);

  return 0;
}
