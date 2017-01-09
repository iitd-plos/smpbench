#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>
//#include <sys/times.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
//#include "common.h"
//#include "rsa.h"


#define ASSERT assert
#define TRUE	1
#define FALSE	0
#define NOT_IMPLEMENTED() assert(0)


/*
* generate a public key and exponent suitable for RSA encryption like this:
* % openssl genrsa -out foo.rsa <numbits>
* % openssl rsa -in foo.rsa -pubout | openssl rsa -pubin -noout -text
*   <will output n and e>
*/
#define KEYLEN 4
uint16_t n[KEYLEN];
uint16_t e[2];
uint16_t plaintext[KEYLEN];

/* would be nice if we could use malloc instead of globals here */
uint16_t _tmpglobal_ab[2 * KEYLEN];
uint16_t _tmpglobal_q[KEYLEN];
uint16_t _tmpglobal_x[2 * KEYLEN];
uint16_t _tmpglobal_ybnt[2 * KEYLEN];
uint16_t _tmpglobal_ybit[2 * KEYLEN];
uint16_t _tmpglobal_qitybit[2 * KEYLEN];
uint16_t _tmpglobal_temp[KEYLEN];

#define CP_MAGIC 7524


void check_pt(int magic, int num_NV, int num_V, ...)
{
	printf("Inside Check Point -- Num NV vars = %d Num V vars = %d \n", num_NV, num_V);
}

#define CHECKPOINT check_pt(CP_MAGIC, 0, 0)

/**
* One word addition with a carry bit
* c_i = (a_1 + b_i + epsilon_prime) mod 0xFFFF
*/
#define add_word(c_i, a_i, b_i, epsilon_prime) ({ \
	uint16_t epsilon; \
	*c_i = (a_i + b_i + epsilon_prime);  \
  \
	if ((*c_i >= (a_i + epsilon_prime)) && (*c_i >= b_i)) { \
		epsilon = 0;  \
	}  \
	else {  \
		epsilon = 1;  \
	}  \
	epsilon;  \
} )

/**
* One word subtraction with a borrow bit
* c_i = (a_1 - b_i - epsilon_prime) mod 0xFFFF
*/
#define subtract_word( c_i, a_i, b_i, epsilon_prime) ({  \
	uint8_t epsilon;  \
	*c_i = (a_i - b_i - epsilon_prime);  \
	if (0xFFFF == b_i) {  \
		epsilon = 1;  \
	}  \
	else {  \
		if (a_i < b_i) {  \
			epsilon = 1;  \
		}  \
		else {  \
			epsilon = 0;  \
		}  \
	}  \
  \
	epsilon;  \
})

/**
* Multiprecision addition c.f. Alg. 2.5
* Input: a, b \in [0,2^{Wt})
* Output: (epsilon, c) where c = a + b mod 2^{Wt} and epsilon is the carry bit
*/
#define add_mp_elements(pfe_c, pfe_a, pfe_b, wordlength) ({  \
	uint16_t epsilon;  \
	int i; \
	epsilon = add_word(&pfe_c[0], pfe_a[0], pfe_b[0], 0);  \
	for (i = 1; i < wordlength; i++) {  \
		epsilon = add_word(&pfe_c[i], pfe_a[i], pfe_b[i], epsilon);  \
	}  \
	epsilon;  \
})

/**
* Multiprecision subtraction c.f. Alg. 2.6
* Input: a, b \in [0,2^{Wt})
* Output: (epsilon, c) where c = a - b mod 2^{Wt} and epsilon is the borrow bit
*/
#define subtract_mp_elements( pfe_c, pfe_a, pfe_b, wordlength) ({  \
	uint16_t epsilon;  \
	int i;   \
	epsilon = subtract_word(&pfe_c[0], pfe_a[0], pfe_b[0], 0);  \
	for (i = 1; i < wordlength; i++) {  \
		epsilon = subtract_word(&pfe_c[i], pfe_a[i], pfe_b[i], epsilon);  \
	}  \
	epsilon;  \
})


