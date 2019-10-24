
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

//#include <builtins.h>


#define TYPE int

#define lll LEN


__attribute__ ((aligned(16))) TYPE X[lll],Y[lll],Z[lll],U[lll],V[lll];


//float* __restrict__ array;
TYPE array[LEN2*LEN2] __attribute__((aligned(16)));

TYPE x[LEN] __attribute__((aligned(16)));
TYPE temp;
int temp_int;


__attribute__((aligned(16))) TYPE a[LEN],b[LEN],c[LEN],d[LEN],e[LEN],
                                   aa[LEN2][LEN2],bb[LEN2][LEN2],cc[LEN2][LEN2],tt[LEN2][LEN2];

__attribute__((aligned(16))) TYPE as[LEN1],bs[LEN1];


int indx[LEN] __attribute__((aligned(16)));


TYPE* __restrict__ xx;
TYPE* yy;
TYPE arr[LEN];

// FP functions had divide operation

/*int set1d(TYPE value, int stride)
{
	if (stride == -1) {
		for (int i = 0; i < LEN; i++) {
			arr[i] = (TYPE) (i+1);
		}
	} else if (stride == -2) {
		for (int i = 0; i < LEN; i++) {
			arr[i] = (TYPE) ((i+1) * (i+1));
		}
	} else {
		for (int i = 0; i < LEN; i += stride) {
			arr[i] = value;
		}
	}
	return 0;
}

int set1ds(TYPE value, int stride)
{
	if (stride == -1) {
		for (int i = 0; i < LEN; i++) {
			arr[i] = (TYPE) (i+1);
		}
	} else if (stride == -2) {
		for (int i = 0; i < LEN; i++) {
			arr[i] = (TYPE) ((i+1) * (i+1));
		}
	} else {
		for (int i = 0; i < LEN; i += stride) {
			arr[i] = value;
		}
	}
	return 0;
}

int set2d(TYPE value, int stride)
{

//  -- initialize two-dimensional arraysft

	if (stride == -1) {
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				array[i][j] = (TYPE) (i+1);
			}
		}
	} else if (stride == -2) {
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				array[i][j] = (TYPE) ((i+1) * (i+1));
			}
		}
	} else {
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j += stride) {
				array[i][j] = value;
			}
		}
	}
	return 0;
}

void check(int name){

	TYPE suma = 0;
	TYPE sumb = 0;
	TYPE sumc = 0;
	TYPE sumd = 0;
	TYPE sume = 0;
	for (int i = 0; i < LEN; i++){
		suma += a[i];
		sumb += b[i];
		sumc += c[i];
		sumd += d[i];
		sume += e[i];
	}
	TYPE sumaa = 0;
	TYPE sumbb = 0;
	TYPE sumcc = 0;
	for (int i = 0; i < LEN2; i++){
		for (int j = 0; j < LEN2; j++){
			sumaa += aa[i][j];
			sumbb += bb[i][j];
			sumcc += cc[i][j];

		}
	}
	TYPE sumarray = 0;
	for (int i = 0; i < LEN2*LEN2; i++){
		sumarray += array[i];
	}

	if (name == 1) printf("%f \n",suma);
	if (name == 2) printf("%f \n",sumb);
	if (name == 3) printf("%f \n",sumc);
	if (name == 4) printf("%f \n",sumd);
	if (name == 5) printf("%f \n",sume);
	if (name == 11) printf("%f \n",sumaa);
	if (name == 22) printf("%f \n",sumbb);
	if (name == 33) printf("%f \n",sumcc);
	if (name == 0) printf("%f \n",sumarray);
	if (name == 12) printf("%f \n",suma+sumb);
	if (name == 25) printf("%f \n",sumb+sume);
	if (name == 13) printf("%f \n",suma+sumc);
	if (name == 123) printf("%f \n",suma+sumb+sumc);
	if (name == 1122) printf("%f \n",sumaa+sumbb);
	if (name == 112233) printf("%f \n",sumaa+sumbb+sumcc);
	if (name == 111) printf("%f \n",sumaa+suma);
	if (name == -1) printf("%f \n",temp);
	if (name == -12) printf("%f \n",temp+sumb);

}

*/
TYPE sum1d(){
	TYPE ret = 0.;
	for (int i = 0; i < LEN; i++)
		ret += arr[i];
	return ret;
}


