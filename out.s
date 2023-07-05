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
	li	a0, 1
	mv	a0, a0
	j	.L5
.L4:
	li	a0, 0
	mv	a0, a0
	j	.L5
.L5:
	.text
	.global dfs
dfs:
	addi	s1, a0, 0
	li	s1, 18
	mul	s1, s1, s1
	add	s1, a1, s1
	li	s1, 18
	mul	s1, s1, s1
	add	s1, a2, s1
	li	s1, 18
	mul	s1, s1, s1
	add	s1, a3, s1
	li	s1, 18
	mul	s1, s1, s1
	add	s1, a4, s1
	li	s1, 7
	mul	s1, s1, s1
	add	s1, a5, s1
	slli	s1, s1, 2
	add	s1, dp, s1
	li	s1, -1
	bne	s1, s1, .L7
	j	.L9
.L7:
	addi	a0, a0, 0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a1, a0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a2, a0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a3, a0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a4, a0
	li	a0, 7
	mul	a0, a0, a0
	add	a0, a5, a0
	slli	a0, a0, 2
	add	a0, dp, a0
	mv	a0, a0
	mv	a0, a0
	j	.L10
.L9:
	add	s1, a0, a1
	add	s1, s1, a2
	add	s1, s1, a3
	add	s1, s1, a4
	beqz	s1, .L11
	j	.L13
.L10:
.L11:
	li	a0, 1
	mv	a0, a0
	j	.L10
.L13:
	bnez	a0, .L14
	j	.L16
.L14:
	li	s1, 2
	mv	a1, s1
	mv	a0, a5
	call	equal
	mv	s1, a0
	sub	s1, a0, s1
	addi	s1, a0, -1
	li	s1, 1
	mv	a5, s1
	mv	a4, a4
	mv	a3, a3
	mv	a2, a2
	mv	a1, a1
	mv	a0, s1
	call	dfs
	mv	s1, a0
	mul	s1, s1, s1
	addi	s1, s1, 0
	rem	, s1, 498650688(zero)
	j	.L16
.L16:
.L17:
	li	s1, 3
	mv	a1, s1
	mv	a0, a5
	call	equal
	mv	s1, a0
	sub	s1, a1, s1
	addi	s1, a0, 1
	addi	s1, a1, -1
	li	s1, 2
	mv	a5, s1
	mv	a4, a4
	mv	a3, a3
	mv	a2, a2
	mv	a1, s1
	mv	a0, s1
	call	dfs
	mv	s1, a0
	mul	s1, s1, s1
	addi	s1, s1, 0
	rem	, s1, 498650688(zero)
	j	.L19
.L19:
.L20:
	li	s1, 4
	mv	a1, s1
	mv	a0, a5
	call	equal
	mv	s1, a0
	sub	s1, a2, s1
	addi	s1, a1, 1
	addi	s1, a2, -1
	li	s1, 3
	mv	a5, s1
	mv	a4, a4
	mv	a3, a3
	mv	a2, s1
	mv	a1, s1
	mv	a0, a0
	call	dfs
	mv	s1, a0
	mul	s1, s1, s1
	addi	s1, s1, 0
	rem	, s1, 498650688(zero)
	j	.L22
.L22:
.L23:
	li	s1, 5
	mv	a1, s1
	mv	a0, a5
	call	equal
	mv	s1, a0
	sub	s1, a3, s1
	addi	s1, a2, 1
	addi	s1, a3, -1
	li	s1, 4
	mv	a5, s1
	mv	a4, a4
	mv	a3, s1
	mv	a2, s1
	mv	a1, a1
	mv	a0, a0
	call	dfs
	mv	s1, a0
	mul	s1, s1, s1
	addi	s1, s1, 0
	rem	, s1, 498650688(zero)
	j	.L25
.L25:
.L26:
	addi	a6, a3, 1
	addi	a6, a4, -1
	li	a6, 5
	mv	a5, a6
	mv	a4, a6
	mv	a3, a6
	mv	a2, a2
	mv	a1, a1
	mv	a0, a0
	call	dfs
	mv	a6, a0
	mul	a6, a4, a6
	addi	a6, a6, 0
	rem	a6, a6, 498650688(zero)
	mv	a6, a6
	mv	s0, a6
	j	.L28
