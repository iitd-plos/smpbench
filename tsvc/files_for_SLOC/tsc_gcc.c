
/*
 * This is an executable test containing a number of loops to measure
 * the performance of a compiler. Arrays' length is LEN by default
 * and if you want a different array length, you should replace every 
 * LEN by your desired number which must be a multiple of 40. If you 
 * want to increase the number of loop calls to have a longer run time
 * you have to manipulate the constant value ntimes. There is a dummy
 * function called in each loop to make all computations appear required.
 * The time to execute this function is included in the time measurement 
 * for the output but it is neglectable.
 *
 *  The output includes three columns:
 *	Loop:		The name of the loop
 *	Time(Sec): 	The time in seconds to run the loop
 *	Checksum:	The checksum calculated when the test has run
 *
 * In this version of the codelets arrays are static type.
 *
 * All functions/loops are taken from "TEST SUITE FOR VECTORIZING COMPILERS"
 * by David Callahan, Jack Dongarra and David Levine except those whose 
 * functions' name have 4 digits.
 */


#define LEN 32000
#define LEN1 3200
#define LEN2 256

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <sys/param.h>
#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "tsvc/tsvc_helper.h"

//#include <builtins.h>


#define TYPE int

#define lll LEN


TYPE val = 1;
__attribute__ ((aligned(16))) TYPE X[lll],Y[lll],Z[lll],U[lll],V[lll];


//float* __restrict__ array;
TYPE array[LEN2*LEN2] __attribute__((aligned(16)));

TYPE x[LEN] __attribute__((aligned(16)));
TYPE temp;
int temp_int;


__attribute__((aligned(16))) TYPE a[LEN],b[LEN],c[LEN],d[LEN],e[LEN],
                                   aa[LEN2][LEN2],bb[LEN2][LEN2],cc[LEN2][LEN2],tt[LEN2][LEN2];


int indx[LEN] __attribute__((aligned(16)));


TYPE* __restrict__ xx;
TYPE* yy;
TYPE arr[LEN];


TYPE sum1d(){
	TYPE ret = 0.;
	for (int i = 0; i < LEN; i++)
		ret += arr[i];
	return ret;
}


int s000()
{

//	linear dependence testing
//	no dependence - vectorizable

		for (int i = 0; i < lll; i++) {
			X[i] = Y[i] + val;
		}
	return 0;
}


int s112()
{

//	linear dependence testing
//	loop reversal

		for (int i = LEN - 2; i >= 0; i--) {
			a[i+1] = a[i] + b[i];
		}
	return 0;
}


int s1112()
{

//	linear dependence testing
//	loop reversal

		for (int i = LEN - 1; i >= 0; i--) {
			a[i] = b[i] + val;
		}
	return 0;
}

int s121()
{

//	induction variable recognition
//	loop with possible ambiguity because of scalar store
    int j;
		for (int i = 0; i < LEN-1; i++) {
			j = i + 1;
			a[i] = a[j] + b[i];
		}
	return 0;
}


int s122(int n1, int n3)
{

//	induction variable recognition
//	variable lower and upper bound, and stride
//	reverse data access and jump in data access

	int j, k;
		j = 1;
		k = 0;
		for (int i = n1-1; i < LEN; i += n3) {
			k += j;
			a[i] += b[LEN - k];
		}
	return 0;
}

int s1221()
{

//	run-time symbolic resolution

		for (int i = 4; i < LEN; i++) {
			b[i] = b[i - 4] + a[i];
		}
	return 0;
}

int s1251()
{

//	scalar and array expansion
//	scalar expansion

	TYPE s;
		for (int i = 0; i < LEN; i++) {
			s = b[i]+c[i];
			b[i] = a[i]+d[i];
			a[i] = s*e[i];
		}
	return 0;
}

int s127()
{

//	induction variable recognition
//	induction variable with multiple increments

	int j;
		j = -1;
		for (int i = 0; i < LEN/2; i++) {
			j++;
			a[j] = b[i] + c[i] * d[i];
			j++;
			a[j] = b[i] + d[i] * e[i];
		}
	return 0;
}

int s1281()
{

//	crossing thresholds
//	index set splitting
//	reverse data access

	TYPE x;
		for (int i = 0; i < LEN; i++) {
			x = b[i]*c[i]+a[i]*d[i]+e[i];
			a[i] = x-(TYPE)1.0;
			b[i] = x;
		}
	return 0;
}

