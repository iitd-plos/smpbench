#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <assert.h>
#define ASSERT assert
#define TRUE	1
#define FALSE	0


extern int a_global[1000];
extern int *a_global_pointer;

struct time {
  long long num_starts;
  int		running ;
//  int		flags ;
  
  long long	wallClock_start ;
//  long long	processor_start ;
//  long long	clockticks_start ;	/* CLOCK TICKS, not USECS */
//  long long	user_start ;
//  long long	system_start ;
  
  long long	wallClock_elapsed ;
//  long long	processor_elapsed ;
//  long long	clockticks_elapsed ;	/* CLOCK TICKS, not USECS */
//  long long	user_elapsed ;
//  long long	system_elapsed ;
};



void stopwatch_reset(struct time *timer);
int stopwatch_run(struct time *timer);
void stopwatch_stop(struct time *timer);
void stopwatch_print(struct time *timer);

size_t my_strlen(char const *str/*, char a*/);
size_t my_strlen_scasb(char *str/*, char a*/);
size_t my_strlen_scasb2(char *str/*, char a*/);

char *my_strrchr(char *haystack, char needle);
char *my_strrchr_scasb(char *haystack, char needle);

void usage (void);

int
main (int argc, char **argv)
{
  if (argc < 2)
      usage();

  char *s, *s2, *s3, *p, *p2, *p3;
  size_t slen, slen2;
  //char *s = argv[2];
  long s_size = 1234567;
  s = (char *)malloc(s_size * sizeof(char));
  assert(s);
  s2 = (char *)malloc(s_size * sizeof(char));
  assert(s2);
  s3 = (char *)malloc(s_size * sizeof(char));
  assert(s3);
  for (p = s, p2 = s2, p3 = s3; (p - s) < s_size; p++, p2++, p3++) {
    *p = ((p - s) % 26) + 'a';
    assert(*p != 0);
    *p2 = ((p2 - s2) % 26) + 'a';
    assert(*p2 != 0);
    *p3 = ((p3 - s3) % 26) + 'a';
    assert(*p3 != 0);
  }
  s[0] = '/'; s2[0] = '/'; s3[0] = '/'; //have a different zero'th elem, so that reverse search traverses the full array
  s[1] = ';'; s2[1] = ';'; s3[1] = ';';
  slen = s_size;//strlen(s);
  //s = argv[2];
  //slen = strlen(s);
  s[slen - 1] = '\0';
  s[slen - 2] = '\0';
  s[slen - 3] = '\0';
  s[slen - 4] = '\0';
  s[slen - 5] = '\0';
  s[slen - 6] = '\0';
  s[slen - 7] = '\0';
  s[slen - 8] = '\0';
  s[slen - 9] = '\0';
  s[slen - 10] = '\0';
  s[slen - 11] = '\0';
  s[slen - 12] = '\0';
  s[slen - 13] = '\0';
  s[slen - 14] = '\0';
  s[slen - 15] = '\0';
  s[slen - 16] = '\0';

  slen2 = s_size;
  s2[slen2 - 1] = '\0';
  s2[slen2 - 2] = '\0';
  s2[slen2 - 3] = '\0';
  s2[slen2 - 4] = '\0';
  s2[slen2 - 5] = '\0';
  s2[slen2 - 6] = '\0';
  s2[slen2 - 7] = '\0';
  s2[slen2 - 8] = '\0';
  s2[slen2 - 9] = '\0';
  s2[slen2 - 10] = '\0';
  s2[slen2 - 11] = '\0';
  s2[slen2 - 12] = '\0';
  s2[slen2 - 13] = '\0';
  s2[slen2 - 14] = '\0';
  s2[slen2 - 15] = '\0';
  s2[slen2 - 16] = '\0';

  //some of these functions are implemented as optimized routines in libraries; but they have fixed implementations (e.g., only for char but not for uint16_t)
  if (!strcmp(argv[1], "array_cmpb")) { //show results for uint16_t. Discuss that while wmemcmp exists, very few people use it due to portability issues; different compilers have different representations of wide-character (Windows: 16-bit, Linux 32-bit) [source: http://stackoverflow.com/questions/11287213/what-is-a-wide-character-string-in-c-language]
    struct time array_cmpb_timer;
    struct time array_cmpb_cmpsb_timer;
    struct time array_cmpb_cmpsw_timer;
    struct time array_cmpb_cmpsl_timer;

    stopwatch_reset(&array_cmpb_timer);
    stopwatch_reset(&array_cmpb_cmpsb_timer);
    stopwatch_reset(&array_cmpb_cmpsw_timer);
    stopwatch_reset(&array_cmpb_cmpsl_timer);

    stopwatch_run(&array_cmpb_timer);
    int cmp1b = array_cmpb(s, s2, slen);
    stopwatch_stop(&array_cmpb_timer);

    stopwatch_run(&array_cmpb_cmpsb_timer);
    int cmp2b = array_cmpb_cmpsb(s, s2, slen);
    stopwatch_stop(&array_cmpb_cmpsb_timer);

    stopwatch_run(&array_cmpb_cmpsw_timer);
    int cmp3b = array_cmpb_cmpsw(s, s2, slen);
    stopwatch_stop(&array_cmpb_cmpsw_timer);

    stopwatch_run(&array_cmpb_cmpsl_timer);
    int cmp4b = array_cmpb_cmpsl(s, s2, slen);
    stopwatch_stop(&array_cmpb_cmpsl_timer);

    printf("cmp1b = %d, cmp2b = %d, cmp3b = %d, cmp4b = %d\n", cmp1b, cmp2b, cmp3b, cmp4b);
    stopwatch_print(&array_cmpb_timer);
    stopwatch_print(&array_cmpb_cmpsb_timer);
    stopwatch_print(&array_cmpb_cmpsw_timer);
    stopwatch_print(&array_cmpb_cmpsl_timer);
  } else if (!strcmp(argv[1], "array_cmpw")) {
    struct time array_cmpw_timer;
    struct time array_cmpw_cmpsw_timer;
    struct time array_cmpw_cmpsl_timer;

    stopwatch_reset(&array_cmpw_timer);
    stopwatch_reset(&array_cmpw_cmpsw_timer);
    stopwatch_reset(&array_cmpw_cmpsl_timer);

    stopwatch_run(&array_cmpw_timer);
    int cmp1w = array_cmpw(s, s2, slen/2);
    stopwatch_stop(&array_cmpw_timer);

    stopwatch_run(&array_cmpw_cmpsw_timer);
    int cmp2w = array_cmpw_cmpsw(s, s2, slen/2);
    stopwatch_stop(&array_cmpw_cmpsw_timer);

    stopwatch_run(&array_cmpw_cmpsl_timer);
    int cmp3w = array_cmpw_cmpsl(s, s2, slen/2);
    stopwatch_stop(&array_cmpw_cmpsl_timer);

    printf("cmp1w = %d, cmp2w = %d, cmp3w = %d\n", cmp1w, cmp2w, cmp3w);
    stopwatch_print(&array_cmpw_timer);
    stopwatch_print(&array_cmpw_cmpsw_timer);
    stopwatch_print(&array_cmpw_cmpsl_timer);
  } else if (!strcmp(argv[1], "array_cmpl")) {
    struct time array_cmpl_timer;
    struct time array_cmpl_cmpsl_timer;

    stopwatch_reset(&array_cmpl_timer);
    stopwatch_reset(&array_cmpl_cmpsl_timer);

    stopwatch_run(&array_cmpl_timer);
    int cmp1d = array_cmpl(s, s2, slen/4);
    stopwatch_stop(&array_cmpl_timer);

    stopwatch_run(&array_cmpl_cmpsl_timer);
    int cmp2d = array_cmpl_cmpsl(s, s2, slen/4);
    stopwatch_stop(&array_cmpl_cmpsl_timer);

    printf("cmp1d = %d, cmp2d = %d\n", cmp1d, cmp2d);
    stopwatch_print(&array_cmpl_timer);
    stopwatch_print(&array_cmpl_cmpsl_timer);
  } else if (!strcmp(argv[1], "array_setb")) {
    struct time array_setb_timer;
    struct time array_setb_stosb_timer;
    struct time array_setb_stosw_timer;
    struct time array_setb_stosl_timer;

    stopwatch_reset(&array_setb_timer);
    stopwatch_reset(&array_setb_stosb_timer);
    stopwatch_reset(&array_setb_stosw_timer);
    stopwatch_reset(&array_setb_stosl_timer);

    stopwatch_run(&array_setb_timer);
    int set1b = array_setb(s, s2, slen);
    stopwatch_stop(&array_setb_timer);

    stopwatch_run(&array_setb_stosb_timer);
    int set2b = array_setb_stosb(s, s2, slen);
    stopwatch_stop(&array_setb_stosb_timer);

    stopwatch_run(&array_setb_stosw_timer);
    int set3b = array_setb_stosw(s, s2, slen);
    stopwatch_stop(&array_setb_stosw_timer);

    stopwatch_run(&array_setb_stosl_timer);
    int set4b = array_setb_stosl(s, s2, slen);
    stopwatch_stop(&array_setb_stosl_timer);

    printf("set1b = %d, set2b = %d, set3b = %d, set4b = %d\n", set1b, set2b, set3b, set4b);
    stopwatch_print(&array_setb_timer);
    stopwatch_print(&array_setb_stosb_timer);
    stopwatch_print(&array_setb_stosw_timer);
    stopwatch_print(&array_setb_stosl_timer);
  } else if (!strcmp(argv[1], "array_setw")) {
    struct time array_setw_timer;
    struct time array_setw_stosw_timer;
    struct time array_setw_stosl_timer;

    stopwatch_reset(&array_setw_timer);
    stopwatch_reset(&array_setw_stosw_timer);
    stopwatch_reset(&array_setw_stosl_timer);

    stopwatch_run(&array_setw_timer);
    int set1w = array_setw(s, s2, slen/2);
    stopwatch_stop(&array_setw_timer);

    stopwatch_run(&array_setw_stosw_timer);
    int set2w = array_setw_stosw(s, s2, slen/2);
    stopwatch_stop(&array_setw_stosw_timer);

    stopwatch_run(&array_setw_stosl_timer);
    int set3w = array_setw_stosl(s, s2, slen/2);
    stopwatch_stop(&array_setw_stosl_timer);

    printf("set1w = %d, set2w = %d, set3w = %d\n", set1w, set2w, set3w);
    stopwatch_print(&array_setw_timer);
    stopwatch_print(&array_setw_stosw_timer);
    stopwatch_print(&array_setw_stosl_timer);
  } else if (!strcmp(argv[1], "array_setl")) {
    struct time array_setl_timer;
    struct time array_setl_stosl_timer;

    stopwatch_reset(&array_setl_timer);
    stopwatch_reset(&array_setl_stosl_timer);

    stopwatch_run(&array_setl_timer);
    int set1l = array_setl(s, s2, slen/4);
    stopwatch_stop(&array_setl_timer);

    stopwatch_run(&array_setl_stosl_timer);
    int set2l = array_setl_stosl(s, s2, slen/4);
    stopwatch_stop(&array_setl_stosl_timer);

    printf("set1l = %d, set2l = %d\n", set1l, set2l);
    stopwatch_print(&array_setl_timer);
    stopwatch_print(&array_setl_stosl_timer);
  } else if (!strcmp(argv[1], "array_findb")) {
    struct time array_findb_timer;
    struct time array_findb_scasb_timer;
    struct time array_findbn_timer;
    struct time array_findbn_scasb_timer;

    stopwatch_reset(&array_findb_timer);
    stopwatch_reset(&array_findb_scasb_timer);
    stopwatch_reset(&array_findbn_timer);
    stopwatch_reset(&array_findbn_scasb_timer);

    stopwatch_run(&array_findb_timer);
    int find1b = array_findb(s, slen, s[slen - 1]);
    stopwatch_stop(&array_findb_timer);

    stopwatch_run(&array_findb_scasb_timer);
    int find2b = array_findb_scasb(s, slen, s[slen - 1]);
    stopwatch_stop(&array_findb_scasb_timer);

    stopwatch_run(&array_findbn_timer);
    int find1bn = array_findb(s, slen, ')');
    stopwatch_stop(&array_findbn_timer);

    stopwatch_run(&array_findbn_scasb_timer);
    int find2bn = array_findb_scasb(s, slen, ')');
    stopwatch_stop(&array_findbn_scasb_timer);

    printf("find1b = %d, find2b = %d, find1bn = %d, find2bn = %d\n", find1b, find2b, find1bn, find2bn);
    stopwatch_print(&array_findb_timer);
    stopwatch_print(&array_findb_scasb_timer);
    stopwatch_print(&array_findbn_timer);
    stopwatch_print(&array_findbn_scasb_timer);
  } else if (!strcmp(argv[1], "array_findw")) {
    struct time array_findw_timer;
    struct time array_findw_scasw_timer;
    struct time array_findwn_timer;
    struct time array_findwn_scasw_timer;

    stopwatch_reset(&array_findw_timer);
    stopwatch_reset(&array_findw_scasw_timer);
    stopwatch_reset(&array_findwn_timer);
    stopwatch_reset(&array_findwn_scasw_timer);

    stopwatch_run(&array_findw_timer);
    int find1w = array_findw(s, slen/2, *((uint16_t *)&s[slen - 2]));
    stopwatch_stop(&array_findw_timer);

    stopwatch_run(&array_findw_scasw_timer);
    int find2w = array_findw_scasw(s, slen/2, *((uint16_t *)&s[slen - 2]));
    stopwatch_stop(&array_findw_scasw_timer);

    stopwatch_run(&array_findwn_timer);
    int find1wn = array_findw(s, slen/2, ')');
    stopwatch_stop(&array_findwn_timer);

    stopwatch_run(&array_findwn_scasw_timer);
    int find2wn = array_findw_scasw(s, slen/2, ')');
    stopwatch_stop(&array_findwn_scasw_timer);

    printf("find1w = %d, find2w = %d, find1wn = %d, find2wn = %d\n", find1w, find2w, find1wn, find2wn);
    stopwatch_print(&array_findw_timer);
    stopwatch_print(&array_findw_scasw_timer);
    stopwatch_print(&array_findwn_timer);
    stopwatch_print(&array_findwn_scasw_timer);
  } else if (!strcmp(argv[1], "array_findl")) {
    struct time array_findl_timer;
    struct time array_findl_scasl_timer;
    struct time array_findln_timer;
    struct time array_findln_scasl_timer;

    stopwatch_reset(&array_findl_timer);
    stopwatch_reset(&array_findl_scasl_timer);
    stopwatch_reset(&array_findln_timer);
    stopwatch_reset(&array_findln_scasl_timer);

    stopwatch_run(&array_findl_timer);
    int find1l = array_findl(s, slen/4, *((uint32_t *)&s[slen - 4]));
    stopwatch_stop(&array_findl_timer);

    stopwatch_run(&array_findl_scasl_timer);
    int find2l = array_findl_scasl(s, slen/4, *((uint32_t *)&s[slen - 4]));
    stopwatch_stop(&array_findl_scasl_timer);

    stopwatch_run(&array_findln_timer);
    int find1ln = array_findl(s, slen/4, '(');
    stopwatch_stop(&array_findln_timer);

    stopwatch_run(&array_findln_scasl_timer);
    int find2ln = array_findl_scasl(s, slen/4, '(');
    stopwatch_stop(&array_findln_scasl_timer);

    printf("find1l = %d, find2l = %d, find1ln = %d, find2ln = %d\n", find1l, find2l, find1ln, find2ln);
    stopwatch_print(&array_findl_timer);
    stopwatch_print(&array_findl_scasl_timer);
    stopwatch_print(&array_findln_timer);
    stopwatch_print(&array_findln_scasl_timer);

  } else if (!strcmp(argv[1], "array_rfindb")) {
    struct time array_rfindb_timer;
    struct time array_rfindb_scasb_timer;
    struct time array_rfindbn_timer;
    struct time array_rfindbn_scasb_timer;

    stopwatch_reset(&array_rfindb_timer);
    stopwatch_reset(&array_rfindb_scasb_timer);
    stopwatch_reset(&array_rfindbn_timer);
    stopwatch_reset(&array_rfindbn_scasb_timer);

    stopwatch_run(&array_rfindb_timer);
    int rfind1b = array_rfindb(s, slen, s[0]);
    stopwatch_stop(&array_rfindb_timer);

    stopwatch_run(&array_rfindb_scasb_timer);
    int rfind2b = array_rfindb_scasb(s, slen, s[0]);
    stopwatch_stop(&array_rfindb_scasb_timer);

    stopwatch_run(&array_rfindbn_timer);
    int rfind1bn = array_rfindb(s, slen, ')');
    stopwatch_stop(&array_rfindbn_timer);

    stopwatch_run(&array_rfindbn_scasb_timer);
    int rfind2bn = array_rfindb_scasb(s, slen, ')');
    stopwatch_stop(&array_rfindbn_scasb_timer);

    printf("rfind1b = %d, rfind2b = %d, rfind1bn = %d, rfind2bn = %d\n", rfind1b, rfind2b, rfind1bn, rfind2bn);
    stopwatch_print(&array_rfindb_timer);
    stopwatch_print(&array_rfindb_scasb_timer);
    stopwatch_print(&array_rfindbn_timer);
    stopwatch_print(&array_rfindbn_scasb_timer);
  } else if (!strcmp(argv[1], "array_rfindw")) {
    struct time array_rfindw_timer;
    struct time array_rfindw_scasw_timer;
    struct time array_rfindwn_timer;
    struct time array_rfindwn_scasw_timer;

    stopwatch_reset(&array_rfindw_timer);
    stopwatch_reset(&array_rfindw_scasw_timer);
    stopwatch_reset(&array_rfindwn_timer);
    stopwatch_reset(&array_rfindwn_scasw_timer);

    stopwatch_run(&array_rfindw_timer);
    int rfind1w = array_rfindw(s, slen/2, *((uint16_t *)&s[0]));
    stopwatch_stop(&array_rfindw_timer);

    stopwatch_run(&array_rfindw_scasw_timer);
    int rfind2w = array_rfindw_scasw(s, slen/2, *((uint16_t *)&s[0]));
    stopwatch_stop(&array_rfindw_scasw_timer);

    stopwatch_run(&array_rfindwn_timer);
    int rfind1wn = array_rfindw(s, slen/2, '(');
    stopwatch_stop(&array_rfindwn_timer);

    stopwatch_run(&array_rfindwn_scasw_timer);
    int rfind2wn = array_rfindw_scasw(s, slen/2, '(');
    stopwatch_stop(&array_rfindwn_scasw_timer);

    printf("rfind1w = %d, rfind2w = %d, rfind1wn = %d, rfind2wn = %d\n", rfind1w, rfind2w, rfind1wn, rfind2wn);
    stopwatch_print(&array_rfindw_timer);
    stopwatch_print(&array_rfindw_scasw_timer);
    stopwatch_print(&array_rfindwn_timer);
    stopwatch_print(&array_rfindwn_scasw_timer);
  } else if (!strcmp(argv[1], "array_rfindl")) {
    struct time array_rfindl_timer;
    struct time array_rfindl_scasl_timer;
    struct time array_rfindln_timer;
    struct time array_rfindln_scasl_timer;

    stopwatch_reset(&array_rfindl_timer);
    stopwatch_reset(&array_rfindl_scasl_timer);
    stopwatch_reset(&array_rfindln_timer);
    stopwatch_reset(&array_rfindln_scasl_timer);

    stopwatch_run(&array_rfindl_timer);
    int rfind1l = array_rfindl(s, slen/4, *((uint32_t *)&s[0]));
    stopwatch_stop(&array_rfindl_timer);

    stopwatch_run(&array_rfindl_scasl_timer);
    int rfind2l = array_rfindl_scasl(s, slen/4, *((uint32_t *)&s[0]));
    stopwatch_stop(&array_rfindl_scasl_timer);

    stopwatch_run(&array_rfindln_timer);
    int rfind1ln = array_rfindl(s, slen/4, ')');
    stopwatch_stop(&array_rfindln_timer);

    stopwatch_run(&array_rfindln_scasl_timer);
    int rfind2ln = array_rfindl_scasl(s, slen/4, ')');
    stopwatch_stop(&array_rfindln_scasl_timer);

    printf("rfind1l = %d, rfind2l = %d, rfind1ln = %d, rfind2ln = %d\n", rfind1l, rfind2l, rfind1ln, rfind2ln);
    stopwatch_print(&array_rfindl_timer);
    stopwatch_print(&array_rfindl_scasl_timer);
    stopwatch_print(&array_rfindln_timer);
    stopwatch_print(&array_rfindln_scasl_timer);
  } else if (!strcmp(argv[1], "strlen")) { //call it array_find and show results for uint16_t
    struct time my_strlen_timer;
    struct time my_strlen_scasb_timer;
    //struct time my_strlen_scasb2_timer;

    stopwatch_reset(&my_strlen_timer);
    stopwatch_reset(&my_strlen_scasb_timer);
    //stopwatch_reset(&my_strlen_scasb2_timer);
    size_t len1 = 0, len2 = 0, len3 = 0;
    
    stopwatch_run(&my_strlen_timer);
    len1 = my_strlen(s);
    stopwatch_stop(&my_strlen_timer);

    stopwatch_run(&my_strlen_scasb_timer);
    len2 = my_strlen_scasb(s);
    stopwatch_stop(&my_strlen_scasb_timer);

    //stopwatch_run(&my_strlen_scasb2_timer);
    //len3 = my_strlen_scasb2(s);
    //stopwatch_stop(&my_strlen_scasb2_timer);


    printf("len1 = %zd, len2 = %zd\n", len1, len2);
    stopwatch_print(&my_strlen_timer);
    stopwatch_print(&my_strlen_scasb_timer);
    //stopwatch_print(&my_strlen_scasb2_timer);

/*
    struct time my_strlenw_timer;
    struct time my_strlen_scasw_timer;
    struct time my_strlen_scasw2_timer;

    stopwatch_reset(&my_strlenw_timer);
    stopwatch_reset(&my_strlen_scasw_timer);
    stopwatch_reset(&my_strlen_scasw2_timer);
    
    stopwatch_run(&my_strlenw_timer);
    size_t len1w = my_strlenw((uint16_t *)s);
    stopwatch_stop(&my_strlenw_timer);

    stopwatch_run(&my_strlen_scasw_timer);
    size_t len2w = my_strlen_scasw((uint16_t *)s);
    stopwatch_stop(&my_strlen_scasw_timer);

    stopwatch_run(&my_strlen_scasw2_timer);
    size_t len3w = my_strlen_scasw2((uint16_t *)s);
    stopwatch_stop(&my_strlen_scasw2_timer);

    printf("len1w = %zd, len2w = %zd, len3w = %zd\n", len1w, len2w, len3w);
    stopwatch_print(&my_strlenw_timer);
    stopwatch_print(&my_strlen_scasw_timer);
    stopwatch_print(&my_strlen_scasw2_timer);


    struct time my_strlend_timer;
    struct time my_strlen_scasd_timer;
    struct time my_strlen_scasd2_timer;

    stopwatch_reset(&my_strlend_timer);
    stopwatch_reset(&my_strlen_scasd_timer);
    stopwatch_reset(&my_strlen_scasd2_timer);
    
    stopwatch_run(&my_strlend_timer);
    size_t len1d = my_strlend((uint32_t *)s);
    stopwatch_stop(&my_strlend_timer);
    size_t len2d = 0, len3d = 0;
    stopwatch_run(&my_strlen_scasd_timer);
    len2d = my_strlen_scasd((uint32_t *)s);
    stopwatch_stop(&my_strlen_scasd_timer);

    stopwatch_run(&my_strlen_scasd2_timer);
    len3d = my_strlen_scasd2((uint32_t *)s);
    stopwatch_stop(&my_strlen_scasd2_timer);

    printf("len1d = %zd, len2d = %zd, len3d = %zd\n", len1d, len2d, len3d);
    stopwatch_print(&my_strlend_timer);
    stopwatch_print(&my_strlen_scasd_timer);
    stopwatch_print(&my_strlen_scasd2_timer);*/

    exit(0);
  } else if (!strcmp(argv[1], "strrchr")) {
    struct time my_strrchr_timer;
    struct time my_strrchr_scasb_timer;
    struct time my_strrchr1_timer;
    struct time my_strrchr1_scasb_timer;
    struct time my_strrchrn_timer;
    struct time my_strrchrn_scasb_timer;

    stopwatch_reset(&my_strrchr_timer);
    stopwatch_reset(&my_strrchr_scasb_timer);
    stopwatch_reset(&my_strrchr1_timer);
    stopwatch_reset(&my_strrchr1_scasb_timer);
    stopwatch_reset(&my_strrchrn_timer);
    stopwatch_reset(&my_strrchrn_scasb_timer);
    
    stopwatch_run(&my_strrchr_timer);
    char *strrchr_out = my_strrchr(s, s[0]);
    stopwatch_stop(&my_strrchr_timer);

    stopwatch_run(&my_strrchr_scasb_timer);
    char *strrchr_scasb_out = my_strrchr_scasb(s, s[0]);
    stopwatch_stop(&my_strrchr_scasb_timer);

    stopwatch_run(&my_strrchr1_timer);
    char *strrchr1_out = my_strrchr(s, s[1]);
    stopwatch_stop(&my_strrchr1_timer);

    stopwatch_run(&my_strrchr1_scasb_timer);
    char *strrchr1_scasb_out = my_strrchr_scasb(s, s[1]);
    stopwatch_stop(&my_strrchr1_scasb_timer);

    stopwatch_run(&my_strrchrn_timer);
    char *strrchrn_out = my_strrchr(s, '(');
    stopwatch_stop(&my_strrchrn_timer);

    stopwatch_run(&my_strrchrn_scasb_timer);
    char *strrchrn_scasb_out = my_strrchr_scasb(s, '(');
    stopwatch_stop(&my_strrchrn_scasb_timer);

    printf("s = %p, strrchr_out = %p, strrchr_scasb_out = %p, strrchr1_out = %p, strrchr1_scasb_out = %p, strrchrn_out = %p, strrchrn_scasb_out = %p\n", s, strrchr_out, strrchr_scasb_out, strrchr1_out, strrchr1_scasb_out, strrchrn_out, strrchrn_scasb_out);
    stopwatch_print(&my_strrchr_timer);
    stopwatch_print(&my_strrchr_scasb_timer);
    stopwatch_print(&my_strrchr1_timer);
    stopwatch_print(&my_strrchr1_scasb_timer);
    stopwatch_print(&my_strrchrn_timer);
    stopwatch_print(&my_strrchrn_scasb_timer);

    exit(0);
  } else if (!strcmp(argv[1], "strcmp")) {
    struct time my_strcmp_timer;
    struct time my_strcmp_cmpsb_timer;
    struct time my_strcmpn_timer;
    struct time my_strcmpn_cmpsb_timer;

    stopwatch_reset(&my_strcmp_timer);
    stopwatch_reset(&my_strcmp_cmpsb_timer);
    stopwatch_reset(&my_strcmpn_timer);
    stopwatch_reset(&my_strcmpn_cmpsb_timer);
    
    stopwatch_run(&my_strcmp_timer);
    int strcmp_out = my_strcmp(s, s2);
    stopwatch_stop(&my_strcmp_timer);

    stopwatch_run(&my_strcmp_cmpsb_timer);
    int strcmp_cmpsb_out = my_strcmp_cmpsb(s, s2);
    stopwatch_stop(&my_strcmp_cmpsb_timer);

    stopwatch_run(&my_strcmpn_timer);
    int strcmpn_out = my_strcmp(s, s3);
    stopwatch_stop(&my_strcmpn_timer);

    stopwatch_run(&my_strcmpn_cmpsb_timer);
    int strcmpn_cmpsb_out = my_strcmp_cmpsb(s, s3);
    stopwatch_stop(&my_strcmpn_cmpsb_timer);

    printf("strcmp_out = %d, strcmp_cmpsb_out = %d, strcmpn_out = %d, strcmpn_cmpsb_out = %d\n", strcmp_out, strcmp_cmpsb_out, strcmpn_out, strcmpn_cmpsb_out);
    stopwatch_print(&my_strcmp_timer);
    stopwatch_print(&my_strcmp_cmpsb_timer);
    stopwatch_print(&my_strcmpn_timer);
    stopwatch_print(&my_strcmpn_cmpsb_timer);
    exit(0);
  } else if (!strcmp(argv[1], "count_ones")) {
    struct time count_ones_timer;
    struct time count_ones_popcnt_timer;

    stopwatch_reset(&count_ones_timer);
    stopwatch_reset(&count_ones_popcnt_timer);
    
    stopwatch_run(&count_ones_timer);
    int count_ones_out = count_ones32(s, slen/4);
    stopwatch_stop(&count_ones_timer);

    stopwatch_run(&count_ones_popcnt_timer);
    int count_ones_popcnt_out = count_ones_popcnt32(s, slen/4);
    stopwatch_stop(&count_ones_popcnt_timer);

    printf("count_ones_out = %d, count_ones_popcnt_out = %d\n", count_ones_out, count_ones_popcnt_out);
    stopwatch_print(&count_ones_timer);
    stopwatch_print(&count_ones_popcnt_timer);
    exit(0);
  } else if (!strcmp(argv[1], "sum8")) {
    int ret;
    ret = sum8(argc - 1, argv + 1);
    ret += cp_test(argc - 1);
    printf("Summed an array of 8-bit elements of size %d.\n", ret);
    return 0;
  }
  return 0;
}
