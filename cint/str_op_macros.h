#define ARRAY_CMPW_REMAINING(a, b, n, ret, i) do { \
  if (ret == 1) { \
    /*__asm volatile("cld\n\t" \
                 "movl $0, %%eax\n\t" \
                 "cmp %%ecx,%%ecx\n\t" \
                 "repe cmbpsb\n\t" \
                 "sete %%al\n\t" \
                 : "=a"(ret) \
                 : "S"(ptr_a), "D"(ptr_b), "c"(n-(ptr_a-a)) \
                 : ); */ \
    for (; i < n; i++) { \
      if (((uint16_t *)a)[i] != ((uint16_t *)b)[i]) { \
        ret = 0; \
        break; \
      } \
    } \
  } \
} while(0)

#define ARRAY_CMPW_REMAINING_PTR(a, b, n, ret, ptr_a, ptr_b) do { \
  if (ret == 1) { \
    /*__asm volatile("cld\n\t" \
                 "movl $0, %%eax\n\t" \
                 "cmp %%ecx,%%ecx\n\t" \
                 "repe cmbpsb\n\t" \
                 "sete %%al\n\t" \
                 : "=a"(ret) \
                 : "S"(ptr_a), "D"(ptr_b), "c"(n-(ptr_a-a)) \
                 : ); */ \
    for (; ptr_a - (uint16_t const *)a < n; ptr_a++, ptr_b++) { \
      if (*ptr_a != *ptr_b) { \
        ret = 0; \
        break; \
      } \
    } \
  } \
} while(0)




#define ARRAY_CMPW_CMPSL_NOITER(a, b, n, ret) do { \
  __asm volatile("cld\n\t" \
               "movl $0, %%eax\n\t" \
               "cmp %%ecx,%%ecx\n\t" \
               "repe cmpsl\n\t" \
               "sete %%al\n\t" \
               : "=a"(ret) \
               : "S"(a), "D"(b), "c" (n/2) \
               : /*"%ecx", "%esi", "%edi"*/); \
  size_t ii_prime = n - (n & 1); \
  ARRAY_CMPW_REMAINING(a, b, n, ret, ii_prime); \
} while (0)

#define MY_STRRCHR_NOITER(haystack, needle, ptr) do { \
  ptr = haystack; \
  while (ptr - haystack != (unsigned long)-1 && *ptr) { ptr++; } \
  if (ptr - haystack == (unsigned long)-1) ptr--; \
  while (ptr - haystack != (unsigned long)-1 && *ptr != needle) { ptr--; } \
} while(0)

#define MY_STRRCHR_SCASB_NOITER(haystack, needle, ret) do { \
  ret = haystack; \
  __asm volatile ("cld\n\t" \
                "movl %%edx,%%edi\n\t" \
                "movl $-1,%%ecx\n\t" \
                "movl $0,%%eax\n\t" \
                "repne scasb\n\t" \
                "negl %%ecx\n\t" \
                "sub $1,%%ecx\n\t" \
                "sub $1,%%edi\n\t" \
                "std\n\t" \
                "movb %%bl,%%al\n\t" \
                "cmpl $1,%%ecx\n\t" \
                "repne scasb\n\t" \
                "setne %%al\n\t" \
                "movzbl %%al,%%eax\n\t" \
                "subl %%eax,%%ecx\n\t" \
                "leal (%%edx,%%ecx,1),%%edi\n\t" \
                : "=D"(ret) \
                : "d"(haystack), "b"(needle) \
                : "%eax", "%ecx"); \
  /*if (ret < haystack && *ret != needle) { \
    ret = NULL; \
  }*/ \
} while(0)

#define ARRAY_RFINDB_NOITER(str, n, needle, ii) do { \
  for (ii = n; ii > 0 && str[ii - 1] != needle; ii--); \
  ii--; \
} while(0)

#define ARRAY_RFINDB_SCASB_NOITER(str, n, needle, ret) do { \
  __asm volatile ("std"); \
  __asm volatile ("movl %%edx, %%edi\n\t" \
                "movl %%esi, %%ecx\n\t" \
                "cmpl $1, %%ecx\n\t" \
                "repne scasb\n\t" \
                "setne %%bl\n\t" \
                "movzbl %%bl, %%ebx\n\t" \
                "subl %%ebx, %%ecx\n\t" \
                : "=c"(ret) \
                : "S"(n), "a"(needle), "d"(str + n - 1) \
                : "%edi","%ebx"); \
} while(0)

