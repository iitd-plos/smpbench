#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdbool.h>

//const char interp_section[] __attribute__((section(".interp"))) = "/path/to/dynamic/linker";

void myexit(int ec);

#define NDATA (int *)mymalloc(ncol * sizeof(int))
#define NLIST (struct _list *)mymalloc(sizeof(struct _list))
#define NPLAY (struct _play *)mymalloc(sizeof(struct _play))
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

//#define mymalloc abcmall
#define atoi my_atoi
#define memset mymemset
#define memcpy mymemcpy
#define memcmp mymemcmp
#define strcmp mystrcmp
#define strncmp mystrncmp



struct _list
{
  int *data;
  struct _list *next;
} *wanted;

struct _play
{
  int value;
  int *state;
  struct _list *first;
  struct _play *next;
} *game_tree;

int nrow = 3,ncol = 5;      /* global so as to avoid passing them all over the place */

void *mymalloc(size_t size);



int *copy_data(int* data) /* creates a duplicate of a given -data list */
{
  int *new = NDATA;
  int counter = ncol;
  while (counter --)
      new[counter] = data[counter];
  return new;
}

int next_data(int *data)  /* gives the next logical setup to the one passed */
                          /* new setup replaces the old. Returns 0 if no valid */
{                         /* setup exists after the one passed */
  int counter = 0;
  int valid = 0;     /* default to none */
  while ((counter != ncol) && (! valid)) /* until its done */
    {
      if (data[counter] == nrow) /* if we hit a border */
        {
	  data[counter] = 0;     /* reset it to zero     */
	  counter ++;      /* and take next column */
	}
       else
        {
	  data[counter] ++;      /* otherwise, just increment row number */
	  valid = 1;                /* and set valid to true. */
	}
    }
  return valid;                     /* return whether or not */
}                                   /* a next could be found */

void melt_data(int *data1,int *data2) /* melts 2 _data's into the first one. */
{
  int counter = ncol;
  while (counter --)     /* do every column */
    {
      if (data1[counter] > data2[counter]) /* take the lowest one */
          data1[counter] = data2[counter]; /* and put in first _data */
    }
}

void melt_data_simple(int *data1,int *data2) /* melts 2 _data's into the first one. */
{
  int counter = ncol;
  while (counter --)     /* do every column */
    {
      data1[counter] = data2[counter]; /* put in first _data */
    }
}



int equal_data(int *data1,int *data2) /* check if both _data's are equal */
{
  int counter = ncol;
  while ((counter --) && (data1[counter] == data2[counter]));
  return (counter < 0);
}

int valid_data(int *data) /* checks if the play could ever be achieved. */
{
  int low;      /* var to hold the current height */
  int counter = 0;
  low = nrow;   /* default to top of board */
  while (counter != ncol) /* for every column */
    {
      if (data[counter] > low) break;  /* if you get something higher */
      low = data[counter];             /* set this as current height */
      counter ++;
    }
  return (counter == ncol);
}

void dump_list(struct _list *list) /* same for a _list structure */
{
  if (list != NULL)
    {
      dump_list(list -> next); /* dump the rest of it */
      myfree(list -> data); /* and its _data structure */
      myfree(list);
    }
}

__attribute__((noinline)) void dump_play(struct _play *play) /* and for the entire game tree */
{
  if (play != NULL)
    {
      dump_play(play -> next);  /* dump the rest of the _play */
      dump_list(play -> first); /* its _list */
      myfree(play -> state); /* and its _data */
      myfree(play);
    }
}

int get_value(int *data) /* get the value (0 or 1) for a specific _data */
{
  struct _play *search;
  search = game_tree; /* start at the begginig */
  while (! equal_data(search -> state,data)) /* until you find a match */
      search = search -> next; /* take next element */
  return search -> value; /* return its value */
}

void show_data(int *data) /* little display routine to give off results */
{
  int counter = 0;
  while (counter != ncol)
    {
      printf("%d",data[counter ++]);
      if (counter != ncol) putchar(',');
    }
}

void show_move(int *data) /* puts in the "(" and ")" for show_data() */
{
  putchar('(');
  show_data(data);
  printf(")\n");
}

void show_list(struct _list *list) /* show the entire list of moves */
{
  while (list != NULL)
    {
      show_move(list -> data);
      list = list -> next;
    }
}

void show_play(struct _play *play) /* to diplay the whole tree */
{
  while (play != NULL)
    {
      printf("For state :\n");
      show_data(play -> state);
      printf("  value = %d\n",play -> value);
      printf("We get, in order :\n");
      show_list(play -> first);
      play = play -> next;
    }
}

int in_wanted(int *data) /* checks if the current _data is in the wanted list */
{
  struct _list *current;
  current = wanted; /* start at the begginig */
  while (current != NULL) /* unitl the last one */
    {
      if (equal_data(current -> data,data)) break; /* break if found */
      current = current -> next; /* take next element */
    }
  if (current == NULL) return 0; /* if at the end, not found */
  return 1;
}

__attribute__((noinline)) int *make_data(int row,int col) /* creates a new _data with the correct */
                                /* contents for the specified row & col */
{
  int count;
  int *new = NDATA;
  for (count = 0;count != col;count ++) /* creates col-1 cells with nrow */
      new[count] = nrow;
  for (;count != ncol;count ++) /* and the rest with row as value */
      new[count] = row;
  return new;         /* and return pointer to first element */
}

struct _list *make_list(int *data,int *value,int *all) /* create the whole _list of moves */
                                                          /* for the _data structure data */
{
  int row,col;
  int *temp;
  struct _list *head,*current;
  *value = 1; /* set to not good to give */
  head = NLIST; /* create dummy header */
  head -> next = NULL; /* set NULL as next element */
  current = head;      /* start from here */
  for (row = 0;row != nrow;row ++) /* for every row */
    {
      for (col = 0;col != ncol;col ++) /* for every column */
        {
	  temp = make_data(row,col); /* create _data for this play */
	  melt_data(temp,data);      /* melt it with the current one */
	  if (! equal_data(temp,data)) /* if they are different, it good */
	    {
	      current -> next = NLIST; /* create new element in list */
	      current -> next -> data = copy_data(temp); /* copy data, and place in list */
	      current -> next -> next = NULL; /* NULL the next element */
	      current = current -> next; /* advance pointer */
	      if (*value == 1) /* if still not found a good one */
	          *value = get_value(temp); /* look at this value */
	      if ((! *all) && (*value == 0))
	        {  /* if we found it, and all is not set */
		  col = ncol - 1; /* do what it take sto break out now */
		  row = nrow - 1;
	          if (in_wanted(temp)) /* if in the wanted list */
		      *all = 2; /* flag it */
		}
	    }
	   else /* if its not a valid move */
	    {
	      if (col == 0) row = nrow - 1; /* break out if at first column */
	      col = ncol - 1;               /* but make sure you break out */
	    }                               /* of the col for-loop anyway */
	  myfree(temp); /* dump this unneeded space */
	}
    }
  current = head -> next; /* skip first element */
  myfree(head); /* dump it */
  if (current != NULL) *value = 1 - *value; /* invert value if its */
  return current;                           /* not the empty board */
}

