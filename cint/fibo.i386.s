.data
output:
.ascii  "\n Fibonacci number is:  \0"
len_output = .- output-1		# length of ascii output string
lessthan:
  .string "Less than hundred.\n"
len_lt = . - lessthan - 1
greaterthan:
  .string "Greater than hundred.\n"
len_gt = . - greaterthan - 1
.text
.globl _fibonacci
.type _fibonacci, STT_FUNC
# fib(n) = fib(n-1) + fib(n-2)
  nop
  nop
  nop
_fibonacci:
  pushl %ebp
  movl %esp,%ebp
  pushl %esi
  pushl %edx  /* <-- PUSH TO SAVE BEFORE CLOBBERING */
  movl 8(%ebp),%esi

  # 0th and 1st numbers are defined to be 1.
  cmpl $1,%esi
  jle BASE

  # find fib(n-1)
  subl $1,%esi
  pushl %esi
  call _fibonacci

  addl $4,%esp
  movl %eax,%edx  # <-- %edx CLOBBERED!

  # find fib(n-2)
  subl $1,%esi
  pushl %esi
  call _fibonacci

  addl $4,%esp
  addl %edx,%eax

DONE:
  popl %edx  # <-- POP TO RESTORE AFTER CLOBBERING
  popl %esi
  popl %ebp
  ret

BASE:
  movl $1,%eax
  jmp DONE

.globl _start
.global print
.type _start, STT_FUNC
_start:
  pushl $11
  call 1f
  1: addl $4, %esp
#call _fibonacci
  movl $_fibonacci, %eax
  call *%eax
  addl $4, %esp
  pushl %eax
  movl $output, %ecx
  movl $len_output, %edx
  movl $4, %eax
  movl $1, %ebx
  int $0x80
  popl %eax
  cmpl $100, %eax
  jge  pgreaterthan
  movl $lessthan, %ecx
  movl $len_lt, %edx
  jmp print
pgreaterthan:
  movl $greaterthan, %ecx
  movl $len_gt, %edx
print:
  movl $4, %eax
  movl $1, %ebx
  int $0x80

  #Exit
  movl  $1,%eax
  xorl  %ebx,%ebx
  int $0x80
  ret