int s1351()
{

//	induction pointer recognition

		TYPE* __restrict__ A = a;
		TYPE* __restrict__ B = b;
		TYPE* __restrict__ C = c;
		for (int i = 0; i < LEN; i++) {
			*A = *B+*C;
			A++;
			B++;
			C++;
		}
	return 0;
}


int s173()
{
//	symbolics
//	expression in loop bounds and subscripts

	int k = LEN/2;
		for (int i = 0; i < LEN/2; i++) {
			a[i+k] = a[i] + b[i];
		}
	return 0;
}


int s2244()
{

//	node splitting
//	cycle with ture and anti dependency

		for (int i = 0; i < LEN-1; i++) {
			a[i+1] = b[i] + e[i];
			a[i] = b[i] + c[i];
		}
	return 0;
}

int s251()
{

//	scalar and array expansion
//	scalar expansion

	TYPE s;
		for (int i = 0; i < LEN; i++) {
			s = b[i] + c[i] * d[i];
			a[i] = s * s;
		}
	return 0;
}

int s243()
{

//	node splitting
//	false dependence cycle breaking

		for (int i = 0; i < LEN-1; i++) {
			a[i] = b[i] + c[i  ] * d[i];
			b[i] = a[i] + d[i  ] * e[i];
			a[i] = b[i] + a[i+1] * d[i];
		}
	return 0;
}

int s3251()
{

//	scalar and array expansion
//	scalar expansion

		for (int i = 0; i < LEN-1; i++){
			a[i+1] = b[i]+c[i];
			b[i]   = c[i]*e[i];
			d[i]   = a[i]*e[i];
		}
	return 0;
}

int s351()
{

//	loop rerolling
//	unrolled saxpy

	TYPE alpha = c[0];
	int i1 = 0;
		for (int i = 0; i < LEN; i = i+5) {
		  i1++;
			a[i] += alpha * b[i];
			a[i + 1] += alpha * b[i + 1];
			a[i + 2] += alpha * b[i + 2];
			a[i + 3] += alpha * b[i + 3];
			a[i + 4] += alpha * b[i + 4];
		}
	return 0;
}



int s452()
{

//	intrinsic functions
//	seq function
		for (int i = 0; i < LEN; i++) {
			a[i] = b[i] + c[i] * (TYPE) (val);
			a[i] = a[i] + c[i];
		}
	return 0;
}


int val_s;
int s453()
{

//	induction varibale recognition

		for (int i = 0; i < LEN; i++) {
			a[i] = val_s * b[i];
		}
	return 0;
}


//int s313()
//{
//
////	reductions
////	dot product
//
//	TYPE dot;
//		dot = (TYPE)0.;
//		for (int i = 0; i < LEN; i++) {
//			dot += a[i] * b[i];
//		}
//	temp = dot;
//	return 0;
//}

//same as vpv
//int s431()
//{
//
////	parameters
////	parameter statement
//
//	int k1=1;
//	int k2=2;
//	int k=2*k1-k2;
//		for (int i = 0; i < LEN; i++) {
//			a[i] = a[i+k] + b[i];
//		}
//	return 0;
//}

int vtv()
{

//	control loops
//	vector times vector

		for (int i = 0; i < LEN; i++) {
			a[i] *= b[i];
		}
	return 0;
}


int vpvtv()
{

//	control loops
//	vector plus vector times vector

		for (int i = 0; i < LEN; i++) {
			a[i] += b[i] * c[i];
		}
	return 0;
}


int vpvts( TYPE s)
{

//	control loops
//	vector plus vector times scalar

		for (int i = 0; i < LEN; i++) {
			a[i] += b[i] * s;
		}
	return 0;
}


int vpvpv()
{

//	control loops
//	vector plus vector plus vector

		for (int i = 0; i < LEN; i++) {
			a[i] += b[i] + c[i];
		}
	return 0;
}

int vtvtv()
{

//	control loops
//	vector times vector times vector

		for (int i = 0; i < LEN; i++) {
			a[i] = a[i] * b[i] * c[i];
		}
	return 0;
}


int s111()
{

//	linear dependence testing
//	no dependence - vectorizable

		for (int i = 1; i < LEN; i += 2) {
			a[i] = a[i - 1] + b[i];
		}
	return 0;
}

