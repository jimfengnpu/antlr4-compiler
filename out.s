	.data
	.global array
array:
	.zero 440
	.data
	.global n
n:
	.word 0
	.text
	.global init
init:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	li	a1,1
	mv	a3,a1
	j	.L2
.L2:
	mul	a1,a0,a0
	addi	a1,a1,1
	ble	a3,a1, .L3
	j	.L4
.L3:
	mv	a1,a3
	slli	a1,a1,2
	la	a2,array
	add	a1,a2,a1
	li	a2,-1
	sw	a2,0(a1)
	addi	a1,a3,1
	mv	a3,a1
	j	.L2
.L4:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
	.text
	.global findfa
findfa:
	addi	sp,sp,-24
	sd	ra,16(sp)
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,24
	addi	sp,sp,-8
	mv	s1,a0
	slli	a1,s1,2
	la	a2,array
	add	a1,a2,a1
	lw	a1,0(a1)
	beq	a1,a0, .L6
	j	.L7
.L6:
	j	.L9
.L9:
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	ret
.L7:
	mv	a0,s1
	slli	a0,a0,2
	la	a1,array
	add	a0,a1,a0
	lw	a0,0(a0)
	call	findfa
	mv	a1,s1
	slli	a1,a1,2
	la	a2,array
	add	a1,a2,a1
	sw	a0,0(a1)
	mv	a0,s1
	slli	a1,a0,2
	la	a0,array
	add	a0,a0,a1
	lw	a0,0(a0)
	j	.L9
	.text
	.global mmerge
mmerge:
	addi	sp,sp,-24
	sd	ra,16(sp)
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,24
	addi	sp,sp,-8
	mv	s1,a1
	call	findfa
	mv	a1,s1
	mv	s1,a0
	mv	a0,a1
	call	findfa
	bne	s1,a0, .L11
	j	.L13
.L11:
	mv	a1,s1
	slli	a2,a1,2
	la	a1,array
	add	a1,a1,a2
	sw	a0,0(a1)
	j	.L13
.L13:
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	ret
	.text
	.global main
main:
	addi	sp,sp,-72
	sd	ra,64(sp)
	sd	s0,56(sp)
	sd	s7,48(sp)
	sd	s6,40(sp)
	sd	s5,32(sp)
	sd	s4,24(sp)
	sd	s3,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,72
	addi	sp,sp,-8
	li	a0,1
	j	.L15
.L15:
	bnez	a0, .L16
	j	.L17
.L16:
	addi	a0,a0,-1
	mv	s1,a0
	li	a0,4
	la	a1,n
	sw	a0,0(a1)
	la	a0,n
	lw	a0,0(a0)
	call	init
	la	a0,n
	lw	a1,0(a0)
	la	a0,n
	lw	a0,0(a0)
	mul	a0,a0,a1
	addi	a0,a0,1
	mv	s2,a0
	li	a0,0
	mv	s4,a0
	li	a0,0
	mv	s3,a0
	j	.L18
.L18:
	li	a0,10
	blt	s3,a0, .L19
	j	.L20
.L19:
	call	getint
	mv	s5,a0
	call	getint
	mv	s7,a0
	mv	a0,s4
	beqz	s4, .L21
	j	.L23
.L21:
	addi	a0,s5,-1
	la	a1,n
	lw	a1,0(a1)
	mul	a0,a1,a0
	add	a0,a0,s7
	mv	s6,a0
	mv	a0,s6
	slli	a0,a0,2
	la	a1,array
	add	a0,a1,a0
	mv	a1,s6
	sw	a1,0(a0)
	li	a0,1
	beq	s5,a0, .L24
	j	.L26
.L24:
	la	a0,array
	li	a1,0
	sw	a1,0(a0)
	li	a0,0
	mv	a1,a0
	mv	a0,s6
	call	mmerge
	j	.L26
.L26:
	la	a0,n
	lw	a0,0(a0)
	beq	s5,a0, .L27
	j	.L29
.L27:
	mv	a0,s2
	slli	a1,a0,2
	la	a0,array
	add	a1,a0,a1
	mv	a0,s2
	sw	a0,0(a1)
	mv	a1,s2
	mv	a0,s6
	call	mmerge
	j	.L29
.L29:
	la	a0,n
	lw	a0,0(a0)
	blt	s7,a0, .L33
	j	.L32
.L33:
	addi	a1,s6,1
	mv	a0,a1
	slli	a2,a0,2
	la	a0,array
	add	a0,a0,a2
	li	a2,-1
	lw	a0,0(a0)
	bne	a0,a2, .L30
	j	.L32
.L30:
	mv	a0,a1
	mv	a1,a0
	mv	a0,s6
	call	mmerge
	j	.L32
.L32:
	li	a0,1
	bgt	s7,a0, .L37
	j	.L36
.L37:
	addi	a0,s6,-1
	mv	a1,a0
	slli	a1,a1,2
	la	a2,array
	add	a2,a2,a1
	li	a1,-1
	lw	a2,0(a2)
	bne	a2,a1, .L34
	j	.L36
.L34:
	mv	a1,a0
	mv	a0,s6
	call	mmerge
	j	.L36
.L36:
	la	a0,n
	lw	a0,0(a0)
	blt	s5,a0, .L41
	j	.L40
.L41:
	la	a0,n
	lw	a0,0(a0)
	add	a0,s6,a0
	mv	a1,a0
	slli	a1,a1,2
	la	a2,array
	add	a2,a2,a1
	li	a1,-1
	lw	a2,0(a2)
	bne	a2,a1, .L38
	j	.L40
.L38:
	mv	a1,a0
	mv	a0,s6
	call	mmerge
	j	.L40
.L40:
	li	a0,1
	bgt	s5,a0, .L45
	j	.L44
.L45:
	la	a0,n
	lw	a0,0(a0)
	sub	a0,s6,a0
	mv	a1,a0
	slli	a1,a1,2
	la	a2,array
	add	a1,a2,a1
	li	a2,-1
	lw	a1,0(a1)
	bne	a1,a2, .L42
	j	.L44
.L42:
	mv	a1,a0
	mv	a0,s6
	call	mmerge
	j	.L44
.L44:
	la	a0,array
	mv	a2,a0
	mv	a0,s4
	li	a1,-1
	lw	a2,0(a2)
	bne	a2,a1, .L50
	j	.L23
.L50:
	mv	a0,s2
	slli	a0,a0,2
	la	a1,array
	add	a1,a1,a0
	mv	a0,s4
	li	a2,-1
	lw	a1,0(a1)
	bne	a1,a2, .L49
	j	.L23
.L49:
	li	a0,0
	call	findfa
	mv	s5,a0
	mv	a0,s2
	call	findfa
	mv	a1,a0
	mv	a0,s4
	beq	s5,a1, .L46
	j	.L23
.L46:
	addi	a0,s3,1
	call	putint
	li	a0,10
	call	putch
	li	a0,1
	j	.L23
.L23:
	addi	a1,s3,1
	mv	s4,a0
	mv	s3,a1
	j	.L18
.L20:
	mv	a0,s1
	beqz	s4, .L51
	j	.L15
.L51:
	li	a0,-1
	call	putint
	li	a0,10
	call	putch
	mv	a0,s1
	j	.L15
.L17:
	j	.L54
.L54:
	li	a0,0
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s3,16(sp)
	ld	s4,24(sp)
	ld	s5,32(sp)
	ld	s6,40(sp)
	ld	s7,48(sp)
	ld	s0,56(sp)
	ld	ra,64(sp)
	addi	sp,sp,72
	ret