.L28:
	rem	a0, s0, 498650688(zero)
	addi	a0, a0, 0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a1, a0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a2, a0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a3, a0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a4, a0
	li	a0, 7
	mul	a0, a0, a0
	add	a0, a5, a0
	slli	a0, a0, 2
	add	, dp, a0
	mv	, a0
	addi	a0, a0, 0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a1, a0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a2, a0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a3, a0
	li	a0, 18
	mul	a0, a0, a0
	add	a0, a4, a0
	li	a0, 7
	mul	a0, a0, a0
	add	a0, a5, a0
	slli	a0, a0, 2
	add	a0, dp, a0
	mv	a0, a0
	mv	a0, a0
	j	.L10
	.text
	.global main
main:
	call	getint
	mv	s7, a0
	mv	s4, s7
	li	s7, 0
	mv	s6, s7
	j	.L30
.L30:
	blt	s6, 498650688(zero), .L31
	j	.L32
.L31:
	li	s8, 0
	mv	s7, s8
	j	.L33
.L32:
	li	s7, 0
	mv	s6, s7
	j	.L48
.L33:
	blt	s7, 498650688(zero), .L34
	j	.L35
.L48:
	blt	s6, s4, .L49
	j	.L50
.L34:
	li	s9, 0
	mv	s8, s9
	j	.L36
.L35:
	addi	s7, s6, 1
	mv	s7, s7
	mv	s6, s7
	j	.L30
.L49:
	call	getint
	mv	s7, a0
	addi	s7, s6, 0
	slli	s7, s7, 2
	add	, list, s7
	mv	, s7
	addi	s7, s6, 0
	slli	s7, s7, 2
	add	s7, list, s7
	addi	s7, s7, 0
	slli	s7, s7, 2
	add	s7, cns, s7
	addi	s7, s7, 1
	addi	s7, s6, 0
	slli	s7, s7, 2
	add	s7, list, s7
	addi	s7, s7, 0
	slli	s7, s7, 2
	add	, cns, s7
	mv	, s7
	addi	s7, s6, 1
	mv	s7, s7
	mv	s6, s7
	j	.L48
.L50:
	li	a0, 0
	mv	a5, a0
	mv	a4, s3
	mv	a3, s2
	mv	a2, s1
	mv	a1, s0
	mv	a0, s5
	call	dfs
	mv	a0, a0
	mv	a0, a0
	mv	a0, a0
	call	putint
	mv	a0, a0
	j	.L51
.L36:
	blt	s8, 498650688(zero), .L37
	j	.L38
.L51:
.L37:
	li	s10, 0
	mv	s9, s10
	j	.L39
.L38:
	addi	s8, s7, 1
	mv	s8, s8
	mv	s7, s8
	j	.L33
.L39:
	blt	s9, 498650688(zero), .L40
	j	.L41
.L40:
	li	s11, 0
	mv	s10, s11
	j	.L42
.L41:
	addi	s9, s8, 1
	mv	s9, s9
	mv	s8, s9
	j	.L36
.L42:
	blt	s10, 498650688(zero), .L43
	j	.L44
.L43:
	li	ra, 0
	mv	s11, ra
	j	.L45
.L44:
	addi	s10, s9, 1
	mv	s10, s10
	mv	s9, s10
	j	.L39
.L45:
	li	ra, 7
	blt	s11, ra, .L46
	j	.L47
.L46:
	addi	ra, s6, 0
	li	ra, 18
	mul	ra, ra, ra
	add	ra, s7, ra
	li	ra, 18
	mul	ra, ra, ra
	add	ra, s8, ra
	li	ra, 18
	mul	ra, ra, ra
	add	ra, s9, ra
	li	ra, 18
	mul	ra, ra, ra
	add	ra, s10, ra
	li	ra, 7
	mul	ra, ra, ra
	add	ra, s11, ra
	slli	ra, ra, 2
	add	, dp, ra
	li	ra, -1
	mv	, ra
	addi	ra, s11, 1
	mv	ra, ra
	mv	s11, ra
	j	.L45
.L47:
	addi	s11, s10, 1
	mv	s11, s11
	mv	s10, s11
	j	.L42
