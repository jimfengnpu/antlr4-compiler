	.data
	.global cns
cns:
	.zero 80
	.data
	.global dp
dp:
	.zero 52907904
	.data
	.global list
list:
	.zero 800
	.section .rodata
	.global maxn
maxn:
	.word 18
	.section .rodata
	.global mod
mod:
	.word 1000000007
	.text
	.global equal
equal:
	beq	a0, a1, .L2
	j	.L4
.L2:
	li	a0, a0
	j	.L5
.L4:
	li	a0, a0
	j	.L5
.L5:
	.text
	.global dfs
dfs:
	addi	s11, a0, s9
	mul	s4, s9, s11
	add	a6, a1, s4
	mul	s6, a6, a6
	add	s8, a2, s6
	mul	s7, s8, s8
	add	a7, a3, s7
	mul	s0, a7, a7
	add	s1, a4, s0
	mul	s2, s1, s1
	add	s3, a5, s2
	slli	s10, s3, s3
	add	dp, s9, s10
	lw	a0, dp
	bne	a0, s9, .L7
	j	.L9
.L7:
	addi	s6, a0, s7
	mul	a1, a0, s6
	add	s1, a1, a1
	mul	a2, a0, s1
	add	s5, a2, a2
	mul	a3, a0, s5
	add	a7, a3, a3
	mul	a4, a0, a7
	add	s3, a4, a4
	mul	a5, a0, s3
	add	s0, a5, a5
	slli	s2, s0, a0
	add	dp, a0, s2
	lw	s4, dp
	mv	a6, s4
	mv	a0, a6
	j	.L10
.L9:
	add	s0, a0, a1
	add	a7, s0, a2
	add	a6, a7, a3
	add	a0, a6, a4
	beqz	a0, .L11
	j	.L13
.L10:
.L11:
	li	a0, a0
	j	.L10
.L13:
	bnez	a0, .L14
	j	.L16
.L14:
	mv	a0
	mv	a0
	call	a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L1
	mv	s3, a0
	sub	s4, a0, s3
	addi	s6, a0, a6
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	s1, a0
	mul	s7, s4, s1
	addi	s8, s7, a6
	la	s2, 0(sp)
	lw	s0, 0(sp)
	rem	s9, s8, s0
	j	.L16
.L16:
.L17:
	mv	a0
	mv	a0
	call	a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L1
	mv	s6, a0
	sub	s7, a1, s6
	addi	s8, a0, a6
	addi	s9, a1, a6
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	s4, a0
	mul	s10, s7, s4
	addi	s2, s10, a6
	la	s0, 0(sp)
	lw	s3, 0(sp)
	rem	s1, s2, s3
	j	.L19
.L19:
.L20:
	mv	a0
	mv	a0
	call	a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L1
	mv	s3, a0
	sub	s2, a2, s3
	addi	s10, a1, a6
	addi	s6, a2, a6
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	s1, a0
	mul	s8, s2, s1
	addi	s7, s8, a6
	la	s4, 0(sp)
	lw	s9, 0(sp)
	rem	s0, s7, s9
	j	.L22
.L22:
.L23:
	mv	a0
	mv	a0
	call	a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L1
	mv	s1, a0
	sub	s4, a3, s1
	addi	s7, a2, a6
	addi	s6, a3, a6
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	s8, a0
	mul	s2, s4, s8
	addi	s3, s2, a6
	la	s10, 0(sp)
	lw	s0, 0(sp)
	rem	s9, s3, s0
	j	.L25
.L25:
.L26:
	addi	s0, a3, a6
	addi	s1, a4, a6
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	s8, a0
	mul	s2, a4, s8
	addi	s6, s2, a6
	la	s5, 0(sp)
	lw	s4, 0(sp)
	rem	s7, s6, s4
	mv	s3, s7
	mv	s5, s3
	j	.L28
.L28:
	sw	a0, 0(sp)
	la	0(sp), 0(sp)
	lw	s5, 0(sp)
	rem	s9, s5, s5
	addi	a6, a0, a1
	mul	s11, a0, a6
	sw	a0, 0(sp)
	add	0(sp), a1, s11
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	sw	a0, 0(sp)
	mul	0(sp), a0, 0(sp)
	lw	t0, 0(sp)
	add	a7, a2, 0(sp)
	sw	a0, 0(sp)
	mul	0(sp), a0, a7
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	sw	a0, 0(sp)
	add	0(sp), a3, 0(sp)
	sw	a0, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	mul	0(sp), a0, 0(sp)
	sw	a0, 0(sp)
	lw	s7, 0(sp)
	add	0(sp), a4, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	mul	s4, a0, 0(sp)
	add	s1, a5, s4
	slli	s6, s1, a0
	add	dp, a0, s6
	mv	s2, s9
	sw	s2, dp
	sw	a0, 0(sp)
	addi	0(sp), a0, a1
	lw	s3, 0(sp)
	mul	t1, a0, 0(sp)
	sw	a0, 0(sp)
	add	0(sp), a1, t1
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	sw	a0, 0(sp)
	mul	0(sp), a0, 0(sp)
	lw	s0, 0(sp)
	add	ra, a2, 0(sp)
	sw	a0, 0(sp)
	mul	0(sp), a0, ra
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	add	t3, a3, 0(sp)
	sw	a0, 0(sp)
	mul	0(sp), a0, t3
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	add	t2, a4, 0(sp)
	sw	a0, 0(sp)
	mul	0(sp), a0, t2
	sw	a0, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	add	0(sp), a5, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	slli	s10, 0(sp), a0
	add	dp, a0, s10
	lw	s8, dp
	sw	a0, 0(sp)
	mv	0(sp), s8
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	mv	a0, 0(sp)
	j	.L10
	.text
	.global main