TYPE val = 1;
int s000()
{

//	linear dependence testing
//	no dependence - vectorizable

		for (int i = 0; i < lll; i++) {
			X[i] = Y[i] + val;
		}
	return 0;
}

// %1.1
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

// %1.1

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

// %1.1

int s113()
{

//	linear dependence testing
//	a(i)=a(1) but no actual dependence cycle

		for (int i = 1; i < LEN; i++) {
			a[i] = a[0] + b[i];
		}
	return 0;
}

int s1113()
{

//	linear dependence testing
//	one iteration dependency on a(LEN/2) but still vectorizable

		for (int i = 0; i < LEN; i++) {
			a[i] = a[LEN/2] + b[i];
		}
	return 0;
}

// %1.1

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

// %1.1

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

// %1.1
// clang undef opcode pblendw
/*int s116()
{

//	linear dependence testing
		for (int i = 0; i < LEN - 5; i += 5) {
			a[i] = a[i + 1] * a[i];
			a[i + 1] = a[i + 2] * a[i + 1];
			a[i + 2] = a[i + 3] * a[i + 2];
			a[i + 3] = a[i + 4] * a[i + 3];
			a[i + 4] = a[i + 5] * a[i + 4];
		}
	return 0;
}*/


// %1.1

int s118()
{

//	linear dependence testing
//	potential dot product recursion

		for (int i = 1; i < LEN2; i++) {
			for (int j = 0; j <= i - 1; j++) {
				a[i] += bb[j][i] * a[i-j-1];
			}
		}
	return 0;
}

// %1.1

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
}

// %1.2

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

// %1.2

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

// %1.2

int s123()
{

//	induction variable recognition
//	induction variable under an if
//	not vectorizable, the condition cannot be speculated

	int j;
		j = -1;
		for (int i = 0; i < (LEN/2); i++) {
			j++;
			a[j] = b[i] + d[i] * e[i];
			if (c[i] > (TYPE)0.) {
				j++;
				a[j] = c[i] + d[i] * e[i];
			}
		}
	return 0;
}

// %1.2
// GCC  UNDEF OPCODE -- pblendvb
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

// %1.2
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

// %1.2
int s126()
{

//	induction variable recognition
//	induction variable in two loops; recurrence in inner loop

	int k;
		k = 1;
		for (int i = 0; i < LEN2; i++) {
			for (int j = 1; j < LEN2; j++) {
				bb[j][i] = bb[j-1][i] + array[k-1] * cc[j][i];
				++k;
			}
			++k;
		}
	return 0;
}

// %1.2

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

// %1.2

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

// %1.3

int s131()
{
//	global data flow analysis
//	forward substitution

	int m  = 2;
		for (int i = 0; i < LEN - 1; i++) {
			a[i] = a[i + m] + b[i];
		}
	return 0;
}

// %1.3

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

// %1.4

int s141()
{

//	nonlinear dependence testing
//	walk a row in a symmetric packed array
//	element a(i,j) for (int j>i) stored in location j*(j-1)/2+i

	int k;
		for (int i = 0; i < LEN2; i++) {
			k = (i+1) * ((i+1) - 1) / 2 + (i+1)-1;
			for (int j = i; j < LEN2; j++) {
				array[k] += bb[j][i];
				k += j+1;
			}
		}
	return 0;
}

// %1.5
/*
int s151s(TYPE a[LEN], TYPE b[LEN],  int m)
{
	for (int i = 0; i < LEN-1; i++) {
		a[i] = a[i + m] + b[i];
	}
	return 0;
}

int s151()
{

//	interprocedural data flow analysis
//	passing parameter information into a subroutine

	s151s(a, b,  1);
	return 0;
}

// %1.5

int s152s(TYPE a[LEN], TYPE b[LEN], TYPE c[LEN], int i)
{
	a[i] += b[i] * c[i];
	return 0;
}

int s152()
{

//	interprocedural data flow analysis
//	collecting information from a subroutine
		for (int i = 0; i < LEN; i++) {
			b[i] = d[i] * e[i];
			s152s(a, b, c, i);
		}
	return 0;
}
*/
// %1.6

