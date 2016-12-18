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

.globl _fibonacci
.type _fibonacci, STT_FUNC
_fibonacci:
#lis      3, 10000	# put number of loops   ( num loops +2 is fib num position )
li      3, 10		# put number of loops   ( num loops +2 is fib num position )
li      7, 1		# put 1 into register 7 ( prime loop first fib number )
li      8, 1		# put 1 into register 8 ( prime loop second fib number )
li 9, 1			# XXX: dummy

fib_loop:
add     11, 7, 8     # add the values in registers r7, r8 and store in r11
mr      7, 8		# move r8's value to r7 ( shift numbers for next loop )
mr      8, 11		# move r11's value to r8 ( set up for next loop )
subi    3, 3, 1       # r3--  ( decrement loop counter )
cmpwi   3, 0           # compare r3 with zero  ( are we done with loop? )
bgt     fib_loop	# if r3 greater than 0 repeat fib_loop


# dump output  

li      0, 4		# syscall number ( system write )
li      3, 1		# first arg stdout
lis     4, output@ha	# first half of string
addi    4, 4, output@l  # second half of string
li      5, len		# message length
lbz     18,0(4)		# XXX: dummy
mr      19,20		# XXX: dummy
mr      21,22		# XXX: dummy
mr	22,9		# XXX: dummy
sc			# call kernel

# return fib number
xor.    3, 3, 3      # zero out register 3
mr      3, 11

#exit
blr				#branch to instruction register ( exit )

.globl _start
.type _start, STT_FUNC
_start:
bl	_fibonacci
cmpwi	3,100
bge	cr0, greaterthan
li	0, 4
li	3, 1
lis	4, msg0@ha
addi	4, 4, msg0@l
li	5, len0
sc
b       done

greaterthan:
li      0, 4		    # syscall number (sys_write)
li      3, 1		    # first argument: file descriptor (stdout)
# second argument: pointer to message to write
lis     4, msg1@ha 	   # load top 16 bits of &msg
addi    4, 4,msg1@l      # load bottom 16 bits
li      5, len1	    # third argument: message length
sc			    # call kernel
b       done

# and exit
done:
li      0, 1		    # syscall number (sys_exit)
li      3, 1		    # first argument: exit code
sc			    # call kernel