__attribute__((noinline)) struct _play *make_play(int all) /* make up the entire tree-like stuff */
{
  int val;
  int *temp;
  struct _play *head,*current;
  head = NPLAY; /* dummy header again */
  current = head; /* start here */
  game_tree = NULL; /* no elements yet */
  temp = make_data(0,0); /* new data, for empty board */
  temp[0] --;   /* set it up at (-1,xx) so that next_data() returns (0,xx) */
  while (next_data(temp)) /* take next one, and break if none */
    {
      if (valid_data(temp)) /* if board position is possible */
        {
	  current -> next = NPLAY; /* create a new _play cell */
	  if (game_tree == NULL) game_tree = current -> next;
	      /* set up game_tree if it was previously NULL */
	  current -> next -> state = copy_data(temp); /* make a copy of temp */
	  current -> next -> first = make_list(temp,&val,&all);
	      /* make up its whole list of possible moves */
	  current -> next -> value = val; /* place its value */
	  current -> next -> next = NULL; /* no next element */
	  current = current -> next;      /* advance pointer */
	  if (all == 2)                   /* if found flag is on */
	    {
	      myfree(temp);            /* dump current temp */
	      temp = make_data(nrow,ncol); /* and create one that will break */
	    }
	}
    }
  current = head -> next; /* skip first element */
  myfree(head);             /* dump it */
  return current;         /* and return pointer to start of list */
}

void make_wanted(int *data) /* makes up the list of positions from the full board */
{
         /* everything here is almost like in the previous function. */
	 /* The reason its here, is that it does not do as much as   */
	 /* the one before, and thus goes faster. Also, it saves the */
	 /* results directly in wanted, which is a global variable.  */

  int row,col;
  int *temp;
  struct _list *head,*current;
  head = NLIST;
  head -> next = NULL;
  current = head;
  for (row = 0;row != nrow;row ++)
    {
      for (col = 0;col != ncol;col ++)
        {
	  temp = make_data(row,col);
	  melt_data(temp,data);
	  if (! equal_data(temp,data))
	    {
	      current -> next = NLIST;
	      current -> next -> data = copy_data(temp);
	      current -> next -> next = NULL;
	      current = current -> next;
	    }
	   else
	    {
	      if (col == 0) row = nrow - 1;
	      col = ncol - 1;
	    }
	  myfree(temp);
	}
    }
  current = head -> next;
  myfree(head);
  wanted = current;
}

__attribute__((noinline)) int *get_good_move(struct _list *list) /* gets the first good move from a _list */
{
  if (list == NULL) return NULL; /* if list is NULL, say so */
      /* until end-of-list or a good one is found */
      /* a good move is one that gives off a zero value */
  while ((list -> next != NULL) && (get_value(list -> data)))
      list = list -> next;
  return copy_data(list -> data); /* return the value */
}

int *get_winning_move(struct _play *play) /* just scans for the first good move */
                                          /* in the last _list of a _play. This */
{                                         /* is the full board */
  int *temp;
  while (play -> next != NULL) play = play -> next; /* go to end of _play */
  temp = get_good_move(play -> first); /* get good move */
  return temp;                         /* return it */
}

__attribute__((noinline)) struct _list *where(int *data,struct _play *play)
{
  while (! equal_data(play -> state,data)) /* search for given _data */
      play = play -> next;
  return play -> first;  /* return the pointer */
}

__attribute__((noinline)) void get_real_move(int *data1,int *data2,int *row,int *col) /* returns row & col of the move */
                                                           /* which created data1 from data2 */
{
  *col = 0;
  while (data1[*col] == data2[*col]) /* until there is a change */
      (*col) ++;             /* and increment col number */
  *row = data1[*col];  /* row is given by the content of the structure */
}

int main_chomp(void)
{
  int row,col,player;
  int *current,*temp;
  struct _play *tree;


  ncol = 7;
#ifdef SMALL_PROBLEM_SIZE
  nrow = 7;
#else
  nrow = 8;
#endif
  tree = make_play(1); /* create entire tree structure, not just the */
  player = 0;          /* needed part for first move */
  current = make_data(nrow,ncol); /* start play at full board */
  while (current != NULL)
    {
      temp = get_good_move(where(current,tree)); /* get best move */
      if (temp != NULL)  /* temp = NULL when the poison pill is taken */
        {
          get_real_move(temp,current,&row,&col); /* calculate coordinates */
          /* print it out nicely */
          printf("player %d plays at (%d,%d)\n",player,row,col);
          player = 1 - player; /* next player to do the same */
          myfree(current);  /* dump for memory management */
        }
      current = temp; /* update board */
    }
  dump_play(tree); /* dump unneeded tree */
  printf("player %d loses\n",1 - player); /* display winning player */
  return 0;
}

/*****************************************************************************/
/*
 * The Computer Lannguage Shootout
 * http://shootout.alioth.debian.org/
 * Contributed by Heiner Marxen
 *
 * "fannkuch"	for C gcc
 *
 * $Id: fannkuch-gcc.code,v 1.33 2006/02/25 16:38:58 igouy-guest Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#define Int	int
#define Aint	int

__attribute__((noinline))void reverse_perm_old(Aint* perm1, Aint* perm, long *flips)
{
  int i;
#define XCH(x,y)  { Aint t_mp; t_mp=(x); (x)=(y); (y)=t_mp; }
   int k = perm1[0];    /* cache perm[0] in k */
   do {     /* k!=0 ==> k>0 */
    Int j;
    for( i=1, j=k-1 ; i<j ; ++i, --j ) {
        XCH(perm[i], perm[j])
    }
    *flips = *flips + 1;
    /*
     * Now exchange k (caching perm[0]) and perm[k]... with care!
     * XCH(k, perm[k]) does NOT work!
     */
    j=perm[k]; perm[k]=k ; k=j;
      }while( k );
}


__attribute__((noinline)) void init_perm1(Aint* perm1, int n)
{
  int i;
  for( i=0 ; i<n ; ++i ) perm1[i] = i;	/* initial (trivial) permu */
}

__attribute__((noinline))void copy_perm(Aint* perm1, Aint* perm, int n)
{
    int i;
	    for( i=1 ; i<n ; ++i ) {	/* perm = perm1 */
		perm[i] = perm1[i];
	    }
}    

__attribute__((noinline))long reverse_perm(Aint* perm1, Aint* perm, long flipsmax)
{
  long flips = 0;
  int i;
#define XCH(x,y)	{ Aint t_mp; t_mp=(x); (x)=(y); (y)=t_mp; }
   int k = perm1[0];		/* cache perm[0] in k */
   do {			/* k!=0 ==> k>0 */
		Int	j;
		for( i=1, j=k-1 ; i<j ; ++i, --j ) {
		    XCH(perm[i], perm[j])
		}
		flips = flips + 1;
		/*
		 * Now exchange k (caching perm[0]) and perm[k]... with care!
		 * XCH(k, perm[k]) does NOT work!
		 */
		j=perm[k]; perm[k]=k ; k=j;
	    }while( k );
      if( flipsmax < flips ) {
        flipsmax = flips;
      }
  return flipsmax;
}

__attribute__((noinline))long copy_and_reverse_perm(Aint* perm1, Aint* perm, long flipsmax, int n)
{
  const int n1  = n - 1;
  if( ! (perm1[0]==0 || perm1[n1]==n1) ) {
    copy_perm(perm1, perm, n);
    flipsmax = reverse_perm(perm1, perm, flipsmax);
  }
  return flipsmax;
}
__attribute__((noinline))void print_perm(Aint* perm1, int n)
{
    int		i;
	  for( i=0 ; i<n ; ++i ) printf("%d", (int)(1+perm1[i]));
	  printf("\n");
}