#define ARRAY_RFINDW_NOITER(str, n, needle, ii) do { \
  for (ii = n; ii > 0 && str[ii - 1] != needle; ii--); \
  ii--; \
} while (0)

#define ARRAY_RFINDW_SCASW_NOITER(str, n, needle, ret) do { \
  __asm volatile ("std"); \
  __asm volatile ("movl %%edx, %%edi\n\t" \
                "movl %%esi, %%ecx\n\t" \
                "cmpl $1, %%ecx\n\t" \
                "repne scasw\n\t" \
                "setne %%bl\n\t" \
                "movzbl %%bl, %%ebx\n\t" \
                "sub %%ebx, %%ecx\n\t" \
                : "=c"(ret) \
                : "S"(n), "a"(needle), "d"(str + n - 1) \
                : "%edi","%ebx"); \
} while(0)

#define ARRAY_RFINDL_NOITER(str, n, needle, ptr) do { \
  for (ii = n; ii > 0 && str[ii - 1] != needle; ii--); \
  ii--; \
} while(0)

#define ARRAY_RFINDL_SCASL_NOITER(str, n, needle, ret) do { \
  __asm volatile ("std"); \
  __asm volatile ("movl %%edx, %%edi\n\t" \
                "movl %%esi, %%ecx\n\t" \
                "cmpl $1, %%ecx\n\t" \
                "repne scasl\n\t" \
                "setne %%bl\n\t" \
                "movzbl %%bl, %%ebx\n\t" \
                "sub %%ebx, %%ecx\n\t" \
                : "=c"(ret) \
                : "S"(n), "a"(needle), "d"(str + n - 1) \
                : "%edi","%ebx"); \
} while(0)

#define ARRAY_CMPB_NOITER(a, b, n, ret) do { \
  char const *ptr_a, *ptr_b; \
  for (ptr_a = a, ptr_b = b; ptr_a - (char const *)a < n; ptr_a++, ptr_b++) { \
    if (*ptr_a != *ptr_b) { \
      ret = 0; \
      break; \
    } \
  } \
} while(0)

#define ARRAY_CMPB_REMAINING(a, b, n, ret, ptr_a, ptr_b) do { \
  if (ret == 1) { \
    /*__asm volatile("cld\n\t" \
                 "movl $0, %%eax\n\t" \
                 "cmp %%ecx,%%ecx\n\t" \
                 "repe cmbpsb\n\t" \
                 "sete %%al\n\t" \
                 : "=a"(ret) \
                 : "S"(ptr_a), "D"(ptr_b), "c"(n-(ptr_a-a)) \
                 : ); */ \
    for (; ptr_a - (char const *)a < n; ptr_a++, ptr_b++) { \
      if (*ptr_a != *ptr_b) { \
        ret = 0; \
        break; \
      } \
    } \
  } \
} while(0)

#define ARRAY_CMPB2_NOITER(a, b, n, ret) do { \
  char const *ptr_a, *ptr_b; \
  for (ptr_a = a, ptr_b = b; ptr_a - (char const *)a < n && ptr_a - (char const *)a + 1 < n; ptr_a++, ptr_b++) { \
    if (*ptr_a != *ptr_b) { \
      ret = 0; \
      break; \
    } \
    ptr_a++; ptr_b++; \
    if (!(ptr_a - (char const *)a < n)) { /* always false */\
      break; \
    } \
    if (*ptr_a != *ptr_b) { \
      ret = 0; \
      break; \
    } \
  } \
  ARRAY_CMPB_REMAINING(a, b, n, ret, ptr_a, ptr_b); \
} while(0)

