#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MAGIC_NUMBER 0x54321	/* To identify code fragments in assembly. */
#define MAX(a, b) ((a) < (b) ? (b) : (a))

#define MAX_LEN 0x800000

static uint8_t a[MAX_LEN];
static uint8_t b[MAX_LEN];
static uint8_t c[MAX_LEN];

void
usage (void)
{
  printf ("Usage: combox <prog-name> <arguments>\n");
  printf ("\tprograms: emptyloop printloop fibo_rec fibo_rec2 fibo_iter bubsort hanoi sum8 image_diff min comparison xor sprite_copy memset memcpy memmove bcmp bcopy bzero memccpy memchr memcmp memfrob memmem\n");
  exit (1);
}

int
_sum8(uint8_t *a, int len)
{
  int i;
  int sum = 0;
  for (i = 0; i < len; i++) {
    sum += a[i];
  }
  return sum;
}

int
sum8(int argc, char **argv)
{
  if (argc < 2) {
    printf("Usage: sum8 <array-size>\n");
    exit(1);
  }

  int len = atoi(argv[1]);
  uint8_t *a = (uint8_t *)malloc(len * sizeof(uint8_t));
  if (!a) {
    printf ("%s(): array allocation of size %d failed.\n", __func__, len);
    exit(1);
  }

  int i, j;

  srand48 (0x12345678);

  for (i = 0; i < len; i++) {
    a[i] = rand() & 0xff;
  }

  if (len <= 10) {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++) {
      printf ("a[%d] = %d\n", i, a[i]);
    }
  }

  int sum = _sum8(a, len);

  printf ("sum = %d\n", sum);
  return len;
}

int
_image_diff(int len)
{
  int i;
  int sum = 0;
  for (i = 0; i < len; i++) {
    if (a[i] < b[i]) {
      sum += b[i] - a[i];
    } else {
      sum += a[i] - b[i];
    }
  }
  return sum;
}

int
_memcmp(int len)
{
  int i;
  for (i = 0; i < len; i++) {
    if (a[i] < b[i]) {
      return -1;
    } else if (a[i] > b[i]) {
      return 1;
    }
  }
  return 0;
}

void
_memset(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Usage: memset <array-size> <character>\n");
    exit(1);
  }
  int len = atoi(argv[1]);
  char c = argv[2][0];
  int i;
  for (i = 0; i < len; i++) {
    a[i] = c;
  }
}

void
_memcpy(int argc, char *argv[])
{
  if (argc < 1) {
    printf("Usage: memset <array-size>\n");
    exit(1);
  }
  int len = atoi(argv[1]);
  int i;
  for (i = 0; i < len; i++) {
    b[i] = a[i];
  }
}

void
_memmove(int argc, char *argv[])
{
  if (argc < 1) {
    printf("Usage: memset <array-size>\n");
    exit(1);
  }
  int len = atoi(argv[1]);
  int i;
  for (i = len - 1; i >= 0; i--) {
    b[i] = a[i];
  }
}

void
_bzero(int argc, char *argv[])
{
  if (argc < 1) {
    printf("Usage: memset <array-size>\n");
    exit(1);
  }
  int len = atoi(argv[1]);
  int i;
  for (i = 0; i < len; i++) {
    a[i] = 0;
  }
}

void
_comparison(int len)
{
  int i;
  for (i = 0; i < len; i++) {
    if ((int8_t)a[i] <= (int8_t)b[i]) {
      c[i] = 0;
    } else {
      c[i] = 0xff;
    }
  }
}

void
_min(int len)
{
  int i;
  for (i = 0; i < len; i++) {
    if ((int8_t)a[i] < (int8_t)b[i]) {
      c[i] = a[i];
    } else {
      c[i] = b[i];
    }
  }
}

void
_xor(int len)
{
  int i;
  for (i = 0; i < len; i++) {
    c[i] = a[i] ^ b[i];
  }
}

void
_sprite_copy(int len)
{
  int i;
  for (i = 0; i < len; i++) {
    c[i] = (a[i] == 0) ? b[i] : a[i];
  }
}

