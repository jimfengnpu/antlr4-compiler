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
	addi	sp,sp,-8
	sd	s0,0(s0)
	addi	s0,sp,8
	addi	sp,sp,-8
	beq	a0,a1, .L2
	j	.L4
.L2:
	li	a0,1
	j	.L5
.L5:
	ld	s0,0(s0)
	addi	sp,sp,8
	addi	sp,sp,8
	ret
.L4:
	li	a0,0
	j	.L5
	.text
	.global dfs
dfs:
	addi	sp,sp,-88
	sd	ra,80(s0)
	sd	s0,72(s0)
	sd	s9,64(s0)
	sd	s8,56(s0)
	sd	s7,48(s0)
	sd	s6,40(s0)
	sd	s5,32(s0)
	sd	s4,24(s0)
	sd	s3,16(s0)
	sd	s2,8(s0)
	sd	s1,0(s0)
	addi	s0,sp,88
	addi	sp,sp,-8
	addi	a7,a0,0
	li	a6,18
	mul	a6,a6,a7
	add	a6,a1,a6
	li	a7,18
	mul	a6,a7,a6
	add	a7,a2,a6
	li	a6,18
	mul	a6,a6,a7
	add	a6,a3,a6
	li	a7,18
	mul	a6,a7,a6
	add	a7,a4,a6
	li	a6,7
	mul	a6,a6,a7
	add	a6,a5,a6
	slli	a6,a6,2
	la	a7,dp
	addi	a6,a6,0
	add	a7,a7,a6
	li	a6,-1
	lw	a7,0(a7)
	bne	a7,a6, .L7
	j	.L9
.L7:
	addi	a0,a0,0
	li	a6,18
	mul	a0,a6,a0
	add	a1,a1,a0
	li	a0,18
	mul	a0,a0,a1
	add	a1,a2,a0
	li	a0,18
	mul	a0,a0,a1
	add	a1,a3,a0
	li	a0,18
	mul	a0,a0,a1
	add	a1,a4,a0
	li	a0,7
	mul	a0,a0,a1
	add	a0,a5,a0
	slli	a0,a0,2
	la	a1,dp
	addi	a0,a0,0
	add	a0,a1,a0
	lw	a0,0(a0)
	j	.L10
.L10:
	ld	s1,0(s0)
	ld	s2,8(s0)
	ld	s3,16(s0)
	ld	s4,24(s0)
	ld	s5,32(s0)
	ld	s6,40(s0)
	ld	s7,48(s0)
	ld	s8,56(s0)
	ld	s9,64(s0)
	ld	s0,72(s0)
	ld	ra,80(s0)
	addi	sp,sp,8
	addi	sp,sp,88
	ret
.L9:
	add	a6,a0,a1
	add	a6,a6,a2
	add	a6,a6,a3
	add	a6,a6,a4
	beqz	a6, .L11
	j	.L13
.L11:
	li	a0,1
	j	.L10
.L13:
	bnez	a0, .L14
	j	.L16
.L14:
	li	a6,2
	mv	s4,a1
	mv	a1,a6
	mv	s3,a0
	mv	s5,a4
	mv	s6,a2
	mv	a6,a0
	mv	a5,a0
	mv	a4,a0
	mv	a3,a0
	mv	a0,a5
	call	equal
	mv	a3,a4
	mv	a5,a6
	mv	a2,s6
	mv	a4,s5
	mv	a1,s4
	mv	a6,a0
	mv	a0,s3
	sub	s3,a0,a6
	addi	a6,a0,-1
	li	a7,1
	mv	s5,a5
	mv	a5,a7
	mv	s4,a4
	mv	s7,a3
	mv	s8,a2
	mv	s9,a1
	mv	s6,a0
	mv	a0,a6
	call	dfs
	mv	a1,s9
	mv	a2,s8
	mv	a3,s7
	mv	a4,s4
	mv	a5,s5
	mv	a6,a0
	mv	a0,s6
	mul	a6,s3,a6
	addi	a6,a6,0
	la	a7,mod
	lw	a7,0(a7)
	rem	a6,a6,a7
	j	.L16
.L16:
.L17:
	li	a6,3
	mv	s3,a1
	mv	a1,a6
	mv	a6,a0
	mv	a5,a0
	mv	a7,a0
	mv	a4,a0
	mv	s5,a0
	mv	a3,a0
	mv	s6,a0
	mv	a2,a0
	mv	s4,a0
	mv	a0,a5
	call	equal
	mv	a1,s3
	mv	a2,s6
	mv	a3,s5
	mv	a4,a7
	mv	a5,a6
	mv	a6,a0
	mv	a0,s4
	sub	s3,a1,a6
	addi	a6,a0,1
	addi	a7,a1,-1
	li	s5,2
	mv	s4,a5
	mv	a5,s5
	mv	s5,a4
	mv	s7,a3
	mv	s8,a2
	mv	s9,a1
	mv	a1,a7
	mv	s6,a0
	mv	a0,a6
	call	dfs
	mv	a1,s9
	mv	a2,s8
	mv	a3,s7
	mv	a4,s5
	mv	a5,s4
	mv	a6,a0
	mv	a0,s6
	mul	a6,s3,a6
	addi	a6,a6,0
	la	a7,mod
	lw	a7,0(a7)
	rem	a6,a6,a7
	j	.L19
