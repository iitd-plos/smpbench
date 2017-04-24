#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>

//const char interp_section[] __attribute__((section(".interp"))) = "/path/to/dynamic/linker";

void myexit(int ec)
{
  exit(ec);
}

#define NDATA (int *)mymalloc(ncol * sizeof(int))
#define NLIST (struct _list *)mymalloc(sizeof(struct _list))
#define NPLAY (struct _play *)mymalloc(sizeof(struct _play))
void mymemset(void *s, int c, size_t n)
{
  memset(s,c,n);
}

void *mymemcpy(void *a, const void *b, size_t sz)
{
  return memcpy(a, b, sz);
}

int mymemcmp(const void *a, const void *b, size_t sz)
{
  return memcmp(a, b, sz);
}

int mystrcmp(const char *s1, const char *s2)
{
  return strcmp(s1,s2);
}

int mystrncmp(const char *s1, const char *s2, size_t n)
{
  return strncmp(s1,s2,n);
}

int *mymalloc(size_t size)
{
  return (int *)malloc(size);
}

int
my_atoi(char const *s)
{
  return atoi(s);
}

size_t address_taken_local_var_callee(char **a, char **b, char **c, char **d)
{
  return b - a + (d - c) + 2;
}