int
three_arrays(int argc, char **argv)
{
  if (argc < 2) {
    printf ("Usage: image_diff <array-size>\n");
    exit(1);
  }

  int len = atoi(argv[1]);
  assert(len <= MAX_LEN);
  /**a = (uint8_t *)malloc(len * sizeof(uint8_t));
  *b = (uint8_t *)malloc(len * sizeof(uint8_t));
  *c = (uint8_t *)malloc(len * sizeof(uint8_t));
  if (!*a || !*b || !*c) {
    printf ("%s(): array allocation of size %d failed.\n", __func__, len);
    exit (1);
  }
  */
  int i, j;

  srand48 (0x12345678);
  for (i = 0; i < len; i++) {
    a[i] = rand() & 0xff;
  }
  if (len > 0) {
    a[len - 1] = 0;
  }
  for (i = 0; i < len; i++) {
    b[i] = rand() & 0xff;
  }
  if (len <= 10) {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++) {
      printf ("a[%d] = 0x%hhx\n", i, a[i]);
      printf ("b[%d] = 0x%hhx\n", i, b[i]);
    }
  }

  return len;
}


int
two_arrays(int argc, char **argv)
{
  if (argc < 2) {
    printf ("Usage: image_diff <array-size>\n");
    exit(1);
  }

  int len = atoi(argv[1]);
  assert(len <= MAX_LEN);
  /**a = (uint8_t *)malloc(len * sizeof(uint8_t));
  *b = (uint8_t *)malloc(len * sizeof(uint8_t));
  if (!*a || !*b) {
    printf ("%s(): array allocation of size %d failed.\n", __func__, len);
    exit (1);
  }*/

  int i, j;

  srand48 (0x12345678);
  for (i = 0; i < len; i++) {
    a[i] = rand() & 0xff;
  }
  for (i = 0; i < len; i++) {
    b[i] = rand() & 0xff;
  }
  if (len <= 10) {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++) {
      printf ("a[%d] = 0x%hhx\n", i, a[i]);
      printf ("b[%d] = 0x%hhx\n", i, b[i]);
    }
  }

  return len;
}

long long
bubsort(int argc, char **argv)
{
  if (argc < 2) {
    printf ("Usage: bubsort <array-size>\n");
    exit(1);
  }

  long long len = atoi(argv[1]);
  long long *a = (long long *)malloc(len*sizeof(long long));
  if (!a) {
    printf ("%s(): array allocation of size %lld failed.\n", __func__, len);
    exit (1);
  }

  int i, j;

  srand48 (0x12345678);

  for (i = 0; i < len; i++) {
    a[i] = (((long long)lrand48()) << 32) | ((long long)lrand48()) ;
  }

  if (len <= 10) {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++)
      printf ("a[%d] = %lld\n", i, a[i]);
  }

  for (i = 0; i < len; i++) {
    for (j = 0; j < len - i - 1; j++) {
      if (a[j] > a[j+1]) {
        long long tmp = a[j+1];
        a[j+1] = a[j];
        a[j] = tmp;
      }
    }
  }

  if (len <= 10) {
    printf ("Printing Sorted array:\n");
    for (i = 0; i < len; i++)
      printf ("a[%d] = %lld\n", i, a[i]);
  }


  return len;
}


#define MERGE(l,r,u) do { \
  int ii,jj,kk; \
  ii=l; jj=r; kk=l; \
  while (ii<r && jj<u) { \
    if (a[ii-1]<=a[jj-1]) {b[kk-1]=a[ii-1]; ii++;}  \
    else {b[kk-1]=a[jj-1]; jj++;} \
    kk++; \
  } \
  while (ii<r) {  \
    b[kk-1]=a[ii-1]; ii++; kk++; \
  } \
  while (jj<u) {  \
    b[kk-1]=a[jj-1]; jj++; kk++; \
  } \
  for (kk=l; kk<u; kk++) {  \
    a[kk-1]=b[kk-1];  \
  } \
} while (0)

long long
mergesort (int argc, char **argv)
{
  if (argc < 2)
  {
    printf ("Usage: mergesort <array-size>\n");
    exit(1);
  }

  int len = atoi(argv[1]);
  long long *a = (long long *) malloc (len*sizeof(long long));
  long long *b = (long long *) malloc (len*sizeof(long long));
  if (!a || !b) {
    printf ("%s(): array allocation of size %d failed.\n", __func__, len);
    exit (1);
  }

  int i;

  srand48 (0x12345678);

  for (i = 0; i < len; i++) {
    a[i] = (((long long)lrand48()) << 32) | ((long long)lrand48()) ;
  }

  if (len <= 10) {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++)
      printf ("a[%d] = %lld\n", i, a[i]);
  }

  int k,u;
  k=1;
  while (k<len) {
    i=1;
    while (i+k<=len) {
      u=i+k*2;
      if (u>len) u=len+1;
      int t = i + k;
      MERGE(i,t,u);
      i=i+k*2;
    }
    k=k*2;
  }

  if (len <= 10) {
    printf ("Printing Sorted array:\n");
    for (i = 0; i < len; i++)
      printf ("a[%d] = %lld\n", i, b[i]);
  }


  return len;
}

