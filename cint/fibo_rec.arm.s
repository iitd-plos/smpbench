	.text
	.align	2
	.global	print_chr
	.type	print_chr, %function
print_chr:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r7, fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #8
	mov	r3, r0
	strb	r3, [fp, #-24]
	ldrb	r3, [fp, #-24]
	strb	r3, [fp, #-17]
	sub	r3, fp, #17
	mov %r0, $1
mov %r1, r3
mov %r2, $1
mov %r7, $4
swi $0

	sub	sp, fp, #16
	ldmfd	sp, {r7, fp, sp, pc}
	.size	print_chr, .-print_chr
	.align	2
	.global	print_int
	.type	print_int, %function
print_int:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #24
	str	r0, [fp, #-36]
	mov	r3, #0
	str	r3, [fp, #-20]
	mov	r3, #0
	str	r3, [fp, #-16]
.L4:
	ldr	r1, [fp, #-36]
	ldr	r3, .L10
	smull	r2, r3, r1, r3
	mov	r2, r3, asr #2
	mov	r3, r1, asr #31
	rsb	r2, r3, r2
	mov	r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, r2
	mov	r3, r3, asl #1
	rsb	r3, r3, r1
	str	r3, [fp, #-20]
	ldr	r1, [fp, #-36]
	ldr	r3, .L10
	smull	ip, r3, r1, r3
	mov	r2, r3, asr #2
	mov	r3, r1, asr #31
	rsb	r3, r3, r2
	str	r3, [fp, #-36]
	ldr	r0, [fp, #-16]
	ldr	r3, [fp, #-20]
	and	r3, r3, #255
	add	r3, r3, #48
	and	r3, r3, #255
	and	r1, r3, #255
	mvn	r2, #17
	sub	ip, fp, #12
	add	r3, ip, r0
	add	r2, r3, r2
	mov	r3, r1
	strb	r3, [r2, #0]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-36]
	cmp	r3, #0
	bne	.L4
	ldr	r3, [fp, #-16]
	sub	r3, r3, #1
	str	r3, [fp, #-16]
	b	.L6
.L7:
	ldr	r3, [fp, #-16]
	mvn	r2, #17
	sub	r1, fp, #12
	add	r3, r1, r3
	add	r3, r3, r2
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	mov	r0, r3
	bl	print_chr
	ldr	r3, [fp, #-16]
	sub	r3, r3, #1
	str	r3, [fp, #-16]
.L6:
	ldr	r3, [fp, #-16]
	cmp	r3, #0
	bge	.L7
	mov	r0, #10
	bl	print_chr
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L11:
	.align	2
.L10:
	.word	1717986919
	.size	print_int, .-print_int
	.align	2
	.global	fibonacci
	.type	fibonacci, %function
fibonacci:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #8
	str	r0, [fp, #-20]
	ldr	r3, [fp, #-20]
	cmp	r3, #0
	bne	.L13
	mov	r3, #0
	str	r3, [fp, #-24]
	b	.L15
.L13:
	ldr	r3, [fp, #-20]
	cmp	r3, #1
	bne	.L16
	mov	r3, #1
	str	r3, [fp, #-24]
	b	.L15
.L16:
	ldr	r3, [fp, #-20]
	sub	r3, r3, #1
	mov	r0, r3
	bl	fibonacci
	mov	r4, r0
	ldr	r3, [fp, #-20]
	sub	r3, r3, #2
	mov	r0, r3
	bl	fibonacci
	mov	r3, r0
	add	r4, r4, r3
	str	r4, [fp, #-24]
.L15:
	ldr	r3, [fp, #-24]
	mov	r0, r3
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
	.size	fibonacci, .-fibonacci
	.align	2
	.global	_start
	.type	_start, %function
_start:
	@ args = 0, pretend = 0, frame = 4
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #4
	mov	r3, #0
	str	r3, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L20
.L21:
	ldr	r0, [fp, #-16]
	bl	fibonacci
	mov	r3, r0
	mov	r0, r3
	bl	print_int
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L20:
	ldr	r3, [fp, #-16]
	cmp	r3, #19
	ble	.L21
	
  mov r0, $0
  mov r7, $1
  swi $0
 
	ldmfd	sp, {r3, fp, sp, pc}
