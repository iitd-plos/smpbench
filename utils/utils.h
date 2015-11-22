#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#define ASSERT assert

pid_t xfork(char const *path, char *const args[]);

struct profile_struct;

void profile_init(void);
struct profile_struct *profile_start(char const *bmark);
void profile_stop(struct profile_struct *ps, int error);

uint32_t str2int(char const *str);

static inline unsigned long long
rdtsc(void) {
  uint32_t lo, hi;
  /* We cannot use "=A", since this would use %rax on x86_64 */
  asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
  return (uint64_t)hi << 32 | lo;
}

/* Optimization barrier.

   The compiler will not reorder operations across an
   optimization barrier.  See "Optimization Barriers" in the
   reference guide for more information.*/
#define barrier() asm volatile ("" : : : "memory")

#endif /* utils.h */