#define ARRAY_CMPB4_NOITER(a, b, n, ret) do { \
  char const *ptr_a, *ptr_b; \
  for (ptr_a = a, ptr_b = b; ptr_a - (char const *)a < n && ptr_a - (char const *)a + 1 < n && ptr_a - (char const *)a + 2 < n && ptr_a - (char const *)a + 3 < n; ptr_a++, ptr_b++) { \
    if (*ptr_a != *ptr_b) { \
      ret = 0; \
      break; \
    } \
    ptr_a++; ptr_b++; \
    if (!(ptr_a - (char const *)a < n)) { \
      break; \
    } \
    if (*ptr_a != *ptr_b) { \
      ret = 0; \
      break; \
    } \
    ptr_a++; ptr_b++; \
    if (!(ptr_a - (char const *)a < n)) { \
      break; \
    } \
    if (*ptr_a != *ptr_b) { \
      ret = 0; \
      break; \
    } \
    ptr_a++; ptr_b++; \
    if (!(ptr_a - (char const *)a < n)) { \
      break; \
    } \
    if (*ptr_a != *ptr_b) { \
      ret = 0; \
      break; \
    } \
  } \
  ARRAY_CMPB_REMAINING(a, b, n, ret, ptr_a, ptr_b); \
} while(0)


#define ARRAY_CMPB_CMPSB_NOITER(a, b, n, ret) do { \
  __asm volatile("cld\n\t" \
               "movl $0, %%eax\n\t" \
               "cmp %%ecx,%%ecx\n\t" \
               "repe cmpsb\n\t" \
               "sete %%al\n\t" \
               : "=a"(ret) \
               : "S"(a), "D"(b), "c" (n) \
               : /*"%ecx", "%esi", "%edi"*/); \
} while(0)

#define ARRAY_CMPB_CMPSW_NOITER(a, b, n, ret) do { \
  char const *ptr_a, *ptr_b; \
  int j; \
  /*k = (n/2) * 2;*/ \
  __asm volatile("cld\n\t" \
               "movl $0, %%eax\n\t" \
               "cmp %%ecx,%%ecx\n\t" \
               "repe cmpsw\n\t" \
               "sete %%al\n\t" \
               : "=a"(ret), "=S"(ptr_a), "=D"(ptr_b) \
               : "S"(a), "D"(b), "c" (n/2) \
               : /*"%ecx", "%esi", "%edi"*/); \
  ARRAY_CMPB_REMAINING(a, b, n, ret, ptr_a, ptr_b); \
} while(0)

#define ARRAY_CMPB_CMPSL_NOITER(a, b, n, ret) do { \
  char const *ptr_a, *ptr_b; \
  __asm volatile("cld\n\t" \
               "movl $0, %%eax\n\t" \
               "cmp %%ecx,%%ecx\n\t" \
               "repe cmpsl\n\t" \
               "sete %%al\n\t" \
               : "=a"(ret), "=S"(ptr_a), "=D"(ptr_b) \
               : "S"(a), "D"(b), "c" (n/4) \
               : /*"%ecx", "%esi", "%edi"*/); \
  ARRAY_CMPB_REMAINING(a, b, n, ret, ptr_a, ptr_b); \
} while(0)

#define ARRAY_CMPW_NOITER(a, b, n, ret) do { \
  size_t ii; \
  for (ii = 0; ii < n; ii++) { \
    if (((uint16_t *)a)[ii] != ((uint16_t *)b)[ii]) { \
      ret = 0; \
      break; \
    } \
  } \
} while (0)

#define ARRAY_CMPW2_NOITER(a, b, n, ret) do { \
  size_t ii; \
  for (ii = 0; ii < n && ii + 1 < n; ii++) { \
    if (((uint16_t *)a)[ii] != ((uint16_t *)b)[ii]) { \
      ret = 0; \
      break; \
    } \
    ii++; \
    if (!(ii < n)) { \
      break; \
    } \
    if (((uint16_t *)a)[ii] != ((uint16_t *)b)[ii]) { \
      ret = 0; \
      break; \
    } \
  } \
  ARRAY_CMPW_REMAINING(a, b, n, ret, ii); \
} while (0)

#define ARRAY_CMPW_CMPSW_NOITER(a, b, n, ret) do { \
  __asm volatile("cld\n\t" \
               "movl $0, %%eax\n\t" \
               "cmp %%ecx,%%ecx\n\t" \
               "repe cmpsw\n\t" \
               "sete %%al\n\t" \
               : "=a"(ret) \
               : "S"(a), "D"(b), "c" (n) \
               : /*"%ecx", "%esi", "%edi"*/); \
} while(0)

#define ARRAY_CMPL_NOITER(a, b, n, ret) do { \
  size_t ii; \
  for (ii = 0; ii < n; ii++) { \
    if (((uint32_t *)a)[ii] != ((uint32_t *)b)[ii]) { \
      ret = 0; \
      break; \
    } \
  } \
} while (0)

