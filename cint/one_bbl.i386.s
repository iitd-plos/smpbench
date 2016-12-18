.global _f2
.type _f2, STT_FUNC
_f2:
call .i804d620
ret

.global _start
.type _start, STT_FUNC
_start:
.i804d5d0: sub    $0x2c,%esp
.i804d5d3: mov    0x34(%esp),%eax
.i804d5d7: movl   $0x80c8bd4,0x8(%esp)
.i804d5df: movl   $0x1,0x4(%esp)
.i804d5e7: mov    %eax,0x14(%esp)
jecxz .i804d615
.i804d5eb: mov    0x30(%esp),%eax
.i804d5ef: mov    %eax,0x10(%esp)
.i804d5f3: mov    0x8100be4,%eax
.i804d5f8: mov    %eax,0xc(%esp)
.i804d5fc: mov    0x80f711c,%eax
.i804d601: mov    %eax,(%esp)
.i804d604: call   _f2
.i804d60e: movl   $0x1,(%esp)
.i804d615: call   _f2
.i804d61a: lea    0x0(%esi),%esi

.global _f1
.type _f1, STT_FUNC
_f1:
.i804d620: push   %ebp
.i804d621: push   %edi
.i804d622: push   %esi
.i804d623: push   %ebx
ret

