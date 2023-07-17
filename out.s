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
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	beq	a0,a1, .L2
	j	.L3
.L2:
	li	a0,1
	j	.L5
.L5:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
.L3:
	j	.L4
.L4:
	li	a0,0
	j	.L5
	.text
	.global dfs
dfs:
	addi	sp,sp,-88
	sd	ra,80(sp)
	sd	s0,72(sp)
	sd	s9,64(sp)
	sd	s8,56(sp)
	sd	s7,48(sp)
	sd	s6,40(sp)
	sd	s5,32(sp)
	sd	s4,24(sp)
	sd	s3,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,88
	addi	sp,sp,-8
	mv	a7,a0
	li	a6,18
	mul	a6,a6,a7
	add	a6,a1,a6
	li	a7,18
	mul	a6,a7,a6
	add	a6,a2,a6
	li	a7,18
	mul	a6,a7,a6
	add	a6,a3,a6
	li	a7,18
	mul	a6,a7,a6
	add	a7,a4,a6
	li	a6,7
	mul	a6,a6,a7
	add	a6,a5,a6
	slli	s1,a6,2
	la	a6,dp
	mv	a7,s1
	add	a7,a6,a7
	li	a6,-1
	lw	a7,0(a7)
	bne	a7,a6, .L7
	j	.L8
.L7:
	la	a0,dp
	mv	a1,s1
	add	a0,a0,a1
	lw	a0,0(a0)
	j	.L10
.L10:
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s3,16(sp)
	ld	s4,24(sp)
	ld	s5,32(sp)
	ld	s6,40(sp)
	ld	s7,48(sp)
	ld	s8,56(sp)
	ld	s9,64(sp)
	ld	s0,72(sp)
	ld	ra,80(sp)
	addi	sp,sp,88
	ret
.L8:
	j	.L9
.L9:
	add	a6,a0,a1
	add	a6,a6,a2
	add	a6,a6,a3
	add	a6,a6,a4
	beqz	a6, .L11
	j	.L12
.L11:
	li	a0,1
	j	.L10
.L12:
	bnez	a0, .L14
	j	.L15
.L14:
	li	a6,2
	mv	s4,a1
	mv	a1,a6
	mv	s2,a5
	mv	s5,a4
	mv	s6,a2
	mv	s7,a3
	mv	s3,a0
	mv	a0,a5
	call	equal
	mv	a1,s4
	mv	a3,s7
	mv	a2,s6
	mv	a4,s5
	mv	a5,s2
	mv	a6,a0
	mv	a0,s3
	sub	s2,a0,a6
	addi	a6,a0,-1
	li	a7,1
	mv	s5,a5
	mv	a5,a7
	mv	s4,a4
	mv	s6,a3
	mv	s7,a2
	mv	s8,a1
	mv	s3,a0
	mv	a0,a6
	call	dfs
	mv	a1,s8
	mv	a2,s7
	mv	a3,s6
	mv	a4,s4
	mv	a5,s5
	mv	a6,a0
	mv	a0,s3
	mul	a6,s2,a6
	li	a7,1000000007
	rem	a6,a6,a7
	mv	s2,a6
	j	.L16
.L16:
	bnez	a1, .L17
	j	.L18
.L17:
	li	a6,3
	mv	s5,a1
	mv	a1,a6
	mv	s3,a5
	mv	s6,a4
	mv	s7,a2
	mv	s8,a3
	mv	s4,a0
	mv	a0,a5
	call	equal
	mv	a1,s5
	mv	a3,s8
	mv	a2,s7
	mv	a4,s6
	mv	a5,s3
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
	add	a6,s2,a6
	li	a7,1000000007
	rem	a6,a6,a7
	mv	s2,a6
	j	.L19
.L19:
	bnez	a2, .L20
	j	.L21
.L20:
	li	a6,4
	mv	s4,a1
	mv	a1,a6
	mv	s3,a5
	mv	s5,a4
	mv	s7,a2
	mv	s8,a3
	mv	s6,a0
	mv	a0,a5
	call	equal
	mv	a1,s4
	mv	a3,s8
	mv	a2,s7
	mv	a4,s5
	mv	a5,s3
	mv	a6,a0
	mv	a0,s6
	sub	s3,a2,a6
	addi	a6,a1,1
	addi	a7,a2,-1
	li	s4,3
	mv	s5,a5
	mv	a5,s4
	mv	s6,a4
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
	mv	a4,s6
	mv	a5,s5
	mv	a6,a0
	mv	a0,s4
	mul	a6,s3,a6
	add	a6,s2,a6
	li	a7,1000000007
	rem	a6,a6,a7
	mv	s2,a6
	j	.L22
.L22:
	bnez	a3, .L23
	j	.L24