int s161()
{

//	control flow
//	tests for recognition of loop independent dependences
//	between statements in mutually exclusive regions.

		for (int i = 0; i < LEN-1; ++i) {
			if (b[i] < (TYPE)0.) {
				goto L20;
			}
			a[i] = c[i] + d[i] * e[i];
			goto L10;
L20:
			c[i+1] = a[i] + d[i] * d[i];
L10:
			;
		}
	return 0;
}

int s1161()
{

//	control flow
//	tests for recognition of loop independent dependences
//	between statements in mutually exclusive regions.

		for (int i = 0; i < LEN-1; ++i) {
			if (c[i] < (TYPE)0.) {
				goto L20;
			}
			a[i] = c[i] + d[i] * e[i];
			goto L10;
L20:
			b[i] = a[i] + d[i] * d[i];
L10:
			;
		}
	return 0;
}

// %1.6

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

// %1.7

int s171(int inc)
{

//	symbolics
//	symbolic dependence tests

		for (int i = 0; i < LEN; i++) {
			a[i * inc] += b[i];
		}
	return 0;
}

// %1.7

int s172( int n1, int n3)
{
//	symbolics
//	vectorizable if n3 .ne. 0

		for (int i = n1-1; i < LEN; i += n3) {
			a[i] += b[i];
		}
	return 0;
}

// %1.7

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

// %1.7

int s174(int M)
{

//	symbolics
//	loop with subscript that may seem ambiguous

		for (int i = 0; i < M; i++) {
			a[i+M] = a[i] + b[i];
		}
	return 0;
}

// %1.7

int s175(int inc)
{

//	symbolics
//	symbolic dependence tests

		for (int i = 0; i < LEN-1; i += inc) {
			a[i] = a[i + inc] + b[i];
		}
	return 0;
}

// %1.7

int s176()
{

//	symbolics
//	convolution
	int m = LEN/2;
		for (int j = 0; j < (LEN/2); j++) {
			for (int i = 0; i < m; i++) {
				a[i] += b[i+m-j-1] * c[j];
			}
		}
	return 0;
}

// **********************************************************
// *							    *
// *			VECTORIZATION			    *
// *							    *
// **********************************************************

// %2.1

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

// %2.1

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

// %2.2

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

int s1221()
{

//	run-time symbolic resolution

		for (int i = 4; i < LEN; i++) {
			b[i] = b[i - 4] + a[i];
		}
	return 0;
}

// %2.2

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

// %2.3

int s231()
{
//	loop interchange
//	loop with data dependency

		for (int i = 0; i < LEN2; ++i) {
			for (int j = 1; j < LEN2; j++) {
				aa[j][i] = aa[j - 1][i] + bb[j][i];
			}
		}
	return 0;
}

// %2.3

int s232()
{

//	loop interchange
//	interchanging of triangular loops

		for (int j = 1; j < LEN2; j++) {
			for (int i = 1; i <= j; i++) {
				aa[j][i] = aa[j][i-1]*aa[j][i-1]+bb[j][i];
			}
		}
	return 0;
}

int s1232()
{

//	loop interchange
//	interchanging of triangular loops

		for (int j = 0; j < LEN2; j++) {
			for (int i = j; i < LEN2; i++) {
				aa[i][j] = bb[i][j] + cc[i][j];
			}
		}
	return 0;
}

// %2.3

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

// %2.3
int s235()
{

//	loop interchanging
//	imperfectly nested loops

		for (int i = 0; i < LEN2; i++) {
			a[i] += b[i] * c[i];
			for (int j = 1; j < LEN2; j++) {
				aa[j][i] = aa[j-1][i] + bb[j][i] * a[i];
			}
		}
	return 0;
}

// %2.4

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


// %2.4

int s242(TYPE s1, TYPE s2)
{

//	node splitting

		for (int i = 1; i < LEN; ++i) {
			a[i] = a[i - 1] + s1 + s2 + b[i] + c[i] + d[i];
		}
	return 0;
}

// %2.4

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

// %2.4

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

// %2.5

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


// %2.5

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

// %2.5


int s253()
{

//	scalar and array expansion
//	scalar expansio assigned under if

	TYPE s;
		for (int i = 0; i < LEN; i++) {
			if (a[i] > b[i]) {
				s = a[i] - b[i] * d[i];
				c[i] += s;
				a[i] = s;
			}
		}
	return 0;
}

// %2.5

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