//#include <conio.h>

//#define MAXELT          100
#define INFINITY        0x7fffffffffffffffLL //numbers in list should not exceed
// this. change the value to suit your
// needs
#define SMALLSIZE       10            // not less than 3
#define STACKSIZE       100           // should be ceiling(lg(MAXSIZE)+1)

#define swap(x, y)  do { \
  long long temp; \
  temp=*x; \
  *x=*y; \
  *y=temp; \
} while (0)

#define split(first, last, splitpoint) do { \
  int i,j,k,s,g; \
 \
  /* here, atleast three elements are needed */ \
  if (list[first]<list[(first+last)/2]) {  \
    s=first; \
    g=(first+last)/2; \
  } \
  else { \
    g=first; \
    s=(first+last)/2; \
  } \
  if (list[last]<=list[s])  \
    k=s; \
  else if (list[last]<=list[g]) \
    k=last; \
  else \
    k=g; \
  swap (&list[k],&list[first]); /* swap the split-point element with first */ \
  long long x; \
  x=list[first]; \
  i=first+1;     /* initialize */ \
  j=last+1; \
  while (i<j) { \
    do {                                 /* find j  */ \
      j--; \
    } while (list[j]>x); \
    do { \
      i++;                             /* find i */ \
    } while (list[i]<x); \
    swap(&list[i],&list[j]);      /* swap */ \
  } \
  swap(&list[i],&list[j]);          /* undo the extra swap */ \
  swap(&list[first],&list[j]);      /* bring the split-point  */ \
  /* element to the first */ \
  *splitpoint=j; \
} while (0)

#define push(aa,bb) do { \
  top++; \
  stack[top].a=aa; \
  stack[top].b=bb; \
} while (0)

#define pop(aa, bb) do { \
  *aa=stack[top].a; \
  *bb=stack[top].b; \
  top--; \
} while (0)

#define insertion_sort(first, last) do { \
  int i,c; \
  long long j; \
 \
  for (i=first;i<=last;i++) { \
    j=list[i]; \
    c=i; \
    while ((list[c-1]>j)&&(c>first)) { \
      list[c]=list[c-1]; \
      c--; \
    } \
    list[c]=j; \
  } \
} while (0)


long long quicksort (int argc, char ** argv)
{
  struct {                              // stack element.
    long long a,b;
  } stack[STACKSIZE];

  int top=-1;                           // initialise stack

  if (argc < 2)
  {
    printf ("Usage: quicksort <array-size>\n");
    exit(1);
  }

  int len = atoi(argv[1]);
  long long *list = (long long *) malloc (len*sizeof(long long));

  if (!list) {
    printf ("%s(): array allocation of size %d failed.\n", __func__, len);
    exit (1);
  }

  int i;

  srand48 (0x12345678);

  for (i = 0; i < len; i++) {
    list[i] = (((long long)lrand48()) << 32) | ((long long)lrand48()) ;
  }

  if (len <= 10)
  {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++)
      printf ("list[%d] = %lld\n", i, list[i]);
  }

  int first,last,splitpoint;

  push(0,len-1);
  while (top!=-1) {
    pop(&first,&last);
    for (;;) {
      if (last-first>SMALLSIZE) {
	// find the larger sub-list
	split(first,last,&splitpoint);
	// push the smaller list
	if (last-splitpoint<splitpoint-first) {
	  push(first,splitpoint-1);
	  first=splitpoint+1;
	}
	else {
	  push(splitpoint+1,last);
	  last=splitpoint-1;
	}
      }
      else {  // sort the smaller sub-lists
	// through insertion sort
	insertion_sort(first,last);
	break;
      }
    }
  }                        // iterate for larger list


  if (len <= 10)
  {
    printf ("Printing Sorted array:\n");
    for (i = 0; i < len; i++)
      printf ("list[%d] = %lld\n", i, list[i]);
  }

  return len;
}



