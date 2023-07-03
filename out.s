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
	j	.L5
.L4:
	li	a0, 0
	j	.L5
.L5:
	.text
	.global dfs
dfs:
	addi	a6, a0, 0
	li	a7, 18
	mul	a6, a7, a6
	add	a6, a1, a6
	li	a7, 18
	mul	a6, a7, a6
	add	a6, a2, a6
	li	a7, 18
	mul	a6, a7, a6
	add	a6, a3, a6
	li	a7, 18
	mul	a6, a7, a6
	add	a6, a4, a6
	li	a7, 7
	mul	a6, a7, a6
	add	a6, a5, a6
	slli	a7, a6, 2
	la	a6, dp
	add	a6, a6, a7
	lw	a6, 0(a6)
	li	a7, -1
	bne	a6, a7, .L7
	j	.L9
.L7:
	addi	a6, a0, 0
	li	a0, 18
	mul	a0, a0, a6
	add	a1, a1, a0
	li	a0, 18
	mul	a0, a0, a1
	add	a0, a2, a0
	li	a1, 18
	mul	a0, a1, a0
	add	a0, a3, a0
	li	a1, 18
	mul	a0, a1, a0
	add	a0, a4, a0
	li	a1, 7
	mul	a0, a1, a0
	add	a0, a5, a0
	slli	a0, a0, 2
	la	a1, dp
	add	a0, a1, a0
	lw	a0, 0(a0)
	mv	a0, a0
	mv	a0, a0
	j	.L10
.L9:
	add	a6, a0, a1
	add	a6, a6, a2
	add	a6, a6, a3
	add	a6, a6, a4
	beqz	a6, .L11
	j	.L13
.L10:
.L11:
	li	a0, 1
	j	.L10
.L13:
	bnez	a0, .L14
	j	.L16
.L14:
	li	a1, 2
	mv	a1, a1
	mv	a0, a5
	call	equal
	mv	s1, a0
	sub	s1, a0, s1
	addi	s2, a0, -1
	li	s3, 1
	mv	a5, s3
	mv	a4, a4
	mv	a3, a3
	mv	a2, a2
	mv	a1, a1
	mv	a0, s2
	call	dfs
	mv	a6, a0
	mul	a6, s1, a6
	addi	a6, a6, 0
	la	a7, mod
	rem	a0, a6, a7
	j	.L16
.L16:
.L17:
	li	a1, 3
	mv	a1, a1
	mv	a0, a5
	call	equal
	mv	s1, a0
	sub	s1, a1, s1
	addi	s2, a0, 1
	addi	a1, a1, -1
	li	s3, 2
	mv	a5, s3
	mv	a4, a4
	mv	a3, a3
	mv	a2, a2
	mv	a1, a1
	mv	a0, s2
	call	dfs
	mv	a6, a0
	mul	a6, s1, a6
	addi	a6, a6, 0
	la	a7, mod
	rem	a0, a6, a7
	j	.L19
.L19:
.L20:
	li	a1, 4
	mv	a1, a1
	mv	a0, a5
	call	equal
	mv	s1, a0
	sub	s1, a2, s1
	addi	a1, a1, 1
	addi	a2, a2, -1
	li	s2, 3
	mv	a5, s2
	mv	a4, a4
	mv	a3, a3
	mv	a2, a2
	mv	a1, a1
	mv	a0, a0
	call	dfs
	mv	a6, a0
	mul	a6, s1, a6
	addi	a6, a6, 0
	la	a7, mod
	rem	a0, a6, a7
	j	.L22
.L22:
.L23:
	li	a1, 5
	mv	a1, a1
	mv	a0, a5
	call	equal
	mv	s1, a0
	sub	s1, a3, s1
	addi	a2, a2, 1
	addi	a3, a3, -1
	li	s2, 4
	mv	a5, s2
	mv	a4, a4
	mv	a3, a3
	mv	a2, a2
	mv	a1, a1
	mv	a0, a0
	call	dfs
	mv	a6, a0
	mul	a6, s1, a6
	addi	a6, a6, 0
	la	a7, mod
	rem	a0, a6, a7
	j	.L25
.L25:
.L26:
	addi	a3, a3, 1
	addi	a4, a4, -1
	li	a5, 5
	mv	a5, a5
	mv	a4, a4
	mv	a3, a3
	mv	a2, a2
	mv	a1, a1
	mv	a0, a0
	call	dfs
	mv	a6, a0
	mul	a6, a4, a6
	addi	a6, a6, 0
	la	a7, mod
	rem	a6, a6, a7
	mv	a6, a6
	mv	s0, a6
	j	.L28