long
fannkuch( int n )
{
  Aint* perm;
  Aint* perm1;
  Aint* count;
  long  flips;
  long  flipsmax;
  int   r;
  int   i;
  int   k;
  int   didpr;

  if( n < 1 ) return 0;
  r = n; didpr = 0; flipsmax = 0;

  perm1 = mycalloc(n, sizeof(*perm1));
  init_perm1(perm1, n);
  perm  = mycalloc(n, sizeof(*perm ));
  count = mycalloc(n, sizeof(*count));

  for(;;) {
    if( didpr < 30 ) {
        print_perm(perm1, n);
        ++didpr;
    }
    flipsmax = copy_and_reverse_perm(perm1, perm, flipsmax, n);
	  for( ; r!=1 ; --r ) {
	      count[r-1] = r;
	  }
    for(;;) {
      if( r == n ) {
        return flipsmax;
      }
      /* rotate down perm[0..r] by one */
      {
        Aint perm0 = perm1[0];
        i = 0;
        while( i < r ) {
          k = i+1;
          perm1[i] = perm1[k];
          i = k;
        }
        perm1[r] = perm0;
      }
      if( (count[r] -= 1) > 0 ) {
        break;
      }
      ++r;
    }
  }
}


    int
main_fannkuch( int argc, char* argv[] )
{
    int		n = (argc>1) ? atoi(argv[1]) : 10;

    printf("Pfannkuchen(%d) = %ld\n", n, fannkuch(atoi("10")));
    return 0;
}
/*****
 build & benchmark results

BUILD COMMANDS FOR: fannkuch.gcc

Thu Sep 14 17:44:44 PDT 2006

/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -funroll-loops -march=pentium4  fannkuch.c -o fannkuch.gcc_run

=================================================================
COMMAND LINE (%A is single numeric argument):

fannkuch.gcc_run %A
N=10

PROGRAM OUTPUT
==============
12345678910
21345678910
23145678910
32145678910
31245678910
13245678910
23415678910
32415678910
34215678910
43215678910
42315678910
24315678910
34125678910
43125678910
41325678910
14325678910
13425678910
31425678910
41235678910
14235678910
12435678910
21435678910
24135678910
42135678910
23451678910
32451678910
34251678910
43251678910
42351678910
24351678910
Pfannkuchen(10) = 38
*****/
/* The Computer Language Shootout
   http://shootout.alioth.debian.org/

   Contributed by Josh Goldfoot
   to compile, use gcc -O3

   This revision uses "simple_hash.h," available from
   http://cvs.alioth.debian.org/cgi-bin/cvsweb.cgi/shootout/bench/Include/?cvsroot=shootout

*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

enum { ht_num_primes = 28 };

static unsigned long ht_prime_list[ht_num_primes] = {
    53ul,         97ul,         193ul,       389ul,       769ul,
    1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
    49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
    1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
    50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
    1610612741ul, 3221225473ul, 4294967291ul
};

struct ht_node {
    char *key;
    int val;
    struct ht_node *next;
};

struct ht_ht {
    int size;
    struct ht_node **tbl;
    int iter_index;
    struct ht_node *iter_next;
    int items;
#ifdef HT_DEBUG
    int collisions;
#endif /* HT_DEBUG */
};

/*inline*/ int ht_val(struct ht_node *node) {
    return(node->val);
}

/*inline*/ char *ht_key(struct ht_node *node) {
    return(node->key);
}

/*inline*/ int ht_hashcode(struct ht_ht *ht, char *key) {
    unsigned long val = 0;
    for (; *key; ++key) val = 5 * val + *key;
    return(val % ht->size);
}

struct ht_node *ht_node_create(char *key) {
    char *newkey;
    struct ht_node *node;
    if ((node = (struct ht_node *)mymalloc(sizeof(struct ht_node))) == 0) {
	perror("malloc ht_node");
	exit(1);
    }
    if ((newkey = (char *)strdup(key)) == 0) {
	perror("strdup newkey");
	exit(1);
    }
    node->key = newkey;
    node->val = 0;
    node->next = (struct ht_node *)NULL;
    return(node);
}

__attribute__((noinline)) struct ht_ht *ht_create(int size) {
    int i = 0;
    struct ht_ht *ht = (struct ht_ht *)mymalloc(sizeof(struct ht_ht));
    while (ht_prime_list[i] < size) { i++; }
    ht->size = ht_prime_list[i];
    ht->tbl = (struct ht_node **)mycalloc(ht->size, sizeof(struct ht_node *));
    ht->iter_index = 0;
    ht->iter_next = 0;
    ht->items = 0;
#ifdef HT_DEBUG
    ht->collisions = 0;
#endif /* HT_DEBUG */
    return(ht);
}

void ht_destroy(struct ht_ht *ht) {
    struct ht_node *cur, *next;
    int i;
    for (i=0; i<ht->size; i++) {
	next = ht->tbl[i];
	while (next) {
	    cur = next;
	    next = next->next;
	    myfree(cur->key);
	    myfree(cur);
	}
    }
    myfree(ht->tbl);
    myfree(ht);
}

/*inline*/ struct ht_node *ht_find(struct ht_ht *ht, char *key) {
    int hash_code = ht_hashcode(ht, key);
    struct ht_node *node = ht->tbl[hash_code];
    while (node) {
	if (strcmp(key, node->key) == 0) return(node);
	node = node->next;
    }
    return((struct ht_node *)NULL);
}

/*inline*/ __attribute__((noinline)) struct ht_node *ht_find_new(struct ht_ht *ht, char *key) {
    int hash_code = ht_hashcode(ht, key);
    struct ht_node *prev = 0, *node = ht->tbl[hash_code];
    while (node) {
	if (strcmp(key, node->key) == 0) return(node);
	prev = node;
	node = node->next;
#ifdef HT_DEBUG
	ht->collisions++;
#endif /* HT_DEBUG */
    }
    ht->items++;
    if (prev) {
	return(prev->next = ht_node_create(key));
    } else {
	return(ht->tbl[hash_code] = ht_node_create(key));
    }
}

/*
 *  Hash Table iterator data/functions
 */
/*inline*/ struct ht_node *ht_next(struct ht_ht *ht) {
    unsigned long index;
    struct ht_node *node = ht->iter_next;
    if (node) {
	ht->iter_next = node->next;
	return(node);
    } else {
	while (ht->iter_index < ht->size) {
	    index = ht->iter_index++;
	    if (ht->tbl[index]) {
		ht->iter_next = ht->tbl[index]->next;
		return(ht->tbl[index]);
	    }
	}
    }
    return((struct ht_node *)NULL);
}

/*inline*/ struct ht_node *ht_first(struct ht_ht *ht) {
    ht->iter_index = 0;
    ht->iter_next = (struct ht_node *)NULL;
    return(ht_next(ht));
}

/*inline*/ int ht_count(struct ht_ht *ht) {
    return(ht->items);
}

__attribute__((noinline)) long
hash_table_size (int fl, long buflen)
{
  long maxsize1, maxsize2;

  maxsize1 = buflen - fl;
  maxsize2 = 4;
  while (--fl > 0 && maxsize2 < maxsize1)
    maxsize2 = maxsize2 * 4;
  if (maxsize1 < maxsize2)
    return maxsize1;
  return maxsize2;
}

