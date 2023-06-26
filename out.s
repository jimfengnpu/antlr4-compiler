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
	addi	a5, s1, s9
	mul	a1, a5, a5
	add	s11, s0, a1
	mul	a0, s9, s11
	add	a7, s3, a0
	mul	a2, a7, a7
	add	s6, s2, a2
	mul	s7, s6, s6
	add	a3, s4, s7
	mul	a4, a3, a3
	add	a6, s5, a4
	slli	s10, a6, a6
	add	dp, s9, s10
	lw	a0, dp
	bne	a0, s9, .L7
	j	.L9
.L7:
	addi	s6, s1, s4
	mul	s0, s1, s6
	add	s8, s0, s0
	mul	s3, s1, s8
	add	a2, s3, s3
	mul	s2, a2, a2
	add	a7, s2, s2
	mul	a1, a7, a7
	add	a5, s4, a1
	mul	a3, a5, a5
	add	a4, s5, a3
	slli	a0, a4, a4
	add	dp, a0, a0
	lw	s7, dp
	mv	a6, s7
	mv	a0, a6
	j	.L10
.L9:
	add	a2, s1, s0
	add	a1, a2, s3
	add	a0, a1, s2
	add	a0, a0, s4
	beqz	a0, .L11
	j	.L13
.L10:
.L11:
	li	a0, a0
	j	.L10
.L13:
	bnez	s1, .L14
	j	.L16
.L14:
	mv	a0
	mv	a0
	call	a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L1
	mv	s7, a0
	sub	t1, s1, s7
	addi	s6, s1, a1
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	t2, a0
	mul	s9, t1, t2
	addi	t3, s9, a1
	la	s11, 0(sp)
	lw	t0, 0(sp)
	rem	s10, t3, t0
	j	.L16
.L16:
.L17:
	mv	a0
	mv	a0
	call	a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L1
	mv	t2, a0
	sub	t3, s0, t2
	addi	s9, s1, a1
	addi	s10, s0, a1
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	s11, a0
	mul	t1, t3, s11
	addi	s6, t1, a1
	la	t0, 0(sp)
	lw	ra, 0(sp)
	rem	s7, s6, ra
	j	.L19
.L19:
.L20:
	mv	a0
	mv	a0
	call	a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L1
	mv	t3, a0
	sub	s9, s3, t3
	addi	s6, s0, a1
	addi	t0, s3, a1
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	ra, a0
	mul	s10, s9, ra
	addi	t1, s10, a1
	la	s11, 0(sp)
	lw	s7, 0(sp)
	rem	t2, t1, s7
	j	.L22
.L22:
.L23:
	mv	a0
	mv	a0
	call	a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L1
	mv	ra, a0
	sub	s7, s2, ra
	addi	t1, s3, a1
	addi	s6, s2, a1
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	s11, a0
	mul	s9, s7, s11
	addi	t2, s9, a1
	la	t3, 0(sp)
	lw	s10, 0(sp)
	rem	t0, t2, s10
	j	.L25
.L25:
.L26:
	addi	t1, s2, a1
	addi	t2, s4, a1
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	mv	a0
	call	a0, a0, a0, a0, a0, a0, a0, a1, a2, a3, a4, a5, a6, a7, .L6
	mv	s8, a0
	mul	s6, s4, s8
	addi	s9, s6, a1
	la	t0, 0(sp)
	lw	s11, 0(sp)
	rem	s7, s9, s11
	mv	s10, s7
	mv	s8, s10
	j	.L28
.L28:
	la	s6, 0(sp)
	lw	s8, 0(sp)
	sw	s0, 0(sp)
	rem	0(sp), s8, s8
	addi	a6, s1, s0
	mul	a3, a6, a6
	add	a0, s0, a3
	sw	s0, 0(sp)
	mul	0(sp), a0, a0
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	add	a1, s3, 0(sp)
	sw	s0, 0(sp)
	mul	0(sp), a1, a1
	sw	s0, 0(sp)
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	add	0(sp), s2, 0(sp)
	lw	t3, 0(sp)
	mul	a7, s0, 0(sp)
	sw	s0, 0(sp)
	add	0(sp), s4, a7
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	sw	s0, 0(sp)
	mul	0(sp), s0, 0(sp)
	lw	s10, 0(sp)
	add	s11, s5, 0(sp)
	slli	a4, s11, s0
	add	dp, a4, a4
	sw	s0, 0(sp)
	lw	a5, 0(sp)
	mv	0(sp), 0(sp)
	sw	s0, 0(sp)
	sw	0(sp), dp
	sw	s0, 0(sp)
	addi	0(sp), s1, s0
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	sw	s0, 0(sp)
	mul	0(sp), s0, 0(sp)
	sw	s0, 0(sp)
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	add	0(sp), s0, 0(sp)
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	sw	s0, 0(sp)
	mul	0(sp), s0, 0(sp)
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	sw	s0, 0(sp)
	add	0(sp), s3, 0(sp)
	sw	s0, 0(sp)
	lw	ra, 0(sp)
	mul	0(sp), s0, 0(sp)
	lw	t2, 0(sp)
	sw	s0, 0(sp)
	add	0(sp), s2, 0(sp)
	sw	s0, 0(sp)
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	mul	0(sp), s0, 0(sp)
	lw	s7, 0(sp)
	sw	s0, 0(sp)
	add	0(sp), s4, 0(sp)
	lw	s9, 0(sp)
	mul	a2, s0, 0(sp)
	sw	s0, 0(sp)
	add	0(sp), s5, a2
	sw	s0, 0(sp)
	lw	t0, 0(sp)
	slli	0(sp), 0(sp), s0
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	add	dp, s0, 0(sp)
	sw	s0, 0(sp)
	lw	0(sp), dp
	sw	s0, 0(sp)
	lw	0(sp), 0(sp)
	sw	s0, 0(sp)
	mv	0(sp), 0(sp)
	lw	t1, 0(sp)
	mv	a0, 0(sp)
	j	.L10
	.text
	.global main
