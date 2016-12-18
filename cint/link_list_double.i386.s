.data
.text

.global _start
_start:
movl 8(%ebp), %edx
movl 8(%ebp), %eax
movl (%eax), %eax
sall %eax
movl %eax, (%edx)
movl 8(%ebp), %eax
movl 4(%eax), %eax
movl %eax, 8(%ebp)
cmpl $0, 8(%ebp)
jne _start
jmp _start
