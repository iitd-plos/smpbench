#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

void *mymalloc(size_t size)
{
  return (void *)malloc(size);
}

void *mycalloc(size_t nmemb, size_t size)
{
  return (void *)calloc(nmemb, size);
}

void *myrealloc(void *ptr, size_t size)
{
  return (void *)realloc(ptr, size);
}

FILE *myfopen(char const *path, char const *mode)
{
  return fopen(path, mode);
}

FILE *myfdopen(int fd, char const *mode)
{
  return fdopen(fd, mode);
}

FILE *myfreopen(char const *path, char const *mode, FILE *stream)
{
  return freopen(path, mode, stream);
}

int myfclose(FILE *fp)
{
  return fclose(fp);
}

void myfree(void *ptr)
{
  free(ptr);
}


int
my_atoi(char const *s)
{
  return atoi(s);
}

int myrand()
{
  return rand();
}

char my_char_inc(char *i)
{
  char ret = *i + 1;
  *i = ret;
  return ret;
}

size_t address_taken_local_var_callee(char **a, char **b, char **c, char **d)
{
  return b - a + (d - c) + 2;
}

int myrand_char()
{
  return rand() % 255;
}

void
myprint_char(char c)
{
  printf("%c", c);
}

void
myprint_int(int c)
{
  printf("%d", c);
}

char *
mystrdup(char const *s)
{
  return strdup(s);
}

int mytoupper(int c)
{
  return toupper(c);
}

char*
mystrerrorno()
{
  return strerror(errno);
}
