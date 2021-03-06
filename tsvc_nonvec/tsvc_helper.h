#ifndef TSVC_HELPER_H

#define TSVC_HELPER_H


int dummy(float a[LEN], float b[LEN], float c[LEN], float d[LEN], float e[LEN], float aa[LEN2][LEN2], float bb[LEN2][LEN2], float cc[LEN2][LEN2], float s);

void MYmyexit(int ec);

void MYmymemset(void *s, int c, size_t n);

void *MYmymemcpy(void *a, const void *b, size_t sz);

int MYmymemcmp(const void *a, const void *b, size_t sz);

int MYmystrcmp(const char *s1, const char *s2);

int MYmystrncmp(const char *s1, const char *s2, size_t n);

int MYmy_atoi(char const *s);

int MYmyrand();

char MYmy_char_inc(char const *i);

int MYmyrand_char();

void MYmyprint_char(char c);

void MYmyprint_int(int c);

void MYmyfree(void *ptr);

void *MYmycalloc(size_t nmemb, size_t size);

char *MYmystrdup(char const *);

FILE *MYmyfopen(char const *path, char const *mode);

void *MYmyrealloc(void *ptr, size_t size);

int MYmytoupper(int c);

char* MYmystrerrno();

void MYmydebug(int n);



#define atoi MYmy_atoi

#define memset MYmymemset

#define memcpy MYmymemcpy

#define memcmp MYmymemcmp

#define strcmp MYmystrcmp

#define strncmp MYmystrncmp



#define DBG(l) MYmydebug(l)





#endif