// %2.5
/*
int s255()
{

//	scalar and array expansion
//	carry around variables, 2 levels

	TYPE x, y;
		x = b[LEN-1];
		y = b[LEN-2];
		for (int i = 0; i < LEN; i++) {
			a[i] = (b[i] + x + y) * (TYPE).333;
			y = x;
			x = b[i];
		}
	return 0;
}
*/
// %2.5

int s256()
{

//	scalar and array expansion
//	array expansion

		for (int i = 0; i < LEN2; i++) {
			for (int j = 1; j < LEN2; j++) {
				a[j] = (TYPE)1.0 - a[j - 1];
				cc[j][i] = a[j] + bb[j][i]*d[j];
			}
		}
	return 0;
}

// %2.5

int s257()
{

//	scalar and array expansion
//	array expansion

		for (int i = 1; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				a[i] = aa[j][i] - a[i-1];
				aa[j][i] = a[i] + bb[j][i];
			}
		}
	return 0;
}

int s258()
{

//	scalar and array expansion
//	wrap-around scalar under an if

	TYPE s;
		s = 0.;
		for (int i = 0; i < LEN2; ++i) {
			if (a[i] > 0.) {
				s = d[i] * d[i];
			}
			b[i] = s * c[i] + d[i];
			e[i] = (s + (TYPE)1.) * aa[0][i];
		}
	return 0;
}

// %2.7

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

// %2.7

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

// %2.7

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

// %2.7

int s274()
{

//	control flow
//	complex loop with dependent conditional

		for (int i = 0; i < LEN; i++) {
			a[i] = c[i] + e[i] * d[i];
			if (a[i] > (TYPE)0.) {
				b[i] = a[i] + b[i];
			} else {
				a[i] = d[i] * e[i];
			}
		}
	return 0;
}

// %2.7

int s275()
{

//	control flow
//	if around inner loop, interchanging needed

		for (int i = 0; i < LEN2; i++) {
			if (aa[0][i] > (TYPE)0.) {
				for (int j = 1; j < LEN2; j++) {
					aa[j][i] = aa[j-1][i] + bb[j][i] * cc[j][i];
				}
			}
		}
	return 0;
}

int s2275()
{

//	loop distribution is needed to be able to interchange

		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				aa[j][i] = aa[j][i] + bb[j][i] * cc[j][i];
			}
			a[i] = b[i] + c[i] * d[i];
		}
	return 0;
}

// %2.7

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

// %2.7
int s277()
{

//	control flow
//	test for dependences arising from guard variable computation.

		for (int i = 0; i < LEN-1; i++) {
				if (a[i] >= (TYPE)0.) {
					goto L20;
				}
				if (b[i] >= (TYPE)0.) {
					goto L30;
				}
				a[i] += c[i] * d[i];
L30:
				b[i+1] = c[i] + d[i] * e[i];
L20:
;
		}
	return 0;
}

// %2.7

int s278()
{

//	control flow
//	if/goto to block if-then-else

		for (int i = 0; i < LEN; i++) {
			if (a[i] > (TYPE)0.) {
				goto L20;
			}
			b[i] = -b[i] + d[i] * e[i];
			goto L30;
L20:
			c[i] = -c[i] + d[i] * e[i];
L30:
			a[i] = b[i] + c[i] * d[i];
		}
	return 0;
}

// %2.7

