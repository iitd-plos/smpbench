# obtained from http://www.timestocome.com/personal/fibonacci.s
.data				# data section

output:
.ascii  "\n Fibonacci number is:  \0"
len = .- output-1		# length of ascii output string

msg0:
.ascii  "Less than hundred.\n\0"
len0 = . - msg0-1	    # length of our dear string

msg1:
.ascii  "Greater than hundred.\n\0"
len1 = . - msg1-1

msg2:
.ascii  "Equal to zero \n\0"
len2 = . - msg2-1


.text				# code section

.globl compute_fibo_iter
compute_fibo_iter:
cmpwi   7,3,2
mr      8,3
li      4,1
li      3,0
blelr   7
li      9,0
li      10,1
li      11,3
1: addi    11,11,1
cmpw    7,8,11
mr      0,4
addc    4,4,10
adde    3,3,9
mr      10,0
srawi   9,0,31
bge+    7,1b
blr

.global _sum8
_sum8:
mr.     0,4
mr      11,3
li      3,0
mtctr   0
blelr
li      9,0
1: lbzx    0,9,11
addi    9,9,1
add     3,3,0
bdnz+   1b
blr

.globl compute_fibo_rec
compute_fibo_rec:
cmpwi   7,3,2
stwu    1,-32(1)
mflr    0
stw     31,28(1)
stw     29,20(1)
mr      31,3
stw     30,24(1)
stw     0,36(1)
li      3,0
li      4,1
ble-    7,2f
li      29,0
li      30,0
1: addi    3,31,-1
addi    31,31,-2
bl      compute_fibo_rec
cmpwi   7,31,2
addc    30,30,4
adde    29,29,3
bgt+    7,1b
addic   4,30,1
2: addze   3,29
lwz     0,36(1)
lwz     29,20(1)
lwz     30,24(1)
lwz     31,28(1)
mtlr    0
addi    1,1,32
blr

.globl _start
_start:
lis 3,0
addi 3,3,0x10
bl compute_fibo_iter
li 0,1
li 3,1
sc