__attribute__((noinline)) struct ht_ht *
generate_frequencies (int fl, char *buffer, long buflen)
{
  struct ht_ht *ht;
  char *reader;
  long i;
  char nulled;

  if (fl > buflen)
    return NULL;

  ht = ht_create (hash_table_size (fl, buflen));
  for (i = 0; i < buflen - fl + 1; i++)
    {
      reader = &(buffer[i]);
      nulled = reader[fl];
      reader[fl] = 0x00;
      ht_find_new (ht, reader)->val++;
      reader[fl] = nulled;
    }
  return ht;
}

typedef struct ssorter
{
  char *string;
  int num;
} sorter;

void
write_frequencies (int fl, char *buffer, long buflen)
{
  struct ht_ht *ht;
  long total, i, j, size;
  struct ht_node *nd;
  sorter *s;
  sorter tmp;

  ht = generate_frequencies (fl, buffer, buflen);
  total = 0;
  size = 0;
  for (nd = ht_first (ht); nd != NULL; nd = ht_next (ht))
    {
      total = total + nd->val;
      size++;
    }
  s = mycalloc (size, sizeof (sorter));
  i = 0;
  for (nd = ht_first (ht); nd != NULL; nd = ht_next (ht))
    {
      s[i].string = nd->key;
      s[i++].num = nd->val;
    }
  for (i = 0; i < size - 1; i++)
    for (j = i + 1; j < size; j++)
      if (s[i].num < s[j].num)
	{
	  memcpy (&tmp, &(s[i]), sizeof (sorter));
	  memcpy (&(s[i]), &(s[j]), sizeof (sorter));
	  memcpy (&(s[j]), &tmp, sizeof (sorter));
	}
  /*for (i = 0; i < size; i++)
    printf ("%s %.3f\n", s[i].string, 100 * (float) s[i].num / total);
  printf ("\n");*/
  ht_destroy (ht);
  myfree (s);
}

void
write_count (char *searchFor, char *buffer, long buflen)
{
  struct ht_ht *ht;

  ht = generate_frequencies (strlen (searchFor), buffer, buflen);
  printf ("%d\t%s\n", ht_find_new (ht, searchFor)->val, searchFor);
  ht_destroy (ht);
}

int
main_knucleotide ()
{
  char c;
  char *line, *buffer, *tmp, *x;
  int i, linelen, nothree;
  long buflen, seqlen;
  FILE * f;

  line = mymalloc (256);
  if (!line)
    return 2;
  seqlen = 0;
  nothree = 1;

  f = myfopen("knucleotide-input.txt", "r");
  if (f == NULL) return 2;

  while (nothree && fgets (line, 255, f))
    if (line[0] == '>' && line[1] == 'T' && line[2] == 'H')
      nothree = 0;
  myfree (line);

  buflen = 10240;
  buffer = mymalloc (buflen + 1);
  if (!buffer)
    return 2;
  x = buffer;

  while (fgets (x, 255, f))
    {
      linelen = strlen (x);
      if (linelen)
	{
	  if (x[linelen - 1] == '\n')
	    linelen--;
	  c = x[0];
	  if (c == '>')
	    break;
	  else if (c != ';')
	    {
	      seqlen = seqlen + linelen;
	      if (seqlen + 512 >= buflen)
		{
		  buflen = buflen + 10240;
		  tmp = myrealloc (buffer, buflen + 1);
		  if (tmp == NULL)
		    return 2;
		  buffer = tmp;
		  x = &(buffer[seqlen]);
		}
	      else
		x = &(x[linelen]);
	      x[0] = 0;
	    }
	}
    }
  for (i = 0; i < seqlen; i++)
    buffer[i] = mytoupper (buffer[i]);
  write_frequencies (1, buffer, seqlen);
  write_frequencies (2, buffer, seqlen);
  write_count ("GGT", buffer, seqlen);
  write_count ("GGTA", buffer, seqlen);
  write_count ("GGTATT", buffer, seqlen);
  write_count ("GGTATTTTAATT", buffer, seqlen);
  write_count ("GGTATTTTAATTTATAGT", buffer, seqlen);
  myfree (buffer);
  myfclose (f);
  return 0;
}

/**********
 build & benchmark results

BUILD COMMANDS FOR: knucleotide.gcc

Fri Sep 15 13:56:07 PDT 2006

/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -funroll-loops -march=pentium4  knucleotide.c -o knucleotide.gcc_run

=================================================================
COMMAND LINE (%A is single numeric argument):

knucleotide.gcc_run %A
N=2500

*******/
/* List manipulations */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct list { int hd; struct list * tl; };

struct list * buildlist(int n)
{
  struct list * r;
  if (n < 0) return NULL;
  r = mymalloc(sizeof(struct list));
  r->hd = n;
  r->tl = buildlist(n - 1);
  return r;
}

struct list * reverselist (struct list * l)
{
  struct list * r, * r2;
  for (r = NULL; l != NULL; l = l->tl) {
    r2 = mymalloc(sizeof(struct list));
    r2->hd = l->hd;
    r2->tl = r;
    r = r2;
  }
  return r;
}

struct list * reverse_inplace(struct list * l)
{
  struct list * prev, * next;

  prev = NULL;
  while (l != NULL) {
    next = l->tl;
    l->tl = prev;
    prev = l;
    l = next;
  }
  return prev;
}

int checklist(int n, struct list * l)
{
  int i;
  for (i = 0; i <= n; i++) {
    if (l == NULL) return 0;
    if (l->hd != i) return 0;
    l = l->tl;
  }
  return (l == NULL);
}

int main_lists(int argc, char ** argv)
{
  int n, niter, i;
  struct list * l;

  if (argc >= 2) n = atoi(argv[1]); else n = 1000;
  if (argc >= 3) niter = atoi(argv[1]); else niter = 100000;
  l = buildlist(n);
  if (checklist(n, reverselist(l))) {
    printf("OK\n");
  } else {
    goto BUG;
  }

  for (i = 0; i < 2*niter + 1; i++) {
    l = reverse_inplace(l);
  }
  if (checklist(n, l)) {
    printf("OK\n");
  } else {
    goto BUG;
  }
  
  return 0;
  BUG:
    printf("Bug!\n");
    return 2;
}

/*
 * The Great Computer Language Shootout
 * http://shootout.alioth.debian.org/
 *
 * Written by Dima Dorfman, 2004
 * Compile: gcc -std=c99 -O2 -o nsieve_bits_gcc nsieve_bits.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int bits;
#define	NBITS	(8 * sizeof(bits))

unsigned int
nsieve(unsigned int m)
{
	unsigned int count, i, j;
	bits * a;
        a = mymalloc((m / NBITS) * sizeof(bits));
	memset(a, (1 << 8) - 1, (m / NBITS) * sizeof(bits));
	count = 0;
	for (i = 2; i < m; ++i)
		if (a[i / NBITS] & (1 << i % NBITS)) {
			for (j = i + i; j < m; j += i)
				a[j / NBITS] &= ~(1 << j % NBITS);
			++count;
		}
	return (count);
}

void
test(unsigned int n)
{
	unsigned int count, m;

	m = (1 << n) * 10000;
	count = nsieve(m);
	printf("Primes up to %8u %8u\n", m, count);
}

int
main_nsievebits(int ac, char **av)
{
	unsigned int n;

	n = ac < 2 ? 9 : atoi(av[1]);
	test(n);
	if (n >= 1)
		test(n - 1);
	if (n >= 2)
		test(n - 2);
	//exit(0);
        return 0;
}
/****
 build & benchmark results

BUILD COMMANDS FOR: nsievebits.gcc

Fri Sep 15 06:30:15 PDT 2006

/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -funroll-loops -march=pentium4  nsievebits.c -o nsievebits.gcc_run

=================================================================
COMMAND LINE (%A is single numeric argument):

nsievebits.gcc_run %A


PROGRAM OUTPUT
==============
Primes up to  5120000   356244
Primes up to  2560000   187134
Primes up to  1280000    98610
*****/
// The Computer Language Shootout
// http://shootout.alioth.debian.org/
// Precedent C entry modified by bearophile for speed and size, 31 Jan 2006
// Compile with:  -O3 -s -std=c99 -fomit-frame-pointer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char boolean;