.L28:
	la	a6, mod
	rem	a7, s0, a6
	addi	a6, a0, 0
	li	s0, 18
	mul	a6, s0, a6
	add	s0, a1, a6
	li	a6, 18
	mul	a6, a6, s0
	add	a6, a2, a6
	li	s0, 18
	mul	a6, s0, a6
	add	s0, a3, a6
	li	a6, 18
	mul	a6, a6, s0
	add	a6, a4, a6
	li	s0, 7
	mul	a6, s0, a6
	add	a6, a5, a6
	slli	s0, a6, 2
	la	a6, dp
	add	a0, a6, s0
	mv	a6, a7
	sw	a6, 0(a0)
	addi	a6, a0, 0
	li	a0, 18
	mul	a0, a0, a6
	add	a0, a1, a0
	li	a1, 18
	mul	a0, a1, a0
	add	a1, a2, a0
	li	a0, 18
	mul	a0, a0, a1
	add	a1, a3, a0
	li	a0, 18
	mul	a0, a0, a1
	add	a1, a4, a0
	li	a0, 7
	mul	a0, a0, a1
	add	a0, a5, a0
	slli	a1, a0, 2
	la	a0, dp
	add	a0, a0, a1
	lw	a0, 0(a0)
	mv	a0, a0
	mv	a0, a0
	j	.L10
	.text
	.global main
main:
	call	getint
	mv	a0, a0
	mv	a3, a0
	li	a1, 0
	j	.L30
.L30:
	la	a0, maxn
	blt	a1, a0, .L31
	j	.L32
.L31:
	li	a0, 0
	j	.L33
.L32:
	li	a1, 0
	j	.L48
.L33:
	la	a2, maxn
	blt	a0, a2, .L34
	j	.L35
.L48:
	blt	a1, a3, .L49
	j	.L50
.L34:
	li	a7, 0
	j	.L36
.L35:
	addi	a0, a1, 1
	mv	a0, a0
	mv	a1, a0
	j	.L30
.L49:
	call	getint
	mv	a2, a0
	addi	a0, a1, 0
	slli	a4, a0, 2
	la	a0, list
	add	a0, a0, a4
	mv	a0, a2
	sw	a0, 0(a0)
	addi	a0, a1, 0
	slli	a2, a0, 2
	la	a0, list
	add	a0, a0, a2
	lw	a0, 0(a0)
	addi	a0, a0, 0
	slli	a2, a0, 2
	la	a0, cns
	add	a0, a0, a2
	lw	a0, 0(a0)
	addi	a0, a0, 1
	addi	a2, a1, 0
	slli	a4, a2, 2
	la	a2, list
	add	a2, a2, a4
	lw	a2, 0(a2)
	addi	a2, a2, 0
	slli	a4, a2, 2
	la	a2, cns
	add	a0, a2, a4
	mv	a0, a0
	sw	a0, 0(a0)
	addi	a0, a1, 1
	mv	a0, a0
	mv	a1, a0
	j	.L48
.L50:
	li	s5, 0
	mv	a5, s5
	lw	s4, 80(s4)
	mv	a4, s4
	lw	s3, 64(s3)
	mv	a3, s3
	lw	s2, 48(s2)
	mv	a2, s2
	lw	s1, 32(s1)
	mv	a1, s1
	lw	s0, 16(s0)
	mv	a0, s0
	call	dfs
	mv	a0, a0
	mv	s1, a0
	mv	a0, s1
	call	putint
	mv	s0, s1
	j	.L51
.L36:
	la	a2, maxn
	blt	a7, a2, .L37
	j	.L38
.L51:
.L37:
	li	a4, 0
	j	.L39
.L38:
	addi	a0, a0, 1
	mv	a0, a0
	mv	a0, a0
	j	.L33
.L39:
	la	a2, maxn
	blt	a4, a2, .L40
	j	.L41
.L40:
	li	a2, 0
	j	.L42
.L41:
	addi	a2, a7, 1
	mv	a2, a2
	mv	a7, a2
	j	.L36
.L42:
	la	a5, maxn
	blt	a2, a5, .L43
	j	.L44
.L43:
	li	a5, 0
	j	.L45
.L44:
	addi	a2, a4, 1
	mv	a2, a2
	mv	a4, a2
	j	.L39
.L45:
	li	a6, 7
	blt	a5, a6, .L46
	j	.L47
.L46:
	addi	s0, a1, 0
	li	a6, 18
	mul	a6, a6, s0
	add	s0, a0, a6
	li	a6, 18
	mul	a6, a6, s0
	add	s0, a7, a6
	li	a6, 18
	mul	a6, a6, s0
	add	s0, a4, a6
	li	a6, 18
	mul	a6, a6, s0
	add	s0, a2, a6
	li	a6, 7
	mul	a6, a6, s0
	add	a6, a5, a6
	slli	s0, a6, 2
	la	a6, dp
	add	a0, a6, s0
	li	a6, -1
	sw	a6, 0(a0)
	addi	a5, a5, 1
	mv	a5, a5
	mv	a5, a5
	j	.L45
.L47:
	addi	a2, a2, 1
	mv	a2, a2
	mv	a2, a2
	j	.L42
