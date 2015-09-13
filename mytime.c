#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"

static void
usage(void)
{
  printf("Usage: mytime <num-iter> <command> <args> . . .\n");
  exit(1);
}

int
main(int argc, char **argv)
{
  if (argc <= 2) {
    usage();
  }
  int num_iter = atoi(argv[1]);
  char const *bname = argv[2];
  if (!num_iter) {
    usage();
  }
  profile_init();
  //argv[2] = "/usr/bin/time";
  int i;
  profile_start(bname);
  for (i = 0; i < num_iter; i++) {
    pid_t child = xfork(argv[3], &argv[3]);
    waitpid(child, NULL, 0);
  }
  profile_stop(0);
  return 0;
}
