	.data
	.global a
a:
	.zero 120000040
	.data
	.global ans
ans:
	.word 0
	.section .rodata
	.global base
base:
	.word 16
	.text
	.global getMaxNum
getMaxNum:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	li	a2,0
	mv	a4,a2
	li	a2,0
	mv	a5,a2
	j	.L2
.L2:
	blt	a4,a0, .L3
	j	.L4
.L3:
	mv	a2,a4
	slli	a6,a2,2
	mv	a2,a6
	add	a3,a1,a2
	mv	a2,a5
	lw	a3,0(a3)
	bgt	a3,a5, .L5
	j	.L7
.L5:
	mv	a2,a6
	add	a2,a1,a2
	lw	a2,0(a2)
	j	.L7
.L7:
	addi	a3,a4,1
	mv	a4,a3
	mv	a5,a2
	j	.L2
.L4:
	mv	a0,a5
	j	.L8
.L8:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
	.text
	.global getNumPos
getNumPos:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	li	a2,0
	j	.L10
.L10:
	blt	a2,a1, .L11
	j	.L12
.L11:
	srai	a0,a0,4
	addi	a2,a2,1
	j	.L10
.L12:
	li	a1,16
	rem	a0,a0,a1
	j	.L13
.L13:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
	.text
	.global radixSort
radixSort:
	addi	sp,sp,-80
	sd	ra,72(sp)
	sd	s0,64(sp)
	sd	s8,56(sp)
	sd	s7,48(sp)
	sd	s6,40(sp)
	sd	s5,32(sp)
	sd	s4,24(sp)
	sd	s3,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,80
	addi	sp,sp,-192
	li	a4,0
	sw	a4,-144(s0)
	li	a4,0
	sw	a4,-140(s0)
	li	a4,0
	sw	a4,-136(s0)
	li	a4,0
	sw	a4,-132(s0)
	li	a4,0
	sw	a4,-128(s0)
	li	a4,0
	sw	a4,-124(s0)
	li	a4,0
	sw	a4,-120(s0)
	li	a4,0
	sw	a4,-116(s0)
	li	a4,0
	sw	a4,-112(s0)
	li	a4,0
	sw	a4,-108(s0)
	li	a4,0
	sw	a4,-104(s0)
	li	a4,0
	sw	a4,-100(s0)
	li	a4,0
	sw	a4,-96(s0)
	li	a4,0
	sw	a4,-92(s0)
	li	a4,0
	sw	a4,-88(s0)
	li	a4,0
	sw	a4,-84(s0)
	li	a4,0
	sw	a4,-208(s0)
	li	a4,0
	sw	a4,-204(s0)
	li	a4,0
	sw	a4,-200(s0)
	li	a4,0
	sw	a4,-196(s0)
	li	a4,0
	sw	a4,-192(s0)
	li	a4,0
	sw	a4,-188(s0)
	li	a4,0
	sw	a4,-184(s0)
	li	a4,0
	sw	a4,-180(s0)
	li	a4,0
	sw	a4,-176(s0)
	li	a4,0
	sw	a4,-172(s0)
	li	a4,0
	sw	a4,-168(s0)
	li	a4,0
	sw	a4,-164(s0)
	li	a4,0
	sw	a4,-160(s0)
	li	a4,0
	sw	a4,-156(s0)
	li	a4,0
	sw	a4,-152(s0)
	li	a4,0
	sw	a4,-148(s0)
	li	a4,0
	sw	a4,-272(s0)
	li	a4,0
	sw	a4,-268(s0)
	li	a4,0
	sw	a4,-264(s0)
	li	a4,0
	sw	a4,-260(s0)
	li	a4,0
	sw	a4,-256(s0)
	li	a4,0
	sw	a4,-252(s0)
	li	a4,0
	sw	a4,-248(s0)
	li	a4,0
	sw	a4,-244(s0)
	li	a4,0
	sw	a4,-240(s0)
	li	a4,0
	sw	a4,-236(s0)
	li	a4,0
	sw	a4,-232(s0)
	li	a4,0
	sw	a4,-228(s0)
	li	a4,0
	sw	a4,-224(s0)
	li	a4,0
	sw	a4,-220(s0)
	li	a4,0
	sw	a4,-216(s0)
	li	a4,0
	sw	a4,-212(s0)
	li	a4,-1
	beq	a0,a4, .L19
	j	.L18
.L19:
	addi	sp,sp,192
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s3,16(sp)
	ld	s4,24(sp)
	ld	s5,32(sp)
	ld	s6,40(sp)
	ld	s7,48(sp)
	ld	s8,56(sp)
	ld	s0,64(sp)
	ld	ra,72(sp)
	addi	sp,sp,80
	ret
