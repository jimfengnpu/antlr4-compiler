	.text
	.global move
move:
	addi	sp,sp,-24
	sd	ra,16(sp)
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,24
	addi	sp,sp,-8
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	mv	s1,a1
	call	putint
	mv	a1,s1
	li	a0,32
	mv	s1,a1
	call	putch
	mv	a1,s1
	mv	a0,a1
	call	putint
	li	a0,44
	call	putch
	li	a0,32
	call	putch
	ret
	.text
	.global hanoi
hanoi:
	addi	sp,sp,-48
	sd	ra,40(sp)
	sd	s0,32(sp)
	sd	s4,24(sp)
	sd	s3,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,48
	li	a4,1
	beq	a0,a4, .L3
	j	.L4
.L3:
	mv	s1,a1
	mv	a1,a3
	mv	a0,s1
	call	move
	mv	a1,s1
	j	.L5
.L5:
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s3,16(sp)
	ld	s4,24(sp)
	ld	s0,32(sp)
	ld	ra,40(sp)
	addi	sp,sp,48
	ret
.L4:
	addi	a4,a0,-1
	mv	s1,a3
	mv	a3,a2
	mv	s2,a2
	mv	a2,s1
	mv	s3,a1
	mv	s4,a0
	mv	a0,a4
	call	hanoi
	mv	a0,s4
	mv	a1,s3
	mv	a2,s2
	mv	a3,s1
	mv	s2,a1
	mv	a1,a3
	mv	s1,a3
	mv	s3,a2
	mv	s4,a0
	mv	a0,s2
	call	move
	mv	a0,s4
	mv	a1,s2
	mv	a2,s3
	mv	a3,s1
	addi	a0,a0,-1
	mv	s1,a2
	mv	a2,a1
	mv	a1,s1
	call	hanoi
	mv	a2,s1
	j	.L5
	.text
	.global main
main:
	addi	sp,sp,-24
	sd	ra,16(sp)
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,24
	addi	sp,sp,-8
	call	getint
	mv	s1,a0
	j	.L7
.L7:
	li	a0,0
	bgt	s1,a0, .L8
	j	.L9
.L8:
	call	getint
	li	a1,3
	mv	a3,a1
	li	a1,2
	mv	a2,a1
	li	a1,1
	call	hanoi
	li	a0,10
	call	putch
	addi	a0,s1,-1
	mv	s1,a0
	j	.L7
.L9:
	j	.L10
.L10:
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	li	a0,0
	ret
