/*****************************************
  Test suite for vectorizing compilers
       Semantic alignment paper
*****************************************/
#include <stdlib.h>

void flip_array(int* array, unsigned len)
{
  for(unsigned i=0; i< len; i++)
  	array[i] ^= 0xFFFFFFFF;
}

void flip_array_vec1(int* array, unsigned len)
{
	if(len%2 == 1)
	{
  	*array ^= 0xFFFFFFFF;
  	array++;
  	len--;
	}
	while(len)
	{
		*((long long int *) array) ^= 0xFFFFFFFFFFFFFFFF;
		array += 2;
		len -= 2;
	}
}

void flip_array_unroll(int* array, unsigned len)
{
	if(len%2 == 1)
	{
  	*array ^= 0xFFFFFFFF;
  	array++;
  	len--;
	}
  for(unsigned i=0; i< len; i = i+2)
	{
  	array[i] ^= 0xFFFFFFFF;
  	array[i+1] ^= 0xFFFFFFFF;
	}
}


/***************************/


// Cleaned version of the TSC benchmarks for verification.
// Cleaning included:
//   (1) removing benchmarking code, including any outer loops
//   (2) removing return call
//   (3) replacing floats with "TYPE" variable
//   (4) parameterizing length
//
// Criteria for selection included:
//   (i) Vectorizes with either GCC or CLANG
//      - compiled with -msse4.2 -O3
//      - gcc 4.9.2
//      - clang 3.4
//   (ii) Single loop
//   (iii) No leaf functions


#define LEN 128
#define LEN1 1024
#define LEN2 16

#define TYPE int

// we want to be sure that the compilers but the data in the
// same memory locations so that they actually output equivalent
// code!
//TYPE a[LEN] __attribute__((section ("SEGMENT_A")));
//TYPE b[LEN] __attribute__((section ("SEGMENT_B")));
//TYPE c[LEN] __attribute__((section ("SEGMENT_C")));
//TYPE d[LEN] __attribute__((section ("SEGMENT_D")));
//TYPE e[LEN] __attribute__((section ("SEGMENT_E")));
//TYPE aa[LEN2][LEN2] __attribute__((section ("SEGMENT_F")));

/* Issues -- (count*something) will never overflow
 * add by a constant, then the constant vector will be stored in rodata 
 */

TYPE a[LEN];
TYPE b[LEN];
TYPE c[LEN];
TYPE d[LEN];
TYPE e[LEN];
TYPE aa[LEN2][LEN2];
TYPE val;
TYPE val1;
TYPE a1[LEN1];
TYPE b1[LEN1];

void testing() {
  a[0] = 0;
  b[0] = 0;
  c[0] = 0;
  d[0] = 0;
  e[0] = 0;
}

TYPE sum1d(int count) {
  TYPE sum = 0;
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    sum += a[i];
  } 
 }
  return sum;
}

TYPE s000(int count) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    a[i] = b[i] + val;
  } 
 }
  return 0;
}


TYPE s112(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = count*8-1; i >= 1; i--) {
    a[i] = a[i-1] + b[i];
  }
  }
  return 0;
}


TYPE s1112(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = count*8-1; i >= 0; i--) {
    a[i] = b[i] + val;
  }
  }
  return 0;
}


TYPE s121(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = 0; i < count*8-1; i++) {
    a[i] = a[i+1] + b[i];
  }
  }
  return 0;
}

TYPE s122(int count) {
  int k = 0;
	if(count >0 && count < 32768)
	{
  for (int i = 1; i < count*8; i++) {
    k++;
    a[i] += b[count*8-k];
  }
  }
  return 0;
}

TYPE s127(int count) {
  int j = -1;
	if(count >0 && count < 32768)
	{
  for (int i = 0; i < count*4-1; i++) {
    j++;
    a[j] = b[i] + c[i] * d[i];
    j++;
    a[j] = b[i] + d[i] * e[i];
  }
  }
  return 0;
}

TYPE s162(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = 0; i < count*8-1; i++) {
    a[i] = a[i + 1] + b[i] * c[i];
  }
  }
  return 0;
}

TYPE s173(int count) {
  int k = count*4;
	if(count >0 && count < 32768)
	{
  for (int i = 0; i < k; i++) {
    a[i+k] = a[i] + b[i];
  }
  }
  return 0;
}

TYPE s1221(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = 4; i < count*8; i++) {
    a[i] = a[i-4] + b[i];
  }
  }
  return 0;
}

TYPE s243(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = 0; i < count*8-1; i++) {
    a[i] = b[i] + c[i  ] * d[i];
    b[i] = a[i] + d[i  ] * e[i];
    a[i] = b[i] + a[i+1] * d[i];
  }
  }
  return 0;
}

TYPE s2244(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = 0; i < count*8-1; i++) {
  	a[i+1] = b[i] + e[i];
		a[i] = b[i] + c[i];
  }
  }
  return 0;
}

TYPE s251(int count) {
  TYPE s;
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
   	s = b[i] + c[i] * d[i];
		a[i] = s * s;
  } 
 }
  return 0;
}

TYPE s1251(int count) {
  TYPE s;
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    s = b[i]+c[i];
    b[i] = a[i]+d[i];
    a[i] = s*e[i];
  } 
 }
  return 0;
}

