	.data
	.global n
n:
	.word 0
	.text
	.global bubblesort
bubblesort:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	li	a1,0
	mv	a5,a1
	j	.L2
.L2:
	la	a1,n
	lw	a1,0(a1)
	addi	a1,a1,-1
	blt	a5,a1, .L3
	j	.L4
.L3:
	li	a1,0
	mv	a3,a1
	j	.L5
.L5:
	la	a1,n
	lw	a1,0(a1)
	sub	a1,a1,a5
	addi	a1,a1,-1
	blt	a3,a1, .L6
	j	.L7
.L6:
	addi	a1,a3,0
	slli	a1,a1,2
	addi	a1,a1,0
	add	a1,a0,a1
	addi	a2,a3,1
	addi	a2,a2,0
	slli	a2,a2,2
	addi	a2,a2,0
	add	a2,a0,a2
	lw	a2,0(a2)
	lw	a1,0(a1)
	bgt	a1,a2, .L8
	j	.L10
.L8:
	addi	a1,a3,1
	addi	a1,a1,0
	slli	a1,a1,2
	addi	a1,a1,0
	add	a1,a0,a1
	lw	a1,0(a1)
	mv	a4,a1
	addi	a1,a3,0
	slli	a1,a1,2
	addi	a1,a1,0
	add	a1,a0,a1
	addi	a2,a3,1
	addi	a2,a2,0
	slli	a2,a2,2
	addi	a2,a2,0
	add	a2,a0,a2
	lw	a1,0(a1)
	sw	a1,0(a2)
	addi	a1,a3,0
	slli	a1,a1,2
	addi	a1,a1,0
	add	a1,a0,a1
	mv	a2,a4
	sw	a2,0(a1)
	j	.L10
.L10:
	addi	a1,a3,1
	mv	a3,a1
	j	.L5
.L7:
	addi	a1,a5,1
	mv	a5,a1
	j	.L2
.L4:
	j	.L11
.L11:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	li	a0,0
	ret
	.text
	.global main
main:
	addi	sp,sp,-24
	sd	ra,16(sp)
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,24
	addi	sp,sp,-40
	li	a1,10
	la	a0,n
	sw	a1,0(a0)
	li	a0,4
	sw	a0,-64(s0)
	li	a0,3
	sw	a0,-60(s0)
	li	a0,9
	sw	a0,-56(s0)
	li	a0,2
	sw	a0,-52(s0)
	li	a0,0
	sw	a0,-48(s0)
	li	a0,1
	sw	a0,-44(s0)
	li	a0,6
	sw	a0,-40(s0)
	li	a0,5
	sw	a0,-36(s0)
	li	a0,7
	sw	a0,-32(s0)
	li	a0,8
	sw	a0,-28(s0)
	addi	a0,s0,-64
	call	bubblesort
	mv	s1,a0
	j	.L13
.L13:
	la	a0,n
	lw	a0,0(a0)
	blt	s1,a0, .L14
	j	.L15
.L14:
	addi	a0,s1,0
	slli	a0,a0,2
	addi	a0,a0,-64
	add	a0,s0,a0
	lw	a0,0(a0)
	call	putint
	li	a0,10
	call	putch
	addi	a0,s1,1
	mv	s1,a0
	j	.L13
.L15:
	j	.L16
.L16:
	addi	sp,sp,40
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	li	a0,0
	ret
