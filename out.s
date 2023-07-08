	.data
	.global n
n:
	.word 0
	.text
	.global swap
swap:
	addi	sp,sp,-16
	sd	s0,0(sp)
	addi	s0,sp,16
	addi	a3,a1,0
	slli	a3,a3,2
	addi	a3,a3,0
	add	a3,a0,a3
	lw	a3,0(a3)
	mv	a4,a3
	addi	a3,a2,0
	slli	a3,a3,2
	addi	a3,a3,0
	add	a3,a0,a3
	addi	a1,a1,0
	slli	a1,a1,2
	addi	a1,a1,0
	add	a1,a0,a1
	lw	a3,0(a3)
	sw	a3,0(a1)
	addi	a1,a2,0
	slli	a1,a1,2
	addi	a1,a1,0
	add	a0,a0,a1
	mv	a1,a4
	sw	a1,0(a0)
	j	.L2
.L2:
	ld	s0,0(sp)
	addi	sp,sp,16
	li	a0,0
	ret
	.text
	.global heap_ajust
heap_ajust:
	addi	sp,sp,-48
	sd	ra,32(sp)
	sd	s0,24(sp)
	sd	s3,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,48
	li	a3,2
	mul	a3,a1,a3
	addi	a3,a3,1
	j	.L4
.L4:
	addi	a4,a2,1
	blt	a3,a4, .L5
	j	.L14
.L5:
	mv	s1,a3
	blt	a3,a2, .L10
	j	.L9
.L10:
	addi	a4,a3,0
	slli	a4,a4,2
	addi	a4,a4,0
	add	a5,a0,a4
	addi	a4,a3,1
	addi	a4,a4,0
	slli	a4,a4,2
	addi	a4,a4,0
	add	a4,a0,a4
	mv	s1,a3
	lw	a4,0(a4)
	lw	a5,0(a5)
	blt	a5,a4, .L7
	j	.L9
.L7:
	addi	a3,a3,1
	mv	s1,a3
	j	.L9
.L9:
	addi	a3,a1,0
	slli	a3,a3,2
	addi	a3,a3,0
	add	a3,a0,a3
	addi	a4,s1,0
	slli	a4,a4,2
	addi	a4,a4,0
	add	a4,a0,a4
	lw	a4,0(a4)
	lw	a3,0(a3)
	bgt	a3,a4, .L14
	j	.L12
.L14:
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s3,16(sp)
	ld	s0,24(sp)
	ld	ra,32(sp)
	addi	sp,sp,48
	li	a0,0
	ret
.L12:
	addi	a3,a0,0
	mv	s3,a2
	mv	a2,s1
	mv	s2,a0
	mv	a0,a3
	call	swap
	mv	a2,s3
	mv	a0,s2
	mv	a1,s1
	li	a3,2
	mul	a3,a1,a3
	addi	a3,a3,1
	j	.L4
	.text
	.global heap_sort
heap_sort:
	addi	sp,sp,-48
	sd	ra,32(sp)
	sd	s0,24(sp)
	sd	s3,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,48
	li	a2,2
	div	a2,a1,a2
	addi	a2,a2,-1
	mv	s1,a2
	j	.L16
.L16:
	li	a2,-1
	bgt	s1,a2, .L17
	j	.L18
.L17:
	addi	a2,a1,-1
	addi	a3,a0,0
	mv	s2,a1
	mv	a1,s1
	mv	s3,a0
	mv	a0,a3
	call	heap_ajust
	mv	a1,s2
	mv	a0,s3
	addi	a2,s1,-1
	mv	s1,a2
	j	.L16
.L18:
	addi	a1,a1,-1
	mv	s1,a1
	j	.L19
.L19:
	li	a1,0
	bgt	s1,a1, .L20
	j	.L22
.L20:
	addi	a3,a0,0
	mv	a2,s1
	li	a1,0
	mv	s2,a0
	mv	a0,a3
	call	swap
	mv	a0,s2
	addi	a1,s1,-1
	addi	a3,a0,0
	mv	a2,a1
	li	a1,0
	mv	s2,a0
	mv	a0,a3
	call	heap_ajust
	mv	a0,s2
	addi	a1,s1,-1
	mv	s1,a1
	j	.L19
.L22:
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s3,16(sp)
	ld	s0,24(sp)
	ld	ra,32(sp)
	addi	sp,sp,48
	li	a0,0
	ret
	.text
	.global main
main:
	addi	sp,sp,-80
	sd	ra,64(sp)
	sd	s0,56(sp)
	sd	s2,48(sp)
	sd	s1,40(sp)
	addi	s0,sp,80
	li	a0,10
	mv	a1,a0
	la	a0,n
	sw	a1,0(a0)
	li	a0,4
	sw	a0,-80(s0)
	li	a0,3
	sw	a0,-76(s0)
	li	a0,9
	sw	a0,-72(s0)
	li	a0,2
	sw	a0,-68(s0)
	li	a0,0
	sw	a0,-64(s0)
	li	a0,1
	sw	a0,-60(s0)
	li	a0,6
	sw	a0,-56(s0)
	li	a0,5
	sw	a0,-52(s0)
	li	a0,7
	sw	a0,-48(s0)
	li	a0,8
	sw	a0,-44(s0)
	addi	a0,s0,-80
	la	a1,n
	lw	a1,0(a1)
	call	heap_sort
	mv	s2,a0
	j	.L24
.L24:
	la	a0,n
	lw	a0,0(a0)
	blt	s2,a0, .L25
	j	.L27
.L25:
	addi	a0,s2,0
	slli	a0,a0,2
	addi	a0,a0,-80
	add	a0,s0,a0
	lw	a0,0(a0)
	call	putint
	li	a0,10
	call	putch
	addi	a0,s2,1
	mv	s2,a0
	j	.L24
.L27:
	ld	s1,40(sp)
	ld	s2,48(sp)
	ld	s0,56(sp)
	ld	ra,64(sp)
	addi	sp,sp,80
	li	a0,0
	ret