unsigned int nsieve_static(int m) {
    unsigned int count = 0, i, j;
    boolean * flags = (boolean *) mymalloc(m * sizeof(boolean));
    memset(flags, 1, m);

    for (i = 2; i < m; ++i)
        if (flags[i]) {
            ++count;
            for (j = i << 1; j < m; j += i)
                if (flags[j]) flags[j] = 0;
    }

    myfree(flags);
    return count;
}

int main_nsieve(int argc, char * argv[]) {
    int m = argc < 2 ? 9 : atoi(argv[1]);
    int i;
    for (i = 0; i < 3; i++)
    {
        unsigned int count = nsieve_static(10000 << (m-i));
        printf("Primes up to %8u %8u\n", 10000 << (m-i), count);
    }
    return 0;
}

/********
 build & benchmark results

BUILD COMMANDS FOR: nsieve.gcc

Thu Sep 14 20:51:46 PDT 2006

/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -funroll-loops -march=pentium4 -s -std=c99 nsieve.c -o nsieve.gcc_run

=================================================================
COMMAND LINE (%A is single numeric argument):

nsieve.gcc_run %A
N=9

PROGRAM OUTPUT
==============
Primes up to  5120000   356244
Primes up to  2560000   187134
Primes up to  1280000    98610
*******/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void quicksort_orig(int lo, int hi, int * base)
{ 
  int i,j;
  int pivot,temp;
    
  if (lo<hi)
  {
    for (i=lo,j=hi,pivot=base[hi];i<j;)
    {
      while (i<hi && base[i]<=pivot) i++;
      while (j>lo && base[j]>=pivot) j--;
      if (i<j) { temp=base[i]; base[i]=base[j]; base[j]=temp; }
    }
    temp=base[i]; base[i]=base[hi]; base[hi]=temp;
    quicksort_orig(lo,i-1,base);  quicksort_orig(i+1,hi,base);
  }
}

void swap(int* base, int i, int j)
{
  int temp = base[i];
  base[i] = base[j];
  base[j] = temp;
}

void quicksort(int lo, int hi, int* base)
{
  int i,j;
  int pivot;

  if (lo<hi)
  {
    for (i=lo,j=hi,pivot=base[hi];i<j;)
    {
      while (i<hi && base[i]<=pivot) i++;
      while (j>lo && base[j]>=pivot) j--;
      if (i<j) { swap(base, i, j); }
    }
    swap(base, i, hi);
    quicksort(lo,i-1,base);  quicksort(i+1,hi,base);
  }
}

int cmpint(const void * i, const void * j)
{
  int vi = *((int *) i);
  int vj = *((int *) j);
  if (vi == vj) return 0;
  if (vi < vj) return -1;
  return 1;
}

void rand_init(int* a, int* b, int n)
{
  for (int i = 0; i < n; i++) b[i] = a[i] = rand() & 0xFFFF;
}

int equal_array(int* a, int* b, int n)
{
    while (n-- > 0) {
      if (*a++ != *b++) return 1;
    }
    return 0;
}

int main_qsort(int n, int bench)
{
  int i;
  int * a, * b;

  a = mymalloc(n * sizeof(int));
  b = mymalloc(n * sizeof(int));
  rand_init(a, b, n);
  quicksort(0, n - 1, a);
  if (!bench) {
    qsort(b, n, sizeof(int), cmpint);
    if (equal_array(a, b, n)) {
      printf("Bug!\n"); return 2;
    }
    printf("OK\n");
  }
  return 0;
}

int quicksort_char(int lo, int hi, char base[])
{
  int i,j;
  char pivot,temp;
  //base = 0;

  if (lo<hi)
  {
    for (i=lo,j=hi,pivot=base[hi];i<j;)
    {
      while (i<hi && base[i]<=pivot) i++;
      while (j>lo && base[j]>=pivot) j--;
      if (i<j)
      {
        temp=base[i]; base[i]=base[j]; base[j]=temp;
      }
    }
    temp=base[i]; base[i]=base[hi]; base[hi]=temp;
  }
  return 0;
}

/* SHA-1 cryptographic hash function */
/* Ref: Handbook of Applied Cryptography, section 9.4.2, algorithm 9.53 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

struct SHA1Context {
  u32 state[5];
  u32 length[2];
  int numbytes;
  unsigned char buffer[64];
};

#define rol1(x) (((x) << 1) | ((x) >> 31))
#define rol5(x) (((x) << 5) | ((x) >> 27))
#define rol30(x) (((x) << 30) | ((x) >> 2))

int arch_big_endian;

void SHA1_copy_and_swap(void * src, void * dst, int numwords)
{
  if (arch_big_endian) {
    memcpy(dst, src, numwords * sizeof(u32));
  } else {
    unsigned char * s, * d;
    unsigned char a, b;
    for (s = src, d = dst; numwords > 0; s += 4, d += 4, numwords--) {
      a = s[0];
      b = s[1];
      d[0] = s[3];
      d[1] = s[2];
      d[2] = b;
      d[3] = a;
    }
  }
}

#define F(x,y,z) ( z ^ (x & (y ^ z) ) )
#define G(x,y,z) ( (x & y) | (z & (x | y) ) )
#define H(x,y,z) ( x ^ y ^ z )

#define Y1 0x5A827999U
#define Y2 0x6ED9EBA1U
#define Y3 0x8F1BBCDCU
#define Y4 0xCA62C1D6U


void SHA1_rounds(struct SHA1Context * ctx , u32 *data)
{
  int i;
  u32 a, b, c, d, e, t;
  /* Expand into 80 integers */
  for (i = 16; i < 80; i++) {
    t = data[i-3] ^ data[i-8] ^ data[i-14] ^ data[i-16];
    data[i] = rol1(t);
  }

  /* Initialize working variables */
  a = ctx->state[0];
  b = ctx->state[1];
  c = ctx->state[2];
  d = ctx->state[3];
  e = ctx->state[4];

  /* Perform rounds */
  for (i = 0; i < 20; i++) {
    t = F(b, c, d) + Y1 + rol5(a) + e + data[i];
    e = d; d = c; c = rol30(b); b = a; a = t;
  }
  for (/*nothing*/; i < 40; i++) {
    t = H(b, c, d) + Y2 + rol5(a) + e + data[i];
    e = d; d = c; c = rol30(b); b = a; a = t;
  }
  for (/*nothing*/; i < 60; i++) {
    t = G(b, c, d) + Y3 + rol5(a) + e + data[i];
    e = d; d = c; c = rol30(b); b = a; a = t;
  }
  for (/*nothing*/; i < 80; i++) {
    t = H(b, c, d) + Y4 + rol5(a) + e + data[i];
    e = d; d = c; c = rol30(b); b = a; a = t;
  }

  /* Update chaining values */
  ctx->state[0] += a;
  ctx->state[1] += b;
  ctx->state[2] += c;
  ctx->state[3] += d;
  ctx->state[4] += e;
}

