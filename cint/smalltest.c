#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdbool.h>

//const char interp_section[] __attribute__((section(".interp"))) = "/path/to/dynamic/linker";

typedef unsigned char boolean;

unsigned int nsievebits(int m) {
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
        unsigned int count = nsievebits(10000 << (m-i));
        printf("Primes up to %8u %8u\n", 10000 << (m-i), count);
    }
    return 0;
}



int main()
{
  printf("start tests\n");
  //sum_positive_globals(100);
  printf("finished\n");
  return 0;
}
