.data				# data section
.text				# code section

.global _start
_start:
mov %eax, (%esp)
call f
addl $4, %esp
mov %eax, %ebx

f:
push %ebp
movl %esp, %ebp
push %edi
push %esi
push %ebx
sub $0x18, %esp
mov 8(%ebp), %eax
mov %eax, 8(%esp)
mov %eax, 4(%esp)
mov %eax, (%esp)
call 1f
add $0x18, %esp
jg  f
leal 8(%ebp), %eax
mov %eax, 8(%ebp)
pop %ebx
pop %esi
pop %edi
pop %ebp
jmp 1f
nop
mov %eax, %ebx
mov %eax, %ebx
mov %eax, %ebx
nop
call f




1:
mov  %esp, %ebp
movl 8(%ebp), %eax
fldl 4(%ebp)
#fldt 4(%ebp)
#fstpt 4(%ebp)
#fstpl 4(%ebp)
#faddl 4(%ebp)
#fcoml 4(%ebp)
#fcompl 4(%ebp)
#fdivl 4(%ebp)
#fdivrl 4(%ebp)
#fmull 4(%ebp)
#fsubl 4(%ebp)
#fsubrl 4(%ebp)
ret
