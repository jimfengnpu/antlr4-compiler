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
	li	a0,0
	mv	a1,a0
	j	.L2
.L2:
	li	a0,10
	blt	a1,a0, .L3
	j	.L4
.L3:
	mv	a0,a1
	slli	a0,a0,2
	addi	a0,a0,-48
	add	a2,s0,a0
	li	a0,0
	sw	a0,0(a2)
	addi	a0,a1,1
	mv	a1,a0
	j	.L2
.L4:
	li	a0,0
	mv	a2,a0
	j	.L5
.L5:
	blt	a2,a4, .L6
	j	.L7
.L6:
	mv	a0,a2
	slli	a1,a0,2
	mv	a0,a1
	add	a0,s0,a0
	lw	a0,0(a0)
	slli	a0,a0,2
	addi	a0,a0,-48
	add	a0,s0,a0
	lw	a0,0(a0)
	addi	a0,a0,1
	add	a1,s0,a1
	lw	a1,0(a1)
	slli	a1,a1,2
	addi	a1,a1,-48
	add	a1,s0,a1
	sw	a0,0(a1)
	addi	a0,a2,1
	mv	a2,a0
	j	.L5
.L7:
	li	a0,1
	mv	a3,a0
	j	.L8
.L8:
	li	a0,10
	blt	a3,a0, .L9
	j	.L10
.L9:
	mv	a0,a3
	slli	a0,a0,2
	addi	a1,a0,-48
	add	a2,s0,a1
	addi	a1,a3,-1
	slli	a1,a1,2
	addi	a1,a1,-48
	add	a1,s0,a1
	lw	a1,0(a1)
	lw	a2,0(a2)
	add	a1,a2,a1
	addi	a0,a0,-48
	add	a0,s0,a0
	sw	a1,0(a0)
	addi	a0,a3,1
	mv	a3,a0
	j	.L8
.L10:
	mv	a0,a4
	j	.L11
.L11:
	li	a1,0
	bgt	a0,a1, .L12
	j	.L13
.L12:
	addi	a3,a0,-1
	mv	a0,a3
	slli	a0,a0,2
	mv	a1,a0
	add	a1,s0,a1
	lw	a1,0(a1)
	slli	a1,a1,2
	addi	a1,a1,-48
	add	a1,s0,a1
	lw	a1,0(a1)
	addi	a2,a1,-1
	mv	a1,a0
	add	a1,s0,a1
	lw	a1,0(a1)
	slli	a1,a1,2
	addi	a1,a1,-48
	add	a1,s0,a1
	sw	a2,0(a1)
	mv	a1,a0
	add	a1,s0,a1
	add	a0,s0,a0
	lw	a0,0(a0)
	slli	a0,a0,2
	addi	a0,a0,-48
	add	a0,s0,a0
	lw	a0,0(a0)
	slli	a0,a0,2
	add	a0,s0,a0
	lw	a1,0(a1)
	sw	a1,0(a0)
	mv	a0,a3
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
	mv	a0,s1
	slli	a0,a0,2
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
