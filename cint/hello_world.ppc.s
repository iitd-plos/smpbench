.data                       # section declaration - variables only
msg:
.string "Hello, world!\n"
len = . - msg       # length of our dear string

.text                       # section declaration - begin code

.global _start
.type _start, STT_FUNC
_start:

# write our string to stdout

li      9, 100     # put number of loops
nop

_loop:
li      0,4         # syscall number (sys_write)
li      3,1         # first argument: file descriptor (stdout)

# second argument: pointer to message to write
lis     4,msg@ha    # load top 16 bits of &msg
addi    4,4,msg@l   # load bottom 16 bits
li      5,len       # third argument: message length
sc                  # call kernel
subi    9,9,1
cmpwi   9, 0
bgt     _loop

# and exit
li      0,1         # syscall number (sys_exit)
li      3,1         # first argument: exit code
sc                  # call kernel
blr