int s279()
{

//	control flow
//	vector if/gotos

		for (int i = 0; i < LEN; i++) {
			if (a[i] > (TYPE)0.) {
				goto L20;
			}
			b[i] = -b[i] + d[i] * d[i];
			if (b[i] <= a[i]) {
				goto L30;
			}
			c[i] += d[i] * e[i];
			goto L30;
L20:
			c[i] = -c[i] + e[i] * e[i];
L30:
			a[i] = b[i] + c[i] * d[i];
		}
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

// %2.7

int s2710( TYPE x)
{

//	control flow
//	scalar and vector ifs

		for (int i = 0; i < LEN; i++) {
			if (a[i] > b[i]) {
				a[i] += b[i] * d[i];
				if (LEN > 10) {
					c[i] += d[i] * d[i];
				} else {
					c[i] = d[i] * e[i] + (TYPE)1.;
				}
			} else {
				b[i] = a[i] + e[i] * e[i];
				if (x > (TYPE)0.) {
					c[i] = a[i] + d[i] * d[i];
				} else {
					c[i] += e[i] * e[i];
				}
			}
		}
	return 0;
}

// %2.7

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

// %2.7

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

// %2.8

int s281()
{

//	crossing thresholds
//	index set splitting
//	reverse data access

	TYPE x;
		for (int i = 0; i < LEN; i++) {
			x = a[LEN-i-1] + b[i] * c[i];
			a[i] = x-(TYPE)1.0;
			b[i] = x;
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

// %2.9
/*
int s291()
{

//	loop peeling
//	wrap around variable, 1 level

	int im1;
		im1 = LEN-1;
		for (int i = 0; i < LEN; i++) {
			a[i] = (b[i] + b[im1]) * (TYPE).5;
			im1 = i;
		}
	return 0;
}

// %2.9

int s292()
{

//	loop peeling
//	wrap around variable, 2 levels
//	similar to S291

	int im1, im2;
		im1 = LEN-1;
		im2 = LEN-2;
		for (int i = 0; i < LEN; i++) {
			a[i] = (b[i] + b[im1] + b[im2]) * (TYPE).333;
			im2 = im1;
			im1 = i;
		}
	return 0;
}
*/
// %2.9

int s293()
{

//	loop peeling
//	a(i)=a(0) with actual dependence cycle, loop is vectorizable

		for (int i = 0; i < LEN; i++) {
			a[i] = a[0];
		}
	return 0;
}

// %2.10

int s2101()
{

//	diagonals
//	main diagonal calculation
//	jump in data access

		for (int i = 0; i < LEN2; i++) {
			aa[i][i] += bb[i][i] * cc[i][i];
		}
	return 0;
}

// %2.12

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

// %2.11

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

// %3.1

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

// %3.1
/*
int s312()
{

//	reductions
//	product reduction

	TYPE prod;
		prod = (TYPE)1.;
		for (int i = 0; i < LEN; i++) {
			prod *= a[i];
		}
		temp = prod;
	return 0;
}
*/
// %3.1
int s313()
{

//	reductions
//	dot product

	TYPE dot;
		dot = (TYPE)0.;
		for (int i = 0; i < LEN; i++) {
			dot += a[i] * b[i];
		}
	temp = dot;
	return 0;
}

// %3.1

int s314()
{

//	reductions
//	if to max reduction

	TYPE x;
		x = a[0];
		for (int i = 0; i < LEN; i++) {
			if (a[i] > x) {
				x = a[i];
			}
		}
	temp = x;
	return 0;
}

// %3.1
// gcc   -- undef opcode pmuldq
// clang -- undef opcode pblendw 

int s315()
{

//	reductions
//	if to max with index reductio 1 dimension

	for (int i = 0; i < LEN; i++)
		a[i] = (i * 7) % LEN;

	TYPE x, chksum;
	int index;
		x = a[0];
		index = 0;
		for (int i = 0; i < LEN; ++i) {
			if (a[i] > x) {
				x = a[i];
				index = i;
			}
		}
		chksum = x + (TYPE) index;
	temp = index+x+1;
	return 0;
}


// %3.1

int s316()
{

//	reductions
//	if to min reduction

	TYPE x;
		x = a[0];
		for (int i = 1; i < LEN; ++i) {
			if (a[i] < x) {
				x = a[i];
			}
		}
	temp = x;
	return 0;
}
// %3.1

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

// %3.1

int s318( int inc)
{

//	reductions
//	isamax, max absolute value, increments not equal to 1


	int k, index;
	TYPE max, chksum;
		k = 0;
		index = 0;
		max = abs(a[0]);
		k += inc;
		for (int i = 1; i < LEN; i++) {
			if (abs(a[k]) <= max) {
				goto L5;
			}
			index = i;
			max = abs(a[k]);
L5:
			k += inc;
		}
		chksum = max + (TYPE) index;
	temp = max + index+1;
	return 0;
}

// %3.1

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

// %3.1

int s3110()
{

//	reductions
//	if to max with index reductio 2 dimensions
//	similar to S315

	int xindex, yindex;
	TYPE max, chksum;
		max = aa[(0)][0];
		xindex = 0;
		yindex = 0;
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				if (aa[i][j] > max) {
					max = aa[i][j];
					xindex = i;
					yindex = j;
				}
			}
		}
		chksum = max + (TYPE) xindex + (TYPE) yindex;
	temp = max + xindex+1 + yindex+1;
	return 0;
}

int s13110()
{

//	reductions
//	if to max with index reductio 2 dimensions

	int xindex, yindex;
	TYPE max, chksum;
		max = aa[(0)][0];
		xindex = 0;
		yindex = 0;
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				if (aa[i][j] > max) {
					max = aa[i][j];
				}
			}
		}
		chksum = max + (TYPE) xindex + (TYPE) yindex;
	temp = max + xindex+1 + yindex+1;
	return 0;
}

