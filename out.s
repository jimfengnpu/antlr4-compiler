	.data
	.global L
L:
	.word 0
	.data
	.global M
M:
	.word 0
	.data
	.global N
N:
	.word 0
	.text
	.global add
add:
	addi	sp,sp,-40
	sd	s0,32(sp)
	sd	s4,24(sp)
	sd	s3,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,40
	addi	sp,sp,-8
	li	s1,0
	mv	s3,s1
	j	.L2
.L2:
	la	s1,M
	lw	s1,0(s1)
	blt	s3,s1, .L3
	j	.L4
.L3:
	addi	s1,s3,0
	slli	s1,s1,2
	addi	s1,s1,0
	add	s1,a0,s1
	addi	s2,s3,0
	slli	s2,s2,2
	addi	s2,s2,0
	add	s2,a3,s2
	lw	s2,0(s2)
	lw	s1,0(s1)
	add	s1,s1,s2
	addi	s2,s3,0
	slli	s2,s2,2
	addi	s2,s2,0
	add	s2,a6,s2
	sw	s1,0(s2)
	addi	s1,s3,0
	slli	s1,s1,2
	addi	s1,s1,0
	add	s1,a1,s1
	addi	s2,s3,0
	slli	s2,s2,2
	addi	s2,s2,0
	add	s2,a4,s2
	lw	s2,0(s2)
	lw	s1,0(s1)
	add	s1,s1,s2
	addi	s2,s3,0
	slli	s2,s2,2
	addi	s2,s2,0
	add	s2,a7,s2
	sw	s1,0(s2)
	addi	s1,s3,0
	slli	s1,s1,2
	addi	s1,s1,0
	add	s2,a2,s1
	addi	s1,s3,0
	slli	s1,s1,2
	addi	s1,s1,0
	add	s1,a5,s1
	lw	s1,0(s1)
	lw	s2,0(s2)
	add	s1,s2,s1
	addi	s2,s3,0
	slli	s2,s2,2
	ld	s4,0(s0)
	addi	s2,s2,0
	add	s2,s4,s2
	sw	s1,0(s2)
	addi	s1,s3,1
	mv	s3,s1
	j	.L2
.L4:
	j	.L5
.L5:
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s3,16(sp)
	ld	s4,24(sp)
	ld	s0,32(sp)
	addi	sp,sp,40
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
	addi	sp,sp,-136
	li	a1,3
	la	a2,N
	sw	a1,0(a2)
	li	a1,3
	la	a2,M
	sw	a1,0(a2)
	li	a1,3
	la	a0,L
	sw	a1,0(a0)
	li	a0,0
	j	.L7
.L7:
	la	a1,M
	lw	a1,0(a1)
	blt	a0,a1, .L8
	j	.L9
.L8:
	addi	a1,a0,0
	slli	a1,a1,2
	addi	a1,a1,-36
	add	a1,s0,a1
	mv	a2,a0
	sw	a2,0(a1)
	addi	a1,a0,0
	slli	a1,a1,2
	addi	a1,a1,-48
	add	a1,s0,a1
	mv	a2,a0
	sw	a2,0(a1)
	addi	a1,a0,0
	slli	a1,a1,2
	addi	a1,a1,-60
	add	a2,s0,a1
	mv	a1,a0
	sw	a1,0(a2)
	addi	a1,a0,0
	slli	a1,a1,2
	addi	a1,a1,-72
	add	a1,s0,a1
	mv	a2,a0
	sw	a2,0(a1)
	addi	a1,a0,0
	slli	a1,a1,2
	addi	a1,a1,-84
	add	a1,s0,a1
	mv	a2,a0
	sw	a2,0(a1)
	addi	a1,a0,0
	slli	a1,a1,2
	addi	a1,a1,-96
	add	a2,s0,a1
	mv	a1,a0
	sw	a1,0(a2)
	addi	a0,a0,1
	j	.L7
.L9:
	addi	a0,s0,-36
	addi	a1,s0,-48
	addi	a2,s0,-60
	addi	a3,s0,-72
	addi	a4,s0,-84
	addi	a5,s0,-96
	addi	a6,s0,-120
	addi	a7,s0,-132
	addi	s1,s0,-144
	sd	s1,0(sp)
	call	add
	mv	s1,a0
	j	.L10
.L10:
	la	a0,N
	lw	a0,0(a0)
	blt	s1,a0, .L11
	j	.L12
.L11:
	addi	a0,s1,0
	slli	a0,a0,2
	addi	a0,a0,-120
	add	a0,s0,a0
	lw	a0,0(a0)
	call	putint
	addi	a0,s1,1
	mv	s1,a0
	j	.L10
.L12:
	li	a0,10
	call	putch
	li	a0,0
	mv	s1,a0
	j	.L13
.L13:
	la	a0,N
	lw	a0,0(a0)
	blt	s1,a0, .L14
	j	.L15
.L14:
	addi	a0,s1,0
	slli	a0,a0,2
	addi	a0,a0,-132
	add	a0,s0,a0
	lw	a0,0(a0)
	call	putint
	addi	a0,s1,1
	mv	s1,a0
	j	.L13
.L15:
	li	a0,10
	call	putch
	li	a0,0
	mv	s1,a0
	j	.L16
.L16:
	la	a0,N
	lw	a0,0(a0)
	blt	s1,a0, .L17
	j	.L18
.L17:
	addi	a0,s1,0
	slli	a0,a0,2
	addi	a0,a0,-144
	add	a0,s0,a0
	lw	a0,0(a0)
	call	putint
	addi	a0,s1,1
	mv	s1,a0
	j	.L16
.L18:
	li	a0,10
	call	putch
	j	.L19
.L19:
	addi	sp,sp,136
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	li	a0,0
	ret