/**
* Compares two big nums
* Returns 1 if a >= b 0 otherwise
*/
#define compare_mp_elements( a, b, wordlength) ({  \
	int i, result; \
	for (i = wordlength - 1; i > -1; i--) {  \
		if (a[i] < b[i]) {  \
			result =  0;  \
		}  \
		else if (a[i] >= b[i]) {  \
			result = 1;  \
		}  \
	}  \
	result;  \
})




/**
* Addition in F_p c.f. Alg. 2.7
* Input: a, b \in [0,p-1)
* Output: c = a + b mod p
*/
#define add_mod_p( c, a, b, p, wordlength) ({  \
	uint8_t epsilon;  \
	epsilon = add_mp_elements(c, a, b, wordlength);  \
	if (1 == epsilon) {  \
		subtract_mp_elements(c, c, p, wordlength);  \
	}  \
	else {  \
		if (1 == compare_mp_elements(c, p, wordlength)) {  \
			subtract_mp_elements(c, c, p, wordlength);  \
		}  \
	}  \
})

/**
* subtraction in F_p c.f. Alg. 2.8
* Input: a, b \in [0,p-1)
* Output: c = a - b mod p
*/
#define subtract_mod_p( c, a, b, p, wordlength) ({  \
	uint8_t epsilon;   \
	epsilon = subtract_mp_elements(c, a, b, wordlength);  \
	if (1 == epsilon) {  \
		add_mp_elements(c, c, p, wordlength);  \
	}  \
})

/**
* Sets a bn to zero
*/
#define set_to_zero(c, wordlength) ({  \
	int i;  \
	for (i = 0; i < wordlength; i++) {  \
		c[i] = 0x0000;  \
	}  \
})

/**
* Multiply two single words into a double word
* Input: a,b words
* Output: uv one 2-word
*/
#define multiply_words( a, b, uv) ({  \
	uint32_t uv_32;  \
	uint16_t u, v;  \
	uv_32 = ((uint32_t)a) * ((uint32_t)b);  \
	u = (uint16_t)(uv_32 >> 16);  \
	v = (uint16_t)uv_32;  \
	uv[1] = u;  \
	uv[0] = v;  \
})

/**
* Multiply two single words into a double word
* Input: a,b words
* Output: uv one 2-word
*/
#define multiply_words_2( a, b, uv) ({  \
	uint16_t a0, a1, b0, b1;  \
	uint16_t t[2];  \
	uint16_t s[2];  \
	uint16_t m;  \
	uint16_t borrow;  \
  \
	a0 = (a & 0xFF00) >> 8;  \
	a1 = a & 0x00FF;  \
	b0 = (b & 0xFF00) >> 8;  \
	b1 = b & 0x00FF;  \
  \
	m = a1 * b1;  \
	t[0] = m & 0x00FF;  \
	borrow = (m & 0xFF00) >> 8;  \
  \
	m = a0 * b1 + borrow;  \
	t[0] ^= ((m & 0x00FF) << 8);  \
	t[1] = ((m & 0xFF00) >> 8);  \
  \
	m = a1*b0;  \
	s[0] = (m & 0x00FF) << 8;  \
	borrow = (m & 0xFF00) >> 8;  \
  \
	m = a0 * b0 + borrow;  \
	s[1] = m;  \
  \
	add_mp_elements(uv, s, t, 2);  \
})

/**
* Multiprecision Multiplication c.f. Alg. 2.9
* Input: a, b \in [0,p-1]
* Output: c = a*b
*/
#define multiply_mp_elements( c, a, b, wordlength) ({  \
	uint16_t UV[2];  \
	uint16_t temp1[2];  \
	uint16_t temp2[2];  \
  \
	int i, j;  \
	set_to_zero(c, 2 * wordlength);  \
	set_to_zero(UV, 2);  \
	for (i = 0; i < wordlength; i++) {  \
		UV[1] = 0;  \
		for (j = 0; j < wordlength; j++) {  \
			temp2[0] = UV[1];  \
			temp2[1] = 0x0000;  \
			multiply_words(a[i], b[j], UV);  \
			temp1[0] = c[i + j];  \
			temp1[1] = 0x0000;  \
			add_mp_elements(UV, UV, temp1, 2);  \
			add_mp_elements(UV, UV, temp2, 2);  \
			c[i + j] = UV[0];  \
		}  \
		c[i + wordlength] = UV[1];  \
	}  \
})

