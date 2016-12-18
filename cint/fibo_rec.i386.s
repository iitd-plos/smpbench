.data
lessthan:
  .string "Less than 0x1000.\n"
len_lt = . - lessthan - 1
greaterthan:
  .string "Greater than 0x1000.\n"
len_gt = . - greaterthan - 1

.text
.globl compute_fibo_rec
# fib(n) = fib(n-1) + fib(n-2)
compute_fibo_rec:
  pushl %ebp
  xor   %edx, %edx
  movl  %esp, %ebp
  pushl %edi
  pushl %esi
  pushl %ebx
  movl  %eax, %ebx
  cmpl  $0x2, %ebx
  movl  $0x1, %eax
  jle   2f
  xor   %esi, %esi
  xor   %edi, %edi
1:lea   -0x1(%ebx), %eax
  sub   $0x2, %ebx
  call  compute_fibo_rec
  add   %eax, %esi
  adc   %edx, %edi
  cmp   $2, %ebx
  jg    1b
  movl  %esi, %eax
  movl  %edi, %edx
  add   $1, %eax
  adc   $0, %edx
2:pop   %ebx
  pop   %esi
  pop   %edi
  pop   %ebp
  ret

.globl _start
_start:
  movl $10, %eax
  push %eax
  call compute_fibo_rec
  cmpl $0x1000, %eax
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