int s1111()
{

//	no dependence - vectorizable
//	jump in data access

		for (int i = 0; i < LEN/2; i++) {
			a[2*i] = c[i] * b[i] + d[i] * b[i] + c[i] * c[i] + d[i] * b[i] + d[i] * c[i];
		}
	return 0;
}


int s113()
{

//	linear dependence testing
//	a(i)=a(1) but no actual dependence cycle

		for (int i = 1; i < LEN; i++) {
			a[i] = a[0] + b[i];
		}
	return 0;
}


int s114()
{

//	linear dependence testing
//	transpose vectorization
//	Jump in data access - not vectorizable

		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < i; j++) {
				aa[i][j] = aa[j][i] + bb[i][j];
			}
		}
	return 0;
}


int s115()
{

//	linear dependence testing
//	triangular saxpy loop

		for (int j = 0; j < LEN2; j++) {
			for (int i = j+1; i < LEN2; i++) {
				a[i] -= aa[j][i] * a[j];
			}
		}
	return 0;
}

int s1115()
{

//	linear dependence testing
//	triangular saxpy loop
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				aa[i][j] = aa[i][j]*cc[j][i] + bb[i][j];
			}
		}
	return 0;
}

int s116()
{

//	linear dependence testing
	int i1 = 0;  
	for (int i = 0; i < LEN-5 ; i += 5, i1++) {
		a[i] = a[i + 1] * a[i];
		a[i + 1] = a[i + 2] * a[i + 1];
		a[i + 2] = a[i + 3] * a[i + 2];
		a[i + 3] = a[i + 4] * a[i + 3];
		a[i + 4] = a[i + 5] * a[i + 4];
	}
	return 0;
}



int s119()
{

//	linear dependence testing
//	no dependence - vectorizable

		for (int i = 1; i < LEN2; i++) {
			for (int j = 1; j < LEN2; j++) {
				aa[i][j] = aa[i-1][j-1] + bb[i][j];
			}
		}
	return 0;
}






int s125()
{

//	induction variable recognition
//	induction variable in two loops; collapsing possible

	int k;
		k = -1;
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				k++;
				array[k] = aa[i][j] + bb[i][j] * cc[i][j];
			}
		}
	return 0;
}




int s128()
{

//	induction variables
//	coupled induction variables
//	jump in data access

	int j, k;
		j = -1;
		for (int i = 0; i < LEN/2; i++) {
			k = j + 1;
			a[i] = b[k] - d[i];
			j = k + 1;
			b[k] = a[i] + c[k];
		}
	return 0;
}



int s131()
{
//	global data flow analysis
//	forward substitution

	int m  = 2;
		for (int i = 0; i < LEN - 2; i++) {
			a[i] = a[i + m] + b[i];
		}
	return 0;
}



int s132()
{
//	global data flow analysis
//	loop with multiple dimension ambiguous subscripts


	int m = 0;
	int j = m;
	int k = m+1;
		for (int i= 1; i < LEN2; i++) {
			aa[j][i] = aa[k][i-1] + b[i] * c[1];
		}
	return 0;
}




int s171(int inc)
{

//	symbolics
//	symbolic dependence tests

		for (int i = 0; i < LEN; i++) {
			a[i * inc] += b[i];
		}
	return 0;
}




int s174(int M)
{

//	symbolics
//	loop with subscript that may seem ambiguous

		for (int i = 0; i < M; i++) {
			a[i+M] = a[i] + b[i];
		}
	return 0;
}




// **********************************************************
// *							    *
// *			VECTORIZATION			    *
// *							    *
// **********************************************************



int s211()
{

//	statement reordering
//	statement reordering allows vectorization

		for (int i = 1; i < LEN-1; i++) {
			a[i] = b[i - 1] + c[i] * d[i];
			b[i] = b[i + 1] - e[i] * d[i];
		}
	return 0;
}



int s212()
{

//	statement reordering
//	dependency needing temporary

		for (int i = 0; i < LEN-1; i++) {
			a[i] *= c[i];
			b[i] += a[i + 1] * d[i];
		}
	return 0;
}

int s1213()
{

//	statement reordering
//	dependency needing temporary

		for (int i = 1; i < LEN-1; i++) {
			a[i] = b[i-1]+c[i];
			b[i] = a[i+1]*d[i];
		}
	return 0;
}



