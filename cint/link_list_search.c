#include <string.h>
#include <stdio.h>
//#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define modulus(v,d) (((unsigned long)v)%(d))

int
main(int argc, char **argv)
{
  long num_searches = 0xa0000;
  long n;
  if (argc >= 2) {
    num_searches = atoi(argv[1]);
  }

  srand48 (0x12345678);

  long num_elems = MAX(num_searches/100,10);
  long domain = 2*num_elems;
  //long long domain = 0x7fffffffffffffffLL;
  typedef struct node_t {
    long val;
    struct node_t *next;
  } node_t;

  node_t *head = NULL;

  int i;
  for (i = 0; i < num_elems; i++) {
    node_t *node = (node_t *) malloc (sizeof(node_t));
    if (!node) {
      printf ("%s: Link-list node allocation failed.\n", __func__);
      return 1;
    }
    node->next = head;
    node->val = lrand48();
    node->val = modulus(node->val, domain);
    head = node;
  }

  if (num_searches <= 10) {
    node_t *cur;
    printf ("Printing link-list elements:\n");
    for (cur = head; cur; cur = cur->next) {
      printf ("%ld\n", cur->val);
    }
  }

  long num_found = 0;
  long sval = lrand48();
  for (i = 0; i < num_searches; i++) {
    sval *= 7919;
    long dval = modulus(sval, domain);
    
    if (num_searches <= 10) {
      printf ("Searching %ld: ", dval);
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

  printf("num searches: %ld\n", num_searches);
  printf("num found: %ld\n", num_found);
  return 0;
}
