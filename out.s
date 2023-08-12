	.data
	.global n
n:
	.word 0
	.text
	.global QuickSort
QuickSort:
	addi	sp,sp,-40
	sd	ra,32(sp)
	sd	s0,24(sp)
	sd	s3,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,40
	addi	sp,sp,-8
	blt	a1,a2, .L2
	j	.L3
.L2:
	mv	a6,a1
	mv	a3,a2
	mv	a4,a1
	slli	a4,a4,2
	add	a4,a0,a4
	lw	a4,0(a4)
	mv	a5,a4
	mv	a4,a3
	mv	s1,a6
	j	.L5
.L5:
	blt	s1,a4, .L6
	j	.L7
.L6:
	mv	a6,a4
	j	.L8
.L8:
	blt	s1,a6, .L11
	j	.L10
.L11:
	mv	a3,a6
	slli	a3,a3,2
	add	a4,a0,a3
	addi	a3,a5,-1
	lw	a4,0(a4)
	bgt	a4,a3, .L9
	j	.L10
.L9:
	addi	a3,a6,-1
	mv	a6,a3
	j	.L8
.L10:
	blt	s1,a6, .L12
	j	.L13
.L12:
	mv	a3,a6
	slli	a3,a3,2
	add	a3,a0,a3
	mv	a4,s1
	slli	a4,a4,2
	add	a4,a0,a4
	lw	a3,0(a3)
	sw	a3,0(a4)
	addi	a3,s1,1
	j	.L14
.L14:
	j	.L15
.L15:
	blt	a3,a6, .L18
	j	.L17
.L18:
	mv	a4,a3
	slli	a4,a4,2
	add	a4,a0,a4
	lw	a4,0(a4)
	blt	a4,a5, .L16
	j	.L17
.L16:
	addi	a3,a3,1
	j	.L15
.L17:
	blt	a3,a6, .L19
	j	.L20
.L19:
	mv	a4,a3
	slli	a4,a4,2
	add	a4,a0,a4
	mv	a7,a6
	slli	a7,a7,2
	add	a7,a0,a7
	lw	a4,0(a4)
	sw	a4,0(a7)
	addi	a4,a6,-1
	j	.L21
.L21:
	mv	s1,a3
	j	.L5
.L20:
	mv	a4,a6
	j	.L21
.L13:
	mv	a3,s1
	j	.L14
.L7:
	mv	a3,s1
	slli	a3,a3,2
	add	a3,a0,a3
	mv	a4,a5
	sw	a4,0(a3)
	addi	a4,s1,-1
	mv	a3,a0
	mv	s2,a2
	mv	a2,a4
	mv	s3,a0
	mv	a0,a3
	call	QuickSort
	mv	a2,s2
	mv	a0,s3
	addi	a1,s1,1
	call	QuickSort
	j	.L4
.L4:
	j	.L22
.L22:
	li	a0,0
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s3,16(sp)
	ld	s0,24(sp)
	ld	ra,32(sp)
	addi	sp,sp,40
	ret
.L3:
	j	.L4
	.text
	.global main
main:
	addi	sp,sp,-24
	sd	ra,16(sp)
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,24
	addi	sp,sp,-40
	li	a0,10
	mv	a1,a0
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
	li	a1,9
	mv	a2,a1
	li	a1,0
	call	QuickSort
	mv	s1,a0
	j	.L24
.L24:
	la	a0,n
	lw	a0,0(a0)
	blt	s1,a0, .L25
	j	.L26
.L25:
	mv	a0,s1
	slli	a0,a0,2
	addi	a0,a0,-64
	add	a0,s0,a0
	lw	a0,0(a0)
	call	putint
	li	a0,10
	call	putch
	addi	a0,s1,1
	mv	s1,a0
	j	.L24
.L26:
	j	.L27
.L27:
	li	a0,0
	addi	sp,sp,40
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	ret
