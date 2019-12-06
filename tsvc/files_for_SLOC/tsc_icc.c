
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


int s1119()
{

//	linear dependence testing
//	no dependence - vectorizable
		for (int i = 1; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				aa[i][j] = aa[i-1][j] + bb[i][j];
			}
		}
	return 0;
int s317()
{

//	reductions
//	product reductio vectorize with
//	1. scalar expansion of factor, and product reduction
//	2. closed form solution: q = factor**n

	TYPE q;
		q = (TYPE)1.;
		for (int i = 0; i < LEN/2; i++) {
			q *= (TYPE)99;
		}
	temp = q;
	return 0;
}

int s162(int k)
{
//	control flow
//	deriving assertions

		if (k > 0) {
			for (int i = 0; i < LEN-1; i++) {
				a[i] = a[i + k] + b[i] * c[i];
			}
		}
	return 0;
}

 int s124()
 {
 
 //	induction variable recognition
 //	induction variable under both sides of if (same value)
 
 	int j;
 		j = -1;
 		for (int i = 0; i < LEN; i++) {
 			if (b[i] > (TYPE)0.) {
 				j++;
 				a[j] = b[i] + d[i] * e[i];
 			} else {
 				j++;
 				a[j] = c[i] + d[i] * e[i];
 			}
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

int vbor()
{

//	control loops
//	basic operations rates, isolate arithmetic from memory traffic
//	all combinations of three, 59 flops for 6 loads and 1 store.

	TYPE a1, b1, c1, d1, e1, f1;
		for (int i = 0; i < LEN2; i++) {
			a1 = a[i];
			b1 = b[i];
			c1 = c[i];
			d1 = d[i];
			e1 = e[i];
			f1 = aa[0][i];
			a1 = a1 * b1 * c1 + a1 * b1 * d1 + a1 * b1 * e1 + a1 * b1 * f1 +
				a1 * c1 * d1 + a1 * c1 * e1 + a1 * c1 * f1 + a1 * d1 * e1
				+ a1 * d1 * f1 + a1 * e1 * f1;
			b1 = b1 * c1 * d1 + b1 * c1 * e1 + b1 * c1 * f1 + b1 * d1 * e1 +
				b1 * d1 * f1 + b1 * e1 * f1;
			c1 = c1 * d1 * e1 + c1 * d1 * f1 + c1 * e1 * f1;
			d1 = d1 * e1 * f1;
			x[i] = a1 * b1 * c1 * d1;
		}
	temp = 0.;
	for (int i = 0; i < LEN; i++){
		temp += x[i];
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

int s31111()
{

//	reductions
//	sum reduction

	TYPE sum;
		sum = (TYPE)0.;
		sum += test(a);
		sum += test(&a[4]);
		sum += test(&a[8]);
		sum += test(&a[12]);
		sum += test(&a[16]);
		sum += test(&a[20]);
		sum += test(&a[24]);
		sum += test(&a[28]);
		temp = sum;
	return 0;
}
int s176()
{

//	symbolics
//	convolution
	int m = LEN/2;
		for (int j = 0; j < (LEN/2); j++) {
			for (int i = 0; i < m; i++) {
				a[i] += b[i+m-j-1] * c[j];
			}
//			DBG(__LINE__);
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



// **********************************************************
//							    *
//			 LANGUAGE COMPLETENESS		    *
//							    *
// **********************************************************







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

	return 0;
}