main:
	call	a0, a1, a2, a3, a4, a5, a6, a7
	mv	s0, a0
	mv	s0, s0
	li	s3, a0
	j	.L30
.L30:
	la	a1, 0(sp)
	lw	a0, 0(sp)
	blt	s3, a0, .L31
	j	.L32
.L31:
	li	a6, a0
	j	.L33
.L32:
	li	a1, a0
	j	.L48
.L33:
	la	a1, 0(sp)
	lw	a0, 0(sp)
	blt	a6, a0, .L34
	j	.L35
.L48:
	blt	a1, s0, .L49
	j	.L50
.L34:
	li	a7, a0
	j	.L36
.L35:
	addi	a1, s3, a2
	mv	a0, a1
	mv	s3, a0
	j	.L30
.L49:
	call	a0, a1, a2, a3, a4, a5, a6, a7
	mv	t2, a0
	addi	t3, a1, a0
	slli	ra, t3, a0
	add	list, a0, ra
	mv	s6, t2
	sw	s6, list
	sw	a0, 0(sp)
	addi	0(sp), a1, a0
	sw	a0, 0(sp)
	lw	s9, 0(sp)
	slli	0(sp), 0(sp), a0
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	add	list, a0, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), list
	lw	t0, 0(sp)
	addi	s11, 0(sp), a0
	sw	a0, 0(sp)
	slli	0(sp), s11, a0
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	add	cns, a0, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), cns
	lw	s8, 0(sp)
	addi	s5, 0(sp), a0
	sw	a0, 0(sp)
	addi	0(sp), a1, a0
	lw	s7, 0(sp)
	sw	a0, 0(sp)
	slli	0(sp), 0(sp), a0
	lw	s4, 0(sp)
	add	list, a0, 0(sp)
	sw	a0, 0(sp)
	lw	0(sp), list
	sw	a0, 0(sp)
	lw	0(sp), 0(sp)
	addi	s10, 0(sp), a0
	sw	a0, 0(sp)
	slli	0(sp), s10, a0
	lw	s1, 0(sp)
	add	cns, a0, 0(sp)
	mv	s3, s5
	sw	s3, cns
	addi	s2, a1, a0
	mv	t1, s2
	mv	a1, t1
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
	la	a1, 0(sp)
	lw	a0, 0(sp)
	blt	a7, a0, .L37
	j	.L38
.L51:
.L37:
	li	s8, a0
	j	.L39
.L38:
	addi	a2, a6, a1
	mv	a0, a2
	mv	a6, a0
	j	.L33
.L39:
	la	a1, 0(sp)
	lw	a0, 0(sp)
	blt	s8, a0, .L40
	j	.L41
.L40:
	li	s9, a0
	j	.L42
.L41:
	addi	a1, a7, a0
	mv	a2, a1
	mv	a7, a2
	j	.L36
.L42:
	la	a1, 0(sp)
	lw	a0, 0(sp)
	blt	s9, a0, .L43
	j	.L44
.L43:
	li	t1, a0
	j	.L45
.L44:
	addi	a0, s8, a2
	mv	a1, a0
	mv	s8, a1
	j	.L39
.L45:
	blt	t1, a0, .L46
	j	.L47
.L46:
	addi	s10, s3, t1
	mul	s11, s10, s10
	add	s7, a6, s11
	mul	a4, s7, s7
	add	s1, a7, a4
	mul	s5, s1, s1
	add	t0, s8, s5
	mul	s2, t0, t0
	add	a3, s9, s2
	mul	s4, a3, a3
	add	a0, t1, s4
	slli	a1, a0, a0
	add	dp, a1, a1
	li	s6, t1
	sw	s6, dp
	addi	a5, t1, t2
	mv	a2, a5
	mv	t1, a2
	j	.L45
.L47:
	addi	a1, s9, a0
	mv	a2, a1
	mv	s9, a2
	j	.L42
