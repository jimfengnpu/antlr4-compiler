	.data
	.global n
n:
	.word 0
	.text
	.global counting_sort
counting_sort:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-40
	li	a3,0
	j	.L2
.L2:
	li	a4,10
	blt	a3,a4, .L3
	j	.L4
.L3:
	slli	a4,a3,2
	addi	a4,a4,-48
	add	a4,s0,a4
	li	a5,0
	sw	a5,0(a4)
	addi	a3,a3,1
	j	.L2
.L4:
	li	a3,0
	mv	a4,a3
	j	.L5
.L5:
	blt	a4,a2, .L6
	j	.L7
.L6:
	slli	a5,a4,2
	mv	a3,a5
	add	a3,a0,a3
	lw	a3,0(a3)
	slli	a3,a3,2
	addi	a3,a3,-48
	add	a3,s0,a3
	lw	a3,0(a3)
	addi	a3,a3,1
	add	a5,a0,a5
	lw	a5,0(a5)
	slli	a5,a5,2
	addi	a5,a5,-48
	add	a5,s0,a5
	sw	a3,0(a5)
	addi	a3,a4,1
	mv	a4,a3
	j	.L5
.L7:
	li	a3,1
	j	.L8
.L8:
	li	a4,10
	blt	a3,a4, .L9
	j	.L10
.L9:
	slli	a6,a3,2
	addi	a4,a6,-48
	add	a5,s0,a4
	addi	a4,a3,-1
	slli	a4,a4,2
	addi	a4,a4,-48
	add	a4,s0,a4
	lw	a4,0(a4)
	lw	a5,0(a5)
	add	a4,a5,a4
	addi	a5,a6,-48
	add	a5,s0,a5
	sw	a4,0(a5)
	addi	a3,a3,1
	j	.L8
.L10:
	mv	a3,a2
	j	.L11
.L11:
	li	a2,0
	bgt	a3,a2, .L12
	j	.L13
.L12:
	addi	a2,a3,-1
	slli	a4,a2,2
	mv	a3,a4
	add	a3,a0,a3
	lw	a3,0(a3)
	slli	a3,a3,2
	addi	a3,a3,-48
	add	a3,s0,a3
	lw	a3,0(a3)
	addi	a3,a3,-1
	mv	a5,a4
	add	a5,a0,a5
	lw	a5,0(a5)
	slli	a5,a5,2
	addi	a5,a5,-48
	add	a5,s0,a5
	sw	a3,0(a5)
	mv	a3,a4
	add	a3,a0,a3
	add	a4,a0,a4
	lw	a4,0(a4)
	slli	a4,a4,2
	addi	a4,a4,-48
	add	a4,s0,a4
	lw	a4,0(a4)
	slli	a4,a4,2
	add	a4,a1,a4
	lw	a3,0(a3)
	sw	a3,0(a4)
	mv	a3,a2
	j	.L11
.L13:
	j	.L14
.L14:
	li	a0,0
	addi	sp,sp,40
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
	.text
	.global main
main:
	addi	sp,sp,-24
	sd	ra,16(sp)
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,24
	addi	sp,sp,-88
	li	a0,10
	la	a1,n
	sw	a0,0(a1)
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
	addi	a1,s0,-104
	la	a2,n
	lw	a2,0(a2)
	call	counting_sort
	mv	s1,a0
	j	.L16
.L16:
	la	a0,n
	lw	a0,0(a0)
	blt	s1,a0, .L17
	j	.L18
.L17:
	slli	a0,s1,2
	addi	a0,a0,-104
	add	a0,s0,a0
	lw	a0,0(a0)
	call	putint
	li	a0,10
	call	putch
	addi	a0,s1,1
	mv	s1,a0
	j	.L16
.L18:
	j	.L19
.L19:
	li	a0,0
	addi	sp,sp,88
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	ret