int s221()
{

//	loop distribution
//	loop that is partially recursive

		for (int i = 1; i < LEN; i++) {
			a[i] += c[i] * d[i];
			b[i] = b[i - 1] + a[i] + d[i];
		}
	return 0;
}




int s222()
{

//	loop distribution
//	partial loop vectorizatio recurrence in middle

		for (int i = 1; i < LEN; i++) {
			a[i] += b[i] * c[i];
			e[i] = e[i - 1] * e[i - 1];
			a[i] -= b[i] * c[i];
		}
	return 0;
}







int s233()
{

//	loop interchange
//	interchanging with one of two inner loops

		for (int i = 1; i < LEN2; i++) {
			for (int j = 1; j < LEN2; j++) {
				aa[j][i] = aa[j-1][i] + cc[j][i];
			}
			for (int j = 1; j < LEN2; j++) {
				bb[j][i] = bb[j][i-1] + cc[j][i];
			}
		}
	return 0;
}

int s2233()
{

//	loop interchange
//	interchanging with one of two inner loops

		for (int i = 1; i < LEN2; i++) {
			for (int j = 1; j < LEN2; j++) {
				aa[j][i] = aa[j-1][i] + cc[j][i];
			}
			for (int j = 1; j < LEN2; j++) {
				bb[i][j] = bb[i-1][j] + cc[i][j];
			}
		}
	return 0;
}




int s241()
{

//	node splitting
//	preloading necessary to allow vectorization

		for (int i = 0; i < LEN-1; i++) {
			a[i] = b[i] * c[i  ] * d[i];
			b[i] = a[i] * a[i+1] * d[i];
		}
	return 0;
}




int s242(TYPE s1, TYPE s2)
{

//	node splitting

		for (int i = 1; i < LEN; ++i) {
			a[i] = a[i - 1] + s1 + s2 + b[i] + c[i] + d[i];
		}
	return 0;
}



int s244()
{

//	node splitting
//	false dependence cycle breaking

		for (int i = 0; i < LEN-1; ++i) {
			a[i] = b[i] + c[i] * d[i];
			b[i] = c[i] + b[i];
			a[i+1] = b[i] + a[i+1] * d[i];
		}
	return 0;
}

int s1244()
{

//	node splitting
//	cycle with ture and anti dependency

		for (int i = 0; i < LEN-1; i++) {
			a[i] = b[i] + c[i] * c[i] + b[i]*b[i] + c[i];
			d[i] = a[i] + a[i+1];
		}
	return 0;
}

int s2251()
{

//	scalar and array expansion
//	scalar expansion

		TYPE s = (TYPE)0.0;
		for (int i = 0; i < LEN; i++) {
			a[i] = s*e[i];
			s = b[i]+c[i];
			b[i] = a[i]+d[i];
		}
	return 0;
}




int s252()
{

//	scalar and array expansion
//	loop with ambiguous scalar temporary

	TYPE t, s;
		t = (TYPE) 0.;
		for (int i = 0; i < LEN; i++) {
			s = b[i] * c[i];
			a[i] = s + t;
			t = s;
		}
	return 0;
}



//icc undef pblend



int s254()
{

//	scalar and array expansion
//	carry around variable

	TYPE x;
		x = b[LEN-1];
		for (int i = 0; i < LEN; i++) {
			a[i] = (b[i] + x) * (TYPE).5;
			x = b[i];
		}
	return 0;
}


//same as s254
//int s255()
//{
//
////	scalar and array expansion
////	carry around variables, 2 levels
//
//	TYPE x, y;
//		x = b[LEN-1];
//		y = b[LEN-2];
//		for (int i = 0; i < LEN; i++) {
//			a[i] = (b[i] + x + y) * (TYPE).333;
//			y = x;
//			x = b[i];
//		}
//	return 0;
//}





int s261()
{

//	scalar and array expansion
//	wrap-around scalar under an if

	TYPE t;
		for (int i = 1; i < LEN; ++i) {
			t = a[i] + b[i];
			a[i] = t + c[i-1];
			t = c[i] * d[i];
			c[i] = t;
		}
	return 0;
}

int s271()
{

//	control flow
//	loop with singularity handling
		for (int i = 0; i < LEN; i++) {
			if (b[i] > (TYPE)0.) {
				a[i] += b[i] * c[i];
			}
		}
	return 0;
}



