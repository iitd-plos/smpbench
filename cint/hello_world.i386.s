.data
.global hw
.size hw,1
hw:
.string "Hello, world!\n"
len = . - hw    # length of our dear string
.text
.globl _start
.type _start, STT_FUNC
_start:
movl $100, %ecx    # put number of loops
_loop:
nop
pushl %ecx
movl  $4,%eax
movl  $1,%ebx
movl  $hw,%ecx
movl  $len,%edx
int $0x80
popl %ecx
decl %ecx
jne  _loop
movl  $1,%eax
xorl  %ebx,%ebx
int $0x80
ret
#nop
#je     hello 
#mov    -0x14(%ebp),%edx
#xor    %ecx,%ecx
#lea    0x3(%edx),%eax
#nop
#mov    -0x11(%ebp),%edx
#add    -0x3c(%ebp),%edx
#add    -0x4d(%ebx),%edx
#xchg   %ebx, %ebx
#mov    0x11(%ebp),%edx
#add    0x3c(%ebp),%edx
#add    0x113c(%ebx),%edx
#leal   0(%esi), %esi
#sub    %edx,%eax
#shr    $0x2,%eax
#add    $0x1,%eax
#mov    %eax,-0x40(%ebp)
#hello:
#mov    -0x18(%ebp),%edx
#mov    (%edx,%ecx,4),%eax
#retl   $0x4
#mov    %eax,(%esi,%ecx,4)
#.byte 0x31, 0x02, 0x0, 0xad, 0x31, 0x02, 0, 0x96, 0x31, 0x2, 0x0, 0x8b, 0x31, 0x2, 0x0, 0x87, 0x2f, 0x2, 0x0, 0x87, 0x2f, 0x2, 0x0, 0x82, 0x31,0x2
#add    $0x1,%ecx
#shll   $0x2, 0x10(%ebp)
#pop    %ebp
#jmp    hello
#nop
#call 1f
#1:nop
#pop %ebx
#nop
#sar %ebx
#nop
#cmp    -0x40(%ebp),%ecx
#jle    1f
#jg     _start
#1:jl     _start
#call   *hello
#.byte 0x8d, 0xb4, 0x26, 0, 0, 0, 0
#call   *0x8(%ebp)
#call   *%eax
#call   *%ecx
##jecxz  hello
#je     _start
