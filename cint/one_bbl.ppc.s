.data				# data section

msg0:
.ascii  "bit is set\n\0"
len0 = . - msg0-1	    # length of our dear string

.text				# code section

.global _start
_start:
dcbz 0,9
addic 9,0,-1
dcbz 1,9
bl 1f
bl 2f
cmpwi 9,8
bne _start
1: bne _start
2: bne _start
#srw 0,8,11
#add 1,2,3
#crxor 4*cr7+so,4*cr7+eq,4*cr7+lt
#mtcr 1
#mfcr 2
#cmpwi 1,9,0
#beq _start
#divwuo. 1,2,3
#dcbz 7,6
#rlwinm 1,1,0,0,27
#stfd 14,-144(11)
#rlwimi 0,9,31,0,0
#dcbz 0,6
#rlwimi 4,4,8,16,23
#mtcrf 15,12
#bcl- 20,4*cr7+so,_start
#bdnz+ _start
#cmpwi 9,0
#sc
#lwarx 11,0,9
#rlwimi 1,2,3,7,9
#rlwimi 1,2,3,1,30
#cror    4*cr7+so,4*cr7+eq,4*cr7+lt
#rlwimi 9,7,0x1b,4,4
#lwz 1,0(2)
#lwz 1,4(3)
#lwz 1,153(3)
#lwz 1,157(3)
#lwz 1,162(3)
b _start