int s272(TYPE t)
{

//	control flow
//	loop with independent conditional

		for (int i = 0; i < LEN; i++) {
			if (e[i] >= t) {
				a[i] += c[i] * d[i];
				b[i] += c[i] * c[i];
			}
		}
	return 0;
}



int s273()
{

//	control flow
//	simple loop with dependent conditional

		for (int i = 0; i < LEN; i++) {
			a[i] += d[i] * e[i];
			if (a[i] < (TYPE)0.)
				b[i] += d[i] * e[i];
			c[i] += a[i] * d[i];
		}
	return 0;
}



//icc undef pblend


int s276()
{

//	control flow
//	if test using loop index

	int mid = (LEN/2);
		for (int i = 0; i < LEN; i++) {
			if (i+1 < mid) {
				a[i] += b[i] * c[i];
			} else {
				a[i] += b[i] * d[i];
			}
		}
	return 0;
}



int s1279()
{

//	control flow
//	vector if/gotos

		for (int i = 0; i < LEN; i++) {
			if (a[i] < (TYPE)0.) {
				if (b[i] > a[i]) {
					c[i] += d[i] * e[i];
				}
			}
		}
	return 0;
}



int s2711()
{

//	control flow
//	semantic if removal

		for (int i = 0; i < LEN; i++) {
			if (b[i] != (TYPE)0.0) {
				a[i] += b[i] * c[i];
			}
		}
	return 0;
}



int s2712()
{

//	control flow
//	if to elemental min

		for (int i = 0; i < LEN; i++) {
			if (a[i] > b[i]) {
				a[i] += b[i] * c[i];
			}
		}
	return 0;
}





//same as s254
//int s291()
//{
//
////	loop peeling
////	wrap around variable, 1 level
//
//	int im1;
//		im1 = LEN-1;
//		for (int i = 0; i < LEN; i++) {
//			a[i] = (b[i] + b[im1]) * (TYPE).5;
//			im1 = i;
//		}
//	return 0;
//}



//same as s254
//int s292()
//{
//
////	loop peeling
////	wrap around variable, 2 levels
////	similar to S291
//
//	int im1, im2;
//		im1 = LEN-1;
//		im2 = LEN-2;
//		for (int i = 0; i < LEN; i++) {
//			a[i] = (b[i] + b[im1] + b[im2]) * (TYPE).333;
//			im2 = im1;
//			im1 = i;
//		}
//	return 0;
//}



int s293()
{

//	loop peeling
//	a(i)=a(0) with actual dependence cycle, loop is vectorizable

		for (int i = 0; i < LEN; i++) {
			a[i] = a[0];
		}
	return 0;
}





int s2102()
{

//	diagonals
//	identity matrix, best results vectorize both inner and outer loops

		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				aa[j][i] = (TYPE)0.;
			}
			aa[i][i] = (TYPE)1.;
		}
	return 0;
}



int s2111()
{

//	wavefronts, it will make jump in data access

		for (int j = 1; j < LEN2; j++) {
			for (int i = 1; i < LEN2; i++) {
				aa[j][i] = aa[j][i-1] + aa[j-1][i];
			}
		}
	temp = 0.;
	for (int i = 0; i < LEN2; i++)
		for (int j = 0; j < LEN2; j++)
			temp += aa[i][j];
	if (temp == 0) temp = 3.;	
	return 0;
}


// **********************************************************
//							    *
//			IDIOM RECOGNITION		    *
//							    *
// **********************************************************



int s311()
{

//	reductions
//	sum reduction

	TYPE sum;
		sum = (TYPE)0.;
		for (int i = 0; i < LEN; i++) {
			sum += a[i];
		}
		temp = sum;
	return 0;
}

TYPE test(TYPE* A){
  TYPE s = (TYPE)0.0;
//  #pragma nosimd
  for (int i = 0; i < 4; i++)
    s += A[i];
  return s;
}


int s319()
{

//	reductions
//	coupled reductions

	TYPE sum;
		sum = 0.;
		for (int i = 0; i < LEN; i++) {
			a[i] = c[i] + d[i];
			sum += a[i];
			b[i] = c[i] + e[i];
			sum += b[i];
		}
	temp = sum;
	return 0;
}




