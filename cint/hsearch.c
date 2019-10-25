#include <string.h>
#include <stdio.h>
//#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

void *malloc(size_t);
void free(void *);

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define modulus(v,d) (((unsigned long)v)%(d))
#define NUM_BUCKETS 13

typedef struct node_t {
  long val;
  struct node_t *next;
} node_t;
node_t *head[NUM_BUCKETS];


void __attribute__ ((noinline))
create_hashtable(long num_elems, long domain)
{
  for (size_t i = 0; i < NUM_BUCKETS; i++) {
     head[i] = NULL;
  }

  int i;
  for (i = 0; i < num_elems; i++) {
    node_t *node = (node_t *) malloc (sizeof(node_t));
    if (!node) {
      printf ("%s: Link-list node allocation failed.\n", __func__);
      exit(1);
    }
    node->val = lrand48();
    node->val = modulus(node->val, domain);
    int h = modulus(node->val, NUM_BUCKETS);
    node->next = head[h];
    head[h] = node;
  }
}

node_t * __attribute__ ((noinline))
hsearch(long dval)
{
  int h = dval % NUM_BUCKETS;
  node_t *cur;
  for (cur = head[h]; cur; cur=cur->next) {
    if (cur->val == dval) {
      return cur;
    }
  }
  return NULL;
}

int
main(int argc, char **argv)
{
  long num_searches = 0xa0000;
  long n;
  if (argc >= 2) {
    num_searches = atoi(argv[1]);
  }

  srand48 (0x12345678);

  long num_elems = MAX(num_searches/30,10);
  long domain = 2*num_elems;
  //long long domain = 0x7fffffffffffffffLL;

  create_hashtable(num_elems, domain);

  if (num_searches <= 10) {
    node_t *cur;
    printf ("Printing link-list elements:\n");
    for (size_t i = 0; i < NUM_BUCKETS; i++) {
      for (cur = head[i]; cur; cur = cur->next) {
        printf ("%ld\n", cur->val);
      }
    }
  }

  long num_found = 0;
  long sval = lrand48();
  for (int i = 0; i < num_searches; i++) {
    sval *= 7919;
    long dval = modulus(sval, domain);
    
    if (num_searches <= 10) {
      printf ("Searching %ld: ", dval);
    }
    node_t *cur = hsearch(dval);
    if (cur) {
      num_found++;
    }
    if (num_searches <= 10) {
      if (!cur) printf ("not found\n");
      else printf("found\n");
    }
  }

  printf("num searches: %ld\n", num_searches);
  printf("num found: %ld\n", num_found);
  return 0;
}