.L18:
	addi	a4,a2,1
	bge	a4,a3, .L19
	j	.L17
.L17:
	mv	a4,a2
	mv	s1,a4
	j	.L20
.L20:
	blt	s1,a3, .L21
	j	.L22
.L21:
	mv	a4,s1
	slli	s3,a4,2
	mv	a4,s3
	add	a4,a1,a4
	mv	s5,a1
	mv	a1,a0
	lw	a4,0(a4)
	mv	s4,a3
	mv	s6,a2
	mv	s2,a0
	mv	a0,a4
	call	getNumPos
	mv	a1,s5
	mv	a2,s6
	mv	a3,s4
	mv	a4,a0
	mv	a0,s2
	slli	a4,a4,2
	addi	a4,a4,-272
	add	a4,s0,a4
	lw	a4,0(a4)
	addi	s2,a4,1
	mv	a4,s3
	add	a4,a1,a4
	mv	s6,a1
	mv	a1,a0
	lw	a4,0(a4)
	mv	s3,a3
	mv	s5,a2
	mv	s4,a0
	mv	a0,a4
	call	getNumPos
	mv	a1,s6
	mv	a2,s5
	mv	a3,s3
	mv	a4,a0
	mv	a0,s4
	slli	a4,a4,2
	addi	a4,a4,-272
	add	a4,s0,a4
	mv	a5,s2
	sw	a5,0(a4)
	addi	a4,s1,1
	mv	s1,a4
	j	.L20
.L22:
	mv	a3,a2
	sw	a3,-144(s0)
	lw	a3,-272(s0)
	add	a3,a2,a3
	sw	a3,-208(s0)
	li	a3,1
	j	.L23
.L23:
	li	a4,16
	blt	a3,a4, .L24
	j	.L25
.L24:
	addi	a4,a3,-1
	slli	a4,a4,2
	addi	a4,a4,-208
	add	a6,s0,a4
	mv	a4,a3
	slli	a5,a4,2
	addi	a4,a5,-144
	add	a4,s0,a4
	lw	a6,0(a6)
	sw	a6,0(a4)
	addi	a4,a5,-144
	add	a6,s0,a4
	addi	a4,a5,-272
	add	a4,s0,a4
	lw	a4,0(a4)
	lw	a6,0(a6)
	add	a4,a6,a4
	addi	a5,a5,-208
	add	a5,s0,a5
	sw	a4,0(a5)
	addi	a3,a3,1
	j	.L23
.L25:
	li	a3,0
	mv	s2,a3
	j	.L26
.L26:
	li	a3,16
	blt	s2,a3, .L29
	j	.L28
.L29:
	mv	a3,s2
	slli	s1,a3,2
	addi	a3,s1,-144
	add	a3,s0,a3
	addi	a4,s1,-208
	add	a4,s0,a4
	lw	a4,0(a4)
	lw	a3,0(a3)
	blt	a3,a4, .L30
	j	.L31
.L30:
	addi	a3,s1,-144
	add	a3,s0,a3
	lw	a3,0(a3)
	slli	a3,a3,2
	add	a3,a1,a3
	lw	a3,0(a3)
	mv	s3,a3
	j	.L32
.L32:
	mv	s6,a1
	mv	a1,a0
	mv	s4,a2
	mv	s5,a0
	mv	a0,s3
	call	getNumPos
	mv	a1,s6
	mv	a2,s4
	mv	a3,a0
	mv	a0,s5
	bne	a3,s2, .L33
	j	.L34
