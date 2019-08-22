#ifndef CTESTS_HELPER_H
#define CTESTS_HELPER_H

void myexit(int ec);
void mymemset(void *s, int c, size_t n);
void *mymemcpy(void *a, const void *b, size_t sz);
int mymemcmp(const void *a, const void *b, size_t sz);
int mystrcmp(const char *s1, const char *s2);
int mystrncmp(const char *s1, const char *s2, size_t n);
int my_atoi(char const *s);
int myrand();
char my_char_inc(char const *i);
int myrand_char();
void myprint_char(char c);
void myprint_int(int c);
void myfree(void *ptr);
void *mycalloc(size_t nmemb, size_t size);
char *mystrdup(char const *);
FILE *myfopen(char const *path, char const *mode);
void *myrealloc(void *ptr, size_t size);
int mytoupper(int c);

#define atoi my_atoi
#define memset mymemset
#define memcpy mymemcpy
#define memcmp mymemcmp
#define strcmp mystrcmp
#define strncmp mystrncmp


#endif