/**
* Multiprecision Multiplication c.f. Alg. 2.9
* Input: a, b \in [0,p-1]
* Output: c = a*b
*/
#define multiply_mp_elements2( c, a, wordlength_a, b, wordlength_b) ({  \
	uint16_t UV[2];  \
	uint16_t temp1[2];  \
	uint16_t temp2[2];  \
  \
	int i, j;  \
	set_to_zero(c, wordlength_a + wordlength_b);  \
	set_to_zero(UV, 2);  \
	for (i = 0; i < wordlength_b; i++) {  \
		UV[1] = 0;  \
		for (j = 0; j < wordlength_a; j++) {  \
			temp2[0] = UV[1];  \
			temp2[1] = 0x0000;  \
			multiply_words(a[i], b[j], UV);  \
			temp1[0] = c[i + j];  \
			temp1[1] = 0x0000;  \
			add_mp_elements(UV, UV, temp1, 2);  \
			add_mp_elements(UV, UV, temp2, 2);  \
			c[i + j] = UV[0];  \
		}  \
		c[i + wordlength_b] = UV[1];  \
	}  \
})


/**
Multiply by a power of b
* out = a*b^k
*/
#define mult_by_power_of_b(out, wordlength_out, a, wordlength_a, k) ({  \
	int i = 0;  \
	set_to_zero(out, wordlength_out);  \
  \
	while (i + k < wordlength_out) {  \
		if (i<wordlength_a) {  \
			out[i + k] = a[i];  \
		}  \
		i++;  \
	}  \
})

#define mod_pow_of_b(out, wordlength_out, a, wordlength_a, k) ({  \
	int i;  \
	while (i < wordlength_out) {  \
		if (i < wordlength_a) {  \
			out[i] = a[i];  \
		}  \
		else {  \
			out[i] = 0;  \
		}  \
		i++;  \
	}  \
})

/*
Divide by a power of b
*/
#define div_by_power_of_b(out, out_len, a, a_len, k) ({  \
	int i;  \
	set_to_zero(out, out_len);  \
	if (out_len + 1 > a_len - k) {  \
		for (i = 0; i < out_len; i++) {  \
			if (k + i<a_len) {  \
				out[i] = a[k + i];  \
			}  \
		}  \
	}  \
})

/**
* @param c An output BigNum such that c = a * b
* @param a A 16-bit unsigned integer
* @param b A BigNum of size wordlength_b in 16-bit words.
* @param wordlength_b
*/
#define multiply_sp_by_mp_element(c, a, b, wordlength_b) ({  \
	uint32_t uv;  \
	uint16_t u;  \
	uint16_t v;  \
	uint16_t carry;  \
	int j;  \
	set_to_zero(c, wordlength_b + 1);  \
	uv = 0;  \
    carry = 0;  \
for (j = 0; j < wordlength_b; j++) {  \
	\
		uv = ((uint32_t)a) * ((uint32_t)b[j]) + ((uint32_t)carry);  \
		u = (uint16_t)(uv >> 16);  \
		v = (uint16_t)uv;  \
		c[j] = v;  \
		carry = u;  \
}  \
c[wordlength_b] = carry;  \
})

#define are_mp_equal( a, b, wordlength) ({  \
	int i = 0;  \
	int answ = 1;  \
	while ((1 == answ) && (i<wordlength)) {  \
		if (a[i] != b[i]) {  \
			answ = 0;  \
		}  \
		i++;  \
	}  \
	answ;  \
})