// %3.1

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

// %3.1

int s3112()
{

//	reductions
//	sum reduction saving running sums

	TYPE sum;
		sum = (TYPE)0.0;
		for (int i = 0; i < LEN; i++) {
			sum += a[i];
			b[i] = sum;
		}
	temp = sum;
	return 0;
}

// %3.1

int s3113()
{

//	reductions
//	maximum of absolute value

	TYPE max;
		max = abs(a[0]);
		for (int i = 0; i < LEN; i++) {
			if ((abs(a[i])) > max) {
				max = abs(a[i]);
			}
		}
	temp = max;
	return 0;
}

// %3.2

int s321()
{

//	recurrences
//	first order linear recurrence

		for (int i = 1; i < LEN; i++) {
			a[i] += a[i-1] * b[i];
		}
	return 0;
}

// %3.2

int s322()
{

//	recurrences
//	second order linear recurrence

		for (int i = 2; i < LEN; i++) {
			a[i] = a[i] + a[i - 1] * b[i] + a[i - 2] * c[i];
		}
	return 0;
}

// %3.2

int s323()
{

//	recurrences
//	coupled recurrence

		for (int i = 1; i < LEN; i++) {
			a[i] = b[i-1] + c[i] * d[i];
			b[i] = a[i] + c[i] * e[i];
		}
	return 0;
}

// %3.3
// GCC  UNDEF OPCODE -- pblendvb
 int s331()
 {
 
 //	search loops
 //	if to last-1
 
 	int j;
 	TYPE chksum;
 		j = -1;
 		for (int i = 0; i < LEN; i++) {
 			if (a[i] < (TYPE)0.) {
 				j = i;
 			}
 		}
 		chksum = (TYPE) j;
 	temp = j+1;
 	return 0;
 }

int max(int a1, int b1)
{
	if (b1 > a1)
		return b1;
	else
		return a1;
}

// %3.3
int s332( TYPE t)
{

//	search loops
//	first value greater than threshoLEN

	int index;
	TYPE value;
	TYPE chksum;
		index = -2;
		value = -1.;
		for (int i = 0; i < LEN; i++) {
			if (a[i] > t) {
				index = i;
				value = a[i];
				goto L20;
			}
		}
L20:
		chksum = value + (TYPE) index;
	temp = value;
	return 0;
}


// %3.4

int s341()
{

//	packing
//	pack positive values
//	not vectorizable, value of j in unknown at each iteration

	int j;
		j = -1;
		for (int i = 0; i < LEN; i++) {
			if (b[i] > (TYPE)0.) {
				j++;
				a[j] = b[i];
			}
		}
	return 0;
}

// %3.4

int s342()
{

//	packing
//	unpacking
//	not vectorizable, value of j in unknown at each iteration


	int j = 0;
		j = -1;
		for (int i = 0; i < LEN; i++) {
			if (a[i] > (TYPE)0.) {
				j++;
				a[i] = b[j];
			}
		}
	return 0;
}

// %3.4

int s343()
{

//	packing
//	pack 2-d array into one dimension
//	not vectorizable, value of k in unknown at each iteration


	int k;
		k = -1;
		for (int i = 0; i < LEN2; i++) {
			for (int j = 0; j < LEN2; j++) {
				if (bb[j][i] > (TYPE)0.) {
					k++;
					array[k] = aa[j][i];
				}
			}
		}
	return 0;
}

// %3.5

