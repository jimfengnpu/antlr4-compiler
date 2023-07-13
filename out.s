	.text
	.global main
main:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	li	a0,0
	li	a1,0
	j	.L2
.L2:
	li	a3,100
	blt	a1,a3, .L3
	j	.L4
.L3:
	li	a3,50
	beq	a1,a3, .L5
	j	.L7
.L5:
	mv	a1,a2
	j	.L9
.L9:
	j	.L2
.L7:
	add	a0,a0,a1
	addi	a2,a1,1
	mv	a1,a2
	j	.L2
.L4:
	j	.L8
.L8:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