void SHA1_transform(struct SHA1Context * ctx)
{
  u32 *data = mymalloc(sizeof(u32) * 80);
  int numwords = 16;
  SHA1_copy_and_swap(ctx->buffer, data, numwords);
  SHA1_rounds(ctx, data);
}

void SHA1_init(struct SHA1Context * ctx)
{
  ctx->state[0] = 0x67452301U;
  ctx->state[1] = 0xEFCDAB89U;
  ctx->state[2] = 0x98BADCFEU;
  ctx->state[3] = 0x10325476U;
  ctx->state[4] = 0xC3D2E1F0U;
  ctx->numbytes = 0;
  ctx->length[0] = 0;
  ctx->length[1] = 0;
}

int process_left_data(struct SHA1Context * ctx, unsigned char * data, unsigned long len)
{
  u32 t;

  /* Update length */
  t = ctx->length[1];
  if ((ctx->length[1] = t + (u32) (len << 3)) < t)
    ctx->length[0]++;    /* carry from low 32 bits to high 32 bits */
  ctx->length[0] += (u32) (len >> 29);

  /* If data was left in buffer, pad it with fresh data and munge block */
  if (ctx->numbytes != 0) {
    t = 64 - ctx->numbytes;
    if (len < t) {
      memcpy(ctx->buffer + ctx->numbytes, data, len);
      ctx->numbytes += len;
      return 1;
    }
    memcpy(ctx->buffer + ctx->numbytes, data, t);
    SHA1_transform(ctx);
    data += t;
    len -= t;
  }
  return 0;
}

void SHA1_add_data(struct SHA1Context * ctx, unsigned char * data,
                   unsigned long len)
{

  if(process_left_data(ctx, data, len))
    return;

  /* Munge data in 64-byte chunks */
  while (len >= 64) {
    memcpy(ctx->buffer, data, 64);
    SHA1_transform(ctx);
    data += 64;
    len -= 64;
  }
  /* Save remaining data */
  memcpy(ctx->buffer, data, len);
  ctx->numbytes = len;
}

void SHA1_finish(struct SHA1Context * ctx, unsigned char output[20])
{
  int i = ctx->numbytes;

  /* Set first char of padding to 0x80. There is always room. */
  ctx->buffer[i++] = 0x80;
  /* If we do not have room for the length (8 bytes), pad to 64 bytes
     with zeroes and munge the data block */
  if (i > 56) {
    memset(ctx->buffer + i, 0, 64 - i);
    SHA1_transform(ctx);
    i = 0;
  }
  /* Pad to byte 56 with zeroes */
  memset(ctx->buffer + i, 0, 56 - i);
  /* Add length in big-endian */
  SHA1_copy_and_swap(ctx->length, ctx->buffer + 56, 2);
  /* Munge the final block */
  SHA1_transform(ctx);
  /* Final hash value is in ctx->state modulo big-endian conversion */
  SHA1_copy_and_swap(ctx->state, output, 5);
}

/* Test harness */

void do_test(unsigned char * txt, unsigned char * expected_output)
{
  struct SHA1Context* ctx;
  unsigned char* output;
  int ok;

  ctx = mymalloc(sizeof(struct SHA1Context));
  output = mymalloc(sizeof(unsigned char)*20);
  SHA1_init(ctx);
  SHA1_add_data(ctx, txt, strlen((char *) txt));
  SHA1_finish(ctx, output);
  ok = memcmp(output, expected_output, 20) == 0;
  printf("Test `%s': %s\n", 
         (char *) txt, (ok ? "passed" : "FAILED"));
}

/*  Test vectors:
 *
 *  "abc"
 *  A999 3E36 4706 816A BA3E  2571 7850 C26C 9CD0 D89D
 *
 *  "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
 *  8498 3E44 1C3B D26E BAAE  4AA1 F951 29E5 E546 70F1
 */

unsigned char test_input_1[] = "abc";

unsigned char test_output_1[20] =
{ 0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E ,
  0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D };

unsigned char test_input_2[] = 
  "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

unsigned char test_output_2[20] =
{ 0x84, 0x98, 0x3E, 0x44, 0x1C, 0x3B, 0xD2, 0x6E, 0xBA, 0xAE,
  0x4A, 0xA1, 0xF9, 0x51, 0x29, 0xE5, 0xE5, 0x46, 0x70, 0xF1 };


void do_bench(int nblocks)
{
  struct SHA1Context ctx;
  unsigned char output[20];
  unsigned char data[64];
  int i;

  for (i = 0; i < 64; i++) data[i] = i;
  SHA1_init(&ctx);
  for (; nblocks > 0; nblocks--) 
    SHA1_add_data(&ctx, data, 64);
  SHA1_finish(&ctx, output);
}

int main_sha1(int argc, char ** argv)
{
  /* Determine endianness */
  union { int i; unsigned char b[4]; } u;
  u.i = 0x12345678;
  switch (u.b[0]) {
  case 0x12: arch_big_endian = 1; break;
  case 0x78: arch_big_endian = 0; break;
  default: printf("Cannot determine endianness\n"); return 2;
  }
  do_test(test_input_1, test_output_1);
  do_test(test_input_2, test_output_2);
  //do_bench(1000000);
  return 0;
}

int ddec(int x, int n)
{
  int i, k = 0;
  int y = x;
  for (i=0; i!=n; ++i)
  {
    y += k*5;
    k += 1;
    if (i >= 5)
      k += 3;
  }
  return y;
}

int nested_loops2(int n)
{
  int ret = 0;
  int i, j;
  for (i=0; i < n; ++i)
  {
    for (j=i; j < n; ++j)
      ++ret;
  }
  return ret;
}

int nested_loops2_1(int n, int m)
{
  int ret = 0;
  int i, j;
  for (i=0; i < n; ++i)
  {
    for (j=i; j < m; ++j)
      ++ret;
  }
  return ret;
}

int nested_loops3(int n, int m, char* a, char* b)
{
  int i, j;
  for (i=0; i < n; ++i)
  {
    for (j=0; j < m; ++j)
      a[i*m+j] = 0;

    b[i] = 0;
  }
  return 0;
}

int peeling_dst(int n)
{
  if(n < 2)
    return 0;

  int i = 0;
  i++;
  i++;
  while(i < n)
  {
    i++;
  }
  return i;
}

int peeling_src(int n)
{
  if(n < 2)
    return 0;

  int i = 0;
  while(i < n)
  {
    i++;
  }
  return i;
}

int splitting_src(int n)
{
  if(n > 1000 || n <= 0)
    return 0;

  int i;
  for(i = 0; i < n; ++i)
  {
  }
  for(; i < 2*n; ++i)
  {
  }
  return i;
}

int splitting_dst(int n)
{
  if(n > 1000 || n <= 0)
    return 0;

  int i;
  for(i = 0; i < 2*n; ++i)
  {
  }
  return i;
}

int tiling_src(int n)
{
  if(n < 2)
    return 0;

  int i = 0;
  while(i < 20*n)
  {
    int j = i;
    while(j < i+4)
    {
      ++j;
    }
    i += 4;
  }
  return i;
}

int tiling_dst(int n)
{
  if(n < 2)
    return 0;

  int i = 0;
  while(i < 20*n)
  {
    ++i;
  }
  return i;
}