int s351()
{

//	loop rerolling
//	unrolled saxpy

	TYPE alpha = c[0];
	int i1=0;
		for (int i = 0; i < LEN1; i += 5) {
			i1++;
			as[i] += alpha * bs[i];
			as[i + 1] += alpha * bs[i + 1];
			as[i + 2] += alpha * bs[i + 2];
			as[i + 3] += alpha * bs[i + 3];
			as[i + 4] += alpha * bs[i + 4];
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

// %3.5

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

// %3.5

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

// %4.1
// %4.2

int s421()
{

//	storage classes and equivalencing
//	equivalence- no overlap

		yy = arr;
		for (int i = 0; i < LEN - 1; i++) {
			arr[i] = yy[i+1] + a[i];
		}
	temp = 0;
	for (int i = 0; i < LEN; i++){
		temp += arr[i];
	}
	return 0;
}

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

// %4.2

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

// %4.2

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

// %4.2

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

// %4.3

int s431()
{

//	parameters
//	parameter statement

	int k1=1;
	int k2=2;
	int k=2*k1-k2;
		for (int i = 0; i < LEN; i++) {
			a[i] = a[i+k] + b[i];
		}
	return 0;
}

// %4.4
// GCC  UNDEF OPCODE -- pblendvb
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

// %4.4

int s442()
{

//	non-logical if's
//	computed goto

		for (int i = 0; i < LEN; i++) {
			switch (indx[i]) {
				case 1:  goto L15;
				case 2:  goto L20;
				case 3:  goto L30;
				case 4:  goto L40;
			}
L15:
			a[i] += b[i] * b[i];
			goto L50;
L20:
			a[i] += c[i] * c[i];
			goto L50;
L30:
			a[i] += d[i] * d[i];
			goto L50;
L40:
			a[i] += e[i] * e[i];
L50:
			;
		}
	return 0;
}

// %4.4
// GCC  UNDEF OPCODE -- pblendvb
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

// %4.5
//Floating point
//int s451()
//{
//
////	intrinsic functions
////	intrinsics
//
//		for (int i = 0; i < LEN; i++) {
//			a[i] = sinf(b[i]) + cosf(c[i]);
//		}
//	return 0;
//}

// %4.5

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

// %4.5

int s453()
{

//	induction varibale recognition

	TYPE s;
		s = 0.;
		for (int i = 0; i < LEN; i++) {
			s += val;
			a[i] = s * b[i];
		}
	return 0;
}

// %4.7

int s471(){

//	call statements

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
/*
// %4.8
void myexit(int ec)
{
  exit(ec);
}

int s481()
{

//	non-local goto's
//	stop statement

		for (int i = 0; i < LEN; i++) {
			if (d[i] < (TYPE)0.) {
				exit (0);
			}
			a[i] += b[i] * c[i];
		}
	return 0;
}
*/
// %4.8

// %4.8
int s482()
{

//	non-local goto's
//	other loop exit with code before exit

		for (int i = 0; i < LEN; i++) {
			a[i] += b[i] * c[i];
			if (c[i] > b[i]) break;
		}
	return 0;
}


int min(int a, int b){
  return (a < b) ? a : b;
}

// %4.9

int s491(int* __restrict__ ip)
{

//	vector semantics
//	indirect addressing on lhs, store in sequence
//	scatter is required

		for (int i = 0; i < LEN; i++) {
			a[ip[i]] = b[i] + c[i] * d[i];
		}
	return 0;
}

// %4.11

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

// %4.11

int s4113(int* __restrict__ ip)
{

//	indirect addressing
//	indirect addressing on rhs and lhs
//	gather and scatter is required

		for (int i = 0; i < LEN; i++) {
			a[ip[i]] = b[ip[i]] + c[i];
		}
	return 0;
}

// %4.11

int s4114(int* ip, int n1)
{

//	indirect addressing
//	mix indirect addressing with variable lower and upper bounds
//	gather is required

	int k;
		for (int i = n1-1; i < LEN; i++) {
			k = ip[i];
			a[i] = b[i] + c[LEN-k+1-2] * d[i];
			k += 5;
		}
	return 0;
}

// %4.11

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

// %4.11

int s4116(int* __restrict__ ip, int j, int inc)
{

//	indirect addressing
//	more complicated sparse sdot
//	gather is required

	TYPE sum;
	int off;
		sum = 0.;
		for (int i = 0; i < LEN2-1; i++) {
			off = inc + i;
			sum += a[off] * aa[j-1][ip[i]];
		}
	temp = sum;
	return 0;
}

// %4.11

int s4117()
{

//	indirect addressing
//	seq function

		for (int i = 0; i < LEN; i++) {
			a[i] = b[i] + c[i/2] * d[i];
		}
	return 0;
}

// %4.12

TYPE f(TYPE a, TYPE b){
	return a*b;
}

int s4121()
{

//	statement functions
//	elementwise multiplication

		for (int i = 0; i < LEN; i++) {
			a[i] += f(b[i],c[i]);
		}
	return 0;
}

// %5.1

int va()
{

//	control loops
//	vector assignment

		for (int i = 0; i < LEN; i++) {
			a[i] = b[i];
		}
	return 0;
}

// %5.1

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

// %5.1

int vas( int* __restrict__ ip)
{

//	control loops
//	vector assignment, scatter
//	scatter is required

		for (int i = 0; i < LEN; i++) {
			a[ip[i]] = b[i];
		}
	return 0;
}

// %5.1

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

// %5.1
/*
int vpv()
{

//	control loops
//	vector plus vector

		for (int i = 0; i < LEN; i++) {
			a[i] += b[i];
		}
	return 0;
}
*/
// %5.1

int vtv()
{

//	control loops
//	vector times vector

		for (int i = 0; i < LEN; i++) {
			a[i] *= b[i];
		}
	return 0;
}

// %5.1

int vpvtv()
{

//	control loops
//	vector plus vector times vector

		for (int i = 0; i < LEN; i++) {
			a[i] += b[i] * c[i];
		}
	return 0;
}

// %5.1

int vpvts( TYPE s)
{

//	control loops
//	vector plus vector times scalar

		for (int i = 0; i < LEN; i++) {
			a[i] += b[i] * s;
		}
	return 0;
}

// %5.1

int vpvpv()
{

//	control loops
//	vector plus vector plus vector

		for (int i = 0; i < LEN; i++) {
			a[i] += b[i] + c[i];
		}
	return 0;
}

// %5.1

int vtvtv()
{

//	control loops
//	vector times vector times vector

		for (int i = 0; i < LEN; i++) {
			a[i] = a[i] * b[i] * c[i];
		}
	return 0;
}

// %5.1
/*
int vsumr()
{

//	control loops
//	vector sum reduction

	TYPE sum;
		sum = 0.;
		for (int i = 0; i < LEN; i++) {
			sum += a[i];
		}
	return 0;
}
*/
// %5.1
/*
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
*/
// %5.1

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
int j;
int k, p;
 void doReversibleTransformation ( void )
 {
    int i;
 
    if (j >= 2) s121();
    j = j*2;
 
    s123();
 
    if (k >= 3)
    	s111();
 
    if (j > k) {
    	if(j >= p)
    			s000();
    	p++;
    	s111();
    	if(k > p)
    		s000();
    }
 
    j = -1;
    for (i = 0; i <= LEN; i++)
        if (a[i] == 0)
           { j = i; break; };
 
    if (j == -1) s121();
 }

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
/*
size_t strlen_vec( char * str ) {
  char * ptr ;
  ulong * longword_ptr ;
  ulong longword , himagic , lomagic ;
  for ( ptr = str ; (( ulong ) ptr & 7) != 0; ++ ptr ) 
    if (* ptr == '\0 ')
      return ptr - str ;
  longword_ptr = ( ulong *) ptr ;
  himagic = 0x8080808080808080L;
  lomagic = 0x0101010101010101L;
  for (;;) {
    longword = * longword_ptr ++;
    if (( longword - lomagic ) & ~ longword & himagic ){
      char * cp = ( char *)( longword_ptr - 1 );
      if ( cp [0] == 0) return cp - str ;
      if ( cp [1] == 0) return cp - str + 1 ;
      if ( cp [2] == 0) return cp - str + 2 ;
      if ( cp [3] == 0) return cp - str + 3 ;
      if ( cp [4] == 0) return cp - str + 4 ;
      if ( cp [5] == 0) return cp - str + 5 ;
      if ( cp [6] == 0) return cp - str + 6 ;
      if ( cp [7] == 0) return cp - str + 7 ;
    }
  }
}
*/
size_t strlen_ex1( char * s ) {
  char * p ;
  for ( p = s ; * p ; ++ p );
  return p - s ;
}

int main(){

	s000();
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

