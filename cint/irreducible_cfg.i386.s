.global _start
.type _start, STT_FUNC
_start:
jne .i0
jmp .i1
.i0: jle .end
.i1: jmp .i0
.end: ret