#define ARRAY_CMPL_CMPSL_NOITER(a, b, n, ret) do {  \
  __asm volatile("cld\n\t" \
               "movl $0, %%eax\n\t" \
               "cmp %%ecx,%%ecx\n\t" \
               "repe cmpsl\n\t" \
               "sete %%al\n\t" \
               : "=a"(ret) \
               : "S"(a), "D"(b), "c" (n) \
               : /*"%ecx", "%esi", "%edi"*/); \
} while(0)

#define ARRAY_SETB_NOITER(dest, fill_value, count) do {\
  char *p; \
  for (p = dest; p - (char *)dest < count; p++) { \
    *p = fill_value; \
  } \
} while(0)

#define ARRAY_SETB_REMAINING(dest, fill_value, count, p) do { \
  for (; p - (char *)dest < count; p++) { \
    *p = fill_value; \
  } \
} while(0)

#define ARRAY_SETB2_NOITER(dest, fill_value, count) do { \
  char *p; \
  for (p = dest; p - (char *)dest < count && p - (char *)dest + 1 < count; p++) { \
    *p = fill_value; \
    p++; \
    if (!(p - (char *)dest < count)) { \
      break; \
    } \
    *p = fill_value; \
  } \
  ARRAY_SETB_REMAINING(dest, fill_value, count, p); \
} while(0)

#define ARRAY_SETB4_NOITER(dest, fill_value, count) do { \
  char *p; \
  for (p = dest; p - (char *)dest < count && p - (char *)dest + 1 < count && p - (char *)dest + 2 < count && p - (char *)dest + 3 < count; p++) { \
    *p = fill_value; \
    p++; \
    if (!(p - (char *)dest < count)) { \
      break; \
    } \
    *p = fill_value; \
    p++; \
    if (!(p - (char *)dest < count)) { \
      break; \
    } \
    *p = fill_value; \
    p++; \
    if (!(p - (char *)dest < count)) { \
      break; \
    } \
    *p = fill_value; \
  } \
  ARRAY_SETB_REMAINING(dest, fill_value, count, p); \
} while(0)

#define ARRAY_SETB_STOSB_NOITER(dest, fill_value, count) do { \
  __asm ("cld\n\t" \
       "rep\n\t" \
       "stosb" \
       : /* no output registers */ \
       : "c" (count), "a" (fill_value), "D" (dest) \
       :/* "%ecx", "%edi" */ \
       ); \
} while(0)

#define ARRAY_SETB_STOSW_NOITER(dest, fill_value, count) do { \
  char *ptr; \
  __asm ("cld\n\t" \
       "rep\n\t" \
       "stosw" \
       : "=D"(ptr) \
       : "c" (count/2), "a" ((fill_value << 8) | fill_value), "D" (dest) \
       :/* "%ecx", "%edi" */ \
       );\
  ARRAY_SETB_REMAINING(dest, fill_value, count, ptr); \
} while(0)

#define ARRAY_SETB_STOSL_NOITER(dest, fill_value, count) do { \
  char *ptr; \
  __asm ("cld\n\t" \
       "rep\n\t" \
       "stosl" \
       : "=D"(ptr) \
       : "c" (count/4), \
         "a" (  (fill_value << 24) \
              | (fill_value << 16) \
              | (fill_value << 8) \
              | fill_value), \
         "D" (dest) \
       :/* "%ecx", "%edi" */ \
       ); \
  ARRAY_SETB_REMAINING(dest, fill_value, count, ptr); \
} while(0)

#define ARRAY_SETW_NOITER(dest, fill_value, count) do { \
  size_t ii; \
  for (ii = 0; ii < count; ii++) { \
    ((uint16_t *)dest)[ii] = fill_value; \
  } \
} while(0)

#define ARRAY_SETW_REMAINING_PTR(dest, fill_value, count, p) do { \
  for (; p - (uint16_t *)dest < count; p++) { \
    *p = fill_value; \
  } \
} while(0)

#define ARRAY_SETW_REMAINING(dest, fill_value, count, ii) do { \
  for (; ii < count; ii++) { \
    ((uint16_t *)dest)[ii] = fill_value; \
  } \
} while(0)