.L33:
	mv	s4,a1
	mv	a1,a0
	mv	s5,a2
	mv	s6,a0
	mv	a0,s3
	call	getNumPos
	mv	a1,s4
	mv	a2,s5
	mv	a3,a0
	mv	a0,s6
	slli	a3,a3,2
	addi	a3,a3,-144
	add	a3,s0,a3
	lw	a3,0(a3)
	slli	a3,a3,2
	add	a3,a1,a3
	lw	a3,0(a3)
	mv	s4,a3
	mv	s7,a1
	mv	a1,a0
	mv	s6,a2
	mv	s5,a0
	mv	a0,s3
	call	getNumPos
	mv	a1,s7
	mv	a2,s6
	mv	a3,a0
	mv	a0,s5
	slli	a3,a3,2
	addi	a3,a3,-144
	add	a3,s0,a3
	lw	a3,0(a3)
	slli	a3,a3,2
	add	a4,a1,a3
	mv	a3,s3
	sw	a3,0(a4)
	mv	s6,a1
	mv	a1,a0
	mv	s7,a2
	mv	s5,a0
	mv	a0,s3
	call	getNumPos
	mv	a1,s6
	mv	a2,s7
	mv	a3,a0
	mv	a0,s5
	slli	a3,a3,2
	addi	a3,a3,-144
	add	a3,s0,a3
	lw	a3,0(a3)
	addi	s5,a3,1
	mv	s8,a1
	mv	a1,a0
	mv	s7,a2
	mv	s6,a0
	mv	a0,s3
	call	getNumPos
	mv	a1,s8
	mv	a2,s7
	mv	a3,a0
	mv	a0,s6
	slli	a3,a3,2
	addi	a3,a3,-144
	add	a3,s0,a3
	mv	a4,s5
	sw	a4,0(a3)
	mv	s3,s4
	j	.L32
.L34:
	addi	a3,s1,-144
	add	a3,s0,a3
	lw	a3,0(a3)
	slli	a3,a3,2
	add	a3,a1,a3
	mv	a4,s3
	sw	a4,0(a3)
	addi	a3,s1,-144
	add	a3,s0,a3
	lw	a3,0(a3)
	addi	a3,a3,1
	addi	a4,s1,-144
	add	a4,s0,a4
	sw	a3,0(a4)
	j	.L29
.L31:
	addi	a3,s2,1
	mv	s2,a3
	j	.L26
.L28:
	mv	a3,a2
	sw	a3,-144(s0)
	lw	a3,-272(s0)
	add	a2,a2,a3
	sw	a2,-208(s0)
	li	a2,0
	mv	s1,a2
	j	.L35
.L35:
	li	a2,16
	blt	s1,a2, .L36
	j	.L19
.L36:
	li	a2,0
	bgt	s1,a2, .L38
	j	.L40
.L38:
	addi	a2,s1,-1
	slli	a2,a2,2
	addi	a2,a2,-208
	add	a4,s0,a2
	mv	a2,s1
	slli	a2,a2,2
	addi	a3,a2,-144
	add	a3,s0,a3
	lw	a4,0(a4)
	sw	a4,0(a3)
	addi	a3,a2,-144
	add	a3,s0,a3
	addi	a4,a2,-272
	add	a4,s0,a4
	lw	a4,0(a4)
	lw	a3,0(a3)
	add	a3,a3,a4
	addi	a2,a2,-208
	add	a2,s0,a2
	sw	a3,0(a2)
	j	.L40
.L40:
	addi	a4,a0,-1
	mv	a5,a1
	mv	a2,s1
	slli	a3,a2,2
	addi	a2,a3,-144
	add	a2,s0,a2
	addi	a3,a3,-208
	add	a3,s0,a3
	lw	a3,0(a3)
	lw	a2,0(a2)
	mv	s2,a1
	mv	a1,a5
	mv	s3,a0
	mv	a0,a4
	call	radixSort
	mv	a0,s3
	mv	a1,s2
	addi	a2,s1,1
	mv	s1,a2
	j	.L35
	.text
	.global main
main:
	addi	sp,sp,-24
	sd	ra,16(sp)
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,24
	addi	sp,sp,-8
	la	a0,a
	call	getarray
	mv	s1,a0
	call	starttime
	la	a0,a
	mv	a3,s1
	li	a1,0
	mv	a2,a1
	mv	a1,a0
	li	a0,8
	call	radixSort
	li	a0,0
	j	.L42
.L42:
	blt	a0,s1, .L43
	j	.L44
.L43:
	mv	a1,a0
	slli	a1,a1,2
	la	a2,a
	add	a2,a2,a1
	addi	a1,a0,2
	lw	a2,0(a2)
	rem	a1,a2,a1
	mul	a2,a0,a1
	la	a1,ans
	lw	a1,0(a1)
	add	a1,a1,a2
	la	a2,ans
	sw	a1,0(a2)
	addi	a0,a0,1
	j	.L42
.L44:
	li	a1,0
	la	a0,ans
	lw	a0,0(a0)
	blt	a0,a1, .L45
	j	.L47
.L45:
	la	a0,ans
	lw	a0,0(a0)
	neg	a0,a0
	la	a1,ans
	sw	a0,0(a1)
	j	.L47
.L47:
	call	stoptime
	la	a0,ans
	lw	a0,0(a0)
	call	putint
	li	a0,10
	call	putch
	j	.L48
.L48:
	li	a0,0
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	ret
