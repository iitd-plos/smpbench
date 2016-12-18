.data

msg:
  .ascii  "Hello, world!\n"
len = . - msg

.text
.globl _start
_start:
  mov %r3, $0
l1:
  mov  %r0, $1      /* fd -> stdout */
  ldr  %r1, =msg    /* buf -> msg */
  ldr  %r2, =len    /* count -> len(msg) */
  mov %r7, $4       /* write is syscall #4 */
  swi $0            /* invoke syscall */
  add %r3,%r3,$1
  cmp %r3, $5
  ble l1
  /* syscall exit(int status) */
  mov %r0, $0      /* status -> 0 */
  mov %r7, $1      /* exit is syscall #1 */
  swi $0