int s3111()
{

//	reductions
//	conditional sum reduction

	TYPE sum;
		sum = 0.;
		for (int i = 0; i < LEN; i++) {
			if (a[i] > (TYPE)0.) {
				sum += a[i];
			}
		}
	temp = sum;
	return 0;
}



int s352()
{

//	loop rerolling
//	unrolled dot product

	TYPE dot;
		dot = (TYPE)0.;
	  int i1=0;
		for (int i = 0; i < LEN; i += 5) {
			i1++;
			dot = dot + a[i] * b[i] + a[i + 1] * b[i + 1] + a[i + 2]
				* b[i + 2] + a[i + 3] * b[i + 3] + a[i + 4] * b[i + 4];
		}
	temp = dot;
	return 0;
}



int s353(int* __restrict__ ip)
{

//	loop rerolling
//	unrolled sparse saxpy
//	gather is required

	TYPE alpha = c[0];
		for (int i = 0; i < LEN; i += 5) {
			a[i] += alpha * b[ip[i]];
			a[i + 1] += alpha * b[ip[i + 1]];
			a[i + 2] += alpha * b[ip[i + 2]];
			a[i + 3] += alpha * b[ip[i + 3]];
			a[i + 4] += alpha * b[ip[i + 4]];
		}
	return 0;
}

// **********************************************************
//							    *
//			 LANGUAGE COMPLETENESS		    *
//							    *
// **********************************************************




int s1421()
{

//	storage classes and equivalencing
//	equivalence- no overlap

	xx = &b[LEN/2];
		for (int i = 0; i < LEN/2; i++) {
			b[i] = xx[i] + a[i];
		}
	temp = 0;
	for (int i = 0; i < LEN/2; i++){
		temp += xx[i];
	}
	return 0;
}



int s422()
{

//	storage classes and equivalencing
//	common and equivalence statement
//	anti-dependence, threshold of 4

	xx = array + 4;
		for (int i = 0; i < LEN; i++) {
			xx[i] = array[i + 8] + a[i];
		}
	temp = 0;
	for (int i = 0; i < LEN; i++){
		temp += xx[i];
	}
	return 0;
}



int s423()
{

//	storage classes and equivalencing
//	common and equivalenced variables - with anti-dependence

	int vl = 64;
	xx = array+vl;
		for (int i = 0; i < LEN - 1; i++) {
			array[i+1] = xx[i] + a[i];
		}
	temp = 0.;
	for (int i = 0; i < LEN; i++){
		temp += array[i];
	}
	return 0;
}



int s424()
{

//	storage classes and equivalencing
//	common and equivalenced variables - overlap
//	vectorizeable in strips of 64 or less

	int vl = 63;
	xx = array + vl;
		for (int i = 0; i < LEN - 1; i++) {
			xx[i+1] = array[i] + a[i];
		}
	temp = 0.;
	for (int i = 0; i < LEN; i++){
		temp += xx[i];
	}
	return 0;
}




 int s441()
 {
 
 //	non-logical if's
 //	arithmetic if
 
 		for (int i = 0; i < LEN; i++) {
 			if (d[i] < (TYPE)0.) {
 				a[i] += b[i] * c[i];
 			} else if (d[i] == (TYPE)0.) {
 				a[i] += b[i] * b[i];
 			} else {
 				a[i] += c[i] * c[i];
 			}
 		}
 	return 0;
 }





 int s443()
 {
 
 //	non-logical if's
 //	arithmetic if
 
 		for (int i = 0; i < LEN; i++) {
 			if (d[i] <= (TYPE)0.) {
 				goto L20;
 			} else {
 				goto L30;
 			}
 L20:
 			a[i] += b[i] * c[i];
 			goto L50;
 L30:
 			a[i] += b[i] * b[i];
 L50:
 			;
 		}
 	return 0;
 }




int s471(){

	int m = LEN;
		for (int i = 0; i < m; i++) {
			x[i] = b[i] + d[i] * d[i];
			b[i] = c[i] + d[i] * e[i];
		}
	temp = 0.;
	for (int i = 0; i < LEN; i++){
		temp += x[i];
	}
	return 0;
}



int s4112(int* __restrict__ ip, TYPE s)
{

//	indirect addressing
//	sparse saxpy
//	gather is required

		for (int i = 0; i < LEN; i++) {
			a[i] += b[ip[i]] * s;
		}
	return 0;
}