long long
hanoi1 (int argc, char **argv)
{
  /* Kolar's Hanoi Tower algorithm no. 1 */
  /* http://hanoitower.mkolar.org/algo.html */
#define ALLO(x) do { \
  if((x = (int *)malloc((n+3) * sizeof(int))) == NULL) {\
    fprintf(stderr, #x " allocation failed!\n"); exit(1); }\
} while (0)

  int i, *a, *b, *c, *p, *fr, *to, *sp, n, n1, n2;
  long long num_moves = 0;

  n = atoi(argv[1]);
  n1 = n+1;
  n2 = n+2;
  ALLO(a);
  ALLO(b);
  ALLO(c);

  a[0] = 1; b[0] = c[0] = n1;
  a[n1] = b[n1] = c[n1] = n1;
  a[n2] = 1; b[n2] = 2; c[n2] = 3;
  for(i=1; i<n1; i++) {
    a[i] = i; b[i] = c[i] = 0;
  }

  fr = a;
  if(n&1) { to = c; sp = b; }
  else    { to = b; sp = c; }

  while(c[0]>1) {
    i = fr[fr[0]++];
    if (n <= 5)
    {
      printf("move disc %d from %d to %d\n", i, fr[n2], to[n2]);
    }
    num_moves++;
    p=sp;
    if((to[--to[0]] = i)&1) {
      sp=to;
      if(fr[fr[0]] > p[p[0]]) { to=fr; fr=p; }
      else to=p;
    } else { sp=fr; fr=p; }
  }

  return num_moves;
}

long long
hanoi2 (int argc, char **argv)
{
  /*  Er's LLHanoi Hanoi Tower loop less algorithm */
  int i, dir, *D, *s, n, n1;

  n = atoi(argv[1]);
  n1 = n+1;
  ALLO(D);
  ALLO(s);

  for(i=0; i<=n1; i++) {
    D[i] = 1; s[i] = i+1;
  }

  dir = n&1;

  long long num_moves = 0;
  for(;;) {
    i = s[0];
    if(i>n) break;
    int prevD = D[i];
    D[i]=(D[i]+(i&1?dir:1-dir))%3+1;
    if (n <=5)
    {
      printf ("move disc %d from %d to %d\n", i, prevD, D[i]);
    }
    num_moves++;
    s[0] = 1;
    s[i-1] = s[i];
    s[i] = i+1;
  }
  return num_moves;
}


long long
hanoi3 (int argc, char **argv)
{
#define TOWER_ID(x) (((x) == a)?1:((x)==b)?2:((x)==c)?3:-1)
  int i, *a, *b, *c, *p, *o1, *o2, *e, n, n1;

  n = atoi(argv[1]);
  n1 = n+1;
  ALLO(a);
  ALLO(b);
  ALLO(c);

  a[0] = 1; b[0] = c[0] = n1;
  a[n1] = n1; b[n1] = n+2; c[n1] = n+3;
  for(i=1; i<n1; i++) {
    a[i] = i; b[i] = c[i] = 0;
  }

  o1 = a;
  if(n&1) { o2 = b; e = c; }
  else    { o2 = c; e = b; }

  long long num_moves = 0;
  while(*c>1) {
    num_moves++;
    if(o1[*o1] > e[*e])
    {
      if (n <=5)
      {
	printf ("move disc from %d to %d\n", TOWER_ID(e), TOWER_ID(o1));
      }
      o1[--(*o1)] = e[(*e)++];
    }
    else
    {
      if (n <=5)
      {
	printf ("move disc from %d to %d\n", TOWER_ID(o1), TOWER_ID(e));
      }
      e[--(*e)] = o1[(*o1)++];
    }
    p = e; e = o1; o1 = o2; o2 = p;
  }
  return num_moves;
}

long long
emptyloop(int argc, char **argv)
{
  long long i, numiter;

  if (argc < 2) {
    printf ("Usage: emptyloop <num-iter>\n");
    exit (1);
  }
 
  numiter = atoi(argv[1]);

  for (i = 0; i < MAX(MAGIC_NUMBER,numiter); i++);

  return i;
}

long long
printloop (int argc, char **argv)
{
  long long i, numiter;

  if (argc < 2)
  {
    printf ("Usage: printloop <num-iter>\n");
    exit (1);
  }
 
  numiter = atoi(argv[1]);

  for (i = 0; i < numiter; i++)
  {
    printf ("hello, world\n");
  }

  return i;
}

static long long compute_fibo_rec2(int n);
static long long
compute_fibo_rec2_helper(int n)
{
  if (n < 3) {
    return 1;
  }
  return (compute_fibo_rec2(n - 1) + compute_fibo_rec2(n - 2));
}

static long long
compute_fibo_rec2(int n)
{
  if (n < 3) {
    return 1;
  }
  return (compute_fibo_rec2_helper(n - 1) + compute_fibo_rec2_helper(n - 2));
}

static long long
fibo_rec2(int argc, char **argv)
{
  int n;
  if (argc < 2) {
    printf ("Usage: fibo_rec2 <n>\n");
    exit (1);
  }
  n = atoi (argv[1]);
  return compute_fibo_rec2(n);
}

static long long
compute_fibo_rec (int n)
{
  if (n < 3) {
    return 1;
  }
  return (compute_fibo_rec(n - 1) + compute_fibo_rec(n - 2));
}

static long long
fibo_rec(int argc, char **argv)
{
  int n;

  if (argc < 2) {
    printf ("Usage: fibo_rec <n>\n");
    exit (1);
  }
  n = atoi(argv[1]);
  return compute_fibo_rec(n);
}

long long
compute_fibo_iter (int n)
{
  long long fibo_cur, fibo_prev;
  int i, tmp;

  if (n < 3)
    return 1;

  fibo_cur = 1;
  fibo_prev = 1;

  for (i = 3; i <= n; i++)
  {
    tmp = fibo_cur;
    fibo_cur += fibo_prev;
    fibo_prev = tmp;
  }

  return fibo_cur;
}

long long
fibo_iter (int argc, char **argv)
{
  int n;

  if (argc < 2)
  {
    printf ("Usage: fibo_iter <n>\n");
    exit (1);
  }
 
  n = atoi (argv[1]);

  return compute_fibo_iter (n);
}

int ll_compare(const void *_a, const void *_b)
{
  long long *a = (long long *)_a;
  long long *b = (long long *)_b;

  return (*a - *b);
}

#define modulus(v,d) (((unsigned long long)v)%(d))
long long
binary_search (int argc, char **argv)
{
  long long n;
  if (argc < 2)
  {
    printf ("Usage: binary_search <num-searches>\n");
    exit(1);
  }

  srand48 (0x12345678);

  long long num_searches = atoi(argv[1]);
  int num_elems = MAX(num_searches/1000,10);
  long long domain = 2*num_elems;
  //long long domain = 0x7fffffffffffffffLL;
  long long *arr = (long long *) malloc (num_elems*sizeof(long long));

  if (!arr) {
    printf ("%s(): array allocation of size %d failed.\n", __func__, num_elems);
    exit (1);
  }

  int i;
  for (i = 0; i < num_elems; i++)
  {
    arr[i] = (((long long)lrand48())<<32) | ((long long)lrand48());
    arr[i] = modulus(arr[i], domain);
  }

  qsort(arr, num_elems, sizeof (long long), ll_compare);

  if (num_searches <= 10)
  {
    printf ("Printing array elements:\n");
    for (i = 0; i < num_elems; i++)
    {
      printf ("%lld\n", arr[i]);
    }
  }

  long long num_found = 0;
  long long sval = (((long long)lrand48())<<32) | ((long long)lrand48());
  for (i = 0; i < num_searches; i++)
  {
    sval *= 7919;
    long long dval = modulus(sval, domain);
    
    if (num_searches <= 10)
    {
      printf ("Searching %lld: ", dval);
    }

    int start = 0, stop = num_elems;

    while (stop > start)
    {
      int middle = (start + stop)/2;
      if (dval < arr[middle])
      {
	stop = middle;
      }
      else if (dval > arr[middle])
      {
	start = middle + 1;
      }
      else
      {
	if (num_searches <= 10) printf ("found\n");
	num_found++;
	break;
      }
    }
    if (num_searches <= 10 && stop <= start) printf ("not found\n");
  }

  return num_found;
}

long long
link_list_search (int argc, char **argv)
{
  long long n;
  if (argc < 2)
  {
    printf ("Usage: link_list_search <num-searches>\n");
    exit(1);
  }

  srand48 (0x12345678);

  long long num_searches = atoi(argv[1]);
  long long num_elems = MAX(num_searches/100,10);
  long long domain = 2*num_elems;
  //long long domain = 0x7fffffffffffffffLL;
  typedef struct node_t {
    long long val;
    struct node_t *next;
  } node_t;

  node_t *head = NULL;

  int i;
  for (i = 0; i < num_elems; i++) {
    node_t *node = (node_t *) malloc (sizeof(node_t));
    if (!node) {
      printf ("%s: Link-list node allocation failed.\n", __func__);
      exit(1);
    }
    node->next = head;
    node->val = (((long long)lrand48())<<32) | ((long long)lrand48());
    node->val = modulus(node->val, domain);
    head = node;
  }

  if (num_searches <= 10) {
    node_t *cur;
    printf ("Printing link-list elements:\n");
    for (cur = head; cur; cur = cur->next) {
      printf ("%lld\n", cur->val);
    }
  }

  long long num_found = 0;
  long long sval = (((long long)lrand48())<<32) | ((long long)lrand48());
  for (i = 0; i < num_searches; i++) {
    sval *= 7919;
    long long dval = modulus(sval, domain);
    
    if (num_searches <= 10) {
      printf ("Searching %lld: ", dval);
    }

    node_t *cur;
    for (cur = head; cur; cur=cur->next) {
      if (cur->val == dval) {
        if (num_searches <= 10) printf ("found\n");
        num_found++;
        break;
      }
    }
    if (num_searches <= 10 && !cur) printf ("not found\n");
  }

  return num_found;
}

#define HASH_FN(val,tsize) (((unsigned long long)val)%tsize)
long long
openhash_search (int argc, char **argv)
{
  long long n;
  if (argc < 2) {
    printf ("Usage: openhash_search <num-searches>\n");
    exit(1);
  }

  srand48 (0x12345678);

  long long num_searches = atoi(argv[1]);
  int num_elems = MAX(num_searches/1000,10);
  long long domain = 2*num_elems;

  typedef struct node_t {
    long long val;
    struct node_t *next;
  } node_t;

  node_t **htable = (node_t **) malloc (num_elems*sizeof(node_t *));

  if (!htable) {
    printf("%s(): htable allocation of size %d failed.\n", __func__, num_elems);
    exit (1);
  }
  memset(htable, 0x0, num_elems*sizeof(node_t *));

  int i;
  for (i = 0; i < num_elems; i++) {
    long long val = (((long long)lrand48())<<32) | ((long long)lrand48());
    val = modulus(val, domain);
    int hval = HASH_FN(val, num_elems);
    node_t *node = (node_t *) malloc (sizeof(node));
    if (!node) {
      printf ("%s(): htable node allocation failed.\n", __func__);
      exit (1);
    }
    node->val = val;
    node->next = htable[hval];
    htable[hval] = node;
  }

  if (num_searches <= 10) {
    printf ("Printing array elements:\n");
    for (i = 0; i < num_elems; i++) {
      node_t *cur;
      for (cur = htable[i]; cur; cur = cur->next) {
        printf ("%lld\n", cur->val);
      }
    }
  }

  long long num_found = 0;
  long long sval = (((long long)lrand48())<<32) | ((long long)lrand48());
  for (i = 0; i < num_searches; i++) {
    sval *= 7919;
    long long dval = modulus(sval, domain);
    
    int hval = HASH_FN(dval, num_elems);
    if (num_searches <= 10) {
      printf ("Searching %lld (hval %d): ", dval, hval);
    }

    node_t *cur;
    for (cur = htable[hval]; cur; cur = cur->next) {
      if (cur->val == dval) {
        if (num_searches <= 10) printf ("found\n");
        num_found++;
        break;
      }
    }

    if (num_searches <= 10 && !cur) printf ("not found\n");
  }

  return num_found;
}

long long
closedhash_search (int argc, char **argv)
{
  long long n;
  if (argc < 2)
  {
    printf ("Usage: closedhash_search <num-searches>\n");
    exit(1);
  }

  srand48 (0x12345678);

  long long num_searches = atoi(argv[1]);
  long long num_elems = MAX(num_searches/1000,10);
  long long domain = 2*num_elems;
  int htable_size = num_elems + 1;

  long long *htable = (long long *) malloc (htable_size*sizeof(long long));

  if (!htable) {
    printf("%s(): htable allocation of size %d failed.\n",__func__, htable_size);
    exit (1);
  }
  memset(htable, 0xff, htable_size*sizeof(long long));

  int i;
  for (i = 0; i < num_elems; i++) {
    long long val = (((long long)lrand48())<<32) | ((long long)lrand48());
    val = modulus(val, domain);
    int hval = HASH_FN(val, htable_size);
    while (htable[hval] != -1) hval = (hval + 1)%htable_size;
    htable[hval] = val;
  }

  if (num_searches <= 10) {
    printf ("Printing array elements:\n");
    for (i = 0; i < htable_size; i++) {
      if (htable[i] != -1) {
        printf ("%lld\n", htable[i]);
      }
    }
  }

  long long num_found = 0;
  long long sval = (((long long)lrand48())<<32) | ((long long)lrand48());
  for (i = 0; i < num_searches; i++) {
    sval *= 7919;
    long long dval = modulus(sval, domain);
    
    if (num_searches <= 10) {
      printf ("Searching %lld: ", dval);
    }

    int hval = HASH_FN(dval, htable_size);

    while (htable[hval] != -1) {
      if (htable[hval] == dval) {
        if (num_searches <= 10) printf ("found\n");
        num_found++;
        break;
      }
      hval = (hval + 1) % htable_size;
    }

    if (num_searches <= 10 && htable[hval]==-1) printf ("not found\n");
  }

  return num_found;
}

int
main (int argc, char **argv)
{
  if (argc < 2)
      usage();

  if (!strcmp (argv[1], "fibo_rec")) {
    long long ret;
    ret = fibo_rec (argc - 1, argv + 1);
    printf("%lld\n", ret);
    return 0;
  }

  if (!strcmp(argv[1], "fibo_rec2")) {
    long long ret;
    ret = fibo_rec2(argc - 1, argv + 1);
    printf("%lld\n", ret);
    return 0;
  }

  if (!strcmp(argv[1], "fibo_iter")) {
    long long ret;
    ret = fibo_iter(argc - 1, argv + 1);
    printf("%lld\n", ret);
    return 0;
  }

  if (!strcmp(argv[1], "printloop")) {
    long long ret;
    ret = printloop(argc - 1, argv + 1);
    printf("Completed %lld iterations of print loop.\n", ret);
    return 0;
  }

  if (!strcmp(argv[1], "emptyloop")) {
    long long ret;
    ret = emptyloop(argc - 1, argv + 1);
    printf("Completed %lld iterations of empty loop.\n", ret);
    return 0;
  }

  if (!strcmp(argv[1], "bubsort")) {
    long long ret;
    ret = bubsort(argc - 1, argv + 1);
    printf("Bubble sorted an array of size %lld.\n", ret);
    return 0;
  }

  if (!strcmp(argv[1], "mergesort")) {
    long long ret;
    ret = mergesort(argc - 1, argv + 1);
    printf("Merge-sorted an array of size %lld.\n", ret);
    return 0;
  }

  if (!strcmp(argv[1], "quicksort")) {
    long long ret;
    ret = quicksort(argc - 1, argv + 1);
    printf("Quick-sorted an array of size %lld.\n", ret);
    return 0;
  }

  if (!strcmp (argv[1], "link_list_search")) {
    long long ret;
    ret = link_list_search (argc - 1, argv + 1);
    long long num_searches = atoi(argv[2]);
    printf("link_list_search: %lld successful searches (total %lld).\n", ret,
        num_searches);
    return 0;
  }

  if (!strcmp (argv[1], "binary_search")) {
    long long ret;
    ret = binary_search (argc - 1, argv + 1);
    long long num_searches = atoi(argv[2]);
    printf("binary_search: %lld successful searches (total %lld).\n", ret,
        num_searches);
    return 0;
  }

  if (!strcmp (argv[1], "openhash_search")) {
    long long ret;
    ret = openhash_search (argc - 1, argv + 1);
    long long num_searches = atoi(argv[2]);
    printf ("openhash_search: %lld successful searches (total %lld).\n", ret,
        num_searches);
    return 0;
  }

  if (!strcmp (argv[1], "closedhash_search")) {
    long long ret;
    ret = closedhash_search (argc - 1, argv + 1);
    long long num_searches = atoi(argv[2]);
    printf ("closedhash_search: %lld successful searches (total %lld).\n", ret,
        num_searches);
    return 0;
  }


  if (!strcmp (argv[1], "hanoi1")) {
    long long ret;
    ret = hanoi1(argc - 1, argv + 1);
    printf ("Used algo1 to solve towers of hanoi of size %s in %lld moves.\n", argv[1],
        ret);
    return 0;
  }

  if (!strcmp (argv[1], "hanoi2")) {
    long long ret;
    ret = hanoi2(argc - 1, argv + 1);
    printf ("Used algo2 to solve towers of hanoi of size %s in %lld moves.\n", argv[1],
        ret);
    return 0;
  }

  if (!strcmp (argv[1], "hanoi3")) {
    long long ret;
    ret = hanoi3(argc - 1, argv + 1);
    printf ("Used algo3 to solve towers of hanoi of size %s in %lld moves.\n", argv[2], ret);
    return 0;
  }

  if (!strcmp(argv[1], "sum8")) {
    int ret;
    ret = sum8(argc - 1, argv + 1);
    printf("Summed an array of 8-bit elements of size %d.\n", ret);
    return 0;
  }

  if (   !strcmp(argv[1], "image_diff")
      || !strcmp(argv[1], "bcmp")
      || !strcmp(argv[1], "memcmp")) {
    int ret, len;
    len = two_arrays(argc - 1, argv + 1);

    if (!strcmp(argv[1], "image_diff")) {
      ret = _image_diff(len);
    } else if (!strcmp(argv[1], "bcmp")) {
      ret = _memcmp(len);
    } else if (!strcmp(argv[1], "memcmp")) {
      ret = _memcmp(len);
    }
    printf("%s (len = %d): ret = %d\n", argv[1], len, ret);
    return 0;
  }

  if (!strcmp(argv[1], "memset")) {
    int ret;
    _memset(argc - 1, argv + 1);
    printf("memset (len = %d) done.\n", atoi(argv[2]));
  }

  if (!strcmp(argv[1], "memcpy")) {
    int ret;
    _memcpy(argc - 1, argv + 1);
    printf("memcpy (len = %d) done.\n", atoi(argv[2]));
  }

  if (!strcmp(argv[1], "memmove")) {
    int ret;
    _memmove(argc - 1, argv + 1);
    printf("memmove (len = %d) done.\n", atoi(argv[2]));
  }

  if (!strcmp(argv[1], "bcopy")) {
    _memcpy(argc - 1, argv + 1);
    printf("bcopy (len = %d): done.\n", atoi(argv[2]));
  }

  if (!strcmp(argv[1], "bzero")) {
    _bzero(argc - 1, argv + 1);
    printf("bzero (len = %d) done.\n", atoi(argv[2]));
  }

  /*if (!strcmp(argv[1], "memccpy")) {
    _memccpy(argc - 1, argv + 1);
    printf("memccpy (len = %d) done.\n", atoi(argv[2]));
  }

  if (!strcmp(argv[1], "memchr")) {
    _memchr(argc - 1, argv + 1);
    printf("memchr (len = %d) done.\n", atoi(argv[2]));
  }

  if (!strcmp(argv[1], "memfrob")) {
    _memfrob(argc - 1, argv + 1);
    printf("memfrob (len = %d) done.\n", atoi(argv[2]));
  }

  if (!strcmp(argv[1], "memmem")) {
    _memmem(argc - 1, argv + 1);
    printf("memmem (len = %d) done.\n", atoi(argv[2]));
  }*/


  if (   !strcmp(argv[1], "min")
      || !strcmp(argv[1], "comparison")
      || !strcmp(argv[1], "xor")
      || !strcmp(argv[1], "sprite_copy")) {
    int len;
    len = three_arrays(argc - 1, argv + 1);
    if (!strcmp(argv[1], "min")) {
      _min(len);
    } else if (!strcmp(argv[1], "comparison")) {
      _comparison(len);
    } else if (!strcmp(argv[1], "xor")) {
      _xor(len);
    } else if (!strcmp(argv[1], "sprite_copy")) {
      _sprite_copy(len);
    }
    if (len <= 10) {
      int i;
      printf ("Printing Output array:\n");
      for (i = 0; i < len; i++) {
        printf ("c[%d] = 0x%hhx\n", i, c[i]);
      }
    }
    return 0;
  }
/*
  if (!strcmp (argv[1], "sum_linklist"))
  {
    ret = sum_linklist (argc - 1, ++argv);
    printf ("%lld\n", ret);
    return 0;
  }

  if (!strcmp (argv[1], "sum_array"))
  {
    ret = sum_array (argc - 1, ++argv);
    return 0;
  }
*/
}
