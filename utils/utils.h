#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#define ASSERT assert

pid_t xfork(char const *path, char *const args[]);
void xsystem(char const *path, char *const args[]);

void profile_init(void);
void profile_flush(void);
void profile_start(char const *bmark);
void profile_stop(int error);

void set_microrollbacks(void);
void microrollback_trigger(void);

uint32_t str2int(char const *str);

static unsigned long long
rdtsc(void) {
  uint32_t lo, hi;
  /* We cannot use "=A", since this would use %rax on x86_64 */
  asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
  return (uint64_t)hi << 32 | lo;
}

void timer_calibrate(void);
void busy_wait(size_t useconds);

/* Optimization barrier.

   The compiler will not reorder operations across an
   optimization barrier.  See "Optimization Barriers" in the
   reference guide for more information.*/
#define barrier() asm volatile ("" : : : "memory")

#endif /* utils.h */