.L23:
	li	a6,5
	mv	s5,a1
	mv	a1,a6
	mv	s4,a4
	mv	s6,a2
	mv	s7,a3
	mv	s3,a0
	mv	a0,a5
	call	equal
	mv	a1,s5
	mv	a3,s7
	mv	a2,s6
	mv	a4,s4
	mv	a5,a0
	mv	a0,s3
	sub	s5,a3,a5
	addi	a6,a2,1
	addi	a7,a3,-1
	li	a5,4
	mv	s3,a4
	mv	s6,a3
	mv	a3,a7
	mv	s7,a2
	mv	a2,a6
	mv	s8,a1
	mv	s4,a0
	call	dfs
	mv	a1,s8
	mv	a2,s7
	mv	a3,s6
	mv	a4,s3
	mv	a5,a0
	mv	a0,s4
	mul	a5,s5,a5
	add	a5,s2,a5
	li	a6,1000000007
	rem	a5,a5,a6
	mv	s2,a5
	j	.L25
.L25:
	bnez	a4, .L26
	j	.L27
.L26:
	addi	a3,a3,1
	addi	a6,a4,-1
	li	a5,5
	mv	s3,a4
	mv	a4,a6
	call	dfs
	mv	a4,s3
	mul	a0,a4,a0
	add	a1,s2,a0
	li	a0,1000000007
	rem	a0,a1,a0
	mv	a1,a0
	j	.L28
.L28:
	li	a0,1000000007
	rem	a0,a1,a0
	la	a2,dp
	mv	a1,s1
	add	a1,a2,a1
	sw	a0,0(a1)
	la	a0,dp
	mv	a1,s1
	add	a0,a0,a1
	lw	a0,0(a0)
	j	.L10
.L27:
	mv	a1,s2
	j	.L28
.L24:
	j	.L25
.L21:
	j	.L22
.L18:
	j	.L19
.L15:
	li	a6,0
	mv	s2,a6
	j	.L16
	.text
	.global main
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,32
	call	getint
	mv	s1,a0
	li	a0,0
	j	.L30
.L30:
	li	a1,18
	blt	a0,a1, .L31
	j	.L32
.L31:
	li	a1,0
	j	.L33
.L33:
	li	a2,18
	blt	a1,a2, .L34
	j	.L35
.L34:
	li	a2,0
	mv	a6,a2
	j	.L36
.L36:
	li	a2,18
	blt	a6,a2, .L37
	j	.L38
.L37:
	li	a2,0
	mv	a5,a2
	j	.L39
.L39:
	li	a2,18
	blt	a5,a2, .L40
	j	.L41
.L40:
	li	a2,0
	mv	a4,a2
	j	.L42
.L42:
	li	a2,18
	blt	a4,a2, .L43
	j	.L44
.L43:
	li	a2,0
	j	.L45
.L45:
	li	a3,7
	blt	a2,a3, .L46
	j	.L47
.L46:
	mv	a3,a0
	li	a7,18
	mul	a3,a7,a3
	add	a7,a1,a3
	li	a3,18
	mul	a3,a3,a7
	add	a7,a6,a3
	li	a3,18
	mul	a3,a3,a7
	add	a3,a5,a3
	li	a7,18
	mul	a3,a7,a3
	add	a7,a4,a3
	li	a3,7
	mul	a3,a3,a7
	add	a3,a2,a3
	slli	a7,a3,2
	la	a3,dp
	add	a3,a3,a7
	li	a7,-1
	sw	a7,0(a3)
	addi	a2,a2,1
	j	.L45
.L47:
	addi	a2,a4,1
	mv	a4,a2
	j	.L42
.L44:
	addi	a2,a5,1
	mv	a5,a2
	j	.L39
.L41:
	addi	a2,a6,1
	mv	a6,a2
	j	.L36
.L38:
	addi	a1,a1,1
	j	.L33
.L35:
	addi	a0,a0,1
	j	.L30
.L32:
	li	a0,0
	mv	s2,a0
	j	.L48
.L48:
	blt	s2,s1, .L49
	j	.L50
.L49:
	call	getint
	mv	a1,s2
	slli	a1,a1,2
	la	a3,list
	mv	a2,a1
	add	a2,a3,a2
	sw	a0,0(a2)
	la	a2,list
	mv	a0,a1
	add	a0,a2,a0
	lw	a0,0(a0)
	slli	a2,a0,2
	la	a0,cns
	add	a0,a0,a2
	lw	a0,0(a0)
	addi	a0,a0,1
	la	a2,list
	add	a1,a2,a1
	lw	a1,0(a1)
	slli	a2,a1,2
	la	a1,cns
	add	a1,a1,a2
	sw	a0,0(a1)
	addi	a0,s2,1
	mv	s2,a0
	j	.L48
.L50:
	la	a0,cns
	addi	a6,a0,4
	la	a0,cns
	addi	a0,a0,8
	la	a1,cns
	addi	a2,a1,12
	la	a1,cns
	addi	a1,a1,16
	la	a3,cns
	addi	a3,a3,20
	li	a4,0
	mv	a5,a4
	lw	a3,0(a3)
	mv	a4,a3
	lw	a1,0(a1)
	mv	a3,a1
	lw	a1,0(a2)
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
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s0,16(sp)
	ld	ra,24(sp)
	addi	sp,sp,32
	ret