#define copy_mp( out, in, wordlength) ({  \
	int i;  \
	for (i = 0; i< wordlength; i++) {  \
		out[i] = in[i];  \
	}  \
})

#define ith_bit(e, i) ({  \
	uint16_t mask;  \
    int result;  \
	mask = 0x0001 << i;  \
	mask = e & mask;  \
	if (0x0000 == mask) {  \
		result = 0;  \
	}  \
	else {  \
	    result = 1;  \
	}  \
	result;  \
})

#define bit_length(e) ({  \
	int i = 15; \
	int found_one = 0;  \
	while (0 == found_one) {  \
		if (1 == ith_bit(e, i)) {  \
			found_one = 1;  \
		}  \
		else {  \
			i--;  \
		}  \
	}  \
	i;  \
})

#define mp_bit_length(e, wordlength) ({  \
	int i = wordlength - 1;  \
	int length;  \
	int last_non_zero_word = -1;  \
	while ((i>-1) && (last_non_zero_word < 0)) {  \
		if (0 != e[i]) {  \
			last_non_zero_word = i;  \
		}  \
		i--;  \
	}  \
	length = 16 * last_non_zero_word + bit_length(e[last_non_zero_word]);  \
	length;  \
})

#define mp_ith_bit( e, i) ({  \
	uint16_t word;  \
	uint16_t word_bit;  \
  \
	word = (int)i / 16;  \
	word_bit = ith_bit(e[word], i - word * 16);  \
	word_bit;  \
})

#define mp_non_zero_words(e, wordlength) ({  \
	int i = wordlength - 1;  \
	int last_non_zero_word = -1;  \
	while ((i>-1) && (last_non_zero_word < 0)) {  \
		if (0 != e[i]) {  \
			last_non_zero_word = i;  \
		}  \
		i--;  \
	}  \
	last_non_zero_word;  \
})

/*
Returns floor((x1*(0xFFFF) + x0)/y)
*/
#define divide_2_word_by_1_word(x1, x0, y) ({  \
	uint32_t result;  \
	if (0 != y) {  \
		result = (((uint32_t)x1) << 16);  \
		result = result + (uint32_t)x0;  \
		result = (result) / ((uint32_t)y);  \
	}  \
	else {  \
		result = 0;  \
	}  \
  result;\
})


/**
* Multiprecision Division c.f. Alg. 14.20 Handbook of Applied Crypto (Menezes, et.al.)
* Input: x = (x_n . . . x_1 x_0)_b, y = (y_t . . . y_1 y_0)_b with n >= t > 1, y_t != 0
* Output: q = (q_{n-t} . . . q_1 q_0)_b, r = (r_t . . . r_1 r_0)_b
* such that x = qy +r, 0 \leq r < y.
*/
#define divide_mp_elements( q, r, x_in, n, y, t) ({  \
	int i, j, k;  \
	uint16_t temp_ls[2];  \
	uint16_t ls[3];  \
	uint16_t rs[3];  \
	uint16_t temp;  \
	for (i = 0; i < n; i++)  \
		_tmpglobal_x[i] = x_in[i];  \
	for (j = 0; j <= n - t; j++) {  \
		q[j] = 0x0000;  \
	}  \
	mult_by_power_of_b(_tmpglobal_ybnt, n, y, t, n - t);  \
	while (1 == compare_mp_elements(_tmpglobal_x, _tmpglobal_ybnt, (int)n)) {  \
		q[n - t] = q[n - t] + 1;  \
		subtract_mp_elements(_tmpglobal_x, _tmpglobal_x, _tmpglobal_ybnt, n);  \
	}  \
	for (i = n - 1; i > t - 1; i--) {   \
		temp = _tmpglobal_x[i] - y[t - 1];  \
		if (0 == temp) {  \
			q[i - t] = 0xFFFF;   \
		}  \
		else {  \
			q[i - t] = divide_2_word_by_1_word(_tmpglobal_x[i], _tmpglobal_x[i - 1], y[t - 1]);  \
		}  \
		temp_ls[0] = y[t - 2];  \
		temp_ls[1] = y[t - 1];  \
		multiply_sp_by_mp_element(ls, q[i - t], temp_ls, 2);  \
		rs[0] = _tmpglobal_x[i - 2];  \
		rs[1] = _tmpglobal_x[i - 1];  \
		rs[2] = _tmpglobal_x[i];  \
		while (0 == compare_mp_elements(rs, ls, 3)) {  \
			q[i - t] = q[i - t] - 1;  \
			multiply_sp_by_mp_element(ls, q[i - t], temp_ls, 2);  \
		}  \
		mult_by_power_of_b(_tmpglobal_ybit, n, y, t, i - t);  \
		multiply_sp_by_mp_element(_tmpglobal_qitybit, q[i - t], _tmpglobal_ybit, n);  \
		if (0 == compare_mp_elements(_tmpglobal_x, _tmpglobal_qitybit, n)) {  \
			add_mp_elements(_tmpglobal_x, _tmpglobal_x, _tmpglobal_ybit, n);  \
			subtract_mp_elements(_tmpglobal_x, _tmpglobal_x, _tmpglobal_qitybit, n);  \
			q[i - t] = q[i - t] - 1;  \
		}  \
		else {  \
			subtract_mp_elements(_tmpglobal_x, _tmpglobal_x, _tmpglobal_qitybit, n);  \
		}  \
		for (k = 0; k < t; k++) {  \
			r[k] = _tmpglobal_x[k];  \
		}  \
	}  \
})