int soft_pipe_src_peeled(int n, char* a, char* b, char* c)
{
  if(n < 2)
    return 0;

  int i = 0;
  a[i] += 1;
  b[i] += a[i];
  c[i] += b[i];
  i++;
  a[i] += 1;
  b[i] += a[i];
  c[i] += b[i];
  i++;
  while(i < n)
  {
    a[i] += 1;
    b[i] += a[i];
    c[i] += b[i];
    i++;
  }
  return i;
}

int soft_pipe_src(int n, char* a, char* b, char* c)
{
  if(n < 2)
    return 0;

  int i = 0;
  while(i < n)
  {
    a[i] += 1;
    b[i] += a[i];
    c[i] += b[i];
    i++;
  }
  return i;
}

int soft_pipe_dst(int n, char* a, char* b, char* c)
{
  if(n < 2)
    return 0;

  a[0] += 1;
  b[0] += a[0];
  a[1] += 1;
  int i = 0;
  while(i < n - 2)
  {
    a[i+2] += 1;
    b[i+1] += a[i+1];
    c[i] += b[i];
    i++;
  }
  c[i] += b[i];
  b[i+1] += a[i+1];
  c[i+1] += b[i+1];
  return i+2;
}

int int1(int a)
{
  return 2 * a;
}

int int2_add(int a, int b)
{
  return 2 * (a + b);
}

int int3_add(int a, int b, int c)
{
  return 2 * (a + b + c);
}

int int4_add(int a, int b, int c, int d)
{
  return 2 * (a + b + c + d);
}

int int5_add(int a, int b, int c, int d, int e)
{
  return 2 * (a + b + c + d + e);
}

int int6_add(int a, int b, int c, int d, int e, int f)
{
  return 2 * (a + b + c + d + e + f);
}

int int7_add(int a, int b, int c, int d, int e, int f, int g)
{
  return 2 * (a + b + c + d + e + f + g);
}

int int8_add(int a, int b, int c, int d, int e, int f, int g, int h)
{
  return 2 * (a + b + c + d + e + f + g + h);
}

int sum_positive_g[144];
int sum_positive_sum = 0;
int const sum_positive_const = 123;

void sum_positive_globals(int n) {
  int *ptr = sum_positive_g;
  int i;
  for (i = 0; i < n; i++, ptr++) {
    if (*ptr > 0) {
      sum_positive_sum = sum_positive_sum + sum_positive_const * (*ptr);
    }
  }
}

void sum_positive_arg(int *a, int n) {
  int *ptr = a;
  int i;
  for (i = 0; i < n; i++, ptr++) {
    if (*ptr > 0) {
      sum_positive_sum = sum_positive_sum + sum_positive_const * (*ptr);
    }
  }
}

void sum_all_globals(int n) {
  int *ptr = sum_positive_g;
  int i;
  for (i = 0; i < n; i++, ptr++) {
    sum_positive_sum = sum_positive_sum + sum_positive_const * (*ptr);
  }
}

void memcpy_2D(int row, int col, int*restrict src, int*restrict dst) {
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      dst[i*col+j] = src[i*col+j];
    }
  }
}

void memcpy_v0(int size, int*restrict src, int*restrict dst)
{
  int i;
  for (i = 0; i < size; i++) {
    dst[i] = src[i];
  }
}

void memcpy_v0_neo(int i, int size, int*restrict src, int*restrict dst)
{
  for (; i < size; i++) {
    dst[i] = src[i];
  }
}

#define N 32
#define M 32

struct T {
  char s[273];
  int i;
} S[N];
void memset_v1(int row, int c)
{
  int i, j;
  for (i = 0; i < row; i++) {
    S[i].i = c;
  }
}
struct T S2[N][M];
void memset2D_v1(int row, int col, int c)
{
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; ++j) {
      S2[i][j].i = c;
    }
  }
}

#define N 32
#define M 32

int gsrc[N][M];
void memset_v0(int row, int col, int c)
{
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; ++j) {
      gsrc[i][j] = c;
    }
  }
}

int g3[N][M][N];
void memset3D_v0(int row, int col, int ind, int c)
{
  int i, j, k;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; ++j) {
      for (k = 0; k < ind; ++k) {
        g3[i][j][k] = c;
      }
    }
  }
}

int gdst[N][M];
void memcpy_v1(int row, int col)
{
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; ++j) {
      gdst[i][j] = gsrc[i][j];
    }
  }
}
/*
int int16_add(int a, int b, int c, int d, int e, int f, int g, int h,
    int i, int j, int k, int l, int m, int n, int o, int p)
{
  return 2 * (a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p);
}*/
/* comment out, doesn work on ccomp
int
aliasing_example(int n)
{
  int *ptr[n], *ptr2[n];
  int a, i, j;

  for (i = 0; i < n; i++) {
    ptr[i] = malloc(1);
    ptr2[i] = malloc(1);
  }
  a = 1;
  ptr[37] = &a;

  for (i = 0; i < 1000; i++) {
    int *tmp;
    printf("hello\n");
    tmp = ptr2[(i*323-12)%n];
    if (tmp) {
      *tmp = i;
    }
    ptr2[i % n]++;
    j = a;
  }
  printf("j = %d\n", j);
  return j;
}
*/
/*
struct big_struct {
  long a, b, c, d, e, f;
};

void
big_struct_arg_function(struct big_struct ret, int n)
{
  ret.a = n;
  ret.b = n;
  ret.c = n;
  ret.d = n;
  ret.e = n;
  ret.f = n;
}

struct big_struct
big_struct_return_function(int n)
{
  struct big_struct ret;
  big_struct_arg_function(ret, n);
  big_struct_arg_function(ret, ret.e);
  return ret;
}
*/

#define LOOP_N 10000

int main_ddec()
{
  int ret = 0;
  for(int i = 0; i < LOOP_N; ++i)
    ret += ddec(i, i);
  return ret;
}

size_t address_taken_local_var_callee(char **a, char **b, char **c, char **d);

size_t address_taken_local_var_caller(char **a)
{
  char *b = *a;
  char **c = &b;
  char **d = &b;
  if (sum_positive_sum) {
    d = a;
  }
  return sum_positive_sum + address_taken_local_var_callee(&b, a, c, d);
}

int a[5];
int b[100];
void foo(int* ptr) {
  int l[20];
  if (!ptr) {
    ptr = l;
  }
  while (myrand() > 100) {
    if (myrand() < 2) {
      ptr = b;
    } else {
      ptr = a;
    }
  }
  *ptr = 1;
  b[0] = 2;
  *a = 9;
  l[0] = a[1];
}

int main_foo() {
  int foo_;
  foo(&foo_);
  return foo_;
}

size_t one_function_call(int x)
{
  sum_positive_sum = x + 1;
  if (x > 0) {
    x = ddec(10, x);
  } else {
    x = 10;
  }
  return sum_positive_sum - x;
}

void display_ratio(num, den, file)
    long num;
    long den;
    FILE *file;
{
    long ratio;  /* 1000 times the compression ratio */

    if (den == 0) {
        ratio = 0; /* no compression */
    } else if (den < 2147483L) { /* (2**31 -1)/1000 */
        ratio = 1000L*num/den;
    } else {
        ratio = num/(den/1000L);
    }
    if (ratio < 0) {
        putc('-', file);
        ratio = -ratio;
    } else {
        putc(' ', file);
    }
    fprintf(file, "%2ld.%1ld%%", ratio / 10L, ratio % 10L);
}

