#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define TOTAL 0x2000000

int big_arr1[TOTAL];
int big_arr2[TOTAL];

int nthreads = 0;

void *
my_thread(void *arg)
{
  int i;
  int index = *((int *)arg);
	int step = (TOTAL / nthreads);
	int start = index * step;
	int end = start + step;
  for(i = start; i < end; i++) {
		big_arr1[i] = 1;
		big_arr2[i] = 10;
  }
  return NULL;
}

#define MAX_THREADS 256

int
main(int argc, char const *argv[])
{
  pthread_t threads[MAX_THREADS];
  int ret, i;

  if (argc != 2) {
    printf("Usage: sharedvar <num-threads>\n");
    exit(1);
  }
  nthreads = atoi(argv[1]);
  assert(nthreads > 0);
  assert(nthreads <= MAX_THREADS);

  for (i = 0; i < nthreads; i++) {
    int *arg = malloc(sizeof(int));
    assert(arg);
    *arg = i;
    if ((ret = pthread_create(&threads[i], NULL, my_thread, arg))) {
      fprintf(stderr, "ERROR: Creating Pthread\n");
    }
  }
  for (i = 0; i < nthreads; i++) {
    pthread_join(threads[i], NULL);
  }
}