/**
* Multiplication in F_p
* Input: a, b \in [0,p-1)
* Output: c = a * b mod p
*/
#define multiply_mod_p(c, a, b, p, wordlength) ({  \
	multiply_mp_elements(_tmpglobal_ab, a, b, wordlength);  \
	CHECKPOINT;  \
	divide_mp_elements(_tmpglobal_q, c, _tmpglobal_ab, 2 * wordlength, p, wordlength);  \
})

/**
* Implementation of the left to right modular exponentiation algorithm
* as described in the HAC book by Menezes et.al.
*
* @param A The result of raising g to the power of e
* @param g an element of Z*_p
* @param e a multi-precission exponent
* @param e_legth the wordlength of the multi-precission exponent
*/

#define mod_exp(A, g, e, e_length, p, p_length) ({  \
	int i;  \
	int t = mp_bit_length(e, e_length);  \
	set_to_zero(A, p_length);  \
	A[0] = 1;  \
	for (i = t; i >= 0; i--) {  \
		CHECKPOINT;  \
		multiply_mod_p(_tmpglobal_temp, A, A, p, p_length);  \
		copy_mp(A, _tmpglobal_temp, p_length);  \
	if (1 == mp_ith_bit(e, i)) {  \
			CHECKPOINT;  \
			multiply_mod_p(_tmpglobal_temp, A, g, p, p_length);  \
			copy_mp(A, _tmpglobal_temp, p_length);  \
		}  \
	}  \
})

#define test_rsa_encrypt() ({  \
  \
	uint16_t ciphertext[KEYLEN];  \
	CHECKPOINT;  \
	mod_exp(ciphertext, plaintext, e, 1, n, KEYLEN);  \
})


int main_RSA64()
{
	//	WDTCTL = WDTPW + WDTHOLD; // stop WDT

	/* see above comment about generating these */
	n[0] = 0xab78; n[1] = 0xafba; n[2] = 0x88e7; n[3] = 0x496d;
	e[0] = 0x0001; e[1] = 0x0001; // e = 65537

	plaintext[0] = 0x4d65; // Me
	plaintext[1] = 0x6d65; // me
	plaintext[2] = 0x6e74; // nt
	plaintext[3] = 0x6f73; // os

	test_rsa_encrypt();
	//	asm volatile ("NOP");
	return 11;

}


int main(int argc, char **argv)
{
	printf("main_RSA64() = %d\n", main_RSA64());
	return 1;
}