.L19:
.L20:
	li	a6,4
	mv	s3,a1
	mv	a1,a6
	mv	a6,a0
	mv	a5,a0
	mv	a7,a0
	mv	a4,a0
	mv	s5,a0
	mv	a3,a0
	mv	s6,a0
	mv	a2,a0
	mv	s4,a0
	mv	a0,a5
	call	equal
	mv	a1,s3
	mv	a2,s6
	mv	a3,s5
	mv	a4,a7
	mv	a5,a6
	mv	a6,a0
	mv	a0,s4
	sub	s3,a2,a6
	addi	a6,a1,1
	addi	a7,a2,-1
	li	s4,3
	mv	s6,a5
	mv	a5,s4
	mv	s5,a4
	mv	s7,a3
	mv	s8,a2
	mv	a2,a7
	mv	s9,a1
	mv	a1,a6
	mv	s4,a0
	call	dfs
	mv	a1,s9
	mv	a2,s8
	mv	a3,s7
	mv	a4,s5
	mv	a5,s6
	mv	a6,a0
	mv	a0,s4
	mul	a6,s3,a6
	addi	a6,a6,0
	la	a7,mod
	lw	a7,0(a7)
	rem	a6,a6,a7
	j	.L22
.L22:
.L23:
	li	a6,5
	mv	s3,a1
	mv	a1,a6
	mv	a6,a0
	mv	a5,a0
	mv	a7,a0
	mv	a4,a0
	mv	s5,a0
	mv	a3,a0
	mv	s6,a0
	mv	a2,a0
	mv	s4,a0
	mv	a0,a5
	call	equal
	mv	a1,s3
	mv	a2,s6
	mv	a3,s5
	mv	a4,a7
	mv	a5,a6
	mv	a6,a0
	mv	a0,s4
	sub	s4,a3,a6
	addi	a6,a2,1
	addi	a7,a3,-1
	li	s3,4
	mv	s6,a5
	mv	a5,s3
	mv	s5,a4
	mv	s7,a3
	mv	a3,a7
	mv	s8,a2
	mv	a2,a6
	mv	s9,a1
	mv	s3,a0
	call	dfs
	mv	a1,s9
	mv	a2,s8
	mv	a3,s7
	mv	a4,s5
	mv	a5,s6
	mv	a6,a0
	mv	a0,s3
	mul	a6,s4,a6
	addi	a6,a6,0
	la	a7,mod
	lw	a7,0(a7)
	rem	a6,a6,a7
	j	.L25
.L25:
.L26:
	addi	a6,a3,1
	addi	a7,a4,-1
	li	s2,5
	mv	s3,a5
	mv	a5,s2
	mv	s4,a4
	mv	a4,a7
	mv	s5,a3
	mv	a3,a6
	mv	s6,a2
	mv	s7,a1
	mv	s2,a0
	call	dfs
	mv	a1,s7
	mv	a2,s6
	mv	a3,s5
	mv	a4,s4
	mv	a5,s3
	mv	a6,a0
	mv	a0,s2
	mul	a6,a4,a6
	addi	a6,a6,0
	la	a7,mod
	lw	a7,0(a7)
	rem	a6,a6,a7
	mv	s2,a6
	j	.L28
.L28:
	la	a6,mod
	lw	a6,0(a6)
	rem	a6,s2,a6
	addi	a7,a0,0
	li	s1,18
	mul	a7,s1,a7
	add	a7,a1,a7
	li	s1,18
	mul	a7,s1,a7
	add	a7,a2,a7
	li	s1,18
	mul	a7,s1,a7
	add	a7,a3,a7
	li	s1,18
	mul	a7,s1,a7
	add	a7,a4,a7
	li	s1,7
	mul	a7,s1,a7
	add	a7,a5,a7
	slli	a7,a7,2
	la	s1,dp
	addi	a7,a7,0
	add	a7,s1,a7
	sw	a6,0(a7)
	addi	a6,a0,0
	li	a0,18
	mul	a0,a0,a6
	add	a0,a1,a0
	li	a1,18
	mul	a0,a1,a0
	add	a0,a2,a0
	li	a1,18
	mul	a0,a1,a0
	add	a1,a3,a0
	li	a0,18
	mul	a0,a0,a1
	add	a0,a4,a0
	li	a1,7
	mul	a0,a1,a0
	add	a0,a5,a0
	slli	a1,a0,2
	la	a0,dp
	addi	a1,a1,0
	add	a0,a0,a1
	lw	a0,0(a0)
	j	.L10
	.text
	.global main
