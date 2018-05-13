.global _f2
.type _f2, STT_FUNC
_f2:
ret

.global _start
.type _start, STT_FUNC
_start:
jne _f1
jmp _start

.global _f1
.type _f1, STT_FUNC
_f1:
ret