#define ARRAY_SETW2_NOITER(dest, fill_value, count) do { \
  size_t ii; \
  for (ii = 0; ii < count && ii + 1 < count; ii++) { \
    ((uint16_t *)dest)[ii] = fill_value; \
    ii++; \
    if (!(ii < count)) { \
      break; \
    } \
    ((uint16_t *)dest)[ii] = fill_value; \
  } \
  ARRAY_SETW_REMAINING(dest, fill_value, count, ii); \
} while(0)

#define ARRAY_SETW_STOSW_NOITER(dest, fill_value, count) do { \
  __asm ("cld\n\t" \
       "rep\n\t" \
       "stosw" \
       : /* no output registers */ \
       : "c" (count), "a" (fill_value), "D" (dest) \
       :/* "%ecx", "%edi" */ \
       ); \
} while(0)

#define ARRAY_SETW_STOSL_NOITER(dest, fill_value, count) do { \
  __asm ("cld\n\t" \
       "rep\n\t" \
       "stosl" \
       : \
       : "c" (count/2), "a" ((fill_value << 16) | fill_value), "D" (dest) \
       :/* "%ecx", "%edi" */ \
       ); \
  size_t ii_prime = count - (count & 1); \
  ARRAY_SETW_REMAINING(dest, fill_value, count, ii_prime); \
} while(0)

#define ARRAY_SETL_NOITER(dest, fill_Value, count) do { \
  size_t ii; \
  for (ii = 0; ii < count; ii++) { \
    ((uint32_t *)dest)[ii] = fill_value; \
  } \
} while(0)

#define ARRAY_SETL_STOSL_NOITER(dest, fill_value, count) do  {\
  __asm ("cld\n\t" \
       "rep\n\t" \
       "stosl" \
       : /* no output registers */ \
       : "c" (count), "a" (fill_value), "D" (dest) \
       : /* "%ecx", "%edi" */ \
       ); \
} while(0)

#define ARRAY_FINDB_NOITER(str, n, needle, ptr, ret) do { \
  for (ptr = str; (ptr - str < n) && *ptr != needle; ptr++); \
  ret = ptr - str; \
} while(0)

#define ARRAY_FINDB_SCASB_NOITER(str, n, needle, ret) do { \
  __asm volatile ("cld\n\t"); \
  __asm volatile ("movl %%edx, %%edi\n\t" \
                "movl %%esi, %%ecx\n\t" \
                "cmpl $1, %%ecx\n\t" \
                "repne scasb\n\t" \
                "sete %%bl\n\t" \
                "movzbl %%bl,%%ebx\n\t" \
                "subl %%ebx,%%esi\n\t" \
                "subl %%ecx,%%esi\n\t" \
                : "=S"(ret) \
                : "S"(n), "a"(needle), "d"(str) \
                : "%ecx", "%ebx"); \
/*
    __asm volatile ("movl %%edx, %%edi\n\t" \
                  "movl %%esi, %%ecx\n\t" \
                  "repne scasb\n\t" \
                  "sete %%bl\n\t" \
                  "movzbl %%bl,%%ebx\n\t" \
                  "subl %%edx,%%edi\n\t" \
                  "subl %%ebx,%%edi\n\t" \
                  : "=D"(ret) \
                  : "S"(n), "a"(needle), "d"(str) \
                  : "%ecx", "%ebx"); \
*/ \
} while(0)

#define ARRAY_FINDW_NOITER(str, n, needle, ptr) do { \
  for (ii = 0; ii < n && ((uint16_t *)str)[ii] != needle; ii++); \
} while(0)

#define ARRAY_FINDW_SCASW_NOITER(str, n, needle, ret) do { \
  __asm volatile ("cld\n\t"); \
  __asm volatile ("movl %%edx, %%edi\n\t" \
                "movl %%esi, %%ecx\n\t" \
                "cmpl $1, %%ecx\n\t" \
                "repne scasw\n\t" \
                "sete %%bl\n\t" \
                "movzbl %%bl,%%ebx\n\t" \
                "subl %%ebx,%%esi\n\t" \
                "subl %%ecx,%%esi\n\t" \
                : "=S"(ret) \
                : "S"(n), "a"(needle), "d"(str) \
                : "%ecx", "%ebx"); \
