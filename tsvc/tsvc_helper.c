#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <assert.h>

void __VERIFIER_error() __attribute__ ((__noreturn__));

void __VERIFIER_error()
{
  myexit(1);
}

void __VERIFIER_assume(int a)
{
  assert(a);
}

char __VERIFIER_nondet_char(void)
{
  return (char)rand();
}

unsigned char __VERIFIER_nondet_uchar(void)
{
  return (unsigned char)rand();
}

int __VERIFIER_nondet_int()
{
  return rand();
}

short __VERIFIER_nondet_short()
{
  return (short)rand();
}
long __VERIFIER_nondet_long(void)
{
  return (long)rand();
}

void *__VERIFIER_nondet_pointer(void)
{
  return (void*)rand();
}

unsigned long __VERIFIER_nondet_ulong(void)
{
  return (unsigned long)rand();
}

void myexit(int ec)
{
  exit(ec);
}

void myabort()
{
  abort();
}

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

/* FILE *myfdopen(int fd, char const *mode) */
/* { */
/*   return fdopen(fd, mode); */
/* } */

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

/* char * */
/* mystrdup(char const *s) */
/* { */
/*   return strdup(s); */
/* } */