//long long div_i64(long long a, long long b)
//{
//  return a/b;
//}
//
//unsigned long long div_u64(unsigned long long a, unsigned long long b)
//{
//  return a/b;
//}

char maplocals_example1(void)
{
  int local0 = 0, local1 = 0;
  int *ptr = &local0;
  int local3 = myrand();
  while (!(local3 & 0x2)) {
    local3 = local3 * 1234567;
    if (local3 & 0x1) {
      ptr = &local1;
    } else {
      ptr = &local0;
    }
  }
  *ptr = 1;
  return local0;
}

int maplocals_example2()
{
  int local0 = 0;
  int *ptr = mymalloc(4);
  if (!ptr) {
    ptr = &local0;
  }
  int local3 = myrand();
  while (!(*ptr & 0x2)) {
    *ptr += local3;
    local3 = myrand();
  }
  return local0;
}

int maplocals_example3(int n)
{
  int a[42];
  a[0] = 123;
  mymemset(a, sizeof a, 0);
  int i;
  for (i = 0; i < n; i++) {
    int j = myrand();
    a[j]++;
  }
  return a[0];
}

char maplocals_example4(char *ptr, int i, int b)
{
  char local0 = 121, local1[42], local2 = 77;
  local1[0] = 123;
  if (b != 0) {
    ptr = &local1;
  }
  local2 = my_char_inc(ptr);
  return local0 + local1[0] + local2;
}

void maplocals_example5(void)
{
#define N 42
  char local0[N];
  local0[0] = 123;
  char *ptr = local0;
  while (ptr <= &local0[N]) {
    *ptr = myrand_char();
    ptr++;
  }
  int i = myrand();
  myprint_int((int)local0[i]);
}



int maplocals_example12(int *ptr)
{
  int local0 = 0, local1 = 0;
  if (!ptr) {
    ptr = &local0;
  }
  int local3 = myrand();
  while (!(*ptr & 0x2)) {
    *ptr += local3;
    local3 = myrand();
  }
  return local0;
}

char maplocals_example11(void)
{
  int local0 = 0, local1 = 1;
  int *ptr = &local0;
  int local3 = myrand();
  while (!(local3 & 0x2)) {
    local3 = local3 * 1234567;
    if (local3 & 0x1) {
      ptr = &local1;
    } else {
      ptr = &local0;
    }
  }
  return *ptr;
}
/** Added as linear guessing test cases **/

int sum_new;
__attribute__((noinline)) int init_new(int n)
{
  int i;
  sum_new = 1;
  for( i=0 ; i<10 ; i++ )  sum_new += sum_new;	
  return sum_new;
}

char array_2D[5][5] = {{1, 2, 3, 4, 5},
                      {6, 7, 8, 9, 10},
                      {11, 12, 13, 14, 15},
                      {16, 17, 18, 19, 20},
                      {21, 22, 23, 24, 25}
		     };  

__attribute__((noinline)) int add_2D_arr(int row, int col)
{
  int i,j;
  for(i=0; i< row; i++)
  {
    for(j=0; j< col; j++)
      array_2D[i][j] = array_2D[i][j]*2;
  }
  return 1;
}

#define N 32
#define M 32

/* will fail with sketching because the guess `symbol + i*5` will have to be related to x86 reg (arity = 3) which is not possible with sketching */
void init_array (int n, int m, int path[N][M])
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      path[i][j] = ((i+1)*(j+1))/* / n*/;
}

void init_array_ptr (int n, int m, int** path)
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++) {
      path[i][j] = ((i+1)*(j+1))/* / n*/;
    }
}

/* is failing with sketching because the guess `symbol + i*5` will have to be related to x86 reg (arity = 3) which is not possible with sketching */
__attribute__((noinline)) int init_2D_arr(int row, int col)
{
  int i,j;
  for(i=0; i< row; i++)
  {
    for(j=0; j< col; j++)
      array_2D[i][j] = i+j;
  }
  return 1;
}

int g[144]; int avg=0; 
__attribute__((noinline)) void array_average( ) 
{
int *ptr = g; int sum =0;
for(int i = 0; i < 144; i++,ptr++)
  sum = sum + *ptr;

avg = sum/144; 
}

int x,y;
__attribute__((noinline)) void ddai(int n)
{
x=0; y=0; 
int i=0; 
while (i < n)
{ 
  y = y+1; 
  x = x+y; 
  i++;
}
}

int lerner1a(int x, int n)
{
  int i, k = 0;
  for (i=0; i!=n; ++i)
  { 
    x += k*5; 
    k += 1;
    if (i >= 5) 
      k += 3;
  } 
  return x; 
}

int lerner1b(int x, int n)
{
  int i, k = 0;
  for (i=0; i!=n; ++i)
  { 
    x += k; 
    k += 5;
    if (i >= 5) 
      k += 15;
  } 
  return x; 
}

int sum_ler_3b3c;
int lerner3b( )
{
  int i,j;
  int sum =0;
  for (i = 0; i < 10; i++) 
  {
    for (j = 0; j < 10; j++)
    {
       sum++;
       sum_ler_3b3c += sum;
    }
  }
}

int lerner3c( )
{
  int i,j;
  for (i = 0; i < 10; i++) 
  {
    for (j = 0; j < 10; j++)
    {
       sum_ler_3b3c += i*10 + j;
    }
  }
}

/*__attribute__((noinline)) int div_2pow_n(int x, int n)
{
  return (x/pow(2,n));
}*/
int main()
{
  printf("start tests\n");
  char* a = (char*)mymalloc(100);
  char* b = (char*)mymalloc(100);
  size_t aa = address_taken_local_var_caller(&a);
  sum_positive_globals(100);
  sum_positive_arg(sum_positive_g, 144);
  sum_all_globals(100);
  int ret =  
        main_ddec() +
        main_chomp() + main_fannkuch(atoi("0"), (char **)atoi("0")) + 
        main_knucleotide() + 
        main_lists(atoi("0"), (char **)atoi("0")) + 
        main_nsievebits(atoi("0"), (char **)atoi("0")) + 
        main_nsieve(atoi("0"), (char **)atoi("0")) + 
        //main_qsort(atoi("0"), (char **)atoi("0")) + 
        main_qsort(10000, 0) + 
        main_sha1(atoi("0"), (char **)atoi("0")) + 
        nested_loops2_1(atoi("100"), atoi("100")) + nested_loops2(atoi("100")) + 
        nested_loops3(atoi("100"), atoi("100"), a, b) + 
        quicksort_char(atoi("0"), atoi("100"), a) +
        peeling_src(atoi("1")) +
        peeling_dst(atoi("0")) +
        splitting_src(atoi("1")) +
        splitting_dst(atoi("0")) +
        tiling_src(atoi("1")) +
        tiling_dst(atoi("0")) +
        int1(2) + int2_add(3,4) + int3_add(3, 4, 5) + int4_add(3, 4, 5, 6) +
        int5_add(3, 4, 5, 6, 7) + int6_add(3, 4, 5, 6, 7, 8) +
        int7_add(3, 4, 5, 6, 7, 8, 9) + int8_add(3, 4, 5, 6, 7, 8, 9, 10) +
        main_foo() +
        sum_positive_sum + 
        add_2D_arr(5,5)
        //int16_add(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
        /*aliasing_example(100) +
        big_struct_return_function(100).a*/;
  printf("finished\n");
  return ret;
}
__attribute__((noinline)) int sum_n(int n)
{
  int i;
  for (i = 0; i < n; ++i);
  return i;
}