/* \
  __asm volatile ("movl %%edx, %%edi\n\t" \
                "movl %%esi, %%ecx\n\t" \
                "repne scasw\n\t" \
                "sete %%bl\n\t" \
                "movzbl %%bl,%%ebx\n\t" \
                "subl %%esi,%%ecx\n\t" \
                "addl %%ebx,%%ecx\n\t" \
                "negl %%ecx\n\t" \
                : "=c"(ret) \
                : "S"(n), "a"(needle), "d"(str) \
                : "%edi", "%ebx"); \
*/ \
} while(0)

#define ARRAY_FINDL_NOITER(str, n, needle, i) do { \
  for (ii = 0; ii < n && ((uint32_t *)str)[ii] != needle; ii++); \
} while(0)

#define ARRAY_FINDL_SCASL_NOITER(str, n, needle, ret) do { \
  __asm volatile ("cld\n\t"); \
    __asm volatile ("movl %%edx, %%edi\n\t" \
                  "movl %%esi, %%ecx\n\t" \
                  "cmpl $1, %%ecx\n\t" \
                  "repne scasl\n\t" \
                  "sete %%bl\n\t" \
                  "movzbl %%bl,%%ebx\n\t" \
                  "subl %%ebx,%%esi\n\t" \
                  "subl %%ecx,%%esi\n\t" \
                  : "=S"(ret) \
                  : "S"(n), "a"(needle), "d"(str) \
                  : "%ecx", "%ebx"); \
/* \
    __asm volatile ("movl %%edx, %%edi\n\t" \
                  "movl %%esi, %%ecx\n\t" \
                  "repne scasl\n\t" \
                  "sete %%bl\n\t" \
                  "movzbl %%bl,%%ebx\n\t" \
                  "subl %%esi,%%ecx\n\t" \
                  "addl %%ebx,%%ecx\n\t" \
                  "negl %%ecx\n\t" \
                  : "=c"(ret) \
                  : "S"(n), "a"(needle), "d"(str) \
                  : "%edi", "%ebx"); \
*/ \
} while(0)

#define MY_STRLEN_NOITER(str, ptr, ret) do { \
  for (ptr = str; (ptr - str < (unsigned long)-1) && *ptr; ptr++); \
  if (ptr - str == (unsigned long)-1) ptr--; /*undef behaviour, need assume statement*/\
  ret = ptr - str; \
} while(0)

#define MY_STRLEN_SCASB_NOITER(str, ret) do { \
  __asm volatile ("cld"); \
  ret = -1; \
  __asm volatile ("movl %%edx,%%edi\n\t" \
                "movl $0,%%eax\n\t" \
                "repne scasb\n\t" \
                "neg %%ecx\n\t" \
                "sub $2,%%ecx\n\t" \
                : "=c"(ret) \
                : "c"(ret), "d"(str) \
                : "%eax","%edi"); \
} while(0)

#define MY_STRCMP(a, b, ret) do { \
  char const *ptr_a, *ptr_b; \
  for (ptr_a = a, ptr_b = b; *ptr_a == *ptr_b && *ptr_a; ptr_a++, ptr_b++); \
  ret = *ptr_a - *ptr_b; \
} while(0)

#define MY_STRCMP_CMPSB(a, b, ret) do { \
  __asm volatile("cld\n\t"); \
  __asm volatile("mov %%ebx, %%esi\n\t" \
               "mov %%edx, %%edi\n\t" \
               "mov $-1,%%ecx\n\t" \
               "repe cmpsb\n\t" \
               "movzbl -1(%%esi),%%eax\n\t" \
               "movzbl -1(%%edi),%%edi\n\t" \
               "subl %%edi, %%eax\n\t" \
               : "=a"(ret) \
               : "b"(a), "d"(b) \
               : "%ecx", "%esi", "%edi"); \
  if (i < 4) printf("ret = %d\n", ret); \
} while(0)

#define COUNT_ONES32_NOITER(a, size, ret) do { \
  unsigned char iret; \
  size_t n, s; \
  ret = 0; \
  for (s = 0; s < size; s++) { \
    iret = 0; \
    for (n = 0; n < 32; n++) { \
      if ((a[s] >> n) & 1) { \
        iret++; \
      } \
    } \
    ret += iret; \
  } \
} while(0)

#define COUNT_ONES_POPCNT32_NOITER(a, size, ret) do { \
  unsigned s; \
  ret = 0; \
  for (s = 0; s < size; s++) { \
    int iret; \
    __asm volatile("popcntl %1, %0" : "=r"(iret) : "m"(a[s])); \
    ret += iret; \
  } \
} while(0)


