#include <linux/unistd.h>
#include <linux/kernel.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define __NR_outl 341
#define __NR_inl  342

extern int is_native;
static inline int
outl(uint32_t value, uint16_t port)
{
  if (is_native) {
    return 0;
  }
  int ret = 0;
  ret = syscall(__NR_outl, value, port);
  if (ret < 0) {
    printf("%s(): syscall(__NR_outl) failed: %s\n", __func__, strerror(errno));
  }
  return ret;
}

static inline uint32_t
inl(uint16_t port)
{
  if (is_native) {
    return 0;
  }
  return syscall(__NR_inl, port);
}