int s4115(int* __restrict__ ip)
{

//	indirect addressing
//	sparse dot product
//	gather is required

	TYPE sum;
		sum = 0.;
		for (int i = 0; i < LEN; i++) {
			sum += a[i] * b[ip[i]];
		}
	temp = sum;
	return 0;
}





TYPE f(TYPE a, TYPE b){
	return a*b;
}



int va()
{

//	control loops
//	vector assignment

		for (int i = 0; i < LEN; i++) {
			a[i] = b[i];
		}
	return 0;
}



int vag( int* __restrict__ ip)
{

//	control loops
//	vector assignment, gather
//	gather is required

		for (int i = 0; i < LEN; i++) {
			a[i] = b[ip[i]];
		}
	return 0;
}





//icc undef pblend

int vif()
{

//	control loops
//	vector if

		for (int i = 0; i < LEN; i++) {
			if (b[i] > (TYPE)0.) {
				a[i] = b[i];
			}
		}
	return 0;
}




int vpv()
{

//	control loops
//	vector plus vector

		for (int i = 0; i < LEN; i++) {
			a[i] += b[i];
		}
	return 0;
}



//same as s311 
//int vsumr()
//{
//
////	control loops
////	vector sum reduction
//
//	TYPE sum;
//		sum = 0.;
//		for (int i = 0; i < LEN; i++) {
//			sum += a[i];
//		}
//		temp = sum;
//	return 0;
//}



//same as s313 
int vdotr()
{

//	control loops
//	vector dot product reduction

	TYPE dot;
		dot = 0.;
		for (int i = 0; i < LEN; i++) {
			dot += a[i] * b[i];
		}
	temp = dot;
	return 0;
}




int main(){

//	s000();
//	s111();
//	s1111();
//	s112();
//	s1112();
//	s113();
//	s1113();
//	s114();
//	s115();
//	s1115();
//	s116();
//	s118();
//	s119();
//	s1119();
//	s121();
//	s122(n1,n3);
//	s123();
//  s124();
//	s125();
//	s126();
//	s127();
//	s128();
//	s131();
//	s132();
//	s141();
//	s151();
//	s152();
//	s161();
//	s1161();
//	s162(n1);
//	s171(n1);
//	s172(n1,n3);
//	s173();
//	s174(LEN/2);
//	s175(n1);
//	s176();
//	s211();
//	s212();
//	s1213();
//	s221();
//	s1221();
//	s222();
//	s231();
//	s232();
//	s1232();
//	s233();
//	s2233();
//	s235();
//	s241();
//	s242(s1, s2);
//	s243();
//	s244();
//	s1244();
//	s2244();
//	s251();
//	s1251();
//	s2251();
//	s3251();
//	s252();
//	s253();
//	s254();
//	s255();
//	s256();
//	s257();
//	s258();
//	s261();
//	s271();
//	s272(s1);
//	s273();
//	s274();
//	s275();
//	s2275();
//	s276();
//	s277();
//	s278();
//	s279();
//	s1279();
//	s2710(s1);
//	s2711();
//	s2712();
//	s281();
//	s1281();
//	s291();
//	s292();
//	s293();
//	s2101();
//	s2102();
//	s2111();
//	s311();
//	s31111();
//	s312();
//	s313();
//	s314();
//	s315();
//	s316();
//	s317();
//	s318(n1);
//	s319();
//	s3110();
//	s13110();
//	s3111();
//	s3112();
//	s3113();
//	s321();
//	s322();
//	s323();
//	s331();
//	s332(s1);
//	s341();
//	s342();
//	s343();
//	s351();
//	s1351();
//	s352();
//	s353(ip);
//	s421();
//	s1421();
//	s422();
//	s423();
//	s424();
//	s431();
//	s441();
//	s442();
//	s443();
//	s451();
//	s452();
//	s453();
//	s471();
//	s481();
//	s482();
//	s491(ip);
//	s4112(ip, s1);
//	s4113(ip);
//	s4114(ip,n1);
//	s4115(ip);
//	s4116(ip, LEN2/2, n1);
//	s4117();
//	s4121();
//	va();
//	vag(ip);
//	vas(ip);
//	vif();
//	vpv();
//	vtv();
//	vpvtv();
//	vpvts(s1);
//	vpvpv();
//	vtvtv();
//	vsumr();
//	vdotr();
//	vbor();
	return 0;
}

