	.text
	.global main
main:
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	call	getint
	srai	a0,a0,5
	neg	a0,a0
	call	putint
	j	.L2
.L2:
	li	a0,0
	ld	s0,0(sp)
	ld	ra,8(sp)
	addi	sp,sp,16
	ret