TYPE s3251(int count) {
  TYPE s;
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8-1; i++) {
		a[i+1] = b[i]+c[i];
		b[i]   = c[i]*e[i];
		d[i]   = a[i]*e[i];
  } 
 }
  return 0;
}

TYPE s1281(int count) {
  TYPE x;
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    x = b[i]*c[i]+a[i]*d[i]+e[i];
    a[i] = x-(TYPE)1;
    b[i] = x;
  } 
 }
  return 0;
}

TYPE s351(int count) {
	TYPE alpha = c[0];
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8-5; i+=5) {
    a1[i] += alpha * b1[i];
    a1[i + 1] += alpha * b1[i + 1];
    a1[i + 2] += alpha * b1[i + 2];
    a1[i + 3] += alpha * b1[i + 3];
    a1[i + 4] += alpha * b1[i + 4];
  } 
 }
  return 0;
}

TYPE s1351(int count) {
  TYPE* __restrict__ A = a;
  TYPE* __restrict__ B = b;
  TYPE* __restrict__ C = c;
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    *A = *B + *C;
    A++;
    B++;
    C++;
  } 
 }
  return 0;
}

TYPE s452(int count) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
	  a[i] = b[i] + c[i] * val;
  } 
 }
  return 0;
}

TYPE vpv(int count) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    a[i] += b[i];
  } 
 }
  return 0;
}

TYPE vtv(int count) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    a[i] *= b[i];
  } 
 }
  return 0;
}

TYPE vpvtv(int count) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    a[i] += b[i]*c[i];
  } 
 }
  return 0;
}

TYPE vpvts(int count, TYPE k) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    a[i] += b[i]*k;
  } 
 }
  return 0;
}

TYPE vpvpv(int count) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    a[i] += b[i]+c[i];
  } 
 }
  return 0;
}

TYPE vtvtv(int count) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    a[i] *= b[i]*c[i];
  } 
 }
  return 0;
}

TYPE vdotr(int count) {
  TYPE sum = 0;
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    sum += a[i]*b[i];
  } 
 }
  return sum;
}


TYPE s453(int count) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    a[i] = val1 * b[i];
    val1 += val;
  } 
 }
  return 0;
}

// vectorizes with gcc 
TYPE s176(int count) {
  int m = count;
  if(count>0 && count<32768) {
 for (int j = 0; j < m; j++) {
    for (int i = 0; i < m; i++) {
      a[i] += b[i+m-j-1] * c[j];
    }
  }
 	}
  return 0;
}

/*
//NP
TYPE s111(int count) {
  if(count>0 && count<32768) {
 for (int i = 1; i < count*8; i+=2) {
    a[i] = a[i-1] + b[i];
  } 
 }
  return 0;
}

//NP
TYPE s1111(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = 0; i < count*4; i++) {
	  a[2*i] = c[i] * b[i] + d[i] * b[i] + c[i] * c[i] + d[i] * b[i] + d[i] * c[i];
  }
  }
  return 0;
}
//NP
TYPE stacktest(int count) {
   if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    a[i] = b[i] + val;
  } 
 }
  return 0;
}


// doesn't vectorize
//NP
TYPE s2710(int count, int x) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    if (a[i] > b[i]) {
      a[i] += b[i] * d[i];
      if (count*8 > 10) {
        c[i] += d[i] * d[i];
      } else {
        c[i] = d[i] * e[i] + 1;
      }
    } else {
      b[i] = a[i] + e[i] * e[i];
      if (x > 0) {
        c[i] = a[i] + d[i] * d[i];
      } else {
        c[i] += e[i] * e[i];
      }
    } 
 }
  }
  return 0;
}

//NP
TYPE s115(int count) {
	if(count >0 && count < 32768)
	{
  for (int j = 0; j < count; j++) {
    for (int i = j+1; i < count; i++) {
      a[i] -= aa[j][i] * a[j];
    }
  }
  }
  return 0;
}

//NP
TYPE s116(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = 0; i < count*8-5; i+=5) {
    a[i] = a[i + 1] * a[i];
    a[i + 1] = a[i + 2] * a[i + 1];
    a[i + 2] = a[i + 3] * a[i + 2];
    a[i + 3] = a[i + 4] * a[i + 3];
    a[i + 4] = a[i + 5] * a[i + 4];
  }
  }
  return 0;
}
//NP
TYPE s175(int count) {
	if(count >0 && count < 32768)
	{
  for (int i = 0; i < count*8-1; i ++) {
    a[i] = a[i + 1] + b[i];
  }
  }
  return 0;
}

//NP
TYPE s315(int count) {
  TYPE x;
  int index;

  x = a[0];
  index = 0;
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    if (a[i] > x) {
      x = a[i];
      index = i;
    }
  } 
 }

  return x + (TYPE)index;
}

//NP
TYPE s318(int count) {
  int k = 0;
  int index = 0;
  TYPE max = abs(a[0]);
  k++;

  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    if (abs(a[k]) <= max) {
      goto L5;
    }
    index = i;
    max = abs(a[k]);
L5:
		k++;
  } 
 }

  return max+index;
}

//NP
TYPE vif(int count) {
  if(count>0 && count<32768) {
 for (int i = 0; i < count*8; i++) {
    if(b[i] > 0)
      a[i] = b[i];
  }
 	}
  return 0;
}
*/


int main()
{
  return 0;
}