main:
	call	a0, a1, a2, a3, a4, a5, a6, a7
	mv	s0, a0
	mv	s0, s0
	li	s2, a0
	j	.L30
.L30:
	la	a1, 0(sp)
	lw	a0, 0(sp)
	blt	s2, a0, .L31
	j	.L32
.L31:
	li	s3, a0
	j	.L33
.L32:
	li	a1, a0
	j	.L48
.L33:
	la	a1, 0(sp)
	lw	a0, 0(sp)
	blt	s3, a0, .L34
	j	.L35
.L48:
	blt	a1, s0, .L49
	j	.L50
.L34:
	li	a3, a0
	j	.L36
.L35:
	addi	a1, s2, a2
	mv	a0, a1
	mv	s2, a0
	j	.L30
.L49:
	call	a0, a1, a2, a3, a4, a5, a6, a7
	mv	t2, a0
	sw	a0, 0(sp)
	addi	0(sp), a1, a0
	sw	a0, 0(sp)
	lw	t1, 0(sp)
	slli	0(sp), 0(sp), a0
	lw	s5, 0(sp)
	add	list, a0, 0(sp)
	mv	s6, t2
	sw	s6, list
	sw	a0, 0(sp)
	addi	0(sp), a1, a0
	sw	a0, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	slli	0(sp), 0(sp), a0
	lw	s1, 0(sp)
	add	list, a0, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), list
	lw	t0, 0(sp)
	sw	a0, 0(sp)
	addi	0(sp), 0(sp), a0
	sw	a0, 0(sp)
	lw	s2, 0(sp)
	slli	0(sp), 0(sp), a0
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	add	cns, a0, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), cns
	sw	a0, 0(sp)
	lw	s9, 0(sp)
	addi	0(sp), 0(sp), a0
	sw	a0, 0(sp)
	addi	0(sp), a1, a0
	lw	s3, 0(sp)
	slli	s4, 0(sp), a0
	add	list, a0, s4
	sw	a0, 0(sp)
	lw	0(sp), list
	lw	s10, 0(sp)
	sw	a0, 0(sp)
	addi	0(sp), 0(sp), a0
	lw	s7, 0(sp)
	sw	a0, 0(sp)
	slli	0(sp), 0(sp), a0
	lw	t3, 0(sp)
	add	cns, a0, 0(sp)
	lw	s8, 0(sp)
	sw	a0, 0(sp)
	mv	0(sp), 0(sp)
	sw	a0, 0(sp)
	sw	0(sp), cns
	addi	s11, a1, a0
	mv	ra, s11
	mv	a1, ra
	j	.L48
.L50:
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	s0, a0
	mv	s1, s0
	mv	a0
	call	a0, a0, a1, a2, a3, a4, a5, a6, a7
	mv	a0, s1
	j	.L51
.L36:
	la	a0, 0(sp)
	lw	a1, 0(sp)
	blt	a3, a1, .L37
	j	.L38
.L51:
.L37:
	li	s6, a0
	j	.L39
.L38:
	addi	a2, s3, a1
	mv	a0, a2
	mv	s3, a0
	j	.L33
.L39:
	la	a0, 0(sp)
	lw	a1, 0(sp)
	blt	s6, a1, .L40
	j	.L41
.L40:
	li	s8, a0
	j	.L42
.L41:
	addi	a1, a3, a0
	mv	a2, a1
	mv	a3, a2
	j	.L36
.L42:
	la	a0, 0(sp)
	lw	a1, 0(sp)
	blt	s8, a1, .L43
	j	.L44
.L43:
	li	t1, a0
	j	.L45
.L44:
	addi	a0, s6, a2
	mv	a1, a0
	mv	s6, a1
	j	.L39
.L45:
	blt	t1, a0, .L46
	j	.L47
.L46:
	addi	s10, s2, t1
	mul	s5, s10, s10
	add	s7, s3, s5
	mul	s4, s7, s7
	add	a1, a3, s4
	mul	a4, a1, a1
	add	a0, s6, a4
	mul	a5, a0, a0
	add	t0, s8, a5
	mul	s11, t0, t0
	add	s1, t1, s11
	slli	a2, s1, s1
	add	dp, a2, a2
	li	s9, t1
	sw	s9, dp
	addi	a7, t1, t2
	mv	a6, a7
	mv	t1, a6
	j	.L45
.L47:
	addi	a1, s8, a0
	mv	a2, a1
	mv	s8, a2
	j	.L42
