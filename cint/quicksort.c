#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

//#define MAXELT          100
#define INFINITY        0x7fffffffffffffffLL //numbers in list should not exceed
// this. change the value to suit your
// needs
#define SMALLSIZE       10            // not less than 3
#define STACKSIZE       100           // should be ceiling(lg(MAXSIZE)+1)

#define swap(x, y)  do { \
  long temp; \
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
  long x; \
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
  long j; \
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




int
main(int argc, char ** argv)
{
  struct {                              // stack element.
    long a,b;
  } stack[STACKSIZE];

  int top=-1;                           // initialise stack

  int len = 0xc00000;
  if (argc >= 2) {
    len = atoi(argv[1]);
  }

  long *list = (long *) malloc (len*sizeof(long));

  if (!list) {
    printf ("%s(): array allocation of size %d failed.\n", __func__, len);
    return 1;
  }

  int i;

  srand48 (0x12345678);

  for (i = 0; i < len; i++) {
    list[i] = lrand48();
  }

  if (len <= 10) {
    printf ("Printing Input array:\n");
    for (i = 0; i < len; i++) {
      printf ("list[%d] = %ld\n", i, list[i]);
    }
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


  if (len <= 10) {
    printf ("Printing Sorted array:\n");
    for (i = 0; i < len; i++)
      printf ("list[%d] = %ld\n", i, list[i]);
  }

  printf("min element = %ld.\n", list[0]);
  printf("median element = %ld.\n", list[len / 2]);
  printf("max element = %ld.\n", list[len - 1]);

  return 0;
}