main:
	addi	sp,sp,-40
	sd	ra,32(s0)
	sd	s0,24(s0)
	sd	s3,16(s0)
	sd	s2,8(s0)
	sd	s1,0(s0)
	addi	s0,sp,40
	addi	sp,sp,-8
	call	getint
	mv	a1,a0
	mv	a0,s1
	mv	s2,a1
	li	a1,0
	j	.L30
.L30:
	la	a2,maxn
	lw	a2,0(a2)
	blt	a1,a2, .L31
	j	.L32
.L31:
	li	a2,0
	mv	a5,a2
	j	.L33
.L33:
	la	a2,maxn
	lw	a2,0(a2)
	blt	a5,a2, .L34
	j	.L35
.L34:
	li	a2,0
	j	.L36
.L36:
	la	a3,maxn
	lw	a3,0(a3)
	blt	a2,a3, .L37
	j	.L38
.L37:
	li	a3,0
	mv	a4,a3
	j	.L39
.L39:
	la	a3,maxn
	lw	a3,0(a3)
	blt	a4,a3, .L40
	j	.L41
.L40:
	li	a3,0
	j	.L42
.L42:
	la	a6,maxn
	lw	a6,0(a6)
	blt	a3,a6, .L43
	j	.L44
.L43:
	li	a6,0
	j	.L45
.L45:
	li	a7,7
	blt	a6,a7, .L46
	j	.L47
.L46:
	addi	s3,a1,0
	li	a7,18
	mul	a7,a7,s3
	add	s3,a5,a7
	li	a7,18
	mul	a7,a7,s3
	add	a7,a2,a7
	li	s3,18
	mul	a7,s3,a7
	add	a7,a4,a7
	li	s3,18
	mul	a7,s3,a7
	add	s3,a3,a7
	li	a7,7
	mul	a7,a7,s3
	add	a7,a6,a7
	slli	a7,a7,2
	la	s3,dp
	addi	a7,a7,0
	add	s3,s3,a7
	li	a7,-1
	sw	a7,0(s3)
	addi	a6,a6,1
	j	.L45
.L47:
	addi	a3,a3,1
	j	.L42
.L44:
	addi	a3,a4,1
	mv	a4,a3
	j	.L39
.L41:
	addi	a2,a2,1
	j	.L36
.L38:
	addi	a2,a5,1
	mv	a5,a2
	j	.L33
.L35:
	addi	a1,a1,1
	j	.L30
.L32:
	li	a1,0
	mv	s1,a1
	j	.L48
.L48:
	blt	s1,s2, .L49
	j	.L50
.L49:
	call	getint
	mv	a1,a0
	addi	a2,s1,0
	slli	a2,a2,2
	la	a3,list
	addi	a2,a2,0
	add	a2,a3,a2
	sw	a1,0(a2)
	addi	a1,s1,0
	slli	a2,a1,2
	la	a1,list
	addi	a2,a2,0
	add	a1,a1,a2
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a1,a1,2
	la	a2,cns
	addi	a1,a1,0
	add	a1,a2,a1
	lw	a1,0(a1)
	addi	a1,a1,1
	addi	a2,s1,0
	slli	a2,a2,2
	la	a3,list
	addi	a2,a2,0
	add	a2,a3,a2
	lw	a2,0(a2)
	addi	a2,a2,0
	slli	a2,a2,2
	la	a3,cns
	addi	a2,a2,0
	add	a2,a3,a2
	sw	a1,0(a2)
	addi	a1,s1,1
	mv	s1,a1
	j	.L48
.L50:
	la	a0,cns
	addi	a6,a0,4
	la	a0,cns
	addi	a0,a0,8
	la	a1,cns
	addi	a1,a1,12
	la	a2,cns
	addi	a2,a2,16
	la	a3,cns
	addi	a3,a3,20
	li	a4,0
	mv	a5,a4
	lw	a3,0(a3)
	mv	a4,a3
	lw	a2,0(a2)
	mv	a3,a2
	lw	a1,0(a1)
	mv	a2,a1
	lw	a0,0(a0)
	mv	a1,a0
	lw	a0,0(a6)
	call	dfs
	mv	s1,a0
	mv	a0,s1
	call	putint
	mv	a0,s1
	j	.L51
.L51:
	ld	s1,0(s0)
	ld	s2,8(s0)
	ld	s3,16(s0)
	ld	s0,24(s0)
	ld	ra,32(s0)
	addi	sp,sp,8
	addi	sp,sp,40
	ret
