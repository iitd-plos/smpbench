.data				# data section
.text				# code section

.global _start
_start:
movl $1, %eax
1: movzbl (%edx,%edi,1),%eax
inc    %edx
add    %eax,%ecx
cmp    %edx,%esi
jg     1b
nop
