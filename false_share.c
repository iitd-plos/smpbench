#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define PGSIZE 4096
#define CACHE_ALIGNMENT 64
struct shared_page {
  unsigned long long arr[PGSIZE/sizeof(unsigned long long)];
} __attribute__ ((aligned(PGSIZE)));

int step = CACHE_ALIGNMENT/sizeof(unsigned long long);
struct shared_page sp;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void atomic_inc(int index)
{
  //pthread_mutex_lock(&mutex);
  assert(index * step < PGSIZE);
  sp.arr[index * step]++;
  //pthread_mutex_unlock(&mutex);
}

#define TOTAL 500000000
int count = 0;
int nthreads = 0;
void *
my_thread(void *arg)
{
  int i;
  int index = *((int *)arg);
  for(i = 0; i < TOTAL; i++) {
    atomic_inc(index);
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
  printf("count=%d\n", count);
}
