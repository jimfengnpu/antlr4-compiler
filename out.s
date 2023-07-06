	.data
	.global n
n:
	.word 0
	.text
	.global swap
swap:
	addi	sp, sp, -16
	addi	s0, sp, 16
	addi	a3, a1, 0
	slli	a3, a3, 2
	add	a0, a0, a3
	lw	a3, 0(a0)
	mv	a4, a3
	addi	a3, a2, 0
	slli	a3, a3, 2
	add	a0, a0, a3
	addi	a1, a1, 0
	slli	a1, a1, 2
	add	a0, a0, a1
	lw	a1, 0(a0)
	sw	a1, 0(a0)
	addi	a1, a2, 0
	slli	a1, a1, 2
	add	a0, a0, a1
	mv	a0, a4
	sw	a0, 0(a0)
	j	.L2
.L2:
	addi	sp, sp, 16
	ret
	.text
	.global heap_ajust
heap_ajust:
	addi	sp, sp, -48
	sd	s4, 24(sp)
	sd	s3, 16(sp)
	sd	s2, 8(sp)
	sd	s1, 0(sp)
	addi	s0, sp, 48
	li	s1, 2
	mul	s1, a1, s1
	addi	s1, s1, 1
	mv	s3, s1
	j	.L4
.L4:
	addi	s1, a2, 1
	blt	s3, s1, .L5
	j	.L14
.L5:
	mv	s1, s3
	blt	s3, a2, .L10
	j	.L9
.L10:
	addi	s1, s3, 0
	slli	s1, s1, 2
	add	a0, a0, s1
	addi	s1, s3, 1
	addi	s1, s1, 0
	slli	s1, s1, 2
	add	a0, a0, s1
	mv	s1, s3
	lw	s4, 0(a0)
	lw	s2, 0(a0)
	blt	s2, s4, .L7
	j	.L9
.L7:
	addi	s1, s3, 1
	j	.L9
.L9:
	addi	s2, a1, 0
	slli	s2, s2, 2
	add	a0, a0, s2
	addi	s3, s1, 0
	slli	s3, s3, 2
	add	a0, a0, s3
	lw	s3, 0(a0)
	lw	s2, 0(a0)
	bgt	s2, s3, .L14
	j	.L12
.L14:
	ld	s1, 0(sp)
	ld	s2, 8(sp)
	ld	s3, 16(sp)
	ld	s4, 24(sp)
	addi	sp, sp, 48
	ret
.L12:
	addi	a3, a0, 0
	mv	a2, s1
	mv	a0, a3
	call	swap
	mv	a1, a0
	mv	a1, s1
	li	s1, 2
	mul	s1, a1, s1
	addi	s1, s1, 1
	mv	s3, s1
	j	.L4
	.text
	.global heap_sort
heap_sort:
	addi	sp, sp, -32
	sd	s2, 8(sp)
	sd	s1, 0(sp)
	addi	s0, sp, 32
	li	a2, 2
	div	a2, a1, a2
	addi	a2, a2, -1
	mv	s1, a2
	j	.L16
.L16:
	li	a2, -1
	bgt	s1, a2, .L17
	j	.L18
.L17:
	addi	a2, a1, -1
	addi	s2, a0, 0
	mv	a1, s1
	mv	a0, s2
	call	heap_ajust
	mv	a2, a0
	addi	a2, s1, -1
	mv	s1, a2
	j	.L16
.L18:
	addi	a1, a1, -1
	mv	s1, a1
	j	.L19
.L19:
	li	a1, 0
	bgt	s1, a1, .L20
	j	.L22
.L20:
	addi	a3, a0, 0
	mv	a2, s1
	li	a1, 0
	mv	a0, a3
	call	swap
	mv	a1, a0
	addi	a1, s1, -1
	addi	s2, a0, 0
	mv	a2, a1
	li	a1, 0
	mv	a0, s2
	call	heap_ajust
	mv	a1, a0
	addi	a1, s1, -1
	mv	s1, a1
	j	.L19
.L22:
	ld	s1, 0(sp)
	ld	s2, 8(sp)
	addi	sp, sp, 32
	ret
	.text
	.global main
main:
	addi	sp, sp, -80
	sd	s3, 56(sp)
	sd	s2, 48(sp)
	sd	s1, 40(sp)
	addi	s0, sp, 80
	li	s2, 10
	la	s3, n
	sw	s2, 0(s3)
	li	s2, 4
	sw	s2, -80(s0)
	li	s2, 3
	sw	s2, -76(s0)
	li	s2, 9
	sw	s2, -72(s0)
	li	s2, 2
	sw	s2, -68(s0)
	li	s2, 0
	sw	s2, -64(s0)
	li	s2, 1
	sw	s2, -60(s0)
	li	s2, 6
	sw	s2, -56(s0)
	li	s2, 5
	sw	s2, -52(s0)
	li	s2, 7
	sw	s2, -48(s0)
	li	s2, 8
	sw	s2, -44(s0)
	addi	s2, s0, 0
	la	s3, n
	lw	s3, 0(s3)
	mv	a1, s3
	mv	a0, s2
	call	heap_sort
	mv	s2, a0
	j	.L24
.L24:
	la	a0, n
	lw	a0, 0(a0)
	blt	s2, a0, .L25
	j	.L27
.L25:
	addi	a0, s2, 0
	slli	a0, a0, 2
	add	s0, s0, a0
	lw	a0, -80(s0)
	call	putint
	li	a0, 10
	call	putch
	addi	a0, s2, 1
	mv	s2, a0
	j	.L24
.L27:
	ld	s1, 40(sp)
	ld	s2, 48(sp)
	ld	s3, 56(sp)
	addi	sp, sp, 80
	ret
